
#ifndef __ATBM2040DRIVER_H__    
#define __ATBM2040DRIVER_H__


#ifdef __cplusplus
extern "C"
{
#endif

#define ATBM_LEOG_CHIP_ID (0xAA)
#define ATBM_LEOF_CHIP_ID (0xE1) /*LeoF*/
#define ATBM_LEOE_CHIP_ID (0xE2) /*LeoE V2*/
#define ATBM_LEOD_CHIP_ID (0xCD)
#define ATBM_LEOC_CHIP_ID (0xCC)
#define ATBM_LEOB_CHIP_ID (0xF0)
/*#define ATBM_LEO_CHIP_ID (0x5D)*/

typedef struct
{
    UINT32 Low;
    UINT32 High;
}ATBM2040Data64_t;

#define ATBM2040_ARRAY_NUM(array) (sizeof(array)/sizeof(array[0]))

typedef struct
{
    UINT32 FreqStart; /*in KHz*/  
    UINT32 FreqEnd; /*in KHz*/    
    UINT8 NMixer;
    UINT8 NLO;
}ATBM2040NLOMixer_t;

/*list registers struct for a special module,for example PLL, and so on*/
typedef struct
{
    UINT8 BaseReg;
    UINT8 OffReg;
    UINT8 Val;
}ATBM2040Reg_t;   

typedef struct
{
    UINT8 BaseReg;
    UINT8 OffReg;
    UINT8 Data[64];
    UINT8 Len;
}ATBM2040RegGroup_t;

typedef struct
{
    UINT8 BaseAddr;
    UINT8 Len;
    UINT8 Data[64];
}ATBM2040HalfAddrRegGroup_t;   


typedef struct
{
    UINT8 BaseReg;
    UINT8 OffReg;
    UINT8 Data[256];
    UINT32 Len;
}ATBM2040Firmware_t;


typedef struct
{  
    UINT32 FreqStart; /*in KHz*/  
    UINT32 FreqEnd; /*in MHz*/  
    UINT32 N_ADC;
}ATBM2040ADCDivider_t; 

typedef struct
{
    UINT32 FreqKHz;/*center frequency in KHz*/
    UINT8 vhf_fltr_res1_sel;
    UINT8 vhf_fltr_data;
    UINT8 vhf_fltr_ref_code;    
}ATBM2040VHFChIndex_t;

typedef struct
{
    UINT32 FreqMHz;/*center frequency in MHz*/
    UINT32 uhf_filt_freq;
    UINT32 uhf_fltr_gm_switch;
    UINT32 uhf_fltr_manual;
}ATBM2040UHFChIndex_t;

typedef struct
{
    UINT32 FreqMHz;/*center frequency in MHz*/
    UINT32 uhf_fltr_manual;

    UINT8 uhf_fltr_fcal_gm_gain;
    UINT8 uhf_filt_fcal_fail;
    UINT16 uhf_filt_fcal_cap_ctrl;
}ATBM2040UHFCalResult_t;


typedef struct
{
    UINT32 FreqMHz;/*center frequency in MHz*/
    UINT32 vhf2_filt_freq;
    UINT32 vhf2_fltr_gm_switch;
}ATBM2040VHF2ChIndex_t;

typedef struct
{
    UINT32 FreqMHz;/*center frequency in MHz*/

    UINT32 vhf2_fltr_gm_switch;

    UINT8 uhf_fltr_fcal_gm_gain;
    UINT8 uhf_filt_fcal_fail;
    UINT16 uhf_filt_fcal_cap_ctrl;

    
}ATBM2040VHF2CalResult_t;

typedef struct
{
    UINT32 FreqKHz;/*center frequency in KHz*/
    UINT8 vhf_fltr_ref_code;    
}ATBM2040VHF1ChIndex_t;


typedef enum
{
    ATBM2040_SAR_ADC_CLK_6MHZ = 0,
    ATBM2040_SAR_ADC_CLK_1_5MHZ,

    ATBM2040_SAR_ADC_CLK_MAX
}ATBM2040SarAdcClk_e;

typedef enum
{
    ATBM2040_IF_PATH_1 = 0,
    ATBM2040_IF_PATH_2,    

    ATBM2040_IF_PATH_MAX
}ATBM2040_IF_PATH_e;

typedef enum
{
    ATBM2040_RF_BAND_VHF1 = 0,
    ATBM2040_RF_BAND_VHF2,
    ATBM2040_RF_BAND_UHF,

    ATBM2040_RF_BAND_MAX
}ATBM2040_RF_BAND_e;

typedef struct
{
    UINT32 StartFreqMHz;    
    UINT32 EndFreqMHz;
    SINT32 RegVal[32];
}ATBM2040AgcPowerTarget_t;


typedef struct
{
    ATBM2040InitConfig_t Config; /*user config parameters*/
    UINT8 ChipID; /*Chip ID*/
    ATBM2040_SIGNAL_MODE_e SignalMode; /* signal mode*/
    ATBM2040_SIGNAL_MODE_e SignalMdBak; /* signal mode*/
    UINT32 FreqKHz;/*Channel frequency in KHz, user passed in*/
    ATBM2040_RF_BAND_e Band; /*cur RF band*/
    ATBM2040_RF_BAND_e BandBak; /* RF band bakup*/
    UINT32 BWKHz; /*Bandwidth in KHz*/
    UINT32 BWKHzBak; /*Bandwidth backup*/
    BOOL InvertSpectrum; /*TRUE:invert spectrum;FALSE:normal*/

    ATBM2040NLOMixer_t *pNLOMixer;/*current MixerDiv*/
    ATBM2040NLOMixer_t *pNLOMixerHMD;
    ATBM2040NLOMixer_t *pNLOMixerLMD;    
    ATBM2040ADCDivider_t *pAdcDiv;/*current ADC Divider*/
    ATBM2040ADCDivider_t *pAdcDivHMD;
    ATBM2040ADCDivider_t *pAdcDivLMD;
    UINT32 HMDAdcClkHz;
    UINT32 LMDAdcClkHz;    

    SINT16 RFPower; /**/ 
    UINT8 ModeTrend;
    UINT8 DSPClkSel; /*0: select OSC; 1: OSC/4*/
    UINT8 ForceChipID; /*Chip ID*/    
    UINT32 IFLevelSpinner; /*Spinner of IF out level*/
    UINT32 LNAGainMD;
    SINT32 MixerIF; /*Mixer IF in Hz*/
    SINT32 MixerIFBak; /*Mixer IF backup*/
    BOOL HighMD; /*TRUE:high */
    BOOL ADCIQSwap; /*TRUE:ADC IQ Swap;FALSE:normal*/
    UINT32 PllDivMode; /*pll_mod_mmd, 0:div/2; 1:div/1*/
    ATBM2040SarAdcClk_e SarAdcClk; /*SAR ADC Clock*/
    UINT32 LowCousumMd;
    BOOL StandbyState;/*TRUE:in standby state; FALSE:wakeup*/

    UINT8 vhf_fltr_ref_code_out;
    UINT8 vhf_fltr_cal_fail;

    ATBM2040AgcPowerTarget_t *pTargetBak;

    BOOL Inited;/*SDK init flag*/
}ATBM2040_t;


#define ATBM2040ABS(x) (((x)>0)?((x)):(-(x)))
#define ATBM2040_UHF_LOW_KHZ (400000)
#define ATBM2040_VHF_CHECK(FreqKHz) (((UINT32)(FreqKHz) <= ATBM2040_UHF_LOW_KHZ)?(TRUE):(FALSE))
#define ATBM2040_MIXER_MD_DIVISION_KHZ (400000)
#define ATBM2040_VHF2_LOW_KHZ (160000)

#define ATBM2040RegListWrite(Id,RegList,Num) for(;;){\
    UINT32 n = 0;\
    ATBM2040Reg_t *pReg = RegList;\
    for(n=0;n<Num;n++){\
        ret |= ATBM2040I2CWrite(Id,pReg->BaseReg,pReg->OffReg,&pReg->Val,1);\
        pReg++;}\
    break;\
}

