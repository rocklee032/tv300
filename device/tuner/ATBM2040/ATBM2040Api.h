/********************************************************************************************************
*Copyright (C) 2016-2030, Altobeam
*File name: ATBM2040Api.h
*Author: duanqiang
*Version: 1.0.7
*Date: 2017-08-25
*Description: Headerfile of ATBM2040Api.c,APIs of ATBM2040 SDK .
*
*********************************************************************************************************/

#ifndef __ATBM2040API_H__    
#define __ATBM2040API_H__

#include "ATBM2040Definition.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*ATBM2040 error code */
#define ATBM2040_NO_ERROR                 (0x00) /*no error*/
#define ATBM2040_ERROR_BAD_PARAM         (0x01) /*invalid parameter*/
#define ATBM2040_ERROR_NOT_INIT         (0x02) /*SDK is not initialized*/
#define ATBM2040_ERROR_I2C_FAILED         (0x04) /*I2C R/W failed*/
#define ATBM2040_ERROR_CFO_NOT_READY     (0x08) /*CFO Evaluation not ready*/
#define ATBM2040_ERROR_NO_DEVICE         (0x10) /*Chip not exist*/
#define ATBM2040_ERROR_UNKNOWN          (0x80000000)    /*other error*/
typedef UINT32 ATBM2040_ERROR_e; /*Error type*/

/*RF Signal mode*/
typedef enum
{
    ATBM2040_SIGNAL_MODE_DTMB = 0, /* DTMB */
    ATBM2040_SIGNAL_MODE_DVBT, /*DVB-T/DVB-T2*/
    ATBM2040_SIGNAL_MODE_DVBC, /*DVB-C/DVB-C2*/
    ATBM2040_SIGNAL_MODE_ISDBT, /* ISDBT */
    ATBM2040_SIGNAL_MODE_ATSC, /* ATSC */
    ATBM2040_SIGNAL_MODE_ATV, /*Analog TV*/
    
    ATBM2040_SIGNAL_MODE_MAX
}ATBM2040_SIGNAL_MODE_e;

/*IF output voltage level*/
typedef enum
{
    ATBM2040_IF_OUT_LEVEL1 = 0, /* 850 mV */    
    ATBM2040_IF_OUT_LEVEL2,     /* 1150 mV */
    ATBM2040_IF_OUT_LEVEL3,     /* 1650 mV */
    ATBM2040_IF_OUT_LEVEL4,     /* 2150 mV */

    ATBM2040_IF_OUT_LEVEL_MAX
}ATBM2040_IF_OUT_LEVEL_e;

/*IF Out Setting */
typedef struct
{
    UINT32 IFOutFreqHz; /*IF out frequency in Hz*/
    ATBM2040_IF_OUT_LEVEL_e IFOutLevel; /*IF out level*/
    UINT32 LevelSpinner; /*Spinner of IF out level*/
}ATBM2040IFOut_t;

/*IF spectrum*/
typedef enum
{
    ATBM2040_SPECTRUM_NORMAL = 0, /*normal spectrum output */    
    ATBM2040_SPECTRUM_INVERT,     /*inverted spectrum output */
    
    ATBM2040_SPECTRUM_MODE_MAX
}ATBM2040_SPECTRUM_MODE_e;

/*Clock out control*/
typedef enum
{
    ATBM2040_CLK_OUT_DISABLE = 0, /*Clock out disable*/
    ATBM2040_CLK_OUT_ENABLE, /*Clock out enable*/
    
    ATBM2040_CLK_OUT_MAX
}ATBM2040_CLK_OUT_e;
typedef enum
{
    ATBM2040_CLK_OUT_AMP_L1 = 0, /*0.83Vp-p*/
    ATBM2040_CLK_OUT_AMP_L2, /*0.9Vp-p*/
    ATBM2040_CLK_OUT_AMP_L3, /*1.0Vp-p*/
    ATBM2040_CLK_OUT_AMP_L4, /*1.15Vp-p*/
    ATBM2040_CLK_OUT_AMP_L5, /*1.3Vp-p*/
    
    ATBM2040_CLK_OUT_AMP_MAX    
}ATBM2040_CLK_OUT_AMP_e;
typedef struct
{
    ATBM2040_CLK_OUT_e ClkOutEnable; /*clock out enable control*/
    ATBM2040_CLK_OUT_AMP_e ClkOutAmp; /*clock out amplitude, valid only if ClkOutEnable is ATBM2040_CLK_OUT_ENABLE*/
}ATBM2040ClkOutCfg_t;

