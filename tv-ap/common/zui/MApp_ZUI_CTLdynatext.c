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

#define MAPP_ZUI_CTL_DYNATEXT_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "datatype.h"
#include "msAPI_OSD.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTglobal.h"

#if ENABLE_ATSC_TTS
//#include "Utl.h"
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif

extern void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText);
extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicTextWinProc
///  Window Proc for "dynamic text" control,
///     which dynamic change the content by calling MApp_ZUI_ACT_GetDynamicText()
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

S32 MApp_ZUI_CTL_DynamicTextWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_PAINT:
            {
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;
                //DRAWSTYLE * style_list = 0;
                DRAWSTYLE_TYPE ds_type = DS_NORMAL;

                //find all static text => dynamic text
                if (param->bIsDisable)
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hWnd);
                    //style_list = GETDISABLEDRAWSTYLE(hWnd);
                    ds_type = DS_DISABLE;
                }
                else if (param->bIsFocus) //the same focus group
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
                    //style_list = GETFOCUSDRAWSTYLE(hWnd);
                    ds_type = DS_FOCUS;
                }
                else
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hWnd);
                    //style_list = GETNORMALDRAWSTYLE(hWnd);
                }

                //if (style_list)
                {
                    //while(style_list->component != CP_NOON)
                    {
                        _MApp_ZUI_API_DefaultOnPaint(hWnd, param, FALSE);
                        //if (style_list->component == CP_TEXT_OUT)
                        {
                            U16 u16TxtComponentIndex = _MApp_ZUI_API_FindFirstComponentIndex(hWnd, ds_type, CP_TEXT_OUT);
                            LPTSTR pStr = MApp_ZUI_ACT_GetDynamicText(hWnd);

                            if (u16TxtComponentIndex != 0xFFFF && pStr)
                            {
                                DRAW_TEXT_OUT_DYNAMIC dyna;
                                //dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                                //if (dyna)
                                {

                                    _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TxtComponentIndex, &dyna);
                                    dyna.pString = pStr;
                                    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, &dyna, &param->dc, param->rect);
                                    //_ZUI_FREE(dyna);
                                }

                        #if( ENABLE_ATSC_TTS )
                                if( MApp_TTS_Cus_Get_UserSetting_TTSOn() ) // If TTS on
                                {
                                    HWND focused = MApp_ZUI_API_GetFocus();
                                #if ENABLE_TTSTEST_FROM_USB
                                    if((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)&&(MApp_ZUI_API_IsSuccessor(HWND_MENU_TEST_TTS_PAGE, hWnd)))
                                    {
                                        //do not  say TTS at HWND_MENU_TEST_TTS_PAGE
                                        return 0;
                                    }
                                #endif
                                    //printf("focused=%u\n", focused);
                                    if ((focused == MApp_ZUI_API_GetParent(hWnd)) || (focused == hWnd))
                                    {
                                        //MApp_TTS_Cus_Add_Str_By_HWndID((U16)hWnd, EN_TTS_SPEAK_NORMAL);

                                        // Patch  '-'
                                        if( ('-' == pStr[0]) )
                                        {
                                            U8 au8Str_Minus[] = "minus";
                                            MApp_TTS_Cus_AddU8String(au8Str_Minus);
                                            MApp_TTS_Cus_AddUniString(pStr+1);
                                        }
                                        else if( MApp_ZUI_GetActiveOSD() == E_OSD_DMP )
                                        {
                                            if((MApp_ZUI_API_IsSuccessor(HWND_DMP_FILE_PAGE_THUMB_GROUP,hWnd))&&(hWnd != HWND_DMP_FILE_PAGE_THUMB_ITEM1_STRING))
                                            {
                                                U16 *filename = pStr;
                                                BOOL jdgwma = FALSE,jdgavi = FALSE,jdgmov = FALSE;
                                                U8 wma[] = "wma";
                                                U8 avi[] = "avi";
                                                U8 mov[] = "mov";
                                                if(pStr != NULL)
                                                {
                                                    do
                                                   {
                                                       if(*filename == '\0')
                                                       {
                                                           if(((*(filename-1) == 'a')&&(*(filename-2) == 'm')&&(*(filename-3) == 'w')) || ((*(filename-1) == 'A')&&(*(filename-2) == 'M')&&(*(filename-3) == 'W')))
                                                           {
                                                              *(filename-1) = *(filename-2) =*(filename-3) = '\0';
                                                              jdgwma = TRUE;
                                                              break;
                                                           }
                                                           else if(((*(filename-1) == 'i')&&(*(filename-2) == 'v')&&(*(filename-3) == 'a'))||((*(filename-1) == 'I')&&(*(filename-2) == 'V')&&(*(filename-3) == 'A')))
                                                           {
                                                              *(filename-1) = *(filename-2) =*(filename-3) = '\0';
                                                              jdgavi = TRUE;
                                                              break;
                                                           }
                                                           else if(((*(filename-1) == 'v')&&(*(filename-2) == 'o')&&(*(filename-3) == 'm'))||((*(filename-1) == 'V')&&(*(filename-2) == 'O')&&(*(filename-3) == 'M')))
                                                           {
                                                              *(filename-1) = *(filename-2) =*(filename-3) = '\0';
                                                              jdgmov = TRUE;
                                                              break;
                                                           }
                                                           else
                                                              break;
                                                       }
                                                       else
                                                       {
                                                           filename++;
                                                       }
                                                   }while(1);
                                                }
                                                if(jdgwma || jdgavi || jdgmov)
                                                {
                                                    MApp_TTS_Cus_AddUniString(pStr);
                                                    if(jdgwma)
                                                        MApp_TTS_Cus_Add_U8Str_Format(wma,EN_TTS_SPEAK_CHARACTERS);
                                                    else if(jdgavi)
                                                        MApp_TTS_Cus_Add_U8Str_Format(avi,EN_TTS_SPEAK_CHARACTERS);
                                                    else
                                                        MApp_TTS_Cus_Add_U8Str_Format(mov,EN_TTS_SPEAK_CHARACTERS);
                                                }
                                                else
                                                {
                                                    MApp_TTS_Cus_AddUniString(pStr);
                                                }
                                            }
                                            else if((MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, hWnd)))
                                            {
                                                ;//has deal with it in other please,do nothing here 
                                            }
                                            else
                                            {
                                                MApp_TTS_Cus_AddUniString(pStr);
                                            }
                                        }
                                        else
                                        {
                                            MApp_TTS_Cus_AddUniString(pStr);
                                        }

                                        MApp_TTSControlSetOn(TRUE);
                                    }
                                }
                        #endif
                            }
                        }
                        //else
                        //{
                        //    _MApp_ZUI_API_DrawComponent(style_list->component, style_list->u16Index, &param->dc, param->rect);
                        //}
                        //style_list++;
                    }
                }

            }
            return 0;
        default:
            break;

    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_DYNATEXT_C
