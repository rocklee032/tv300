/********************************************************************************************************
File:ATBM2040Porting.c
Description:
    ATBM2040 Tuner porting APIs which need to be implemented by user.

*********************************************************************************************************/
#include "ATBM2040Porting.h"    
#include "drvIIC.h"
#include "msAPI_Timer.h"

//#define MxL_I2CBUS_ADDR 0x0200
#define ATBM_I2CBUS_ADDR			((TUNER_IIC_BUS << 8) | 0xC0)

#if (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_USER_SPACE)
#include <pthread.h>
static pthread_mutex_t ATBM2040Mutex = PTHREAD_MUTEX_INITIALIZER;
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_KERNEL_SPACE)
#include <linux/mutex.h>
static struct mutex ATBM2040Mutex;
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_WINDOWS)
static HANDLE ATBM2040Mutex;
#else
/*To realize mutex addcording to system platform.*/
#endif

/********************************************************************
* Function: ATBM2040I2CRead
* Description: Read I2C data. User need to implement this function addcording to system platform.
*            Detail of ATBM2040 I2C format is described in software guide document.
* Input:     pI2CAddr -- I2C slave address and user param
*        BaseReg -- Base register address
*        OffReg -- Offset register address
*        pData -- Pointer to register value
*        Length - Buffer length of 'pData' in byte
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040I2CRead(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 *pData, UINT32 Length)
{
    (void)pI2CAddr;
    (void)BaseReg;
    (void)OffReg;
    (void)pData;
    (void)Length;
#if 1 
    UINT8 ui8AddrData[2];
    
    //pI2CAddr->I2CSlaveAddr=(U8)ATBM_I2CBUS_ADDR;
	ui8AddrData[0] = BaseReg;
	ui8AddrData[1] = OffReg;



	if(MDrv_IIC_ReadBytes(ATBM_I2CBUS_ADDR,2,ui8AddrData,(U16)Length, pData) == FALSE)
    {
        printf("\n read ATBM Fail ");
        return ATBM2040_ERROR_I2C_FAILED;
    }
#endif
    return ATBM2040_NO_ERROR;
}

/********************************************************************
* Function: ATBM2040I2CWrite
* Description: Write I2C data. User need to implement this function addcording to system platform.
*            Detail of ATBM2040 I2C format is described in software guide document.
* Input:     pI2CAddr -- I2C slave address and user param
*        BaseReg -- Base register address
*        OffReg -- Offset register address
*        pData -- Register value
*        Length - Buffer length of 'pData' in byte
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040I2CWrite(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 *pData, UINT32 Length)
{

    (void)pI2CAddr;
    (void)BaseReg;
    (void)OffReg;
    (void)pData;    
    (void)Length;
    //pI2CAddr->I2CSlaveAddr = (U8)ATBM_I2CBUS_ADDR;
	UINT8 i2c_data[2];
    //uint8 reg_data[1];	

	i2c_data[0] = BaseReg;
	i2c_data[1] = OffReg;
	//i2c_data[2] = ui8Data;
		
	//ATBMMutexLock();

    
    if (MDrv_IIC_WriteBytes(ATBM_I2CBUS_ADDR,2, i2c_data, (U16)Length, pData)==FALSE)
    {
        printf("\n write ATBM fail ");
        return ATBM2040_ERROR_I2C_FAILED;
    }

	return ATBM2040_NO_ERROR;
}

/********************************************************************
* Function: ATBM2040Delay
* Description: Delay. User need to implement this function addcording to system platform.
*
* Input:     TimeoutUs -- timeout in us to delay 
*
* Output: N/A
* Retrun: N/A
********************************************************************/
void ATBM2040Delay(UINT32 TimeoutUs)
{
    msAPI_Timer_Delayms(TimeoutUs/1000);
    
}

/********************************************************************
* Function: ATBM2040MutexInit
* Description: Initialize one mutex for SDK. 
* User need to implement this function addcording to system platform.
*
* Input:     N/A
*
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040MutexInit(void)
{
#if (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_USER_SPACE)
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_KERNEL_SPACE)
    mutex_init(&ATBM2040Mutex);
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_WINDOWS)
    ATBM2040Mutex  = CreateSemaphore(NULL,1,1,NULL);
#else
/*To realize mutex addcording to system platform.*/

#endif
    return ATBM2040_NO_ERROR;
}
/********************************************************************
* Function: ATBM2040MutexLock
* Description: Lock the mutex of SDK. 
* User need to implement this function addcording to system platform.
*
* Input:    N/A
*
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040MutexLock(void)
{
#if (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_USER_SPACE)
    int ret = 0;
    ret = pthread_mutex_lock(&ATBM2040Mutex);
    if(0 != ret)
    {
        return ATBM2040_ERROR_UNKNOWN;
    }
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_KERNEL_SPACE)
    mutex_lock(&ATBM2040Mutex);
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_WINDOWS)
    WaitForSingleObject(ATBM2040Mutex,INFINITE);
#else
/*To realize mutex addcording to system platform.*/

#endif
    return ATBM2040_NO_ERROR;
}

/********************************************************************
* Function: ATBM2040MutexUnLock
* Description: Unlock the mutex of SDK. 
* User need to implement this function addcording to system platform.
*
* Input:    N/A
*
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040MutexUnLock(void)
{
#if (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_USER_SPACE)
    int ret = 0;
    ret = pthread_mutex_unlock(&ATBM2040Mutex);
    if(0 != ret)
    {
        return ATBM2040_ERROR_UNKNOWN;
    }
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_KERNEL_SPACE)
    mutex_unlock(&ATBM2040Mutex);
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_WINDOWS)
    ReleaseSemaphore(ATBM2040Mutex,1,NULL);
#else
/*To realize mutex addcording to system platform.*/

#endif
    return ATBM2040_NO_ERROR;
}


