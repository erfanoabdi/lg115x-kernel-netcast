/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2010 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 

/*! \file DEMOD_module.c
 * \brief DEMOD module control Drivers linux module
 */


/**
 *	Necessary includes for device drivers
 */
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
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>


#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include "os_util.h"
//#include "base_dev_cfg.h"
#include "base_device.h"
#include "ctop_regs.h"


#include "demod_drv.h"
#include "demod_module.h"
#include "demod_impl.h"

#include "sys_regs.h"

#include "i2c_core.h"


/******************************************************************************
 *				DEFINES
 *****************************************************************************/

/**
 *	Global variables of the driver
 */


LX_DEMOD_I2C_DESCRIPT_T	gGBBI2cDev; //jeongpil.yun


extern DEMOD_HAL_T		g_demod_hal;

//extern	void	DEMOD_L9_InitHAL( DEMOD_HAL_T*	hal );
extern 	void	DEMOD_H13_InitHAL( DEMOD_HAL_T* hal );


/******************************************************************************
 *				DATA STRUCTURES
 *****************************************************************************/
/**
 *	Structure that declares the usual file
 *	access functions
 */


/******************************************************************************
 *				Local function
 *****************************************************************************/
/**
 *	Structure that declares the usual file
 *	access functions
 */



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_open.
 * Open I2C device
 *
 * @param portI2C [IN] I2C channel index
 * @param deviceID [IN] GBB chip address
 * @param *pHandle [OUT] handle
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_I2C_open(UINT8 portI2C, UINT16 deviceID)
{

		gGBBI2cDev.portI2C = portI2C;
		gGBBI2cDev.slvAddr	  = deviceID;

		gGBBI2cDev.handle =  I2C_DevOpen( portI2C-1);


		I2C_DevSetClock(gGBBI2cDev.handle, I2C_CLOCK_400KHZ);
		DEMOD_PRINT(" portI2C num = %d, slave addr = %d   \n",gGBBI2cDev.portI2C,gGBBI2cDev.slvAddr );


	return RET_OK;


}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Close.
 * Close I2C device
 *
 * @param none [IN] void
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_I2C_Close(void)
{


	gGBBI2cDev.slvAddr	  = 0;


	I2C_DevClose(gGBBI2cDev.handle);

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Read.
 * Read the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_I2C_Read( UINT16 address, UINT16 nBytes, UINT8 *pData)
{

	LX_I2C_RW_DATA_T data;

#ifdef FPGA_DEMOD_TEST

	UINT8	addr[2];
	UINT8 tempData;
	UINT8 tempAddr[2];

	addr[0] = (UINT8)((address >> 8) & 0xFF);
	addr[1] = (UINT8)(address & 0xFF);


	if(address <= 0xff)
	{
	  if(address <= 0x4f)
	  	{
		  gGBBI2cDev.slvAddr = 0xe2;

	  	}
	  else if(address <= 0x6f)
	  	{
		  gGBBI2cDev.slvAddr = 0xe8;

	  	}
	  else if(address <= 0x7f)
	  	{
		  gGBBI2cDev.slvAddr = 0xe4;

	  	}
	  else if(address <= 0xa5)
	  	{
		  gGBBI2cDev.slvAddr = 0xe2;

	  	}
	  else if(address <= 0xef)
	  	{
	  		gGBBI2cDev.slvAddr = 0xe2;
			tempAddr[0] = 0x00;
			tempAddr[1] = 0x8;

			data.slaveAddr = gGBBI2cDev.slvAddr;
			data.subAddrSize = 2;
			data.subAddr[0] = 0x00;
			data.subAddr[1] = 0x8;
			data.buf = &tempData;
			data.bufSize = nBytes;
			data.clock = I2C_CLOCK_100KHZ;
			data.flag = 0;


			if (nBytes != I2C_DevTransfer(gGBBI2cDev.handle, &data, I2C_READ_MODE))
			{
					DEMOD_PRINT("^r^[KDRV_DEMOD DTV] FAIL (%s:%d) I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x8] D[0x%0x])  !!!\n",
					__F__, __L__, gGBBI2cDev.portI2C,gGBBI2cDev.slvAddr, *pData);

					return RET_ERROR;

			}

			if((tempData == 0x40)|| (tempData == 0x20))
			{
				gGBBI2cDev.slvAddr = 0xe8;

			}
			else if(tempData == 0x80)
			{
				gGBBI2cDev.slvAddr = 0xe6;

			}
			else
			{
				gGBBI2cDev.slvAddr = 0xea;

			}

	  	}
	  else
	  	{
		  gGBBI2cDev.slvAddr = 0xe4;

	  	}

	}
	else if(address <= 0x10ff )
	{
		gGBBI2cDev.slvAddr = 0xe2;

	}
	else if(address <= 0x21ff)
	{
		gGBBI2cDev.slvAddr = 0xe6;

	}
	else if(address <= 0x22ff)
	{
		gGBBI2cDev.slvAddr = 0xe8;

	}
	else if(address <= 0x28ff)
	{
		gGBBI2cDev.slvAddr = 0xea;

	}
	else if(address <= 0x30ff)
	{
		gGBBI2cDev.slvAddr = 0xe4;

	}
	else
	{
		gGBBI2cDev.slvAddr = 0xe2;

	}

	data.slaveAddr = gGBBI2cDev.slvAddr;
	data.subAddrSize = 2;
	data.subAddr[0] = (UINT8)((address >> 8) & 0xFF);
	data.subAddr[1] = (UINT8)(address & 0xFF);
	data.buf = pData;
	data.bufSize = nBytes;
	data.clock = I2C_CLOCK_100KHZ;
	data.flag = 0;


	if (nBytes != I2C_DevTransfer(gGBBI2cDev.handle, &data, I2C_READ_MODE))
	{
		DEMOD_PRINT("^r^[KDRV_DEMOD DTV] FAIL (%s:%d) I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
					__F__, __L__, gGBBI2cDev.portI2C,gGBBI2cDev.slvAddr, address, *pData);


		return RET_ERROR;

	}

#else

#if 0
		typedef struct LX_I2C_RW_DATA
		{
			UINT8	slaveAddr;		// Device slave ID
			UINT8	subAddrSize;	// Address length in bytes
			UINT8	subAddr[4]; 	// Starting address inside the device
			UINT8	*buf;			// buffer
			UINT32	bufSize;		// size of buffer
			UINT32	clock;			// Clock
			UINT32	flag;
		} LX_I2C_RW_DATA_T;
#endif

		data.slaveAddr = gGBBI2cDev.slvAddr;
		data.subAddrSize = 2;
		data.subAddr[0] = (UINT8)((address >> 8) & 0xFF);
		data.subAddr[1] = (UINT8)(address & 0xFF);
		data.buf = pData;
		data.bufSize = nBytes;
		data.clock = I2C_CLOCK_400KHZ;
		data.flag = 0;


		if (nBytes != I2C_DevTransfer(gGBBI2cDev.handle, &data, I2C_READ_MODE))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD DTV] FAIL (%s:%d) I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C,gGBBI2cDev.slvAddr, address, *pData);


			return RET_ERROR;

		}
	//		DEMOD_PRINT("[TU_ DTV] SUCCESS (%s:%d) I2C_DevTransfer(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
	//					__F__, __L__, gGBBI2cDev.portI2C /*gGBBI2cDev.handle->ch*/,gGBBI2cDev.slvAddr, address, *pData);

