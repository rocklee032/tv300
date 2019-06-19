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
// (?°ÏMStar Confidential Information?°ß) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#define MAPP_EWBS_C

#include "Board.h"

#if ENABLE_EWBS

#include <string.h>

#include "MApp_EWBS.h"

#include "msAPI_Timer.h"
#include "apiXC_Sys.h"

#include "ZUI_tables_h.inl"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_Menu_Main.h"
#include "MApp_Audio.h"
#include "msAPI_DTVSystem.h"
#include "mapp_si.h"

#include "MApp_GlobalVar.h"
#include "MApp_ChannelChange.h"
#include "MApp_SignalMonitor.h"
#include "MApp_TopStateMachine.h"
#include "MApp_InputSource.h"
#include "MApp_TopStateMachine.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_PowerOnMusic.h"

#include "MApp_MultiTasks.h"
#include "MApp_DVB_ServiceMonitor.h"

//=============================================================================

#define EWBS_DEBUG(x)        //x
#define EWBS_PERIOD          1000//ms
#define EWBS_MSG_DELAY       1000//90000//ms (Time of Message disappearence when EWS status was changed)

static U32 u32EwbsPeriodTime = 0;    //Monitor period
static U32 u32EwbsMsgDelayTime = 0;  //Msg delay time; Sharp only
static BOOL bEwbsAudioFlag = FALSE;
static U8 u8EwbsPrevStatus = FALSE;
extern EN_MENU_STATE enMainMenuState;
extern BOOLEAN bInMP3_Play;
//SI_EWBS_INFO stEwbsInfo;

#define EWBS_DESC_BUF_SIZE   4096
//static U8 u8EwbsDescriptionBuf[EWBS_DESC_BUF_SIZE]={0};

#if ENABLE_SOUNDTEST_MUSIC_LOOP
BOOLEAN MApp_EWBS_SoundTest_Exit(void)
{
    if(MApp_SoundTest_Exit())
    {
        MApp_EWBS_SetAudioFlag(FALSE);
        /* unmute the sound */
        MApp_InputSource_ChangeAudioSource( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),UI_INPUT_SOURCE_NONE);
        MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);

        return TRUE;
    }
    return FALSE;
}
#endif

void MApp_EWBS_Exit(void)
{
    if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWBS_FRAME) == TRUE))
    {
        MApp_ZUI_ACT_ShutdownOSD();
    }
#if ENABLE_SOUNDTEST_MUSIC_LOOP
    if( MApp_EWBS_SoundTest_Exit())
    {
        // msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_EWS, DISABLE, NULL, MAIN_WINDOW);
        //MApp_EWBS_ScreenDisplay_Handler();
    }
    else
#endif
    {
        MApp_ChannelChange_SearchDefaultAudioLang();
        MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
        EWBS_DEBUG(printf("\r\n[EWBS]EWBS Exit"););

        //reset Flag status
        //MApp_EWS_SetMsgCancelFlag(FALSE);
        MApp_EWBS_SetAudioFlag(FALSE);
    }
}

void MApp_EWBS_SetAudioFlag(BOOL flag)
{
    bEwbsAudioFlag = flag;
}

BOOL MApp_EWBS_Audio_Monitor(void)
{
    if(bInMP3_Play)
    {
        MApp_EWBS_SetAudioFlag(FALSE);
        bInMP3_Play = FALSE;
    }
    if((bEwbsAudioFlag == FALSE))
    {
#if ENABLE_SOUNDTEST_MUSIC_LOOP
       // printf(" Make EWS Mp3\n");
        if(MApp_GetEwbsFlag() && stGenSetting.stMiscSetting.g_bEwbsBuzzerNotification)
        {
            if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWBS_FRAME) == TRUE))
            {
                MApp_SoundTest_ON(TRUE);
                MApp_EWBS_SetAudioFlag(TRUE);
            }
        }
#else
/*
        MS_EWSAUDIOINFO stAudioInfo;

        MApp_SI_GetEWBSAudioInfo(&stAudioInfo);
    	EWS_DEBUG(printf("audio PID =%x,audio type=%x\n",stAudioInfo.u16EWSAudioPID,stAudioInfo.u16EWSAudioType);)
        if(stAudioInfo.u16EWBSAudioPID == 0)
        {

            return FALSE;
        }
        MApp_Audio_SetEWBSAudio(stAudioInfo);
        MApp_EWBS_SetAudioFlag(TRUE);
*/
#endif
    }
    return TRUE;
}

void MApp_EWBS_MsgDisplay_Monitor(void)
{
    if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX) && (MApp_ZUI_API_IsWindowVisible(HWND_EWBS_FRAME) == FALSE))
    {
        MApp_ZUI_API_InvalidateWindow(HWND_EWBS_FRAME);
    }
    else
    {
        if(MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)
        {
            enMainMenuState = STATE_MENU_CLEAN_UP;
            return;
        }
        else
        {
            /*if(MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY)
            {
                //MApp_ZUI_ACT_ShutdownOSD();
            }
            else*/
            {
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
            }
        }
    }
}

void MApp_EWBS_Handler(void)
{
    U8 u8EwbsCurrentStatus = MApp_GetEwbsFlag();

    if(IsDTVInUse())
    {
        if((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU) && (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DLG_INPUT_EWBS_LOCATION_COMMON) == TRUE))
            return;

        if(msAPI_Timer_DiffTimeFromNow(u32EwbsPeriodTime) < EWBS_PERIOD)
            return;
        u32EwbsPeriodTime = msAPI_Timer_GetTime0();

        if(u8EwbsCurrentStatus && stGenSetting.stMiscSetting.g_bEwbsMode)
        {
            MApp_EWBS_MsgDisplay_Monitor();
            MApp_EWBS_Audio_Monitor();

        #if ENABLE_SOUNDTEST_MUSIC_LOOP
            MApp_SoundTest_Task(BIN_ID_EWS_MP3);
        #endif

            if(u8EwbsPrevStatus != u8EwbsCurrentStatus)
            {
                EWBS_DEBUG(printf("\r\n[EWS]Screen Mute");)
                MApp_EWBS_Exit();
            }
            u32EwbsMsgDelayTime = msAPI_Timer_GetTime0();
            u8EwbsPrevStatus = u8EwbsCurrentStatus;
        }
        else
        {
            if(u8EwbsPrevStatus != u8EwbsCurrentStatus)
            {
                MApp_EWBS_Exit();
                u8EwbsPrevStatus = u8EwbsCurrentStatus;
            }

        }

    }
}
#endif
#undef MAPP_EWBS_C

