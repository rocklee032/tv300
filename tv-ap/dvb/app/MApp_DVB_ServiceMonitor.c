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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//////////////////////////////////////////////////////////////////////////////////

#include "Board.h"

#if(ENABLE_DVB)

#include <string.h>

#include "msAPI_Timer.h"
#include "msAPI_DTVSystem.h"

#include "mapp_demux.h"
#include "mapp_si.h"
#include "mapp_si_util.h"

#include "MApp_SDT_Monitor.h"

#include "MApp_Audio.h"
#include "MApp_ChannelChange.h"
#include "MApp_MVDMode.h"

#include "MApp_ParentalRating.h"
#include "MApp_BlockSys.h"

#if ENABLE_CI
#include "MApp_CIMMI.h"
#include "msAPI_CI.h"
#endif
#if(ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#include "MApp_TV.h"

#include "MApp_UI_EventHandler.h"


//=============================================================================
extern BOOLEAN g_bMheg5Existed;

#if ENABLE_EWBS
extern BOOLEAN _MApp_EWBS_Check(E_SERVICE_CHANGE eChangeType);
static BOOLEAN _bEwbsInfoEnable;
#endif

#if ENABLE_FileInMonitor
BOOLEAN _RecordUpdateAllPIDs = FALSE;
#endif

#if(ENABLE_DVB)
#if ENABLE_CI_PLUS && MEDIASET_PREMIUM_SMART_CAM
BOOL g_bIsServiceVideoChange = FALSE;
BOOL g_bIsVideoPidChanged = FALSE;
#endif
#endif

//-----------------------------------------------------------------------------------------

typedef struct   //Same Service ID
{
    U8  u8bStillPic :1;
    U8  u8fMHEG5    :1;
    U8  u8IsCAExist :1;
    U8  eVideoType  :3;
    U8  u8Reserved  :2;
    U16 wPmtPid;
    U16 wVideo_PID;
    U16 wPCRPid;
    U8  u8AudStreamNum;
    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];
} MS_CUR_SERVICE_INFO;

//-----------------------------------------------------------------------------------------

