
/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/

/** @file
 *
 *	GFX drawing function control Drivers linux module
 *
 *  author      sinchul.jung (sinchul.jung@lge.com)
 *				raxis.lim    (raxis.lim@lge.com)
 *
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

int 	g_gfx_perf_log = 0;		/* disable by default */

#if 0

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/workqueue.h>/**< For working queue */
#include <linux/interrupt.h>
#include <linux/sched.h>	/* for schedule_timeout */
#include <linux/dma-mapping.h>
#include <asm/cacheflush.h>

#include "gfx_impl.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define KBYTE               1024
#define MBYTE               1048576

#define		MASK_RGB4		0x00f8f8f8

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define SCALER_GET_A(color) 	((color)>>24 & 0xff)
#define SCALER_GET_R(color) 	((color)>>16 & 0xff)
#define SCALER_GET_G(color) 	((color)>> 8 & 0xff)
#define SCALER_GET_B(color) 	((color)     & 0xff)
#define DIV255(value)       	((((value)<<8)+(value)+0xff)>>16)

#define get_min(x,y)        	(((x)>(y))?(y):(x))
#define get_max(x,y)        	(((x)>(y))?(x):(y))

#define GetSrcColor(x,y)        *( src_image + (UINT32)( (int)y * src_inc + (int)x ) )
#define SetDstColor(x,y,col)    *( dst_image + (UINT32)( y * dst_inc + x ) ) = col

#define MARK_TICK(tk)				do { if ( g_gfx_perf_log >= 0 ) (tk) = OS_GetMsecTicks(); } while(0)
#define	REPORT_LOG(lvl,fmt,args...)	do { if ( g_gfx_perf_log == lvl ) printk("[x] %s:%d -- " fmt, __F__, __L__, ##args ); } while(0)

#define	NOP_5()					do { asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); } while(0)
#define NOP_25()				do { NOP_5(); NOP_5(); NOP_5(); NOP_5(); NOP_5(); } while(0)
#define NOP_125()				do { NOP_25(); NOP_25(); NOP_25(); NOP_25(); NOP_25(); } while(0)
#define NOP_250()				do { NOP_125(); NOP_125(); } while(0)
#define NOP_1000()				do { NOP_250(); NOP_250(); } while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
    UINT32*         basePtr;        /* base address of data buffer */
    int             stride;         /* stride info in data buffer */
    SINT16          width;          /* width dimension in data buffer */
    SINT16          height;         /* height dimension in data buffer */
}
LX_GFX_SW_PORT_T;

typedef struct { UINT8	a, r, g, b; } RGBPXL;

typedef int (*GFX_BILINEAR_FUNC)(LX_GFX_SW_PORT_T*, LX_RECT_T*, LX_GFX_SW_PORT_T*, LX_RECT_T* );

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int GFX_BilinearScaler0	( LX_GFX_SW_PORT_T*, LX_RECT_T*, LX_GFX_SW_PORT_T*, LX_RECT_T* );
static int GFX_BilinearScaler1	( LX_GFX_SW_PORT_T*, LX_RECT_T*, LX_GFX_SW_PORT_T*, LX_RECT_T* );
static int GFX_BilinearScaler2	( LX_GFX_SW_PORT_T*, LX_RECT_T*, LX_GFX_SW_PORT_T*, LX_RECT_T* );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static  UINT16  mulTbl[256][256];
static  BOOLEAN fMulTblInitDone = FALSE;

static	GFX_BILINEAR_FUNC	g_bilinear_func_list[] = 
{
	GFX_BilinearScaler2,	/* default */
	GFX_BilinearScaler0,	/* 100% float based original bilinear algorithm */
	GFX_BilinearScaler1,	/* some optimized bilinear algorithm */
	GFX_BilinearScaler2,	/* some pooer image but high speed algorithm */
};

/*========================================================================================
	Implementation Group
========================================================================================*/
/**	software based scaler
 *
 *
 */
