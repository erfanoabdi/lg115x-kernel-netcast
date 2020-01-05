

#ifndef DEMOD_MODULE_H
#define DEMOD_MODULE_H


#include "demod_kapi.h"
#include "i2c_core.h"


 /*
 	define
 */
//#define FPGA_DEMOD_TEST


/*
	Device inform
*/

/**
 * I2C .
 */


typedef struct
{
	LX_I2C_DEV_HANDLE	handle;
	UINT32				slvAddr;
	UINT8				portI2C;
} LX_DEMOD_I2C_DESCRIPT_T;


typedef struct
{
	UINT8  						id; //device minor number
	LX_DEMOD_I2C_DESCRIPT_T		handle;
	BOOLEAN						bInit;
	UINT32						IFFrq;

	LX_DEMOD_OPER_MODE_T 		operMode;
	LX_DEMOD_RF_MODE_T			systemMode;
	LX_DEMOD_SYMRDET_MODE_T 	symbr;
	BOOLEAN 					bIsSerial;

	LX_DEMOD_CONTROL_STATE_T	controlState;
	LX_DEMOD_ACQUIRE_PROCESS_T	acqState;
	LX_DEMOD_FLAG_T				scanJobFlag;

	BOOLEAN 					bSetParams;
	LX_DEMOD_CONFIG_T			setCfgParam;
	LX_DEMOD_CONFIG_T			getCfgParam;
	LX_DEMOD_LOCK_STATE_T		lockStatus;

	LX_DEMOD_SIGNAL_CTX_T		signalStatus;
	SINT32 						freqOffset;

	BOOLEAN						bMonitorEnable;
	BOOLEAN 					bNotifiedLock;
	BOOLEAN 					bNotifiedUnlock;

	UINT8 						unLockLongCount;
	UINT8 						unLockCount;
	UINT8						lockCount;



} DEMOD_CTX_T;


/*
	Enum define
*/


/*
	global variable
*/


/*
	function prototype
*/

extern int DEMOD_I2C_open(UINT8 portI2C, UINT16 deviceID);
extern int DEMOD_I2C_Close(void);
extern int DEMOD_I2C_Read( UINT16 address, UINT16 nBytes, UINT8 *pData);
extern int DEMOD_I2C_Write( UINT16 address, UINT16 nBytes, UINT8 *pData);

extern int ADC_Test_I2C_Read( UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData);
extern int ADC_Test_I2C_Write( UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData);
extern int DEMOD_ADC_Control( LX_DEMOD_ADC_VOLTAGE_SEL_T votageSel);

/* HW function */
extern int DEMOD_ResetHW(void);
extern int DEMOD_SetInclk(LX_DEMOD_INCLK_SEL_T *inclk);
extern int DEMOD_Initialize(void);

#ifdef KDRV_CONFIG_PM
int DEMOD_HW_suspend(void);
int DEMOD_HW_resume(void);
#endif

#endif
