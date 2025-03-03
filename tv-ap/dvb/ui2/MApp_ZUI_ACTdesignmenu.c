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
// (¨MStar Confidential Information〃) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTDESIGNMENU_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "Panel.h"

#include "apiXC.h"
#include "apiXC_Adc.h"

#include "drvXC_HDMI_if.h"
#include "apiXC_Sys.h"
#include "apiXC_PCMonitor.h"
#include "apiXC_ModeParse.h"

#include "apiXC_Cus.h"
#if(ENABLE_CI)
#include "msAPI_CI.h"
#endif
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_OSDPage_Main.h"

#include "MApp_ZUI_ACTdesignmenu.h"

#include "MApp_UiMenuDef.h"
#include "SysInit.h"
#include "MApp_ChannelChange.h"
#include "MApp_InputSource.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_CustomerInfoInclude.h"
#include "MApp_SaveData.h"
#include "apiXC_Sys.h"
#include "MApp_Version.h"
#include "MApp_ZUI_ACTmenufunc.h"
#include "MApp_PCMode.h"
#include "apiXC_Ace.h"
#include "drvPQ.h"
#include "MApp_XC_PQ.h"
#include "msAPI_VD.h"

#include "msAPI_Video.h"
#include "MApp_MVDMode.h"
#include "MApp_Scaler.h"
#include "msAPI_MIU.h"
#include "MApp_GlobalFunction.h"
#include "MApp_XC_Sys.h"
#include "drvUART.h"
#if(ENABLE_OAD)
#include "MApp_OAD.h"
#endif
#if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION
#include"apiXC_Cus.h"
#include"msAPI_VD.h"
#include"MApp_ZUI_ACTmenufunc.h"
#endif
#if((ENABLE_EXTERN_MFC_CHIP)||ENABLE_6M40_4KX2K_PROCESS)
#include "mapp_swupdate.h"
#include "MApp_USBDownload.h"
#endif

#if ENABLE_AUTOTEST
#include "autotest.h"
#endif
#if ENABLE_PVR
#include"MApp_Record.h"
#include "MApp_UiPvr.h"
#endif

#include "MApp_DataBase_Factory.h"


#include "msAPI_DTVSystem.h"

#include "drvVIF.h"
// extern void SET_Default_TW_DTV_CH(void);

#include "MApp_GlobalFunction.h"

#include "MApp_HashKey.h"



#if ENABLE_VD_PACH_IN_CHINA
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)|| \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J)  || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_M10)  || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)   || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
#if ( ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)) )
#include "drvVIF.h"  //Add for CVBS out ATV at Component/HDMI/VGA 20100503EL
#endif
#endif
#endif


#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#define LOG_DESIGNMENU_SHOWITEM                    1 // Change Dislpay Designmenu Mode
#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
extern BOOLEAN b_isCIkeyFileExit;
extern BOOLEAN Mapp_check_valid_key(void);
#endif

typedef struct _DESIGN_BAR_INFO
{
    HWND pre_item;
    HWND cur_item;
} DESIGN_BAR_INFO;

static DESIGN_BAR_INFO _eDesignBarInfo;
#if ENABLE_AUTO_DQS_Design

typedef enum _BIST_TEST_UI
{
    EN_BIST_TEST_UI_START,
    EN_BIST_TEST_UI_PROCESSING,
    EN_BIST_TEST_UI_END,
} BIST_TEST_UI;

static BIST_TEST_UI _BIST_TEST_MODE;
#define DESIGN_MENU_CURRENT_TEXT_DISABLE_COLOR   0xFFFF0000

#endif
/////////////////////////////////////////////////////////////////////

typedef enum _DESIGN_MENU_PAGE
{
    EN_DESIGN_PAGE_ROOT,
    // EN_DESIGN_PAGE_ADC_ADJUST,
#if ENABLE_PANEL_BIN
    EN_DESIGN_PAGE_PANEL_PARAMETER,
#endif
    EN_DESIGN_PAGE_PICTURE_MODE,
    // EN_DESIGN_PAGE_WHITE_BALANCE,
    EN_DESIGN_PAGE_SSC,
    EN_DESIGN_PAGE_MIU_SSC,
    EN_DESIGN_PAGE_LVDS_SSC,
#if URSA_SSC_ENABLE
    EN_DESIGN_PAGE_6MXX_SSC,
#endif
    EN_DESIGN_PAGE_SPECIAL_SET,
    EN_DESIGN_PAGE_VIF,
    EN_DESIGN_PAGE_VD,
    EN_DESIGN_PAGE_AUDIO,
    EN_DESIGN_PAGE_QMAP_PAGE,
    EN_DESIGN_PAGE_SW_INFO_PAGE,
#if ENABLE_AUTOTEST
    EN_DESIGN_PAGE_BMTEST_PAGE,
#endif
#if ENABLE_AUTO_DQS_Design
    EN_DESIGN_PAGE_BIST_TEST,
#endif
    #if (ENABLE_PIP)
    EN_DESIGN_PAGE_PIP_POP,
    #endif
    EN_DESIGN_PAGE_UART_DBG,
#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
    EN_DESIGN_PAGE_CIPLUSKEY_UPGRADE,
#endif
    EN_DESIGN_PAGE_PEQ,
#if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION
    EN_DESIGN_PAGE_OVERSCAN,
#endif

#if ENABLE_CI
     EN_DESIGN_PAGE_CI,
#endif

#if ENABLE_PICTURE_NONLINEAR_CURVE
      EN_DESIGN_PAGE_NONLINEAR_CURVE,
#endif
    EN_DESIGN_RESTORE_DEFAULT,
    EN_DESIGN_PAGE_OTHER,
    EN_DESIGN_PAGE_NON_STANDARD,
    EN_DESIGN_GOTO_FACTORY_MENU,
#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
    EN_DESIGN_WHITE_BALANCE_PATTERN,
#endif

} DESIGN_MENU_PAGE;

U8 u8AFEC_A0_VALUE[6] = {0x10,0xBC,0xAE,0x9A,0x90,0x82};
U8 u8AFEC_A1_VALUE[6] = {0x20,0x6A,0x5E,0x35,0x20,0x04};

#if ENABLE_PICTURE_NONLINEAR_CURVE
typedef enum _NONLINEAR_CURVE_OPTION
{
    EN_NONLINEAR_BRIGHTNESS_CURVE,
    EN_NONLINEAR_CONTRAST_CURVE,
    EN_NONLINEAR_SATURATION_CURVE,
    EN_NONLINEAR_HUE_CURVE,
    EN_NONLINEAR_SHARPNESS_CURVE,
    EN_NONLINEAR_BACKLIGHT_CURVE,
    EN_NONLINEAR_VOLUME_CURVE,
} NONLINEAR_CURVE_OPTION;
#endif

#define PEQ_FO_MIN 100
#define PEQ_FO_MAX 16000
#define PEQ_FO_COARSE_STEP 100
#define PEQ_FO_FINE_STEP 1
#define PEQ_GAIN_MIN 0
#define PEQ_GAIN_MAX 240
#define PEQ_GAIN_STEP 1
#define PEQ_Q_MIN 5
#define PEQ_Q_MAX 160
#define PEQ_Q_STEP 1

#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
#define PATTERN_MIN_VALUE_TO_REG 0x400
#define PATTERN_MAX_VALUE_TO_REG 0x7FF

U16 u16DefaultContrast = 50;
U16 u16WhiteBalancePatternValue;
#endif
static DESIGN_MENU_PAGE _eDesignMenuPage;
#if ENABLE_PICTURE_NONLINEAR_CURVE
static NONLINEAR_CURVE_OPTION _eNonlinearCurveOption[DATA_INPUT_SOURCE_NUM-1];
#endif
static void _MApp_ZUI_ACT_DesignMenuInitPage(DESIGN_MENU_PAGE page);
static U8 _u8IPNumber;
static U8 _u8IPIndex;
static U8 uart_tmp;
static BOOLEAN g_ADCCalibrationResult;

/*static U16 ChinaDESTweakValue = 50;*/
// static U8 ADC_ADJUST_Phase[EN_FacAdj_AdcMode_Ypbpr_Num];


typedef enum
{
    MS_UART_TYPE_MIN,
    MS_UART_TYPE_HK = MS_UART_TYPE_MIN,
    MS_UART_TYPE_AEON,
    MS_UART_TYPE_VDEC,
    MS_UART_TYPE_NONE,
    MS_UART_TYPE_MAX = MS_UART_TYPE_NONE
} EN_MS_UART_TYPE;
/////////////////////////////////////////////////////////////////////
static const char SWCompileDate[]      = {_CODE_DATE_};
static const char SWCompileTime[]      = {_CODE_TIME_};
/////////////////////////////////////////////////////////////////////
static EN_OSDPAGE_STATE _enTargetOSDPageState;

static U16 _u16ScalerAdjLaunchKeys;

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);
//////////////////////////////////////////////////////////////////////

static  HWND _ZUI_TBLSEG _DesignMenuItemHwndList[]=
{
    HWND_DESIGN_MENU_ITEM0,
    HWND_DESIGN_MENU_ITEM1,
    HWND_DESIGN_MENU_ITEM2,
    HWND_DESIGN_MENU_ITEM3,
    HWND_DESIGN_MENU_ITEM4,
    HWND_DESIGN_MENU_ITEM5,
    HWND_DESIGN_MENU_ITEM6,
    HWND_DESIGN_MENU_ITEM7,
    HWND_DESIGN_MENU_ITEM8,
    HWND_DESIGN_MENU_ITEM9,
    HWND_DESIGN_MENU_ITEM10,
    HWND_DESIGN_MENU_ITEM11,
    HWND_DESIGN_MENU_ITEM12,
    HWND_DESIGN_MENU_ITEM13,
    HWND_DESIGN_MENU_ITEM14,
    HWND_DESIGN_MENU_ITEM15,
    HWND_DESIGN_MENU_ITEM16,
    HWND_DESIGN_MENU_ITEM17,
    HWND_DESIGN_MENU_ITEM18,
};

static  HWND _ZUI_TBLSEG _DesignMenuItemHwndNameList[]=
{
    HWND_DESIGN_MENU_ITEM0_NAME,
    HWND_DESIGN_MENU_ITEM1_NAME,
    HWND_DESIGN_MENU_ITEM2_NAME,
    HWND_DESIGN_MENU_ITEM3_NAME,
    HWND_DESIGN_MENU_ITEM4_NAME,
    HWND_DESIGN_MENU_ITEM5_NAME,
    HWND_DESIGN_MENU_ITEM6_NAME,
    HWND_DESIGN_MENU_ITEM7_NAME,
    HWND_DESIGN_MENU_ITEM8_NAME,
    HWND_DESIGN_MENU_ITEM9_NAME,
    HWND_DESIGN_MENU_ITEM10_NAME,
    HWND_DESIGN_MENU_ITEM11_NAME,
    HWND_DESIGN_MENU_ITEM12_NAME,
    HWND_DESIGN_MENU_ITEM13_NAME,
    HWND_DESIGN_MENU_ITEM14_NAME,
    HWND_DESIGN_MENU_ITEM15_NAME,
    HWND_DESIGN_MENU_ITEM16_NAME,
    HWND_DESIGN_MENU_ITEM17_NAME,
    HWND_DESIGN_MENU_ITEM18_NAME,

};


static  HWND _ZUI_TBLSEG _DesignMenuItemHwndValueList[]=
{
    HWND_DESIGN_MENU_ITEM0_VALUE,
    HWND_DESIGN_MENU_ITEM1_VALUE,
    HWND_DESIGN_MENU_ITEM2_VALUE,
    HWND_DESIGN_MENU_ITEM3_VALUE,
    HWND_DESIGN_MENU_ITEM4_VALUE,
    HWND_DESIGN_MENU_ITEM5_VALUE,
    HWND_DESIGN_MENU_ITEM6_VALUE,
    HWND_DESIGN_MENU_ITEM7_VALUE,
    HWND_DESIGN_MENU_ITEM8_VALUE,
    HWND_DESIGN_MENU_ITEM9_VALUE,
    HWND_DESIGN_MENU_ITEM10_VALUE,
    HWND_DESIGN_MENU_ITEM11_VALUE,
    HWND_DESIGN_MENU_ITEM12_VALUE,
    HWND_DESIGN_MENU_ITEM13_VALUE,
    HWND_DESIGN_MENU_ITEM14_VALUE,
    HWND_DESIGN_MENU_ITEM15_VALUE,
    HWND_DESIGN_MENU_ITEM16_VALUE,
    HWND_DESIGN_MENU_ITEM17_VALUE,
    HWND_DESIGN_MENU_ITEM18_VALUE,

};

static code U8 BoardNameStr[] = {
#ifdef BOARD_NAME
        BOARD_NAME
#else
        "Unknown board"
#endif
};

static U8 _MApp_ZUI_ACT_DesignMenuWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < COUNTOF(_DesignMenuItemHwndList); i++)
    {
        if (hwnd == _DesignMenuItemHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_DesignMenuItemHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_DesignMenuIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= COUNTOF(_DesignMenuItemHwndList))
        return HWND_INVALID;
    return _DesignMenuItemHwndList[u8Index];

}

////////////////////////////////////////////////////////////////////

void MApp_ZUI_ACT_AppShowDesignMenu(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_DESIGN_MENU;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_DESIGN_MENU_XSTART, ZUI_DESIGN_MENU_YSTART,
        ZUI_DESIGN_MENU_WIDTH, ZUI_DESIGN_MENU_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }
    _u8IPIndex = 0;
    _u8IPNumber = (U8)MDrv_PQ_GetIPNum(PQ_MAIN_WINDOW);
    //printf("------- Init _u8IPIndex [%bu] _u8IPNumber [%bu] --------\n", _u8IPIndex, _u8IPNumber);

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    //MApp_ZUI_API_SetFocus(HWND_DESIGN_MENU_ITEM0);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BG_TRANSPARENT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_INPUT_INFO, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP1, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP2, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BAR_TRANS, SW_HIDE);
    _MApp_ZUI_ACT_DesignMenuInitPage(EN_DESIGN_PAGE_ROOT);

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    ZUI_MSG(printf("[%s, %d, %s]\n", __FILE__, __LINE__, __FUNCTION__));
}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleDesignMenuKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    //MApp_ZUI_API_ResetTimer(HWND_AUDLANG_LIST_PANE, 0);

    switch(key)
    {
        case VK_EXIT:
            ZUI_MSG(printf("[%s, %d, %s]\n", __FILE__, __LINE__, __FUNCTION__));
            MApp_ZUI_ACT_ExecuteDesignMenuAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;
        case VK_POWER:
            ZUI_MSG(printf("[%s, %d, %s]\n", __FILE__, __LINE__, __FUNCTION__));
            MApp_ZUI_ACT_ExecuteDesignMenuAction(EN_EXE_POWEROFF);
            return TRUE;
        default:
            break;
    }

    //launch code for Scaler Adjust item
    if (VK_NUM_0 <= key && key <= VK_NUM_9)
    {
        _u16ScalerAdjLaunchKeys = (_u16ScalerAdjLaunchKeys<<4)|(key-VK_NUM_0);
        if (_u16ScalerAdjLaunchKeys == 0x9999)
        {
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_ITEM7, SW_SHOW);
        }
    }
    else
    {
        _u16ScalerAdjLaunchKeys = 0xFFFF;
    }

    return FALSE;
}

void MApp_ZUI_ACT_TerminateDesignMenu(void)
{
    ZUI_MSG(printf("[]term:facmenu\n");)
    MApp_OSDPage_SetState(_enTargetOSDPageState);
}

////////////////////////////////////////////////////////////


typedef struct _DESIGN_MENU_ITEM
{
    DESIGN_MENU_PAGE eCurPage;
    DESIGN_MENU_PAGE ePrevPage;
    DESIGN_MENU_PAGE eNextPage;
    U8 u8ShowItem;
    U16 u16StringID;
    BOOLEAN bDisable;
} DESIGN_MENU_ITEM;

static  DESIGN_MENU_ITEM _ZUI_TBLSEG _DesignMenuItem[]=
{
    //==root============================================
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_GOTO_FACTORY_MENU,
        0, en_str_Factory_Setting, FALSE
    },
    /*
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        1, en_str_ADC_ADJUST, FALSE
    },*/
#if ENABLE_PANEL_BIN
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PANEL_PARAMETER,
        1, en_str_Panel_Parameter, FALSE
    },
#endif
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        2, en_str_Picture_Mode, FALSE
    },
#if ENABLE_PICTURE_NONLINEAR_CURVE
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NONLINEAR_CURVE,
#if (ENABLE_NONLINEAR_CURVE)
        3, en_str_NONLINEAR, FALSE
#else
        3, en_str_NONLINEAR, TRUE
#endif
    },
#endif
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NON_STANDARD,
        4,en_str_Non_standard, FALSE
    },
    /*
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        5, en_str_White_balance, FALSE
    },
    */
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SSC,
#if ENABLE_SSC
        6, en_str_SSC, FALSE
#else
        6, en_str_SSC, TRUE
#endif
    },
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        7, en_str_SPECIAL_SET, FALSE
    },
#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_WHITE_BALANCE_PATTERN,
        8, en_str_WhiteBalanceTestPattern, FALSE
    },
#endif
/*
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_VIF,
#if ENABLE_VD_PACH_IN_CHINA
        8, en_str_VIF1, FALSE
#else
        8, en_str_VIF1, TRUE
#endif
    },
*/
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        9, en_str_QMAP_ADJUST, FALSE
    },
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        10, en_str_PEQ, FALSE
    },
        {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OTHER,
        11, en_str_Other, FALSE
    },
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        12, en_str_Info, FALSE
    },
    #if ENABLE_AUTO_DQS_Design
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        13, en_str_BIST_TEST, FALSE
    },
    #endif
  #if ENABLE_MFC_6M20
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ROOT,
        13, en_str_6M20_Update, FALSE
    },
   #endif

  #if (ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ROOT,
        13, en_str_6M30_Update, FALSE
    },
   #endif


#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
   {
       EN_DESIGN_PAGE_ROOT,
       EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CIPLUSKEY_UPGRADE,
       14, en_str_CIplusKey_USB_Upgrade, FALSE
   },
#endif
#if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION
   {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OVERSCAN,
        14, en_str_OverScan, FALSE
    },
#endif
#if ENABLE_AUTOTEST
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BMTEST_PAGE,
        15, en_str_BMTEST, FALSE
    },
#endif
#if ENABLE_PIP
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PIP_POP,
        14, en_str_PIPslashPOP, FALSE // original is 14
    },
#endif
#if ENABLE_CI
    {
        EN_DESIGN_PAGE_ROOT,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        16, en_str_CI_Factory_Setting, FALSE
    },
#endif





//==============CI INFORMATION=========================================//
#if ENABLE_CI
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        0, en_str_CIplus_Credential_Mode, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        1, en_str_Performance_Monitor, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        2, en_str_Resource_Manager, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        3, en_str_Application_Information, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        4, en_str_Conditional_Access_Support, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        5, en_str_Host_Control, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        6, en_str_DatedashTime, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        7, en_str_Man_Machine_Interface, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        8, en_str_Low_Speed_Communication, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        9, en_str_Content_Control, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        10, en_str_Host_Language_Control, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        11, en_str_CAM_Upgrade, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        12, en_str_Operate_Profile, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        13, en_str_Specific_Application_Support, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        14, en_str_Application_Man_Machine_Interface, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        15, en_str_Program_Map_Table, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        16, en_str_Host_Service_Shunning, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        17, en_str_Canal_Ready_Authentication, FALSE
    },
    {
        EN_DESIGN_PAGE_CI,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_CI,
        18, en_str_DEFAULT_TXslashRX, FALSE
    },

#endif
/*
    //==ADC ADJUST======================================
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        0, en_str_Mode, FALSE
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        2, en_str_RdashGAIN, FALSE
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        3, en_str_GdashGAIN, FALSE
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        4, en_strB_GainText, FALSE
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        6, en_str_RdashOFFSET, FALSE
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        7, en_str_GdashOffset, FALSE
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        8, en_str_BdashOFFSET, FALSE
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        10,  en_str_ADC_Tune, FALSE
        /// en_strSubAUTOADCText   en_str_ADC_Tune
    },
    {
        EN_DESIGN_PAGE_ADC_ADJUST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_ADC_ADJUST,
        11,  en_str_Phase, FALSE
    },
*/
#if ENABLE_PANEL_BIN
    //==PANEL PARAMETER======================================
    {
        EN_DESIGN_PAGE_PANEL_PARAMETER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PANEL_PARAMETER,
        0, en_str_PanelBinIndex, FALSE
    },
    {
        EN_DESIGN_PAGE_PANEL_PARAMETER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PANEL_PARAMETER,
        1, en_str_PanelDualPort, FALSE
    },
    {
        EN_DESIGN_PAGE_PANEL_PARAMETER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PANEL_PARAMETER,
        2, en_str_PanelSwapPort, FALSE
    },
    {
        EN_DESIGN_PAGE_PANEL_PARAMETER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PANEL_PARAMETER,
        3, en_str_PanelLVDS_TI_MODE, FALSE
    },

    {
        EN_DESIGN_PAGE_PANEL_PARAMETER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PANEL_PARAMETER,
        4, en_str_TiBitMode, FALSE
    },
    {
        EN_DESIGN_PAGE_PANEL_PARAMETER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PANEL_PARAMETER,
        5, en_str_OutputFormatBitMode, FALSE
    },
#endif
#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
    //==WHITE BALANCE PATTERN======================================
    {
        EN_DESIGN_WHITE_BALANCE_PATTERN,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_WHITE_BALANCE_PATTERN,
        0, en_str_WB_TestPattern, FALSE
    },
    {
        EN_DESIGN_WHITE_BALANCE_PATTERN,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_WHITE_BALANCE_PATTERN,
        1, en_str_WB_TestPattern_Value, FALSE
    },
#endif
    //==PICTURE MODE======================================
    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        0, en_str_Picture_Mode, FALSE
    },
    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        1, en_str_Brightness, FALSE
    },
    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        2, en_str_Contrast, FALSE
    },

    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        3, en_str_Color, FALSE
    },
    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        4, en_str_Sharpness, FALSE
    },
    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        5, en_str_Tint, FALSE
    },
  #if ENABLE_DESIGN_POWER_ON_MODE
    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        6, en_str_Backlight, FALSE
    },
  #endif
    {
        EN_DESIGN_PAGE_PICTURE_MODE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PICTURE_MODE,
        7, en_str_COPY_ALL, FALSE
    },

    /*
    //==WHITE BALANCE======================================
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        0, en_str_Source, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        2, en_str_TEMPERATURE, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        3, en_str_RdashGAIN, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        4, en_str_GdashGAIN, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        5, en_strB_GainText, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        7, en_str_RdashOFFSET, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        8, en_str_GdashOffset, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        9, en_str_BdashOFFSET, FALSE
    },
    {
        EN_DESIGN_PAGE_WHITE_BALANCE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_WHITE_BALANCE,
        10, en_str_COPY_ALL, FALSE
    },
    */

    //===PEQ=============================================

    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        0, en_str_FO1dashCoarse_Hz, FALSE
    },
        {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        1, en_str_FO1dashFine, FALSE
    },
    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        2, en_str_FO2dashCoarse_Hz, FALSE
    },
        {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        3, en_str_FO2dashFine, FALSE
    },
    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        4, en_str_FO3dashCoarse_Hz, FALSE
    },
        {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        5, en_str_FO3dashFine, FALSE
    },
    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        6, en_str_Gain_1_db, FALSE
    },
    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        7, en_str_Gain_2_db, FALSE
    },
        {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        8, en_str_Gain_3_db, FALSE
    },
    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        9, en_str_Q_1, FALSE
    },
    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        10, en_str_Q_2, FALSE
    },
    {
        EN_DESIGN_PAGE_PEQ,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PEQ,
        11, en_str_Q_3, FALSE
    },

    //==QMAP ADJUST======================================
    //==QMAP PAGE
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        0, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        1, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        2, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        3, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        4, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        5, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        6, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        7, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        8, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        9, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        10, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        11, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        12, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        13, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        14, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        15, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        16, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        17, Empty, FALSE
    },
    {
        EN_DESIGN_PAGE_QMAP_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_QMAP_PAGE,
        18, Empty, FALSE
    },

    #if ENABLE_PIP
    //==PIP/POP Settings=====================================
    {
        EN_DESIGN_PAGE_PIP_POP,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PIP_POP,
        0, en_str_PIPslashPOP, FALSE
    },
    {
        EN_DESIGN_PAGE_PIP_POP,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_PIP_POP,
        1, en_str_PIP_Border_Width, FALSE
    },
    #endif
    //==Software Information=================================
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        1, en_str_BUILD_TIME, FALSE
    },