#if 0
/*ATV CFO Evaluate  state control*/
typedef enum
{
    ATBM2040_ATV_CFO_EVAL_DISABLE = 0, /*ATV CFO Evaluate disable*/
    ATBM2040_ATV_CFO_EVAL_ENABLE, /*ATV CFO Evaluate enable*/
}ATBM2040_ATV_CFO_EVAL_e;
#endif

typedef enum
{/*Name of PIN*/
    ATBM2040_PIN_NAME_GPO1 = 0, /*AGC1/GPO1*/
    ATBM2040_PIN_NAME_GPO2, /*AGC2/GPO2*/
    
    ATBM2040_PIN_MAX
}ATBM2040_PIN_NAME_e;

typedef enum
{/*State of GPO*/
    ATBM2040_GPO_STATE_LOW = 0,
    ATBM2040_GPO_STATE_HIGH,

    ATBM2040_GPO_STATE_MAX
}ATBM2040_GPO_STATE_e;

/*Pin config parameter*/
typedef struct
{
    ATBM2040_PIN_NAME_e PinName; /*Pin name*/
    ATBM2040_GPO_STATE_e PinState; /*GPO State, Low/High*/
}ATBM2040PinCfg_t;

/*OSC calibration*/
typedef struct
{
    UINT8 CalibValue; /*OSC PPM calibration, from 0x00 to 0x1F. */
}ATBM2040OSCCalib_t;

/*RF Loopthrough output*/
typedef enum
{
    ATBM2040_RF_LTA_OUT_DISABLE = 0, /*Close RF loopthrough output*/
    ATBM2040_RF_LTA_OUT_ENABLE, /*Open RF loopthrough output*/

    ATBM2040_RF_LTA_OUT_MAX
}ATBM2040_RF_LTA_OUT_e;

/*FEF Mode*/
typedef enum
{
    ATBM2040_FEF_INTERNAL = 0, /*FEF is detected by ATBM2040 itself*/
    ATBM2040_FEF_EXTERNAL_GPO1, /*FEF is detected by Demodulator and passed in from GPO1*/
    ATBM2040_FEF_EXTERNAL_GPO2, /*FEF is detected by Demodulator and passed in from GPO2*/
    ATBM2040_FEF_IGNORE, /*Ignore FEF*/

    ATBM2040_FEF_MODE_MAX
}ATBM2040_FEF_MODE_e;

/*Clock Mode*/
typedef enum
{
    ATBM2040_CLK_MODE_CRYSTAL = 0, /*XTALO/I connected with crystal*/
    ATBM2040_CLK_MODE_EXT, /* XTALI connected with external clock */

    ATBM2040_CLK_MODE_MAX
}ATBM2040_CLK_MODE_e;


/*Fast Tune Mode*/
typedef enum
{
    ATBM2040_FAST_TUNE_MODE_NORMAL = 0, /*normal tune*/
    ATBM2040_FAST_TUNE_MODE_FAST, /*fast tune*/

    ATBM2040_FAST_TUNE_MODE_MAX
}ATBM2040_FAST_TUNE_MODE_e;


