
/********************************************************************************************************
*Copyright (C) 2016-2030, Altobeam
*File name: ATBM2040Api.c
*Author: duanqiang
*Description: Implement of ATBM2040 SDK APIs.
*
*Modification History:
    2016-08-02:
        1. Release SDK v1.0.0
    2016-11-23:
        1. Release SDK v1.0.1
    2017-03-02:
        1. Release SDK v1.0.2
    2017-04-06:
        1. Release SDK v1.0.3
    2017-04-25:
        1. Release SDK v1.0.4
    2017-05-12:
        1. Release SDK v1.0.5
    2017-07-11:
        1. Release SDK v1.0.6
    2017-08-25:
        1. Release SDK v1.0.7
*********************************************************************************************************/
#include "ATBM2040Porting.h"
#include "ATBM2040Driver.h"

#define ATBM_TUNER_DEFAULT_I2C_ADDR (0xC0)
#define ATBM_TUNER_DEFAULT_IF (5000000)
#define ATBM_TUNER_DEFAULT_OSC_FREQKHZ (24000)
#define ATBM_TUNER_DEFAULT_OSC_CAP (0x10)
#define ATBM_TUNER_MAGIC_CODE (0x4D425441) /*('ATBM')*/
static ATBM2040_t ATBM2040Tuner[ATBM2040_TUNER_COUNT];
static BOOL ATBM2040MutexInitFlag = FALSE;
/********************************************************************
* Function: ATBM2040Init
* Description: Do initialization for ATBM2040 hardware .
*
* Input: DevId -- ID of ATBM2040;
*        pConfig -- Pointer to config data
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Init(UINT32 DevId,ATBM2040InitConfig_t *pConfig)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;

    if((NULL == pConfig)||(ATBM_TUNER_MAGIC_CODE != pConfig->MagicCode)||(DevId >= ATBM2040_TUNER_COUNT))
    {
        ATBM2040Print(("[Error]ATBM2040Init(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    if(!ATBM2040MutexInitFlag)
    {
        ret = ATBM2040MutexInit();
        if(ATBM2040_NO_ERROR != ret)
        {
            ATBM2040Print(("[Error]ATBM2040MutexInit() Failed!\n"));
            return ret;
        }
        ATBM2040MutexInitFlag = TRUE;
    }
    ret = ATBM2040MutexLock();
    pTuner = &ATBM2040Tuner[DevId];
    pTuner->Config = *pConfig; /*Save user parameters.*/
    pTuner->LNAGainMD = 0;

    ret |= ATBM2040DrvInit(pTuner);
    ATBM2040CfgPrint(pTuner); /*Debug info print*/
    ATBM2040Print(("[Info]ATBM2040Init(),ret =%d\n",ret));
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040DefaultCfgGet
* Description: Get default config of ATBM2040 .
*
* Input: N/A
* Output: pConfig -- Pointer to config buffer
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040DefaultCfgGet(ATBM2040InitConfig_t *pConfig)
{
    if(NULL == pConfig)
    {
        ATBM2040Print(("[Error]ATBM2040DefaultCfgGet(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    /*Default config of ATBM2040*/
    pConfig->MagicCode = ATBM_TUNER_MAGIC_CODE;
    pConfig->I2CParam.I2CSlaveAddr = ATBM_TUNER_DEFAULT_I2C_ADDR;
    pConfig->I2CParam.Param = 0;
#if ENABLE_TUNER_CLK_EXT
    pConfig->ClkMode = ATBM2040_CLK_MODE_EXT;
#else
    pConfig->ClkMode = ATBM2040_CLK_MODE_CRYSTAL;
#endif
    pConfig->OSCFreqKHz = ATBM_TUNER_DEFAULT_OSC_FREQKHZ;
    pConfig->OSCCap.CalibValue = ATBM_TUNER_DEFAULT_OSC_CAP;
    pConfig->Mode = ATBM2040_SIGNAL_MODE_DTMB;
    pConfig->DtvIFOut.IFOutFreqHz = ATBM_TUNER_DEFAULT_IF;
    pConfig->DtvIFOut.IFOutLevel = ATBM2040_IF_OUT_LEVEL2;
    pConfig->DtvIFOut.LevelSpinner = 0;
    pConfig->AtvIFOut.IFOutFreqHz = ATBM_TUNER_DEFAULT_IF;
    pConfig->AtvIFOut.IFOutLevel = ATBM2040_IF_OUT_LEVEL1;
    pConfig->AtvIFOut.LevelSpinner = 0;
    pConfig->ClkOut.ClkOutEnable = ATBM2040_CLK_OUT_DISABLE;
    pConfig->ClkOut.ClkOutAmp = ATBM2040_CLK_OUT_AMP_L5;
    pConfig->FEFMode = ATBM2040_FEF_INTERNAL;
    pConfig->PinsCfg[0].PinName = ATBM2040_PIN_NAME_GPO1;
    pConfig->PinsCfg[0].PinState = ATBM2040_GPO_STATE_LOW;
    pConfig->PinsCfg[1].PinName = ATBM2040_PIN_NAME_GPO2;
    pConfig->PinsCfg[1].PinState = ATBM2040_GPO_STATE_LOW;
    pConfig->LTAOut = ATBM2040_RF_LTA_OUT_DISABLE;
    pConfig->FastTuneMD = ATBM2040_FAST_TUNE_MODE_NORMAL;

    ATBM2040Print(("[Info]ATBM2040DefaultCfgGet(),ret =%d\n",ATBM2040_NO_ERROR));
    return ATBM2040_NO_ERROR;
}

/********************************************************************
* Function: ATBM2040CfgSet
* Description: Change some config parameter to ATBM2040 .
*
* Input:     DevId -- ID of ATBM2040;
*        pCfgCmd -- Pointer to config command data
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040CfgSet(UINT32 DevId,ATBM2040CfgCMD_t *pCfg)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;

    if((DevId >= ATBM2040_TUNER_COUNT)||(NULL == pCfg))
    {
        ATBM2040Print(("[Error]ATBM2040CfgSet(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }

    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040CfgSet(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }

    ret = ATBM2040MutexLock();
    ret |= ATBM2040DrvCfgSet(pTuner,pCfg);
    ATBM2040Print(("[Info]ATBM2040CfgSet(),ret =%d\n",ret));
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040ChannelTune
* Description: Tune to a channel with special parameter.
*
* Input:     DevId -- ID of ATBM2040;
*        Mode -- RF signal mode, refer to ATBM2040_SIGNAL_MODE_e
*        FreqKHz -- RF center frequency in KHz
*        BandWidthKHz -- Signal bandwidth in KHz
*        SpectrumMode -- IF out with inversed spectrum or not
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040ChannelTune(UINT32 DevId,ATBM2040_SIGNAL_MODE_e Mode,UINT32 FreqKHz,UINT32 BandWidthKHz,ATBM2040_SPECTRUM_MODE_e SpectrumMode)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;

    if((DevId >= ATBM2040_TUNER_COUNT)||(FreqKHz > 1000000)||(BandWidthKHz > 10000))
    {
        ATBM2040Print(("[Error]ATBM2040ChannelTune(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }

    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040ChannelTune(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }
    ret = ATBM2040MutexLock();
    pTuner->FreqKHz = FreqKHz;
    pTuner->BWKHz = BandWidthKHz;
    pTuner->InvertSpectrum = (ATBM2040_SPECTRUM_NORMAL==SpectrumMode)?(FALSE):(TRUE);
    pTuner->SignalMode = Mode;
    ret |= ATBM2040DrvFreqTune(pTuner);
    pTuner->BWKHzBak = pTuner->BWKHz;
    pTuner->MixerIFBak = pTuner->MixerIF;
    pTuner->BandBak = pTuner->Band;
    pTuner->SignalMdBak = pTuner->SignalMode;
    ATBM2040Print(("[Info]ATBM2040ChannelTune(%d,%d,%d,%d),ret =%d\n",(UINT32)Mode,FreqKHz,BandWidthKHz,(UINT32)SpectrumMode,ret));
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040GetLockStatus
* Description: Get RF signal locking status .
*
* Input:     DevId -- ID of ATBM2040;
* Output: pLockStatus -- Pointer to lock status
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetLockStatus(UINT32 DevId,BOOL *pLockStatus)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 Val = 0;
    ATBM2040_t *pTuner = NULL;

    if(DevId >= ATBM2040_TUNER_COUNT)
    {
        ATBM2040Print(("[Error]ATBM2040GetLockStatus(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040GetLockStatus(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }
    ret = ATBM2040MutexLock();
    *pLockStatus = FALSE;
    ret |= ATBM2040RegRead(&pTuner->Config.I2CParam,0x14,0xAA, &Val); /*ro_reg_agc_setting_state[1:0]*/
    if((ATBM2040_NO_ERROR == ret)&&((0x02 == Val)||(0x03 == Val)))
    {
        *pLockStatus = TRUE;
    }
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040GetIFFreq
* Description: Get IF Frequecy(in Hz).
*
* Input:     DevId -- ID of ATBM2040;
* Output: pIFFreqHz -- Pointer to IF frequency(in Hz)
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetIFFreq(UINT32 DevId,UINT32 *pIFFreqHz)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;
    ATBM2040InitConfig_t Config;

    if((DevId >= ATBM2040_TUNER_COUNT)||(NULL == pIFFreqHz))
    {
        ATBM2040Print(("[Error]ATBM2040GetIFFreq(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    pTuner = &ATBM2040Tuner[DevId];
    ret = ATBM2040MutexLock();
    if(pTuner->Inited)
    {
        Config = pTuner->Config;
    }
    else
    {
        ret |= ATBM2040DefaultCfgGet(&Config);
        if(ATBM2040_NO_ERROR != ret)
        {
            ATBM2040Print(("[Error]ATBM2040DefaultCfgGet(),failed!ret = %d\n",ret));
            return ret;
        }
    }
    if(ATBM2040_SIGNAL_MODE_ATV == Config.Mode)
    {
        *pIFFreqHz = pTuner->Config.AtvIFOut.IFOutFreqHz;
    }
    else
    {
        *pIFFreqHz = pTuner->Config.DtvIFOut.IFOutFreqHz;
    }

    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040GetRSSI
* Description: Get current RSSI(in dBm) .
*
* Input:     DevId -- ID of ATBM2040;
* Output: pRSSI -- Pointer to RSSI
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetRSSI(UINT32 DevId,SINT32 *pRSSI)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    SINT16 SignalPow = 0;
    ATBM2040_t *pTuner = NULL;

    if((DevId >= ATBM2040_TUNER_COUNT)||(NULL == pRSSI))
    {
        ATBM2040Print(("[Error]ATBM2040GetRSSI(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    ret = ATBM2040MutexLock();
    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040GetRSSI(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }
    ret |= ATBM2040DrvGetRSSI(&pTuner->Config.I2CParam,&SignalPow);
    *pRSSI = SignalPow/16;

    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040Standby
* Description: Make ATBM2040 enter into standby state .
*
* Input:     DevId -- ID of ATBM2040;
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Standby(UINT32 DevId)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;

    if(DevId >= ATBM2040_TUNER_COUNT)
    {
        ATBM2040Print(("[Error]ATBM2040Standby(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    ret = ATBM2040MutexLock();
    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040Standby(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }
    ret |= ATBM2040DrvStandby(pTuner);
    ATBM2040Print(("[Info]ATBM2040Standby(),ret =%d\n",ret));
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040Wakeup
* Description:  Make ATBM2040 enter into wakeup state .
*
* Input:     DevId -- ID of ATBM2040;
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Wakeup(UINT32 DevId)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;

    if(DevId >= ATBM2040_TUNER_COUNT)
    {
        ATBM2040Print(("[Error]ATBM2040Wakeup(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    ret |= ATBM2040MutexLock();
    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040Wakeup(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }
    ret |= ATBM2040DrvWakeup(pTuner);
    ATBM2040Print(("[Info]ATBM2040Wakeup(),ret =%d\n",ret));
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040GetSDKVer
* Description:  Get version of ATBM2040 SDK .
*
* Input:     DevId -- ID of ATBM2040;
* Output: pVersion -- Pointer to version number(e.g. 102 means v1.0.2)
* Retrun: ATBM2040_ERROR_NO_ERROR -- no error; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040GetSDKVer(UINT32 DevId,UINT32 *pVersion)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;

    if((DevId >= ATBM2040_TUNER_COUNT)||(NULL == pVersion))
    {
        ATBM2040Print(("[Error]ATBM2040GetSDKVer(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    ret = ATBM2040MutexLock();
    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040GetSDKVer(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }
    ret |= ATBM2040DrvGetSDKVer(pTuner,pVersion);
    ATBM2040Print(("[Info]ATBM2040GetSDKVer(),ret =%d\n",ret));
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040Process
* Input:     DevId -- ID of ATBM2040;
* Description:  This API should be called constantly by user application, for example every 200ms one time.
********************************************************************/
ATBM2040_ERROR_e ATBM2040Process(UINT32 DevId)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040_t *pTuner = NULL;

    if(DevId >= ATBM2040_TUNER_COUNT)
    {
        ATBM2040Print(("[Error]ATBM2040Process(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    ret = ATBM2040MutexLock();
    pTuner = &ATBM2040Tuner[DevId];
    if(!pTuner->Inited)
    {
        ATBM2040Print(("[Error]ATBM2040Process(),ATBM2040 is not initialized!\n"));
        return ATBM2040_ERROR_NOT_INIT;
    }
    ret |= ATBM2040DrvProcess(pTuner);
    ret |= ATBM2040MutexUnLock();
    return ret;
}

/********************************************************************
* Function: ATBM2040Detect
* Description: Check if ATBM2040 exist or not.
*
* Input:     pI2CInfo -- I2C paramters, including slave address and other user paramter;
*
* Output: N/A
* Retrun: ATBM2040_ERROR_NO_ERROR -- ATBM2040 exist; others refer to ATBM2040_ERROR_e
********************************************************************/
ATBM2040_ERROR_e ATBM2040Detect(ATBM2040I2CAddr_t *pI2CInfo)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;

    if(NULL == pI2CInfo)
    {
        ATBM2040Print(("[Error]pI2CInfo(),invalid parameter!\n"));
        return ATBM2040_ERROR_BAD_PARAM;
    }
    if(!ATBM2040MutexInitFlag)
    {
        ret = ATBM2040MutexInit();
        if(ATBM2040_NO_ERROR != ret)
        {
            ATBM2040Print(("[Error]ATBM2040MutexInit() Failed!\n"));
            return ret;
        }
        ATBM2040MutexInitFlag = TRUE;
    }
    ret = ATBM2040MutexLock();
    ret |= ATBM2040DrvDetect(pI2CInfo);
    ATBM2040Print(("[Info]ATBM2040Detect(),ret =%d\n",ret));
    ret |= ATBM2040MutexUnLock();
    return ret;
}


#ifdef ATBM2040_CHIP_DEBUG_OPEN
ATBM2040_t *ATBM2040ObjGet(UINT32 DevId)
{
    ATBM2040_t *pTuner = NULL;

    if(DevId >= ATBM2040_TUNER_COUNT)
    {
        ATBM2040Print(("[Error]ATBM2040Wakeup(),invalid parameter!\n"));
        return NULL;
    }
    pTuner = &ATBM2040Tuner[DevId];

    return pTuner;
}
#endif

