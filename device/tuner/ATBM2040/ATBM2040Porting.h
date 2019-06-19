/********************************************************************************************************
*File name: ATBM2040Porting.h
*Description: Headerfile of ATBM2040Porting.c. The functions in this file are called by ATBM2040 SDK, and they should be implemented
*            according to specific system platform.
*
*********************************************************************************************************/

#ifndef __ATBM2040PORTING_H__    
#define __ATBM2040PORTING_H__
#include "ATBM2040Api.h" 

#ifdef __cplusplus
extern "C"
{
#endif

/*The count of ATBM2040 tuner in the system.*/
#define ATBM2040_TUNER_COUNT (1)

/*System OS type.*/
#define ATBM2040_OS_TYPE_LINUX_USER_SPACE (0) /* ATBM2040 working in Linux user space. */
#define ATBM2040_OS_TYPE_LINUX_KERNEL_SPACE (1) /* ATBM2040 working in Linux kernel space. */
#define ATBM2040_OS_TYPE_WINDOWS (2) /* ATBM2040 working in Windows. */
#define ATBM2040_OS_TYPE_CUSTOM (3) /* ATBM2040 working in customer OS type. */

/* Select OS type addcording to system platform. */
#define ATBM2040_OS_TYPE_SEL (ATBM2040_OS_TYPE_CUSTOM)


#ifdef ATBM2040_CHIP_DEBUG_OPEN
#undef ATBM2040_OS_TYPE_SEL
#define ATBM2040_OS_TYPE_SEL (ATBM2040_OS_TYPE_WINDOWS)
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
ATBM2040_ERROR_e ATBM2040I2CRead(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 *pData, UINT32 Length);

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
ATBM2040_ERROR_e ATBM2040I2CWrite(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 *pData, UINT32 Length);

/********************************************************************
* Function: ATBM2040Delay
* Description: Delay. User need to implement this function addcording to system platform.
*
* Input:     TimeoutUs -- timeout in us to delay 
*
* Output: N/A
* Retrun: N/A
********************************************************************/
void ATBM2040Delay(UINT32 TimeoutUs);

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
ATBM2040_ERROR_e ATBM2040MutexInit(void);

/********************************************************************
* Function: ATBM2040MutexLock
* Description: Lock the mutex of SDK. 
* User need to implement this function addcording to system platform.
*
* Input:     N/A
*
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040MutexLock(void);

/********************************************************************
* Function: ATBM2040MutexUnLock
* Description: Unlock the mutex of SDK. 
* User need to implement this function addcording to system platform.
*
* Input:     N/A
*
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040MutexUnLock(void);


/********************************************************************
* 
* Customer configuration macro definations
*
********************************************************************/
/*ATBM2040_CUSTOMER1_CONFIG is used for some customer platform 
*which need IF peek specially in ATV mode. */
#define ATBM2040_CUSTOMER1_CONFIG (0)



/********************************************************************
* ATBM2040 debug output control.
* If define 'ATBM2040_DEBUG_PRINT' to '0', debug output will be closed;
*   otherwise,debug output will be opened. 
* The default implement of 'ATBM2040Print' is 'printf', and it can be changed according to 
*   system platform. 
********************************************************************/
#define ATBM2040_DEBUG_PRINT (1)

#if ATBM2040_DEBUG_PRINT
#if((ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_USER_SPACE)||(ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_WINDOWS))
#include <stdio.h>
#define ATBM2040Print(x) printf x
#elif (ATBM2040_OS_TYPE_SEL == ATBM2040_OS_TYPE_LINUX_KERNEL_SPACE)
#include <linux/kernel.h>
#define ATBM2040Print(x) printk x
#else
#define ATBM2040Print(x) printf x
#endif

#else
#define ATBM2040Print(...)  /* empty */
#endif


#ifdef __cplusplus
}
#endif

#endif /*__ATBM2040PORTING_H__*/
                                                                         
