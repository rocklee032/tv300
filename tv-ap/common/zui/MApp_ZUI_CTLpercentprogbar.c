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
// (MStar Confidential Information!�L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_CTL_PERCENTPROGBAR_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "datatype.h"
#include "debug.h"
#include "msAPI_OSD.h"
#include "msAPI_Memory.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_Bitmap_EnumIndex.h"

static U8 m_u8Percent = 0;

////////////////////////////////////////////////////
// Rect Progress Bar

/*
    FOCUS:
    NORMAL:
    DISABLED:

    Background (Black)
    Foreground (Yellow)

    +--------------------------------------------+
    |     35%      |                             |
    +--------------------------------------------+
                   ^
       Percentage _|


*/

///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_CTL_RectProgressBarWinProc
///  Window Proc for "Rect progress bar" control,
///     which a round rectangle in background, and use red, purple, red rectangles as progress
///     change value by calling
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message
///
///  @return S32 event handler result
///
///  @author MStarSemi @date 2008/5/26
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_CTL_PercentProgressBarWinProc(HWND hWnd, PMSG pMsg)
{

    // Background
    static  DRAW_RECT _ZUI_TBLSEG _DrawProgressBarBg =
    {
        0xFF000000|COLOR_LTGRAY, //OSD_COLOR RcolorFrom;
        0xFF000000|COLOR_LTGRAY, //OSD_COLOR RcolorTo;
        OSD_GRADIENT_DISABLE, //OSD_GRADIENT eRectGradient;
        0, //OSD_COLOR BroderColor;
        eRectBorder, //RECT_ATTRIB attrib;
        0, //U8 sizeBorder;
        0, //radius
    };

    // Foreground
    static  DRAW_RECT _ZUI_TBLSEG _DrawProgressBarFg =
    {
#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
        0xFF000000|0x92, //OSD_COLOR RcolorFrom;
        0xFF000000|0x92, //OSD_COLOR RcolorTo;
#else
        0xFF000000|COLOR_YELLOW, //OSD_COLOR RcolorFrom;
        0xFF000000|COLOR_YELLOW, //OSD_COLOR RcolorTo;
#endif
        OSD_GRADIENT_DISABLE, //OSD_GRADIENT eRectGradient;
        0, //OSD_COLOR BroderColor;
        eRectBorder, //RECT_ATTRIB attrib;
        0, //U8 sizeBorder;
        0, //radius
    };

    switch(pMsg->message)
    {
        case MSG_PAINT:
            {
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;

                DRAW_RECT * pDraw = (DRAW_RECT*)_ZUI_MALLOC(sizeof(DRAW_RECT));
                if (pDraw)
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
                    memcpy(pDraw, &_DrawProgressBarBg, sizeof(DRAW_RECT));
                    _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, pDraw, &param->dc, param->rect);
                    _ZUI_FREE(pDraw);
                }
                else
                {
                    __ASSERT(0);
                }

                pDraw = (DRAW_RECT*)_ZUI_MALLOC(sizeof(DRAW_RECT));
                if (pDraw)
                {
                    RECT rectFg;
                    U32 u32Width = ((U32)(param->rect->width - 4) * m_u8Percent) / 100;

                    rectFg.left = param->rect->left + 2;
                    rectFg.top = param->rect->top + 2;
                    rectFg.width = (S16)u32Width;
                    rectFg.height = param->rect->height - 4;
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
                    memcpy(pDraw, &_DrawProgressBarFg, sizeof(DRAW_RECT));
                    _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, pDraw, &param->dc, &rectFg);
                    _ZUI_FREE(pDraw);
                }
                else
                {
                    __ASSERT(0);
                }
            }
            return 0;
        default:
            break;

    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

void MApp_ZUI_CTL_PercentProgressBar_SetPercentage(U8 u8Percent)
{
    if(u8Percent > 100)
    {
        u8Percent = 100;
    }
    m_u8Percent = u8Percent;
}

#undef MAPP_ZUI_CTL_PERCENTPROGBAR_C