#if ENABLE_OAD
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        2, en_str_TV_Version, FALSE
    },
#endif
#if ENABLE_SHOW_PHASE_DESIGN
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        3, en_str_MIU0_DQS0, FALSE
    },
      {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        4, en_str_MIU0_DQS1, FALSE
    },
     #if(ENABLE_MIU_1)
      {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        5, en_str_MIU1_DQS0, FALSE
    },
      {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
       6, en_str_MIU1_DQS1, FALSE
    },
    #endif
    #endif
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        7, en_str_Board, FALSE
    },

    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        8, en_str_Panel, FALSE
    },
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        9, en_str_Main_PQ_Version, FALSE
    },
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        10, en_str_Sub_PQ_Version, FALSE
    },
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        11, en_str_Date, FALSE
    },
    {
        EN_DESIGN_PAGE_SW_INFO_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SW_INFO_PAGE,
        12, en_str_Time, FALSE
    },


    #if ENABLE_AUTOTEST
    //==Benchmark test Information=================================
    {
        EN_DESIGN_PAGE_BMTEST_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BMTEST_PAGE,
        0, en_str_Aeon_Dhrystone, FALSE
    },
    {
        EN_DESIGN_PAGE_BMTEST_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BMTEST_PAGE,
        1, en_str_Mips_Dhrystone, FALSE
    },
    {
        EN_DESIGN_PAGE_BMTEST_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BMTEST_PAGE,
        2, en_str_Aeon_MM_Test, FALSE
    },
    {
        EN_DESIGN_PAGE_BMTEST_PAGE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BMTEST_PAGE,
        3, en_str_Mips_MM_Test, FALSE
    },
    #endif
#if ENABLE_AUTO_DQS_Design
    //==Run-Time BIST TEST===================================
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        0, en_str_BIST_TEST, FALSE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        1, en_str_MIU_0_Phase_Plus_2colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        2, en_str_MIU_0_Phase_Plus_1colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        3, en_str_MIU_0_Phase_Plus_0colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        4, en_str_MIU_0_Phase_Minus_1colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        5, en_str_MIU_0_Phase_Minus_2colon, TRUE
    },
    #if(ENABLE_MIU_1)
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        6, en_str_MIU_1_Phase_Plus_2colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        7, en_str_MIU_1_Phase_Plus_1colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        8, en_str_MIU_1_Phase_Plus_0colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        9, en_str_MIU_1_Phase_Minus_1colon, TRUE
    },
    {
        EN_DESIGN_PAGE_BIST_TEST,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_BIST_TEST,
        10, en_str_MIU_1_Phase_Minus_2colon, TRUE
    },
    #endif
#endif
    //==SSC=============================================
    {
        EN_DESIGN_PAGE_SSC,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_MIU_SSC,
        0, en_str_MIU_SSC, FALSE
    },
    {
        EN_DESIGN_PAGE_SSC,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_LVDS_SSC,
        1, en_str_LVDS_SSC, FALSE
    },
#if URSA_SSC_ENABLE
    {
        EN_DESIGN_PAGE_SSC,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_6MXX_SSC,
        2, en_str_6MXX_SSC, FALSE
    },
#endif
    //==MIU SSC=============================================
    {
        EN_DESIGN_PAGE_MIU_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_MIU_SSC,
        0, en_str_MIU_Enable, FALSE
    },
    {
        EN_DESIGN_PAGE_MIU_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_MIU_SSC,
        1, en_str_MIU_Modulation, FALSE
    },
    {
        EN_DESIGN_PAGE_MIU_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_MIU_SSC,
        2, en_str_MIU_Percentage, FALSE
    },

    //==LVDS SSC=============================================
    {
        EN_DESIGN_PAGE_LVDS_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_LVDS_SSC,
        0, en_str_LVDS_Enable, FALSE
    },
    {
        EN_DESIGN_PAGE_LVDS_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_LVDS_SSC,
        1, en_str_LVDS_Modulation, FALSE
    },
    {
        EN_DESIGN_PAGE_LVDS_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_LVDS_SSC,
        2, en_str_LVDS_Percentage, FALSE
    },
    {
        EN_DESIGN_PAGE_LVDS_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_LVDS_SSC,
        3, en_str_Panel_Swing, FALSE
    },

    //==6MXX SSC=============================================
#if URSA_SSC_ENABLE
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        0, en_str_Ursa_MIU0_Enable, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        1, en_str_MIU0_Modulation, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        2, en_str_MIU0_Percentage, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        3, en_str_Ursa_MIU1_Enable, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        4, en_str_MIU1_Modulation, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        5, en_str_MIU1_Percentage, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        6, en_str_Ursa_LVDS_Enable, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        7, en_str_LVDS_Modulation, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        8, en_str_LVDS_Percentage, FALSE
    },
    {
        EN_DESIGN_PAGE_6MXX_SSC,
        EN_DESIGN_PAGE_SSC, EN_DESIGN_PAGE_6MXX_SSC,
        9, en_str_Panel_Swing, FALSE
    },
#endif
    //==SPECIAL SET=============================================
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        0, en_str_2HOUR_OFF, FALSE
    },
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        1, en_str_WDT, FALSE
    },
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        2, en_str_WHITE_PATTERN, FALSE
    },
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_RESTORE_DEFAULT,
        3, en_str_Restore_Factory_Default, FALSE
    },
    #if ENABLE_PVR
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
       4, en_str_PVR_RECORD_ALL, FALSE
    },
    #endif
    #if ENABLE_DESIGN_POWER_ON_MODE
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        5, en_str_Power, FALSE
    },
    #endif

#if MirrorEnable
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        6, en_str_Mirror_Enable, FALSE
    },
#endif

#if ENABLE_ADJUST_TSCLOCK_PHASE
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        7, en_str_Clock, FALSE
    },
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        8, en_str_Phase, FALSE
    },
#endif

#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
    {
        EN_DESIGN_PAGE_SPECIAL_SET,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_SPECIAL_SET,
        7, en_str_WhiteBalanceTestPattern, FALSE
    },
#endif

    // ===== NON STANDARD ==========
     {
         EN_DESIGN_PAGE_NON_STANDARD,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_VIF,
        0,en_str_VIF,FALSE
     },
     {
         EN_DESIGN_PAGE_NON_STANDARD,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_VD,
        1,en_str_VD,FALSE
     },
     {
         EN_DESIGN_PAGE_NON_STANDARD,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_AUDIO,
        2,en_str_Audio,FALSE
     },

    //==VIF=============================================
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        0, en_str_VIF_AGC_REF, FALSE
    },
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        1, en_str_VIF_CR_KP, FALSE
    },
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        2, en_str_VIF_CR_KI, FALSE
    },
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        3, en_str_VIF_ASIA_SIGNAL_OPTION, FALSE
    },
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        4,en_str_VIF_CLAMPGAIN_GAIN_OV_NEGATIVE , FALSE
    },
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        5, en_str_China_DESCRAMBLER_BOX, FALSE
    },
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        6, en_str_VIF_CR_THR, FALSE
    },
    {
        EN_DESIGN_PAGE_VIF,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VIF,
        7, en_str_VERSION, FALSE
    },

    //==VD=============================================
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        0, en_str_AFEC_D4, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        1, en_str_AFEC_D5_brackers2, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        2, en_str_AFEC_D8_brackers3colon0, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        3, en_str_AFEC_D9_brackers0, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        4, en_str_AFEC_D7_brackers3colon0, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        5, en_str_AFEC_D7_brackers7colon4, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        6, en_str_AFEC_A0A1, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        7, en_str_AFEC_66_brackers7colon6, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        8, en_str_AFEC_6E_brackers7colon4, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        9, en_str_AFEC_6E_brackers3colon0, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        10, en_str_AFEC_43, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        11, en_str_AFEC_44, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        12, en_str_AFEC_CB, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        13, en_str_CF2_ATV, FALSE
    },
    {
        EN_DESIGN_PAGE_VD,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_VD,
        14, en_str_CF2_AV, FALSE
    },

    //==Audio=============================================
    {
        EN_DESIGN_PAGE_AUDIO,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_AUDIO,
        0, en_str_Audio_HIDEV_MODE, FALSE
    },
    {
        EN_DESIGN_PAGE_AUDIO,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_AUDIO,
        1, en_str_AUDIO_NR_THR, FALSE
    },
    {
        EN_DESIGN_PAGE_AUDIO,
        EN_DESIGN_PAGE_NON_STANDARD, EN_DESIGN_PAGE_AUDIO,
        2, en_str_prescale, FALSE
    },

    //==Other=============================================
    {
        // test pattern
        EN_DESIGN_PAGE_OTHER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OTHER,
        0, en_str_test_pattern, FALSE
    },
    {
        // xvycc
        EN_DESIGN_PAGE_OTHER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OTHER,
        1, en_str_xvycc, FALSE
    },
    {
        // initial channel
        EN_DESIGN_PAGE_OTHER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OTHER,
        2, en_str_Initial_Channel, FALSE
    },
    {
        // UART DEBUG
        EN_DESIGN_PAGE_OTHER,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OTHER,
        3, en_str_UART_DEBUG, FALSE
    },
#if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION
  //==Over Scan===============================================
  {
        EN_DESIGN_PAGE_OVERSCAN,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OVERSCAN,
        0, en_str_overscan_reslution, FALSE
    },
    {
        EN_DESIGN_PAGE_OVERSCAN,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OVERSCAN,
        2, en_str_OVERSCANdashHSIZE, FALSE
    },
    {
        EN_DESIGN_PAGE_OVERSCAN,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OVERSCAN,
        3, en_str_OVERSCANdashHPOSITION, FALSE
    },
    {
        EN_DESIGN_PAGE_OVERSCAN,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OVERSCAN,
        4, en_str_OVERSCANdashVSIZE, FALSE
    },
    {
        EN_DESIGN_PAGE_OVERSCAN,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_OVERSCAN,
        5, en_str_OVERSCANdashVPOSITION, FALSE
    },
#endif
#if ENABLE_NONLINEAR_CURVE
 //==NONLINEAR CURVE======================================
    {
        EN_DESIGN_PAGE_NONLINEAR_CURVE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NONLINEAR_CURVE,
        0, en_str_Mode, FALSE
    },
    {
        EN_DESIGN_PAGE_NONLINEAR_CURVE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NONLINEAR_CURVE,
        1, en_str_OSD_0, FALSE
    },
    {
        EN_DESIGN_PAGE_NONLINEAR_CURVE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NONLINEAR_CURVE,
        2, en_str_OSD_25, FALSE
    },
    {
        EN_DESIGN_PAGE_NONLINEAR_CURVE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NONLINEAR_CURVE,
        3, en_str_OSD_50, FALSE
    },
    {
        EN_DESIGN_PAGE_NONLINEAR_CURVE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NONLINEAR_CURVE,
        4, en_str_OSD_75, FALSE
    },
    {
        EN_DESIGN_PAGE_NONLINEAR_CURVE,
        EN_DESIGN_PAGE_ROOT, EN_DESIGN_PAGE_NONLINEAR_CURVE,
        5, en_str_OSD_100, FALSE
    },
 #endif


};

#if(LOG_DESIGNMENU_SHOWITEM)
#define GET_DESIGNMENU_SHOWITEM(stuMenuItem)            GetDesignMenuItemIndex(stuMenuItem)

// ----------------------------------------------------------
// 功能说明: 获取工厂菜单项的索引
// 参数说明:
//    stuMenuItem: 工厂菜单项目DESIGN_MENU_ITEM
// 返回说明:
//    返回菜单项从0开始的索引值
// 附加说明:
//    约定: 各页的首项的索引都为0
// ----------------------------------------------------------
static U8 GetDesignMenuItemIndex(DESIGN_MENU_ITEM stuMenuItem)
{
    U8 i = 0;
    U8 ucMenuIndex = 0;
    //printf("GetDesignMenuItemIndex(%bu)\n", (U8)stuMenuItem.u8ShowItem);

    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
        if (_DesignMenuItem[i].u8ShowItem == 0) //    约定: 各页的首项的索引都为0
            ucMenuIndex = 0;
        else
            ucMenuIndex ++;

        // 特殊页面在此作特殊处理
        if(_DesignMenuItem[i].eCurPage == EN_DESIGN_PAGE_SW_INFO_PAGE && _DesignMenuItem[i].u8ShowItem == 1)
            ucMenuIndex = 1; // EN_DESIGN_PAGE_SW_INFO_PAGE页面: 从1开始的，首项原先已经有显示内容.

        if (_DesignMenuItem[i].eCurPage == stuMenuItem.eCurPage && _DesignMenuItem[i].u8ShowItem == stuMenuItem.u8ShowItem)
        {
            // printf("ucMenuIndex = %bu\n", ucMenuIndex);
            return ucMenuIndex;
        }
    }

    printf("--WARNING--: DESIGN_MENU_ITEM inexistence!\n");
    return 0xFF; // 不存在的页面
}

// ----------------------------------------------------------
// 功能说明: 获取_DesignMenuItem数组的u8ShowItem值
// 参数说明:
//    enuCurPage: 当前页面对象DESIGN_MENU_PAGE
//    ucItemIndex: 菜单项从0开始的索引
// 返回说明:
//    返回_DesignMenuItem数组的u8ShowItem值
// 附加说明:
//    约定: 各页的首项的索引都为0
// ----------------------------------------------------------
static U16 GetDesignMenuItemu8ShowItem(DESIGN_MENU_PAGE enuCurPage, U8 ucItemIndex)
{
    U8 i = 0;
    U8 ucMenuItemuIndex = 0;

    // 特殊页面在此作特殊处理
    if(enuCurPage == EN_DESIGN_PAGE_SW_INFO_PAGE)
        ucMenuItemuIndex = 1; // EN_DESIGN_PAGE_SW_INFO_PAGE页面: 从1开始的，首先有显示内容.
    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
        if(_DesignMenuItem[i].eCurPage == enuCurPage)
        {
            if (ucMenuItemuIndex == ucItemIndex)
            {
                return _DesignMenuItem[i].u8ShowItem;
            }
            ucMenuItemuIndex ++;
        }
    }

    printf("--WARNING--: DESIGN_MENU_PAGE or ucItemIndex inexistence!\n");
    return 0xFF; // 不存在的页面
}

// ----------------------------------------------------------
// 功能说明: 获取_DesignMenuItem数组的16StringID值
// 参数说明:
//    enuCurPage: 当前页面对象DESIGN_MENU_PAGE
//    ucItemIndex: 菜单项从0开始的索引
// 返回说明:
//    返回_DesignMenuItem数组的16StringID值
// 附加说明:
//    约定: 各页的首项的索引都为0
// ----------------------------------------------------------
static U16 GetDesignMenuItemu16StringID(DESIGN_MENU_PAGE enuCurPage, U8 ucItemIndex)
{
    U8 i = 0;
    U8 ucMenuItemuIndex = 0;

    // 特殊页面在此作特殊处理
    if(enuCurPage == EN_DESIGN_PAGE_SW_INFO_PAGE)
        ucMenuItemuIndex = 1; // EN_DESIGN_PAGE_SW_INFO_PAGE页面: 从1开始的，首先有显示内容.
    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
        if(_DesignMenuItem[i].eCurPage == enuCurPage)
        {
            if (ucMenuItemuIndex == ucItemIndex)
            {
                return _DesignMenuItem[i].u16StringID;
            }
            ucMenuItemuIndex ++;
        }
    }

    printf("--WARNING--: DESIGN_MENU_PAGE or ucItemIndex inexistence!\n");
    return 0xFF; // 不存在的页面
}

// ----------------------------------------------------------
// 功能说明: 获取工厂菜单本页在前一页菜单的菜单项的索引
// 参数说明:
//    enuCurPage: 当前页面对象DESIGN_MENU_PAGE
// 返回说明:
//    返回本页面在前一页面的菜单项从0开始的索引值
// 附加说明:
//    约定: 各页的首项的索引都为0
// ----------------------------------------------------------
static U8 GetDesignPreMenuItemIndex(DESIGN_MENU_PAGE enuCurPage)
{
    U8 i = 0;
    U8 ucMenuIndex = 0;
   // printf("GetDesignPreMenuItemIndex(%bu)\n", (U8)enuCurPage);

    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
        if (_DesignMenuItem[i].u8ShowItem == 0) //    约定: 各页的首项的索引都为0
            ucMenuIndex = 0;
        else
            ucMenuIndex ++;

        // 特殊页面在此作特殊处理
        if(_DesignMenuItem[i].eCurPage == EN_DESIGN_PAGE_SW_INFO_PAGE && _DesignMenuItem[i].u8ShowItem == 1)
            ucMenuIndex = 1; // EN_DESIGN_PAGE_SW_INFO_PAGE页面: 从1开始的，首项原先已经有显示内容.

        if (_DesignMenuItem[i].eNextPage == enuCurPage)
        {
            // printf("ucMenuIndex = %bu\n", ucMenuIndex);
            return ucMenuIndex;
        }
    }

    printf("--WARNING--: ePrevPage inexistence!\n");
    return 0xFF; // 不存在前一页面
}
#endif
//modify for complie error
#if 0//ENABLE_VD_PACH_IN_CHINA
static U8 Get_VIF_KP_KI_MapToIndex(U16 KP_KI_DATA)
{
    U8 i;
    for (i = 0; i < COUNTOF(VIF_KP_KI_DATA); i++)
    {
        if (KP_KI_DATA == VIF_KP_KI_DATA[i])
        {
            return i;
        }
    }
    return 0;
}
static U8 Get_AFEC_A0_A1_MapToIndex(U16 A0_A1_DATA)
{
    U8 i;
    for (i = 0; i < COUNTOF(AFEC_A0_A1_DATA); i++)
    {
        if (A0_A1_DATA == AFEC_A0_A1_DATA[i])
        {
            return i;
        }
    }
    return 0;
}

#endif
static void _MApp_ZUI_ACT_DesignMenuInitPage(DESIGN_MENU_PAGE page)
{
    printf("===== [%s, %d, %s] =====\n", __FILE__, __LINE__, __FUNCTION__);
    BOOLEAN bFirst = TRUE;
    U8 i;
  #if ENABLE_AUTO_DQS_Design
    if(page == EN_DESIGN_PAGE_BIST_TEST)
    {
        _BIST_TEST_MODE = EN_BIST_TEST_UI_START;
    }
  #endif
    MApp_ZUI_API_InvalidateWindow(HWND_DESIGN_MENU_TITLE);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_LIST, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BAR, SW_HIDE);
    if(page == EN_DESIGN_PAGE_QMAP_PAGE)
    {
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_SW_INFO, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_INPUT_INFO, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP1, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP2, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BOARD_INFO, SW_HIDE);
    }

    #if ENABLE_CI
    else if(page == EN_DESIGN_PAGE_CI)
    {
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_SW_INFO, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_INPUT_INFO, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP1, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP2, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BOARD_INFO, SW_HIDE);
    }
    #endif

    else if(page == EN_DESIGN_PAGE_PEQ)
    {
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_SW_INFO, SW_HIDE);
    //    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_INPUT_INFO, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP1, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP2, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BOARD_INFO, SW_HIDE);
    }
    else if (page == EN_DESIGN_PAGE_SW_INFO_PAGE)
    {
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_SW_INFO, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_INPUT_INFO, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP1, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP2, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BOARD_INFO, SW_HIDE);
    }
    else if (page == EN_DESIGN_RESTORE_DEFAULT)
    {
        extern BOOLEAN MApp_ZUI_ACT_ExecuteMenuCommonDialogAction(U16 act);
        extern COMMON_DLG_MODE _eCommonDlgMode;
        MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
        _enTargetOSDPageState = STATE_OSDPAGE_CLEAN_UP;
        _eCommonDlgMode = EN_COMMON_DLG_MODE_DESIGN_RESET;
        MApp_ZUI_ACT_ExecuteMenuCommonDialogAction(EN_EXE_DESIGN_RESET);
        return;
    }
    else if (page == EN_DESIGN_GOTO_FACTORY_MENU)
    {
        extern BOOLEAN MApp_ZUI_ACT_ExecuteInputSourceAction(U16 act);
        MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_GOTO_FACTORY_MENU);
        return;
    }
    else
    {
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_SW_INFO, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_INPUT_INFO, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP1, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP2, SW_HIDE);
        if(page == EN_DESIGN_PAGE_ROOT)
        {
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BOARD_INFO, SW_SHOW);
        }
        else
        {
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BOARD_INFO, SW_HIDE);
        }
    }
    #if ENABLE_VD_PACH_IN_CHINA
    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
        if(_DesignMenuItem[i].u16StringID == en_str_VIF_PROGRAMMABLE_DELAY)
           break;
    }
    if(i<COUNTOF(_DesignMenuItem))
    {
        if(G_DESIGN_SETTING.stVDSetting.China_DESCRAMBLER_BOX == 7)
        {
            _DesignMenuItem[i].bDisable = FALSE;
        }
        else
        {
            DRV_VIF_SetParameter(VIF_PARA_SET_DESCRAMBLERBOX_DELAY, 0, sizeof(DWORD));
            _DesignMenuItem[i].bDisable = TRUE;
        }
    }
    #endif
    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
        if (_DesignMenuItem[i].eCurPage == page)
        {
          #if(LOG_DESIGNMENU_SHOWITEM)
            HWND hwnd = _MApp_ZUI_ACT_DesignMenuIndexMapToWindow(GET_DESIGNMENU_SHOWITEM(_DesignMenuItem[i]));
          #else
            HWND hwnd = _MApp_ZUI_ACT_DesignMenuIndexMapToWindow(_DesignMenuItem[i].u8ShowItem);
          #endif
            MApp_ZUI_API_ShowWindow(hwnd, SW_SHOW);

            if (_DesignMenuItem[i].bDisable)
            {
                MApp_ZUI_API_EnableWindow(hwnd, FALSE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(hwnd, TRUE);
                if (bFirst)
                {
                    bFirst = FALSE;
                    MApp_ZUI_API_SetFocus(hwnd);
                }
            }
        }
    }
    if (bFirst)
    {
        MApp_ZUI_API_SetFocus(HWND_INVALID); //no focus...
    }
    _eDesignMenuPage = page;
    printf("_eFactoryMenuPage = %d\n", _eDesignMenuPage);
    g_ADCCalibrationResult = FALSE;
}
/*
static void _MApp_ZUI_ACT_DesignMenuPrePageFocusItem(DESIGN_MENU_PAGE prePage, DESIGN_MENU_PAGE curPage)
{
    U8 i;
    MApp_ZUI_API_InvalidateWindow(HWND_DESIGN_MENU_TITLE);
    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_LIST, SW_HIDE);

    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
        if (_DesignMenuItem[i].eCurPage == prePage)
        {
            HWND hwnd = _MApp_ZUI_ACT_DesignMenuIndexMapToWindow(      _DesignMenuItem[i].u8ShowItem);
            MApp_ZUI_API_ShowWindow(hwnd, SW_SHOW);
            if (_DesignMenuItem[i].bDisable)
            {
                MApp_ZUI_API_EnableWindow(hwnd, FALSE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(hwnd, TRUE);
                if (_DesignMenuItem[i].eNextPage== curPage)
                {
                    MApp_ZUI_API_SetFocus(hwnd);
                }
            }
        }
    }
    _eDesignMenuPage = prePage;
}
*/
static void _MApp_ZUI_ACT_DesignMenuNextPage(U8 u8Item)
{
    U8 i;
    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
      #if(LOG_DESIGNMENU_SHOWITEM)
        if (_DesignMenuItem[i].eCurPage == _eDesignMenuPage && GET_DESIGNMENU_SHOWITEM(_DesignMenuItem[i]) == u8Item)
      #else
        if (_DesignMenuItem[i].eCurPage == _eDesignMenuPage &&
            _DesignMenuItem[i].u8ShowItem == u8Item)
      #endif
        {
            if (_eDesignMenuPage != _DesignMenuItem[i].eNextPage)
            {
                if( _DesignMenuItem[i].eNextPage == EN_DESIGN_PAGE_PEQ)
                {
                    if( !ST_AUDIO_PEQ.u8_PEQOnOff)
                    {
                        return;
                    }
                }
                else if(_DesignMenuItem[i].eNextPage == EN_DESIGN_RESTORE_DEFAULT)
                {
                    _eDesignMenuPage = EN_DESIGN_RESTORE_DEFAULT;
                    return;
                }

                _MApp_ZUI_ACT_DesignMenuInitPage(_DesignMenuItem[i].eNextPage);
            }
            return;
        }
    }
}

