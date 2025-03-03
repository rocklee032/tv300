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

#define MAPP_ATV_MANUALTUNING_MAIN_C

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_Global.h"

#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_ATV_ManualTuning_Main.h"
#include "MApp_ChannelChange.h"

#if (CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_ACTatvmanualtuning.h"
#include "ZUI_exefunc.h"
#endif

void msAPI_Tuner_SetCurrentChannelPLL(U16 u16TunerPLL);

///////////////////////////////////////////////////////////

EN_ATV_MANUALTUNING_STATE enAtvManualTuningState;

//////////////////////////////////////////////////////////

EN_RET MApp_ATV_ManualTuning_Main(void)
{
    EN_RET enRetVal = EXIT_NULL;

    switch(enAtvManualTuningState)
    {
        case STATE_ATV_MANUALTUNING_INIT:
//@@-- DTV source to ATV, show disable channel,otherwise ATV will no audio.
         #if ENABLE_SBTVD_ATV_SYSTEM
            //MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
         #endif
            MApp_ZUI_ACT_StartupOSD(E_OSD_ATV_MANUAL_TUNING);
            enAtvManualTuningState = STATE_ATV_MANUALTUNING_WAIT;
            break;

        case STATE_ATV_MANUALTUNING_WAIT:
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;

          #if (CHAKRA3_AUTO_TEST)
            if( g_AT_enATVManualTuningState == E_AUTO_TEST_TUNING_WAIT_START )
            {
                // Setup init freq
                //MApp_AT_SetATVManualTuneFreq();
                {
                    // Get init freq from auto test
                    U32 u32Freq = MApp_AT_Get_AtvManualTuneFreq();
                  #if TN_FREQ_STEP == FREQ_STEP_62_5KHz
                    MS_U16 u16TunerPLL = u32Freq*10/625;
                  #elif TN_FREQ_STEP == FREQ_STEP_50KHz
                    MS_U16 u16TunerPLL = u32Freq/50;
                  #else
                    MS_U16 u16TunerPLL = u32Freq*100/3125;
                  #endif // TN_FREQ_STEP

                    msAPI_Tuner_SetCurrentChannelPLL(u16TunerPLL);
                }

                MApp_ZUI_API_SetFocus(HWND_ATUNE_SEARCH);
                MApp_ZUI_ACT_ExecuteAtvManualTuningAction(EN_EXE_GOTO_SCAN_INC);

                g_AT_enATVManualTuningState = E_AUTO_TEST_TUNING_START;
                //printf("E_AUTO_TEST_TUNING_START\n");
            }
          #endif
            break;

        case STATE_ATV_MANUALTUNING_CLEAN_UP:
            MApp_ZUI_ACT_ShutdownOSD();
            enAtvManualTuningState = STATE_ATV_MANUALTUNING_INIT;
            enRetVal = EXIT_CLOSE;
            break;

        case STATE_ATV_MANUALTUNING_GOTO_STANDBY:
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal = EXIT_GOTO_STANDBY;
            break;

        case STATE_ATV_MANUALTUNING_GOTO_MAIN_MENU:
            MApp_ZUI_ACT_ShutdownOSD();
            enAtvManualTuningState = STATE_ATV_MANUALTUNING_INIT;
            enRetVal = EXIT_GOTO_MENU;
            break;

        case STATE_ATV_MANUALTUNING_GOTO_ATV_SCAN:
            enAtvManualTuningState = STATE_ATV_MANUALTUNING_WAIT;
            enRetVal = EXIT_GOTO_ATVSCAN;
            break;

        default:
            enAtvManualTuningState = STATE_ATV_MANUALTUNING_WAIT;
            break;
    }
    return enRetVal;
}

#undef MAPP_ATV_MANUALTUNING_MAIN_C