#endif
	return RET_OK;


}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Write.
 * Write the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - register data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_I2C_Write( UINT16 address, UINT16 nBytes, UINT8 *pData)
{
	LX_I2C_RW_DATA_T data;

#ifdef FPGA_DEMOD_TEST

	UINT8	addr[2];
	UINT16  chipaddress[5] = {0xe2, 0xe4, 0xe6, 0xe8, 0xea} ;
	UINT8 	count;

	addr[0] = (UINT8)((address >> 8) & 0xFF);
	addr[1] = (UINT8)(address & 0xFF);

 	for(count=0;count < 5; count++)
 	{
 		if((address == 0x0) && ((*pData >> 7) == 0))
 		{
			gGBBI2cDev.slvAddr = chipaddress[4-count];

 		}
		else
		{
			gGBBI2cDev.slvAddr = chipaddress[count];
		}

		data.slaveAddr = gGBBI2cDev.slvAddr;
		data.subAddrSize = 2;
		data.subAddr[0] = (UINT8)((address >> 8) & 0xFF);
		data.subAddr[1] = (UINT8)(address & 0xFF);
		data.buf = pData;
		data.bufSize = nBytes;
		data.clock = I2C_CLOCK_100KHZ;
		data.flag = 0;


		if (nBytes != I2C_DevTransfer(gGBBI2cDev.handle, &data, I2C_WRITE_MODE))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD DTV] FAIL (%s:%d) I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C,gGBBI2cDev.slvAddr, address, *pData);


			return RET_ERROR;

		}
 	}
//	DEMOD_PRINT("[KDRV_DEMOD] SUCCESS (%s:%d) I2C_DevTransfer(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x])	!!!\n",
//				__F__, __L__, gGBBI2cDev.portI2C, gGBBI2cDev.slvAddr, address, data);

	return RET_OK;
#endif