static void _MApp_ZUI_ACT_DesignMenuPrevPage(U8 u8Item)
{
    U8 i;
    for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
    {
      #if(LOG_DESIGNMENU_SHOWITEM)
        if (_DesignMenuItem[i].eCurPage == _eDesignMenuPage && GET_DESIGNMENU_SHOWITEM(_DesignMenuItem[i]) == u8Item)
      #else
        if (_DesignMenuItem[i].eCurPage == _eDesignMenuPage &&
            _DesignMenuItem[i].u8ShowItem == u8Item)
      #endif
        {
            if (_eDesignMenuPage != _DesignMenuItem[i].ePrevPage)
            {
                _MApp_ZUI_ACT_DesignMenuInitPage(_DesignMenuItem[i].ePrevPage);
               // _MApp_ZUI_ACT_DesignMenuPrePageFocusItem(_DesignMenuItem[i].ePrevPage, _DesignMenuItem[i].eCurPage);
            }
            return;
        }
    }
}

static void _MApp_ZUI_ACT_QMAPPrevPage(void)
{

    DESIGN_MENU_PAGE _ePrevPage = EN_DESIGN_PAGE_QMAP_PAGE;
    U8 u8ShowItem = 0;

    if(_u8IPIndex == (_u8IPNumber-1))
    {
        u8ShowItem = _u8IPIndex%(COUNTOF(_DesignMenuItemHwndList));
    }
    else
    {
        u8ShowItem = (COUNTOF(_DesignMenuItemHwndList)-1);
    }

    _MApp_ZUI_ACT_DesignMenuInitPage(_ePrevPage);
    MApp_ZUI_API_SetFocus(_DesignMenuItemHwndList[u8ShowItem]);
    return;
}

static void _MApp_ZUI_ACT_QMAPNextPage(void)
{
    DESIGN_MENU_PAGE _eNextPage = EN_DESIGN_PAGE_QMAP_PAGE;

    _MApp_ZUI_ACT_DesignMenuInitPage(_eNextPage);
    return;
}




/*
#if (ENABLE_NONLINEAR_CURVE)
static void _MApp_ZUI_ACT_DesignMenu_ChangeDataInputSource(E_DATA_INPUT_SOURCE eDataInputSource)
{
    //from function MApp_UiMenuFunc_ChangeDataInputSource()
    switch(eDataInputSource)
    {
        default:
  #if ENABLE_DTV
        case DATA_INPUT_SOURCE_DTV:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;//Thomas 20150714 to do
            break;
  #endif
        case DATA_INPUT_SOURCE_ATV:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
            break;
    #if (INPUT_AV_VIDEO_COUNT >= 1)
        case DATA_INPUT_SOURCE_AV:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV;
            break;
    #endif
    #if (INPUT_AV_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_AV2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV2;
            break;
    #endif
    #if (INPUT_AV_VIDEO_COUNT >= 3)
        case DATA_INPUT_SOURCE_AV3:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV3;
            break;
    #endif
    #if (INPUT_SCART_VIDEO_COUNT >= 1)
        case DATA_INPUT_SOURCE_SCART:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART;
            break;
    #endif
    #if (INPUT_SCART_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_SCART2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART2;
            break;
    #endif
    #if(ENABLE_SCART_SVIDEO)

    case DATA_INPUT_SOURCE_SVIDEO:
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART;
        break;


    #elif    (INPUT_SV_VIDEO_COUNT >= 1)
        case DATA_INPUT_SOURCE_SVIDEO:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SVIDEO;
            break;
    #endif


    #if (INPUT_SV_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_SVIDEO2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SVIDEO2;
            break;
    #endif
    #if    (INPUT_YPBPR_VIDEO_COUNT >= 1)
        case DATA_INPUT_SOURCE_COMPONENT:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_COMPONENT;
            break;
    #endif

    #if    (INPUT_YPBPR_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_COMPONENT2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_COMPONENT2;
            break;
    #endif

        case DATA_INPUT_SOURCE_RGB:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_RGB;
            break;

    #if (INPUT_HDMI_VIDEO_COUNT > 0)
        case DATA_INPUT_SOURCE_HDMI:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI;
            break;
    #endif
    #if    (INPUT_HDMI_VIDEO_COUNT >= 2)
        case DATA_INPUT_SOURCE_HDMI2:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI2;
            break;
    #endif
    #if    (INPUT_HDMI_VIDEO_COUNT >= 3)
        case DATA_INPUT_SOURCE_HDMI3:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI3;
            break;
    #endif
    #if    (INPUT_HDMI_VIDEO_COUNT >= 4)
        case DATA_INPUT_SOURCE_HDMI4:
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI4;
            break;
    #endif
    }

    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);

    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        //MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
    }
    else if (IsAnyTVSourceInUse())
    {
    }
    else
    {
        //MApp_ChannelChange_EnableAV();
    }
}
#endif
*/
typedef enum
{
    EN_REDRAW_NONE,
    EN_REDRAW_ITEM,
    EN_REDRAW_LIST,
} REDRAW_TYPE;

