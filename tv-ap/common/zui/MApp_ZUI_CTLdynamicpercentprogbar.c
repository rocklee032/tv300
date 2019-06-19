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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_CTL_DYNAMICPERCENTPROGBAR_C
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
#include "apiGOP.h"
#include "MApp_GlobalVar.h"

#define MAX_PERCENT_TYPE 2
static UI_REGION_INFO m_LicenseRegionInfo;
static S16 aS16Percent[MAX_PERCENT_TYPE];

//DEBUG
#define RECT_DEBUG(x)   //x

#define MAX_GOP0_COEF   0x3f
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);

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
// Background Gray
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

// Foreground Black
static  DRAW_RECT _ZUI_TBLSEG _DrawProgressBarFgYellow =
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

// Foreground Green
static  DRAW_RECT _ZUI_TBLSEG _DrawProgressBarFgGreen =
{
#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
    0xFF000000|0x92, //OSD_COLOR RcolorFrom;
    0xFF000000|0x92, //OSD_COLOR RcolorTo;
#else
    0xFF000000|COLOR_GREEN, //OSD_COLOR RcolorFrom;
    0xFF000000|COLOR_GREEN, //OSD_COLOR RcolorTo;
#endif
    OSD_GRADIENT_DISABLE, //OSD_GRADIENT eRectGradient;
    0, //OSD_COLOR BroderColor;
    eRectBorder, //RECT_ATTRIB attrib;
    0, //U8 sizeBorder;
    0, //radius
};

// Foreground Blue
static  DRAW_RECT _ZUI_TBLSEG _DrawProgressBarFgBlue =
{
#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
    0xFF000000|0x92, //OSD_COLOR RcolorFrom;
    0xFF000000|0x92, //OSD_COLOR RcolorTo;
#else
    0xFF000000|COLOR_BLUE, //OSD_COLOR RcolorFrom;
    0xFF000000|COLOR_BLUE, //OSD_COLOR RcolorTo;
#endif
    OSD_GRADIENT_DISABLE, //OSD_GRADIENT eRectGradient;
    0, //OSD_COLOR BroderColor;
    eRectBorder, //RECT_ATTRIB attrib;
    0, //U8 sizeBorder;
    0, //radius
};

void MApp_ZUI_CTL_DrawRectBorder(HWND hWnd, PMSG pMsg)
{
    #define THICKNESS 2
    static  DRAW_RECT_BORDER _ZUI_TBLSEG _DrawRetentionBorder =
    {
        COLOR_RED,
        COLOR_RED,
        THICKNESS,
        eSolidLine,
    };

    RECT TempRect;
    MS_U8 u8CountIndex = 0;
    PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;
    while (u8CountIndex < m_LicenseRegionInfo.u8RegionCount)
    {
        //RECT_DEBUG(printf("SRC left:%d,Top:%d,width:%d,height:%d\n",param->rect->left,param->rect->top,param->rect->width,param->rect->height));
        S16 s16Left = param->rect->left;
        S16 s16Width = param->rect->width;
        U16 u16TempRegion = m_LicenseRegionInfo.stRetentionLimitInfo[u8CountIndex].u16RetentionLimitRegion;
        U8 u8WidthPercent = (U8)(u16TempRegion & 0xFF);
        U8 u8LeftPercent = (U8)(u16TempRegion >> 8);

        //RECT_DEBUG(printf("u8WidthPercent = %u,u8LeftPercent = %u\n",u8WidthPercent,u8LeftPercent));
        s16Left = (S16)((U32)s16Width * u8LeftPercent/100);
        s16Width = (S16)((U32)s16Width * u8WidthPercent/100);
        s16Width -= s16Left;
        s16Left += param->rect->left;
        RECT rect;
        memset(&rect,0,sizeof(RECT));
        rect.left = s16Left;
        rect.top = param->rect->top -2;
        rect.width = s16Width;
        rect.height = param->rect->height + 2;
        //RECT_DEBUG(printf("DST left:%d,Top:%d,width:%d,height:%d\n",param->rect->left,param->rect->top,param->rect->width,param->rect->height));
        if (TRUE == m_LicenseRegionInfo.stRetentionLimitInfo[u8CountIndex].bLicense)
        {
            // LICENSE
            DRAW_RECT_BORDER * pDrawBorder = (DRAW_RECT_BORDER*)_ZUI_MALLOC(sizeof(DRAW_RECT_BORDER));
            if (pDrawBorder)
            {
                memcpy(pDrawBorder, &_DrawRetentionBorder, sizeof(DRAW_RECT_BORDER));
                _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, pDrawBorder, &param->dc, &rect);
                _ZUI_FREE(pDrawBorder);
            }

            if (0xFF == m_LicenseRegionInfo.stRetentionLimitInfo[u8CountIndex].u8RetentionLimitCount)
            {
                //RECT_DEBUG(printf("Illegal u8RetentionLimitCount\n"));
                u8CountIndex++;
                continue;
            }

            DRAW_TEXT_OUT_DYNAMIC *dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
            {
                U16 u16TxtComponentIndex = 0;
                LPTSTR str = CHAR_BUFFER;
                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TxtComponentIndex, dyna);
                MApp_ZUI_API_GetU16String(m_LicenseRegionInfo.stRetentionLimitInfo[u8CountIndex].u8RetentionLimitCount);

                str += MApp_ZUI_API_Strlen(str);
                *str = '\0';
                dyna->pString = CHAR_BUFFER;
                dyna->eTextAttrib = eTextAlignMiddleWH;
                dyna->TextColor = COLOR_RED;

                //height too small to draw text , add 20
                memcpy(&TempRect, &rect, sizeof(RECT));
                TempRect.top -= 10;
                TempRect.height += 20;
                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, dyna, &param->dc, &TempRect);
                _ZUI_FREE(dyna);
            }
        }

        // URI & LICENSE check Expire
        {
            if (FALSE == m_LicenseRegionInfo.stRetentionLimitInfo[u8CountIndex].bExpire)
            {
                U16 u16TempPercent = m_LicenseRegionInfo.stRetentionLimitInfo[u8CountIndex].u16RetentionLimitPercent;
                u8WidthPercent = (U8)(u16TempPercent & 0xFF);
                u8LeftPercent = (U8)(u16TempPercent >> 8);
                s16Left = param->rect->left;
                s16Width = param->rect->width;
                s16Left = (S16)((U32)s16Width * u8LeftPercent/100);
                s16Width = (S16)((U32)s16Width * u8WidthPercent/100);
                s16Width -= s16Left;
                s16Left += param->rect->left;
                rect.left = s16Left;
                rect.width = s16Width;
            }

            DRAW_RECT * pDraw = (DRAW_RECT*)_ZUI_MALLOC(sizeof(DRAW_RECT));
            if (pDraw)
            {
                //adjust rect
                memcpy(&TempRect, &rect, sizeof(RECT));
                TempRect.top += 4;
                TempRect.height -= 4;

                memcpy(pDraw, &_DrawProgressBarFgGreen, sizeof(DRAW_RECT));
                param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);

                _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, pDraw, &param->dc, &TempRect);
                _ZUI_FREE(pDraw);
            }
        }
        u8CountIndex++;
    }

    UNUSED(hWnd);
}

