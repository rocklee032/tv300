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
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTEWBSCONFIRMFUNC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_GlobalFunction.h"
#include "MApp_UiMenuDef.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_ChannelChange.h"

////////////////////////////////////////////////////
//NOTE: when we are selecting country, don't modify the real one!!
#if(ENABLE_EWBS)
static EN_OSD_EWBS_AREA_SETTING _eEwbsArea = E_EWBS_DEFAULT;

static EN_OSD_EWBS_AREA_SETTING _eEwbsWideAreaZone = E_EWBS_DEFAULT;
static EN_OSD_EWBS_AREA_SETTING _eEwbsRegion = E_EWBS_DEFAULT;
static EN_OSD_EWBS_AREA_SETTING _eEwbsCity = E_EWBS_DEFAULT;

U8 u8Temp_EWBS_Num1 = 0;
U8 u8Temp_EWBS_Num2 = 0;
U8 u8Temp_EWBS_Num3 = 0;
U8 u8Temp_EWBS_Num4 = 0;

extern EN_OSD_EWBS_AREA_TYPE_SETTING eEwbsAreaType;

//Philippines
//Philippines wide area zone list
ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stPhilippinesWideAreaList[] =
{
    {OSD_WIDE_AREA_LUZON, en_str_Luzon},
    {OSD_WIDE_AREA_VISAYAS, en_str_Visayas},
    {OSD_WIDE_AREA_MINDANAO, en_str_Mindanao},
};

//Philippines region list
ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stLuzonRegionList[] =
{
    {OSD_REGION_NCR, en_str_NCR},
    {OSD_REGION_CAR, en_str_CAR},
    {OSD_REGION_ILOCOS_REGION, en_str_Ilocos_Region},
    {OSD_REGION_CAGAYAN_VALLEY, en_str_Cagayan_Valley},
    {OSD_REGION_CENTRAL_LUZON, en_str_Central_Luzon},
    {OSD_REGION_CALABARZON, en_str_Calabarzon},
    {OSD_REGION_MIMAROPA, en_str_Mimaropa},
    {OSD_REGION_BICOL_REGION, en_str_Bicol_Region},
};

ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stVisayasRegionList[] =
{
    {OSD_REGION_WESTERN_VISAYAS, en_str_Western_Visayas},
    {OSD_REGION_CENTRAL_VISAYAS, en_str_Central_Visayas},
    {OSD_REGION_EASTERN_VISAYAS, en_str_Eastern_Visayas},
};

ST_OSD_SELECTION_STRING_MAPPING_LIST _ZUI_TBLSEG stMindanaoRegionList[] =
{
    {OSD_REGION_ZAMBOANGA_PENINSULA, en_str_Zamboanga_Peninsula},
    {OSD_REGION_NORTHERN_MINDANAO, en_str_Northern_Mindanao},
    {OSD_REGION_DAVAO_REGION, en_str_Davao_Region},
    {OSD_REGION_SOCCSKSARGEN, en_str_Soccsksargen},
    {OSD_REGION_CARAGA, en_str_Caraga},
    {OSD_REGION_AUTONOMOUS_REGION_IN_MUSLIM_MINDANAO, en_str_ARMM},
};