static REDRAW_TYPE _MApp_ZUI_ACT_DesignMenuDecIncValue(U8 u8Item, BOOLEAN bInc)
{
#if ENABLE_PANEL_BIN
    U8 _u8PanelBinIndex;
#endif

#if (LOG_DESIGNMENU_SHOWITEM)
    u8Item = GetDesignMenuItemu8ShowItem(_eDesignMenuPage, u8Item);
#endif

    switch(_eDesignMenuPage)
    {
        case EN_DESIGN_PAGE_ROOT:
            switch(u8Item)
            {
                case 10:
                    ST_AUDIO_PEQ.u8_PEQOnOff = !ST_AUDIO_PEQ.u8_PEQOnOff;
                    return EN_REDRAW_ITEM;
            }
            break;


    #if ENABLE_CI

        case EN_DESIGN_PAGE_CI:
            switch(u8Item)
            {
                case 0:
                    stGenSetting.g_CISetting.UCredential_Mode = !stGenSetting.g_CISetting.UCredential_Mode;
                    break;
                case 1:
                    stGenSetting.g_CISetting.UPerformance_Monitor = !stGenSetting.g_CISetting.UPerformance_Monitor;
                    break;
                case 2:
                    stGenSetting.g_CISetting.UResource_Manager = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UResource_Manager, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_RM,(U8)stGenSetting.g_CISetting.UResource_Manager);
                    break;
                case 3:
                    stGenSetting.g_CISetting.UApplication_Information = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UApplication_Information, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_APPINFO,stGenSetting.g_CISetting.UApplication_Information);
                    break;
                case 4:
                    stGenSetting.g_CISetting.UConditional_Access_Support = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UConditional_Access_Support, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_CAS,stGenSetting.g_CISetting.UConditional_Access_Support);
                    break;
                case 5:
                    stGenSetting.g_CISetting.UHost_Control = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UHost_Control, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_HC,stGenSetting.g_CISetting.UHost_Control);
                    break;
                case 6:
                    stGenSetting.g_CISetting.UDate_Time = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UDate_Time, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_DT,stGenSetting.g_CISetting.UDate_Time);
                    break;
                case 7:
                    stGenSetting.g_CISetting.UMan_Machine_Interface = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UMan_Machine_Interface, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_MMI,stGenSetting.g_CISetting.UMan_Machine_Interface);
                    break;
                case 8:
                    stGenSetting.g_CISetting.ULow_Speed_Communication = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.ULow_Speed_Communication, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_LSC,stGenSetting.g_CISetting.ULow_Speed_Communication);
                    break;
                case 9:
                    stGenSetting.g_CISetting.UContent_Control = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UContent_Control, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_CC,stGenSetting.g_CISetting.UContent_Control);
                    break;
                case 10:
                    stGenSetting.g_CISetting.UHost_Language_Control = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UHost_Language_Control, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_HLC,stGenSetting.g_CISetting.UHost_Language_Control);
                    break;
                case 11:
                    stGenSetting.g_CISetting.UCAM_Upgrade = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UCAM_Upgrade, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_CU,stGenSetting.g_CISetting.UCAM_Upgrade);
                    break;
                case 12:
                    stGenSetting.g_CISetting.UOperate_Profile = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UOperate_Profile, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_OP,stGenSetting.g_CISetting.UOperate_Profile);
                    break;
                case 13:
                    stGenSetting.g_CISetting.USpecific_Application_Support = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.USpecific_Application_Support, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_SAS,stGenSetting.g_CISetting.USpecific_Application_Support);
                    break;
                case 14:
                    stGenSetting.g_CISetting.UApplication_Man_Machine_Interface = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UApplication_Man_Machine_Interface, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_APPMMI,stGenSetting.g_CISetting.UApplication_Man_Machine_Interface);
                    break;
                case 15:
                    stGenSetting.g_CISetting.UProgram_Map_Table = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UProgram_Map_Table, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_PMT,stGenSetting.g_CISetting.UProgram_Map_Table);
                    break;
                case 16:
                    stGenSetting.g_CISetting.UHost_Service_Shunning = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UHost_Service_Shunning, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_HSS,stGenSetting.g_CISetting.UHost_Service_Shunning);
                    break;
                case 17:
                    stGenSetting.g_CISetting.UCanal_Ready_Authentication = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UCanal_Ready_Authentication, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_AUTH,stGenSetting.g_CISetting.UCanal_Ready_Authentication);
                    break;
                case 18:
                    stGenSetting.g_CISetting.UDEFAULT = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_CISetting.UDEFAULT, 0, 4, 1);
                    msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_DEFAULT,stGenSetting.g_CISetting.UDEFAULT);
                    break;
            }
            MApp_SaveGenSetting();
            return EN_REDRAW_LIST;
            break;

    #endif // #if ENABLE_CI


    #if ENABLE_PANEL_BIN
        case EN_DESIGN_PAGE_PANEL_PARAMETER:
            _u8PanelBinIndex = G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex;
            G_FACTORY_SETTING.stFacPnlSetting.bUpdated[_u8PanelBinIndex] = 1;
            switch(u8Item)
            {
                case 0:
                    return EN_REDRAW_LIST;

                case 1:
                    G_FACTORY_SETTING.stFacPnlSetting.m_bPanelDualPort[_u8PanelBinIndex] =
                    (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, G_FACTORY_SETTING.stFacPnlSetting.m_bPanelDualPort[_u8PanelBinIndex], 0, 1, 1);
                    return EN_REDRAW_ITEM;

                case 2:
                    G_FACTORY_SETTING.stFacPnlSetting.m_bPanelSwapPort[_u8PanelBinIndex] =
                    (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, G_FACTORY_SETTING.stFacPnlSetting.m_bPanelSwapPort[_u8PanelBinIndex], 0, 1, 1);
                    return EN_REDRAW_ITEM;

                case 3:
                    G_FACTORY_SETTING.stFacPnlSetting.m_bPanelLVDS_TI_MODE[_u8PanelBinIndex] =
                    (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, G_FACTORY_SETTING.stFacPnlSetting.m_bPanelLVDS_TI_MODE[_u8PanelBinIndex], 0, 1, 1);
                    return EN_REDRAW_ITEM;

                case 4:
                    G_FACTORY_SETTING.stFacPnlSetting.m_ucTiBitMode[_u8PanelBinIndex] =
                    (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, G_FACTORY_SETTING.stFacPnlSetting.m_ucTiBitMode[_u8PanelBinIndex], 0, 2, 1);
                    return EN_REDRAW_ITEM;

                case 5:
                    G_FACTORY_SETTING.stFacPnlSetting.m_ucOutputFormatBitMode[_u8PanelBinIndex] =
                    (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, G_FACTORY_SETTING.stFacPnlSetting.m_ucOutputFormatBitMode[_u8PanelBinIndex], 0, 1, 1);
                    return EN_REDRAW_ITEM;

            }
            break;
    #endif // #if ENABLE_PANEL_BIN



    #if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
    case EN_DESIGN_WHITE_BALANCE_PATTERN:
        switch(u8Item)
        {
            case 0:
                u16WhiteBalancePatternValue = (G_FACTORY_SETTING.stFacWBPatternSetting.u8WBPatternValue*(PATTERN_MAX_VALUE_TO_REG-PATTERN_MIN_VALUE_TO_REG)+50)/100+PATTERN_MIN_VALUE_TO_REG;
                if(G_FACTORY_SETTING.stFacWBPatternSetting.enWBPattern == EN_WB_PATTERN_OFF)
                {
                    G_FACTORY_SETTING.stFacWBPatternSetting.enWBPattern = EN_WB_PATTERN_ON;
                }
                else
                {
                    G_FACTORY_SETTING.stFacWBPatternSetting.enWBPattern = EN_WB_PATTERN_OFF;
                }

                if(G_FACTORY_SETTING.stFacWBPatternSetting.enWBPattern)
                {
                    MApi_XC_ACE_PicSetContrast(MAIN_WINDOW,TRUE,0);
                    MApi_XC_ACE_PicSetBrightnessPrecise(MAIN_WINDOW,u16WhiteBalancePatternValue,u16WhiteBalancePatternValue,u16WhiteBalancePatternValue);
                }
                else
                {
                    // Restore default contrast and brightness
                    MApp_XC_PQ_Set_Contrast( MAIN_WINDOW, FALSE);
                    MApp_XC_PQ_Set_Brightness(MAIN_WINDOW, TRUE);
                }

                return EN_REDRAW_ITEM;

            case 1:
                if(G_FACTORY_SETTING.stFacWBPatternSetting.enWBPattern == EN_WB_PATTERN_OFF)
                {
                    return EN_REDRAW_ITEM;
                }
                else
                {
                    G_FACTORY_SETTING.stFacWBPatternSetting.u8WBPatternValue =
                    MApp_ZUI_ACT_DecIncValue(bInc, G_FACTORY_SETTING.stFacWBPatternSetting.u8WBPatternValue, 0, 100, 1);
                    u16WhiteBalancePatternValue = (G_FACTORY_SETTING.stFacWBPatternSetting.u8WBPatternValue*(PATTERN_MAX_VALUE_TO_REG-PATTERN_MIN_VALUE_TO_REG)+50)/100+PATTERN_MIN_VALUE_TO_REG;

                    MApi_XC_ACE_PicSetContrast(MAIN_WINDOW,TRUE,0);
                    MApi_XC_ACE_PicSetBrightnessPrecise(MAIN_WINDOW,u16WhiteBalancePatternValue,u16WhiteBalancePatternValue,u16WhiteBalancePatternValue);

                    return EN_REDRAW_ITEM;
                }
        }
        break;
    #endif
        case EN_DESIGN_PAGE_PICTURE_MODE:
            switch(u8Item)
            {
                case 0:  // picture mode
                    ST_VIDEO.ePicture = (EN_MS_PICTURE)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, ST_VIDEO.ePicture, PICTURE_MIN, PICTURE_NUMS-1, 1);
                    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    MApp_SetPictureMode(MAIN_WINDOW, TRUE);  //MApp_PicSetPicture( (T_MS_PICTURE *) &ST_PICTURE, SYS_INPUT_SOURCE_TYPE);
                    return EN_REDRAW_ITEM;

                case 1: //from case MAPP_UIMENUFUNC_SUB_BC_ADJUST_SUB_BRIGHTNES:
                    ST_PICTURE.u8Brightness =
                        (U8)MApp_ZUI_ACT_DecIncValue(bInc, ST_PICTURE.u8Brightness, 0, 100, 1);

                    MApp_SaveSubColorSetting(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));

                #if 1
                    MApp_XC_PQ_Set_Brightness(MAIN_WINDOW, TRUE);
                #else
                    MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW,
                                                            MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_R),
                                                            MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_G),
                                                            MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_B));
                #endif

                    return EN_REDRAW_ITEM;

                case 2: //from case MAPP_UIMENUFUNC_SUB_BC_ADJUST_SUB_CONTRAST:

                    ST_PICTURE.u8Contrast =
                       (U8) MApp_ZUI_ACT_DecIncValue(bInc, ST_PICTURE.u8Contrast, 0, 100, 1);

                    MApp_SaveSubColorSetting(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));

                #if 1
                    MApp_XC_PQ_Set_Contrast(MAIN_WINDOW, TRUE);
                #else
                    MApi_XC_ACE_PicSetContrast(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), MApp_Scaler_FactoryContrast(msAPI_Mode_PictureContrastN100toReallyValue(ST_PICTURE.u8Contrast),ST_SUBCOLOR.u8SubContrast));
                #endif

                    return EN_REDRAW_ITEM;

                case 3:

                    ST_PICTURE.u8Saturation = MApp_ZUI_ACT_DecIncValue(
                        bInc,ST_PICTURE.u8Saturation, 0, 100, 1);

                #if 1 // Use new API
                    MApp_XC_PQ_Set_Saturation(MAIN_WINDOW, TRUE);
                #else
                    MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(ST_PICTURE.u8Saturation) );
                #endif
                    return EN_REDRAW_ITEM;
                case 4:

                    ST_PICTURE.u8Sharpness = MApp_ZUI_ACT_DecIncValue(
                        bInc,ST_PICTURE.u8Sharpness, 0, 100, 1);
                    MApi_XC_ACE_PicSetSharpness( MAIN_WINDOW, msAPI_Mode_PictureSharpnessN100toReallyValue(ST_PICTURE.u8Sharpness) );

                    return EN_REDRAW_ITEM;
                case 5:

                    ST_PICTURE.u8Hue = MApp_ZUI_ACT_DecIncValue(
                        bInc,ST_PICTURE.u8Hue, 0, 100, 1);
                    MApi_XC_ACE_PicSetHue( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), msAPI_Mode_PictureHueN100toReallyValue(ST_PICTURE.u8Hue) );

                    return EN_REDRAW_ITEM;
                case 6:

                    ST_PICTURE.u8Backlight = MApp_ZUI_ACT_DecIncValue(
                        bInc,ST_PICTURE.u8Backlight, 0, 100, 1);
                    MApi_PNL_SetBackLight(ENABLE);

                    return EN_REDRAW_ITEM;
                case 7: //from case MAPP_UIMENUFUNC_SUB_BC_ADJUST_COPY_ALL:
                    MApp_CopySubColorDataToAllInput();

                    return EN_REDRAW_LIST;
            }
            break;


            case EN_DESIGN_PAGE_QMAP_PAGE:
            {
                U8 u8IPIdx, u8TabIdx, u8IPNum, u8TabNum;

                u8IPIdx = _u8IPIndex;
                u8IPNum = _u8IPNumber;
                if(u8IPIdx < u8IPNum)
                {
                    u8TabNum = (U8)MDrv_PQ_GetTableNum(PQ_MAIN_WINDOW, (U16)u8IPIdx);
                    //printf("IP:%u [%s], tabnum=%u\n", u8IPIdx, MDrv_PQ_GetIPName(u8IPIdx), u8TabNum);

                    u8TabIdx = (U8)MDrv_PQ_GetCurrentTableIndex(PQ_MAIN_WINDOW, (U16)u8IPIdx);
                    //printf(">>> TAB[%bu] <<<\n", u8TabIdx);
                    if(bInc)
                    {
                        u8TabIdx++;
                        if(u8TabIdx >= u8TabNum)
                        {
                            u8TabIdx = 0;
                        }
                    }
                    else
                    {
                        if(u8TabIdx == 0)
                        {
                            u8TabIdx = u8TabNum - 1;
                        }
                        else
                        {
                            u8TabIdx--;
                        }
                    }
                    //printf(">>>=== ID[%bu]  TAB[%bu] ===<<<\n", u8IPIdx, u8TabIdx);
                    MDrv_PQ_LoadTable(PQ_MAIN_WINDOW, (U16)u8TabIdx, (U16)u8IPIdx);
                    return EN_REDRAW_ITEM;
                    //printf("TAB:%u [%s]\n", u8TabIdx,
                    //(u8TabIdx == PQ_IP_NULL) ? "null" : MDrv_PQ_GetTableName(u8IPIdx, u8TabIdx));
                }
            }
            break;


    #if ENABLE_PIP
        case EN_DESIGN_PAGE_PIP_POP:
            switch(u8Item)
            {
                case 0:
                {
                    if(stGenSetting.g_stPipSetting.bPipEnable)
                    {
                        if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)
                        {
                            stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
                            MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
                        }
                        UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
                        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
                        if((MApp_Get_PIPMode() == EN_PIP_MODE_POP) ||(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL))
                        {
                            MS_WINDOW_TYPE stPOPMainWin;
                            stPOPMainWin.x = 0;
                            stPOPMainWin.y = 0;
                            stPOPMainWin.width = PANEL_WIDTH;
                            stPOPMainWin.height = PANEL_HEIGHT;
                            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, ENABLE, 0, MAIN_WINDOW);
                            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, ENABLE, 0, SUB_WINDOW);
                            MApp_Scaler_SetWindow(
                            NULL,
                            NULL,
                            NULL,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio,
                            SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                            MAIN_WINDOW);
                            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, DISABLE, 0, MAIN_WINDOW);
                            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, DISABLE, 0, SUB_WINDOW);
                        }
                    }
                    stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
                    stGenSetting.g_stPipSetting.bPipEnable = (BOOLEAN)!stGenSetting.g_stPipSetting.bPipEnable;
                    return EN_REDRAW_ITEM;
                }
                break;
                case 1:
                {
                    stGenSetting.g_stPipSetting.u8BorderWidth =
                        (U16)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)stGenSetting.g_stPipSetting.u8BorderWidth, 0x1, 0xA, 1);
                    //set sub window border color as yellow temporarily
                    MApi_XC_SetBorderFormat( stGenSetting.g_stPipSetting.u8BorderWidth, stGenSetting.g_stPipSetting.u8BorderWidth<<4, stGenSetting.g_stPipSetting.u8BorderWidth, stGenSetting.g_stPipSetting.u8BorderWidth<<4, 0xFC, SUB_WINDOW );
                    return EN_REDRAW_ITEM;
                }
                break;
            }
            break;
    #endif // #if ENABLE_PIP


        case EN_DESIGN_PAGE_SW_INFO_PAGE:
            switch(u8Item)
            {

            }
            break;

    #if ENABLE_AUTOTEST
        case EN_DESIGN_PAGE_BMTEST_PAGE:
            switch(u8Item)
            {

            }
            break;
    #endif

    #if ENABLE_AUTO_DQS_Design
        case EN_DESIGN_PAGE_BIST_TEST:
            switch(u8Item)
            {

            }
            break;
    #endif

        case EN_DESIGN_PAGE_PEQ:
            // TODO: fix me
            switch(u8Item)
            {
                case EN_FacAdj_FO1_Coarse:
                    ST_AUDIO_PEQ.u16_Fo1Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u16_Fo1Value, PEQ_FO_MIN, PEQ_FO_MAX, PEQ_FO_COARSE_STEP);
                    msAPI_AUD_SetPEQ(0, ST_AUDIO_PEQ.u8_Gain1Value, (U8)(ST_AUDIO_PEQ.u16_Fo1Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo1Value%100), ST_AUDIO_PEQ.u8_Q1Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_FO1_Fine:
                    ST_AUDIO_PEQ.u16_Fo1Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u16_Fo1Value, PEQ_FO_MIN, PEQ_FO_MAX, PEQ_FO_FINE_STEP);
                    msAPI_AUD_SetPEQ(0, ST_AUDIO_PEQ.u8_Gain1Value, (U8)(ST_AUDIO_PEQ.u16_Fo1Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo1Value%100), ST_AUDIO_PEQ.u8_Q1Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_FO2_Coarse:
                    ST_AUDIO_PEQ.u16_Fo2Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u16_Fo2Value, PEQ_FO_MIN, PEQ_FO_MAX, PEQ_FO_COARSE_STEP);
                    msAPI_AUD_SetPEQ(1, ST_AUDIO_PEQ.u8_Gain2Value, (U8)(ST_AUDIO_PEQ.u16_Fo2Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo2Value%100), ST_AUDIO_PEQ.u8_Q2Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_FO2_Fine:
                    ST_AUDIO_PEQ.u16_Fo2Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u16_Fo2Value, PEQ_FO_MIN, PEQ_FO_MAX, PEQ_FO_FINE_STEP);
                    msAPI_AUD_SetPEQ(1, ST_AUDIO_PEQ.u8_Gain2Value, (U8)(ST_AUDIO_PEQ.u16_Fo2Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo2Value%100), ST_AUDIO_PEQ.u8_Q2Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_FO3_Coarse:
                    ST_AUDIO_PEQ.u16_Fo3Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u16_Fo3Value, PEQ_FO_MIN, PEQ_FO_MAX, PEQ_FO_COARSE_STEP);
                    msAPI_AUD_SetPEQ(2, ST_AUDIO_PEQ.u8_Gain3Value, (U8)(ST_AUDIO_PEQ.u16_Fo3Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo3Value%100), ST_AUDIO_PEQ.u8_Q3Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_FO3_Fine:
                    ST_AUDIO_PEQ.u16_Fo3Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u16_Fo3Value, PEQ_FO_MIN, PEQ_FO_MAX, PEQ_FO_FINE_STEP);
                    msAPI_AUD_SetPEQ(2, ST_AUDIO_PEQ.u8_Gain3Value, (U8)(ST_AUDIO_PEQ.u16_Fo3Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo3Value%100), ST_AUDIO_PEQ.u8_Q3Value);
                    return EN_REDRAW_ITEM;

                case  EN_FacAdj_Gain1:
                    ST_AUDIO_PEQ.u8_Gain1Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u8_Gain1Value, PEQ_GAIN_MIN, PEQ_GAIN_MAX, PEQ_GAIN_STEP);
                    msAPI_AUD_SetPEQ(0, ST_AUDIO_PEQ.u8_Gain1Value, (U8)(ST_AUDIO_PEQ.u16_Fo1Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo1Value%100), ST_AUDIO_PEQ.u8_Q1Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_Gain2:
                    ST_AUDIO_PEQ.u8_Gain2Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u8_Gain2Value, PEQ_GAIN_MIN, PEQ_GAIN_MAX, PEQ_GAIN_STEP);
                    msAPI_AUD_SetPEQ(1, ST_AUDIO_PEQ.u8_Gain2Value, (U8)(ST_AUDIO_PEQ.u16_Fo2Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo2Value%100), ST_AUDIO_PEQ.u8_Q2Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_Gain3:
                    ST_AUDIO_PEQ.u8_Gain3Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u8_Gain3Value, PEQ_GAIN_MIN, PEQ_GAIN_MAX, PEQ_GAIN_STEP);
                    msAPI_AUD_SetPEQ(2, ST_AUDIO_PEQ.u8_Gain3Value, (U8)(ST_AUDIO_PEQ.u16_Fo3Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo3Value%100), ST_AUDIO_PEQ.u8_Q3Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_Q1:
                    ST_AUDIO_PEQ.u8_Q1Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u8_Q1Value, PEQ_Q_MIN, PEQ_Q_MAX, PEQ_Q_STEP);
                    msAPI_AUD_SetPEQ(0, ST_AUDIO_PEQ.u8_Gain1Value, (U8)(ST_AUDIO_PEQ.u16_Fo1Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo1Value%100), ST_AUDIO_PEQ.u8_Q1Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_Q2:
                    ST_AUDIO_PEQ.u8_Q2Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u8_Q2Value, PEQ_Q_MIN, PEQ_Q_MAX, PEQ_Q_STEP);
                    msAPI_AUD_SetPEQ(1, ST_AUDIO_PEQ.u8_Gain2Value, (U8)(ST_AUDIO_PEQ.u16_Fo2Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo2Value%100), ST_AUDIO_PEQ.u8_Q2Value);
                    return EN_REDRAW_ITEM;

                case EN_FacAdj_Q3:
                    ST_AUDIO_PEQ.u8_Q3Value = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,ST_AUDIO_PEQ.u8_Q3Value, PEQ_Q_MIN, PEQ_Q_MAX, PEQ_Q_STEP);
                    msAPI_AUD_SetPEQ(2, ST_AUDIO_PEQ.u8_Gain3Value, (U8)(ST_AUDIO_PEQ.u16_Fo3Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo3Value%100), ST_AUDIO_PEQ.u8_Q3Value);
                    return EN_REDRAW_ITEM;

            }
            break;


        case EN_DESIGN_PAGE_MIU_SSC:
          #if(ENABLE_SSC)
            switch(u8Item)
            {
                /* Enable/Disable MIU SSC */
                case 0:
                    /* switching between enable and disbale */
                    stGenSetting.g_SSCSetting.SscMIUEnable = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.SscMIUEnable, DISABLE, ENABLE, 1);
                    /* Set MIU SSC */
                    msAPI_MIU_SetSsc(stGenSetting.g_SSCSetting.MIUSscSpanKHzx10, stGenSetting.g_SSCSetting.MIUSscStepPercentagex100, stGenSetting.g_SSCSetting.SscMIUEnable );
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;

                /* Increase/Decrease MIU SSC Span*/
                case 1:
                    /* Increase/Decrease MIU SSC Span */
                    stGenSetting.g_SSCSetting.MIUSscSpanKHzx10 = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.MIUSscSpanKHzx10, 20, MIU_SSC_SPAN_MAX, 1);
                    /* Set MIU SSC */
                    msAPI_MIU_SetSsc(stGenSetting.g_SSCSetting.MIUSscSpanKHzx10, stGenSetting.g_SSCSetting.MIUSscStepPercentagex100, stGenSetting.g_SSCSetting.SscMIUEnable );
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;

                /* Increase/Decrease MIU SSC Step*/
                case 2:
                    /* Increase/Decrease MIU SSC Step */
                   stGenSetting.g_SSCSetting.MIUSscStepPercentagex100 = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.MIUSscStepPercentagex100, 1, MIU_SSC_STEP_MAX, 1);
                    /* Set MIU SSC */
                    msAPI_MIU_SetSsc(stGenSetting.g_SSCSetting.MIUSscSpanKHzx10, stGenSetting.g_SSCSetting.MIUSscStepPercentagex100, stGenSetting.g_SSCSetting.SscMIUEnable );
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
            }
          #endif // #if(ENABLE_SSC)
                break;


             case EN_DESIGN_PAGE_LVDS_SSC:
              #if(ENABLE_SSC)
                switch(u8Item)
                {
                    /* Enable/Disable LVDS SSC */
                    case 0:
                        /* switching between enable and disbale */
                        stGenSetting.g_SSCSetting.SscLVDSEnale = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.SscLVDSEnale, DISABLE, ENABLE, 1);
                        /* Set LVDS SSC */
                      #if ((ENABLE_LVDSTORGB_CONVERTER == ENABLE)||CHAKRA3_AUTO_TEST)
                        g_IPanel.SetSSC( SSC_SPAN_PERIOD, SSC_STEP_PERCENT, DISABLE );
                      #else
                        g_IPanel.SetSSC( stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10,
                                            stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100,
                                            stGenSetting.g_SSCSetting.SscLVDSEnale);
                      #endif
                        MApp_SaveSSCData();
                        return EN_REDRAW_ITEM;

                    /* Increase/Descrease LVDS Span */
                    case 1:
                        stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10= MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10, 0, LVDS_SSC_SPAN_MAX, 1);
                        /* Set LVDS SSC */
                      #if ((ENABLE_LVDSTORGB_CONVERTER == ENABLE)||CHAKRA3_AUTO_TEST)
                        g_IPanel.SetSSC( SSC_SPAN_PERIOD, SSC_STEP_PERCENT, DISABLE );
                      #else
                        g_IPanel.SetSSC( stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10,
                                            stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100,
                                            stGenSetting.g_SSCSetting.SscLVDSEnale);
                      #endif
                        MApp_SaveSSCData();
                        return EN_REDRAW_ITEM;

                    /* Increase/Descrease LVDS Step */
                    case 2:
                        /* Increase/Decrease LVDS SSC Step */
                        stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100= MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100, 0, LVDS_SSC_STEP_MAX, 1);
                        /* Set LVDS SSC */
                      #if ((ENABLE_LVDSTORGB_CONVERTER == ENABLE)||CHAKRA3_AUTO_TEST)
                        g_IPanel.SetSSC( SSC_SPAN_PERIOD, SSC_STEP_PERCENT, DISABLE );
                      #else
                        g_IPanel.SetSSC( stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10,
                                            stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100,
                                            stGenSetting.g_SSCSetting.SscLVDSEnale);
                      #endif
                        MApp_SaveSSCData();
                        return EN_REDRAW_ITEM;
                        /* Increase/Descrease LVDS Swing Step */
                    case 3:
                        /* Increase/Decrease LVDS Swing Step */
                        stGenSetting.g_SSCSetting.LVDSSwing= MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.LVDSSwing, LVDS_SSC_SWING_MIN, LVDS_SSC_SWING_MAX, 10);
                        /* Set LVDS Swing */
                        MApi_PNL_Control_Out_Swing(stGenSetting.g_SSCSetting.LVDSSwing);//add LVDSSwing Funciton
                        MApp_SaveSSCData();
                        return EN_REDRAW_ITEM;
                }
              #endif // #if(ENABLE_SSC)
                break;


    #if URSA_SSC_ENABLE
        case EN_DESIGN_PAGE_6MXX_SSC:
          #if(ENABLE_SSC)
            switch(u8Item)
            {
                case 0:
                    stGenSetting.g_SSCSetting.SscUrsaMIU0Enable=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.SscUrsaMIU0Enable, DISABLE, ENABLE, 1);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 1:
                    stGenSetting.g_SSCSetting.MIU0SscModulation=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.MIU0SscModulation, 20, 40, 1);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 2:
                    stGenSetting.g_SSCSetting.MIU0SscPercentage=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.MIU0SscPercentage, 0, 100, 10);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 3:
                    stGenSetting.g_SSCSetting.SscUrsaMIU1Enable=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.SscUrsaMIU1Enable, DISABLE, ENABLE, 1);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 4:
                    stGenSetting.g_SSCSetting.MIU1SscModulation=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.MIU1SscModulation, 20, 40, 1);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 5:
                    stGenSetting.g_SSCSetting.MIU1SscPercentage=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.MIU1SscPercentage, 0, 100, 10);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 6:
                    stGenSetting.g_SSCSetting.SscUrsaLVDSEnable=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.SscUrsaLVDSEnable, DISABLE, ENABLE, 1);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 7:
                    stGenSetting.g_SSCSetting.LVDSSscModulation=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.LVDSSscModulation, 20, 40, 1);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 8:
                    stGenSetting.g_SSCSetting.LVDSSscPercentage=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.LVDSSscPercentage, 0, 300, 10);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;
                case 9:
                    stGenSetting.g_SSCSetting.PanelSwing=MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SSCSetting.PanelSwing, 0, 0x1F, 1);
                    MApp_SaveSSCData();
                    return EN_REDRAW_ITEM;

            }
          #endif // #if(ENABLE_SSC)
                break;
    #endif // #if URSA_SSC_ENABLE


        case EN_DESIGN_PAGE_SPECIAL_SET:
            switch(u8Item)
            {
                case 0: //hour off
                    stGenSetting.g_Time.cAutoSleepFlag =
                        (EN_MENU_TIME_AutoOff)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)stGenSetting.g_Time.cAutoSleepFlag, 0,EN_FacAdj_2HourOff_Num-1,1);

                    return EN_REDRAW_ITEM;

                case 1: //WDT
                    if (!MDrv_Sys_IsWatchDogEnabled())
                        MDrv_Sys_EnableWatchDog();
                    else
                        MDrv_Sys_DisableWatchDog();

                    return EN_REDRAW_ITEM;

                case 2:  //from case MAPP_UIMENUFUNC_ADJUSTADC_WHITE_PATTERN:
                    stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN =
                        (EN_DESIGN_WHITE_PATTERN)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN,0,(U16)(EN_FacAdj_WhitePattern_Num-1),1);

                    msAPI_Scaler_SetTestPattern(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), (EN_TEST_COLOR) stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN);

                    return EN_REDRAW_ITEM;

              #if ENABLE_PVR
                 case 4:
                    stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel = (stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel > 0)? 0:1;

                    if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel)
                    {
                        MApp_Record_RecordAllEnable();
                    }
                    else
                    {
                        MApp_Record_RecordAllDisable();
                    }
                    return EN_REDRAW_ITEM;
              #endif

              #if ENABLE_DESIGN_POWER_ON_MODE
                 case 5:
                    G_DESIGN_SETTING.stFacMiscSetting.u8PowerOnMode =
                        (POWERON_MODE_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)G_DESIGN_SETTING.stFacMiscSetting.u8PowerOnMode,POWERON_MODE_SAVE,(U16)(POWERON_MODE_NUMS-1),1);
                    MApp_SaveDesignSetting();

                    return EN_REDRAW_ITEM;
              #endif

              #if  MirrorEnable
                case 6:
                    stGenSetting.g_SysSetting.g_MirrorEnable = MApp_ZUI_ACT_DecIncValue_Cycle(bInc, stGenSetting.g_SysSetting.g_MirrorEnable, DISABLE, ENABLE, 1);
                        MApp_SetDesignImageMirror();
                    return EN_REDRAW_ITEM;
              #endif
              #if ENABLE_ADJUST_TSCLOCK_PHASE
                case 7:
                {
                    if(IsS2InUse() || IsDVBTInUse() || IsDVBCInUse())
                    {
                        MS_U8 u8PreDivider,u8CurDivider;
                        u8PreDivider = msAPI_Demod_GetTSClockDivider();
                        if(u8PreDivider == 0xFF)
                        {
                            return EN_REDRAW_ITEM;
                        }
                        u8CurDivider = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, u8PreDivider, 0, 31, 1);
                        if(msAPI_Demod_SetTSClockDivider(u8CurDivider))
                        {
                            printf("u8PreDivider : %d,u8CurDivider : %d\n",u8PreDivider,u8CurDivider);
                        }
                        else
                        {
                            printf("msAPI_Demod_SetTSClockDivider failed\n");
                        }
                        return EN_REDRAW_ITEM;
                    }
                    else
                    {
                        return EN_REDRAW_NONE;
                    }
                }
                case 8:
                {
                    if(IsS2InUse() || IsDVBTInUse() || IsDVBCInUse())
                    {
                        MS_U8 u8PreTuningNumber,u8CurTuningNumber;
                        u8PreTuningNumber = msAPI_Demod_GetPhaseTuningNumber();
                        if(u8PreTuningNumber == 0xFF)
                        {
                            return EN_REDRAW_ITEM;
                        }
                        u8CurTuningNumber = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, u8PreTuningNumber, 0, 31, 1);
                        if(msAPI_Demod_SetPhaseTuningNumber(u8CurTuningNumber))
                        {
                            printf("u8PreTuningNumber : %d,u8CurTuningNumber : %d\n",u8PreTuningNumber,u8CurTuningNumber);
                        }
                        else
                        {
                            printf("msAPI_Demod_SetPhaseTuningNumber failed\n");
                        }
                        return EN_REDRAW_ITEM;
                    }
                    else
                    {
                        return EN_REDRAW_NONE;
                    }
                }
              #endif
              
            }
            break;


            case EN_DESIGN_PAGE_VIF:
            #if ENABLE_VD_PACH_IN_CHINA
                switch(u8Item)
                {
                    case 0: // VIF_AGC_REF
                        G_DESIGN_SETTING.stVDSetting.Vif_AGCREFNEGATIVE = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                                (U8)G_DESIGN_SETTING.stVDSetting.Vif_AGCREFNEGATIVE, 0x20, 0x80, 1);
                        MDrv_WriteByte(0x112308,G_DESIGN_SETTING.stVDSetting.Vif_AGCREFNEGATIVE);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 1:
                        G_DESIGN_SETTING.stVDSetting.Vif_CR_KP = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.Vif_CR_KP, 0, 0x0F, 1);
                        MDrv_WriteByte(0x112222,(G_DESIGN_SETTING.stVDSetting.Vif_CR_KI<<4)+G_DESIGN_SETTING.stVDSetting.Vif_CR_KP);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 2:
                        G_DESIGN_SETTING.stVDSetting.Vif_CR_KI = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.Vif_CR_KI, 0, 0x0F, 1);
                        MDrv_WriteByte(0x112222,(G_DESIGN_SETTING.stVDSetting.Vif_CR_KI<<4)+G_DESIGN_SETTING.stVDSetting.Vif_CR_KP);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 3: // VIF_ASIA_SIGNAL_OPTION
                        G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                                (U8)G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION, 0, 1, 1);
                        MDrv_WriteByteMask(0x112220,G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION<<1,BIT1);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 4:
                        G_DESIGN_SETTING.stVDSetting.Vif_CLAMPGAIN_GAIN_OV_NEGATIVE= MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        G_DESIGN_SETTING.stVDSetting.Vif_CLAMPGAIN_GAIN_OV_NEGATIVE, 0, 0x7FF, 1);
                        MDrv_WriteByte(0x112148,(U8)G_DESIGN_SETTING.stVDSetting.Vif_CLAMPGAIN_GAIN_OV_NEGATIVE);
                        MDrv_WriteByte(0x112149,(U8)(G_DESIGN_SETTING.stVDSetting.Vif_CLAMPGAIN_GAIN_OV_NEGATIVE>>8));
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 5:
                    {

                        #if (0 == CHINA_DESCRAMBLER_BOX)
                            float X = 31.85;
                            G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc, (U16)G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX, 0, 100, 1);
                            MApp_SaveFactorySetting();
                            DWORD Y = DEC_TO_HEX((U16)((X + (G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX - 50) / 10.0) * 43.2));

                            DRV_VIF_SetParameter(VIF_PARA_SET_DESCRAMBLERBOX_DELAY, &Y, sizeof(DWORD));

                        #endif

                        return EN_REDRAW_ITEM;
                    }
                    case 6:
                        G_DESIGN_SETTING.stVDSetting.Vif_CR_THR = (U16)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.Vif_CR_THR, 0x70, 0x500, 1);
                        MDrv_WriteByte(0x112208,(U8)G_DESIGN_SETTING.stVDSetting.Vif_CR_THR);
                        MDrv_WriteByte(0x112209,(U8)(G_DESIGN_SETTING.stVDSetting.Vif_CR_THR>>8));
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 7: // VERSION
                        return EN_REDRAW_NONE;
                }
            #endif
               break;

            case EN_DESIGN_PAGE_VD:
            #if ENABLE_VD_PACH_IN_CHINA
                switch(u8Item)
                {
                    case 0:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_D4 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_D4, 0, 0xFF, 1);
                        MDrv_WriteByte(BK_AFEC_D4_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_D4);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 1:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_D5_Bit2 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_D5_Bit2, 0, 1, 1);
                        MDrv_WriteByteMask(BK_AFEC_D5_ADDRESS, (G_DESIGN_SETTING.stVDSetting.u8AFEC_D5_Bit2<<2), BIT2);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 2:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_D8_Bit3210 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_D8_Bit3210, 0, 0x0F, 1);
                        MDrv_WriteByteMask(BK_AFEC_D8_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_D8_Bit3210, 0x000F);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 3:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_D9_Bit0 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_D9_Bit0, 0, 1, 1);
                        MDrv_WriteByteMask(BK_AFEC_D9_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_D9_Bit0, BIT0);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 4:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_LOW_BOUND= (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_LOW_BOUND, 0, 0xFF, 1);
                        MDrv_WriteByte(BK_AFEC_D7_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_LOW_BOUND);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;

                    case 5:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_HIGH_BOUND= (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_HIGH_BOUND, 0, 0xFF, 1);
                        MDrv_WriteByte(BK_AFEC_D7_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_HIGH_BOUND);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 6:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_A0A1_COUNT = MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_A0A1_COUNT, 0, 5, 1);
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_A0 = u8AFEC_A0_VALUE[G_DESIGN_SETTING.stVDSetting.u8AFEC_A0A1_COUNT];
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_A1 = u8AFEC_A1_VALUE[G_DESIGN_SETTING.stVDSetting.u8AFEC_A0A1_COUNT];
                        MDrv_WriteByte(BK_AFEC_A0_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_A0);
                        MDrv_WriteByte(BK_AFEC_A1_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_A1);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 7:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_66_Bit76 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_66_Bit76, 0, 3, 1);
                        MDrv_WriteByteMask(BK_AFEC_66_ADDRESS, (G_DESIGN_SETTING.stVDSetting.u8AFEC_66_Bit76<<6), (BIT7|BIT6));
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 8:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit7654 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit7654, 0, 0x0F, 1);
                        MDrv_WriteByteMask(BK_AFEC_6E_ADDRESS, (G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit7654<<4),0xF0);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 9:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit3210 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit3210, 0, 0x0F, 1);
                        MDrv_WriteByteMask(BK_AFEC_6E_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit3210,0x0F);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 10:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_43_OPTION= (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_43_OPTION, 0, 1, 1);
                        if(0==G_DESIGN_SETTING.stVDSetting.u8AFEC_43_OPTION)
                        {
                            G_DESIGN_SETTING.stVDSetting.u8AFEC_43 = 0x74;
                        }
                        else if(1==G_DESIGN_SETTING.stVDSetting.u8AFEC_43_OPTION)
                        {
                            G_DESIGN_SETTING.stVDSetting.u8AFEC_43 = 0x14;
                        }
                        MDrv_WriteByteMask(BK_AFEC_43_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_43, 0xFF);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 11:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_44 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_44, 0, 0XFF, 1);
                        MDrv_WriteByteMask(BK_AFEC_44_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_44, 0xFF);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 12:
                        G_DESIGN_SETTING.stVDSetting.u8AFEC_CB= (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_CB, 0, 0XFF, 1);
                        MDrv_WriteByteMask(BK_AFEC_CB_ADDRESS, G_DESIGN_SETTING.stVDSetting.u8AFEC_CB, 0xFF);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 13:
                        G_DESIGN_SETTING.stVDSetting.CF_2_ATV = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.CF_2_ATV, 0, 1, 1);
                        MDrv_WriteByte(BK_AFEC_CF_ADDRESS, G_DESIGN_SETTING.stVDSetting.CF_2_ATV<<2);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 14:
                        G_DESIGN_SETTING.stVDSetting.CF_2_AV = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.CF_2_AV, 0, 1, 1);
                        MDrv_WriteByte(BK_AFEC_CF_ADDRESS, G_DESIGN_SETTING.stVDSetting.CF_2_AV<<2);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                }
            #endif
                break;

            case EN_DESIGN_PAGE_AUDIO:
            #if ENABLE_VD_PACH_IN_CHINA
                switch(u8Item)
                {
                    case 0:
                        G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV= (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV, 0, 3, 1);
                        if(G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV==1)
                        {
                            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_ENABLE_HIDEV, TRUE, NULL);
                            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_HIDEV_FILTER_BW_LEVEL, MSAPI_AUD_SIF_HIDEV_FILTER_BW_L1, NULL);
                        }
                        else if(G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV==2)
                        {
                            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_ENABLE_HIDEV, TRUE, NULL);
                            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_HIDEV_FILTER_BW_LEVEL, MSAPI_AUD_SIF_HIDEV_FILTER_BW_L2, NULL);
                        }
                        else if(G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV==3)
                        {
                            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_ENABLE_HIDEV, TRUE, NULL);
                            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_HIDEV_FILTER_BW_LEVEL, MSAPI_AUD_SIF_HIDEV_FILTER_BW_L3, NULL);
                        }
                        else
                        {
                            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_ENABLE_HIDEV, FALSE, NULL);
                        }
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 1:
                        G_DESIGN_SETTING.stVDSetting.AUDIO_NR= MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.AUDIO_NR, 0, 0x35, 1);
                        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_setNR_Threshold, G_DESIGN_SETTING.stVDSetting.AUDIO_NR,0X00);//should finetune
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                    case 2:
                        G_DESIGN_SETTING.stVDSetting.PRESCALE=(U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)G_DESIGN_SETTING.stVDSetting.PRESCALE, 0, 0xFF, 1);
                        MApp_SaveDesignSetting();
                        return EN_REDRAW_ITEM;
                }
            #endif
                break;

            case EN_DESIGN_PAGE_OTHER:
                switch(u8Item)
                {
                case 0:
                    stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN =
                        (EN_DESIGN_WHITE_PATTERN)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN,0,(U16)(EN_FacAdj_WhitePattern_Num-1),1);

                    msAPI_Scaler_SetTestPattern(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), (EN_TEST_COLOR) stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN);

                    return EN_REDRAW_ITEM;
                    break;
                case 1:
                    stLMGenSetting.stMDesign_Adjust.xvycc = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                        (U16)stLMGenSetting.stMDesign_Adjust.xvycc, 0, 1, 1);
                    MApp_SaveDesignSetting();
                    return EN_REDRAW_ITEM;
                case 2:
                    {
                        if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {
                            // switch input source
                            MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_ATV, MAIN_WINDOW);
                        }
                        else if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {
                        #if (ENABLE_DVB)
                            MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_DVBT, MAIN_WINDOW);//Thomas 20150714 to do
                            // initial channel
                            SET_Default_TW_DTV_CH();
                        #endif
                        }
                    }
                    break;

                case 3:
                    uart_tmp = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,(U16) uart_tmp, MS_UART_TYPE_MIN, MS_UART_TYPE_MAX, 1);
                    if(uart_tmp == MS_UART_TYPE_HK )
                    {
                #if( defined(__aeon__) )
                    {
                        //MDrv_UART_Init(E_UART_AEON_R2, 115200);
                        mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
                    }
                #else
                    mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
                #endif
                    }
                    else if(uart_tmp == MS_UART_TYPE_AEON)
                    {
                #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
                        mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
                #elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET)
                        mdrv_uart_connect(E_UART_PORT0, E_UART_SECURE_R2);
                #else
                        mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
                #endif
                     }
                    else if(uart_tmp == MS_UART_TYPE_VDEC)
                    {
                        mdrv_uart_connect(E_UART_PORT0, E_UART_VDEC);
                    }
                    else
                    {
                         mdrv_uart_connect(E_UART_PORT0, E_UART_OFF);
                    }
                    return EN_REDRAW_ITEM;
                }
                break;

      #if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION

        case  EN_DESIGN_PAGE_OVERSCAN:
            switch (u8Item)
            {
                case 0://reslution
                    return EN_REDRAW_ITEM;

                case 2://h-size
                    G_OVERSCAN_HRatio = MApp_ZUI_ACT_DecIncValue(bInc, G_OVERSCAN_HRatio, 0, 50, 1);
                    MApp_SaveOverScanData();
                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                          stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                          SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                                          MAIN_WINDOW);
                    return EN_REDRAW_ITEM;

                case 3://h-position
                    G_OVERSCAN_HPOSITION=(MApp_ZUI_ACT_DecIncValue(bInc, G_OVERSCAN_HPOSITION, 0, 50, 1));
                    MApp_SaveOverScanData();
                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                          stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                          SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                                          MAIN_WINDOW);
                    return EN_REDRAW_ITEM;

                case 4://v-size
                    G_OVERSCAN_VRatio=MApp_ZUI_ACT_DecIncValue(bInc, G_OVERSCAN_VRatio, 0, 100, 1);
                    MApp_SaveOverScanData();
                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                          stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                          SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                                          MAIN_WINDOW);
                    return EN_REDRAW_ITEM;

                case 5://v-position
                    G_OVERSCAN_VPOSITION=(MApp_ZUI_ACT_DecIncValue(bInc, G_OVERSCAN_VPOSITION, 0, 14, 1));
                    MApp_SaveOverScanData();
                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                          stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                          SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),
                                          MAIN_WINDOW);
                    return EN_REDRAW_ITEM;
            }
            break;

      #endif // #if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION


        #if (ENABLE_NONLINEAR_CURVE)
            case EN_DESIGN_PAGE_NONLINEAR_CURVE:
            {
                P_MS_USER_NONLINEAR_CURVE pNonLinearCurve = NULL;
                U16 u16MaxValue = 255;


                E_DATA_INPUT_SOURCE src = DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW);

        #if(ENABLE_PICTURE_NONLINEAR_CURVE)
                if(EN_NONLINEAR_BRIGHTNESS_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_BRIGHTNESS);
                }
                else if(EN_NONLINEAR_CONTRAST_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_CONTRAST);
                }
                else if(EN_NONLINEAR_SATURATION_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_SATURATION);
                }
                else if(EN_NONLINEAR_SHARPNESS_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_SHARPNESS);
                    u16MaxValue = 0x3F;
                }
                else if(EN_NONLINEAR_HUE_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_HUE);
                    u16MaxValue = 100;
                }
                else if(EN_NONLINEAR_BACKLIGHT_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_BACKLIGHT);
                }
        #endif
        #if(ENABLE_SOUND_NONLINEAR_CURVE)
                if(EN_NONLINEAR_VOLUME_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_VOLUME);
                    u16MaxValue = 100;
                }
        #endif

                if(pNonLinearCurve==NULL)
                {
                    MApp_Fatal_Error("NULL POINTER\n", __FUNCTION__);
                    return EN_REDRAW_NONE;
                }


                switch(u8Item)
                {
                    case 0:
                #if(ENABLE_SOUND_NONLINEAR_CURVE)
                    _eNonlinearCurveOption[src] =
                       (NONLINEAR_CURVE_OPTION) MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)(_eNonlinearCurveOption[src]),(U16)EN_NONLINEAR_BRIGHTNESS_CURVE,(U16)EN_NONLINEAR_VOLUME_CURVE,1);
                #else
                    _eNonlinearCurveOption[src] =
                       (NONLINEAR_CURVE_OPTION) MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)(_eNonlinearCurveOption[src]),(U16)EN_NONLINEAR_BRIGHTNESS_CURVE,(U16)EN_NONLINEAR_BACKLIGHT_CURVE,1);
                #endif
                        return EN_REDRAW_LIST;

                    case 1:
                        pNonLinearCurve->u8OSD_0 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)pNonLinearCurve->u8OSD_0, 0, (U16)pNonLinearCurve->u8OSD_25, 1);
                        break;

                    case 2:
                        pNonLinearCurve->u8OSD_25 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)pNonLinearCurve->u8OSD_25, (U16)pNonLinearCurve->u8OSD_0, (U16)pNonLinearCurve->u8OSD_50, 1);
                        break;

                    case 3:
                        pNonLinearCurve->u8OSD_50 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)pNonLinearCurve->u8OSD_50, (U16)pNonLinearCurve->u8OSD_25, (U16)pNonLinearCurve->u8OSD_75, 1);
                        break;

                    case 4:
                        pNonLinearCurve->u8OSD_75 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)pNonLinearCurve->u8OSD_75, (U16)pNonLinearCurve->u8OSD_50, (U16)pNonLinearCurve->u8OSD_100, 1);
                        break;

                    case 5:
                        pNonLinearCurve->u8OSD_100 = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(bInc,
                            (U16)pNonLinearCurve->u8OSD_100, (U16)pNonLinearCurve->u8OSD_75, u16MaxValue, 1);
                        break;

                    default:
                        return EN_REDRAW_NONE;

                }

                {
                    if(EN_NONLINEAR_BRIGHTNESS_CURVE == _eNonlinearCurveOption[src])
                    {
                    #if 1 //
                        MApp_XC_PQ_Set_Brightness(MAIN_WINDOW, TRUE);
                    #else
                        MApi_XC_ACE_PicSetBrightnessInVsync(MAIN_WINDOW,
                                                    MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_R),
                                                    MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_G),
                                                    MApi_XC_Sys_ACE_transfer_Bri((MApp_Scaler_FactoryAdjBrightness(msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness),ST_SUBCOLOR.u8SubBrightness)), BRIGHTNESS_B));
                    #endif
                    }
                    else if(EN_NONLINEAR_CONTRAST_CURVE == _eNonlinearCurveOption[src])
                    {
                    #if 1
                        MApp_XC_PQ_Set_Contrast(MAIN_WINDOW, TRUE);
                    #else
                        MApi_XC_ACE_PicSetContrast(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), MApp_Scaler_FactoryContrast(msAPI_Mode_PictureContrastN100toReallyValue(ST_PICTURE.u8Contrast),ST_SUBCOLOR.u8SubContrast));
                    #endif
                    }
                    else if(EN_NONLINEAR_SATURATION_CURVE == _eNonlinearCurveOption[src])
                    {
                    #if 1 // Use new API
                        MApp_XC_PQ_Set_Saturation(MAIN_WINDOW, TRUE);
                    #else
                        MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(ST_PICTURE.u8Saturation) );
                    #endif
                    }
                    else if(EN_NONLINEAR_SHARPNESS_CURVE == _eNonlinearCurveOption[src])
                    {
                        MApi_XC_ACE_PicSetSharpness( MAIN_WINDOW, msAPI_Mode_PictureSharpnessN100toReallyValue(ST_PICTURE.u8Sharpness) );
                    }
                    else if(EN_NONLINEAR_HUE_CURVE == _eNonlinearCurveOption[src])
                    {
                        MApi_XC_ACE_PicSetHue( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), msAPI_Mode_PictureHueN100toReallyValue(ST_PICTURE.u8Hue) );
                    }
                #if(ENABLE_SOUND_NONLINEAR_CURVE)
                    else if(EN_NONLINEAR_VOLUME_CURVE == _eNonlinearCurveOption[src])
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
                    }
                #endif
                    MApp_SaveNonLinearCurveSetting();
                    return EN_REDRAW_ITEM;
                }
                break;
            }
        #endif

        default:
            break;
    }
    return EN_REDRAW_NONE;
}
/*
#if (ENABLE_NONLINEAR_CURVE)
static U16 _MApp_ZUI_ACT_GetDataInputSourceStringID(E_DATA_INPUT_SOURCE src)
{
    U16 u16TempID = Empty;
    {
        switch(src)
        {
            case DATA_INPUT_SOURCE_RGB:
                u16TempID= en_str_PCdashRGB;
                break;
         #if ENABLE_DTV
            case DATA_INPUT_SOURCE_DTV:
                u16TempID=en_str_DTV;
                break;
         #endif
            case DATA_INPUT_SOURCE_ATV:
                u16TempID=en_str_ATV;
                break;

            #if (INPUT_AV_VIDEO_COUNT == 1)
            case DATA_INPUT_SOURCE_AV:
                u16TempID=en_str_AV;
                break;
            #elif (INPUT_AV_VIDEO_COUNT >= 2)
            case DATA_INPUT_SOURCE_AV:
                u16TempID=en_str_AV_1;
                break;
            case DATA_INPUT_SOURCE_AV2:
                u16TempID=en_str_AV_2;
                break;
            #endif
            #if (INPUT_AV_VIDEO_COUNT >= 3)
            case DATA_INPUT_SOURCE_AV3:
                u16TempID=en_str_AV_3;
                break;
            #endif

            #if (INPUT_SV_VIDEO_COUNT == 1)
            case DATA_INPUT_SOURCE_SVIDEO:
                u16TempID=en_str_SdashVideo;
                break;
            #elif (INPUT_SV_VIDEO_COUNT == 2)
            case DATA_INPUT_SOURCE_SVIDEO:
                u16TempID=en_str_SdashVideo_1;
                break;
            case DATA_INPUT_SOURCE_SVIDEO2:
                u16TempID=en_str_SdashVideo_2;
                break;
            #endif

            #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
            case DATA_INPUT_SOURCE_COMPONENT:
                u16TempID=en_str_Component1;
                break;
            #endif
            #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
            case DATA_INPUT_SOURCE_COMPONENT2:
                u16TempID=en_str_Component2;
                break;
            #endif
            #if   (INPUT_SCART_VIDEO_COUNT == 1)
            case DATA_INPUT_SOURCE_SCART:
                u16TempID=en_str_SCART;
                break;
            #elif (INPUT_SCART_VIDEO_COUNT == 2)
            case DATA_INPUT_SOURCE_SCART:
                u16TempID=en_str_SCART_1;
                break;
            case DATA_INPUT_SOURCE_SCART2:
                u16TempID=en_str_SCART_2;
                break;
            #endif
        #if (INPUT_HDMI_VIDEO_COUNT == 1)
            case DATA_INPUT_SOURCE_HDMI:
                u16TempID=en_str_HDMI;
                break;
        #endif
        #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case DATA_INPUT_SOURCE_HDMI:
                u16TempID=en_str_HDMI1;
                break;

            case DATA_INPUT_SOURCE_HDMI2:
                u16TempID=en_str_HDMI2;
                break;
        #endif
        #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case DATA_INPUT_SOURCE_HDMI3:
                u16TempID=en_str_HDMI3;
                break;
        #endif
        #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case DATA_INPUT_SOURCE_HDMI4:
                u16TempID=en_str_HDMI4;
                break;
        #endif

            default:
            #if ENABLE_DTV
                u16TempID=en_str_DTV;
            #else
                u16TempID=en_str_ATV;
            #endif
                break;
        }
    }
    return u16TempID;
}
#endif
*/
#if (ENABLE_NONLINEAR_CURVE)
static U16 _MApp_ZUI_ACT_GetNonlinearCurveOption(NONLINEAR_CURVE_OPTION NonCu)
{
    U16 u16TempID = Empty;
    {
        switch(NonCu)
        {
            case EN_NONLINEAR_BRIGHTNESS_CURVE:
                u16TempID = en_str_Brightness_Curve;
                break;
            case EN_NONLINEAR_CONTRAST_CURVE:
                u16TempID = en_str_Contrast_Curve;
                break;
            case EN_NONLINEAR_SATURATION_CURVE:
                u16TempID = en_str_Saturation_Curve;
                break;
            case EN_NONLINEAR_HUE_CURVE:
                u16TempID = en_str_Hue_Curve;
                break;
            case EN_NONLINEAR_SHARPNESS_CURVE:
                u16TempID = en_str_Sharpness_Curve;
                break;
            #if(ENABLE_SOUND_NONLINEAR_CURVE)
            case EN_NONLINEAR_VOLUME_CURVE:
                u16TempID = en_str_Volume_Curve;
                break;
            #endif
            case EN_NONLINEAR_BACKLIGHT_CURVE:
                u16TempID = en_str_Backlight_Curve;
                break;
            default:
                u16TempID = en_str_Brightness_Curve;
                break;
        }
    }
    return u16TempID;
}
#endif