int GFX_RunSwScale(LX_GFX_SW_SCALE_CTRL_PARAM_T* param)
{
	int			i,j;
	int			ret = RET_ERROR;

	OS_CACHE_MAP_T		src_cache_map;
	OS_CACHE_MAP_T		dst_cache_map;

	LX_GFX_SW_PORT_T	src_port;
	LX_GFX_SW_PORT_T	dst_port;

	UINT64	tk0, tk1, tk2, tk3;
	UINT32	src_remap_offset, dst_remap_offset;
	int		src_remap_size, dst_remap_size;
	UINT32*	src_phys_start;
	UINT32*	dst_phys_start;

    GFX_SURFACE_OBJ_T*   src0_surface = &(g_gfx_surf_list[param->src0.surface_fd]);
    GFX_SURFACE_OBJ_T*   dst_surface  = &(g_gfx_surf_list[param->dst.surface_fd]);

	tk0 = tk1 = tk2 = tk3 = 0;

	/* make calculation table */
    if ( fMulTblInitDone == FALSE )
    {
        for ( i=0; i <= 0xff; i++ )
        for ( j=0; j <= 0xff; j++ )
        {
            mulTbl[i][j] = i*j;
        }
        fMulTblInitDone = TRUE;
    }

MARK_TICK(tk0);

	memset( &src_port, 0x0, sizeof(LX_GFX_SW_PORT_T));
	memset( &dst_port, 0x0, sizeof(LX_GFX_SW_PORT_T));

	/* make src port */
	src_remap_offset	= (src0_surface->surf.stride>>2) * param->src0.rect.y + param->src0.rect.x;	/* 4byte aligned */
	src_remap_size		= src0_surface->surf.stride * param->src0.rect.h;
	dst_remap_offset	= ( dst_surface->surf.stride>>2) * param->dst.rect.y  + param->dst.rect.x;	/* 4byte aligned */
	dst_remap_size		= dst_surface->surf.stride  * param->dst.rect.h;

	src_phys_start		= (UINT32*)src0_surface->surf.phys_addr + src_remap_offset;
	dst_phys_start		= (UINT32*) dst_surface->surf.phys_addr + dst_remap_offset;

	ret = OS_OpenCacheMap ( &src_cache_map, (void*)src_phys_start, src_remap_size );
	GFX_CHECK_ERROR( ret != RET_OK, goto func_exit, "can't ioremap src port\n");

	src_port.basePtr 		= (UINT32*)src_cache_map.virt_addr;
	src_port.width			= src0_surface->surf.width;
	src_port.height			= src0_surface->surf.height;
	src_port.stride			= src0_surface->surf.stride;

	param->src0.rect.x		= 0;
	param->src0.rect.y		= 0;

	/* make dst port */
	ret = OS_OpenCacheMap ( &dst_cache_map, (void*)dst_phys_start, dst_remap_size );
	GFX_CHECK_ERROR( ret != RET_OK, goto func_exit, "can't ioremap dst port\n");
	dst_port.basePtr		= (UINT32*)dst_cache_map.virt_addr;
	dst_port.width			= dst_surface->surf.width;
	dst_port.height			= dst_surface->surf.height;
	dst_port.stride			= dst_surface->surf.stride;

	param->dst.rect.x		= 0;
	param->dst.rect.y		= 0;

	OS_InvalCacheMap( &src_cache_map, 0x0, src_remap_size );
	OS_InvalCacheMap( &dst_cache_map, 0x0, dst_remap_size );

MARK_TICK(tk1);

    switch( param->scaler_mode & 0xff00 )
    {
        case LX_GFX_SW_SCALER_MODE_LINEAR:
        case LX_GFX_SW_SCALER_MODE_BILINEAR:
        {
            GFX_BILINEAR_FUNC bilinear_func = NULL;
#if 0
            int sub_algo = (param->scaler_mode & 0xff);
            GFX_CHECK_ERROR( sub_algo > NELEMENTS(g_bilinear_func_list), goto func_exit, "unkown bilinear 0x%x\n", param->scaler_mode );
            bilinear_func = g_bilinear_func_list[sub_algo];
#else
            bilinear_func = g_bilinear_func_list[0];	/* use just default value */
#endif
            ret = bilinear_func( &src_port, &param->src0.rect, &dst_port, &param->dst.rect );
        }
        break;

        default:
        {
            GFX_ERROR("unkonwn scaler mode 0x%x\n", param->scaler_mode );
        }
        break;
    }
MARK_TICK(tk2);

	OS_CleanCacheMap( &dst_cache_map, 0x0, dst_remap_size );

func_exit:
	OS_CloseCacheMap( &src_cache_map );
	OS_CloseCacheMap( &dst_cache_map );

MARK_TICK(tk3);
	REPORT_LOG( 1, "scaler mode 0x%x (%dx%d)->(%d,%d) diff0 %d, dif1 %d, diff2 %d\n", 
						param->scaler_mode, 
						param->src0.rect.w, param->src0.rect.h,
						param->dst.rect.w, param->dst.rect.h,
						(int)(tk1-tk0), (int)(tk2-tk1), (int)(tk3-tk2) );
	return ret;
}

#if 0	/* DO NOT support half scaler */

#undef	USE_FULL_READ_MEMCPY
#undef	USE_FULL_WRITE_MEMCPY
#define	USE_FAST_PIXEL_COMPOSITION
#define	USE_FOUR_PIXEL

volatile UINT32	xx;