//void _MApp_Service_Check( void )
void MApp_DVB_ServiceMonitor( void )
{
    MS_SI_CUR_SERVICE_INFO stSIServiceInfo;
    E_SERVICE_CHANGE eChangeType;
    eChangeType = E_SERVICE_INVALUE;
#if ENABLE_CI_PLUS && MEDIASET_PREMIUM_SMART_CAM
    static U32 _u32TimerVidPidChg = 0;
    static U32 _u32TimerRestartChnCh = 0;

    if(_u32TimerRestartChnCh)
    {
        if(msAPI_Timer_DiffTimeFromNow(_u32TimerRestartChnCh) > 3000)
        {
            _u32TimerRestartChnCh = 0;
        }
    }
    if(_u32TimerVidPidChg)
    {
        if(msAPI_Timer_DiffTimeFromNow(_u32TimerVidPidChg) > 10000)
        {
            MApi_VDEC_SetControl(VDEC_USER_CMD_DROP_ERR_FRAME, 0);

            MApp_AVCH264_BypasSeqChgCheck(FALSE);

            _u32TimerVidPidChg = 0;
        }
    }
#endif

    if (MApp_SI_Is_Service_Change(&stSIServiceInfo,&eChangeType)
#if ENABLE_SDT_OTHER_MONITOR
        ||(g_SDT_u32CheckMovServieTimer && MApp_SI_IsSdtOtherCome())
#endif
#ifdef ENABLE_DELETE_PROGRAM_CONTROL
        || msAPI_CM_GetRemoveProgram(&eChangeType)
#endif
        )
    {
        BOOLEAN bNeedRestartChnChange = FALSE;
        //BOOLEAN bGotSameAudio=FALSE;
        BOOLEAN bNeedUpdateAudInfo = FALSE, bTrueFalse;
        MEMBER_SERVICETYPE bServiceType;
        WORD wCurrentPosition, wCurServiceID;
        WORD wVideo_PID = 0, wPCR_PID = 0;
        U8 i, j, AudioNum;
        BYTE bSelectedAudStream = 0xFF;
        AUD_INFO aAudioStreamInfo;
        AUD_INFO NewstAudioStreamInfo,OldstAudioStreamInfo;
        U8 u8PreLRAudioMode = MApp_Audio_Get_LRMode();//g_u8LRAudioMode;
        BOOLEAN bGetSameAudioPidAsDB;

        if (E_SERVICE_REMOVED == eChangeType)
        {
            if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
            #if ENABLE_SDT_OTHER_MONITOR
                MEMBER_SERVICETYPE bServiceTypeTmp = E_SERVICETYPE_DTV;
                WORD wSIDTmp = 0;
                WORD wLCNTmp = 0;

                MApp_SDT_Get_UserService(&bServiceTypeTmp, &wSIDTmp, &wLCNTmp);

                MApp_Dmx_Disable_Reset_Filter();

                //gu8VerChange = TRUE;
                MApp_UI_NotifySysEvent(E_SYS_EVENT_DTV_SERVICE_VER_CHANGE, 0);

                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);

                //g_SDT_eUserServiceType=bServiceTypeTmp;
                //g_SDT_u16UserSID= wSIDTmp;
                //g_SDT_u16UserLCN= wLCNTmp;
                MApp_SDT_Set_UserService(bServiceTypeTmp, wSIDTmp, wLCNTmp);

            #else
            #if(ENABLE_S2)
                if (Dvbs2_Default_Scan == 1)
                {
                    Dvbs2_Default_Scan = 0;
                }
                else
            #endif
                {
                    //gu8VerChange = TRUE;
                    MApp_UI_NotifySysEvent(E_SYS_EVENT_DTV_SERVICE_VER_CHANGE, 0);

                    MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
            #endif

            }

          #if (ENABLE_PIP)
            if (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                {
                    MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                    MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                }
            }
          #endif

        }
      #if ENABLE_SDT_OTHER_MONITOR
        else if ((E_SERVICE_MOVE == eChangeType)||(g_SDT_u32CheckMovServieTimer && MApp_SI_IsSdtOtherCome()))
        {
            MOVE_SERVICE_IDS stMoveSrv;
            MEMBER_SERVICETYPE eGotServiceType;
            WORD u16GotPosition;
            if(g_SDT_u32CheckMovServieTimer && msAPI_SI_Timer_DiffTime(msAPI_SI_Timer_GetTime(), g_SDT_u32CheckMovServieTimer) > CHANGE_TO_MOVE_SERVICE_TIMEOUT)
            {
                MApp_SI_ResetSdtOtherComeFlag();
                g_SDT_u32CheckMovServieTimer = 0;
            }
            else
            {
                MApp_SI_Get_MoveServiceIDS(&stMoveSrv);
                if (TRUE == msAPI_CM_GetServiceTypeAndPositionWithIDs(stMoveSrv.wTSID, stMoveSrv.wONID, stMoveSrv.wSID, 1, &eGotServiceType, &u16GotPosition, TRUE))
                {
                    if(MApp_ChannelChange_ChangeSpeciChannel(stMoveSrv.wSID, stMoveSrv.wONID, stMoveSrv.wTSID, TYPE_CHANNEL_CHANGE_SER_ID, TRUE, TRUE))
                    {
                    //printf("ChannelChange_ChangeSpeciChannel \n");
                    }
                }
                else if(g_SDT_u32CheckMovServieTimer == 0 && MApp_SI_IsSdtOtherCome()==FALSE)
                {
                    g_SDT_u32CheckMovServieTimer = msAPI_SI_Timer_GetTime();
                }
                if(MApp_SI_IsSdtOtherCome()==TRUE)
                {
                    MApp_SI_ResetSdtOtherComeFlag();
                    if(g_SDT_u32CheckMovServieTimer)
                        g_SDT_u32CheckMovServieTimer = 0;
                }
            }
        }
      #endif
        else
        {
            MS_CUR_SERVICE_INFO stServiceInfo;
            BOOLEAN bSaveAudio=MApp_SI_Is_Save_Audio();//20090806
            stServiceInfo.eVideoType = msAPI_SI_ToCM_Video_Type(stSIServiceInfo.eVideoType);
            stServiceInfo.u8bStillPic = stSIServiceInfo.u8bStillPic;
            stServiceInfo.u8fMHEG5 = stSIServiceInfo.u8fMHEG5;
            stServiceInfo.u8IsCAExist = stSIServiceInfo.u8IsCAExist;
            stServiceInfo.wPmtPid = stSIServiceInfo.wPmtPid;
            stServiceInfo.wVideo_PID = stSIServiceInfo.wVideo_PID;
            stServiceInfo.wPCRPid = stSIServiceInfo.wPCRPid;
            stServiceInfo.u8AudStreamNum = stSIServiceInfo.u8AudStreamNum;

            if(stServiceInfo.u8fMHEG5)
            {
                g_bMheg5Existed = TRUE;
            }
            else
            {
                g_bMheg5Existed = FALSE;
            }


            int maxAudio = MAX_AUD_LANG_NUM > SI_MAX_AUD_LANG_NUM ? SI_MAX_AUD_LANG_NUM : MAX_AUD_LANG_NUM;
        #if 1 // Use new API
            msAPI_SI_Copy_SI_AudInfo_To_CM_AudInfo(stSIServiceInfo.stAudInfo, stServiceInfo.stAudInfo, maxAudio);

        #else

            int maxISO = MAX_AUD_ISOLANG_NUM > SI_MAX_AUD_ISOLANG_NUM ? SI_MAX_AUD_ISOLANG_NUM : MAX_AUD_ISOLANG_NUM;

            for (i = 0; i < maxAudio; i++)
            {
                //stServiceInfo.stAudInfo[i].wAudType=msAPI_SI_ToCM_Audio_Type(stSIServiceInfo.stAudInfo[i].wAudType);
                stServiceInfo.stAudInfo[i].eSIAudType = (SI_AUDIOSTREAM_TYPE)stSIServiceInfo.stAudInfo[i].wAudType;
                stServiceInfo.stAudInfo[i].wAudPID=stSIServiceInfo.stAudInfo[i].wAudPID;

                //stServiceInfo.stAudInfo[i].u8ProfileAndLevel=stSIServiceInfo.stAudInfo[i].u8ProfileAndLevel;
                stServiceInfo.stAudInfo[i].eProfileAndLevel = msAPI_SI_ToCM_ProfileAndLevel(stSIServiceInfo.stAudInfo[i].u8ProfileAndLevel);

                //stServiceInfo.stAudInfo[i].u8Component_AAC_Type=stSIServiceInfo.stAudInfo[i].u8Component_AAC_Type;

                for (j = 0; j < maxISO; j++)
                {
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLangIndex = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLangIndex;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo = msAPI_SI_ToCM_Audio_Mode(stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo);
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bAudType = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bAudType;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bIsValid = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bIsValid;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bReserved = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bReserved;
                }
            }
        #endif

            bServiceType = msAPI_CM_GetCurrentServiceType();
            wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
            wVideo_PID = msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition);
            wCurServiceID = msAPI_CM_GetService_ID(bServiceType, wCurrentPosition);

            //Note: Don't need to take care about TTX and Subtitle.
            //      These modules will do the updat by themselves in data gathering stage.
            if (stServiceInfo.u8IsCAExist != msAPI_CM_GetProgramAttribute(bServiceType, wCurrentPosition, E_ATTRIBUTE_IS_SCRAMBLED))
            {
                msAPI_CM_ScrambleProgram(bServiceType,wCurrentPosition,stServiceInfo.u8IsCAExist);
                //bNeedRestartChnChange = TRUE; //**-- Italy CI Certificate --**//
                //bReturn  = TRUE;
            }
            if (stServiceInfo.u8bStillPic != msAPI_CM_GetProgramAttribute(bServiceType, wCurrentPosition, E_ATTRIBUTE_IS_STILL_PICTURE))
            {
                bTrueFalse = stServiceInfo.u8bStillPic;
                // To do. msAPI_CM_UpdateProgram() does not support this yet.
                //if(E_RESULT_SUCCESS == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, &bTrueFalse, E_ATTRIBUTE_IS_STILL_PICTURE))
                //{
                //}
            }
            if (msAPI_CM_GetProgramAttribute(bServiceType, wCurrentPosition, E_ATTRIBUTE_IS_SERVICE_ID_ONLY) == TRUE)
            {
                msAPI_CM_ServiceIDOnlyProgram(bServiceType, wCurrentPosition, FALSE);
            }

            if (stServiceInfo.eVideoType != (U8)msAPI_CM_GetProgramVideoType(bServiceType, wCurrentPosition))
            {
                msAPI_CM_SetProgramVideoType(bServiceType,wCurrentPosition,stServiceInfo.eVideoType);
                bNeedRestartChnChange = TRUE;
            }
            if (stServiceInfo.wPmtPid != msAPI_CM_GetPmtPID(bServiceType,wCurrentPosition))
            {
                //printf("Service (%u) Change Pmt PID, old(%u):new(%u)\n",wCurServiceID,msAPI_CM_GetPmtPID(bServiceType,wCurrentPosition),stServiceInfo.wPmtPid);
                if(TRUE == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)&stServiceInfo.wPmtPid, E_DATA_PMT_PID))
                {
                  #if ENABLE_FileInMonitor
                    _RecordUpdateAllPIDs = TRUE;
                  #endif
                    //bNeedRestartChnChange = TRUE;
                }
            }
            if (stServiceInfo.wVideo_PID != msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition))
            {
                //printf("Service (%u) Change Vid PID, old(%u):new(%u)\n",wCurServiceID,msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition),stServiceInfo.wVideo_PID);
                if(TRUE == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)&stServiceInfo.wVideo_PID, E_DATA_VIDEO_PID))
                {
                  #if ENABLE_FileInMonitor
                    _RecordUpdateAllPIDs = TRUE;
                  #endif

#if ENABLE_CI_PLUS && MEDIASET_PREMIUM_SMART_CAM
                    if(bNeedRestartChnChange)
                    {
                        _u32TimerRestartChnCh = msAPI_Timer_GetTime0();
                    }
                    if(!_u32TimerRestartChnCh && msAPI_CI_CardDetect() && (msAPI_Demod_Get_CurTSPathCase() == E_DEMOD_TSP_PATH_CASE_CI_IN_USE))
                    {
                        MApi_VDEC_SetControl(VDEC_USER_CMD_DROP_ERR_FRAME, 1);

                        msAPI_DMX_StartFilter(stServiceInfo.wVideo_PID, MSAPI_DMX_FILTER_TYPE_VIDEO, MApp_Dmx_GetFid(EN_VIDEO_FID));

                        _u32TimerVidPidChg = msAPI_Timer_GetTime0();

                        g_bIsVideoPidChanged = TRUE;

                        MApp_AVCH264_BypasSeqChgCheck(TRUE);
                    }
                    else
#endif
                    {
                        bNeedRestartChnChange = TRUE;
                    }
                }
            }
            if (stServiceInfo.wPCRPid != msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition))
            {
                //printf("Service (%u) Change PCR PID, old(%u):new(%u)\n",wCurServiceID,msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition),stServiceInfo.wPCRPid);
                if(TRUE == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)&stServiceInfo.wPCRPid, E_DATA_PCR_PID))
                {
                  #if ENABLE_FileInMonitor
                    _RecordUpdateAllPIDs = TRUE;
                  #endif
                }
            }
            msAPI_DMX_Pid(*MApp_Dmx_GetFid(EN_PCR_FID),&wPCR_PID,FALSE);
            if (stServiceInfo.wPCRPid != wPCR_PID)
            {
                DMX_FILTER_STATUS eDMXFLTSTA;
                msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_PCR_FID) );
                eDMXFLTSTA = msAPI_DMX_StartFilter( stServiceInfo.wPCRPid, MSAPI_DMX_FILTER_TYPE_PCR, MApp_Dmx_GetFid(EN_PCR_FID) );
            }