static LPTSTR _MApp_ZUI_ACT_GetQText(U8 u8Q)
{
    u8Q += 5;
    LPTSTR a;
    // 0~156 map to 0.5~16
    a = MApp_ZUI_API_GetU16String(u8Q);
    U8 digit = MApp_GetNoOfDigit(u8Q);
    if(digit == 3)
    {
        a[4] = 0;
        a[3] = a[2];
        a[2] = '.';
    }
    else if(digit == 2)
    {
        a[3] = 0;
        a[2] = a[1];
        a[1] = '.';
    }
    else
    {
        a[3] = 0;
        a[2] = a[0];
        a[1] = '.';
        a[0] = '0';
    }

    return a;
}


static LPTSTR _MApp_ZUI_ACT_GetGainText(U8 u8Gain)
{
    LPTSTR a;
    // 0~240 map to -12.0~12.0
    if(u8Gain >= 120) //120~240
    {
        u8Gain -= 120;
        a = MApp_ZUI_API_GetU16String(u8Gain);
        U8 digit = MApp_GetNoOfDigit(u8Gain);
        if(digit == 3)
        {
            a[4] = 0;
            a[3] = a[2];
            a[2] = '.';
        }
        else if(digit == 2)
        {
            a[3] = 0;
            a[2] = a[1];
            a[1] = '.';
        }
        else
        {
            a[3] = 0;
            a[2] = a[0];
            a[1] = '.';
            a[0] = '0';
        }
    }
    else // 0~119
    {
        u8Gain = 120 - u8Gain;
        a = MApp_ZUI_API_GetU16String(u8Gain);
        U8 digit = MApp_GetNoOfDigit(u8Gain);
        if(digit == 3)
        {
            a[5] = 0;
            a[4] = a[2];
            a[3] = '.';
            a[2] = a[1];
            a[1] = a[0];
            a[0] = '-';
        }
        else if(digit == 2)
        {
            a[4] = 0;
            a[3] = a[1];
            a[2] = '.';
            a[1] = a[0];
            a[0] = '-';
        }
        else
        {
            a[4] = 0;
            a[3] = a[0];
            a[2] = '.';
            a[1] = '0';
            a[0] = '-';
        }
    }
    return a;
}

static LPTSTR _MApp_ZUI_ACT_GetDesignMenuValueText(U8 u8Item)
{
    U16 u16TempID = Empty;
#if ENABLE_PANEL_BIN
    U8 _u8PanelBinIndex;
#endif
  #if(LOG_DESIGNMENU_SHOWITEM)
      u8Item = GetDesignMenuItemu8ShowItem(_eDesignMenuPage, u8Item);
  #endif

    switch(_eDesignMenuPage)
    {
        case EN_DESIGN_PAGE_ROOT:
            switch(u8Item)
            {
                case 0: //TBD for Resolution show, use WHITE_PATTERN temporary
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 9:
                case 8:
                    break;
                case 10:
                    if(ST_AUDIO_PEQ.u8_PEQOnOff)
                    {
                        u16TempID = en_str_On;
                    }
                    else
                    {
                        u16TempID = en_str_Off;
                    }
                    break;
                case 14:
                #if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
                    if(b_isCIkeyFileExit == FALSE)
                    {
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"No file", strlen("No file"));
                    }
                    else if (Mapp_check_valid_key())
                    {
                        u16TempID=en_str_OK;
                    }
                    else
                    {
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"NG", strlen("NG"));
                    }
                #endif
                    break;
            }
            break;
        #if ENABLE_CI
        case EN_DESIGN_PAGE_CI:
            switch(u8Item)
            {
                case 0:
                    {
                       if(stGenSetting.g_CISetting.UCredential_Mode)
                       {
                            u16TempID = en_str_TestbracketsNand_Flash;
                       }
                       else
                       {
                         u16TempID = en_str_TestbracketsNand_Library;
                       }
                    }
                    break;
                case 1:
                    {
                        if(stGenSetting.g_CISetting.UPerformance_Monitor)
                        {
                         u16TempID = en_str_On;
                         }
                        else
                        {
                         u16TempID = en_str_Off;
                        }
                    }
                    break;
                case 2:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UResource_Manager);
                    }
                case 3:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UApplication_Information);
                    }
                case 4:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UConditional_Access_Support);
                   }
                case 5:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UHost_Control);
                    }
                case 6:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UDate_Time);
                    }
                case 7:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UMan_Machine_Interface);
                    }
                case 8:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.ULow_Speed_Communication);
                    }
                case 9:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UContent_Control);
                    }
                case 10:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UHost_Language_Control);
                    }
                case 11:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UCAM_Upgrade);
                    }
                case 12:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UOperate_Profile);
                    }
                case 13:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.USpecific_Application_Support);
                    }
                case 14:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UApplication_Man_Machine_Interface);
                    }
                case 15:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UProgram_Map_Table);
                    }
                case 16:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UHost_Service_Shunning);
                    }
                case 17:
                    {
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UCanal_Ready_Authentication);
                    }
                case 18:
                    {
                       return MApp_ZUI_API_GetU16String(stGenSetting.g_CISetting.UDEFAULT);
                    }
            }
            break;
        #endif


#if ENABLE_PANEL_BIN
            case EN_DESIGN_PAGE_PANEL_PARAMETER:

                _u8PanelBinIndex = G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex;
                switch(u8Item)
                {
                    case 0:
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,
                                    (U8*)MApi_PNL_Get_PanelName(MApi_PNL_Get_CurPanelType()),
                                    128 );
                    case 1:
                        return MApp_ZUI_API_GetU16String(G_FACTORY_SETTING.stFacPnlSetting.m_bPanelDualPort[_u8PanelBinIndex]);

                    case 2:
                        return MApp_ZUI_API_GetU16String(G_FACTORY_SETTING.stFacPnlSetting.m_bPanelSwapPort[_u8PanelBinIndex]);

                    case 3:
                        return MApp_ZUI_API_GetU16String(G_FACTORY_SETTING.stFacPnlSetting.m_bPanelLVDS_TI_MODE[_u8PanelBinIndex]);

                    case 4:
                        return MApp_ZUI_API_GetU16String(G_FACTORY_SETTING.stFacPnlSetting.m_ucTiBitMode[_u8PanelBinIndex]);

                    case 5:
                        return MApp_ZUI_API_GetU16String(G_FACTORY_SETTING.stFacPnlSetting.m_ucOutputFormatBitMode[_u8PanelBinIndex]);
                }
                break;
#endif
#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
        case EN_DESIGN_WHITE_BALANCE_PATTERN:
            switch(u8Item)
            {
                case 0:
                {
                    if(G_FACTORY_SETTING.stFacWBPatternSetting.enWBPattern == EN_WB_PATTERN_ON)
                        u16TempID=en_str_On;
                    else
                        u16TempID=en_str_Off;
                }
                    break;

                case 1:
                    return MApp_ZUI_API_GetU16String(G_FACTORY_SETTING.stFacWBPatternSetting.u8WBPatternValue);
            }
            break;