#if 0
		typedef struct LX_I2C_RW_DATA
		{
			UINT8	slaveAddr;		// Device slave ID
			UINT8	subAddrSize;	// Address length in bytes
			UINT8	subAddr[4]; 	// Starting address inside the device
			UINT8	*buf;			// buffer
			UINT32	bufSize;		// size of buffer
			UINT32	clock;			// Clock
			UINT32	flag;
		} LX_I2C_RW_DATA_T;
#endif
	/*
		int KADP_I2C_Read(LX_I2C_HANDLE_T handle,
						UINT8 slaveAddr,
						UINT8 *subAddr,
						UINT8 subAddrSize,
						UINT8 *buf,
						UINT32 bufSize)
	*/

		data.slaveAddr = gGBBI2cDev.slvAddr;
		data.subAddrSize = 2;
		data.subAddr[0] = (UINT8)((address >> 8) & 0xFF);
		data.subAddr[1] = (UINT8)(address & 0xFF);
		data.buf = pData;
		data.bufSize = nBytes;
		data.clock = I2C_CLOCK_400KHZ;
		data.flag = 0;


		if (nBytes != I2C_DevTransfer(gGBBI2cDev.handle, &data, I2C_WRITE_MODE))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD DTV] FAIL (%s:%d) I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C,gGBBI2cDev.slvAddr, address, *pData);


			return RET_ERROR;

		}
	//		DEMOD_PRINT("[TU_ DTV] SUCCESS (%s:%d) I2C_DevTransfer(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
	//					__F__, __L__, gGBBI2cDev.portI2C /*gGBBI2cDev.handle->ch*/,gGBBI2cDev.slvAddr, address, *pData);


	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Test_I2C_Read.
 * Read the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int ADC_Test_I2C_Read( UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData)
{

		LX_I2C_RW_DATA_T data;

#if 0
			typedef struct LX_I2C_RW_DATA
			{
				UINT8	slaveAddr;		// Device slave ID
				UINT8	subAddrSize;	// Address length in bytes
				UINT8	subAddr[4]; 	// Starting address inside the device
				UINT8	*buf;			// buffer
				UINT32	bufSize;		// size of buffer
				UINT32	clock;			// Clock
				UINT32	flag;
			} LX_I2C_RW_DATA_T;
#endif


		data.slaveAddr = slvAddr;
		data.subAddrSize = 1;
		data.subAddr[0] = address;
		data.buf = pData;
		data.bufSize = nBytes;
		data.clock = I2C_CLOCK_100KHZ;
		data.flag = 0;


		if (nBytes != I2C_DevTransfer(gGBBI2cDev.handle, &data, I2C_READ_MODE))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD DTV] FAIL (%s:%d) I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C,slvAddr, address, *pData);


			return RET_ERROR;

		}


	return RET_OK;


}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Test_I2C_Write.
 * Write the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - register data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int ADC_Test_I2C_Write( UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData)
{
		LX_I2C_RW_DATA_T data;

#if 0
		typedef struct LX_I2C_RW_DATA
		{
			UINT8	slaveAddr;		// Device slave ID
			UINT8	subAddrSize;	// Address length in bytes
			UINT8	subAddr[4]; 	// Starting address inside the device
			UINT8	*buf;			// buffer
			UINT32	bufSize;		// size of buffer
			UINT32	clock;			// Clock
			UINT32	flag;
		} LX_I2C_RW_DATA_T;
#endif

		data.slaveAddr = slvAddr;
		data.subAddrSize = 1;
		data.subAddr[0] = address;
//		data.subAddr[1] = (UINT8)(address & 0xFF);
		data.buf = pData;
		data.bufSize = nBytes;
		data.clock = I2C_CLOCK_100KHZ;
		data.flag = 0;


		if (nBytes != I2C_DevTransfer(gGBBI2cDev.handle, &data, I2C_WRITE_MODE))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD DTV] FAIL (%s:%d) I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C,slvAddr, address, *pData);


			return RET_ERROR;

		}


	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ADC_Control.
 * Select the adc voltage range.
 *
 * @param address [IN] 	votageSel - LX_DEMOD_ADC_VOLTAGE_SEL_T (1V or 2V)
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_ADC_Control( LX_DEMOD_ADC_VOLTAGE_SEL_T votageSel)
{

#if 1
	UINT8 subaddress;
	UINT8 wrdata;
	UINT8 slaveAddr;
	UINT16 nbyte;

	if( LX_DEMOD_ADC_SEL_1V == votageSel)
	{
		subaddress = 0x1b;
		wrdata = 0x9;
		slaveAddr = 0x80;
		nbyte = 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD] FAIL (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
		DEMOD_PRINT("^Y^[KDRV_DEMOD] success (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
					__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);


		subaddress = 0x1c;
		wrdata = 0xa9;
		slaveAddr = 0x80;
		nbyte = 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD] FAIL (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
		DEMOD_PRINT("^Y^[KDRV_DEMOD] success (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
					__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);


		subaddress = 0x1d;
		wrdata = 0x3;
		slaveAddr = 0x80;
		nbyte = 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD] FAIL (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
		DEMOD_PRINT("^Y^[KDRV_DEMOD] success (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
					__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);


		subaddress = 0x1e;
		wrdata = 0x19;
		slaveAddr = 0x80;
		nbyte = 1;
		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD] FAIL (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
		DEMOD_PRINT("^Y^[KDRV_DEMOD] success (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
					__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);


		subaddress = 0x1f;
		wrdata = 0x00;
		slaveAddr = 0x80;
		nbyte = 1;
		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("^r^[KDRV_DEMOD] FAIL (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
						__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
		DEMOD_PRINT("^Y^[KDRV_DEMOD] success (%s:%d) ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) !!!\n",
					__F__, __L__, gGBBI2cDev.portI2C, slaveAddr, subaddress, wrdata);
	}
	else
	{

	}
#endif
	return RET_OK;

}

#if 0
#endif



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/


int DEMOD_ResetHW(void)
{

	DEMOD_PRINT("[DEMOD] DEMOD_ResetHW start !! \n");

	if(NULL == g_demod_hal.ResetHW)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.ResetHW())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_SetI2C.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_SetI2C(void)
{
	if(NULL == g_demod_hal.SetI2C)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SetI2C())
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("[DEMOD] DEMOD_SetI2C end !! \n");
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_SetInclk.
 * select inclk mode
 *
 * @param inclk  [IN] LX_DEMOD_INCLK_SEL_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_SetInclk(LX_DEMOD_INCLK_SEL_T *inclk)
{

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetInclk Start !! \n");

	if(NULL == g_demod_hal.SetInclk)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SetInclk(inclk))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetInclk End !! \n");

	return RET_OK;
}