/*ATBM2040 config setting command*/
typedef enum
{    
    ATBM2040_CFG_CMD_DTV_IF_OUT_SETTING = 0, /*set DTV IF output parameter,refer to ATBM2040IFOut_t*/
    ATBM2040_CFG_CMD_ATV_IF_OUT_SETTING, /*set ATV IF output parameter,refer to ATBM2040IFOut_t*/
    ATBM2040_CFG_CMD_CLK_OUT, /*set clock output parameter,refer to ATBM2040ClkOutCfg_t*/
    ATBM2040_CFG_CMD_PIN_SETTING, /*set PIN parameter,refer to ATBM2040PinCfg_t*/
    ATBM2040_CFG_CMD_OSC_CAP_SET, /*set OSC PPM calibration value,refer to ATBM2040OSCCalib_t*/
    ATBM2040_CFG_CMD_RF_LTA, /*set RF loop through output status, refer to ATBM2040_RF_LTA_OUT_e*/
    ATBM2040_CFG_CMD_FAST_TUNE, /*set fast tune mode, refer to ATBM2040_FAST_TUNE_MODE_e*/
    ATBM2040_CFG_CMD_MAX
}ATBM2040_CFG_CMD_e;

/*ATBM2040 config setting */
typedef struct
{
    ATBM2040_CFG_CMD_e CfgCmd; /*config setting command code*/
    union{
        ATBM2040IFOut_t IFOut; /*'CfgCmd' is 'ATBM2040_CFG_CMD_DTV_IF_OUT_SETTING' or 'ATBM2040_CFG_CMD_ATV_IF_OUT_SETTING'*/
        ATBM2040ClkOutCfg_t ClkOut; /*'CfgCmd' is 'ATBM2040_CFG_CMD_CLK_OUT'*/
        ATBM2040PinCfg_t PinCfg; /*'CfgCmd' is 'ATBM2040_CFG_CMD_PIN_SETTING'*/
        ATBM2040OSCCalib_t OSCCap; /*'CfgCmd' is 'ATBM2040_CFG_CMD_OSC_CAP_SET'*/
        ATBM2040_RF_LTA_OUT_e LTAOut; /*'CfgCmd' is 'ATBM2040_CFG_CMD_RF_LTA'*/
        ATBM2040_FAST_TUNE_MODE_e FastTuneMD; /*'CfgCmd' is 'ATBM2040_CFG_CMD_FAST_TUNE'*/
    }Cfg;
}ATBM2040CfgCMD_t;

typedef struct
{
    UINT8 I2CSlaveAddr; /*I2C Slave Address, e.g. 0xC0*/
    UINT32 Param; /*Other paramter, e.g. I2C bus number*/
}ATBM2040I2CAddr_t;
/*ATBM2040 configuration parameters when SDK init.*/
typedef struct
{
    UINT32 MagicCode; /*Magic code. Fixed by 'ATBM2040DefaultCfgGet', don't modify it!*/
    ATBM2040I2CAddr_t I2CParam; /*I2C paramter*/
    ATBM2040_CLK_MODE_e ClkMode; /*tuner clock mode*/
    UINT32 OSCFreqKHz; /*OSC Frequency in KHz, e.g. 24000KHz*/
    ATBM2040OSCCalib_t OSCCap; /*OSC PPM calibration*/
    ATBM2040_SIGNAL_MODE_e Mode; /*RF signal modulation*/
    ATBM2040IFOut_t DtvIFOut; /*parameters of DTV IF out*/
    ATBM2040IFOut_t AtvIFOut; /*parameters of ATV IF out*/
    ATBM2040ClkOutCfg_t ClkOut; /*control of Clock out*/
    ATBM2040_FEF_MODE_e FEFMode; /*FEF Mode(AGC Freeze in DVBT2 mode)*/
    ATBM2040PinCfg_t PinsCfg[ATBM2040_PIN_MAX]; /*Config parameters of PINs*/
    ATBM2040_RF_LTA_OUT_e LTAOut; /*RF Loopthrough output*/
    ATBM2040_FAST_TUNE_MODE_e FastTuneMD; /*Fast Tune mode*/
}ATBM2040InitConfig_t;

