//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  [Doxygen]
/// @file msapi_audio.h
/// @brief API for Audio Control
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#include "Board.h"

#include "MApp_InputSource.h"

//===============================================================================

#if (ENABLE_AUDIO_SYS_BTSC)
void CheckATVAudioMode_BTSC(void)
{
    AUDIOMODE_TYPE eDetectedAudioMode;
    EN_DUAL_AUDIO_SELECTION eSaveAudioMode;

    eDetectedAudioMode = (AUDIOMODE_TYPE)MApi_AUDIO_SIF_GetSoundMode();

    if( eDetectedAudioMode == E_AUDIOMODE_INVALID )
        return;

    if( (m_eAudioMode == eDetectedAudioMode&&!bForceCheckAudioMode )||
        (m_eAudioMode == eDetectedAudioMode&&eDetectedAudioMode==E_AUDIOMODE_K_STEREO))
        return;

    if( ((m_eAudioMode == E_AUDIOMODE_DUAL_A) || (m_eAudioMode == E_AUDIOMODE_DUAL_B) || (m_eAudioMode == E_AUDIOMODE_DUAL_AB)) &&
        ((eDetectedAudioMode == E_AUDIOMODE_DUAL_A) || (eDetectedAudioMode == E_AUDIOMODE_DUAL_B) || (eDetectedAudioMode == E_AUDIOMODE_DUAL_AB)) )
    {
        return;
    }

  #if 1
    if(bForceCheckAudioMode)
    {
      //  printf("\r\n m_eAudioMode=%bu",m_eAudioMode);
       // printf("\r\n eDetectedAudioMode=%bu",eDetectedAudioMode);
        if(eDetectedAudioMode==E_AUDIOMODE_MONO_SAP)
        {
            printf("\r\n Mono Sap to Mono");
            eDetectedAudioMode=E_AUDIOMODE_FORCED_MONO;
        }
        else if(eDetectedAudioMode==E_AUDIOMODE_STEREO_SAP)
        {
            printf("\r\n Stereo Sap  to Stereo");
            eDetectedAudioMode=E_AUDIOMODE_K_STEREO;
        }
        else if(m_eAudioMode==E_AUDIOMODE_FORCED_MONO&&eDetectedAudioMode==E_AUDIOMODE_STEREO_SAP)
        {
            printf("\r\n Force Mono to Stereo");
            eDetectedAudioMode=E_AUDIOMODE_K_STEREO;
        }
        bForceCheckAudioMode=FALSE;
    }
    else
    {
        if((m_eAudioMode == E_AUDIOMODE_FORCED_MONO||m_eAudioMode == E_AUDIOMODE_K_STEREO||m_eAudioMode == E_AUDIOMODE_STEREO_SAP||m_eAudioMode==E_AUDIOMODE_MONO)&&
      (eDetectedAudioMode == E_AUDIOMODE_FORCED_MONO||eDetectedAudioMode == E_AUDIOMODE_K_STEREO||eDetectedAudioMode == E_AUDIOMODE_STEREO_SAP||eDetectedAudioMode == E_AUDIOMODE_MONO_SAP))
        {
            return;
        }
    }
  #endif

    if( ((m_eAudioMode == E_AUDIOMODE_NICAM_DUAL_A) || (m_eAudioMode == E_AUDIOMODE_NICAM_DUAL_B) || (m_eAudioMode == E_AUDIOMODE_NICAM_DUAL_AB)) &&
        ((eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_A) || (eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_B) || (eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_AB)) )
    {
        return;
    }

  #if 0
    if( m_eAudioMode == E_AUDIOMODE_FORCED_MONO && eDetectedAudioMode != E_AUDIOMODE_DUAL_A )
    {
        return;
    }
  #endif

  #if 0
    if( (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) || (eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_A) )
    {
        printf("msAPI_ATV_WasForeignLanguageSelected=%bd\n",msAPI_ATV_WasForeignLanguageSelected());

        if( TRUE == msAPI_ATV_WasForeignLanguageSelected() )
        {
            printf("eDetectedAudioMode2=%bd,%bd\n",eDetectedAudioMode,E_AUDIOMODE_DUAL_A);

            eDetectedAudioMode = (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) ? E_AUDIOMODE_DUAL_B : E_AUDIOMODE_NICAM_DUAL_B;
        }
    }
  #endif

    if( (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) || (eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_A) )
    {
        eSaveAudioMode = (EN_DUAL_AUDIO_SELECTION)msAPI_ATV_GetDualAudioSelected();
        if(eSaveAudioMode == E_DUAL_AUDIO_A)
        {
            eDetectedAudioMode = (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) ? E_AUDIOMODE_DUAL_A : E_AUDIOMODE_NICAM_DUAL_A;
        }
        else if(eSaveAudioMode == E_DUAL_AUDIO_B)
        {
            eDetectedAudioMode = (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) ? E_AUDIOMODE_DUAL_B : E_AUDIOMODE_NICAM_DUAL_B;
        }
        else //E_DUAL_AUDIO_AB
        {
            eDetectedAudioMode = (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) ? E_AUDIOMODE_DUAL_AB : E_AUDIOMODE_NICAM_DUAL_AB;
        }
    }

  #ifndef ATSC_SYSTEM//ATSC_FIX_C
    if( TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
    {
        msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, eDetectedAudioMode);
    }
  #endif

    if(m_eAudioMode==eDetectedAudioMode)
        return ;

    m_eAudioMode = eDetectedAudioMode;

    m_bIsAudioModeChanged = TRUE;

    SetAudioMute(E_AUDIO_INTERNAL_1_MUTEON,E_AUDIOMUTESOURCE_ATV);

    msAPI_Timer_Delayms_2(DELAY_FOR_ENTERING_MUTE, E_DELAY_ID_AUDIO_API_SOUND_MODE);

    MApi_AUDIO_SIF_SetSoundMode(m_eAudioMode);

    msAPI_Timer_Delayms_2(DELAY_FOR_LEAVING_MUTE, E_DELAY_ID_AUDIO_API_SOUND_MODE);

    SetAudioMute(E_AUDIO_INTERNAL_1_MUTEOFF,E_AUDIOMUTESOURCE_ATV);

}