#endif

        case EN_DESIGN_PAGE_PICTURE_MODE:
            switch(u8Item)
            {
                case 0:   // picture mode
                    u16TempID = _MApp_ZUI_ACT_GetPictureModeStringID();
                    break;

                case 1: //from case EN_DNUM_GetSubBCAdjustBrightnesValue:
                    // return MApp_ZUI_API_GetU16String(ST_SUBCOLOR.u8SubBrightness + 50 - SUB_BRIGHTNESS_BYPASS);
                    return MApp_ZUI_API_GetU16String(ST_PICTURE.u8Brightness);

                case 2: //from case EN_DNUM_GetSubBCAdjustContrastValue:
                    // return MApp_ZUI_API_GetU16String(ST_SUBCOLOR.u8SubContrast + 50 - SUB_CONTRAST_BYPASS);
                    return MApp_ZUI_API_GetU16String(ST_PICTURE.u8Contrast);

                case 3:
                    return MApp_ZUI_API_GetU16String(ST_PICTURE.u8Saturation);

                case 4:
                    return MApp_ZUI_API_GetU16String(ST_PICTURE.u8Sharpness);

                case 5:
                    return MApp_ZUI_API_GetU16String(ST_PICTURE.u8Hue);

                case 6:
                    return MApp_ZUI_API_GetU16String(ST_PICTURE.u8Backlight);

                case 7:
                    break; //TODO: the same as contrast???


            }
            break;

        case EN_DESIGN_PAGE_PEQ:
            // TODO: fix me
            switch(u8Item)
            {
                case EN_FacAdj_FO1_Coarse:
                    return MApp_ZUI_API_GetU16String(ST_AUDIO_PEQ.u16_Fo1Value);
                case EN_FacAdj_FO1_Fine:
                    return MApp_ZUI_API_GetU16String(ST_AUDIO_PEQ.u16_Fo1Value);
                case EN_FacAdj_FO2_Coarse:
                    return MApp_ZUI_API_GetU16String(ST_AUDIO_PEQ.u16_Fo2Value);
                case EN_FacAdj_FO2_Fine:
                    return MApp_ZUI_API_GetU16String(ST_AUDIO_PEQ.u16_Fo2Value);
                case EN_FacAdj_FO3_Coarse:
                    return MApp_ZUI_API_GetU16String(ST_AUDIO_PEQ.u16_Fo3Value);
                case EN_FacAdj_FO3_Fine:
                    return MApp_ZUI_API_GetU16String(ST_AUDIO_PEQ.u16_Fo3Value);
                    //gain :-12.0~12.0
                case EN_FacAdj_Gain1:
                    return _MApp_ZUI_ACT_GetGainText(ST_AUDIO_PEQ.u8_Gain1Value);
                case EN_FacAdj_Gain2:
                    return _MApp_ZUI_ACT_GetGainText(ST_AUDIO_PEQ.u8_Gain2Value);
                case EN_FacAdj_Gain3:
                    return _MApp_ZUI_ACT_GetGainText(ST_AUDIO_PEQ.u8_Gain3Value);
                    // 0.5~16
                case EN_FacAdj_Q1:
                    return _MApp_ZUI_ACT_GetQText(ST_AUDIO_PEQ.u8_Q1Value);
                case EN_FacAdj_Q2:
                    return _MApp_ZUI_ACT_GetQText(ST_AUDIO_PEQ.u8_Q2Value);
                case EN_FacAdj_Q3:
                    return _MApp_ZUI_ACT_GetQText(ST_AUDIO_PEQ.u8_Q3Value);
            }
            break;
/*
        case EN_DESIGN_PAGE_WHITE_BALANCE:
            switch(u8Item)
            {
                case 0:
                    u16TempID = _MApp_ZUI_ACT_GetDataInputSourceStringID(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));
                    break;

                case 2: //from case WB_TEMPERATURE_TEXT:
                    {
                        if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_COOL)
                            u16TempID=en_str_Cool;
                        else if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_MEDIUM)
                            u16TempID=en_str_Medium;
                        else if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_WARM)
                            u16TempID=en_str_Warm;
                    #if(MS_COLOR_TEMP_COUNT ==4)
                        else if (ST_PICTURE.eColorTemp == MS_COLOR_TEMP_USER)
                            u16TempID=en_str_User;
                    #endif
                    }
                    break;

                case 3: //from case EN_DNUM_GetWBRedGainValue:
                    return MApp_ZUI_API_GetU16String(ST_COLOR_TEMP.cRedColor);

                case 4: //from case EN_DNUM_GetWBGreenGainValue:
                    return MApp_ZUI_API_GetU16String(ST_COLOR_TEMP.cGreenColor);

                case 5: //from case EN_DNUM_GetWBBlueGainValue:
                    return MApp_ZUI_API_GetU16String(ST_COLOR_TEMP.cBlueColor);

                case 7: //from case EN_DNUM_GetWBRedOffsetValue:
                    return MApp_ZUI_API_GetU16String(ST_COLOR_TEMP.cRedOffset);

                case 8: //from case EN_DNUM_GetWBGreenOffsetValue:
                    return MApp_ZUI_API_GetU16String(ST_COLOR_TEMP.cGreenOffset);

                case 9: //from case EN_DNUM_GetWBBlueOffsetValue:
                    return MApp_ZUI_API_GetU16String(ST_COLOR_TEMP.cBlueOffset);
            }
            break;
*/
        case EN_DESIGN_PAGE_QMAP_PAGE:
            {
                U8 u8IPIdx, u8TabIdx, u8IPNum;

                u8IPIdx = ((_u8IPIndex)/(COUNTOF(_DesignMenuItemHwndList)))*(COUNTOF(_DesignMenuItemHwndList))+u8Item;
                u8IPNum = _u8IPNumber;

                //printf("=======IP[%bu / %bu] = %s\n", u8IPIdx, u8IPNum, MDrv_PQ_GetIPName(u8IPIdx));
                if(u8IPIdx < u8IPNum)
                {
                     u8TabIdx = (U8)MDrv_PQ_GetCurrentTableIndex(PQ_MAIN_WINDOW, (U16)u8IPIdx);

                    //printf("===TAB[%bu] = ", u8TabIdx);
                    if(u8TabIdx != 0xFF)
                    {
                        //printf("%s\n", MDrv_PQ_GetTableName(u8IPIdx, u8TabIdx));
                        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)MDrv_PQ_GetTableName(u8IPIdx, u8TabIdx), 255);
                    }
                }
            }
        break;

        #if ENABLE_PIP
        case EN_DESIGN_PAGE_PIP_POP:
            switch(u8Item)
            {
                case 0: //PIP/POP : On/Off
                {
                    if(stGenSetting.g_stPipSetting.bPipEnable)
                    {
                        u16TempID = en_str_On;
                    }
                    else
                    {
                        u16TempID = en_str_Off;
                    }
                }
                break;

                case 1: //PIP Border Width
                {
                    return MApp_ZUI_API_GetU16String(stGenSetting.g_stPipSetting.u8BorderWidth);
                }
                break;
            }
        break;
        #endif
        case EN_DESIGN_PAGE_SW_INFO_PAGE:
            switch(u8Item)
            {
                case 1:
                {
                    char ptr_head[128];

                    snprintf(ptr_head, 128, "%s, %s", SWCompileDate, SWCompileTime);

                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                }
            #if ENABLE_OAD
                case 2:
                {
                    U16 curStringLen = 0;
                    U8 digit;
                    U32 u32tv = 0;
                    U32 u32ts = 0;

                    MApp_OAD_GetVersion(&u32tv,&u32ts);
                    MApp_ZUI_API_Strcpy(&CHAR_BUFFER[0], MApp_ZUI_API_GetString(en_str_TV_Version));
                    curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                    CHAR_BUFFER[curStringLen] = CHAR_SPACE;
                    curStringLen +=1;
                    digit = MApp_GetNoOfDigit(u32tv);
                    __MApp_UlongToString(u32tv, (CHAR_BUFFER+curStringLen), digit);
                    curStringLen +=digit;
                    CHAR_BUFFER[curStringLen] = 0;
                    return CHAR_BUFFER;
                }
            #endif
       #if ENABLE_SHOW_PHASE_DESIGN
                case 3:
                  {

                     U16 i, Miu0_Dqs0,Miu0_Dqs0_PhaseNum=0;
                     Miu0_Dqs0=g_u16Miu0_Dqs0;
                     for(i=0;i<16;i++)
                      {
                        if((Miu0_Dqs0&0x01)==1)
                       Miu0_Dqs0_PhaseNum++;
                        Miu0_Dqs0=Miu0_Dqs0>>1;
                       }
             return MApp_ZUI_API_GetU16String(Miu0_Dqs0_PhaseNum);
                   }
                  case 4:
                  {
                     U16 i,Miu0_Dqs1,Miu0_Dqs0_PhaseNum=0;
                     Miu0_Dqs1=g_u16Miu0_Dqs1;
                     for(i=0;i<16;i++)
                      {
                        if((Miu0_Dqs1&0x01)==1)
                       Miu0_Dqs0_PhaseNum++;
                        Miu0_Dqs1=Miu0_Dqs1>>1;
                       }
                     return MApp_ZUI_API_GetU16String(Miu0_Dqs0_PhaseNum);
                   }
         #if(ENABLE_MIU_1)
                   case 5:
                  {
                     int i,Miu1_Dqs1,Miu0_Dqs1_PhaseNum=0;
                     Miu1_Dqs1=g_u16Miu1_Dqs0;
                     for(i=0;i<16;i++)
                      {
                        if((Miu1_Dqs1&0x01)==1)
                       Miu0_Dqs1_PhaseNum++;
                        Miu1_Dqs1=Miu1_Dqs1>>1;
                       }
             return MApp_ZUI_API_GetU16String(Miu0_Dqs1_PhaseNum);
                   }
                  case 6:
                  {
                     int i,Miu1_Dqs1,Miu0_Dqs1_PhaseNum=0;
                     Miu1_Dqs1=g_u16Miu1_Dqs1;
                    for(i=0;i<16;i++)
                      {
                        if((Miu1_Dqs1&0x01)==1)
                       Miu0_Dqs1_PhaseNum++;
                        Miu1_Dqs1=Miu1_Dqs1>>1;
                       }
                     return MApp_ZUI_API_GetU16String(Miu0_Dqs1_PhaseNum);
                   }
           #endif
        #endif

                case 7:
                    printf("sizeof(BoardNameStr) + 1 = %d\n", sizeof(BoardNameStr) + 1);
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, BoardNameStr, sizeof(BoardNameStr) + 1);

                case 8:
                    //return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, PanelNameStr[PANEL_CURRENT_TYPE_SEL], sizeof(PanelNameStr[PANEL_CURRENT_TYPE_SEL]) + 1);
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,
                                (U8*)MApi_PNL_Get_PanelName(MApi_PNL_Get_CurPanelType()),
                                128 );
                case 9:
                {
                    char MainPQVersionStr[128];
                    #ifdef MainPQVersion
                    memcpy(MainPQVersionStr, MainPQVersion, sizeof(MainPQVersion) + 1);
                    #else
                    memcpy(MainPQVersionStr, "NONE", sizeof("NONE") );
                    #endif

                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)MainPQVersionStr, strlen(MainPQVersionStr) + 1);
                    return CHAR_BUFFER;
                }

                case 10:
                {
                    char SubPQVersionStr[128];
                    #ifdef SubPQVersion
                    memcpy(SubPQVersionStr, SubPQVersion, sizeof(SubPQVersion) + 1);
                    #else
                    memcpy(SubPQVersionStr, "NONE", sizeof("NONE") );
                    #endif
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)SubPQVersionStr, strlen(SubPQVersionStr) + 1);
                }

                case 11:
                {
                    char DateString[128];
                    memcpy(DateString, SWCompileDate, sizeof(SWCompileDate) );
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)DateString, sizeof(SWCompileDate) + 1);
                }

                case 12:
                {
                    char TimeString[128];
                    memcpy(TimeString, SWCompileTime, sizeof(SWCompileTime) );
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)TimeString, sizeof(SWCompileTime) + 1);
                }
            }
        break;
        #if ENABLE_AUTOTEST
        case EN_DESIGN_PAGE_BMTEST_PAGE:
        {
            //printf("==================================================\n\n");
            static int i=0;
            //static char aeon_dhrystone[10];
            static char mips_dhrystone[10]={};
            static char aeon_dhrystone[10]={};
            static char mips_mmtest[10]={};
            static char aeon_mmtest[10]={};

            if(i==0)
            {
                // Do benchmark
                CPU_BENCHMARK_TEST(mips_dhrystone,aeon_dhrystone,mips_mmtest,aeon_mmtest);

                i++;
            }
            #if 1
            switch(u8Item)
            {
                case 0:
                {
                      char *ptr;
                      char ptr_head[128];

                      ptr = ptr_head;
                      strcpy(ptr,aeon_dhrystone);
                      strcat(ptr, "  Dhrystones/sec");
                      return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                }
                case 1:
                {
                      char *ptr;
                      char ptr_head[128]={0};

                      ptr = ptr_head;

                      strcpy(ptr,mips_dhrystone);
                      strcat(ptr, "  Dhrystones/sec");
                      return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                }
                case 2:
                {
                      char *ptr;
                      char ptr_head[128]={0};

                      ptr = ptr_head;

                      strcpy(ptr,aeon_mmtest);
                      strcat(ptr, "  micro second");
                      return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                }
                case 3:
                {
                      char *ptr;
                      char ptr_head[128]={0};

                      ptr = ptr_head;

                      strcpy(ptr,mips_mmtest);
                      strcat(ptr, "  micro second");
                      return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                }
            }
            #endif
        break;
     }
     #endif
#if ENABLE_AUTO_DQS_Design
        case EN_DESIGN_PAGE_BIST_TEST:
            switch(u8Item)
            {
                case 0:
                    if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                        u16TempID = en_str_Testing3dot;
                    else
                        u16TempID = en_str_Start;
                    break;
                case 1:
                    if((u8DQSM0[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM0[2] >= (u8DQSM0[0]+0x22))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 2:
                    if((u8DQSM0[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM0[2] >= (u8DQSM0[0]+0x11))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 3:
                    if((u8DQSM0[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM0[2] >= (u8DQSM0[0]+0x00))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 4:
                    if((u8DQSM0[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM0[0] >= (u8DQSM0[1]+0x11))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 5:
                    if((u8DQSM0[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM0[0] >= (u8DQSM0[1]+0x22))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
            #if ENABLE_MIU_1
                case 6:
                    if((u8DQSM1[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM1[2] >= (u8DQSM1[0]+0x22))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 7:
                    if((u8DQSM1[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM1[2] >= (u8DQSM1[0]+0x11))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 8:
                    if((u8DQSM1[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM1[2] >= (u8DQSM1[0]+0x00))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 9:
                    if((u8DQSM1[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM1[0] >= (u8DQSM1[1]+0x11))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
                case 10:
                    if((u8DQSM1[0] == 0x00)||(_BIST_TEST_MODE == EN_BIST_TEST_UI_START))
                    {
                        u16TempID = en_str_dashdash;
                    }
                    else if(_BIST_TEST_MODE == EN_BIST_TEST_UI_PROCESSING)
                    {
                        u16TempID = en_str_Testing3dot;
                    }
                    else if(u8DQSM1[0] >= (u8DQSM1[1]+0x22))
                    {
                        u16TempID = en_str_SUCCESS;
                    }
                    else
                    {
                        u16TempID = en_str_Fail;
                    }
                    break;
            #endif
                default:
                    break;
            }
        break;
    #endif
    case EN_DESIGN_PAGE_MIU_SSC:
#if ENABLE_SSC
                switch(u8Item)
                {
                    case 0:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.SscMIUEnable);

                    case 1:
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_M10)    // Janus,Maria10
                        {
                            CHAR_BUFFER[0] = ((stGenSetting.g_SSCSetting.MIUSscSpanKHzx10/10) == 0) ? ' ' : '0'+(stGenSetting.g_SSCSetting.MIUSscSpanKHzx10/10);
                            CHAR_BUFFER[1] = '0'+((stGenSetting.g_SSCSetting.MIUSscSpanKHzx10%10));
                            CHAR_BUFFER[2] = CHAR_SPACE;
                            CHAR_BUFFER[3] = CHAR_K;
                            CHAR_BUFFER[4] = CHAR_H;
                            CHAR_BUFFER[5] = CHAR_z;
                            CHAR_BUFFER[6] = 0;
                    return CHAR_BUFFER;
                    //return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.MIUSscSpanKHzx10);
                        }
#else
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.MIUSscSpanKHzx10);
#endif
                    case 2:
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_M10)    // Janus,Maria10
                        {
                            CHAR_BUFFER[0] = '0'+(stGenSetting.g_SSCSetting.MIUSscStepPercentagex100/10);
                            CHAR_BUFFER[1] = '.';
                            CHAR_BUFFER[2] = '0'+(stGenSetting.g_SSCSetting.MIUSscStepPercentagex100%10);
                            CHAR_BUFFER[3] = CHAR_SPACE;
                            CHAR_BUFFER[4] = '%';
                            CHAR_BUFFER[5] = 0;
                    return CHAR_BUFFER;
                            //return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.MIUSscStepPercentagex100);
                        }
#else
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.MIUSscStepPercentagex100);
#endif
                }
#endif
                break;
            case EN_DESIGN_PAGE_LVDS_SSC:
#if ENABLE_SSC
                switch(u8Item)
                {
                    case 0:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.SscLVDSEnale);

                    case 1:
                        {
                            CHAR_BUFFER[0] = ((stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10/100) == 0) ? ' ' : '0'+(stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10/100);
                            CHAR_BUFFER[1] = '0'+((stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10%100)/10);
                            CHAR_BUFFER[2] = '.';
                            CHAR_BUFFER[3] = '0'+(stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10%10);
                            CHAR_BUFFER[4] = CHAR_SPACE;
                            CHAR_BUFFER[5] = CHAR_K;
                            CHAR_BUFFER[6] = CHAR_H;
                            CHAR_BUFFER[7] = CHAR_z;
                            CHAR_BUFFER[8] = 0;
                    return CHAR_BUFFER;
                    //return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10);
                        }
                    case 2:
                        {
                            CHAR_BUFFER[0] = '0'+((stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100/100));
                            CHAR_BUFFER[1] = '.';
                    CHAR_BUFFER[2] = '0'+((stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100%100)/10);
                            CHAR_BUFFER[3] = '0'+(stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100%10);
                            CHAR_BUFFER[4] = CHAR_SPACE;
                            CHAR_BUFFER[5] = '%';
                            CHAR_BUFFER[6] = 0;
                    return CHAR_BUFFER;
                          //  return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100);
                        }
                    case 3:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.LVDSSwing);
                }
#endif
                break;
#if URSA_SSC_ENABLE
            case EN_DESIGN_PAGE_6MXX_SSC:
#if ENABLE_SSC
                switch(u8Item)
                {
                    case 0:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.SscUrsaMIU0Enable);
                    case 1:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.MIU0SscModulation);
                    case 2:
                        CHAR_BUFFER[0] = '0'+((stGenSetting.g_SSCSetting.MIU0SscPercentage/100));
                        CHAR_BUFFER[1] = '.';
                        CHAR_BUFFER[2] = '0'+((stGenSetting.g_SSCSetting.MIU0SscPercentage/10%10));
                        CHAR_BUFFER[3] = 0;
                        return CHAR_BUFFER;
                    case 3:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.SscUrsaMIU1Enable);
                    case 4:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.MIU1SscModulation);
                    case 5:
                        CHAR_BUFFER[0] = '0'+((stGenSetting.g_SSCSetting.MIU1SscPercentage/100));
                        CHAR_BUFFER[1] = '.';
                        CHAR_BUFFER[2] = '0'+((stGenSetting.g_SSCSetting.MIU1SscPercentage/10%10));
                        CHAR_BUFFER[3] = 0;
                        return CHAR_BUFFER;
                    case 6:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.SscUrsaLVDSEnable);
                    case 7:
                        return MApp_ZUI_API_GetU16String(stGenSetting.g_SSCSetting.LVDSSscModulation);
                    case 8:
                        CHAR_BUFFER[0] = '0'+((stGenSetting.g_SSCSetting.LVDSSscPercentage/100));
                        CHAR_BUFFER[1] = '.';
                        CHAR_BUFFER[2] = '0'+((stGenSetting.g_SSCSetting.LVDSSscPercentage%100)/10);
                        CHAR_BUFFER[3] = 0;
                        return CHAR_BUFFER;
                    case 9:
                        return MApp_ZUI_API_GetU16HexString(stGenSetting.g_SSCSetting.PanelSwing);
                }
#endif
                break;
#endif
        case EN_DESIGN_PAGE_SPECIAL_SET:
            switch(u8Item)
            {
                case 0: //
                    if (stGenSetting.g_Time.cAutoSleepFlag == EN_Time_AutoOff_Off)
                        u16TempID=en_str_Off;
                    else if (stGenSetting.g_Time.cAutoSleepFlag == EN_Time_AutoOff_On)
                        u16TempID=en_str_On;
                    break;
                case 1: //
                    if (!MDrv_Sys_IsWatchDogEnabled())
                        u16TempID=en_str_Off;
                    else
                        u16TempID=en_str_On;
                    break;

                case 2: //
                    {
                        if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_DesAdj_WhitePattern_Off)
                            u16TempID=en_str_Off;
                        else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_DesAdj_WhitePattern_White)
                            u16TempID=en_str_White;
                        else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_DesAdj_WhitePattern_Red)
                            u16TempID=en_str_Red;
                        else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_DesAdj_WhitePattern_Green)
                            u16TempID=en_str_Green;
                        else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_DesAdj_WhitePattern_Blue)
                            u16TempID=en_str_Blue;
                        else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_DesAdj_WhitePattern_Black)
                            u16TempID=en_str_Black;
                    }
                    break;

                #if ENABLE_PVR
                case 4: // Record All Function
                    {
                        if (stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel)
                            u16TempID=en_str_On;
                        else
                            u16TempID=en_str_Off;
                    }
                    break;
                #endif
                #if ENABLE_DESIGN_POWER_ON_MODE
                case 5: //
                    if (G_DESIGN_SETTING.stFacMiscSetting.u8PowerOnMode == POWERON_MODE_OFF)
                        u16TempID=en_str_Off;
                    else if (G_DESIGN_SETTING.stFacMiscSetting.u8PowerOnMode == POWERON_MODE_ON)
                        u16TempID=en_str_On;
                    else
                        u16TempID=en_str_Last;
                    break;
                #endif
                #if  MirrorEnable
                case 6:
                    //    printf("\n  panelMirror:%d [%s,%s,%d]\n",stGenSetting.g_SysSetting.g_MirrorEnable,__FILE__,__FUNCTION__,__LINE__);
                    if(stGenSetting.g_SysSetting.g_MirrorEnable)
                    {
                        u16TempID=en_str_On;
                    }
                    else
                    {
                        u16TempID=en_str_Off;
                    }
                      break;
                #endif
                #if ENABLE_ADJUST_TSCLOCK_PHASE
                case 7:
                {
                    return MApp_ZUI_API_GetU16HexString(msAPI_Demod_GetTSClockDivider());
                }
                case 8:
                {
                    return MApp_ZUI_API_GetU16HexString(msAPI_Demod_GetPhaseTuningNumber());
                }
                #endif
            }
        break;
        case EN_DESIGN_PAGE_VIF:
        #if ENABLE_VD_PACH_IN_CHINA
            switch(u8Item)
            {
                case 0: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.Vif_AGCREFNEGATIVE);
                    break;
                case 1: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.Vif_CR_KP);
                    break;
                case 2: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.Vif_CR_KI);
                    break;
                case 3: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION);
                    break;
                case 4: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.Vif_CLAMPGAIN_GAIN_OV_NEGATIVE);
                    break;
                case 5: //
                    {
                        int ChinaDESValue = G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX - 50;
                        printf("johnson---->%d\n",G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX);
                        int absChinaDESValue = abs(ChinaDESValue);
                        TCHAR * str = CHAR_BUFFER;
                        if (ChinaDESValue < 0)
                        {
                            *str++ = '-';
                        }
                        *str++ = absChinaDESValue / 10 + '0';
                        *str++ = '.';
                        *str++ = absChinaDESValue % 10 + '0';
                        *str = '\0';
                        return CHAR_BUFFER;
                    }
                case 6: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.Vif_CR_THR);
                    break;
                case 7: //
                {
                    char *ptr;
                    char ptr_head[10];
                    ptr = ptr_head;
                    //modify for complie error when is not A7
                    ptr[0]='0';//VIF_VERSION1;
                    ptr[1]='0';//VIF_VERSION2;
                    ptr[2]='5';//VIF_VERSION3;
                    ptr[3]=0;
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                }
            }
        #endif
        break;

        case EN_DESIGN_PAGE_VD:
        #if ENABLE_VD_PACH_IN_CHINA
            switch(u8Item)
            {
                case 0:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_D4);

                case 1:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_D5_Bit2);

                case 2:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_D8_Bit3210);

                case 3:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_D9_Bit0);

                case 4: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_LOW_BOUND);
                    break;

                case 5: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_D7_HIGH_BOUND);
                    break;

                case 6:
                    return MApp_ZUI_API_GetU16HexString((((U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_A0)<<8) + (U16)G_DESIGN_SETTING.stVDSetting.u8AFEC_A1);

                case 7: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_66_Bit76);

                case 8: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit7654);

                case 9: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_6E_Bit3210);
                    break;

                case 10: //
                    if(0x14 == G_DESIGN_SETTING.stVDSetting.u8AFEC_43)
                    {
                        u16TempID=en_str_OnText;
                    }
                    else if(0x74 == G_DESIGN_SETTING.stVDSetting.u8AFEC_43)
                    {
                        u16TempID=en_str_Off;
                    }
                    break;

                case 11: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_44);
                    break;

                case 12: //
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.u8AFEC_CB);
                    break;
                case 13:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.CF_2_ATV);
                    break;
                case 14:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.CF_2_AV);
                    break;
            }
        #endif
            break;

        case EN_DESIGN_PAGE_AUDIO:
        #if ENABLE_VD_PACH_IN_CHINA
            switch(u8Item)
            {
                case 0: //
                    if(G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV==1)
                    {
                        u16TempID=en_str_HIDEVL1;
                    }
                    else if(G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV==2)
                    {
                        u16TempID=en_str_HIDEVL2;
                    }
                    else if(G_DESIGN_SETTING.stVDSetting.AUDIO_HIDEV==3)
                    {
                        u16TempID=en_str_HIDEVL3;
                    }
                    else
                    {
                        u16TempID=en_str_Off;
                    }
                    break;

                case 1:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.AUDIO_NR);
                    break;
                case 2:
                    return MApp_ZUI_API_GetU16HexString(G_DESIGN_SETTING.stVDSetting.PRESCALE);
            }
        #endif
            break;

        case EN_DESIGN_PAGE_OTHER: //wing
            switch(u8Item)
            {
            #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
                (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
                (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
                (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
                 (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
                (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA) || \
                 (CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY))
                case 0:
                {
                    if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_FacAdj_WhitePattern_Off)
                        u16TempID=en_str_Off;
                    else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_FacAdj_WhitePattern_White)
                        u16TempID=en_str_White;
                    else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_FacAdj_WhitePattern_Red)
                        u16TempID=en_str_Red;
                    else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_FacAdj_WhitePattern_Green)
                        u16TempID=en_str_Green;
                    else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_FacAdj_WhitePattern_Blue)
                        u16TempID=en_str_Blue;
                    else if (stLMGenSetting.stMDesign_Adjust.enTMP_WHITE_PATTERN == EN_FacAdj_WhitePattern_Black)
                        u16TempID=en_str_Black;
                }
                break;
                case 1:
                {
                    if(0 == stLMGenSetting.stMDesign_Adjust.xvycc)
                    {
                        u16TempID = en_str_Off;
                    }
                    else if(1 == stLMGenSetting.stMDesign_Adjust.xvycc)
                    {
                        u16TempID = en_str_OnText;
                    }
                    break;
                }
                case 2:
                    {

                        if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {
                            u16TempID = en_str_DTV;
                        }
                        else if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {
                            u16TempID = en_str_ATV;
                        }
                        else
                        {
                            u16TempID = en_str_dashdash;
                        }

                    }
                    break;
                case 3:
                    printf("connection:%d\n",mdrv_uart_get_connection(E_UART_PORT0));
                    switch(uart_tmp)
                    {
                        case MS_UART_TYPE_HK:
                            u16TempID=en_str_HK;
                            break;
                        case MS_UART_TYPE_AEON:
                            u16TempID=en_str_AEON;
                            break;
                        case MS_UART_TYPE_VDEC:
                            u16TempID=en_str_VDEC;
                            break;
                        case MS_UART_TYPE_NONE:
                        default:
                            u16TempID=en_str_None; //avoid string table to large
                            break;
                    }

                break;

            #else
                case 0:
                 if(mdrv_uart_get_connection(E_UART_PORT0) == E_UART_PIU_UART0)
                    u16TempID=en_str_HK;
              #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
                 else if(mdrv_uart_get_connection(E_UART_PORT0) == E_UART_AEON_R2)
                     u16TempID=en_str_AEON;
              #else
                 else if(mdrv_uart_get_connection(E_UART_PORT0) == E_UART_AEON)
                     u16TempID=en_str_AEON;
              #endif
                 else if(mdrv_uart_get_connection(E_UART_PORT0) == E_UART_VDEC )
                     u16TempID=en_str_VDEC;
                 else if(mdrv_uart_get_connection(E_UART_PORT0) == E_UART_OFF )
                     u16TempID=en_str_None; //avoid string table to large
                break;
            #endif
            }
            break;