#define ATBM2040RegListWriteExt(Id,RegList,Num, RegNewValue) for(;;){\
    UINT32 n = 0;\
    ATBM2040Reg_t *pReg = RegList;\
    for(n=0;n<Num;n++){\
        if((pReg->OffReg != RegNewValue.OffReg)||(pReg->BaseReg != RegNewValue.BaseReg)){\
        ret |= ATBM2040I2CWrite(Id,pReg->BaseReg,pReg->OffReg,&pReg->Val,1);}\
        else{ret |= ATBM2040I2CWrite(Id,RegNewValue.BaseReg,RegNewValue.OffReg,&RegNewValue.Val,1);}\
        pReg++;}\
    break;\
}

#define ATBM2040RegRevise(RegList,Num,RegBase,RegOff,NewVal) for(;;){\
    UINT32 n = 0;\
    ATBM2040Reg_t *pReg = RegList;\
    for(n=0;n<Num;n++){ if((pReg->BaseReg == RegBase)&&(pReg->OffReg == RegOff)){pReg->Val=NewVal;}\
        pReg++;}\
    break;\
}
#define ATBM2040_BURST_WRITE_START {
#define ATBM2040_BURST_WRITE_END }
#define ATBM2040_REG_ADDR_SET(_REG,_BaseAddr,_OffAddr) _REG.BaseReg = _BaseAddr;_REG.OffReg = _OffAddr;