static int GFX_HalfOnlyScaler(	LX_GFX_SW_PORT_T*    	pSrcPort,
								LX_RECT_T*                  pSrcRect,
								LX_GFX_SW_PORT_T*     pDstPort,
								LX_RECT_T*                  pDstRect )
{
	int		ret = RET_ERROR;
	UINT64	tk0, tk1;

	int		src_pitch, dst_pitch, src_inc, dst_inc;
	UINT32 *src_image, *dst_image;

	src_pitch 	= pSrcPort->stride;	/* src pitch */
	dst_pitch 	= pDstPort->stride;	/* dst pitch */
	src_inc		= src_pitch>>2;		/* src inc 	*/
	dst_inc		= dst_pitch>>2;		/* src inc 	*/

	src_image	=  (UINT32*)pSrcPort->basePtr + pSrcRect-> y * src_inc + pSrcRect->x;
	dst_image	=  (UINT32*)pDstPort->basePtr + pDstRect-> y * dst_inc + pDstRect->x;

//	printk(" optimized half only alogorithm started.. (%d,%d,%d,%d) -> (%d,%d,%d,%d)\n",
//						pSrcRect->x, pSrcRect->y, pSrcRect->w, pSrcRect->h, 
//						pDstRect->x, pDstRect->y, pDstRect->w, pDstRect->h ); 

MARK_TICK(tk0);
#ifdef USE_FULL_READ_MEMCPY
	UINT64	rtk0, rtk1;

	UINT32*	src_nocache	= src_image;
	UINT32*	src_buffer	= OS_Malloc( src_pitch * pSrcRect->h ); 

MARK_TICK(rtk0);
	memcpy( src_buffer, src_nocache, src_pitch * pSrcRect->h );
MARK_TICK(rtk1);
//	printk("read  completed -- #1 : diff tick = %d\n", (int)(rtk1-rtk0) );

	src_image	= src_buffer;
#endif

#ifdef USE_FULL_WRITE_MEMCPY
	UINT32*	dst_nocache	= dst_image;
	UINT32*	dst_buffer	= OS_Malloc( dst_pitch * pDstRect->h );

	dst_image	= dst_buffer;
#endif

	{
		int	 	x, y;
		register UINT32	color1;
		register UINT32	color2;
		register UINT32	color3;
		register UINT32	color4;
//		UINT8	a, r, g, b;

		/* calculate scale value */

		int		i, j;

		UINT32* src0_img_ptr;
		UINT32* src1_img_ptr;
		UINT32* dst_img_ptr;
		UINT32*	src_img_base = src_image;
		UINT32* dst_img_base = dst_image;

		UINT32	c;

		UINT64	ctk0, ctk1;
MARK_TICK(ctk0);

		/* dst 가 src 의 1/2 이기 때문에 이 가정에 근거하여 작업을 진행한다 */
		for( j=pDstRect->h, y=0; j>0 ; j-- )
		{
			src0_img_ptr	= src_img_base;
			src1_img_ptr	= src_img_base + src_inc;
			dst_img_ptr 	= dst_img_base;

			for( i=pDstRect->w, x=0 ; i>0; i-- )
			{
				color1	= *src0_img_ptr++;  color2 = *src0_img_ptr++;
				color3	= *src1_img_ptr++;  color4 = *src1_img_ptr++;

				/* 기존 code 대비 algorithm 의 효율성 측면이 높아 당분간 아래 코드 사용함 */
#ifdef USE_FAST_PIXEL_COMPOSITION

				if ( color1 )
				{
#ifdef USE_FOUR_PIXEL
					c = ((MASK_RGB4 & color1) + (MASK_RGB4 & color2) + (MASK_RGB4 & color3) + (MASK_RGB4 & color4)) >> 2;
#else
					c = ((MASK_RGB4 & color1) + (MASK_RGB4 & color4)) >> 1;
#endif
					*dst_img_ptr++ = ( color1 & 0xff000000 ) | ( c & 0x00ffffff );
				}
				else
				{
					dst_img_ptr++;
				}
#else
				if ( color1 ) //|| color4 )
				{
					a = ( SCALER_GET_A(color1) + SCALER_GET_A(color2) + SCALER_GET_A(color3) + SCALER_GET_A(color4) ) >> 2;
					r = ( SCALER_GET_R(color1) + SCALER_GET_R(color2) + SCALER_GET_R(color3) + SCALER_GET_R(color4) ) >> 2;
					g = ( SCALER_GET_G(color1) + SCALER_GET_G(color2) + SCALER_GET_G(color3) + SCALER_GET_G(color4) ) >> 2;
					b = ( SCALER_GET_B(color1) + SCALER_GET_B(color2) + SCALER_GET_B(color3) + SCALER_GET_B(color4) ) >> 2;

					// Set output
					*dst_img_ptr++ = (a<<24) | (r<<16) | (g<<8) | (b);
				}
				else
				{
					*dst_img_ptr++ = 0x0;
				}
#endif
			}

			src_img_base += (src_inc<<1);
			dst_img_base += dst_inc;
		}
MARK_TICK(ctk1);
		REPORT_LOG( 2, "calc  completed -- #2 : diff tick = %d\n", (int)(ctk1-ctk0) );
	}

#ifdef USE_FULL_WRITE_MEMCPY
	UINT64	wtk0, wtk1;

MARK_TICK(wtk0);
	memcpy( dst_nocache, dst_buffer, dst_pitch * pDstRect->h );
MARK_TICK(wtk1);
//	printk("write completed -- #3 : diff tick = %d\n", (int)(wtk1-wtk0) );

	OS_Free( dst_buffer );
#endif

#ifdef USE_FULL_READ_MEMCPY
	OS_Free( src_buffer );
#endif

	ret = RET_OK;

MARK_TICK(tk1);
//	printk("stretch completed -- #4 : diff tick = %d\n", (int)(tk1-tk0) );

	return ret;
}
#endif