#if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION
             case EN_DESIGN_PAGE_OVERSCAN:
            switch(u8Item)
            {
                case 0: //reslution
      {
    U16 u16H, u16V, u16F;
    LPTSTR str = CHAR_BUFFER; //iu8Buffer_i = 0;

    if ( IsYPbPrInUse() )
    {
        if(g_PcadcModeSetting[MAIN_WINDOW].u8ModeIndex >= MApi_XC_GetTotalModeCount() )
        {
            return NULL;
        }

        u16V = MApp_PCMode_Get_VResolution( MAIN_WINDOW ,TRUE);

        if( u16V == 0 )//not get resolution yet , so return 0 , to avoid kill timer
            return NULL;

        __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
        str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
        if (MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & XC_MD_INTERLACE_BIT)
        {
            *str++ = CHAR_i;
        }
        else
        {
            *str++ = CHAR_p;
        }

        u16F = (MApi_XC_PCMonitor_Get_VFreqx10( MAIN_WINDOW ) + 5) / 10;
        if(u16F > 56 && u16F < 62)
        {
            u16F= 60;
        }
        else if(u16F > 46 && u16F < 52)
        {
            u16F= 50;
        }
        else if(u16F > 22 && u16F < 26)
        {
            u16F = 24;
        }
        else if(u16F > 28 && u16F < 32)
        {
            u16F = 30;
        }
        else
        {
            u16F= 60;
        }
        *str++ = CHAR_AT;
        __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
        str += MApp_ZUI_API_Strlen(str);
        *str++ = CHAR_H;
        *str++ = CHAR_z;
        *str = 0;
        return (MApp_IsSrcHasSignal(MAIN_WINDOW) == FALSE) ? NULL : CHAR_BUFFER;
    }
    else if ( IsVgaInUse() )
    {
        if(MApp_PCMode_GetCurrentState(MAIN_WINDOW) != E_PCMODE_STABLE_SUPPORT_MODE)    //(MApp_PCMode_SyncLossFlag() || g_bUnsupportMode || (g_bInputTimingStable!=TRUE))
        {
            return NULL;
        }
        else
        {
            u16H = MApp_PCMode_Get_HResolution( MAIN_WINDOW , TRUE);
            u16V = MApp_PCMode_Get_VResolution( MAIN_WINDOW , TRUE);
            u16F = MApi_XC_GetVerticalFrequency(MApp_PCMode_Get_Mode_Idx(MAIN_WINDOW)) / 10;
           if(u16F > 58 && u16F < 61)
            {
                u16F= 60;
            }
            if(u16F > 63 && u16F < 66)
            {
                u16F= 65;
            }
            else if(u16F > 68 && u16F < 71)
            {
                u16F= 70;
            }
            else if( u16F > 73 && u16F < 76)
            {
                u16F= 75;
            }
            __MApp_UlongToString( ( U32 )u16H, str, MApp_GetNoOfDigit( u16H ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
            *str++ = CHAR_x;
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
            *str++ = CHAR_AT;
            __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
            *str++ = CHAR_H;
            *str++ = CHAR_z;
            *str = 0;

            return CHAR_BUFFER;
        }
    }
    else if ( IsHDMIInUse() )
    {
        if (MApp_IsSrcHasSignal(MAIN_WINDOW) == FALSE)
            return NULL;

        u16V = MApp_PCMode_Get_VResolution(MAIN_WINDOW,FALSE);
        u16H = MApp_PCMode_Get_HResolution(MAIN_WINDOW,FALSE);
        if((u16V==0)||(u16H==0))
        {
            return NULL;
        }

        if ((u16H >= 710 && u16H <= 1540) && (u16V >= 470 && u16V <= 490))
        {
            u16V = 480;
        }
        else if ((u16H>=710 && u16H<=1540)&&(u16V > 566 && u16V < 586))
        {
            u16V = 576;
        }
        // 1280x720
        else if((u16V > 710 && u16V < 730) && (u16H> 1270 && u16H < 1290))
        {
            u16V = 720;
        }
        // 1920x1080
        else if((u16V > 1070 && u16V < 1090) && (u16H > 1910 && u16H < 1930))
        {
            u16V = 1080;
        }
        else
        {
            u16F = MApi_XC_PCMonitor_Get_VFreqx10( MAIN_WINDOW );
            if ((u16H >= 620&& u16H <= 670) && (u16V >= 470 && u16V <= 490))
            {
                u16V = 480;
                u16H = 640;
            }
            else if ((u16H >= 780&& u16H <= 840) && (u16V >= 580&& u16V <= 620))
            {
                u16V = 600;
                u16H = 800;
            }
            else if ((u16H >= 1000&& u16H <= 1050) && (u16V >= 740&& u16V <= 790))
            {
                u16V = 768;
                u16H = 1024;
            }
            else if( (u16H> 1270 && u16H < 1300)&&(u16V > 740 && u16V < 790))
            {
                u16V = 768;
                u16H = 1280;
            }
            else if( (u16H> 1300 && u16H < 1390)&&(u16V > 740 && u16V < 790))
            {
                u16V = 768;
                u16H = 1360;
            }
            else if ((u16H >= 1260&& u16H <= 1300) && (u16V >= 1000&& u16V <= 1250))
            {
                u16V = 1024;
                u16H = 1280;
            }
            else if ((u16H >= 1580&& u16H <= 1620) && (u16V >= 1180&& u16V <= 1220))
            {
                u16V = 1200;
                u16H = 1600;
            }
            else
            {
                ;
            }

            if(u16F > 560 && u16F < 620)
            {
                u16F= 60;
            }
            else if(u16F > 670 && u16F < 710)
            {
                u16F= 70;
            }
            else if(u16F >= 710 && u16F < 730)
            {
                u16F= 72;
            }
            else if( u16F > 730 && u16F < 770)
            {
                u16F= 75;
            }
            else if( u16F > 800 && u16F < 850)
            {
                u16F= 85;
            }
            else
            {
                u16F = (u16F+5)/10;
            }

            __MApp_UlongToString( ( U32 )u16H, str, MApp_GetNoOfDigit( u16H ) );
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_x;
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_AT;
            __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
                str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_H;
            *str++ = CHAR_z;
            *str = 0;
            return CHAR_BUFFER;
        }

        {
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str);
        }

        if (MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & XC_MD_INTERLACE_BIT)
        {
            *str++ = CHAR_i;
        }
        else
        {
            *str++ = CHAR_p;
        }
        u16F=MApi_XC_PCMonitor_Get_VFreqx10(MAIN_WINDOW);
        if( u16F > 550 )
        {// (60)
            u16F = 60;
        }
        else if( u16F > 450 )
        {// (50)
            u16F =50;
        }
        else if( u16F > 275 )
        {// (30)
            u16F = 30;
        }
        else if( u16F > 240 )
        {//(25P)
            u16F = 25;
        }
        else if( u16F > 230 )
        {//(24P)
            u16F = 24;
        }
        else if( u16F > 200 )
        {//(23P)
            u16F = 23;
        }
        *str++ = CHAR_AT;
        __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
        str += MApp_ZUI_API_Strlen(str);
        *str++ = CHAR_H;
        *str++ = CHAR_z;
        *str = 0;
        return CHAR_BUFFER;
    }
    else if(IsDTVInUse())
    {
        VDEC_DispInfo pinfo;
        BOOLEAN bRet = msAPI_VID_GetVidInfo(&pinfo);

        u16V = pinfo.u16VerSize;

        if (u16V >= 470 && u16V <= 490)
        {
            u16V = 480;
        }
        else if (u16V > 566 && u16V < 586)
        {
            u16V = 576;
        }
        else if(u16V > 710 && u16V < 730)
        {
            u16V = 720;
        }
        else if(u16V > 1070 && u16V < 1090)
        {
            u16V = 1080;
        }

        if(MApp_IsSrcHasSignal(MAIN_WINDOW) && bRet )//if(u16V > 0)
        {
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );

            if(pinfo.u8Interlace == 1)
                *str++ = CHAR_i;
            else
                *str++ = CHAR_p;

            *str = 0;

            return CHAR_BUFFER;
        }
        else
            return NULL;
    }
    else
    {
         if (MApp_IsSrcHasSignal(MAIN_WINDOW) == FALSE)
              return NULL;
    #if 1
        switch ( mvideo_vd_get_videosystem() )
        {
            case SIG_NTSC:
                *str++ = 'N';
                *str++ = 'T';
                *str++ = 'S';
                *str++ = 'C';
                *str = 0;
                break;

            case SIG_NTSC_443:
                *str++ = 'N';
                *str++ = 'T';
                *str++ = 'S';
                *str++ = 'C';
                *str++ = '4';
                *str++ = '4';
                *str++ = '3';
                *str = 0;
                break;

            case SIG_PAL:
                *str++ = 'P';
                *str++ = 'A';
                *str++ = 'L';
                *str = 0;
                break;

            case SIG_PAL_M:
                *str++ = 'P';
                *str++ = 'A';
                *str++ = 'L';
                *str++ = '-';
                *str++ = 'M';
                *str = 0;
                break;

            case SIG_PAL_NC:
                *str++ = 'P';
                *str++ = 'A';
                *str++ = 'L';
                *str++ = '-';
                *str++ = 'N';
                *str++ = 'c';
                *str = 0;
                break;

            case SIG_SECAM:
                *str++ = 'S';
                *str++ = 'E';
                *str++ = 'C';
                *str++ = 'A';
                *str++ = 'M';
                *str = 0;
                break;

            default:
                return NULL;
        }
    #else
        switch ( mvideo_vd_get_videosystem() )
        {
            case SIG_NTSC:
            case SIG_NTSC_443:
                //u16TempID = en_str_resolution_480i;
                *str++ = '4';
                *str++ = '8';
                *str++ = '0';
                *str++ = CHAR_i;
                *str = 0;
                break;
            case SIG_PAL:
            case SIG_PAL_M:
            case SIG_PAL_NC:
            case SIG_SECAM:
                //u16TempID = en_str_resolution_576i;
                *str++ = '5';
                *str++ = '7';
                *str++ = '6';
                *str++ = CHAR_i;
                *str = 0;
                break;
            default:
                return NULL;
        }
    #endif
        return CHAR_BUFFER;
    }

    return NULL;
}
                //u16TempID=en_str_overscan_reslution;
                break;

                case 2: //h-size
                    return MApp_ZUI_API_GetU16String(G_OVERSCAN_HRatio);

                case 3: //h-position
                    return MApp_ZUI_API_GetU16String(G_OVERSCAN_HPOSITION);

                case 4: //v-size
                    return MApp_ZUI_API_GetU16String(G_OVERSCAN_VRatio);

                case 5: //v-position
                     return MApp_ZUI_API_GetU16String(G_OVERSCAN_VPOSITION);

            }
            break;
 #endif
 #if (ENABLE_NONLINEAR_CURVE)

            case EN_DESIGN_PAGE_NONLINEAR_CURVE:
            {
                P_MS_USER_NONLINEAR_CURVE pNonLinearCurve = NULL;
                E_DATA_INPUT_SOURCE src = DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW);



#if(ENABLE_PICTURE_NONLINEAR_CURVE)
                if(EN_NONLINEAR_BRIGHTNESS_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_BRIGHTNESS);
                }
                else if(EN_NONLINEAR_CONTRAST_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_CONTRAST);
                }
                else if(EN_NONLINEAR_SATURATION_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_SATURATION);
                }
                else if(EN_NONLINEAR_SHARPNESS_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_SHARPNESS);
                }
                else if(EN_NONLINEAR_HUE_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_HUE);
                }
                else if(EN_NONLINEAR_BACKLIGHT_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_BACKLIGHT);
                }
#endif
#if(ENABLE_SOUND_NONLINEAR_CURVE)
                if(EN_NONLINEAR_VOLUME_CURVE == _eNonlinearCurveOption[src])
                {
                    pNonLinearCurve = MApp_GetNonLinearCurve(NONLINEAR_CURVE_VOLUME);
                }
#endif

                if(pNonLinearCurve==NULL)
                {
                    MApp_Fatal_Error("NULL POINTER\n", __FUNCTION__);
                    CHAR_BUFFER[0] = 'N';
                    CHAR_BUFFER[1] = 'G';
                    CHAR_BUFFER[2] = 0;
                    return CHAR_BUFFER;
                }


                switch(u8Item)
                {
                    case 0:
                        u16TempID = _MApp_ZUI_ACT_GetNonlinearCurveOption(_eNonlinearCurveOption[src]);
                        break;

                    case 1:
                        return MApp_ZUI_API_GetU16String(pNonLinearCurve->u8OSD_0);

                    case 2:
                        return MApp_ZUI_API_GetU16String(pNonLinearCurve->u8OSD_25);

                    case 3:
                        return MApp_ZUI_API_GetU16String(pNonLinearCurve->u8OSD_50);

                    case 4:
                        return MApp_ZUI_API_GetU16String(pNonLinearCurve->u8OSD_75);

                    case 5:
                        return MApp_ZUI_API_GetU16String(pNonLinearCurve->u8OSD_100);

                }
                break;
            }
#endif

        default:
            break;
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return NULL; //for empty string
}

////////////////////////////////////////////////////////
#if ( (ENABLE_USB || ENABLE_USB_2 || ENABLE_USB_3 || ENABLE_USB_4) && ENABLE_FILESYSTEM )
#ifndef MSOS_TYPE_LINUX
extern U8 MDrv_USBGetPortEnableStatus(void);
extern void MApp_ZUI_SwUpdate_ProgressBar(U8 percent);
extern void msAPI_BLoader_Reboot(void);
#endif
#endif

