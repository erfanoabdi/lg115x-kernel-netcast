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
 *  DVB-CI Command Interface Physical Layer
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  version	0.6
 *  date		2010.02.22
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
 */




/*=============================================================================+
| Include                                                                      |
+=============================================================================*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/cdev.h>

#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/memory.h>
#include "ci_io.h"
#include "ci_defs.h"
#include "os_util.h"

#include "ci_kapi.h"
#include "ci_drv.h"

/*=============================================================================+
| Local Symbol Definition                                                      |
+=============================================================================*/

#define MAX_CHECK_COUNT		500

#define MAX_POSS_BUF_SIZE	1000


/*=============================================================================+
| Global Variable Declaration                                                  |
+=============================================================================*/


UINT16	CiNegoBufSize[MAX_MOD_NUM] = {	0 };

extern volatile UINT32 guwDetectCard;
extern volatile S_CI_REG_T* gpstCIReg;
extern volatile UINT32 guwIsPowerRestart;

extern UINT32 gCI_KDRV_Delay[CI_D_ENUM_MAX];	// jinhwan.bae for delay


/*=============================================================================+
| Function Definition                                                          |
+=============================================================================*/



#define MAXIM_RETRY_COUNT ( 600 )	

/*----------------------------------------------------------------------------*/
/*
   NAME:         HW_IO_ResetSoft

   DESCRIPTION:  Perform software reset of hardware IO interface.

   PARAMETERS:   mId = module id

   RETURN VALUE: HW_IO_OK   = success
                 HW_IO_FAIL = fail
                                                                              */
/*----------------------------------------------------------------------------*/

/**
 *	Perform software reset of hardware IO interface
 */

int HW_IO_ResetSoft(MOD_ID mId)
{
	int		chkCnt = MAXIM_RETRY_COUNT;

	COMM_WR(mId, CI_RS);

	while( chkCnt-- )
	{
	
		if( !guwDetectCard )			// for ISR
			return HW_IO_FAIL;

		if( CHECK_FR(mId) )
			break;

		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_SOFT_RESET_CHECK_FR] );	
	}

/*	if( chkCnt <= 0 )
	{
		return HW_IO_FAIL;
	}
*/

	/* CI spec doesn't say that RS must be cleared on soft reset. but */
	/* in case of some modules RS must be cleared to complete soft reset */
	COMM_WR(mId, 0x00);

	// OS_MsecSleep(10) L9 Originally Blocked by comment , but Previous Exist, So Ready with 0 jinhwan.bae
	OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_END_SOFT_RESET] ); 

	return HW_IO_OK;	
}


/*----------------------------------------------------------------------------*/
/*
   NAME:         HW_IO_SetRS

   DESCRIPTION:  Set RS Bit 

   PARAMETERS:   mId = module id

   RETURN VALUE: HW_IO_OK   = success
                 HW_IO_FAIL = fail
                                                                              */
/*----------------------------------------------------------------------------*/

/**
 *	Perform set RS bit to 1 to softreset CAM
 *	Actually it's Netcast Request to meet CI+ 1.3 Confirmance Test
 *	FR Bit is not concerned, it's Netcast Needs, just return ASAP without FR checking.
 */

int HW_IO_SetRS(MOD_ID mId)
{
	COMM_WR(mId, CI_RS);
	
	return HW_IO_OK;	
}

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*
   NAME:         HW_IO_NegoBuf

   DESCRIPTION:  Perform buffer negotiation.

   PARAMETERS:   mId = module id

   RETURN VALUE: HW_IO_OK   = success
                 HW_IO_FAIL = fail
                                                                              */
/*----------------------------------------------------------------------------*/
/**
 *	Perform buffer negotiation
 */