void CheckAudioMode_SoundMode_BTSC(void)
{
    AUDIOSTATUS eCurrentAudioStatus;

    BYTE ucValue;
    static BYTE PreucVaue;

    m_eAudioStandard = E_AUDIOSTANDARD_M_BTSC;

    CheckATVAudioMode_BTSC(); //just for remove make warning

    ucValue = MApi_AUDIO_SIF_GetSoundMode();
    if(PreucVaue != ucValue)
    {
        PreucVaue = ucValue;
        printf("GetSoundMode=%d\n",ucValue);
        return;
    }

    eCurrentAudioStatus = E_STATE_AUDIO_NO_CARRIER;

    if(ucValue & 0x01)
        eCurrentAudioStatus |= E_STATE_AUDIO_PRIMARY_CARRIER;
    if(ucValue & 0x02)
        eCurrentAudioStatus |= E_STATE_AUDIO_STEREO;
    if(ucValue & 0x04)
        eCurrentAudioStatus |= E_STATE_AUDIO_BILINGUAL;

    if( m_eAudioStatus != eCurrentAudioStatus )
    {
        m_eAudioStatus = eCurrentAudioStatus;
    }

}
#endif

#if ( ENABLE_AUDIO_SYS_A2)
static void CheckATVAudioMode_A2_OtherSource(void)
{
    AUDIOMODE_TYPE eDetectedAudioMode, m_eAudioMode_ATV;
    EN_DUAL_AUDIO_SELECTION eSaveAudioMode;


    msAPI_ATV_GetAudioMode(E_AUDIOSOURCE_ATV, &m_eAudioMode_ATV);

    if( TRUE == MApi_AUDIO_SIF_IsPALType(AU_SIF_PAL_MONO) )
    {
        eDetectedAudioMode = E_AUDIOMODE_MONO;
    }
    else
    {
        eDetectedAudioMode = (AUDIOMODE_TYPE)MApi_AUDIO_SIF_GetSoundMode();
    }

    if( eDetectedAudioMode == E_AUDIOMODE_INVALID )
        return;

    if( m_eAudioMode_ATV == eDetectedAudioMode )
    {
        MApi_AUDIO_SIF_SetSoundMode(m_eAudioMode_ATV);
        return;
    }

    if( ((m_eAudioMode_ATV == E_AUDIOMODE_DUAL_A) || (m_eAudioMode_ATV == E_AUDIOMODE_DUAL_B) || (m_eAudioMode_ATV == E_AUDIOMODE_DUAL_AB)) &&
        ((eDetectedAudioMode == E_AUDIOMODE_DUAL_A) || (eDetectedAudioMode == E_AUDIOMODE_DUAL_B) || (eDetectedAudioMode == E_AUDIOMODE_DUAL_AB)) )
    {
        MApi_AUDIO_SIF_SetSoundMode(m_eAudioMode_ATV);
        return;
    }

    if( ((m_eAudioMode_ATV == E_AUDIOMODE_NICAM_DUAL_A) || (m_eAudioMode_ATV == E_AUDIOMODE_NICAM_DUAL_B) || (m_eAudioMode_ATV == E_AUDIOMODE_NICAM_DUAL_AB)) &&
        ((eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_A) || (eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_B) || (eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_AB)) )
    {
        MApi_AUDIO_SIF_SetSoundMode(m_eAudioMode_ATV);
        return;
    }

    if( m_eAudioMode_ATV == E_AUDIOMODE_FORCED_MONO && eDetectedAudioMode != E_AUDIOMODE_DUAL_A )
    {
        MApi_AUDIO_SIF_SetSoundMode(m_eAudioMode_ATV);
        return;
    }

    if( (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) || (eDetectedAudioMode == E_AUDIOMODE_NICAM_DUAL_A) )
    {
        eSaveAudioMode = (EN_DUAL_AUDIO_SELECTION)msAPI_ATV_GetDualAudioSelected();
        if(eSaveAudioMode == E_DUAL_AUDIO_A)
        {
            eDetectedAudioMode = (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) ? E_AUDIOMODE_DUAL_A : E_AUDIOMODE_NICAM_DUAL_A;
        }
        else if(eSaveAudioMode == E_DUAL_AUDIO_B)
        {
            eDetectedAudioMode = (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) ? E_AUDIOMODE_DUAL_B : E_AUDIOMODE_NICAM_DUAL_B;
        }
        else //E_DUAL_AUDIO_AB
        {
            eDetectedAudioMode = (eDetectedAudioMode == E_AUDIOMODE_DUAL_A) ? E_AUDIOMODE_DUAL_AB : E_AUDIOMODE_NICAM_DUAL_AB;
        }
    }

    //if( TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
    //{
    //    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, eDetectedAudioMode);
    //}

    m_eAudioMode_ATV = eDetectedAudioMode;

    m_bIsAudioModeChanged = TRUE;

    MApi_AUDIO_SIF_SetSoundMode(m_eAudioMode_ATV);
}