#if ENABLE_STOFA
            if(OSD_COUNTRY_SETTING == OSD_COUNTRY_DENMARK)
            {
                if(MApi_AUDIO_GetAC3Info(Audio_AC3_infoType_Acmod) == AUD_CH_MODE_DUAL_MONO)
                {
                    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
                    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
                }
            }
#endif
            /* Check Audio*/
            /* Get current audio count */
            AudioNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
            /* Get all the audio infor */
            if (AudioNum != stServiceInfo.u8AudStreamNum)
            {
                //printf("PMT content change: audio number change, old(%bu), new(%bu)\n",AudioNum,pPmtInfo->u8AudStreamNum);
                bNeedUpdateAudInfo = TRUE;
            }
            else
            {
                /* Get current selected audio index */
                bSelectedAudStream = g_u8AudLangSelected;//msAPI_CM_GetSelectedAudioStream(bServiceType, wCurrentPosition);
                for(i = 0; i< AudioNum; i++)
                {
                    bGetSameAudioPidAsDB = FALSE;
                    /* Get all audio information */
                    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);

                    /* check audio info change or not */
                    for(j = 0; j < stServiceInfo.u8AudStreamNum; j++)
                    {
                        if (stServiceInfo.stAudInfo[j].wAudPID == aAudioStreamInfo.wAudPID)
                        {
                            bGetSameAudioPidAsDB = TRUE;
                            //if (stServiceInfo.stAudInfo[j].wAudType == aAudioStreamInfo.wAudType)
                            if (stServiceInfo.stAudInfo[j].eSIAudType == aAudioStreamInfo.eSIAudType)
                            {
                                if (!memcmp(stServiceInfo.stAudInfo[j].aISOLangInfo, aAudioStreamInfo.aISOLangInfo,sizeof(LANG_ISO639)*MAX_AUD_ISOLANG_NUM))
                                {
                                    break;
                                }
                                else
                                {
                                    bNeedUpdateAudInfo = TRUE;
                                    break;
                                }
                            }
                            else
                            {
                                if (bSelectedAudStream == i)
                                {
                                    //bNeedRestartChnChange = TRUE;
                                }
                                bNeedUpdateAudInfo = TRUE;
                                break;
                            }
                        }
                    }
                    if(bGetSameAudioPidAsDB == FALSE)
                    {
                        bNeedUpdateAudInfo = TRUE;
                        if(bSelectedAudStream == i)
                        {
                            //bNeedRestartChnChange = TRUE;
                            break;
                        }
                    }
                }
            }

            if (bNeedUpdateAudInfo == TRUE)
            {
                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &OldstAudioStreamInfo, g_u8AudLangSelected);
                msAPI_CM_EnableStoreDataToFlash(bSaveAudio);//20090806
                #if ENABLE_FileInMonitor
                _RecordUpdateAllPIDs = TRUE;
                #endif
                if (TRUE != msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)stServiceInfo.stAudInfo, E_DATA_AUDIO_STREAM_INFO))
                {
                    //printf("Update Aud info fail\n");
                }
                msAPI_CM_EnableStoreDataToFlash(TRUE);//20090806

                //NZ freview spec, got prefer language should change audio
                if( (bNeedRestartChnChange == FALSE)
                  &&(bSelectedAudStream!=0xFF)
                  &&(stGenSetting.g_SoundSetting.enSoundAudioLan1 != OldstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex) /*&& (stGenSetting.g_SoundSetting.enSoundAudioLan2 != OldstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex)*/
                  )
                {
                    U8 temp=g_u8AudLangSelected;
                #if (ENABLE_CI_PLUS)
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        MApp_ChannelChange_SearchDefaultOPAudioLang();
                    }
                    else
                #endif
                    {
                        MApp_ChannelChange_SearchDefaultAudioLang();
                    }

                    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &NewstAudioStreamInfo, g_u8AudLangSelected);
                    if((stGenSetting.g_SoundSetting.enSoundAudioLan1 == NewstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex) || (stGenSetting.g_SoundSetting.enSoundAudioLan2 == NewstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex))
                    {
                        bSelectedAudStream=0xFF;

                    }
                    else
                    {
                        g_u8AudLangSelected=temp;
                    }
                }

            #if(ENABLE_DVB_AUDIO_DESC)
                if(stGenSetting.g_SoundSetting.bEnableAD == TRUE)
                {
                #if ENABLE_CI_PLUS
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        MApp_Audio_OpSearchAdAudio();
                    }
                    else
                #endif
                    {
                        MApp_Audio_SearchAdAudio();
                    }

                    // if ad exist
                    if (g_u8AdAudSelected != 0xFF)
                    {
                        MApp_Audio_SetAdAudio(g_u8AdAudSelected);
                        //MApp_Audio_SetAudioLanguage(g_u8AdAudSelected);
                        MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);
                        MApp_Audio_AdjustADVolume(stGenSetting.g_SoundSetting.ADVolume);
                    }
                }
            #endif
            }

            if (bNeedRestartChnChange == TRUE)
            {
                //printf("need Restar Chn with stopDSMCC %bu\n",!_stSIInfo.stPmtMonInfo.u8fMHEG5);
                //printf("### change channel due to PMT content change>>\n");
                if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    BOOLEAN bCheckPW = FALSE;

                  #if ENABLE_CI_PLUS && MEDIASET_PREMIUM_SMART_CAM
                    g_bIsServiceVideoChange = TRUE;
                  #endif

                #if ENABLE_SDT_OTHER_MONITOR
                    MEMBER_SERVICETYPE bServiceTypeTmp=E_SERVICETYPE_DTV;
                    WORD wSIDTmp=0;
                    WORD wLCNTmp=0;

                    MApp_SDT_Get_UserService(&bServiceTypeTmp, &wSIDTmp, &wLCNTmp);

                #if 0//MHEG5_ENABLE
                    BOOLEAN bIsCIMHEGRun = FALSE;
                    if (msAPI_IsCIMHEGRun() != E_MHEG_CI_OFF)
                    {
                        bIsCIMHEGRun = TRUE;
                    }
                #endif
                    MApp_Dmx_Disable_Reset_Filter();
                    MApp_Dmx_SetReset_EventInfo_status(FALSE);
                    MApp_ChannelChange_DisableChannel(FALSE,MAIN_WINDOW);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);

                    if( MApp_Get_ParentalBlock_state() /*_bParentalBlock*/)
                    {
                        MApp_ParentalControl_SetBlockStatus(TRUE);
                        if(bCheckPW)
                            MApp_Set_CheckParentalPWStatus(TRUE);
                    }

                    MApp_Dmx_SetReset_EventInfo_status(TRUE);

                    //g_SDT_eUserServiceType=bServiceTypeTmp;
                    //g_SDT_u16UserSID= wSIDTmp;
                    //g_SDT_u16UserLCN= wLCNTmp;
                    MApp_SDT_Set_UserService(bServiceTypeTmp, wSIDTmp, wLCNTmp);

                #else
                    MApp_Dmx_SetReset_EventInfo_status(FALSE);
                    bCheckPW = MApp_Get_CheckParentalPWStatus();
                    MApp_ChannelChange_DisableChannel(FALSE,MAIN_WINDOW);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    if( MApp_Get_ParentalBlock_state() /*_bParentalBlock*/)
                    {
                        MApp_ParentalControl_SetBlockStatus(TRUE);
                        if(bCheckPW)
                            MApp_Set_CheckParentalPWStatus(TRUE);
                    }
                    MApp_Dmx_SetReset_EventInfo_status(TRUE);
                #endif

                  #if ENABLE_CI_PLUS && MEDIASET_PREMIUM_SMART_CAM
                    g_bIsServiceVideoChange = FALSE;
                  #endif

                #if 0//MHEG5_ENABLE
                    if(bIsCIMHEGRun == TRUE)
                    {
                        msAPI_MHEG5_SetCIMHEGRun(E_MHEG_CI_TRIGGER);
                        bIsCIMHEGRun = FALSE;
                    }
                #endif
                }
              #if (ENABLE_PIP)
                if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                    {
                        MApp_ChannelChange_DisableChannel(FALSE,SUB_WINDOW);
                        MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                    }
                }
              #endif
            }
            else if(bNeedUpdateAudInfo == TRUE)//check if need replay later
            {
            #if (ENABLE_CI_PLUS)
                if(TRUE == MApp_CI_IsOpMode())
                {
                    MApp_ChannelChange_SearchDefaultOPAudioLang();
                }
                else
            #endif
                {
                    MApp_ChannelChange_SearchDefaultAudioLang();
                }


            #if(ENABLE_DVB_AUDIO_DESC)
                if(g_u8AdAudSelected == 0xFF)
                {
                    MApp_ChannelChange_SearchBroadcastMixAudio();
                }
            #endif

                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &NewstAudioStreamInfo, g_u8AudLangSelected);

                if (OldstAudioStreamInfo.wAudPID != NewstAudioStreamInfo.wAudPID ||
                    (u8PreLRAudioMode != MApp_Audio_Get_LRMode()/*g_u8LRAudioMode*/) ||
                    //OldstAudioStreamInfo.wAudType != NewstAudioStreamInfo.wAudType
                    OldstAudioStreamInfo.eSIAudType != NewstAudioStreamInfo.eSIAudType
                    )
                {
                    MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
                }
            }
        }

    }
    //EWBS
#if ENABLE_EWBS
    _bEwbsInfoEnable = _MApp_EWBS_Check(eChangeType);
#endif

}

#if ENABLE_EWBS
BOOLEAN MApp_GetEwbsFlag(void)
{
    return _bEwbsInfoEnable;
}
#endif

//=============================================================================

#endif