/** 특정 데이터를 msec 동안 처리한 경우 걔략적으로 KB/sec 를 계산하여 리턴한다.
 *
 *	@param msec [IN] 처리하는데 걸린 msec 시간.
 *	@param nDataLen [IN] 처리된 모든 데이터의 양 
 *	@return KB/sec 계산값
 */
#if 0
static	UINT32 CalcDataPerformance ( UINT32 msec, UINT32 nDataLen )
{
	return ( nDataLen * 1000 / msec ) / KBYTE;	
}
#endif

static int GFX_BilinearScaler0(	LX_GFX_SW_PORT_T*     pSrcPort,
								LX_RECT_T*            pSrcRect,
								LX_GFX_SW_PORT_T*     pDstPort,
								LX_RECT_T*            pDstRect )
{
	/* DO NOT use float !!! */
#if 1
	return GFX_BilinearScaler1 ( pSrcPort, pSrcRect, pDstPort, pDstRect );
#else
	int		ret = RET_ERROR;

	UINT32	color;
	float	fX, fY;
	float	xScale, yScale;

	UINT64	tk0, tk1;
	int		src_pitch, dst_pitch, src_inc, dst_inc;
	UINT32 *src_image, *dst_image;

	src_pitch 	= pSrcPort->stride;	/* src pitch */
	dst_pitch 	= pDstPort->stride;	/* dst pitch */
	src_inc		= src_pitch>>2;		/* src inc 	*/
	dst_inc		= dst_pitch>>2;		/* src inc 	*/

	tk0 = tk1 = 0;

	src_image   =  pSrcPort->basePtr + pSrcRect-> y * src_inc + pSrcRect->x;
	dst_image   =  pDstPort->basePtr + pDstRect-> y * dst_inc + pDstRect->x;

	REPORT_LOG( 2, " original bilinear alogorithm started.. (%d,%d,%d,%d) -> (%d,%d,%d,%d)\n",
						pSrcRect->x, pSrcRect->y, pSrcRect->w, pSrcRect->h, 
						pDstRect->x, pDstRect->y, pDstRect->w, pDstRect->h ); 
MARK_TICK(tk0);
	xScale = (float)pSrcRect->w / (float)pDstRect->w;
	yScale = (float)pSrcRect->h / (float)pDstRect->h;

	if ( !( pSrcRect->w > pDstRect->w && pSrcRect->h > pDstRect->h ) ) 
	{
		long x, y;
		//?1999 Steve McMahon (steve@dogma.demon.co.uk)
		long ifX, ifY, ifX1, ifY1, src_w_max, src_h_max;
		float ia1, ia2, ir1, ir2, ig1, ig2, ib1, ib2, dx, dy;
		UINT8  a,r,g,b;
		RGBPXL rgb1, rgb2, rgb3, rgb4;
		src_w_max = pSrcRect->w-1;
		src_h_max = pSrcRect->h-1;

		for( y=0; y<pDstRect->h ; y++ )
		{
			fY = y * yScale;
			ifY = (int)fY;
			ifY1 = get_min(src_h_max, ifY+1);
			dy = fY - ifY;

			for( x=0; x<pDstRect->w ; x++ )
			{
				fX = x * xScale;
				ifX = (int)fX;
				ifX1 = get_min(src_w_max, ifX+1);
				dx = fX - ifX;
				// Interpolate using the four nearest pixels in the source
				{
					UINT8* iDst;
					iDst = (UINT8*)(src_image + (UINT32)(ifY * ( src_pitch>>2 ) + ifX));
					rgb1.b = *iDst++;	rgb1.g= *iDst++;	rgb1.r =*iDst++; rgb1.a = *iDst++; 
					iDst = (UINT8*)(src_image + (UINT32)(ifY * ( src_pitch>>2 ) + ifX1));
					rgb2.b = *iDst++;	rgb2.g= *iDst++;	rgb2.r =*iDst++; rgb2.a = *iDst++; 
					iDst = (UINT8*)(src_image + (UINT32)(ifY1 *( src_pitch>>2 ) + ifX));
					rgb3.b = *iDst++;	rgb3.g= *iDst++;	rgb3.r =*iDst++; rgb3.a = *iDst++; 
					iDst = (UINT8*)(src_image + (UINT32)(ifY1 *( src_pitch>>2 ) + ifX1));
					rgb4.b = *iDst++;	rgb4.g= *iDst++;	rgb4.r =*iDst++; rgb4.a = *iDst++; 
				}
				// Interplate in x direction:
				ia1 = rgb1.a * (1 - dy) + rgb3.a * dy;
				ir1 = rgb1.r * (1 - dy) + rgb3.r * dy;
				ig1 = rgb1.g * (1 - dy) + rgb3.g * dy;
				ib1 = rgb1.b * (1 - dy) + rgb3.b * dy;
				ia2 = rgb2.a * (1 - dy) + rgb4.a * dy;
				ir2 = rgb2.r * (1 - dy) + rgb4.r * dy;
				ig2 = rgb2.g * (1 - dy) + rgb4.g * dy;
				ib2 = rgb2.b * (1 - dy) + rgb4.b * dy;
				// Interpolate in y:
				a = (UINT8)(ia1 * (1 - dx) + ia2 * dx);
				r = (UINT8)(ir1 * (1 - dx) + ir2 * dx);
				g = (UINT8)(ig1 * (1 - dx) + ig2 * dx);
				b = (UINT8)(ib1 * (1 - dx) + ib2 * dx);
				// Set output
				color = (a<<24) | (r<<16) | (g<<8) | (b);
				SetDstColor( x, y, color );
			}
		} 
	} 
	else 
	{
		//high resolution shrink, thanks to Henrik Stellmann <henrik.stellmann@volleynet.de>
		const long ACCURACY = 1000;
		long i,j; // index for faValue
		long x,y; // coordinates in  source image
		UINT8* pSource;
		UINT8* pDest  = (UINT8*)dst_image;
		long* naAccu  = (long*)OS_Malloc( sizeof(long) * ( 4 * pDstRect->w + 4) );
		long* naCarry = (long*)OS_Malloc( sizeof(long) * ( 4 * pDstRect->w + 4) );
		long* naTemp;
		long  nWeightX,nWeightY;
		float fEndX;
		long nScale = (long)(ACCURACY * xScale * yScale);

		int u, v = 0; // coordinates in dest image
		float fEndY = yScale - 1.0f;

		memset(naAccu,  0, sizeof(long) * 4 * pDstRect->w);
		memset(naCarry, 0, sizeof(long) * 4 * pDstRect->w);

		for (y = 0; y < pSrcRect->h; y++)
		{
//			info.nProgress = (long)(100*y/pSrcRect->h); //<Anatoly Ivasyuk>
//			if (info.nEscape) break;
			pSource = (UINT8*)( src_image + y * ( src_pitch>>2 ) );
			u = i = 0;
			fEndX = xScale - 1.0f;
			if ((float)y < fEndY)        // complete source row goes into dest row
			{
				for (x = 0; x < pSrcRect->w; x++)
				{
					if ((float)x < fEndX)       // complete source pixel goes into dest pixel
					{
						for (j = 0; j < 4; j++)	naAccu[i + j] += (*pSource++) * ACCURACY;
					} 	// source pixel is splitted for 2 dest pixels
					else
					{
						nWeightX = (long)(((float)x - fEndX) * ACCURACY);
						for (j = 0; j < 4; j++)
						{
							naAccu[i] += (ACCURACY - nWeightX) * (*pSource);
							naAccu[4 + i++] += nWeightX * (*pSource++);
						}
						fEndX += xScale;
						u++;
					}
				}
			} 
			else 
			{       // source row is splitted for 2 dest rows       
				nWeightY = (long)(((float)y - fEndY) * ACCURACY);
				for (x = 0; x < pSrcRect->w; x++)
				{
					if ((float)x < fEndX)       // complete source pixel goes into 2 pixel
					{
						for (j = 0; j < 4; j++)
						{
							naAccu[i + j] += ((ACCURACY - nWeightY) * (*pSource));
							naCarry[i + j] += nWeightY * (*pSource++);
						}
					} 	// source pixel is splitted for 4 dest pixels
					else
					{
						nWeightX = (int)(((float)x - fEndX) * ACCURACY);
						for (j = 0; j < 4; j++) 
						{
							naAccu[i] += ((ACCURACY - nWeightY) * (ACCURACY - nWeightX)) * (*pSource) / ACCURACY;
							*pDest++ = (UINT8)(naAccu[i] / nScale);
							naCarry[i] += (nWeightY * (ACCURACY - nWeightX) * (*pSource)) / ACCURACY;
							naAccu[i + 4] += ((ACCURACY - nWeightY) * nWeightX * (*pSource)) / ACCURACY;
							naCarry[i + 4] = (nWeightY * nWeightX * (*pSource)) / ACCURACY;
							i++;
							pSource++;
						}
						fEndX += xScale;
						u++;
					}
				}
				if (u < pDstRect->w){ // possibly not completed due to rounding errors
					for (j = 0; j < 4; j++) *pDest++ = (UINT8)(naAccu[i++] / nScale);
				}
				naTemp = naCarry;
				naCarry = naAccu;
				naAccu = naTemp;
				memset(naCarry, 0, sizeof(int) * 4);    // need only to set first pixel zero
				pDest = (UINT8*)(dst_image + (++v * (dst_pitch>>2)));
				fEndY += yScale;
			}
		}
		if (v < pDstRect->h){	// possibly not completed due to rounding errors
			for (i = 0; i < 4 * pDstRect->w; i++) *pDest++ = (UINT8)(naAccu[i] / nScale);
		}
		OS_Free (naAccu);
		OS_Free (naCarry);
	}
	ret = RET_OK;
MARK_TICK(tk1);
	REPORT_LOG( 2, "simple bilinear mode -- #2 : diff tick = %d\n", (int)(tk1-tk0) );

	return ret;
#endif
}