//for CheckAudioStandard in other source except DTV and ATV.
static void CheckAudioStandard_A2_ForOtherSource(void)
{
    AUDIOSTATUS eCurrentAudioStatus;

    MS_BOOL AudioStatusIsA2 = FALSE;
    MS_U8 max_a2_mode_invalid_cnt = 0x20;


    if( m_eAudioSource == E_AUDIOSOURCE_ATV )
        return;


        if( TRUE != MApi_AUDIO_SIF_GetAudioStatus(&eCurrentAudioStatus) )
            return;

        CheckATVAudioMode_A2_OtherSource(); //just for remove make warning

        if( m_eAudioStatus != eCurrentAudioStatus )
        {
            m_eAudioStatus = eCurrentAudioStatus;
            msAPI_Timer_Delayms(5);

            if( TRUE != MApi_AUDIO_SIF_GetAudioStatus(&eCurrentAudioStatus) )
                return;

            if( m_eAudioStatus != eCurrentAudioStatus )     //Check twice for speed up detection, C.P.Chen 2007/12/06
            {
                m_eAudioStatus = eCurrentAudioStatus;
                return;
            }
        }

        if (g_A2ModeInvalidCnt >= max_a2_mode_invalid_cnt)
        {
            if( ((m_eAudioStatus & (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_PILOT)) == (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_PILOT))
               && ((m_eAudioStatus & E_STATE_AUDIO_STEREO) || (m_eAudioStatus & E_STATE_AUDIO_BILINGUAL)))
                AudioStatusIsA2 = TRUE;
        }
        else
        {
            if( (m_eAudioStatus & (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_PILOT)) == (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_PILOT) )
                AudioStatusIsA2 = TRUE;
        }

    #if 1//(TV_SYSTEM == TV_PAL)

        if( m_eAudioStandard == E_AUDIOSTANDARD_L)    // need touch.
        {
            if( ((m_eAudioStatus & (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_NICAM)) == (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_NICAM)) ||
                ((m_eAudioStatus & E_STATE_AUDIO_PRIMARY_CARRIER) == E_STATE_AUDIO_PRIMARY_CARRIER) )
            {
                CheckATVAudioMode_A2_OtherSource();
            }
            return;
        }

        if( (m_eAudioStatus & (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_NICAM)) == (E_STATE_AUDIO_PRIMARY_CARRIER|E_STATE_AUDIO_NICAM) )
        {
            g_A2ModeInvalidCnt = 0;
        #if (MTS_NICAM_UNSTABLE)
            if(g_NICAMEnable == 0)
            {
                return;
            }
        #endif

            if( FALSE == MApi_AUDIO_SIF_IsPALType(AU_SIF_PAL_NICAM) )
            {
                switch(m_eAudioStandard)
                {
                    case E_AUDIOSTANDARD_BG:
                    case E_AUDIOSTANDARD_BG_A2:
                        m_eAudioStandard = E_AUDIOSTANDARD_BG_NICAM;
                        break;
                    case E_AUDIOSTANDARD_DK:
                    case E_AUDIOSTANDARD_DK1_A2:
                        m_eAudioStandard = E_AUDIOSTANDARD_DK_NICAM;
                        break;
                    default:
                        break;
                }
                //SetAudioMuteDuringLimitedTime(500, E_AUDIOMUTESOURCE_ACTIVESOURCE); //C.P.Chen 2007/12/06
                MApi_AUDIO_SIF_SetPALType(AU_SIF_PAL_NICAM);
                MApi_AUDIO_SIF_SetStandard(m_eAudioStandard);
                DEBUG_CHECK_AUD_STD(printf("Aud_set_std(0x%X)\n", m_eAudioStandard););

                // We do not want to change audio standard of eeprom when one channel search is running or manual change.
                //if( TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
                //{
                //    PRINT_CURRENT_LINE();
                //    msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), m_eAudioStandard);
                //}

                //m_wAtvAudioCheckCount = (5);
                return;
            }

            CheckATVAudioMode_A2_OtherSource();
        }
        else if(AudioStatusIsA2 == TRUE)
        {   //Reload A2 while Pilot detected. C.P.Chen
            if( FALSE == MApi_AUDIO_SIF_IsPALType(AU_SIF_PAL_A2) )
            {
                if((m_eAudioStatus&E_STATE_AUDIO_DK2) == E_STATE_AUDIO_DK2)
                    m_eAudioStandard = E_AUDIOSTANDARD_DK2_A2;
                else if((m_eAudioStatus&E_STATE_AUDIO_DK3) == E_STATE_AUDIO_DK3)
                    m_eAudioStandard = E_AUDIOSTANDARD_DK3_A2;

                MApi_AUDIO_SIF_SetStandard(m_eAudioStandard);
                //SetAudioMuteDuringLimitedTime(800, E_AUDIOMUTESOURCE_ACTIVESOURCE);  //C.P.Chen 2007/12/06
                g_A2ModeInvalidCnt = 0;
                MApi_AUDIO_SIF_SetPALType(AU_SIF_PAL_A2);

                // We do not want to change audio standard of eeprom when one channel search is running or manual change.
                //if( TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
                //{
                //    PRINT_CURRENT_LINE();
                //    msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), m_eAudioStandard);
                //}

                //m_wAtvAudioCheckCount = (5);
                return;
            }
            else if((m_eAudioStatus & (E_STATE_AUDIO_STEREO|E_STATE_AUDIO_BILINGUAL)) == 0 )
            {
                g_A2ModeInvalidCnt++;
            }
            else // STEREO or DUAL exist
            {
                g_A2ModeInvalidCnt = 0;
            }

            CheckATVAudioMode_A2_OtherSource();
        }
        else if( (m_eAudioStatus & E_STATE_AUDIO_PRIMARY_CARRIER) == E_STATE_AUDIO_PRIMARY_CARRIER )
        {
            CheckATVAudioMode_A2_OtherSource();

            msAPI_Tuner_UpdateMediumAndChannelNumber();

        #if (MTS_NICAM_UNSTABLE)
            if( TRUE == MApi_AUDIO_SIF_IsPALType(AU_SIF_PAL_NICAM) )
            {
                if (g_CarrierStableCnt <= 30)
                {
                    g_CarrierStableCnt++;
                    return;
                }
                g_CarrierStableCnt = 0;
                g_NICAMEnable = 0;
            }
        #endif

            switch(m_eAudioStandard)
            {
                case E_AUDIOSTANDARD_BG_NICAM:
                    MApi_AUDIO_SIF_SetStandard(E_AUDIOSTANDARD_BG_A2);
                    m_eAudioStandard = E_AUDIOSTANDARD_BG_A2;
                    break;
                case E_AUDIOSTANDARD_DK_NICAM:
                    MApi_AUDIO_SIF_SetStandard(E_AUDIOSTANDARD_DK1_A2);
                    m_eAudioStandard = E_AUDIOSTANDARD_DK1_A2;
                    break;
                default:
                    break;
            }

            if( FALSE == MApi_AUDIO_SIF_IsPALType(AU_SIF_PAL_MONO) )
            {
                //SetAudioMuteDuringLimitedTime(100, E_AUDIOMUTESOURCE_ACTIVESOURCE); //C.P.Chen 2007/12/06
                MApi_AUDIO_SIF_SetPALType(AU_SIF_PAL_MONO);

                // We do not want to change audio standard of eeprom when one channel search is running or manual change.
                //if( TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
                //{
                //    PRINT_CURRENT_LINE();
                //    msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), MApi_AUDIO_SIF_ConvertToBasicAudioStandard(m_eAudioStandard));
                //}
            }
        }
        else
        {
        }
    #endif // #if (TV_SYSTEM == TV_PAL)

}
#endif