int HW_IO_NegoBuf( MOD_ID mId, UINT32 *o_pwBufSize )
{

	int		chkCnt;
	UINT16	size;
	UINT16	sizeLen;


	if( NULL == o_pwBufSize )
	{
		CI_DTV_SOC_Message(CI_ERR,"CI-IO NegoBuf Null ptr failed!\n");

		return -1;
	}

	if( mId != MOD_A ) return HW_IO_FAIL;    // single module

	CiNegoBufSize[mId] = 0;

	CI_DTV_SOC_Message(CI_IO_INFO,"STATUS Register value before reset => 0x%x\n", STAT_RD(mId));

	// OS_MsecSleep(100) L9 Originally Blocked by comment , but Previous Exist, So Ready with 0 jinhwan.bae
	OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_NEGOBUF_BEFORE_SOFTRESET] );
	
	/* STEP 1: PERFORM SOFTWARE RESET ----------------------------------------*/
	if( HW_IO_ResetSoft(mId) != HW_IO_OK )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_NegoBuf : HW_IO_ResetSoft() failed\n");
		return HW_IO_FAIL;
	}


	/* STEP 2: READ BUFFER SIZE FROM MODULE ----------------------------------*/
	COMM_WR(mId, CI_SR);
	chkCnt = MAXIM_RETRY_COUNT;

	while( chkCnt-- )
	{
		if( !guwDetectCard )			// for ISR
			return HW_IO_FAIL;

		if( CHECK_DA(mId) )
			break;

		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_NEGOBUF_CHECK_DA] );
	}

	if( chkCnt <= 0 )
	{
		COMM_WR(mId, 0x00);
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_NegoBuf: data not available\n");
		return HW_IO_FAIL;
	}


	/* read the length of buffer size */
	sizeLen = (UINT16) SIZE_MS_RD(mId);
	sizeLen = (sizeLen<<8) & 0xFF00;
	sizeLen |= (UINT16) SIZE_LS_RD(mId);

	CI_DTV_SOC_Message(CI_IO_INFO,"Length of module buffer size = %d\n", sizeLen);

	/* read the high byte of buffer size */
	size = (UINT16) DATA_RD(mId);
	if( 2 == sizeLen )
	{
		/* read the low byte of buffer size */
		size = (size<<8)&0xFF00;
		size |= (UINT16) DATA_RD(mId);
	}

	CI_DTV_SOC_Message(CI_IO_INFO,"Module %c buffer size = %d\n", 'A'+mId, size);

	COMM_WR(mId, 0x00);


	/* STEP 3: DETERMINE BUFFER SIZE -----------------------------------------*/
	if( size<MOD_BUF_SIZE_MIN || size>MOD_BUF_SIZE_MAX )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_NegoBuf: invalid module buffer size");

		return HW_IO_FAIL;
	}

	if( size > HOST_BUF_SIZE )
		size = (UINT16) HOST_BUF_SIZE;

	CiNegoBufSize[mId] = size;

	*o_pwBufSize = size;

	CI_DTV_SOC_Message(CI_IO_INFO,"Negotiated buffer size = %d\n", size);



	/* STEP 4: WRITE BUFFER SIZE TO MODULE -----------------------------------*/
	COMM_WR(mId, CI_SW|CI_HC);

	chkCnt = MAXIM_RETRY_COUNT;

	while( chkCnt-- )
	{
		if( !guwDetectCard )			// for ISR
			return HW_IO_FAIL;

		if( CHECK_FR(mId) )
		{
			break;
		}

 		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_NEGOBUF_CHECK_FR] ); 
	}
	

	if( chkCnt <= 0 )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_NegoBuf: status error (FR=0)\n");
		return HW_IO_FAIL;
	}

	/* write the size of buffer size */
	SIZE_LS_WR(mId, (UINT8) 0x02);
	SIZE_MS_WR(mId, (UINT8) 0x00);

	/* write the high byte of buffer size */
	DATA_WR(mId, (UINT8) ((size>>8)&0xFF));

	/* write the low byte of buffer size */
	DATA_WR(mId, (UINT8) (size&0xFF));

	//  OS_MsecSleep(10) In L9, Previous 10 Exist. Please Refer to that at the problem. jinhwan.bae
 	OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_NEGOBUF_AFTER_WRITE_DATA] );

	COMM_WR(mId, 0x00);

	CI_DTV_SOC_Message(CI_IO_INFO,"Buffer negotiation SUCCESS\n");


	return HW_IO_OK;
}


/**
 *	Perform Read from CI Module
 */