/**
 *
 *	@note DDX 에 기반하여 구현되어 있으나 algorithm 에서 float 를 제거하고, 가급적 계산 성능을 
 *	올릴 수 있는 쪽으로 구현되어 있다.
 *	DFB 등 이미지 품질 위주의 함수등에서 사용함.
 */
static int GFX_BilinearScaler1	(	LX_GFX_SW_PORT_T*     pSrcPort,
									LX_RECT_T*            pSrcRect,
									LX_GFX_SW_PORT_T*     pDstPort,
									LX_RECT_T*            pDstRect )
{
	int		ret = RET_ERROR;
	int	 	x, y;
	int		ifX, ifY, ifX1, ifY1, src_w_max, src_h_max;
	UINT32	dX0, dX1, dY0, dY1;
	UINT32	a, r, g, b;
	UINT32	xScale, yScale;
	UINT32	color1,color2,color3,color4;

	UINT64	tk0, tk1;
	int		src_pitch, dst_pitch, src_inc, dst_inc;
	UINT32 *src_image, *dst_image;
	UINT16 *fX0Data, *fX1Data;
	UINT32 *dX0Data, *dX1Data;

	src_pitch 	= pSrcPort->stride;	/* src pitch */
	dst_pitch 	= pDstPort->stride;	/* dst pitch */
	src_inc		= src_pitch>>2;		/* src inc 	*/
	dst_inc		= dst_pitch>>2;		/* src inc 	*/

	tk0 = tk1 = 0;

	src_image   =  pSrcPort->basePtr + pSrcRect-> y * src_inc + pSrcRect->x;
	dst_image   =  pDstPort->basePtr + pDstRect-> y * dst_inc + pDstRect->x;

	src_w_max 	= pSrcRect->w-1;
	src_h_max 	= pSrcRect->h-1;

	/* calculate scale value */
	xScale = ( pSrcRect->w << 16 ) / pDstRect->w;
	yScale = ( pSrcRect->h << 16 ) / pDstRect->h;

	fX0Data = (UINT16*)OS_Malloc( sizeof(UINT16) * pDstRect->w );
	fX1Data = (UINT16*)OS_Malloc( sizeof(UINT16) * pDstRect->w );
	dX0Data	= (UINT32*)OS_Malloc( sizeof(UINT32) * pDstRect->w );
	dX1Data	= (UINT32*)OS_Malloc( sizeof(UINT32) * pDstRect->w );

	REPORT_LOG( 2, " optimized bilinear alogorithm started.. (%d,%d,%d,%d) -> (%d,%d,%d,%d)\n",
						pSrcRect->x, pSrcRect->y, pSrcRect->w, pSrcRect->h, 
						pDstRect->x, pDstRect->y, pDstRect->w, pDstRect->h ); 
	{
		UINT32	dX;
		int		i, j;

		UINT32	ia1, ia2, ir1, ir2, ig1, ig2, ib1, ib2;
		UINT32* dst_img_ptr;
		UINT32* dst_img_base = dst_image;

MARK_TICK(tk0);
		/* x 좌표에 대해서 미리 값들을 구해 놓는다. */
		for ( x=pDstRect->w-1 ; x>=0 ; x-- ) 
		{
			ifX		= x * xScale;
			dX		= (ifX&0xffff)>>8;
			*(dX0Data+x)  = dX;						/* save dx 		*/
			*(dX1Data+x)  = 0xff - dX;				/* save 1-dx 	*/
	
			ifX		>>= 16;							/* calc ifX 	*/
			ifX1	= get_min(src_w_max, ifX+1);	/* calc ifX+1 	*/
	
			*(fX0Data+x) = ifX;
			*(fX1Data+x) = ifX1;
		}

		for( j=pDstRect->h, y=0; j>0 ; j--, y++ )
		{
			ifY 	= y * yScale;
			dY0		= (ifY&0xffff)>>8;				/* save dy		*/
			dY1		= 0xff - dY0;					/* save 1-dy	*/
			ifY		>>= 16;							/* calc ifY		*/
			ifY1 	= get_min(src_h_max, ifY+1);	/* calc ifY+1	*/

			dst_img_ptr = dst_img_base;

			for( i=pDstRect->w, x=0 ; i>0; i--, x++ )
			{
				ifX 	= *(fX0Data + x );			/* fetch ifX	*/
				ifX1	= *(fX1Data + x );			/* fetch ifX+1	*/
				dX0		= *(dX0Data + x );			/* fetch dx		*/
				dX1		= *(dX1Data + x );			/* fetch 1-dx	*/

#define	GET_SRC_COLOR(x,y)	*( src_image + (UINT32)( (int)(y) * src_inc + (int)(x)) )
				color1 = GET_SRC_COLOR( ifX, ifY );

				if ( 1 ) //color1 )
				{
					color2 = GET_SRC_COLOR( ifX1, ifY );
					color3 = GET_SRC_COLOR( ifX , ifY1 );
					color4 = GET_SRC_COLOR( ifX1, ifY1 );
	
					ia1 = mulTbl[dY1][SCALER_GET_A(color1)] + mulTbl[dY0][ SCALER_GET_A(color3)];
					ir1 = mulTbl[dY1][SCALER_GET_R(color1)] + mulTbl[dY0][ SCALER_GET_R(color3)];
					ig1 = mulTbl[dY1][SCALER_GET_G(color1)] + mulTbl[dY0][ SCALER_GET_G(color3)];
					ib1 = mulTbl[dY1][SCALER_GET_B(color1)] + mulTbl[dY0][ SCALER_GET_B(color3)];
					ia2 = mulTbl[dY1][SCALER_GET_A(color2)] + mulTbl[dY0][ SCALER_GET_A(color4)];
					ir2 = mulTbl[dY1][SCALER_GET_R(color2)] + mulTbl[dY0][ SCALER_GET_R(color4)];
					ig2 = mulTbl[dY1][SCALER_GET_G(color2)] + mulTbl[dY0][ SCALER_GET_G(color4)];
					ib2 = mulTbl[dY1][SCALER_GET_B(color2)] + mulTbl[dY0][ SCALER_GET_B(color4)];
	
					ia1 = DIV255(ia1); ir1 = DIV255(ir1); ig1 = DIV255(ig1); ib1 = DIV255(ib1);
					ia2 = DIV255(ia2); ir2 = DIV255(ir2); ig2 = DIV255(ig2); ib2 = DIV255(ib2);

					a = mulTbl[dX1][ia1] + mulTbl[dX0][ia2];
					r = mulTbl[dX1][ir1] + mulTbl[dX0][ir2];
					g = mulTbl[dX1][ig1] + mulTbl[dX0][ig2];
					b = mulTbl[dX1][ib1] + mulTbl[dX0][ib2];

					a = DIV255(a); r = DIV255(r); g = DIV255(g); b = DIV255(b);

					// Set output
					*dst_img_ptr++ = (a<<24) | (r<<16) | (g<<8) | (b);
				}
				else
				{
					dst_img_ptr++;	
				}
			}

			dst_img_base += dst_inc;
		}
		OS_Free ( fX0Data );
		OS_Free ( fX1Data );
		OS_Free ( dX0Data );
		OS_Free ( dX1Data );
MARK_TICK(tk1);
		REPORT_LOG( 2, "stretch completed -- #2 : diff tick = %d\n", (int)(tk1-tk0) );
	}

	ret = RET_OK;

	return ret;
}