#if( ENABLE_ATV_AUDIOCHECK_IN_OTHER_SRC )

//for CheckAudioStandard in other source except DTV and ATV.
static void CheckAudioStandard_OtherSource(void)
{
    if( m_eAudioSource == E_AUDIOSOURCE_ATV )
        return;

#if( ENABLE_AUDIO_SYS_BTSC )
    if( msAPI_AUD_Is_AudSystemBTSC() )
    {
        CheckAudioMode_SoundMode_BTSC();
    }
    else
#endif
    {
    #if( ENABLE_AUDIO_SYS_A2 )
        CheckAudioStandard_A2_ForOtherSource();
    #endif
    }
}

#if 0
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MW_ATV_AudioProcessor()
/// @brief \b Function \b Description: Audio Process when source is not TV.
/// @param <IN>        \b NONE    :
/// @param <OUT>       \b NONE    :
/// @param <RET>       \b  NONE    :
/// @param <GLOBAL>    \b NONE    :
////////////////////////////////////////////////////////////////////////////////
void Mapi_ATV_AudioProcessor(void)
{
    if( m_eAudioSource <= E_AUDIOSOURCE_ATV ||
        m_eAudioSource >= E_AUDIOSOURCE_INVALID)
    {
//        printf("return from Mapi_ATV_AudioProcessor\n");
        return;
    }
//    printf("into Mapi_ATV_AudioProcessor\n");
    if(m_wAtvAudioCheckCount > 0)
    {
        m_wAtvAudioCheckCount--;
        return;
    }

    m_wAtvAudioCheckCount = 5;

//    if( IsVDHasSignal()==TRUE )
    {
    #if(ENABLE_AUDIO_AUTO_DETECT)
        CheckAudioStandard_OtherSource();
    #endif//(ENABLE_AUDIO_AUTO_DETECT)
    }
}
#endif
#endif