/********************************************************************
* Function: ATBM2040Init
* Description: Do initialization for ATBM2040 hardware .
*
* Input: DevId -- ID of ATBM2040;
*        pConfig -- Pointer to config data
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Init(UINT32 DevId,ATBM2040InitConfig_t *pConfig);

/********************************************************************
* Function: ATBM2040DefaultCfgGet
* Description: Get default config of ATBM2040 .
*
* Input:     N/A
* Output: pConfig -- Pointer to config buffer
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040DefaultCfgGet(ATBM2040InitConfig_t *pConfig);

/********************************************************************
* Function: ATBM2040CfgSet
* Description: Change some config parameter to ATBM2040 .
*
* Input: DevId -- ID of ATBM2040;
*        pCfgCmd -- Pointer to config command data
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040CfgSet(UINT32 DevId,ATBM2040CfgCMD_t *pCfgCmd);


/********************************************************************
* Function: ATBM2040ChannelTune
* Description: Tune to a channel with special parameter.
*
* Input: DevId -- ID of ATBM2040;
*        Mode -- RF signal mode, refer to ATBM2040_SIGNAL_MODE_e
*        FreqKHz -- RF center frequency in KHz
*        BandWidthKHz -- Signal bandwidth in KHz
*        SpectrumMode -- IF out with inversed spectrum or not
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040ChannelTune(UINT32 DevId,ATBM2040_SIGNAL_MODE_e Mode,UINT32 FreqKHz,UINT32 BandWidthKHz,ATBM2040_SPECTRUM_MODE_e SpectrumMode);

/********************************************************************
* Function: ATBM2040GetLockStatus
* Description: Get RF signal locking status .
*
* Input: DevId -- ID of ATBM2040;
* Output: pLockStatus -- Pointer to lock status
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetLockStatus(UINT32 DevId,BOOL *pLockStatus);

/********************************************************************
* Function: ATBM2040GetIFFreq
* Description: Get IF Frequecy(in Hz).
*
* Input: DevId -- ID of ATBM2040;
* Output: pIFFreqHz -- Pointer to IF frequency(in Hz)
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetIFFreq(UINT32 DevId,UINT32 *pIFFreqHz);

/********************************************************************
* Function: ATBM2040GetRSSI
* Description: Get current RSSI(in dB) .
*
* Input: DevId -- ID of ATBM2040;
* Output: pRSSIx16 -- Pointer to RSSI
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetRSSI(UINT32 DevId,SINT32 *pRSSI);

/********************************************************************
* Function: ATBM2040Standby
* Description: Make ATBM2040 enter into standby state .
*
* Input: DevId -- ID of ATBM2040;
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Standby(UINT32 DevId);

/********************************************************************
* Function: ATBM2040Wakeup
* Description:  Make ATBM2040 enter into wakeup state .
*
* Input: DevId -- ID of ATBM2040;
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Wakeup(UINT32 DevId);

/********************************************************************
* Function: ATBM2040GetSDKVer
* Description:  Get version of ATBM2040 SDK .
*
* Input: DevId -- ID of ATBM2040;
* Output: pVersion -- Pointer to version number(e.g. 102 means v1.0.2)
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetSDKVer(UINT32 DevId,UINT32 *pVersion);

/********************************************************************
* Function: ATBM2040Process
* Input: DevId -- ID of ATBM2040;
* Description:  This API should be called constantly by user application, for example every 200ms one time. 
********************************************************************/
ATBM2040_ERROR_e ATBM2040Process(UINT32 DevId);

/********************************************************************
* Function: ATBM2040Detect
* Description: Check if ATBM2040 exist or not.
*
* Input: pI2CInfo -- I2C paramters, including slave address and other user paramter;
*        
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- ATBM2040 exist; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Detect(ATBM2040I2CAddr_t *pI2CInfo);

#ifdef __cplusplus
}
#endif

#endif /*__ATBM2040API_H__*/
                                                                         