static int GFX_BilinearScaler2	(	LX_GFX_SW_PORT_T*    	pSrcPort,
									LX_RECT_T*              pSrcRect,
									LX_GFX_SW_PORT_T*     	pDstPort,
									LX_RECT_T*              pDstRect )
{
	int		ret = RET_ERROR;
	int		i, j;
	int	 	x, y;
	int		ifX, ifY, ifX1, ifY1, src_w_max, src_h_max;
	UINT32	xScale, yScale;
	UINT32	color1,color2,color3,color4;

	UINT64	tk0 = 0;
	UINT64	tk1 = 0;

	int		src_pitch 	= pSrcPort->stride;	/* src pitch */
	int		dst_pitch 	= pDstPort->stride;	/* dst pitch */
	int 	src_inc		= src_pitch>>2;		/* src inc 	*/
	int 	dst_inc		= dst_pitch>>2;		/* src inc 	*/

	UINT16* fX0Data;
	UINT16* fX1Data;

	UINT32*	src_image   =  pSrcPort->basePtr + pSrcRect-> y * src_inc + pSrcRect->x;
	UINT32*	dst_image   =  pDstPort->basePtr + pDstRect-> y * dst_inc + pDstRect->x;

	src_w_max 	= pSrcRect->w-1;
	src_h_max 	= pSrcRect->h-1;

	/* calculate scale value */
	xScale = ( pSrcRect->w << 16 ) / pDstRect->w;
	yScale = ( pSrcRect->h << 16 ) / pDstRect->h;

	fX0Data = (UINT16*)OS_Malloc( sizeof(UINT16) * pDstRect->w );
	fX1Data = (UINT16*)OS_Malloc( sizeof(UINT16) * pDstRect->w );

	REPORT_LOG( 2, " very simple bilinear alogorithm started.. (%d,%d,%d,%d) -> (%d,%d,%d,%d)\n",
						pSrcRect->x, pSrcRect->y, pSrcRect->w, pSrcRect->h, 
						pDstRect->x, pDstRect->y, pDstRect->w, pDstRect->h ); 
MARK_TICK(tk0);
	{
		UINT32 c;
		UINT32* dst_img_ptr;
		UINT32* dst_img_base = dst_image;

		/* x 좌표에 대해서 미리 값들을 구해 놓는다. */
		for ( x=pDstRect->w-1 ; x>=0 ; x-- ) 
		{
			ifX     = (x * xScale)>>16;
			ifX1    = get_min(src_w_max, ifX+1);

        	*(fX0Data+x) = ifX;
        	*(fX1Data+x) = ifX1;
		}

		for( j=pDstRect->h, y=0; j>0 ; j--, y++ )
		{
			ifY     = ( y * yScale ) >> 16;
			ifY1    = get_min(src_h_max, ifY+1);

			dst_img_ptr = dst_img_base;

			for( i=pDstRect->w, x=0 ; i>0; i--, x++ )
			{
				ifX 	= *(fX0Data + x );			/* fetch ifX	*/
				ifX1	= *(fX1Data + x );			/* fetch ifX+1	*/

#define	GET_SRC_COLOR(x,y)	*( src_image + (UINT32)( (int)(y) * src_inc + (int)(x)) )
				color1 = GET_SRC_COLOR( ifX, ifY );

				if ( color1 )
				{
					color2 = GET_SRC_COLOR( ifX1, ifY  );
					color3 = GET_SRC_COLOR( ifX,  ifY1 );
					color4 = GET_SRC_COLOR( ifX1, ifY1 );
	
#ifdef USE_FOUR_PIXEL
                	c = ((MASK_RGB4 & color1) + (MASK_RGB4 & color2) + (MASK_RGB4 & color3) + (MASK_RGB4 & color4)) >> 2;
#else
                	c = ((MASK_RGB4 & color1) + (MASK_RGB4 & color4)) >> 1;
#endif
					*dst_img_ptr++ = ( color1 & 0xff000000 ) | ( c & 0x00ffffff );
				}
				else
				{
					dst_img_ptr++;
				}
			}

			dst_img_base += dst_inc;
		}
		OS_Free ( fX0Data );
		OS_Free ( fX1Data );

MARK_TICK(tk1);
		REPORT_LOG( 2, "stretch completed -- #2 : diff tick = %d\n", (int)(tk1-tk0) );
	}

	ret = RET_OK;

	return ret;
}