BOOLEAN MApp_ZUI_ACT_ExecuteDesignMenuAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_DESIGN_MENU_GOTO_BAR_ADJUST:
            if(_eDesignMenuPage == EN_DESIGN_PAGE_SW_INFO_PAGE/*||_eDesignMenuPage == EN_DESIGN_PAGE_ADC_ADJUST||*/
               //|| _eDesignMenuPage == EN_DESIGN_PAGE_PICTURE_MODE // || _eDesignMenuPage == EN_DESIGN_PAGE_WHITE_BALANCE
               )
            {
               if(MApp_ZUI_API_GetFocus() == HWND_DESIGN_MENU_ITEM0)
               {
                  return TRUE;
               }
            }
            //skip resolution bar setting
            if(_eDesignMenuPage == EN_DESIGN_PAGE_ROOT &&  MApp_ZUI_API_GetFocus() == HWND_DESIGN_MENU_ITEM0)
            {
               return TRUE;
            }
            //WDT should not be show design menu bar,it should be not for user to change
            if(GetDesignMenuItemu16StringID(_eDesignMenuPage,_MApp_ZUI_ACT_DesignMenuWindowMapToIndex(MApp_ZUI_API_GetFocus())) == en_str_WDT)
            {
                return TRUE;
            }
        #if ENABLE_AUTO_DQS_Design
            if(_eDesignMenuPage == EN_DESIGN_PAGE_BIST_TEST)
            {
               return TRUE;
            }
        #endif
            if(_MApp_ZUI_ACT_GetDesignMenuValueText(_MApp_ZUI_ACT_DesignMenuWindowMapToIndex(MApp_ZUI_API_GetFocus())) == NULL)
            {
               return TRUE;
            }
            _eDesignBarInfo.pre_item = MApp_ZUI_API_GetFocus();
            _eDesignBarInfo.cur_item = HWND_DESIGN_MENU_BAR_TEXT;
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BG_TRANSPARENT, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BAR_TRANS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_DESIGN_MENU_BAR);
            return TRUE;

        case EN_EXE_DESIGN_MENU_EXIT_BAR_ADJUST:
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BAR_TRANS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BG_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_LIST, SW_SHOW);
            if(_eDesignMenuPage == EN_DESIGN_PAGE_QMAP_PAGE)
            {
                  MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP1, SW_HIDE);
                  MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_HOT_KEY_HELP2, SW_HIDE);
                  MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_INPUT_INFO, SW_SHOW);
                  MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BOARD_INFO, SW_HIDE);

            }
            _MApp_ZUI_ACT_DesignMenuInitPage(_eDesignMenuPage);
            MApp_ZUI_API_SetFocus(_eDesignBarInfo.pre_item);
            return TRUE;

        case EN_EXE_BIST_TEST:
        #if ENABLE_AUTO_DQS_Design
            if(_eDesignMenuPage == EN_DESIGN_PAGE_BIST_TEST)
            {
                _BIST_TEST_MODE = EN_BIST_TEST_UI_PROCESSING;
                MApp_ZUI_API_InvalidateWindow(HWND_DESIGN_MENU_ITEM0_VALUE);
                _MApp_ZUI_API_WindowProcOnIdle();
                MDrv_MIU_AutoDQS_Design();
                _BIST_TEST_MODE = EN_BIST_TEST_UI_END;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DESIGN_MENU_LIST);
            }
        #endif
            return TRUE;

        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetOSDPageState = STATE_OSDPAGE_CLEAN_UP;

            #if ENABLE_DMP
            if(UI_INPUT_SOURCE_DMP == UI_INPUT_SOURCE_TYPE)
            {
                _enTargetOSDPageState = STATE_OSDPAGE_GOTO_DMP;
            }
            #endif

            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetOSDPageState = STATE_OSDPAGE_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_DESIGN_MENU_PREV_PAGE:
           #if(LOG_DESIGNMENU_SHOWITEM)
             {//  for 返回上一页时总是选中第一项的Bug
                U8 u8Index = GetDesignPreMenuItemIndex(_eDesignMenuPage);
                _MApp_ZUI_ACT_DesignMenuPrevPage(_MApp_ZUI_ACT_DesignMenuWindowMapToIndex(MApp_ZUI_API_GetFocus()));
                _MApp_ZUI_ACT_DesignMenuInitPage(_eDesignMenuPage);
                if(u8Index!=0xFF)
                    MApp_ZUI_API_SetFocus(_DesignMenuItemHwndList[u8Index]);
             }
           #else
             _MApp_ZUI_ACT_DesignMenuPrevPage(_MApp_ZUI_ACT_DesignMenuWindowMapToIndex(MApp_ZUI_API_GetFocus()));
             _MApp_ZUI_ACT_DesignMenuInitPage(_eDesignMenuPage);
           #endif
            return TRUE;

        case EN_EXE_DESIGN_MENU_NEXT_PAGE:
            printf("[%s, %d, %s]\n", __FILE__, __LINE__, __FUNCTION__);
            if(_eDesignMenuPage == EN_DESIGN_PAGE_QMAP_PAGE)
            {
                printf("[%s, %d, %s]\n", __FILE__, __LINE__, __FUNCTION__);
                //printf("========== Get Focus [%u] ==========\n", (U16)MApp_ZUI_API_GetFocus());
                if(MApp_ZUI_API_GetFocus() != HWND_DESIGN_MENU_BG_TRANSPARENT)
                {
                    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BG_TRANSPARENT, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_DESIGN_MENU_BG_TRANSPARENT);
                }
                else
                {
                    DESIGN_MENU_PAGE _ePrevPage = EN_DESIGN_PAGE_QMAP_PAGE;
                    U8 u8ShowItem = 0;

                    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DESIGN_MENU_BG_TRANSPARENT, SW_HIDE);
                    u8ShowItem = _u8IPIndex%(COUNTOF(_DesignMenuItemHwndList));
                    _MApp_ZUI_ACT_DesignMenuInitPage(_ePrevPage);
                    MApp_ZUI_API_SetFocus(_DesignMenuItemHwndList[u8ShowItem]);
                }
            }
        #if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
            else if(_eDesignMenuPage == EN_DESIGN_PAGE_ROOT &&
                MApp_ZUI_API_GetFocus() == HWND_DESIGN_MENU_ITEM10)
            {
                printf("\r\n Begin CI+ Upgrade! \n");
                MApp_ZUI_API_InvalidateAllSuccessors(MApp_ZUI_API_GetFocus());
                MApp_WriteCiPlus_Key();
                return TRUE;
            }
        #endif
            else if(_eDesignMenuPage == EN_DESIGN_PAGE_PICTURE_MODE)
            {
                printf("[%s, %d, %s]\n", __FILE__, __LINE__, __FUNCTION__);
                MApp_CopySubColorDataToAllInput();
            }
            else
            {
                printf("[%s, %d, %s]\n", __FILE__, __LINE__, __FUNCTION__);
                _MApp_ZUI_ACT_DesignMenuNextPage(
                    _MApp_ZUI_ACT_DesignMenuWindowMapToIndex(MApp_ZUI_API_GetFocus()));
                    _MApp_ZUI_ACT_DesignMenuInitPage(_eDesignMenuPage);
            }
            return TRUE;

        case EN_EXE_QMAP_PREV_PAGE:
            if(_eDesignMenuPage == EN_DESIGN_PAGE_QMAP_PAGE)
             {
                BOOLEAN _bChangePage;
                 _bChangePage = FALSE;

                 if(_u8IPIndex == 0)
                 {
                     _u8IPIndex = _u8IPNumber - 1;
                 }
                 else
                 {
                     _u8IPIndex--;
                 }
                //printf("-------- PREV _u8IPIndex [%bu] --------\n", _u8IPIndex);
                 if(MApp_ZUI_API_GetFocus() == HWND_DESIGN_MENU_ITEM0)
                 {
                     _MApp_ZUI_ACT_QMAPPrevPage();
                     return TRUE;
                 }
             }
             return FALSE;

        case EN_EXE_QMAP_NEXT_PAGE:
            if(_eDesignMenuPage == EN_DESIGN_PAGE_QMAP_PAGE)
             {
                 BOOLEAN _bChangePage;
                 _bChangePage = FALSE;
                 if((_u8IPIndex != 0) && (((_u8IPIndex+1)%(COUNTOF(_DesignMenuItemHwndList))) == 0))
                 {
                     _bChangePage = TRUE;
                 }
                 if(_u8IPIndex == (_u8IPNumber-1))
                 {
                     _u8IPIndex = 0;
                     _bChangePage = TRUE;
                 }
                 else
                 {
                     _u8IPIndex++;
                 }
                 //printf("-------- NEXT _u8IPIndex [%bu] --------\n", _u8IPIndex);
                 if(_bChangePage)
                 {
                     _MApp_ZUI_ACT_QMAPNextPage();
                     return TRUE;
                 }
             }
             return FALSE;

        case EN_EXE_QMAP_PAGE_DOWN:
            if(_eDesignMenuPage == EN_DESIGN_PAGE_QMAP_PAGE)
            {
                DESIGN_MENU_PAGE _ePrevPage = EN_DESIGN_PAGE_QMAP_PAGE;
                U8 u8ShowItem = 0;

                if(_u8IPIndex == (_u8IPNumber-1))
                {
                    _u8IPIndex = 0;
                }
                else if((_u8IPIndex + (U8)(COUNTOF(_DesignMenuItemHwndList))) > (_u8IPNumber-1))
                {
                    _u8IPIndex = (_u8IPNumber - 1);
                }
                else
                {
                    _u8IPIndex = _u8IPIndex + (COUNTOF(_DesignMenuItemHwndList));
                }
                u8ShowItem = _u8IPIndex%(COUNTOF(_DesignMenuItemHwndList));
                _MApp_ZUI_ACT_DesignMenuInitPage(_ePrevPage);
                MApp_ZUI_API_SetFocus(_DesignMenuItemHwndList[u8ShowItem]);
            }
            return FALSE;

        case EN_EXE_QMAP_PAGE_UP:
            if(_eDesignMenuPage == EN_DESIGN_PAGE_QMAP_PAGE)
            {
                DESIGN_MENU_PAGE _ePrevPage = EN_DESIGN_PAGE_QMAP_PAGE;
                U8 u8ShowItem = 0;

                if(_u8IPIndex == 0)
                {
                    _u8IPIndex = (_u8IPNumber - 1);
                }
                else if(_u8IPIndex < (COUNTOF(_DesignMenuItemHwndList)))
                {
                    _u8IPIndex = 0;
                }
                else
                {
                    _u8IPIndex = _u8IPIndex - (COUNTOF(_DesignMenuItemHwndList));
                }
                u8ShowItem = _u8IPIndex%(COUNTOF(_DesignMenuItemHwndList));
                _MApp_ZUI_ACT_DesignMenuInitPage(_ePrevPage);
                MApp_ZUI_API_SetFocus(_DesignMenuItemHwndList[u8ShowItem]);
            }
            return FALSE;

        case EN_EXE_DESIGN_MENU_ADJ_DEC:
        case EN_EXE_DESIGN_MENU_ADJ_INC:
        {
            printf("%d\n",__LINE__);
            if(MApp_ZUI_API_GetFocus() == HWND_DESIGN_MENU_ITEM0)
            {
              if(_eDesignMenuPage == EN_DESIGN_PAGE_ROOT || EN_DESIGN_PAGE_SW_INFO_PAGE|| // EN_DESIGN_PAGE_ADC_ADJUST||
                  EN_DESIGN_PAGE_PICTURE_MODE // ||EN_DESIGN_PAGE_WHITE_BALANCE
                  )
                 {
                  printf("%d\n",__LINE__);
                        REDRAW_TYPE eRedraw = _MApp_ZUI_ACT_DesignMenuDecIncValue(
                       _MApp_ZUI_ACT_DesignMenuWindowMapToIndex(
                        MApp_ZUI_API_GetFocus()),
                        act==EN_EXE_DESIGN_MENU_ADJ_INC);

                       if (eRedraw == EN_REDRAW_ITEM)
                       {
                               MApp_ZUI_API_InvalidateAllSuccessors(MApp_ZUI_API_GetFocus());
                       }
                       else if (eRedraw == EN_REDRAW_LIST)
                       {
                               MApp_ZUI_API_InvalidateAllSuccessors(HWND_DESIGN_MENU_LIST);
                       }
                 }
              else
              {
                   return TRUE;
              }
            }
            else
            {
                printf("%d\n",__LINE__);
                    REDRAW_TYPE eRedraw = _MApp_ZUI_ACT_DesignMenuDecIncValue(
                   _MApp_ZUI_ACT_DesignMenuWindowMapToIndex(
                    _eDesignBarInfo.pre_item),
                    act==EN_EXE_DESIGN_MENU_ADJ_INC);

                   if (eRedraw == EN_REDRAW_ITEM)
                   {
                         MApp_ZUI_API_InvalidateAllSuccessors(HWND_DESIGN_MENU_BAR);
                   }
                   else if (eRedraw == EN_REDRAW_LIST)
                   {
                         MApp_ZUI_API_InvalidateAllSuccessors(HWND_DESIGN_MENU_LIST);
                   }
            }
            return TRUE;
        }
    #if ((ENABLE_EXTERN_MFC_CHIP)||ENABLE_6M40_4KX2K_PROCESS)
        case EN_EXE_DESIGN_MENU_UPDATA_MEMC:
          #if ( (ENABLE_USB || ENABLE_USB_2 || ENABLE_USB_3 || ENABLE_USB_4) && ENABLE_FILESYSTEM )
          #ifndef MSOS_TYPE_LINUX
                 {
                      U8 u8PortEnStatus = 0;

                     MApp_UsbDownload_USB_UpDate_SetMFCPort();

                      printf("USB MFC SW Update!\n");
                      u8PortEnStatus = MDrv_USBGetPortEnableStatus();
                      if((u8PortEnStatus & BIT0) == BIT0)
                      {
                          MApp_UsbDownload_Init(BIT0, MApp_ZUI_SwUpdate_ProgressBar);
                      }
                      else if((u8PortEnStatus & BIT1) == BIT1)
                      {
                          MApp_UsbDownload_Init(BIT1, MApp_ZUI_SwUpdate_ProgressBar);
                      }
                      else
                      {
                          MApp_UsbDownload_USB_UpDate_SetHKPort();
                          printf("Error> Unknown USB port\n");
                           return TRUE;
                      }

                      if(!MW_UsbDownload_Search())
                      {
                          MApp_UsbDownload_USB_UpDate_SetHKPort();
                           return TRUE;
                      }

          #if 1//example for module check.
                      MW_UsbDownload_SetDownloadType(DL_CK_MODULE);//Enable Module Check
                      printf("+++Enable Module Check\n");
                      if (MW_UsbDownload_Start())
                      {
                          msAPI_BLoader_Reboot();
                      }
                      else
                      {
                          printf("+++Module is mis-match\n");
                          if(MW_UsbDownload_GetErrorType() == DL_ERROR_MODULE)//Module is mis-match
                          {
                              printf("+++Download again\n");
                              MW_UsbDownload_SetDownloadType(DL_CK_NONE);//Disable Module Check
                              if (MW_UsbDownload_Start())//Download again.
                              {
                                  msAPI_BLoader_Reboot();
                              }
                          }
                      }
          #else //Normal
                      if (MW_UsbDownload_Start())
                      {
                          msAPI_BLoader_Reboot();
                      }
          #endif
              }
          #else
              printf("Un-support USB Update\n");
          #endif

          #endif

                return TRUE;
     #endif
        default:
            return FALSE;
   }
}
LPTSTR MApp_ZUI_ACT_GetDesignMenuDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    U8 u8Item;
    U8 i;

    //step1: special cases: title
    if (hwnd == HWND_DESIGN_MENU_TITLE)
    {
        switch(_eDesignMenuPage)
        {
            case EN_DESIGN_PAGE_ROOT:
                u16TempID = en_str_Design_Setting;
                break;
/*
            case EN_DESIGN_PAGE_ADC_ADJUST:
                u16TempID = en_str_ADC_ADJUST;
                break;
*/
#if ENABLE_PANEL_BIN
            case EN_DESIGN_PAGE_PANEL_PARAMETER:
                u16TempID = en_str_Panel_Parameter;
                break;
#endif


#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
            case EN_DESIGN_WHITE_BALANCE_PATTERN:
                u16TempID = en_str_WhiteBalanceTestPattern;
                break;
#endif

            case EN_DESIGN_PAGE_PICTURE_MODE:
                u16TempID = en_str_Picture_Mode;
                break;
/*
            case EN_DESIGN_PAGE_WHITE_BALANCE:
                u16TempID = en_str_White_balance;
                break;
*/
            case EN_DESIGN_PAGE_QMAP_PAGE:
                u16TempID = en_str_QMAP_ADJUST;
                break;
            #if ENABLE_PIP
            case EN_DESIGN_PAGE_PIP_POP:
                u16TempID = en_str_PIPslashPOP;
                break;
            #endif
            case EN_DESIGN_PAGE_SW_INFO_PAGE:
                u16TempID = en_str_Info;
                break;
            #if ENABLE_AUTOTEST
            case EN_DESIGN_PAGE_BMTEST_PAGE:
                u16TempID = en_str_BMTEST;
                break;
            #endif
#if ENABLE_AUTO_DQS_Design
            case EN_DESIGN_PAGE_BIST_TEST:
                u16TempID = en_str_BIST_TEST;
                break;
#endif
            case EN_DESIGN_PAGE_PEQ:
                u16TempID = en_str_PEQ;
                break;
            case EN_DESIGN_PAGE_SSC:
                u16TempID = en_str_SSC;
                break;
            case EN_DESIGN_PAGE_MIU_SSC:
                u16TempID = en_str_MIU_SSC;
                break;
            case EN_DESIGN_PAGE_LVDS_SSC:
                u16TempID = en_str_LVDS_SSC;
                break;
        #if URSA_SSC_ENABLE
            case EN_DESIGN_PAGE_6MXX_SSC:
                u16TempID = en_str_6MXX_SSC;
                break;
         #endif
            case EN_DESIGN_PAGE_SPECIAL_SET:
                u16TempID = en_str_SPECIAL_SET;
                break;
            case EN_DESIGN_PAGE_OTHER:
                u16TempID = en_str_Other; // en_str_UART_DEBUG;
                break;
#if ENABLE_SZ_DESIGN_OVER_SCAN_FUNCTION
            case EN_DESIGN_PAGE_OVERSCAN:
                 u16TempID = en_str_overscan_reslution;
                break;
#endif
 #if ENABLE_NONLINEAR_CURVE
            case EN_DESIGN_PAGE_NONLINEAR_CURVE:
                u16TempID = en_str_NONLINEAR;
                break;
 #endif
 #if ENABLE_CI
            case EN_DESIGN_PAGE_CI:
                   u16TempID = en_str_CI_Factory_Setting;
                break;
 #endif
            case EN_DESIGN_PAGE_NON_STANDARD:
                    u16TempID = en_str_Non_standard;
                break;
            case EN_DESIGN_PAGE_VIF:
                    u16TempID = en_str_VIF;
                break;
            case EN_DESIGN_PAGE_VD:
                    u16TempID = en_str_VD;
                break;
            case EN_DESIGN_PAGE_AUDIO:
                    u16TempID = en_str_Audio;
                break;
        default:
            break;
        }
        goto END;

    }

    u8Item = _MApp_ZUI_ACT_DesignMenuWindowMapToIndex(hwnd);

        //special case: board type in item name...

    if( hwnd == HWND_DESIGN_MENU_BOARD_INFO)
    {
        U8 VersionName[] = BOARD_NAME;
        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, VersionName,255);
    }

    //step2: value windows
    if (_DesignMenuItemHwndValueList[u8Item] == hwnd) //is value window...
    {
        return _MApp_ZUI_ACT_GetDesignMenuValueText(u8Item);
    }
    if(hwnd == HWND_DESIGN_MENU_BAR_TEXT)
    {
        u8Item = _MApp_ZUI_ACT_DesignMenuWindowMapToIndex(_eDesignBarInfo.pre_item);
        return MApp_ZUI_ACT_GetDesignMenuDynamicText(_DesignMenuItemHwndNameList[u8Item]);
    }
    if(hwnd == HWND_DESIGN_MENU_BAR_OPTION)
    {
        u8Item = _MApp_ZUI_ACT_DesignMenuWindowMapToIndex(_eDesignBarInfo.pre_item);
        return _MApp_ZUI_ACT_GetDesignMenuValueText(u8Item);
    }
    if (hwnd == HWND_DESIGN_MENU_INPUT_TYPE)
    {
        //printf("MApp_ZUI_ACTfactorymenu.c Line %d : %s\n", __LINE__, MDrv_PQ_GetSrcTypeName(MAIN_WINDOW));
        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)MDrv_PQ_GetSrcTypeName(PQ_MAIN_WINDOW), 255);
    }
    if (hwnd == HWND_DESIGN_SW_INFO_TEXT)
    {
                #if 1
                    {
                    char *ptr;
                    char ptr_head[128];
                    unsigned char * pu8Temp;
                    U8 u8Data,u8Temp_i,u8Temp_j;
                    U8 u8ASCII_Mapping[16] = {'0','1','2','3','4','5','6','7','8','9','A',
                        'B','C','D','E','F'};
                    unsigned char Customer_info_others[48];
                    U32 u32Temp;
                    ptr = ptr_head;
                    //<1>.For Customer ID
                    //ptr = strcpy(ptr, "CID:" );
                    //ptr +=4;

                    ptr = memcpy(ptr, &Customer_info[0],4);
                    ptr +=4;
                    *ptr = '-';
                    ptr++;

                    //<2>.For Customer ID
                    //ptr = strcpy(ptr, "MID:" );
                    //ptr +=4;
                    ptr = memcpy(ptr, &Customer_info[4],4);
                    ptr +=4;
                    *ptr = '-';
                    ptr++;

                    //<3>.For Customer ID
                    //ptr = strcpy(ptr, "Chip:" );
                    //ptr +=5;

                    ptr = memcpy(ptr, &Customer_info[8],4);
                    ptr +=4;
                    *ptr = '-';
                    ptr++;

                    //<3>.To prepare the Customer Info Others
                    u8Temp_i=0;
                    //Get SW Project Name:01 => Chakra
                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_SW_PROJECT];
                    u8Data = ((*(pu8Temp))>> 4);
                    Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
                    u8Data = (*(pu8Temp) & 0x0F);
                    Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
                    Customer_info_others[u8Temp_i++] =  '-';

                   //Get SW Project Generation:01 => 1.0
                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_SW_PROJECT_GENERATION];
                    u8Data = ((*(pu8Temp))>> 4);
                    Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
                    u8Data = (*(pu8Temp) & 0x0F);
                    Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
                    Customer_info_others[u8Temp_i++] =  '-';

                    //Get Product Type:TV-01
                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_PRODUCT];
                    u8Data = ((*(pu8Temp))>> 4);
                    Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
                    u8Data = (*(pu8Temp) & 0x0F);
                    Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
                    Customer_info_others[u8Temp_i++] =  '-';

                    //Get TV System
                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_TV_SYSTEM];
                    u8Data = ((*(pu8Temp))>> 4);
                    Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
                    u8Data = (*(pu8Temp) & 0x0F);
                    Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
                    Customer_info_others[u8Temp_i++] =  '-';

                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_LABEL];
                    u32Temp = ((*(pu8Temp+2))<<16)|((*(pu8Temp+1))<<8)|((*(pu8Temp+0)));

                    for (u8Temp_j=0;u8Temp_j<6;u8Temp_j++)
                    {
                        u8Data = u32Temp%10;
                        u32Temp = u32Temp/10;
                        Customer_info_others[u8Temp_i+5-u8Temp_j] = u8ASCII_Mapping[u8Data];
                    }
                    u8Temp_i +=6;
                    Customer_info_others[u8Temp_i++] =  '-';


                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_CL];
                    u32Temp = ((*(pu8Temp+2))<<16)|((*(pu8Temp+1))<<8)|((*(pu8Temp+0)));
                    for (u8Temp_j=0;u8Temp_j<8;u8Temp_j++)
                    {
                        u8Data = u32Temp%10;
                        u32Temp = u32Temp/10;
                        Customer_info_others[u8Temp_i+7-u8Temp_j] = u8ASCII_Mapping[u8Data];
                    }
                    u8Temp_i +=8;
                    Customer_info_others[u8Temp_i++] =  '-';

                    //Get SW Release Purpose:01 => 1.0
                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_RELEASE_PURPOSE];
                    u8Data = ((*(pu8Temp))>> 4);
                    Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
                    u8Data = (*(pu8Temp) & 0x0F);
                    Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];
                    Customer_info_others[u8Temp_i++] =  '-';

                    //Get CUP type
                    pu8Temp = &CID_Buf[CUSTOMER_INFO_START_CPU_TYPE];
                    u8Data = ((*(pu8Temp))>> 4);
                    Customer_info_others[u8Temp_i++] = u8ASCII_Mapping[u8Data];
                    u8Data = (*(pu8Temp) & 0x0F);
                    Customer_info_others[u8Temp_i++] =  u8ASCII_Mapping[u8Data];

                    ptr = memcpy(ptr, &Customer_info_others[0],(u8Temp_i));
                    ptr +=(u8Temp_i);
                    *ptr = 0;
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                }
        #else
                {
                  #if 0
                    char *ptr;
                    char ptr_head[128];

                    ptr = ptr_head;
                    ptr = strcpy(ptr, SWVersionName );
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                  #else // Modifed it by coverity_0544
                    char ptr_head[128];
                    strcpy(ptr_head, SWVersionName );
                    return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, strlen(ptr_head));
                  #endif
                }
                break;
        #endif
    }
    //step3: item name
    if(_eDesignMenuPage == EN_DESIGN_PAGE_QMAP_PAGE )
    {
        U8 u8IPIdx, u8IPNum;

        u8IPIdx = ((_u8IPIndex/(COUNTOF(_DesignMenuItemHwndList)))*(COUNTOF(_DesignMenuItemHwndList)))+u8Item;
        u8IPNum = _u8IPNumber;
        if(u8IPIdx < u8IPNum)
        {
            //printf("================= IP:%u [%s]\n", u8IPIdx, MDrv_PQ_GetIPName(u8IPIdx));
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)MDrv_PQ_GetIPName(u8IPIdx), 255);
        }
    }
    else
    {
        for (i = 0; i < COUNTOF(_DesignMenuItem); i++)
        {
          #if(LOG_DESIGNMENU_SHOWITEM)
            if ((_DesignMenuItem[i].eCurPage == _eDesignMenuPage) && GET_DESIGNMENU_SHOWITEM(_DesignMenuItem[i]) == u8Item)
          #else
            if (_DesignMenuItem[i].eCurPage == _eDesignMenuPage &&
                _DesignMenuItem[i].u8ShowItem == u8Item)
          #endif
            {
                u16TempID = _DesignMenuItem[i].u16StringID;
                break;
            }
        }
    }

END:
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return NULL; //for empty string
}

OSD_COLOR MApp_ZUI_ACT_GetDesignmenuDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, OSD_COLOR colorOriginal)
{
    UNUSED(type);
 #if ENABLE_AUTO_DQS_Design
    BOOLEAN BIST_TEST_COLOR = FALSE;
    if(_eDesignMenuPage == EN_DESIGN_PAGE_BIST_TEST)
    {
        if((_BIST_TEST_MODE == EN_BIST_TEST_UI_START)||
        ((u8DQSM0[0]==0x00)&&(_MApp_ZUI_ACT_DesignMenuWindowMapToIndex(hwnd)<=5))
        ||((u8DQSM1[0]==0x00)&&(_MApp_ZUI_ACT_DesignMenuWindowMapToIndex(hwnd)>5)))
            return colorOriginal;

        switch((U16)_MApp_ZUI_ACT_DesignMenuWindowMapToIndex(hwnd))
        {
            case 1:
                if(u8DQSM0[2] < (u8DQSM0[0]+0x22))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 2:
                if(u8DQSM0[2] < (u8DQSM0[0]+0x11))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 3:
                if(u8DQSM0[2] < (u8DQSM0[0]+0x00))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 4:
                if(u8DQSM0[0] < (u8DQSM0[1]+0x11))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 5:
                if(u8DQSM0[0] < (u8DQSM0[1]+0x22))
                    BIST_TEST_COLOR = TRUE;
                break;
       #if ENABLE_MIU_1
            case 6:
                if(u8DQSM1[2] < (u8DQSM1[0]+0x22))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 7:
                if(u8DQSM1[2] < (u8DQSM1[0]+0x11))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 8:
                if(u8DQSM1[2] < (u8DQSM1[0]+0x00))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 9:
                if(u8DQSM1[0] < (u8DQSM1[1]+0x11))
                    BIST_TEST_COLOR = TRUE;
                break;
            case 10:
                if(u8DQSM1[0] < (u8DQSM1[1]+0x22))
                    BIST_TEST_COLOR = TRUE;
                break;
       #endif
            default:
                break;
        }

        if(BIST_TEST_COLOR)
        {
            return DESIGN_MENU_CURRENT_TEXT_DISABLE_COLOR;
        }
        else
        {
            return colorOriginal;
        }
    }
#else
    UNUSED(hwnd);
#endif
    return colorOriginal;
}

/////////////////////////////////////////////////////////
// Customize Window Procedures

#undef MAPP_ZUI_ACTDESIGNMENU_C