#define ATBM2040_GAIN_PHASE_COMPENSATION (0) /*1: open gain and phase compensation;0: close gain and phase compensation;*/
#define ATBM2040_FIRMWARE_LOAD (1)

#ifdef  ATBM2040_CHIP_DEBUG_OPEN
extern ATBM2040_ERROR_e ATBM2040DrvChipDebugOption(ATBM2040_t *pTuner);
extern ATBM2040_ERROR_e ATBM2040DrvChipDebugSwConfigDone(ATBM2040_t *pTuner);
extern SINT32 ATBM2040DrvChipDebugPowerTargetSet(ATBM2040_t *pTuner,ATBM2040Reg_t *pReg,UINT32 RegCnt);
extern ATBM2040_ERROR_e ATBM2040DrvChipDebugUHFFilterGMManaulRatioGet(ATBM2040_t *pTuner,double *pGmRatio,double *pManaulRatio,
                                                                                      double *pRFRatio,int *pRFOffset,BOOL *pDebugOpen);
extern ATBM2040_ERROR_e ATBM2040DrvFirmwareEnable(ATBM2040_t *pTuner);
extern ATBM2040_ERROR_e ATBM2040DrvFirmwareDisable(ATBM2040_t *pTuner);

#endif

ATBM2040_ERROR_e ATBM2040RegWrite(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 Value);
ATBM2040_ERROR_e ATBM2040RegRead(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 *pValue);
ATBM2040_ERROR_e ATBM2040DrvRegLatch(ATBM2040I2CAddr_t *pI2CAddr,BOOL OnOff);
void ATBM2040DrvPLLDivCal(ATBM2040_t *pTuner,UINT8 *pNInt,UINT32 *pNFrac,BOOL HighMD);
ATBM2040_ERROR_e ATBM2040DrvSwReset(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvInit(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvFreqTune(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvCfgSet(ATBM2040_t *pTuner,ATBM2040CfgCMD_t *pCfg);
ATBM2040_ERROR_e ATBM2040DrvFastTuneModeSet(ATBM2040_t *pTuner);

void ATBM2040DrvADCClkCal(ATBM2040_t *pTuner, UINT32 *pHLOAdcClkHz, UINT32  *pLLOAdcClkHz);
ATBM2040_ERROR_e ATBM2040DrvGetRSSI(ATBM2040I2CAddr_t *pI2CAddr,SINT16 *pRSSIx16);
ATBM2040_ERROR_e ATBM2040DrvGetATVCfo(ATBM2040I2CAddr_t *pI2CAddr,SINT32 *pCfoKHz);
ATBM2040_ERROR_e ATBM2040DrvStandby(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvWakeup(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvGetSDKVer(ATBM2040_t *pTuner,UINT32 *pVer);
void ATBM2040DrvIIRCoefJudgeStateSet(BOOL Open);
ATBM2040_ERROR_e ATBM2040DrvIIRCoefJudge(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvLteTargetSet(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvRSSICalibration(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvProcess(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvRegDataFlushWrite(ATBM2040I2CAddr_t *pSlvAddr,UINT8 BaseAddr,UINT8 OffAddr,UINT8 *pData,UINT32 Size);
ATBM2040_ERROR_e ATBM2040DrvRegDataBurstWrite(ATBM2040_t *pTuner,UINT8 *pData,UINT32 Size);
ATBM2040_ERROR_e ATBM2040DrvRegHalfAddrBurstWrite(ATBM2040_t *pTuner,UINT8 BaseAddr,UINT8 *pData,UINT8 Length);
ATBM2040_ERROR_e ATBM2040DrvRxFltAndSpectrumParse(ATBM2040_t *pTuner);
ATBM2040_ERROR_e ATBM2040DrvDetect(ATBM2040I2CAddr_t *pI2CAddr);

void ATBM2040CfgPrint(ATBM2040_t *pTuner);


#ifdef __cplusplus
}
#endif

#endif /*__ATBM2040DRIVER_H__*/
                                                                         