/*========================================================================================
	Implementation Group
========================================================================================*/
/**	fast software blitter
 *	this function supports only simple copy with no attribute.
 *	@note src and dst should have the same pixel format
 *
 *	@param param [IN] blit param
 *	@return RET_OK if success, RET_ERROR otherwise
 *
 */
int GFX_RunSwBlit(LX_GFX_SW_BLIT_CTRL_PARAM_T* param)
{
	int			j;
	int			ret = RET_ERROR;

	UINT64				tk0, tk1;
	OS_CACHE_MAP_T		src_cache_map;
	OS_CACHE_MAP_T		dst_cache_map;

    GFX_SURFACE_OBJ_T*   src_surface = &(g_gfx_surf_list[param->src0.surface_fd]);
    GFX_SURFACE_OBJ_T*   dst_surface = &(g_gfx_surf_list[param->dst.surface_fd]);

	/* make src port */
	UINT8*		src_phys_start		= (UINT8*)GFX_GetPortBaseAddr( src_surface, &param->src0.rect );
	UINT8*		dst_phys_start		= (UINT8*)GFX_GetPortBaseAddr( dst_surface, &param->dst.rect );

	int			src_remap_size		= src_surface->surf.stride * param->src0.rect.h;
	int			dst_remap_size		= dst_surface->surf.stride  * param->dst.rect.h;

	int			line_length			= param->dst.rect.w * GFX_PxlFmt2Bpp( dst_surface->surf.pixel_format )/8;

	tk0 = tk1 = 0;

MARK_TICK(tk0);

	ret = OS_OpenCacheMap ( &src_cache_map, (void*)src_phys_start, src_remap_size );
	GFX_CHECK_ERROR( ret != RET_OK, goto func_exit, "can't ioremap src port\n");

	/* make dst port */
	ret = OS_OpenCacheMap ( &dst_cache_map, (void*)dst_phys_start, dst_remap_size );
	GFX_CHECK_ERROR( ret != RET_OK, goto func_exit, "can't ioremap dst port\n");

	OS_InvalCacheMap( &src_cache_map, 0x0, src_remap_size );
	OS_InvalCacheMap( &dst_cache_map, 0x0, dst_remap_size );

	{	
		UINT8*	src_image = (UINT8*)src_cache_map.virt_addr;
		UINT8*	dst_image = (UINT8*)dst_cache_map.virt_addr;

//		printk("do loop for h %d, len %d\n", param->dst.rect.h, line_length );

		for( j=param->dst.rect.h; j>0; j-- )
		{
			memcpy( dst_image, src_image, line_length );

			src_image += src_surface->surf.stride;
			dst_image += dst_surface->surf.stride;
 		}

		OS_CleanCacheMap( &dst_cache_map, 0x0, dst_remap_size );
	}
func_exit:
	OS_CloseCacheMap( &src_cache_map );
	OS_CloseCacheMap( &dst_cache_map );

MARK_TICK(tk1);
	REPORT_LOG( 2, "sw blit completed -- #2 : diff tick = %d\n", (int)(tk1-tk0) );

	return ret;
}

#endif