void MApp_ZUI_CTL_DynamicPercentProgressBar_GetDrawRectInfo(MS_U8 hWnd, PMSG pMsg, RECT *pRect, MS_U8 u8Index)
{
    U32 u32Width = 0;
    U32 u32Left = 0;
    S16 width_Fg =0;
    S16 left_Fg = 0;
    S16 temp_Fg = 0;
    PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;

    temp_Fg = aS16Percent[u8Index];
    width_Fg = temp_Fg & 0x00FF;
    left_Fg = (temp_Fg >> 8);
    //RECT_DEBUG(printf("width_Fg = %d,left_Fg = %d\n",width_Fg,left_Fg));
    u32Left = ((U32)(param->rect->width - 4) * left_Fg) / 100;
    u32Width = ((U32)(param->rect->width - 4) * width_Fg) / 100;
    u32Width -= u32Left;
    u32Left += param->rect->left;
    pRect->left = (S16)u32Left + 2;
    pRect->top = param->rect->top + 2;
    pRect->width = (S16)u32Width;
    pRect->height = param->rect->height - 4;
    //RECT_DEBUG(printf("left = %d,top = %d,width = %d,height = %d\n",pRect->left,pRect->top,pRect->width,pRect->height));
    UNUSED(hWnd);

}
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
S32 MApp_ZUI_CTL_DynamicPercentProgressBarWinProc(HWND hWnd, PMSG pMsg)
{

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
                MApp_ZUI_CTL_DrawRectBorder(hWnd, pMsg);
                _ZUI_FREE(pDraw);
            }
            else
            {
                __ASSERT(0);
            }

            {
                RECT rectFg;
                MS_U8 u8Index;
                DRAW_RECT DrawArr[MAX_PERCENT_TYPE];
                DrawArr[0] = _DrawProgressBarFgYellow;
                DrawArr[1] = _DrawProgressBarFgBlue;

                param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
                for(u8Index = 0; u8Index < MAX_PERCENT_TYPE; u8Index++)
                {
                    MApp_ZUI_CTL_DynamicPercentProgressBar_GetDrawRectInfo(hWnd, pMsg, &rectFg, u8Index);
                    _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, &DrawArr[u8Index], &param->dc, &rectFg);
                }
            }
        }
        return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

void MApp_ZUI_CTL_RectBorderSetBarInfo(UI_REGION_INFO RetentionLimitInfo)
{
    U8 u8Index = 0;
    memset(&m_LicenseRegionInfo, 0 ,sizeof(m_LicenseRegionInfo));
    memcpy(&m_LicenseRegionInfo, &RetentionLimitInfo, sizeof(UI_REGION_INFO));

    RECT_DEBUG(printf("[UI]RegionCount=%u\n", m_LicenseRegionInfo.u8RegionCount));
    for (u8Index=0; u8Index<m_LicenseRegionInfo.u8RegionCount; u8Index++)
    {
        if (TRUE == m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].bLicense)
        {
            RECT_DEBUG(printf("[UI][Draw License][%u]Region=%04x, Percent=%04x, Count=%d, Expire=%u \n",
                              u8Index,
                              m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].u16RetentionLimitRegion,
                              m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].u16RetentionLimitPercent,
                              m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].u8RetentionLimitCount,
                              m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].bExpire));
        }
        else
        {
            RECT_DEBUG(printf("[UI][Draw URI][%u]Region=%04x, Percent=%04x, Expire=%d \n",
                              u8Index, m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].u16RetentionLimitRegion,
                              m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].u16RetentionLimitPercent,
                              m_LicenseRegionInfo.stRetentionLimitInfo[u8Index].bExpire));
        }
    }
}

void MApp_ZUI_CTL_SetPercentProgressBar(S16* Percent)
{
    MS_U8 u8Index;
    memset(aS16Percent, 0 ,sizeof(aS16Percent));
    for(u8Index = 0; u8Index < MAX_PERCENT_TYPE; u8Index++)
    {
        aS16Percent[u8Index] = Percent[u8Index];
    }
}
#undef MAPP_ZUI_CTL_DYNAMICPERCENTPROGBAR_C