void msAPI_Audio_Standard_and_SoundMode_Task(void)
{
    static U32 _s_u32SoundMode_Task_LastTime = 0;

    if( msAPI_Timer_DiffTime_2( _s_u32SoundMode_Task_LastTime, MsOS_GetSystemTime() ) < 10 )
    {
        return;
    }

    _s_u32SoundMode_Task_LastTime = MsOS_GetSystemTime();


    //printf("m_eAudioSource=%d\n", m_eAudioSource);

    if( m_eAudioSource >= E_AUDIOSOURCE_INVALID )
    {
        return;
    }

    // When main source is ATV,
    if( (m_eAudioSource == E_AUDIOSOURCE_ATV)
        //IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
      /*||IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) */
      )
    {
        //printf("Src is ATV\n");

        if( MApp_Is_InAutoScan_ATV() ) // In AutoScan
        {
            return;
        }

        if( MApp_IsSrcHasSignal(MAIN_WINDOW)
          //&&( m_bBySyncAudioMute == FALSE)
           )
        {
            //printf("Check AUD Std&Mode\n");
            // todo: CheckAudioStandard() to here

        #if 0//(ENABLE_AUDIO_AUTO_DETECT)
          #if( ENABLE_AUDIO_SYS_BTSC )
            if( msAPI_AUD_Is_AudSystemBTSC() )
            {
                CheckAudioMode_SoundMode_BTSC();
            }
            else
          #endif
            {
            #if( ENABLE_AUDIO_SYS_A2 )
                CheckAudioStandard_A2();
            #endif
            }
        #endif
        }

    }
    else if( E_VIF_ON_ATV_CVBSOUT == MApp_InputSource_GetVifWorkingStatus() ) // When cvbs out is ATV
    {
        //printf("CVBS out ATV\n");

    #if( ENABLE_ATV_AUDIOCHECK_IN_OTHER_SRC )
        /*if( m_eAudioSource <= E_AUDIOSOURCE_ATV )
        {
            return;
        } */

        //Mapi_ATV_AudioProcessor();

      #if(ENABLE_AUDIO_AUTO_DETECT)
        CheckAudioStandard_OtherSource();
      #endif//(ENABLE_AUDIO_AUTO_DETECT)

    #endif
    }
}