/** initialize HAL function list
 *
 */
static void    DEMOD_InitHAL ( void )
{
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_InitHAL Start !! \n");

    memset( &g_demod_hal, 0x0, sizeof(DEMOD_HAL_T));

    /* initialize HAL (Hardware Abstraction Layer) */
#if 0
	if(lx_chip_rev() <= LX_CHIP_REV(L9, B1))
	{
        DEMOD_L9_InitHAL( &g_demod_hal );

	}
	else if(lx_chip_rev() <= LX_CHIP_REV(H13, B0))
#else
	if(lx_chip_rev() <= LX_CHIP_REV(H13, B0))
#endif
    {
        DEMOD_H13_InitHAL( &g_demod_hal );
    }
    else
    {
        DEMOD_H13_InitHAL( &g_demod_hal );
		DEMOD_PRINT("[KDRV_DEMOD] Fail, UNKOWN chip version  !! \n");
    }
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_InitHAL End !! \n");

}


#ifdef KDRV_CONFIG_PM

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_HW_suspend.
 * HW suspend
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_HW_suspend(void)
{

	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		ACE_REG_H13A0_RdFL(gbb_afe_0);
		ACE_REG_H13A0_RdFL(gbb_0);

		ACTRL_Rd01(gbb_afe_0, inck_sel, guiPmClk);
		ACTRL_Rd01(gbb_0, i2csel, guiPmI2C);

	}
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_HW_resume.
 * HW resume
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/


int DEMOD_HW_resume(void)
{

	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		ACE_REG_H13A0_RdFL(gbb_afe_0);
		ACE_REG_H13A0_RdFL(gbb_0);


		ACE_REG_H13A0_Wr01(gbb_afe_0, inck_sel, guiPmClk);
		ACE_REG_H13A0_Wr01(gbb_0, i2csel, guiPmI2C);

		ACE_REG_H13A0_WrFL(gbb_afe_0);
		ACE_REG_H13A0_WrFL(gbb_0);

	}
	return RET_OK;
}
#endif




#if 0
#endif

/**
* ADC Module exit
*
* @parm void
* @return int
*/
int DEMOD_exit(void)
{
	int ret = RET_OK;


	return ret;
}


/**
* ADC Module initialize
*
* @parm void
* @return int
*/
int DEMOD_Initialize(void)
{

	int ret = RET_OK;
	LX_DEMOD_INCLK_SEL_T inclk = LX_DEMOD_ARM_SETTING;

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_Initialize Start !! \n");

	DEMOD_InitHAL();

	if( RET_OK != DEMOD_SetI2C())
	{
		ret = RET_ERROR;
	}

	if( RET_OK != DEMOD_SetInclk(&inclk))
	{
		ret = RET_ERROR;
	}


	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_Initialize End !! \n");


	return ret;
}

