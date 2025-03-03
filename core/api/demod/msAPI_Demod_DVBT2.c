
#if(ENABLE_DEMOD_DVBT2)

#if (FRONTEND_DEMOD_T2_TYPE == EMBEDDED_DVBT2_DEMOD)
    #include "drvDMD_INTERN_DVBT2.h"
#endif

BOOL msAPI_Demod_DVBT2_Init(void)
{
#if (FRONTEND_DEMOD_T2_TYPE == EMBEDDED_DVBT2_DEMOD)
    INTERN_T2_PowerOnInit();
#elif (FRONTEND_DEMOD_T2_TYPE == SI2164B_DVBT)
    devDemod_Silab2164B_DVBT2Init();
#else
    mdev_CofdmInit();
    mdev_CofdmControlPowerOnOff(TRUE);
#endif
    return TRUE;
}

void msAPI_Demod_DVBT2_Set_Power(BOOL bTurnOn)
{
#if (FRONTEND_DEMOD_T2_TYPE == EMBEDDED_DVBT2_DEMOD)
    //bTurnOn=bTurnOn;
    mdev_CofdmControlPowerOnOff(bTurnOn);
#elif (FRONTEND_DEMOD_T2_TYPE == SI2164B_DVBT)
    devDemod_Silab2164B_DVBT2_SetPower(bTurnOn);
#else
    mdev_CofdmControlPowerOnOff(bTurnOn);
#endif
}

void msAPI_Demod_DVBT2_Exit(void)
{
#if (FRONTEND_DEMOD_T2_TYPE == SI2164B_DVBT)
    devDemod_Silab2164B_DVBT2_SetPower(FALSE);
#elif (FRONTEND_DEMOD_T2_TYPE == EMBEDDED_DVBT2_DEMOD)
    MDrv_DMD_DVBT2_Exit();
#else
    mdev_CofdmControlPowerOnOff(FALSE);
#endif
}

EnuApiDemodLockStatus msAPI_Demod_DVBT2_Get_LockStatus(void)
{
#if (FRONTEND_DEMOD_T2_TYPE == SI2164B_DVBT)
    if(devDemod_Silab2164B_DVBT2_GetLockStatus())
        return E_API_DEMOD_STATUS_LOCKED;

#else
    if( TRUE == mdev_CofdmGetLockStatus(COFDM_FEC_LOCK_T2_123X) )
    {
        return E_API_DEMOD_STATUS_LOCKED;
    }
#endif
    return E_API_DEMOD_STATUS_NO_LOCK;
}

#if( (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)   \
      )
    #define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NORMAL             2000
    #define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NO_LOCK_HISTORY    1500

#elif( (FRONTEND_DEMOD_DVBT_TYPE == SI2164B_DVBT)   \
          )
    #define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NORMAL             2000
   //#define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NO_LOCK_HISTORY    1500


#elif( FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD )
    #define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NORMAL             10000 // 10sec
    #define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NO_LOCK_HISTORY    1500

#else //
    #define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NORMAL             10000
    #define DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NO_LOCK_HISTORY    1500
#endif

EnuApiDemodLockStatus msAPI_Demod_DVBT2_DetectLockTask(void)
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    U32 u32Timeout = DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NORMAL;


    //printf("[DVBT2_Detect]");
#if (FRONTEND_DEMOD_T2_TYPE == SI2164B_DVBT)
    if(devDemod_Silab2164B_DVBT2_GetLockStatus())
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
        return eDemodLockStatus;
    }    
#else


    if (mdev_CofdmGetLockStatus(COFDM_FEC_LOCK_T2_123X) == TRUE)
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
        return eDemodLockStatus;
    }

    if (mdev_CofdmGetLockStatus(COFDM_P1_LOCK_HISTORY_123X) == FALSE) // No lock history
    { //Speed up
        u32Timeout = DEMOD_DVBT2_DETECT_LOCK_TIMEOUT__NO_LOCK_HISTORY;
    }
#endif
    if( msAPI_Demod_Get_DetectLockUseTime() > u32Timeout )
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    }
    else
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_CHECKING;
    }

    return eDemodLockStatus;
}

BOOLEAN msAPI_Demod_DVBT2_Get_PostViterbiBer(float *ber)
{
    *ber = 0;
#if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_GetPostViterbiBer(ber);
#elif (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB1210_DEMOD)
    return MSB1210_GetPostViterbiBer(ber);
#elif (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    return MSB124X_DTV_GetPostBER(ber);
#elif (FRONTEND_DEMOD_DVBT_TYPE == SI2164B_DVBT)
    return devDemod_Silab2164B_DVBT2_GetPostBER(ber);

#elif (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
  #if DEMOD_DVBT_USE_UTOPIA
    return MDrv_DMD_DVBT_GetPostViterbiBer(ber);
  #else
    return INTERN_DVBT_GetPostViterbiBer(ber);
  #endif
    return FALSE;
#endif
}



BOOL msAPI_Demod_DVBT2_GetSignalQuality(WORD *quality)
{

#if(FRONTEND_DEMOD_DVBT_TYPE == SI2164B_DVBT)
    *quality=devDemod_Silab2164B_GetSignalQuality();
     return TRUE;
#else
    return mdev_CofdmGetSignalQuality(quality);

#endif


}

BOOLEAN msAPI_Demod_DVBT2_Ready(void)
{
#if(FRONTEND_DEMOD_DVBT_TYPE == SI2164B_DVBT)
    return devDemod_Silab2164B_Ready();
#else
    return mdev_Cofdm_MSB123X_Ready();
#endif

}


#endif