//Philippines city list
ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stNCRCityList[] =
{
    {OSD_CITY_CALOOCAN, en_str_Caloocan, {1,0,5,7}},
    {OSD_CITY_LAS_PINAS, en_str_Las_Pinas, {1,0,5,8}},//
    {OSD_CITY_MAKATI, en_str_Makati, {1,0,5,9}},
    {OSD_CITY_MALABON, en_str_Malabon, {1,0,6,0}},
    {OSD_CITY_MANDALUYONG, en_str_Mandaluyong, {1,0,6,1}},
    {OSD_CITY_MANILA, en_str_Manila, {1,0,6,2}},
    {OSD_CITY_MARIKINA, en_str_Marikina, {1,0,6,3}},
    {OSD_CITY_MUNTINLUPA, en_str_Muntinlupa, {1,0,6,4}},
    {OSD_CITY_NAVOTAS, en_str_Navotas, {1,0,6,5}},
    {OSD_CITY_PARANAQUE, en_str_Paranaque, {1,0,6,6}},
    {OSD_CITY_PASAY, en_str_Pasay, {1,0,6,7}},
    {OSD_CITY_PASIG, en_str_Pasig, {1,0,6,8}},
    {OSD_CITY_PATEROS, en_str_Pateros ,{1,0,6,9}},
    {OSD_CITY_QUEZON_CITY, en_str_Quezon_City, {1,0,7,0}},
    {OSD_CITY_SAN_JUAN, en_str_San_Juan, {1,0,7,1}},
    {OSD_CITY_TAGUIG, en_str_Taguig, {1,0,7,2}},
    {OSD_CITY_VALENZUELA, en_str_Valenzuela, {1,0,7,3}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stCARCityList[] =
{
    {OSD_CITY_ABRA, en_str_Abra, {1,0,8,9}},
    {OSD_CITY_APAYAO, en_str_Apayao, {1,0,9,0}},
    {OSD_CITY_BAGUIO, en_str_Baguio, {1,0,9,1}},
    {OSD_CITY_BENGUET, en_str_Benguet, {1,0,9,2}},
    {OSD_CITY_IFUGAO, en_str_Ifugao, {1,0,9,3}},
    {OSD_CITY_KALINGA, en_str_Kalinga, {1,0,9,4}},
    {OSD_CITY_MT_PROVINCE, en_str_Mt_Province, {1,0,9,5}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stIlocosRegionCityList[] =
{
    {OSD_CITY_ILOCOS_NORTE, en_str_Ilocos_Norte, {1,1,2,1}},
    {OSD_CITY_ILOCOS_SUR, en_str_Ilocos_Sur, {1,1,2,2}},
    {OSD_CITY_LA_UNION, en_str_La_Union, {1,1,2,3}},
    {OSD_CITY_PAGASINAN, en_str_Pagasinan, {1,1,2,4}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stCagayanValleyCityList[] =
{
    {OSD_CITY_BATANES, en_str_Batanes, {1,1,5,3}},
    {OSD_CITY_CAGAYAN, en_str_Cagayan, {1,1,5,4}},
    {OSD_CITY_ISABELA, en_str_Isabela, {1,1,5,5}},
    {OSD_CITY_NUEVA_VIZCAYA, en_str_Nueva_Vizcaya, {1,1,5,6}},
    {OSD_CITY_QUIRINO, en_str_Quirino, {1,1,5,7}},
    {OSD_CITY_SANTIAGO, en_str_Santiago, {1,1,5,8}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stCentralLuzonCityList[] =
{
    {OSD_CITY_ANGELES, en_str_Angeles, {1,1,8,5}},
    {OSD_CITY_AURORA, en_str_Aurora, {1,1,8,6}},
    {OSD_CITY_BATAAN, en_str_Bataan, {1,1,8,7}},
    {OSD_CITY_BULACAN, en_str_Bulacan, {1,1,8,8}},
    {OSD_CITY_NUEVA_ECIJA, en_str_Nueva_Ecija, {1,1,8,9}},
    {OSD_CITY_OLONGAPO, en_str_Olongapo, {1,1,9,0}},
    {OSD_CITY_PAMPANGA, en_str_Pampanga, {1,1,9,1}},
    {OSD_CITY_TARLAC, en_str_Tarlac, {1,1,9,2}},
    {OSD_CITY_ZAMBALES, en_str_Zambales, {1,1,9,3}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stCalabarzonCityList[] =
{
    {OSD_CITY_BATANGAS, en_str_Batangas, {1,2,1,7}},
    {OSD_CITY_CAVITE, en_str_Cavite, {1,2,1,8}},
    {OSD_CITY_LAGUNA, en_str_Laguna, {1,2,1,9}},
    {OSD_CITY_LUCENA, en_str_Lucena, {1,2,2,0}},
    {OSD_CITY_QUEZON, en_str_Quezon, {1,2,2,1}},
    {OSD_CITY_RIZAL, en_str_Rizal, {1,2,2,2}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stMimaropaCityList[] =
{
    {OSD_CITY_MARINDUQUE, en_str_Marinduque, {1,2,4,9}},
    {OSD_CITY_OCCIDENTAL_MINDORO, en_str_Occidental_Mindoro, {1,2,5,0}},
    {OSD_CITY_ORIENTAL_MINDORO, en_str_Oriental_Mindoro, {1,2,5,1}},
    {OSD_CITY_PALAWAN, en_str_Palawan, {1,2,5,2}},
    {OSD_CITY_PUERTO_PRINCESA, en_str_Puerto_Princesa, {1,2,5,3}},
    {OSD_CITY_ROMBLON, en_str_Romblon, {1,2,5,4}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stBicolRegionCityList[] =
{
    {OSD_CITY_ALBAY, en_str_Albay, {1,2,8,1}},
    {OSD_CITY_CAMARINES_SUR, en_str_Camarines_Sur, {1,2,8,2}},
    {OSD_CITY_CAMARINES_NORTE, en_str_Camarines_Norte, {1,2,8,3}},
    {OSD_CITY_CATANDUANES, en_str_Catanduanes, {1,2,8,4}},
    {OSD_CITY_MASBATA, en_str_Masbata, {1,2,8,5}},
    {OSD_CITY_NAGA, en_str_Naga, {1,2,8,6}},
    {OSD_CITY_SORSOGON, en_str_Sorsogon, {1,2,8,7}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stWesternVisayasCityList[] =
{
    {OSD_CITY_AKLAN, en_str_Aklan, {1,5,6,9}},
    {OSD_CITY_ANTIQUE, en_str_Antique, {1,5,7,0}},
    {OSD_CITY_BACOLOD, en_str_Bacolod, {1,5,7,1}},
    {OSD_CITY_CAPIZ, en_str_Capiz, {1,5,7,2}},
    {OSD_CITY_GUIMARAS, en_str_Guimaras, {1,5,7,3}},
    {OSD_CITY_ILOILO, en_str_Iloilo, {1,5,7,4}},
    {OSD_CITY_ILOILO_CITY, en_str_Iloilo_City, {1,5,7,5}},
    {OSD_CITY_NEGROS_OCCIDENTAL, en_str_Negros_Occidental, {1,5,7,6}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stCentralVisayasCityList[] =
{
    {OSD_CITY_BOHOL, en_str_Bohol, {1,6,0,1}},
    {OSD_CITY_CEBU, en_str_Cebu, {1,6,0,2}},
    {OSD_CITY_CEBU_CITY, en_str_Cebu_City, {1,6,0,3}},
    {OSD_CITY_LAPU_LAPU, en_str_Lapu_Lapu, {1,6,0,4}},
    {OSD_CITY_NEGROS_ORIENTAL, en_str_Negros_Oriental, {1,6,0,5}},
    {OSD_CITY_SIQUIJOR, en_str_Siquijor, {1,6,0,6}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stEasternVisayasCityList[] =
{
    {OSD_CITY_BILIRAN, en_str_Biliran, {1,6,3,3}},
    {OSD_CITY_EASTERN_SAMAR, en_str_Eastern_Samar, {1,6,3,4}},
    {OSD_CITY_LEYTE, en_str_Leyte, {1,6,3,5}},
    {OSD_CITY_NORTHERN_SAMAR, en_str_Northern_Samar, {1,6,3,6}},
    {OSD_CITY_ORMOC, en_str_Ormoc, {1,6,3,7}},
    {OSD_CITY_SAMAR, en_str_Samar, {1,6,3,8}},
    {OSD_CITY_SOUTHERN_LEYTE, en_str_Southern_Leyte, {1,6,3,9}},
    {OSD_CITY_TACLOBAN, en_str_Tacloban, {1,6,4,0}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stZamboangaPeninsulaCityList[] =
{
    {OSD_CITY_ISABELA_CITY, en_str_Isabela_City, {2,0,8,1}},
    {OSD_CITY_ZAMBOANGA_CITY, en_str_Zamboanga_City, {2,0,8,2}},
    {OSD_CITY_ZAMBOANGA_DEL_NORTE, en_str_Zamboanga_del_Norte, {2,0,8,3}},
    {OSD_CITY_ZAMBOANGA_DEL_SUR, en_str_Zamboanga_del_Sur, {2,0,8,4}},
    {OSD_CITY_ZAMBOANGA_SIBUGAY, en_str_Zamboanga_Sibugay, {2,0,8,5}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stNorthernMindanaoCityList[] =
{
    {OSD_CITY_BUKIDNON, en_str_Bukidnon, {2,1,1,3}},
    {OSD_CITY_CAGAYAN_DE_ORO, en_str_Cagayan_de_Oro, {2,1,1,4}},
    {OSD_CITY_CAMIGUIN, en_str_Camiguin, {2,1,1,5}},
    {OSD_CITY_ILIGAN, en_str_Iligan, {2,1,1,6}},
    {OSD_CITY_LANAO_DEL_NORTE, en_str_Lanao_del_Norte, {2,1,1,7}},
    {OSD_CITY_MISAMIS_OCCIDENTAL, en_str_Misamis_Occidental, {2,1,1,8}},
    {OSD_CITY_MISAMIS_ORIENTA, en_str_Misamis_Oriental, {2,1,1,9}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stDavaoRegionCityList[] =
{
    {OSD_CITY_COMPOSTELA_VALLEY, en_str_Compostela_Valley, {2,1,4,5}},
    {OSD_CITY_DAVAO_CITY, en_str_Davao_City, {2,1,4,6}},
    {OSD_CITY_DAVAO_DEL_NORTE, en_str_Davao_del_Norte, {2,1,4,7}},
    {OSD_CITY_DAVAO_DEL_SUR, en_str_Davao_del_Sur, {2,1,4,8}},
    {OSD_CITY_DAVAO_ORIENTAL, en_str_Davao_Oriental, {2,1,4,9}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stSoccsksargenCityList[] =
{
    {OSD_CITY_COTABATO, en_str_Cotabato, {2,1,4,5}},
    {OSD_CITY_COTABATO_CITY, en_str_Cotabato_City, {2,1,4,6}},
    {OSD_CITY_GENERAL_SANTOS, en_str_General_Santos, {2,1,4,7}},
    {OSD_CITY_SARANGGANI, en_str_Saranggani, {2,1,4,8}},
    {OSD_CITY_SOUTH_COTABATO, en_str_South_Cotabato, {2,1,4,9}},
    {OSD_CITY_SULTAN_KUDARAT, en_str_Sultan_Kudarat, {2,1,4,9}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stCaragaCityList[] =
{
    {OSD_CITY_AGUSAN_DEL_NORTE, en_str_Agusan_del_Norte, {2,2,0,9}},
    {OSD_CITY_AGUSAN_DEL_SUR, en_str_Agusan_del_Sur, {2,2,1,0}},
    {OSD_CITY_BUTUAN, en_str_Butuan, {2,2,1,1}},
    {OSD_CITY_DINAGAT_ISLANDS, en_str_Dinagat_Islands, {2,2,1,2}},
    {OSD_CITY_SURIGAO_DEL_NORTE, en_str_Surigao_del_Norte, {2,2,1,3}},
    {OSD_CITY_SURIGAO_DEL_SUR, en_str_Surigao_del_Sur, {2,2,1,4}},
};

ST_EWBS_CITY_MAPPING_LIST _ZUI_TBLSEG stARMMCityList[] =
{

    {OSD_CITY_BASILAN, en_str_Basilan, {2,2,4,1}},
    {OSD_CITY_LANAO_DEL_SUR, en_str_Lanao_del_Sur, {2,2,4,2}},
    {OSD_CITY_MAGUINDANAO, en_str_Maguindanao, {2,2,4,3}},
    {OSD_CITY_SULU, en_str_Sulu, {2,2,4,4}},
    {OSD_CITY_TAWI_TAWI, en_str_Tawi_Tawi, {2,2,4,5}},
};  

BOOLEAN MApp_ZUI_ACT_ExecuteEWBSConfirmDialogAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_EWBS_CONFIRM:
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_EWBS_CONFIRM, SW_HIDE);

            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_CHANNEL);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_PAGE, SW_SHOW);
            MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_CHANNEL_PAGE_LIST, HWND_MENU_EWBS_INFO);

            eEwbsAreaType = OSD_AREA_TYPE_WIDE_AREA_ZONE;

            _eEwbsWideAreaZone = E_EWBS_DEFAULT;
            _eEwbsRegion = E_EWBS_DEFAULT;
            _eEwbsCity = E_EWBS_DEFAULT;

            return TRUE;

        default:
            ZUI_DBG_FAIL(printf("[ZUI]CLOCKACT\n"));
            ABORT();
    }

    return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_ACT_GetEWBSConfirmDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    switch(hwnd)
    {
        case HWND_MENU_DLG_EWBS_CONFIRM_AREA_OPTION:
        {
            switch(eEwbsAreaType)	//treat eEwbsAreaType as a flag
            {
                case OSD_AREA_TYPE_WIDE_AREA_ZONE:
                    u16TempID = en_str_Wide_Area_Zone;
                        break;
                case OSD_AREA_TYPE_REGION:
                    u16TempID = en_str_Region;
                        break;
                case OSD_AREA_TYPE_CITY:
                    u16TempID = en_str_City;
                        break;
                default :
                    u16TempID = en_str_Wide_Area_Zone;
                        break;
             }
        }
        break;
    }
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return 0; //for empty string....
}

EN_OSD_EWBS_AREA_SETTING MApp_ZUI_ACT_GetEWBSArea(void)
{
    return _eEwbsArea;
}

void MApp_ZUI_ACT_SetEWBSArea(EN_OSD_EWBS_AREA_SETTING EwbsArea)
{
    _eEwbsArea = EwbsArea;
}

void MApp_ZUI_ACT_SetEWBSAreaIndex(U8 u8Index)
{
    if(MApp_GetOSDCountrySetting() == E_PHILIPPINES)
    {
        switch(eEwbsAreaType)
        {
            case OSD_AREA_TYPE_WIDE_AREA_ZONE:
            {
                if (stPhilippinesWideAreaList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_WIDE_AREA_NUM)
                {
                    MS_DEBUG_MSG(printf("Set Wide Area Zone Overflow: %u\n", (U16)stPhilippinesWideAreaList[u8Index].u16SelectionItem));
                    _eEwbsWideAreaZone = E_EWBS_LUZON;
                }
                else
                {
                    _eEwbsWideAreaZone =(EN_OSD_EWBS_AREA_SETTING)stPhilippinesWideAreaList[u8Index].u16SelectionItem;
                }
                _eEwbsArea = _eEwbsWideAreaZone;
                break;
            }
            case OSD_AREA_TYPE_REGION:
            {
                if(_eEwbsWideAreaZone == E_EWBS_LUZON)
                {
                    if (stLuzonRegionList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_LUZON_REGION_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set Region Overflow: %u\n", (U16)stLuzonRegionList[u8Index].u16SelectionItem));
                        _eEwbsRegion = E_EWBS_NATIONAL_CAPITAL_REGION;
                    }
                    else
                    {
                        _eEwbsRegion = (EN_OSD_EWBS_AREA_SETTING)stLuzonRegionList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsWideAreaZone == E_EWBS_VISAYAS)
                {
                    if (stLuzonRegionList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_VISAYAS_REGION_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set Region Overflow: %u\n", (U16)stVisayasRegionList[u8Index].u16SelectionItem));
                        _eEwbsRegion = E_EWBS_WESTERN_VISAYAS;
                    }
                    else
                    {
                        _eEwbsRegion = (EN_OSD_EWBS_AREA_SETTING)stVisayasRegionList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsWideAreaZone == E_EWBS_MINDANAO)
                {
                    if (stLuzonRegionList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_MINDANAO_REGION_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set Region Overflow: %u\n", (U16)stMindanaoRegionList[u8Index].u16SelectionItem));
                        _eEwbsRegion = E_EWBS_ZAMBOANGA_PENINSULA;
                    }
                    else
                    {
                        _eEwbsRegion = (EN_OSD_EWBS_AREA_SETTING)stMindanaoRegionList[u8Index].u16SelectionItem;
                    }
                }
                _eEwbsArea = _eEwbsRegion;
                break;
            }
            case OSD_AREA_TYPE_CITY:
            {
                if(_eEwbsRegion == E_EWBS_NATIONAL_CAPITAL_REGION)
                {
                    if (stNCRCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_NCR_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stNCRCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_CALOOCAN;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stNCRCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_CORDILLERA_ADMINISTRATIVE_REGION)
                {
                    if (stCARCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_CAR_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stCARCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_ABRA;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stCARCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_ILOCOS_REGION)
                {
                    if (stIlocosRegionCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_ILOCOS_REGION_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stIlocosRegionCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_ILOCOS_NORTE;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stIlocosRegionCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_CAGAYAN_VALLEY)
                {
                    if (stCagayanValleyCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_CAGAYAN_VALLEY_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stCagayanValleyCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_BATANES;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stCagayanValleyCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_CENTRAL_LUZON)
                {
                    if (stCentralLuzonCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_CENTRAL_LUZON_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stCentralLuzonCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_BATANES;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stCentralLuzonCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_CALABARZON)
                {
                    if (stCalabarzonCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_CALABARZON_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stCalabarzonCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_BATANGAS;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stCalabarzonCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_MIMAROPA)
                {
                    if (stMimaropaCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_MIMAROPA_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stMimaropaCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_MARINDUQUE;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stMimaropaCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_BICOL_REGION)
                {
                    if (stBicolRegionCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_BICOL_REGION_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stBicolRegionCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_ALBAY;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stBicolRegionCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_WESTERN_VISAYAS)
                {
                    if (stWesternVisayasCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_WESTERN_VISAYAS_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stWesternVisayasCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_AKLAN;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stWesternVisayasCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_CENTRAL_VISAYAS)
                {
                    if (stCentralVisayasCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_CENTRAL_VISAYAS_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stCentralVisayasCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_BOHOL;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stCentralVisayasCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_EASTERN_VISAYAS)
                {
                    if (stEasternVisayasCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_EASTERN_VISAYAS_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stEasternVisayasCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_BILIRAN;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stEasternVisayasCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_ZAMBOANGA_PENINSULA)
                {
                    if (stZamboangaPeninsulaCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_ZAMBOANGA_PENINSULA_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stZamboangaPeninsulaCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_ISABELA_CITY;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stZamboangaPeninsulaCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_NORTHERN_MINDANAO)
                {
                    if (stNorthernMindanaoCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_NORTHERN_MINDANAO_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stNorthernMindanaoCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_BUKIDNON;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stNorthernMindanaoCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_DAVAO_REGION)
                {
                    if (stDavaoRegionCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_DAVAO_REGION_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stDavaoRegionCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_COMPOSTELA_VALLEY;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stDavaoRegionCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_SOCCSKSARGEN)
                {
                    if (stSoccsksargenCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_SOCCSKSARGEN_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stSoccsksargenCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_COTABATO;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stSoccsksargenCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_CARAGA)
                {
                    if (stCaragaCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_CARAGA_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stCaragaCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_AGUSAN_DEL_NORTE;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stCaragaCityList[u8Index].u16SelectionItem;
                    }
                }
                else if(_eEwbsRegion == E_EWBS_AUTONOMOUS_REGION_IN_MUSLIM_MINDANAO)
                {
                    if (stARMMCityList[u8Index].u16SelectionItem >= OSD_PHILIPPINES_ARMM_CITY_NUM)
                    {
                        MS_DEBUG_MSG(printf("Set City Overflow: %u\n", (U16)stARMMCityList[u8Index].u16SelectionItem));
                        _eEwbsCity = E_EWBS_BASILAN;
                    }
                    else
                    {
                        _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)stARMMCityList[u8Index].u16SelectionItem;
                    }
                }

                _eEwbsArea = _eEwbsCity;
                break;
            }
            default:
                break;
        }
    }

    MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLG_EWBS_CONFIRM);
}

void MApp_ZUI_ACT_SetEWBSDefaultAreaIndex(void)
{
    HWND hwndFocus = MApp_ZUI_API_GetFocus();
    U8 u8Index;
    if ((hwndFocus < HWND_MENU_DLG_EWBS_CONFIRM_COUNTRY_GRID_01)||(hwndFocus > HWND_MENU_DLG_EWBS_CONFIRM_COUNTRY_GRID_09))
        return;

    u8Index = (hwndFocus - HWND_MENU_DLG_EWBS_CONFIRM_COUNTRY_GRID_01)/3;

    if((eEwbsAreaType == OSD_AREA_TYPE_WIDE_AREA_ZONE)&&(_eEwbsWideAreaZone == E_EWBS_DEFAULT))
    {
        _eEwbsWideAreaZone = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_LUZON + u8Index);
    }
    else if((eEwbsAreaType == OSD_AREA_TYPE_REGION)&&(_eEwbsRegion == E_EWBS_DEFAULT))
    {
        switch(_eEwbsWideAreaZone)
        {
            case E_EWBS_LUZON:
            {
                _eEwbsRegion = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_NATIONAL_CAPITAL_REGION + u8Index);
            }
            break;
            case E_EWBS_VISAYAS:
            {
                _eEwbsRegion = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_WESTERN_VISAYAS + u8Index);
            }
            break;
            case E_EWBS_MINDANAO:
            {
                _eEwbsRegion = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_ZAMBOANGA_PENINSULA + u8Index);
            }
            break;
            default:
                break;
        }
    }
    else if((eEwbsAreaType == OSD_AREA_TYPE_CITY)&&(_eEwbsCity == E_EWBS_DEFAULT))
    {
        switch(_eEwbsRegion)
        {
            case E_EWBS_NATIONAL_CAPITAL_REGION:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_CALOOCAN + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stNCRCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stNCRCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stNCRCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stNCRCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_CORDILLERA_ADMINISTRATIVE_REGION:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_ABRA + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCARCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCARCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCARCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCARCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_ILOCOS_REGION:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_ILOCOS_NORTE + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stIlocosRegionCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stIlocosRegionCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stIlocosRegionCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stIlocosRegionCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_CAGAYAN_VALLEY:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_BATANES + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCagayanValleyCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCagayanValleyCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCagayanValleyCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCagayanValleyCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_CENTRAL_LUZON:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_ANGELES + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCentralLuzonCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCentralLuzonCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCentralLuzonCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCentralLuzonCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_CALABARZON:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_BATANGAS + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCalabarzonCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCalabarzonCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCalabarzonCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCalabarzonCityList[u8Index].u8LocationCode[3];
            }
            case E_EWBS_MIMAROPA:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_MARINDUQUE + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stMimaropaCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stMimaropaCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stMimaropaCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stMimaropaCityList[u8Index].u8LocationCode[3];
            }
            case E_EWBS_BICOL_REGION:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_ALBAY + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stBicolRegionCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stBicolRegionCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stBicolRegionCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stBicolRegionCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_WESTERN_VISAYAS:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_AKLAN + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stWesternVisayasCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stWesternVisayasCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stWesternVisayasCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stWesternVisayasCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_CENTRAL_VISAYAS:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_BOHOL + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCentralVisayasCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCentralVisayasCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCentralVisayasCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCentralVisayasCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_EASTERN_VISAYAS:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_BILIRAN + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stEasternVisayasCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stEasternVisayasCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stEasternVisayasCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stEasternVisayasCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_ZAMBOANGA_PENINSULA:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_ISABELA_CITY + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_NORTHERN_MINDANAO:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_BUKIDNON + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stNorthernMindanaoCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stNorthernMindanaoCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stNorthernMindanaoCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stNorthernMindanaoCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_DAVAO_REGION:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_COMPOSTELA_VALLEY + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stDavaoRegionCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stDavaoRegionCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stDavaoRegionCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stDavaoRegionCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_SOCCSKSARGEN:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_COTABATO + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stSoccsksargenCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stSoccsksargenCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stSoccsksargenCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stSoccsksargenCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_CARAGA:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_AGUSAN_DEL_NORTE + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCaragaCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCaragaCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCaragaCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCaragaCityList[u8Index].u8LocationCode[3];
            }
            break;
            case E_EWBS_AUTONOMOUS_REGION_IN_MUSLIM_MINDANAO:
            {
                _eEwbsCity = (EN_OSD_EWBS_AREA_SETTING)(E_EWBS_BASILAN + u8Index);

                stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stARMMCityList[u8Index].u8LocationCode[0];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stARMMCityList[u8Index].u8LocationCode[1];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stARMMCityList[u8Index].u8LocationCode[2];
                stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stARMMCityList[u8Index].u8LocationCode[3];
            }
            break;
            default:
                break;
        }
    }
}

U8 MApp_ZUI_ACT_GetEWBSAreaIndexMax(void)
{
    U8 u8MaxIndex = 0;
    if(MApp_GetOSDCountrySetting() == E_PHILIPPINES)
    {
        if(eEwbsAreaType == OSD_AREA_TYPE_WIDE_AREA_ZONE)
        {
            u8MaxIndex = (U8)(sizeof(stPhilippinesWideAreaList)/sizeof(stPhilippinesWideAreaList[0])) - 1;
        }
        else if(eEwbsAreaType == OSD_AREA_TYPE_REGION)
        {
            if(_eEwbsWideAreaZone == OSD_WIDE_AREA_LUZON)
            {
                u8MaxIndex = (U8)(sizeof(stLuzonRegionList)/sizeof(stLuzonRegionList[0])) - 1;
            }
            else if(_eEwbsWideAreaZone == OSD_WIDE_AREA_VISAYAS)
            {
                u8MaxIndex = (U8)(sizeof(stVisayasRegionList)/sizeof(stVisayasRegionList[0])) - 1;
            }
            else if(_eEwbsWideAreaZone == OSD_WIDE_AREA_MINDANAO)
            {
                u8MaxIndex = (U8)(sizeof(stMindanaoRegionList)/sizeof(stMindanaoRegionList[0])) - 1;
            }
        }
        else if(eEwbsAreaType == OSD_AREA_TYPE_CITY)
        {
            if(_eEwbsRegion == OSD_REGION_NCR)
            {
                u8MaxIndex = (U8)(sizeof(stNCRCityList)/sizeof(stNCRCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_CAR)
            {
                u8MaxIndex = (U8)(sizeof(stCARCityList)/sizeof(stCARCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_ILOCOS_REGION)
            {
                u8MaxIndex = (U8)(sizeof(stIlocosRegionCityList)/sizeof(stIlocosRegionCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_CAGAYAN_VALLEY)
            {
                u8MaxIndex = (U8)(sizeof(stCagayanValleyCityList)/sizeof(stCagayanValleyCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_CENTRAL_LUZON)
            {
                u8MaxIndex = (U8)(sizeof(stCentralLuzonCityList)/sizeof(stCentralLuzonCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_CALABARZON)
            {
                u8MaxIndex = (U8)(sizeof(stCalabarzonCityList)/sizeof(stCalabarzonCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_MIMAROPA)
            {
                u8MaxIndex = (U8)(sizeof(stMimaropaCityList)/sizeof(stMimaropaCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_BICOL_REGION)
            {
                u8MaxIndex = (U8)(sizeof(stBicolRegionCityList)/sizeof(stBicolRegionCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_WESTERN_VISAYAS)
            {
                u8MaxIndex = (U8)(sizeof(stWesternVisayasCityList)/sizeof(stWesternVisayasCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_CENTRAL_VISAYAS)
            {
                u8MaxIndex = (U8)(sizeof(stCentralVisayasCityList)/sizeof(stCentralVisayasCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_EASTERN_VISAYAS)
            {
                u8MaxIndex = (U8)(sizeof(stEasternVisayasCityList)/sizeof(stEasternVisayasCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_ZAMBOANGA_PENINSULA)
            {
                u8MaxIndex = (U8)(sizeof(stZamboangaPeninsulaCityList)/sizeof(stZamboangaPeninsulaCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_NORTHERN_MINDANAO)
            {
                u8MaxIndex = (U8)(sizeof(stNorthernMindanaoCityList)/sizeof(stNorthernMindanaoCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_DAVAO_REGION)
            {
                u8MaxIndex = (U8)(sizeof(stDavaoRegionCityList)/sizeof(stDavaoRegionCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_SOCCSKSARGEN)
            {
                u8MaxIndex = (U8)(sizeof(stSoccsksargenCityList)/sizeof(stSoccsksargenCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_CARAGA)
            {
                u8MaxIndex = (U8)(sizeof(stCaragaCityList)/sizeof(stCaragaCityList[0])) - 1;
            }
            else if(_eEwbsRegion == OSD_REGION_AUTONOMOUS_REGION_IN_MUSLIM_MINDANAO)
            {
                u8MaxIndex = (U8)(sizeof(stARMMCityList)/sizeof(stARMMCityList[0])) - 1;
            }
        }
    }

    return u8MaxIndex;
}

U8 MApp_ZUI_ACT_GetEWBSAreaIndex(void)
{
    U8 u8Index = 0;
    if(MApp_GetOSDCountrySetting() == E_PHILIPPINES)
    {
        if(eEwbsAreaType == OSD_AREA_TYPE_WIDE_AREA_ZONE)
        {
            for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
            {
                if (_eEwbsWideAreaZone == (EN_OSD_EWBS_AREA_SETTING)stPhilippinesWideAreaList[u8Index].u16SelectionItem)
                {
                    return u8Index;
                }
            }
        }
        if(eEwbsAreaType == OSD_AREA_TYPE_REGION)
        {
            if(_eEwbsWideAreaZone == E_EWBS_LUZON)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsRegion == (EN_OSD_EWBS_AREA_SETTING)stLuzonRegionList[u8Index].u16SelectionItem)
                    {
                        return u8Index;
                    }
                }
            }
            if(_eEwbsWideAreaZone == E_EWBS_VISAYAS)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsRegion == (EN_OSD_EWBS_AREA_SETTING)stVisayasRegionList[u8Index].u16SelectionItem)
                    {
                        return u8Index;
                    }
                }
            }
            if(_eEwbsWideAreaZone == E_EWBS_MINDANAO)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsRegion == (EN_OSD_EWBS_AREA_SETTING)stMindanaoRegionList[u8Index].u16SelectionItem)
                    {
                        return u8Index;
                    }
                }
            }
        }
        if(eEwbsAreaType == OSD_AREA_TYPE_CITY)
        {
            if(_eEwbsRegion == E_EWBS_NATIONAL_CAPITAL_REGION)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stNCRCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stNCRCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stNCRCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stNCRCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stNCRCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_CORDILLERA_ADMINISTRATIVE_REGION)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stCARCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCARCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCARCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCARCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCARCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_ILOCOS_REGION)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stIlocosRegionCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stIlocosRegionCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stIlocosRegionCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stIlocosRegionCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stIlocosRegionCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_CAGAYAN_VALLEY)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stCagayanValleyCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCagayanValleyCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCagayanValleyCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCagayanValleyCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCagayanValleyCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_CENTRAL_LUZON)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stCentralLuzonCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCentralLuzonCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCentralLuzonCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCentralLuzonCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCentralLuzonCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_CALABARZON)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stCalabarzonCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCalabarzonCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCalabarzonCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCalabarzonCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCalabarzonCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_MIMAROPA)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stMimaropaCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stMimaropaCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stMimaropaCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stMimaropaCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stMimaropaCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_BICOL_REGION)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stBicolRegionCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stBicolRegionCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stBicolRegionCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stBicolRegionCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stBicolRegionCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_WESTERN_VISAYAS)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stWesternVisayasCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stWesternVisayasCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stWesternVisayasCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stWesternVisayasCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stWesternVisayasCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_CENTRAL_VISAYAS)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stCentralVisayasCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCentralVisayasCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCentralVisayasCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCentralVisayasCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCentralVisayasCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_EASTERN_VISAYAS)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stEasternVisayasCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stEasternVisayasCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stEasternVisayasCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stEasternVisayasCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stEasternVisayasCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_ZAMBOANGA_PENINSULA)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stZamboangaPeninsulaCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stZamboangaPeninsulaCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_NORTHERN_MINDANAO)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stNorthernMindanaoCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stNorthernMindanaoCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stNorthernMindanaoCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stNorthernMindanaoCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stNorthernMindanaoCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_DAVAO_REGION)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stDavaoRegionCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stDavaoRegionCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stDavaoRegionCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stDavaoRegionCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stDavaoRegionCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_SOCCSKSARGEN)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stSoccsksargenCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stSoccsksargenCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stSoccsksargenCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stSoccsksargenCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stSoccsksargenCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_CARAGA)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stCaragaCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stCaragaCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stCaragaCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stCaragaCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stCaragaCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
            if(_eEwbsRegion == E_EWBS_AUTONOMOUS_REGION_IN_MUSLIM_MINDANAO)
            {
                for (u8Index = 0; u8Index <= MApp_ZUI_ACT_GetEWBSAreaIndexMax(); u8Index++)
                {
                    if (_eEwbsCity == (EN_OSD_EWBS_AREA_SETTING)stARMMCityList[u8Index].u16SelectionItem)
                    {
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[0] = stARMMCityList[u8Index].u8LocationCode[0];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[1] = stARMMCityList[u8Index].u8LocationCode[1];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[2] = stARMMCityList[u8Index].u8LocationCode[2];
                        stGenSetting.stMiscSetting.u8EWBSLocationCode[3] = stARMMCityList[u8Index].u8LocationCode[3];

                        return u8Index;
                    }
                }
            }
        }
    }

    return 0;
}

LPTSTR MApp_ZUI_ACT_GetEWBSAreaStringByIndex(U8 u8Index)
{
    U16 u16TempID = Empty;
    if (u8Index > MApp_ZUI_ACT_GetEWBSAreaIndexMax())
    {
        return 0;   //exceed country list count
    }
    else
    {
        if(MApp_GetOSDCountrySetting() == E_PHILIPPINES)
        {
            switch(eEwbsAreaType)
            {
                case OSD_AREA_TYPE_WIDE_AREA_ZONE:
                {
                    u16TempID = stPhilippinesWideAreaList[u8Index].u16StringIndex;
                    break;
                }
                case OSD_AREA_TYPE_REGION:
                {
                    if(_eEwbsWideAreaZone == E_EWBS_LUZON)
                    {
                        u16TempID = stLuzonRegionList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsWideAreaZone == E_EWBS_VISAYAS)
                    {
                        u16TempID = stVisayasRegionList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsWideAreaZone == E_EWBS_MINDANAO)
                    {
                        u16TempID = stMindanaoRegionList[u8Index].u16StringIndex;
                    }
                    break;
                }
                case OSD_AREA_TYPE_CITY:
                {
                    if(_eEwbsRegion == E_EWBS_NATIONAL_CAPITAL_REGION)
                    {
                        u16TempID = stNCRCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_CORDILLERA_ADMINISTRATIVE_REGION)
                    {
                        u16TempID = stCARCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_ILOCOS_REGION)
                    {
                        u16TempID = stIlocosRegionCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_CAGAYAN_VALLEY)
                    {
                        u16TempID = stCagayanValleyCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_CENTRAL_LUZON)
                    {
                        u16TempID = stCentralLuzonCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_CALABARZON)
                    {
                        u16TempID = stCalabarzonCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_MIMAROPA)
                    {
                        u16TempID = stMimaropaCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_BICOL_REGION)
                    {
                        u16TempID = stBicolRegionCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_WESTERN_VISAYAS)
                    {
                        u16TempID = stWesternVisayasCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_CENTRAL_VISAYAS)
                    {
                        u16TempID = stCentralVisayasCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_EASTERN_VISAYAS)
                    {
                        u16TempID = stEasternVisayasCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_ZAMBOANGA_PENINSULA)
                    {
                        u16TempID = stZamboangaPeninsulaCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_NORTHERN_MINDANAO)
                    {
                        u16TempID = stNorthernMindanaoCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_DAVAO_REGION)
                    {
                        u16TempID = stDavaoRegionCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_SOCCSKSARGEN)
                    {
                        u16TempID = stSoccsksargenCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_CARAGA)
                    {
                        u16TempID = stCaragaCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_AUTONOMOUS_REGION_IN_MUSLIM_MINDANAO)
                    {
                        u16TempID = stARMMCityList[u8Index].u16StringIndex;
                    }
                    if(_eEwbsRegion == E_EWBS_AUTONOMOUS_REGION_IN_MUSLIM_MINDANAO)
                    {
                        u16TempID = stARMMCityList[u8Index].u16StringIndex;
                    }
                    break;
                }
                default:
                    break;
            }
        }

    }
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return 0; //for empty string....
}
#endif

#undef MAPP_ZUI_ACTEWBSCONFIRMFUNC_C


