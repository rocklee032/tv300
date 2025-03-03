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
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_CTL_AUTOCLOSE_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "datatype.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTglobal.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_ACTchannelinfo.h"
#include "MApp_ZUI_ACTcoexistWin.h"
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_AutoCloseWinProc
///  Window Proc for "auto close" control,
///     register a timer when being created.
//      And if timer event notified, then execute EN_EXE_CLOSE_CURRENT_OSD
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
extern MS_BOOL bChangeMessageboxTimer;
MS_BOOL bAutoTimeout = FALSE;
#endif

S32 MApp_ZUI_CTL_AutoCloseWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_CREATE:
#ifdef ATSC_SYSTEM
            if( hWnd == HWND_CHINFO_TRANSPARENT )
            {
                U32 timeout_ms = MApp_ZUI_API_GetWindowData(hWnd);//Get ATV TimeOut

                if (IsDTVInUse() && (enChannelInfoPageType == TYPE_CHANNEL_INFO))
                    timeout_ms = ATSC_CHANNEL_INFO_TIME_OUT_MS;

                if (timeout_ms > 0)
                {
                    //setting AP timeout, auto close
                    MApp_ZUI_API_SetTimer(hWnd, 0, timeout_ms);
                }
            }
            else
#endif
            {
                U32 timeout_ms = MApp_ZUI_API_GetWindowData(hWnd);

#if ENABLE_ATSC
                if (MApp_ZUI_GetActive_ChannelInfo_OSD())
                {
                    timeout_ms = 5000;
                }
#endif

                if (timeout_ms > 0)
                {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                    if( bChangeMessageboxTimer)
                    {
                        if(hWnd == HWND_MSGBOX_COMMON_BG)
                        {
                            printf("..............messagebox ...MApp_ZUI_API_SetTimer 30s..........\n");
                            MApp_ZUI_API_SetTimer(hWnd, 0, 30000);
                            bChangeMessageboxTimer = FALSE;
                        }
                    }
                    else
#endif
                    //setting AP timeout, auto close
                    MApp_ZUI_API_SetTimer(hWnd, 0, timeout_ms);
                }
            }
            break;

        case MSG_TIMER:
            {
                //if the time is up, kill the timer and then close AP!
                //maybe timeout on common dialog...MApp_ZUI_API_KillTimer(hwnd, 0);
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)&&(MApp_ZUI_API_IsSuccessor(HWND_MSGBOX_COMMON,hWnd)))
                {
                    bAutoTimeout = TRUE;
                }
#endif
#if((UI_SKIN_SEL ==  UI_SKIN_1366X768X565)||(UI_SKIN_SEL ==  UI_SKIN_960X540X565)||(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565))
                {
                    if(hWnd == HWND_EPG_RECORDER_PASSWORD_BG)
                    {
                        if(MApp_ZUI_API_IsWindowVisible (hWnd))
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                        break;
                    }
                }
#endif
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            break;

        default:
            //
            break;
    }

    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_AUTOCLOSE_C