int	HW_IO_Read( MOD_ID mId, UINT8 *o_pbyData, UINT16 *io_pwDataBufSize )
{
	int		chkCnt;
	UINT16	size;
	UINT8	aucBuf[MAX_POSS_BUF_SIZE];
	UINT8	*pBuf = NULL;
	UINT32  uiTmp = 0;
	UINT8	statusReg;
	UINT16	i;

	/* confirm that data is available */
	chkCnt = MAX_CHECK_COUNT;
	while( chkCnt-- )
	{
		if( !guwDetectCard )			// for ISR
			return HW_IO_FAIL;

		if( guwIsPowerRestart )		// for power restart
		{
			return HW_IO_FAIL;
		}

		if( CHECK_DA(mId) )
			break;
		
		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_READ_CHECK_DA] );
	}

	if( chkCnt <= 0 )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_Read: IO busy (DA=0)\n");
		return HW_IO_BUSY;
	}


	/* read the size of data */
	size = (UINT16) SIZE_MS_RD(mId);
	size = (size<<8) & 0xFF00;
	size |= (UINT16) SIZE_LS_RD(mId);

	if( size > CiNegoBufSize[mId] )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_Read: data is bigger than buffer (data size=%d)\n", size);
		return HW_IO_FAIL;
	}


	uiTmp = size;
	if( uiTmp > MAX_POSS_BUF_SIZE )
	{
		pBuf = OS_KMalloc( uiTmp );
		if( !pBuf )
		{
			CI_DTV_SOC_Message(CI_ERR,"HW_IO_Read: malloc <<F>>\n");

			return MEM_ALLOC_FAILED;
		}
	}
	else
	{
		pBuf = aucBuf;
	}


	/* read the first byte */
	pBuf[0] = DATA_RD(mId);


 	statusReg = STAT_RD(mId);
	if( (statusReg&CI_DA) || !(statusReg&CI_RE) )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_Read: IO status error (DA=1 or RE=0)\n");
		goto HW_IO_READ_FAIL;
	}


	/* read middle bytes */
	for( i=1; i<(size-1); i++ )
	{
		if( !guwDetectCard )			// for ISR
			goto HW_IO_READ_FAIL;
		
		if( guwIsPowerRestart )		// for power restart
			goto HW_IO_READ_FAIL;


		pBuf[i] = DATA_RD(mId);

		if( !CHECK_RE(mId) )
		{
			CI_DTV_SOC_Message(CI_IO_INFO,"HW_IO_Read: IO status error (RE=0)\n");
			CI_DTV_SOC_Message(CI_IO_INFO,"%d'th byte of %d bytes, status reg=0x%02X\n", i, size, CHECK_RE(mId));
			goto HW_IO_READ_FAIL;
		}
	}

	/* read the last byte */
	pBuf[i] = DATA_RD(mId);

	if( CHECK_RE(mId) )
	{
		CI_DTV_SOC_Message(CI_IO_INFO,"HW_IO_Read: IO status error (RE=1)\n");
		CI_DTV_SOC_Message(CI_IO_INFO,"status reg=0x%02X\n", CHECK_RE(mId));
		goto HW_IO_READ_FAIL;
	}


#ifdef CI_IO_DUMP
	CI_IO_INFO( "Read Data: ");

	for( i=0; i<size; i++ )
	{
		CI_DTV_SOC_Message(CI_IO_INFO,"0x%02x ", pBuf[i]);
	}

	CI_DTV_SOC_Message(CI_IO_INFO,"Read %d bytes IO Data Success ... \n", size);
#endif /* CI_IO_DUMP */

	CI_DTV_SOC_Message(CI_IO_INFO,"Original data size is %d bytes <<S>>\n", size);

	if( *io_pwDataBufSize <= size )
	{
		size = *io_pwDataBufSize;
	}
	else
	{
		*io_pwDataBufSize = size;
	}


	CI_DTV_SOC_Message(CI_IO_INFO," CI-IO> copy_to_user - gonna start\n");
	CI_DTV_SOC_Message(CI_IO_INFO,"BufAddr -0x%x data Len - %d\n",  (UINT32)o_pbyData, size);

	if( copy_to_user( ( void __user * )o_pbyData, pBuf, size ) )
    {
		CI_DTV_SOC_Message(CI_ERR," CI-IO> copy_to_user <<F>>\n");

		goto HW_IO_READ_FAIL;
    }


	CI_DTV_SOC_Message(CI_IO_INFO,"%d bytes of data read <<S>>\n", size);

	if( uiTmp > MAX_POSS_BUF_SIZE )
	{
		OS_Free( pBuf );
	}

	return HW_IO_OK;

HW_IO_READ_FAIL:

	if( uiTmp > MAX_POSS_BUF_SIZE )
	{
		OS_Free( pBuf );
	}

	CI_DTV_SOC_Message(CI_ERR,"\n\nRead IO Data <<F>>\n\n");

	return HW_IO_FAIL;
}



/**
 *	Perform Write to CI Module
 */
int HW_IO_Write( MOD_ID mId ,UINT8 *i_pbyData, UINT32 i_wDataBufSize )
{
	UINT32	chkCnt;
	UINT16	i;

	UINT8  *pBuf = i_pbyData;
	UINT16	size = i_wDataBufSize;

#ifdef CI_IO_DUMP
	CI_DTV_SOC_Message(CI_IO_INFO,"Send Data: ");

	for( i=0; i<size; i++ )
	{
		CI_DTV_SOC_Message(CI_IO_INFO,"0x%02x ", pBuf[i]);
	}

	CI_DTV_SOC_Message(CI_IO_INFO,"\n");
#endif /* CI_IO_DUMP */

	/* confirm that data is not available */
	chkCnt = MAX_CHECK_COUNT;

	while( chkCnt-- )
	{
		if( !guwDetectCard )			// for ISR
			goto HW_IO_WRITE_FAIL;

		if( guwIsPowerRestart )		// for power restart
			goto HW_IO_WRITE_FAIL;


		if( !CHECK_DA(mId) )
			break;
		
		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_WRITE_CHECK_DA] );
	}


	if( chkCnt <= 0 )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_Write: IO busy (DA=1)\n");

		return HW_IO_BUSY;
	}

	/* set HC=1 */
	COMM_WR(mId, CI_HC);

	/* confirm that module is free */
	chkCnt = MAX_CHECK_COUNT;

	while( chkCnt-- )
	{
		if( !guwDetectCard )			// for ISR
			goto HW_IO_WRITE_FAIL;

		if( guwIsPowerRestart )		// for power restart
			goto HW_IO_WRITE_FAIL;

		if( CHECK_FR(mId) )
			break;

		
		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_WRITE_CHECK_FR] );
	}

 
	if( chkCnt <= 0 )
	{
		COMM_WR(mId, 0x00);
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_Write: IO status error (FR=0)\n");

		goto HW_IO_WRITE_FAIL;
	}

	// write the size of data
	SIZE_LS_WR(mId, (UINT8) (size&0x00FF));
	SIZE_MS_WR(mId, (UINT8) ((size>>8)&0x00FF));
	
	// write the first byte 
	DATA_WR(mId, pBuf[0]);

	chkCnt = MAX_CHECK_COUNT;

	while( chkCnt-- )
	{
		if( !guwDetectCard )			// for ISR
			goto HW_IO_WRITE_FAIL;

		if( guwIsPowerRestart )		// for Power reset
			goto HW_IO_WRITE_FAIL;

		if( !(STAT_RD(mId)&CI_FR) && (STAT_RD(mId)&CI_WE) ) break;
		
		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_WRITE_FIRST_BYTE_STAT_RD_FR_WE] );
	}

 
	if( chkCnt <= 0 )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_Write: IO status error (FR=1 or WE=0)\n");
		goto HW_IO_WRITE_FAIL;
	}

	/* write middle bytes */
	for( i=1; i<(size-1); i++ )
	{
		DATA_WR(mId, pBuf[i]);

		chkCnt = MAX_CHECK_COUNT;

		while( chkCnt-- )
		{
			if( !guwDetectCard )			// for ISR
				goto HW_IO_WRITE_FAIL;

			if( guwIsPowerRestart )		// for Power reset
				goto HW_IO_WRITE_FAIL;


			if( CHECK_WE(mId) ) break;
				
			OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_WRITE_MIDDLE_BYTE_CHECK_WE] );
		}


		//if (!alphaCrypt && chkCnt <= 0)
		if( chkCnt <= 0 )
		{
			CI_DTV_SOC_Message(CI_ERR,"HW_IO_Write: IO status error (WE=0)\n");
			goto HW_IO_WRITE_FAIL;
		}
	}

	/* write the last byte */
	DATA_WR(mId, pBuf[i]);

	chkCnt = MAX_CHECK_COUNT;

	while( chkCnt-- )
	{
		if( !guwDetectCard )			// for ISR
			goto HW_IO_WRITE_FAIL;

		if( guwIsPowerRestart )		//for Power reset
			goto HW_IO_WRITE_FAIL;


		if( !CHECK_WE(mId) )
			break;

		OS_MsecSleep( gCI_KDRV_Delay[CI_D_IO_WRITE_LAST_BYTE_CHECK_WE] ); 
	}

	if( chkCnt <= 0 )
	{
		CI_DTV_SOC_Message(CI_ERR,"HW_IO_Write: IO status error (WE=1)\n");
		goto HW_IO_WRITE_FAIL;
	}

	COMM_WR(mId, 0x00);

	CI_DTV_SOC_Message(CI_IO_INFO,"Write IO Data Success ... \n ");

	return HW_IO_OK;

	
HW_IO_WRITE_FAIL:

	COMM_WR(mId, 0x00);

	CI_DTV_SOC_Message(CI_ERR,"\n HW_IO_Write <<F>>\n\n");

	return HW_IO_FAIL;
}

int CI_IO_EnableLog( UINT32 ulArg)
{
	int eRet = NOT_OK;
	int idx;

	CI_DTV_SOC_Message(CI_DBG_INFO, "<--CI_IO_EnableLog");

	for ( idx = 0; idx < LX_MAX_MODULE_DEBUG_NUM; idx++)
	{
		if ( ulArg & (1<<idx) ) OS_DEBUG_EnableModuleByIndex ( g_ci_debug_fd, idx, DBG_COLOR_NONE );
		else					OS_DEBUG_DisableModuleByIndex( g_ci_debug_fd, idx);
	}
		
	CI_DTV_SOC_Message(CI_DBG_INFO, "-->CI_IO_EnableLog");

	eRet = OK;

	return (eRet);
}


/*----------------------------------------------------------------------------*/

