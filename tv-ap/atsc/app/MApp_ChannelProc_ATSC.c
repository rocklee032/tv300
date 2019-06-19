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

#define MAPP_CHANNELPROC_ATSC_C
////////////////////////////////////////////////////////////////////////////////
/// @file MApp_ChannelProc.c
/// @author MStar Semiconductor Inc.
/// @brief Channel number check and read from SDRM for APP layer
////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdio.h>

#include "Board.h"

#if(ENABLE_ATSC)

//#include "datatype.h"
#include "msAPI_Ram.h"
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"

//#include "msAPI_Tuner_ATSC.h"
#include "RF_Tuner_ATSC.h"


#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_DataBase_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_ScanMenu_ATSC.h"
#include "MApp_Psip.h"
#include "MApp_EpgDB_ATSC.h"
#include "MApp_SaveData.h"
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
#include "MApp_Scan_ATSC.h"
#endif

#define INVALID_MINOR_NUMBER            0x8000
#define MAX_NUM_OF_IDLE_CHAN_PER_PAGE   1   //MAX_VC_PER_PHYSICAL
#define MAX_NUM_OF_FAV_CHAN_PER_PAGE    1

//==============================================================================
/*                    Macro                                                     */
//==============================================================================
#define CUTOFF 8

//#define ENABLE_CHANPROC_DEBUG     0

#define CHANPROC_DBINFO(y) y

#define CHANRTN_DBINFO(y)   //y

#define DEBUG_CH_INC(x)     //x
#define DEBUG_CH_DEC(x)     //x

#define DEBUG_CREATE_MAIN_LIST(x)   //x

#define DEBUG_PROG_IDX(x)   //x

//==============================================================================
/*                      Local                                                   */
//==============================================================================
static EN_LIST_TYPE enCurProgListType;

static U16 u16PreProgIndexOfMainList;

//static U16 u16CurProgIndex;  // Seperate to 2 variable: g_u16CurProgIndexOfMainList, g_u16CurProgIndexOfFavList
static U16 g_u16CurProgIndexOfMainList;
static U16 g_u16CurProgIndexOfFavList;


static U16 iu16Buffer_i;
static U16 iu16Buffer_j;
static U16 iu16Buffer_k;
static U16 iu16Buffer_l;


static MS_VIRTUAL_CHANNEL g_ATSC_stVirCh_Tmp;

//==============================================================================
/*                      Functions                                               */
//==============================================================================

BOOLEAN MApp_ChanProc_Is_MainListProgIdxValid(U16 u16ProgIdx)
{
    if( u16ProgIdx == INVALID_SERVICE_IDX )
    {
        return FALSE;
    }

    if( u16ProgIdx == 0 )
    {
        return FALSE;
    }

    if( u16ProgIdx > stChSetting.u16MainListSrvNum )
    {
        return FALSE;
    }

    return TRUE;
}

void MApp_ChanProc_GetSingleChannel(MS_VIRTUAL_CHANNEL *pVirCh, U16 u16Index)
{
    //CHANPROC_DBINFO( printf("MApp_ChanProc_GetSingleChannel(u16Index=%u)\n", u16Index); );

    MApp_DB_ATSC_LoadVirChannel(u16Index, pVirCh);
}
//==============================================================================
void MApp_ChanProc_SetSingleChannel(MS_VIRTUAL_CHANNEL *pVirCh, U16 u16Index)
{
    CHANPROC_DBINFO( printf("MApp_ChanProc_SetSingleChannel(u16Index=%u)\n", u16Index); );

    MApp_DB_ATSC_SaveVirChannel(u16Index, pVirCh);
}
//==============================================================================
MS_VIRTUAL_CHANNEL* MApp_ChanProc_GetChannelPointer(U16 u16Index)
{
    /*
     * CAUTION
     * g_stVirtualCh should always represents current virtual channel.
     * If someone invokes MApp_ChanProc_GetChannelPointer(index)
     * where index is not current program index, g_stVirtualCh will be polluted.
     */

    MApp_ChanProc_GetSingleChannel( (&g_ATSC_stVirCh_Tmp) , u16Index);

#if 0
    printf ("\ni = %u >> PN = %u, SrcId = %u\n", u16Index, g_ATSC_stVirCh_Tmp.u16ProgramNumber, g_ATSC_stVirCh_Tmp.u16SourceId);
#endif

    return &g_ATSC_stVirCh_Tmp;
}
//==============================================================================
MS_VIRTUAL_CHANNEL* MApp_ChanProc_GetCurChannelPointer(void)
{
#if 0
    printf ("\ni = %u >> PN = %u, SrcId = %u\n", u16Index, g_ATSC_stCurVirCh.u16ProgramNumber, g_ATSC_stCurVirCh.u16SourceId);
#endif

    /*
     * CAUTION
     * g_stVirtualCh should always represents current virtual channel.
     * If someone invokes MApp_ChanProc_GetChannelPointer(index)
     * where index is not current program index, g_stVirtualCh will be polluted.
     */
    //return &g_stVirtualCh;
    return &g_ATSC_stCurVirCh;
}

U8 MApp_ChanProc_Get_Ch_AudLangNum(MS_VIRTUAL_CHANNEL* pstVirCh)
{
    if( pstVirCh == NULL )
        return 0;


    if( pstVirCh->u8AudLangNum < MAX_AUD_LANG_NUM_ATSC )
    {
        return pstVirCh->u8AudLangNum;
    }
    else
    {
        return MAX_AUD_LANG_NUM_ATSC;
    }
}

U8 MApp_ChanProc_Get_CurCh_AudLangNum(void)
{
    //return MApp_ChanProc_Get_Ch_AudLangNum(&g_stVirtualCh);
    return MApp_ChanProc_Get_Ch_AudLangNum(&g_ATSC_stCurVirCh);
}

void MApp_ChanProc_GetRfChannelPointer2(MS_VIRTUAL_CHANNEL* pstVirtualCh_func,MS_RF_CHANNEL_new* prfchannel)
{
  #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    if (MApp_ChanProc_IsCurProgIndexAir())
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
    }
    else
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
    }
    MApp_DB_ATSC_LoadRfChannel(pstVirtualCh_func->u8RfNum, prfchannel);
    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
  #else
    MApp_DB_ATSC_LoadRfChannel(pstVirtualCh_func->u8RfNum, prfchannel);
  #endif
}

/*******************************************************************************/
MS_VIRTUAL_CHANNEL* MApp_ChanProc_GetTempChannelPointer(U16 u16Index)
{
    MApp_ChanProc_GetSingleChannel( (&g_ATSC_stVirCh_Tmp) , u16Index);
    return &g_ATSC_stVirCh_Tmp;
}

//==============================================================================
void MApp_ChanProc_GetSingleVirtualChannel(MS_VIRTUAL_CHANNEL *pstVirtualCh_func, U16 u16Index)
{
    MApp_ChanProc_GetSingleChannel(pstVirtualCh_func, u16Index);
}

void MApp_ChanProc_Get_VirCh_By_MainListIdx(MS_VIRTUAL_CHANNEL *pstVirtualCh_func, U16 u16MainListIdx)
{
    MApp_ChanProc_GetSingleChannel( pstVirtualCh_func, VIR_CH_IDX(u16MainListIdx));
}

//==============================================================================

EN_DEMOD_ATSC_MODE MApp_ChanProc_Get_ChannelModulation(MS_VIRTUAL_CHANNEL* pstVirCh)
{
    MS_RF_CHANNEL_new stRfChTmp;
    MApp_ChanProc_GetRfChannelPointer(pstVirCh, &stRfChTmp);
    return (EN_DEMOD_ATSC_MODE)stRfChTmp.stTPSetting.fModulation;
}

void MApp_ChanProc_Get_TPSetting(MS_VIRTUAL_CHANNEL* pstVirCh, MS_TP_SETTING_ATSC* pTpSetting_ATSC)
{
    MS_RF_CHANNEL_new stRfChTmp;
    MApp_ChanProc_GetRfChannelPointer(pstVirCh, &stRfChTmp);
    memcpy(pTpSetting_ATSC, &(stRfChTmp.stTPSetting), sizeof(MS_TP_SETTING_ATSC) );
}

BOOL MApp_ChanProc_Is_ChannelAtv(MS_VIRTUAL_CHANNEL* pstVirCh)
{
    if( MApp_ChanProc_Get_ChannelModulation(pstVirCh) == DEMOD_ATSC_MODE_NTSC )
        return TRUE;

    return FALSE;
}

BOOL MApp_ChanProc_Is_CurChannelAtv(void)
{
    if(MApp_ChanProc_GetCurMainListProgIndex() == INVALID_SERVICE_IDX)
        return TRUE; // default ATV

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    if (MApp_ChanProc_IsCurProgIndexAir())
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
        pstVirtualCh = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(MApp_ChanProc_GetCurProgIndex()));
    }
    else
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
        pstVirtualCh = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()));
    }
    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
#else
    pstVirtualCh = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurMainListProgIndex()));
#endif

    return MApp_ChanProc_Is_ChannelAtv(pstVirtualCh);
}

//==============================================================================
BOOLEAN MApp_ChanProc_IsInSamePhysicalChannel(U16 u16ProgIdx_1, U16 u16ProgIdx_2)
{
    if(stChSetting.astMainList[u16ProgIdx_1].u8PhysicalChIdx == stChSetting.astMainList[u16ProgIdx_2].u8PhysicalChIdx)
        return TRUE;
    else
        return FALSE;
}
//==============================================================================
/* u16CurIndex: Actual program number start from 1 */
/*
BOOLEAN MApp_ChanProc_IsInSamePage(U16 u16CurIndex, U8 u8ChanNumPerPage)
{
    if(u16CurIndex >= u16CurChanlMoveBaseIndx && u16CurIndex < (u16CurChanlMoveBaseIndx + u8ChanNumPerPage))
        return TRUE;
    else
        return FALSE;
}
*/
//==============================================================================
/* u16CurIndex: Actual program number start from 1 */
U16 MApp_ChanProc_CalculateCurPageBaseIdx(U16 u16CurIndex, U8 u8ChanNumPerPage)
{
    /* u16CurIndex: start from 1 */
    if (u16CurIndex == INVALID_SERVICE_IDX)
        return INVALID_SERVICE_IDX;
    else
    {
        if((u16CurIndex % u8ChanNumPerPage) == 0)
            u16CurIndex--;

        return (u16CurIndex - (u16CurIndex % u8ChanNumPerPage) + 1);
    }
}

U16 MApp_ChanProc_GetNextFavoriteOrdinal(U16 u16Star)
{
    for(iu16Loop_i = u16Star+2; iu16Loop_i <= stChSetting.u16MainListSrvNum; iu16Loop_i++)
    {
        if( IS_FAV_CH_ATSC(iu16Loop_i) )
        {
            return iu16Loop_i-1;
        }
    }
    return INVALID_SERVICE_IDX-1;
}

//==============================================================================
U16 MApp_ChanProc_GetFirstFavoriteOrdinal(void)
{
    for(iu16Loop_i = 1; iu16Loop_i <= stChSetting.u16MainListSrvNum; iu16Loop_i++)
    {
        if( IS_FAV_CH_ATSC(iu16Loop_i) )
        {
            return iu16Loop_i-1;
        }
    }
    return INVALID_SERVICE_IDX-1;
}

//==============================================================================
void MApp_ChanProc_GetTotalFavFromMainList(void)
{
    // Clear Fav list
    memset(stChSetting.au16FavList, 0, sizeof(stChSetting.au16FavList));
    stChSetting.u16FavListSrvNum = 0;


    U16 u16MainListIdx;

    U16 u16FavListIdx = 1; // Why 1!? should change to 0
    g_u16CurProgIndexOfFavList = u16FavListIdx;

    U16 u16CurMainListProgIndex = MApp_ChanProc_GetCurMainListProgIndex();

    for(u16MainListIdx = 1; u16MainListIdx <= stChSetting.u16MainListSrvNum; ++ u16MainListIdx )
    {
        if( IS_FAV_CH_ATSC(u16MainListIdx) )
        {
            stChSetting.au16FavList[u16FavListIdx] = u16MainListIdx;

            if( u16MainListIdx == u16CurMainListProgIndex )
            {
                g_u16CurProgIndexOfFavList = u16FavListIdx;
            }

            u16FavListIdx ++;
            stChSetting.u16FavListSrvNum ++;
        }
    }

}

//==============================================================================
void MApp_ChanProc_GetTotalDispFromMainList(void)
{
#if 0
    memset(stChSetting.au16FavList, 0, sizeof(stChSetting.au16FavList));

    //TV
    stChSetting.u16DispListSrvNum = 0;

    U16 u16MainListIdx;
    U16 u16FavListIdx = 1;

    for(u16MainListIdx = 1; u16MainListIdx <= stChSetting.u16MainListSrvNum; u16MainListIdx++)
    {
        /*If the program of no signal is added to channel list, it should add all program into au16FavList.*/
        //if( !IS_DIR_CH(iu16Loop_i) )
        {
            stChSetting.au16FavList[u16FavListIdx] = u16MainListIdx;
            u16FavListIdx ++;

            stChSetting.u16DispListSrvNum++;
        }
    }
#endif
}
//==============================================================================
U16 MApp_ChanProc_GetNumOfServices(EN_LIST_TYPE enListType)
{
    switch(enListType)
    {
    #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
        case DISP_LIST:
        case MAIN_LIST:
            return stChSettingDisp[ANT_AIR].u16MainListSrvNum + stChSettingDisp[ANT_CATV].u16MainListSrvNum;
        case FAV_LIST:
            return stChSettingDisp[ANT_AIR].u16FavListSrvNum + stChSettingDisp[ANT_CATV].u16FavListSrvNum;
        //case DISP_LIST:
            //return stChSettingDisp[ANT_AIR].u16DispListSrvNum + stChSettingDisp[ANT_CATV].u16DispListSrvNum;
    #else

        case DISP_LIST:
//            return stChSetting.u16DispListSrvNum;
        case MAIN_LIST:
            return stChSetting.u16MainListSrvNum;

        case FAV_LIST:
            return stChSetting.u16FavListSrvNum;
    #endif

        default:
            return 0;
    }
}

//==============================================================================
U16 MApp_ChanProc_CalculateTotalSrvNum(MS_PHYSICAL_CHANNEL *pstPhysicalChTemp, EN_ANT_TYPE enAntennaType)
{
    U8 u8PhyChIdx_Min;
    U8 u8PhyChIdx_Max;

    if(enAntennaType == ANT_AIR)
    {
        u8PhyChIdx_Min = CHAN_AIR_MIN;
        u8PhyChIdx_Max = CHAN_AIR_MAX;
    }
    else //ANT_CATV
    {
        u8PhyChIdx_Min = CHAN_CATV_MIN;
        u8PhyChIdx_Max = CHAN_CATV_MAX;
    }


    U16 u16TotalSrvNum = 0;

    U8 u8PhyChIdx;

    for(u8PhyChIdx = u8PhyChIdx_Min; u8PhyChIdx <= u8PhyChIdx_Max; u8PhyChIdx++)
    {
        u16TotalSrvNum += pstPhysicalChTemp[u8PhyChIdx].u8NumOfVirCh;
    }

    //stChSetting.u16DispListSrvNum = 0;
    stChSetting.u16TotalHideSrvNum = 0;

    U16 u16VirChInfoIdx;
    for(u16VirChInfoIdx=1; u16VirChInfoIdx <= u16TotalSrvNum; u16VirChInfoIdx++)
    {
        //if( stChSetting.astVirtualChInfo[iu16Buffer_j].fIsDirCh == 0 )
        //    stChSetting.u16DispListSrvNum++;

        if( stChSetting.astVirtualChInfo[u16VirChInfoIdx].fIsHideCh )
            stChSetting.u16TotalHideSrvNum++;
    }

    return u16TotalSrvNum; //total service num
}

#ifdef MAINLISTSRV_ANALOGCH_NUM
U16 MApp_ChanProc_CalculateAnalogSrvNum(MS_PHYSICAL_CHANNEL *pstPhysicalChTemp, EN_ANT_TYPE enAntennaType)
{
    MS_VIRTUAL_CHANNEL *pstVch = NULL;
    MS_RF_CHANNEL_new RfCh;

    if(enAntennaType == ANT_AIR)
    {
        iu8Buffer_i = CHAN_AIR_MIN;
        iu8Buffer_j = CHAN_AIR_MAX;
    }
    else //ANT_CATV
    {
        iu8Buffer_i = CHAN_CATV_MIN;
        iu8Buffer_j = CHAN_CATV_MAX;
    }

    iu16Buffer_i = 0;
    pstVch = (MS_VIRTUAL_CHANNEL *) msAPI_Memory_Allocate(sizeof(MS_VIRTUAL_CHANNEL),NULL);

    for(iu8Loop_i=iu8Buffer_i; iu8Loop_i<=iu8Buffer_j; iu8Loop_i++)
    {
        if(pstPhysicalChTemp[iu8Loop_i].u8NumOfVirCh == 1)
        {
            if(pstVch != NULL)
            {
                MApp_ChanProc_GetSingleChannel(pstVch, stChSetting.astVirtualChInfo[pstPhysicalChTemp[iu8Loop_i].u16VirChInfoStartIdx].u16VirChIdx);

                MApp_ChanProc_GetRfChannelPointer(pstVch, &RfCh);
                if ( RfCh.stTPSetting.fModulation == DEMOD_ATSC_MODE_NTSC )
                {
                    iu16Buffer_i++;
                }
            }
            else
            {
                ASSERT(0);
            }
        }
    }

    if(pstVch != NULL)
        MSAPI_MEMORY_FREE(pstVch,NULL);
    return iu16Buffer_i; //total service num
}
#endif
//==============================================================================
void MApp_ChanProc_RefreshVirChInfoStartIdx(void)
{
    U16 u16Loop;    // S.G.HAN 061214
    U8 u8MaxPchChNum;

    u8MaxPchChNum = (ANT_TYPE == ANT_AIR) ? MAX_AIR_PHYSICAL_CH_NUM : MAX_CATV_PHYSICAL_CH_NUM;
    stChSetting.astPhysicalCh[0].u16VirChInfoStartIdx = 1;
    for(u16Loop=1; u16Loop<u8MaxPchChNum; u16Loop++)    // S.G.HAN 061214
    {
        stChSetting.astPhysicalCh[u16Loop].u16VirChInfoStartIdx = stChSetting.astPhysicalCh[u16Loop-1].u16VirChInfoStartIdx + stChSetting.astPhysicalCh[u16Loop-1].u8NumOfVirCh;    // S.G.HAN 061214
    }
}
/*******************************************************************************************************************/
/* qsort function */
static void swap(unsigned char *a, unsigned char *b, U16 u16Width)
{
    char tmp;

    if(a != b)
    {
        while(u16Width--)
        {
            tmp = *a;
            *a++ = *b;
            *b++ = tmp;
        }
    }
}
static void shortsort(unsigned char *pLow, unsigned char *pHeight, U16 u16Width, EN_SORT_METHOD stMethod)
{
    unsigned char *p, *pMax;

    while(pHeight > pLow)
    {
        pMax = pLow;
        for (p = pLow + u16Width; p <= pHeight; p += u16Width)
        {
            switch(stMethod)
            {
                case METHOD_MAIN_LIST:
                    if(MApp_ChanProc_SortMainList(p, pMax) > 0)
                    {
                        pMax = p;
                    }
                    break;
                case METHOD_PHY_CH:
                    if(MApp_ChanProc_SortPhysicalChannel(p, pMax) > 0)
                    {
                        pMax = p;
                    }
                    break;
            }
        }

        swap(pMax, pHeight, u16Width);
        pHeight -= u16Width;
    }
}

void MApp_ChanProc_QSort(void *pBase, U16 u16Num, U16 u16Width, EN_SORT_METHOD stMethod)
{
    U8 xdata *pLow = NULL, *pHeight = NULL, *pMiddle = NULL;
    U8 xdata *pLowPart = NULL, *pHeightPart = NULL;
    U16 u16Size;
    U8 xdata *pLowStack[MAX(MAX_NUM_OF_CATV_VIR_CH,MAX_NUM_OF_AIR_VIR_CH)];
    U8 xdata *pHightStack[MAX(MAX_NUM_OF_CATV_VIR_CH,MAX_NUM_OF_AIR_VIR_CH)];
    S16 s16stkPtr;


    //printf("MApp_ChanProc_QSort(u16Num=%u)\n", u16Num);

/*
    printf("&pLow=0x%X\n", &pLow);
    printf("&pMiddle=0x%X\n", &pMiddle);
    printf("&pLowStack=0x%X ~ 0x%X\n", &pLowStack, (U32)(&pLowStack)+ sizeof(pLowStack) );
    printf("&pHightStack=0x%X ~ 0x%X\n", &pHightStack, (U32)(&pHightStack)+ sizeof(pHightStack) );
    printf("&s16stkPtr=0x%X\n", &s16stkPtr);
*/

    if(u16Num < 2 || u16Width == 0)
    {
        return;
    }

    s16stkPtr = 0;

    pLow = pBase;
    pHeight = (U8 *)pBase + u16Width * (u16Num - 1);

RECURSE :
    u16Size = (pHeight - pLow) / u16Width + 1;

    if (u16Size <= CUTOFF)
    {
        shortsort(pLow, pHeight, u16Width, stMethod);
    }
    else
    {
        pMiddle = pLow + (u16Size / 2) * u16Width;

        swap(pMiddle, pLow, u16Width);

        pLowPart = pLow;
        pHeightPart = pHeight + u16Width;

        for (; ;)
        {
            switch (stMethod)
            {
                case METHOD_MAIN_LIST:
                    do
                    {
                        pLowPart += u16Width;
                    }
                    while(pLowPart <= pHeight && MApp_ChanProc_SortMainList(pLowPart, pLow) <= 0);

                    do
                    {
                        pHeightPart -= u16Width;
                    }
                    while(pHeightPart > pLow && MApp_ChanProc_SortMainList(pHeightPart, pLow) >= 0);

                    break;

                case METHOD_PHY_CH:
                    do
                    {
                        pLowPart += u16Width;
                    }
                    while(pLowPart <= pHeight && MApp_ChanProc_SortPhysicalChannel(pLowPart, pLow) <= 0);

                    do
                    {
                        pHeightPart -= u16Width;
                    }
                    while(pHeightPart > pLow && MApp_ChanProc_SortPhysicalChannel(pHeightPart, pLow) >= 0);

                    break;
            }

            if (pHeightPart < pLowPart)
            {
                break;
            }

            swap(pLowPart, pHeightPart, u16Width);
        }

        swap(pLow, pHeightPart, u16Width);

        if (pHeightPart - (pLow + 1) >= pHeight - pLowPart)
        {
            if (pLow + u16Width < pHeightPart)
            {
                pLowStack[s16stkPtr] = pLow;
                pHightStack[s16stkPtr] = pHeightPart - u16Width;
                s16stkPtr++;
            }

            if (pLowPart < pHeight)
            {
                pLow = pLowPart;
                goto RECURSE;
            }
        }
        else
        {
            if (pLowPart < pHeight)
            {
                pLowStack[s16stkPtr] = pLowPart;
                pHightStack[s16stkPtr] = pHeight;
                s16stkPtr++;
            }

            if (pLow + u16Width < pHeightPart)
            {
                pHeight = pHeightPart - u16Width;
                goto RECURSE;
            }
        }
    }

    s16stkPtr--;
    if (s16stkPtr >= 0)
    {
        pLow = pLowStack[s16stkPtr];
        pHeight = pHightStack[s16stkPtr];
        goto RECURSE;
    }
    else
    {
        return;
    }
}

//==============================================================================
/* compare function : return 1 => swap, else => no operation */
S8 MApp_ChanProc_SortPhysicalChannel(void xdata *pElem1, void xdata *pElem2)
{
    MS_VIRTUAL_CHANNEL stVirCh_1;
    MS_VIRTUAL_CHANNEL stVirCh_2;

    memset(&stVirCh_1, 0, sizeof(MS_VIRTUAL_CHANNEL));
    MApp_ChanProc_GetSingleChannel( &stVirCh_1, ((MS_VIRTUAL_CHANNEL_INFO *)pElem1)->u16VirChIdx);

    memset(&stVirCh_2, 0, sizeof(MS_VIRTUAL_CHANNEL));
    MApp_ChanProc_GetSingleChannel( &stVirCh_2, ((MS_VIRTUAL_CHANNEL_INFO *)pElem2)->u16VirChIdx);

    if(stVirCh_1.stVirtualChNum.major_num > stVirCh_2.stVirtualChNum.major_num) //compare major number
    {
        return 1;
    }
    else if( stVirCh_1.stVirtualChNum.major_num == stVirCh_2.stVirtualChNum.major_num) //compare minor number again
    {
        if(stVirCh_1.stVirtualChNum.minor_num > stVirCh_2.stVirtualChNum.minor_num)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

//==============================================================================
/* compare function : return 1 => swap, else => no operation */
S8 MApp_ChanProc_SortMainList(void xdata *pElem1, void xdata *pElem2)
{
#if ENABLE_ATSC_CHLIST_DTV_IN_FRONT_AND_ATV_IN_BACK
    MS_TP_SETTING_ATSC stTPSettingTemp0, stTPSettingTemp1;
#endif

    /*iu8Buffer_i*/ U8 u8Ch1_PhyChIdx = ((MS_MAINLIST_A *)pElem1)->u8PhysicalChIdx;
    /*iu8Buffer_j*/ U8 u8Ch1_VirChInfoIdx = ((MS_MAINLIST_A *)pElem1)->u8VirChInfoIdx;
    /*iu8Buffer_k*/ U8 u8Ch2_PhyChIdx = ((MS_MAINLIST_A *)pElem2)->u8PhysicalChIdx;
    /*iu8Buffer_l*/ U8 u8Ch2_VirChInfoIdx = ((MS_MAINLIST_A *)pElem2)->u8VirChInfoIdx;

//    MApp_ChanProc_GetSingleVirtualChannel(l_pastVirtualCh  , stChSetting.astVirtualChInfo[stChSetting.astPhysicalCh[iu8Buffer_i].u16VirChInfoStartIdx + iu8Buffer_j].u16VirChIdx);
  //  MApp_ChanProc_GetSingleVirtualChannel(l_pastVirtualCh+1, stChSetting.astVirtualChInfo[stChSetting.astPhysicalCh[iu8Buffer_k].u16VirChInfoStartIdx + iu8Buffer_l].u16VirChIdx);

    MS_VIRTUAL_CHANNEL stVirCh_1;
    MS_VIRTUAL_CHANNEL stVirCh_2;

    memset(&stVirCh_1, 0, sizeof(MS_VIRTUAL_CHANNEL));
    MApp_ChanProc_GetSingleChannel( &stVirCh_1, stChSetting.astVirtualChInfo[stChSetting.astPhysicalCh[u8Ch1_PhyChIdx].u16VirChInfoStartIdx + u8Ch1_VirChInfoIdx].u16VirChIdx);

    memset(&stVirCh_2, 0, sizeof(MS_VIRTUAL_CHANNEL));
    MApp_ChanProc_GetSingleChannel( &stVirCh_2, stChSetting.astVirtualChInfo[stChSetting.astPhysicalCh[u8Ch2_PhyChIdx].u16VirChInfoStartIdx + u8Ch2_VirChInfoIdx].u16VirChIdx);


    iu16Buffer_i = stVirCh_1.stVirtualChNum.major_num;
    iu16Buffer_j = stVirCh_1.stVirtualChNum.minor_num;
    iu16Buffer_k = stVirCh_2.stVirtualChNum.major_num;
    iu16Buffer_l = stVirCh_2.stVirtualChNum.minor_num;

#if ENABLE_ATSC_CHLIST_DTV_IN_FRONT_AND_ATV_IN_BACK

    //MApp_ChanProc_Get_TPSetting(&l_pastVirtualCh[0], &stTPSettingTemp0);
    MApp_ChanProc_Get_TPSetting(&stVirCh_1, &stTPSettingTemp0);

    //MApp_ChanProc_Get_TPSetting(&l_pastVirtualCh[1], &stTPSettingTemp1);
    MApp_ChanProc_Get_TPSetting(&stVirCh_2, &stTPSettingTemp1);

    if (stTPSettingTemp0.fModulation == 0 && stTPSettingTemp1.fModulation != 0)//0:NTSC 1:256QAM 2:64QAM 3:8VSB
    {
        return 1;
    }
    else if (stTPSettingTemp0.fModulation != 0 && stTPSettingTemp1.fModulation == 0)//0:NTSC 1:256QAM 2:64QAM 3:8VSB
    {
        return -1;
    }
    else
    {
        ;
    }
#endif

    if(iu16Buffer_i > iu16Buffer_k) //compare major number
    {
        return 1;
    }
    else if(iu16Buffer_i == iu16Buffer_k) //compare minor number again
    {
        if(iu16Buffer_j > iu16Buffer_l)
        {
            return 1;
        }
        else if(iu16Buffer_j == iu16Buffer_l) //compare physical channel number again
        {
            if(u8Ch1_PhyChIdx > u8Ch2_PhyChIdx)
                return 1;
            else if(u8Ch1_PhyChIdx == u8Ch2_PhyChIdx)
                return 0;
            else  //u8Ch1_PhyChIdx < u8Ch2_PhyChIdx
                return -1;
        }
        else //iu16Buffer_j < iu16Buffer_l
        {
            return -1;
        }
    }
    else //iu16Buffer_i < iu16Buffer_k
    {
        return -1;
    }
}
//==============================================================================
void MApp_ChanProc_CreateMainList(MS_PHYSICAL_CHANNEL *pstPhysicalChTemp, MS_MAINLIST_A *pstMainListTemp, EN_ANT_TYPE enAntennaType)
{
    U8 u8RfChMin, u8RfChMax, u8NumOfVirCh;
    U16 u16MaxSrvNum, u16SrcCount;


    DEBUG_CREATE_MAIN_LIST( PRINT_CURRENT_LINE(); );
    DEBUG_CREATE_MAIN_LIST( printf("MApp_ChanProc_CreateMainList(enAntennaType=%u)\n", enAntennaType); );

    if(enAntennaType == ANT_AIR)
    {
        u8RfChMin = CHAN_AIR_MIN;
        u8RfChMax = CHAN_AIR_MAX;
    }
    else //ANT_CATV
    {
        u8RfChMin = CHAN_CATV_MIN;
        u8RfChMax = CHAN_CATV_MAX;
    }
    u16MaxSrvNum = stChSetting.u16MainListSrvNum;

    u16SrcCount = 0; //service count

    U8 u8RfChIdx;
    U8 u8VirChInfoIdx;

    for(u8RfChIdx=u8RfChMin; (u8RfChIdx<=u8RfChMax)&&(u16SrcCount<u16MaxSrvNum); ++ u8RfChIdx)
    {
        u8NumOfVirCh = pstPhysicalChTemp[u8RfChIdx].u8NumOfVirCh;

      #if 0//(ENABLE_CHANPROC_DEBUG == 1)
        l_pastVirtualCh = (MS_VIRTUAL_CHANNEL *)au8Section;

        for(u8Loop_j=0; u8Loop_j<u8NumOfVirCh; u8Loop_j++)
        {
            MApp_ChanProc_GetSingleVirtualChannel(l_pastVirtualCh, stChSetting.astVirtualChInfo[pstPhysicalChTemp[u8Loop_i].u16VirChInfoStartIdx + u8Loop_j].u16VirChIdx);
            printf("1: u8Loop_i %d u8Loop_j %d u16VirChInfoStartIdx %d\n", u8Loop_i, u8Loop_j, (U16)pstPhysicalChTemp[u8Loop_i].u16VirChInfoStartIdx);
            printf("1: physical %d u8NumOfVirCh %bu u16VirChIdx %u >> %d-%d\n", u8Loop_i, u8NumOfVirCh, stChSetting.astVirtualChInfo[pstPhysicalChTemp[u8Loop_i].u16VirChInfoStartIdx + u8Loop_j].u16VirChIdx,
                l_pastVirtualCh[0].stVirtualChNum.major_num, l_pastVirtualCh[0].stVirtualChNum.minor_num);
        }
      #endif

        if( u8NumOfVirCh > 1 )
        {
            DEBUG_CREATE_MAIN_LIST( printf("u8RfChIdx=%u, u8NumOfVirCh=%u\n", u8RfChIdx, u8NumOfVirCh); );

            /* sort major number and minor number of physical channel */
            MApp_ChanProc_QSort(&stChSetting.astVirtualChInfo[pstPhysicalChTemp[u8RfChIdx].u16VirChInfoStartIdx], u8NumOfVirCh, sizeof(MS_VIRTUAL_CHANNEL_INFO), METHOD_PHY_CH);
        }

        for(u8VirChInfoIdx = 0; u8VirChInfoIdx < u8NumOfVirCh; ++ u8VirChInfoIdx )
        {
            pstMainListTemp[u16SrcCount].u8PhysicalChIdx = u8RfChIdx;
            pstMainListTemp[u16SrcCount].u8VirChInfoIdx = u8VirChInfoIdx;
            u16SrcCount++;

          #if 0//(ENABLE_CHANPROC_DEBUG == 1)
            MApp_ChanProc_GetSingleVirtualChannel(l_pastVirtualCh, stChSetting.astVirtualChInfo[pstPhysicalChTemp[u8Loop_i].u16VirChInfoStartIdx + u8Loop_j].u16VirChIdx);

            printf("2: physical %d u8NumOfVirCh %d u16VirChIdx %u >> %d-%d\n", u8Loop_i, u8NumOfVirCh, stChSetting.astVirtualChInfo[pstPhysicalChTemp[u8Loop_i].u16VirChInfoStartIdx + u8Loop_j].u16VirChIdx,
                l_pastVirtualCh[0].stVirtualChNum.major_num, l_pastVirtualCh[0].stVirtualChNum.minor_num);
          #endif
        }

    }

    /* sort major number and minor number of main list */
    if(u16MaxSrvNum > 1)
    {
        MApp_ChanProc_QSort(pstMainListTemp, u16MaxSrvNum, sizeof(MS_MAINLIST_A), METHOD_MAIN_LIST);
    }

    //stChSetting.u16TotalHideSrvNum = 0;
    stChSetting.u16FavListSrvNum = 0;

  #if 0//(ENABLE_CHANPROC_DEBUG == 1)
    printf("u16SrcCount = %d\n", u16SrcCount);
    for(u16MaxSrvNum=0; u16MaxSrvNum<u16SrcCount; u16MaxSrvNum++)
        printf("3: u8PhysicalChIdx %d u8VirChInfoIdx %d u16VirChIdx %d\n", pstMainListTemp[u16MaxSrvNum].u8PhysicalChIdx, pstMainListTemp[u16MaxSrvNum].u8VirChInfoIdx, (U16)VIR_CH_IDX(u16MaxSrvNum+1));
  #endif

    enCurProgListType = MAIN_LIST;

    DEBUG_CREATE_MAIN_LIST( MApp_CM_PrintAllCh(); );
}
//==============================================================================
U16 MApp_ChanProc_GetProgIdxByVirChNum(MS_VIRTUAL_CHANNEL_NUM *pstVirtualChNum)
{
    U16 u16ProgIndex;
    MS_VIRTUAL_CHANNEL *l_pastVirtualCh;
    l_pastVirtualCh = (MS_VIRTUAL_CHANNEL *)g_u32Section;
    u16ProgIndex = INVALID_SERVICE_IDX;

#if (ONE_PART_CHNO==ENABLE)
    U16 u16DtvProgIndexTemp = INVALID_SERVICE_IDX;
    U16 u16AtvProgIndexTemp = INVALID_SERVICE_IDX;
#else
    pstVirtualChNum->minor_num=0;
#endif

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    U16 u16MaxProgIndex;
    if(ANT_TYPE == ANT_AIR)
    {
        iu16Loop_i = 1;
        u16MaxProgIndex = stChSettingDisp[ANT_AIR].u16MainListSrvNum;
    }
    else
    {
        iu16Loop_i = stChSettingDisp[ANT_AIR].u16MainListSrvNum + 1;
        u16MaxProgIndex = stChSettingDisp[ANT_AIR].u16MainListSrvNum + stChSettingDisp[ANT_CATV].u16MainListSrvNum;
    }
    for(; iu16Loop_i <= u16MaxProgIndex; iu16Loop_i++)
#else
    for(iu16Loop_i = 1; iu16Loop_i <= stChSetting.u16MainListSrvNum; iu16Loop_i++)
#endif
    {
    #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
        if (iu16Loop_i <= stChSettingDisp[ANT_AIR].u16MainListSrvNum)
        {
            MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
            MApp_ChanProc_GetSingleVirtualChannel(l_pastVirtualCh, VIR_CH_IDX_AIR(iu16Loop_i));
        }
        else
        {
            MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
            MApp_ChanProc_GetSingleVirtualChannel(l_pastVirtualCh, VIR_CH_IDX_CATV(iu16Loop_i - stChSettingDisp[ANT_AIR].u16MainListSrvNum));
        }
        MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
    #else
        MApp_ChanProc_GetSingleVirtualChannel(l_pastVirtualCh, VIR_CH_IDX(iu16Loop_i));
    #endif
        CHANPROC_DBINFO(printf("--- [%u]:  SrvNum=%u >>>  CurVir[%u-%u], DbVir [%u-%u], OnePart=%u, PhyIdx=%d\n", iu16Loop_i, stChSetting.u16MainListSrvNum,
                    pstVirtualChNum->major_num, pstVirtualChNum->minor_num,
                    l_pastVirtualCh->stVirtualChNum.major_num,  l_pastVirtualCh->stVirtualChNum.minor_num,
                    (U8)l_pastVirtualCh->stVirtualChNum.fIsOnePartChNum, PHY_CH_IDX(iu16Loop_i)));

        //Load program index: one-part -> two-part -> RF number
#if (ONE_PART_CHNO==ENABLE)
        if(pstVirtualChNum->minor_num == INVALID_MINOR_NUMBER)
        {
            //one-part
            if((l_pastVirtualCh->stVirtualChNum.fIsOnePartChNum)
                && (l_pastVirtualCh->stVirtualChNum.major_num == pstVirtualChNum->major_num))
            {
                u16ProgIndex = iu16Loop_i;
                CHANPROC_DBINFO(printf("find One-Part CH[%u]\n", u16ProgIndex));
                break;
            }
            else
            {
            #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
                if (iu16Loop_i <= stChSettingDisp[ANT_AIR].u16MainListSrvNum)
                {
                    if(PHY_CH_IDX_AIR(iu16Loop_i) == pstVirtualChNum->major_num)
                    {
                        if(u16DtvProgIndexTemp == INVALID_SERVICE_IDX)
                        {
                            if((l_pastVirtualCh->stVirtualChNum.minor_num) && (MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_DTV || MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_DTV))
                            {
                                u16DtvProgIndexTemp = iu16Loop_i;
                                CHANPROC_DBINFO(printf("find DTV[%u]\n", u16DtvProgIndexTemp));
                            }
                            else if((!(l_pastVirtualCh->stVirtualChNum.minor_num)) && (MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_ATV || MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_ATV))
                            {
                                u16AtvProgIndexTemp = iu16Loop_i;
                                CHANPROC_DBINFO(printf("find ATV[%u]\n", u16AtvProgIndexTemp));
                            }
                        }
                    }
                }
                else
                {
                    if((PHY_CH_IDX_CATV(iu16Loop_i - stChSettingDisp[ANT_AIR].u16MainListSrvNum)) == pstVirtualChNum->major_num)
                    {
                        if(u16DtvProgIndexTemp == INVALID_SERVICE_IDX)
                        {
                            if((l_pastVirtualCh->stVirtualChNum.minor_num) && (MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_DTV || MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_DTV))
                            {
                                u16DtvProgIndexTemp = iu16Loop_i;
                                CHANPROC_DBINFO(printf("find DTV[%u]\n", u16DtvProgIndexTemp));
                            }
                            else if((!(l_pastVirtualCh->stVirtualChNum.minor_num)) && (MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_ATV || MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_ATV))
                            {
                                u16AtvProgIndexTemp = iu16Loop_i;
                                CHANPROC_DBINFO(printf("find ATV[%u]\n", u16AtvProgIndexTemp));
                            }
                        }
                    }
                }
            #else
                if(PHY_CH_IDX(iu16Loop_i) == pstVirtualChNum->major_num)
                {
                    if(u16DtvProgIndexTemp == INVALID_SERVICE_IDX)
                    {
                        if(l_pastVirtualCh->stVirtualChNum.minor_num)
                        {
                            u16DtvProgIndexTemp = iu16Loop_i;
                            CHANPROC_DBINFO(printf("find DTV[%u]\n", u16DtvProgIndexTemp));
                        }
                        else
                        {
                            u16AtvProgIndexTemp = iu16Loop_i;
                            CHANPROC_DBINFO(printf("find ATV[%u]\n", u16AtvProgIndexTemp));
                        }
                    }
                }
            #endif
            }
        }
        else
 #endif
        {
            if((l_pastVirtualCh->stVirtualChNum.major_num == pstVirtualChNum->major_num)
                && (l_pastVirtualCh->stVirtualChNum.minor_num == pstVirtualChNum->minor_num)
                && (l_pastVirtualCh->stVirtualChNum.minor_num > 0))
            {
                //two-part
                u16ProgIndex = iu16Loop_i;
                CHANPROC_DBINFO(printf("find DTV[%u]\n", u16ProgIndex));
                break;
            }
        #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
            else if (iu16Loop_i <= stChSettingDisp[ANT_AIR].u16MainListSrvNum)
            {
                if((PHY_CH_IDX_AIR(iu16Loop_i) == pstVirtualChNum->major_num)
                    && (pstVirtualChNum->minor_num == 0))
                {
                    u16ProgIndex = iu16Loop_i;
                    CHANPROC_DBINFO(printf("find ATV[%u]\n", u16ProgIndex));
                    break;
                }
            }
            else
            {
                if(((PHY_CH_IDX_CATV(iu16Loop_i - stChSettingDisp[ANT_AIR].u16MainListSrvNum)) == pstVirtualChNum->major_num)
                    && (pstVirtualChNum->minor_num == 0))
                {
                    u16ProgIndex = iu16Loop_i;
                    CHANPROC_DBINFO(printf("find ATV[%u]\n", u16ProgIndex));
                    break;
                }
            }
        #else
            else if((PHY_CH_IDX(iu16Loop_i) == pstVirtualChNum->major_num) && (pstVirtualChNum->minor_num == 0))
            {
                //RF number
                u16ProgIndex = iu16Loop_i;
                CHANPROC_DBINFO(printf("find ATV[%u]\n", u16ProgIndex));
                break;
            }
        #endif
        }
    }

#if (ONE_PART_CHNO==ENABLE)
    if(u16ProgIndex ==  INVALID_SERVICE_IDX)
    {
        if(u16DtvProgIndexTemp)
        {
            u16ProgIndex = u16DtvProgIndexTemp;
        }
        else if (u16AtvProgIndexTemp)
        {
            u16ProgIndex = u16AtvProgIndexTemp;
        }
    }
    CHANPROC_DBINFO(printf("find TV[%u] %d, %d\n", u16ProgIndex, u16DtvProgIndexTemp, u16AtvProgIndexTemp));
#endif

    return u16ProgIndex;
}

//==============================================================================
U16 MApp_ChanProc_GetProgIdxByVirChIdx(U8 u8PhysicalChIdx, U8 u8VirChInfoIdx)
{
    U16 u16MainListIdx;

    for(u16MainListIdx = 1; u16MainListIdx <= stChSetting.u16MainListSrvNum; ++u16MainListIdx )
    {
        if(stChSetting.astMainList[u16MainListIdx].u8PhysicalChIdx == u8PhysicalChIdx &&
           stChSetting.astMainList[u16MainListIdx].u8VirChInfoIdx == u8VirChInfoIdx)
           return u16MainListIdx;
    }

    return INVALID_SERVICE_IDX;
}
//==============================================================================
/*
static U16 MApp_ChanProc_MapProgIndex2MainList(U16 u16Index, EN_LIST_TYPE enListType)
{
    return (enListType==FAV_LIST||enListType==DISP_LIST) ? stChSetting.au16FavList[u16Index] : u16Index;
}
*/
//==============================================================================
void MApp_ChanProc_SaveLastWatched(void)
{
#if 1
  #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    stGenSetting.g_SysSetting.u16MainListLastWatched = g_u16CurProgIndexOfMainList;// MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex,enCurProgListType);
  #else
    stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = g_u16CurProgIndexOfMainList;//MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex,enCurProgListType);
  #endif

#else
  #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    stGenSetting.g_SysSetting.u16MainListLastWatched = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex,enCurProgListType);
  #else
    stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex,enCurProgListType);
  #endif
#endif
}
//==============================================================================
EN_LIST_TYPE MApp_ChanProc_GetCurProgListType(void)
{
    return enCurProgListType;
}
//==============================================================================
U16 MApp_ChanProc_GetCurProgIndex(void)
{
#if 1
    return MApp_ChanProc_GetCurMainListProgIndex();
#else
    return u16CurProgIndex;
#endif
}

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
BOOLEAN MApp_ChanProc_IsCurProgIndexAir(void)
{
    if(MApp_ChanProc_GetCurProgIndex() <= stChSettingDisp[ANT_AIR].u16MainListSrvNum)
        return TRUE;
    else
        return FALSE;
}

U16 MApp_ChanProc_GetCurCableProgIndex(void)
{
    return (MApp_ChanProc_GetCurProgIndex() - stChSettingDisp[ANT_AIR].u16MainListSrvNum);
}
#endif

//==============================================================================
U16 MApp_ChanProc_GetCurMainListProgIndex(void)
{
#if 1
    //printf("Get CurProgIdxOfMainList => %u\n", g_u16CurProgIndexOfMainList);
    return g_u16CurProgIndexOfMainList;
#else

    return MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex, enCurProgListType);
#endif
}
//==============================================================================
U16 MApp_ChanProc_GetPreProgIndexOfMainList(void)
{
    return u16PreProgIndexOfMainList;
}
//==============================================================================
void MApp_ChanProc_ResetAllIndex(U16 value)
{
    DEBUG_PROG_IDX( PRINT_CURRENT_LINE(); );
    DEBUG_PROG_IDX( printf("MApp_ChanProc_ResetAllIndex(%u)\n", value); );


#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    g_u16CurProgIndexOfMainList = u16PreProgIndexOfMainList = stGenSetting.g_SysSetting.u16MainListLastWatched = value;
#else
    g_u16CurProgIndexOfMainList = u16PreProgIndexOfMainList = stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = value;
#endif

}
//==============================================================================
void MApp_ChanProc_ResetProgIdxByVirChIdx(U8 u8PrePhyChIdx, U8 u8PreVirChInfoIdx, U8 u8CurPhyChIdx, U8 u8CurVirChInfoIdx)
{
    U16 u16Loop;

    DEBUG_PROG_IDX( printf("MApp_ChanProc_ResetProgIdxByVirChIdx(u8CurVirChInfoIdx=%u)\n", u8CurVirChInfoIdx); );
    DEBUG_PROG_IDX( printf("u16PreProgIndexOfMainList=%u", u16PreProgIndexOfMainList); );

    g_u16CurProgIndexOfMainList = u16PreProgIndexOfMainList = INVALID_SERVICE_IDX;

    for(u16Loop = 1; u16Loop <= stChSetting.u16MainListSrvNum; u16Loop++)
    {
        if(u16PreProgIndexOfMainList == INVALID_SERVICE_IDX &&
           stChSetting.astMainList[u16Loop].u8PhysicalChIdx == u8PrePhyChIdx &&
           stChSetting.astMainList[u16Loop].u8VirChInfoIdx == u8PreVirChInfoIdx)
        {
           u16PreProgIndexOfMainList = u16Loop;
        }

        if(g_u16CurProgIndexOfMainList == INVALID_SERVICE_IDX &&
           stChSetting.astMainList[u16Loop].u8PhysicalChIdx == u8CurPhyChIdx &&
           stChSetting.astMainList[u16Loop].u8VirChInfoIdx == u8CurVirChInfoIdx)
        {
           g_u16CurProgIndexOfMainList = u16Loop;
        }

        if( (u16PreProgIndexOfMainList!=INVALID_SERVICE_IDX) && (g_u16CurProgIndexOfMainList!=INVALID_SERVICE_IDX) )
        {
            DEBUG_PROG_IDX(printf("%u)", u16PreProgIndexOfMainList));
            return;
        }
    }

    DEBUG_PROG_IDX( printf(" -> %u\n", u16PreProgIndexOfMainList); );
}

BOOLEAN MApp_ChanProc_ResetProgIdx_ToFirstAtvDtv(BOOLEAN bIsAtv)
{
    //printf("MApp_ChanProc_ResetProgIdx_ToFirstAtvDtv(bIsAtv=%u)\n", bIsAtv);

    U16 u16ChIdx;
    MS_VIRTUAL_CHANNEL stTmpVirCh;
    BOOLEAN bFound = FALSE;

    for(u16ChIdx = 1; u16ChIdx <= stChSetting.u16MainListSrvNum; u16ChIdx ++)
    {
        // Clear stTmpVirCh
        memset(&stTmpVirCh, 0, sizeof(stTmpVirCh));
        MApp_ChanProc_GetSingleVirtualChannel(&stTmpVirCh, VIR_CH_IDX(u16ChIdx));

        EN_DEMOD_ATSC_MODE eAtscDemod = MApp_ChanProc_Get_ChannelModulation(&stTmpVirCh);

        if( eAtscDemod == DEMOD_ATSC_MODE_NTSC)
        {
            if(bIsAtv) // Find first ATV
            {
                // Found
                bFound = TRUE;
                break;
            }
        }
        else // DTV
        {
            if(!bIsAtv) // Find first DTV
            {
                // Found
                bFound = TRUE;
                break;
            }
        }
    }

    if( bFound )
    {
        printf("Change g_u16CurProgIndexOfMainList: %u -> %u\n", g_u16CurProgIndexOfMainList, u16ChIdx);
        MApp_ChanProc_SetMainListProgIndex(u16ChIdx);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//==============================================================================
BOOLEAN MApp_ChanProc_IncProgIndex(EN_LIST_TYPE enListType, U8 incItemsCount, BOOLEAN fSkipHide)
{
    DEBUG_CH_INC(printf("MApp_ChanProc_IncProgIndex(enListType=%u,incItemsCount=%u,fSkipHide=%u)\n", enListType, incItemsCount, fSkipHide); );

    if( enListType != MAIN_LIST )
    {
        return FALSE;
    }

    U16 u16ServiceNum = MApp_ChanProc_GetNumOfServices(enListType);
    U16 u16CurProgIndex_Backup = g_u16CurProgIndexOfMainList;

#if 1
    if( (u16CurProgIndex_Backup + incItemsCount) >= u16ServiceNum )
    {
        u16CurProgIndex_Backup = 1;
    }
    else
    {
        u16CurProgIndex_Backup += incItemsCount;
    }
#else
    if((u16CurProgIndex + incItemsCount) >= MApp_ChanProc_GetNumOfServices(enListType))
    {
        if(((u16CurProgIndex - 1) - ((u16CurProgIndex - 1) % incItemsCount)) == ((MApp_ChanProc_GetNumOfServices(enListType) - 1) - ((MApp_ChanProc_GetNumOfServices(enListType) - 1) % incItemsCount)))
            u16CurProgIndex = 1;
        else
            u16CurProgIndex = MApp_ChanProc_GetNumOfServices(enListType);
    }
    else
    {
        u16CurProgIndex += incItemsCount;
    }
#endif

    DEBUG_PROG_IDX( printf(" 1 g_u16CurProgIndexOfMainList=%u\n", g_u16CurProgIndexOfMainList); );
    DEBUG_PROG_IDX( printf(" 1 u16PreProgIndexOfMainList=%u\n", u16PreProgIndexOfMainList); );

    if(!fSkipHide)
    {
        //u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, enListType);
        u16PreProgIndexOfMainList = g_u16CurProgIndexOfMainList;
        g_u16CurProgIndexOfMainList = u16CurProgIndex_Backup;

        DEBUG_PROG_IDX( printf(" 2 g_u16CurProgIndexOfMainList=%u\n", g_u16CurProgIndexOfMainList); );
        DEBUG_PROG_IDX( printf(" 2 u16PreProgIndexOfMainList=%u\n", u16PreProgIndexOfMainList); );
        return TRUE;
    }


    U16 u16ChIdx;

    for(u16ChIdx=1; u16ChIdx <= u16ServiceNum; u16ChIdx++)
    {
        if( !IS_HIDE_CH_ATSC(u16CurProgIndex_Backup) )
        {
            //u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, enListType);
            u16PreProgIndexOfMainList = g_u16CurProgIndexOfMainList;
            g_u16CurProgIndexOfMainList = u16CurProgIndex_Backup;

            DEBUG_PROG_IDX( printf("3 g_u16CurProgIndexOfMainList=%u\n", g_u16CurProgIndexOfMainList); );
            DEBUG_PROG_IDX( printf("3 u16PreProgIndexOfMainList=%u\n", u16PreProgIndexOfMainList); );

            return TRUE;
        }

        if( ++u16CurProgIndex_Backup > u16ServiceNum )
            u16CurProgIndex_Backup = 1;
    }

    //u16CurProgIndex = u16CurProgIndex_Backup;

    return FALSE;
}

BOOLEAN MApp_ChanProc_IncFavProgIndex( U8 incItemsCount, BOOLEAN fSkipHide)
{
#if 1 // TO be defined
    UNUSED(incItemsCount);
    UNUSED(fSkipHide);

    return FALSE;
#else
    DEBUG_CH_INC(printf("MApp_ChanProc_IncFavProgIndex(incItemsCount=%u,fSkipHide=%u)\n", incItemsCount, fSkipHide); );

    U16 u16CurIndex = 0;
    BOOLEAN IsInList = FALSE;

    U16 u16ServiceNum = MApp_ChanProc_GetNumOfServices(FAV_LIST);

    // Check Fav service num ...
    if( u16ServiceNum <= 1 )
    {
        return FALSE;
    }

    for( u16CurIndex = 1; u16CurIndex <= u16ServiceNum; u16CurIndex++)
    {
        if(stChSetting.au16FavList[u16CurIndex] == g_u16CurProgIndexOfMainList)
        {
            IsInList = TRUE;
            break;
        }
    }

    U16 u16CurProgIndex_Backup = g_u16CurProgIndexOfMainList;//u16CurProgIndex;

    if(IsInList)
    {
        if((u16ServiceNum - u16CurIndex) < incItemsCount)
        {
            if(((u16CurIndex - 1) - ((u16CurIndex - 1) % incItemsCount)) == ((u16ServiceNum - 1) - ((u16ServiceNum - 1) % incItemsCount)))
                u16CurProgIndex = stChSetting.au16FavList[1];
            else
                u16CurProgIndex = stChSetting.au16FavList[u16ServiceNum];
            }
        else
        {
            u16CurProgIndex = stChSetting.au16FavList[u16CurIndex + incItemsCount];
        }
    }
    else
    {
        u16CurProgIndex = stChSetting.au16FavList[1]; // Why 2
    }

    if(!fSkipHide)
    {
        if(IsInList)
            u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, FAV_LIST);
        else
            u16PreProgIndexOfMainList = stChSetting.au16FavList[1];

        return TRUE;
    }

    for( u16CurIndex = 1; u16CurIndex <= u16ServiceNum; u16CurIndex++)
    {
        if(stChSetting.au16FavList[u16CurIndex] == u16CurProgIndex)
        {
            break;
        }
    }

    U16 u16ChIdx_Tmp;

    for(u16ChIdx_Tmp = 1; u16ChIdx_Tmp <= u16ServiceNum; u16ChIdx_Tmp++)
    {
        if(!IS_HIDE_CH_ATSC(u16CurProgIndex))
        {
            if(IsInList)
                u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, FAV_LIST);
            else
                u16PreProgIndexOfMainList = stChSetting.au16FavList[1];
            return TRUE;
        }

        if( ++u16CurIndex > u16ServiceNum )
            u16CurIndex = 1;

        u16CurProgIndex = stChSetting.au16FavList[u16CurIndex];
    }

    u16CurProgIndex = u16CurProgIndex_Backup;

    return FALSE;
#endif
}

BOOLEAN MApp_ChanProc_DecProgIndex(EN_LIST_TYPE enListType, U8 decItemsCount, BOOLEAN fSkipHide)
{
    DEBUG_CH_DEC( printf(" MApp_ChanProc_DecProgIndex(enListType=%u,decItemsCount=%u,fSkipHide=%u)\n", enListType, decItemsCount, fSkipHide); );

    if( enListType != MAIN_LIST )
    {
        return FALSE;
    }

    U16 u16ServiceNum = MApp_ChanProc_GetNumOfServices(enListType);
    U16 u16CurProgIndex_Backup = g_u16CurProgIndexOfMainList;

    if( u16CurProgIndex_Backup <= decItemsCount )
        u16CurProgIndex_Backup = u16ServiceNum;
    else
        u16CurProgIndex_Backup -= decItemsCount;

    DEBUG_PROG_IDX( printf(" 1 g_u16CurProgIndexOfMainList=%u\n", g_u16CurProgIndexOfMainList); );
    DEBUG_PROG_IDX( printf(" 1 u16PreProgIndexOfMainList=%u\n", u16PreProgIndexOfMainList); );

    if(!fSkipHide)
    {
        //u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, enListType);
        u16PreProgIndexOfMainList = g_u16CurProgIndexOfMainList;
        g_u16CurProgIndexOfMainList = u16CurProgIndex_Backup;

        DEBUG_PROG_IDX( printf(" 2 g_u16CurProgIndexOfMainList=%u\n", g_u16CurProgIndexOfMainList); );
        DEBUG_PROG_IDX( printf(" 2 u16PreProgIndexOfMainList=%u\n", u16PreProgIndexOfMainList); );

        return TRUE;
    }


    U16 u16ChIdx_Tmp;

    for(u16ChIdx_Tmp=1; u16ChIdx_Tmp <= u16ServiceNum; u16ChIdx_Tmp++)
    {
        if( !IS_HIDE_CH_ATSC(u16CurProgIndex_Backup) )
        {
            //u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, enListType);
            u16PreProgIndexOfMainList = g_u16CurProgIndexOfMainList;
            g_u16CurProgIndexOfMainList = u16CurProgIndex_Backup;

            DEBUG_PROG_IDX( printf(" 2 g_u16CurProgIndexOfMainList=%u\n", g_u16CurProgIndexOfMainList); );
            DEBUG_PROG_IDX( printf(" 2 u16PreProgIndexOfMainList=%u\n", u16PreProgIndexOfMainList); );

            return TRUE;
        }

        if(--u16CurProgIndex_Backup < 1)
            u16CurProgIndex_Backup = u16ServiceNum;
    }

    //u16CurProgIndex = u16CurProgIndex_Backup;

    return FALSE;
}

BOOLEAN MApp_ChanProc_DecFavProgIndex( U8 decItemsCount, BOOLEAN fSkipHide)
{
#if 1 // TO be defined
    UNUSED(decItemsCount);
    UNUSED(fSkipHide);

    return FALSE;
#else

    DEBUG_CH_DEC( printf(" MApp_ChanProc_DecProgIndex(decItemsCount=%u,fSkipHide=%u)\n", decItemsCount, fSkipHide); );

    U16 u16CurFavIndex = 0;
    BOOLEAN IsInList = FALSE;

    U16 u16ServiceNum = MApp_ChanProc_GetNumOfServices(FAV_LIST);

    // Check Fav service num ...
    if( u16ServiceNum <= 1 )
    {
        return FALSE;
    }

    for( u16CurFavIndex = 1; u16CurFavIndex <= u16ServiceNum; u16CurFavIndex++)
    {
        if(stChSetting.au16FavList[u16CurFavIndex] == g_u16CurProgIndexOfMainList)
        {
            IsInList = TRUE;
            break;
        }
    }

    U16 u16CurProgIndex_Tmp;

    if(IsInList)
    {
        if( u16CurFavIndex <= decItemsCount)
        {
            u16CurProgIndex_Tmp = stChSetting.au16FavList[u16ServiceNum];
        }
        else
        {
            u16CurProgIndex_Tmp = stChSetting.au16FavList[u16CurFavIndex - decItemsCount];
        }
    }
    else
    {
        u16CurProgIndex_Tmp = stChSetting.au16FavList[u16ServiceNum];
    }

    if(!fSkipHide)
    {
        if(IsInList)
        {
            //u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, FAV_LIST);
            u16PreProgIndexOfMainList = g_u16CurProgIndexOfMainList;
            g_u16CurProgIndexOfMainList = u16CurProgIndex_Tmp;
        }
        else
        {
            //u16PreProgIndexOfMainList = stChSetting.au16FavList[u16ServiceNum - 1];
            u16PreProgIndexOfMainList = g_u16CurProgIndexOfMainList;

            // Set to last fav ch
            g_u16CurProgIndexOfMainList = stChSetting.au16FavList[u16ServiceNum - 1];
        }

        return TRUE;
    }

    for( u16CurIndex = 1; u16CurIndex <= u16ServiceNum; u16CurIndex++)
    {
        if(stChSetting.au16FavList[u16CurIndex] == u16CurProgIndex)
        {
            break;
        }
    }

    U16 u16ChIdx_Tmp;
    for(u16ChIdx_Tmp = 1; u16ChIdx_Tmp <= u16ServiceNum; u16ChIdx_Tmp++)
    {
        if( !IS_HIDE_CH_ATSC(u16CurProgIndex) )
        {
            if(IsInList)
                u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex_Backup, FAV_LIST);
            else
                u16PreProgIndexOfMainList = stChSetting.au16FavList[u16ServiceNum - 1];

            return TRUE;
        }

        if(--u16CurIndex < 1)
            u16CurIndex = u16ServiceNum;

        u16CurProgIndex = stChSetting.au16FavList[u16CurIndex];
    }

    //u16CurProgIndex = u16CurProgIndex_Backup;

    return FALSE;
#endif
}

BOOLEAN MApp_ChanProc_RefreshChannelBuffer(EN_LIST_TYPE enListType)
{

    //if (u16CurProgIndex == INVALID_SERVICE_IDX)
    if( !MApp_ChanProc_Is_MainListProgIdxValid(g_u16CurProgIndexOfMainList) )
    {
        if( MApp_ChanProc_IncProgIndex(MAIN_LIST, 1, TRUE) == FALSE )
        {
            return FALSE;
        }
    }

    // VirCH
    switch(enListType)
    {
        case MAIN_LIST:
            //if( !MApp_ChanProc_IsInSamePage(u16CurProgIndex, MAX_NUM_OF_IDLE_CHAN_PER_PAGE) )
            {
                //u16CurChanlMoveBaseIndx = u16CurProgIndex;
                /*--> Daniel.Chai@20071228 g_stVirtualCh should always be refreshed, issue happened when
                // when No-Database, power off, NBC608B auto scan, g_stVirtualCh.u16SourceId error cause EPG event wrong, vchip unlock.
                MApp_ChanProc_GetSingleVirtualChannel(&g_stVirtualCh, VIR_CH_IDX(u16CurProgIndex));
                *///<-- Move to below line
            }

        #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
            if (MApp_ChanProc_IsCurProgIndexAir())
            {
                MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
                MApp_ChanProc_GetSingleVirtualChannel(&g_ATSC_stCurVirCh, VIR_CH_IDX_AIR(u16CurProgIndex));
             }
             else
            {
                MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
                MApp_ChanProc_GetSingleVirtualChannel(&g_ATSC_stCurVirCh, VIR_CH_IDX_CATV(MApp_ChanProc_GetCurCableProgIndex()));
            }
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
        #else

            //MApp_ChanProc_GetSingleVirtualChannel(&g_stVirtualCh, VIR_CH_IDX(u16CurProgIndex));
            MApp_ChanProc_Get_VirCh_By_MainListIdx( &g_ATSC_stCurVirCh, g_u16CurProgIndexOfMainList );

        #endif
            break;

        case FAV_LIST:
            //u16CurChanlMoveBaseIndx = u16CurProgIndex;

        #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
            if (MApp_ChanProc_IsCurProgIndexAir())
            {
                MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
                MApp_ChanProc_GetSingleVirtualChannel(&g_ATSC_stCurVirCh, VIR_CH_IDX_AIR(stChSettingDisp[ANT_AIR].au16FavList[u16CurProgIndex]));
             }
             else
            {
                MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
                MApp_ChanProc_GetSingleVirtualChannel(&g_ATSC_stCurVirCh, VIR_CH_IDX_CATV(stChSettingDisp[ANT_CATV].au16FavList[MApp_ChanProc_GetCurCableProgIndex()]));
            }
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
        #else
            //MApp_ChanProc_GetSingleVirtualChannel(&g_stVirtualCh, VIR_CH_IDX(stChSetting.au16FavList[u16CurProgIndex]));
            MApp_ChanProc_Get_VirCh_By_MainListIdx( &g_ATSC_stCurVirCh, stChSetting.au16FavList[g_u16CurProgIndexOfFavList] );

        #endif
            break;

    #if 0 // No use
        case DISP_LIST:
            //u16CurChanlMoveBaseIndx = u16CurProgIndex;

        #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
            if (MApp_ChanProc_IsCurProgIndexAir())
            {
                MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
                MApp_ChanProc_GetSingleVirtualChannel(&g_ATSC_stCurVirCh, VIR_CH_IDX_AIR(stChSettingDisp[ANT_AIR].au16FavList[u16CurProgIndex]));
             }
             else
            {
                MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
                MApp_ChanProc_GetSingleVirtualChannel(&g_ATSC_stCurVirCh, VIR_CH_IDX_CATV(stChSettingDisp[ANT_CATV].au16FavList[MApp_ChanProc_GetCurCableProgIndex()]));
            }
            MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
        #else
            MApp_ChanProc_GetSingleVirtualChannel(&g_ATSC_stCurVirCh, VIR_CH_IDX(stChSetting.au16FavList[u16CurProgIndex]));
        #endif
            break;
    #endif

        default:
            return FALSE;
    }

    if(!MApp_ChanProc_IsInSamePhysicalChannel(g_u16CurProgIndexOfMainList, u16PreProgIndexOfMainList))
    {
#if (!ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
        stGenSettingVchipRegion5.u8VersionNo = INVALID_VERSION_NUM;
#endif
    }
    //#else
    //    if( !MApp_ChanProc_IsInSamePhysicalChannel(MApp_ChanProc_MapProgIndex2MainList(u16CurProgIndex, enListType), u16PreProgIndexOfMainList) )
    //    {
    //        MApp_ChanProc_GetOnePhysicalSourceID(u16CurProgIndex);
    //    }
    //#endif

    return TRUE;
}

//*************************************************************************
BOOLEAN MApp_ChanProc_SwitchProgIndex(EN_LIST_TYPE enFromListType, EN_LIST_TYPE enToListType)
{
#if 1 // No need
    UNUSED(enFromListType);
    UNUSED(enToListType);
    return FALSE;
#else
    U16 u16NumOfservices;

    PRINT_CURRENT_LINE();
    printf("MApp_ChanProc_SwitchProgIndex(enFromListTyp=%u, enToListType=%u)\n", enFromListType, enToListType));

    if( MApp_ChanProc_GetCurProgListType() == enToListType )
    {
        return TRUE;
    }

    iu16Buffer_k = u16CurProgIndex;

//    CHANRTN_DBINFO(printf("\r\n [MApp_ChanProc_SwitchProgIndex] (%u->", u16PreProgIndexOfMainList));

    CHANPROC_DBINFO(printf("\r\n [MApp_ChanProc_SwitchProgIndex] (%u->%u)", (U16)enFromListType, enToListType));
    CHANPROC_DBINFO(printf("\r\n before : u16CurProgIndex(%u) u16PreProgIndexOfMainList(%u)", u16CurProgIndex, u16PreProgIndexOfMainList));
    switch(enFromListType)
    {
        case MAIN_LIST:
            switch(enToListType)
            {
                //case DISP_LIST:
                case FAV_LIST:
                    enCurProgListType = enToListType;
                    u16NumOfservices = MApp_ChanProc_GetNumOfServices(enToListType);
                    for(iu16Loop_j=1; iu16Loop_j <= u16NumOfservices; iu16Loop_j++)
                    {
                        if(stChSetting.au16FavList[iu16Loop_j] >= u16CurProgIndex)
                        {
                            u16CurProgIndex = iu16Loop_j;

                            if (stChSetting.au16FavList[iu16Loop_j] >= iu16Buffer_k)
                            {
                                CHANPROC_DBINFO(printf("\r\n after : u16CurProgIndex(%u) u16PreProgIndexOfMainList(%u)", u16CurProgIndex, u16PreProgIndexOfMainList));
                                CHANRTN_DBINFO(printf("%u)", u16PreProgIndexOfMainList));
                                return FALSE;
                            }
                            else
                            {
                                u16PreProgIndexOfMainList = iu16Buffer_k;
                                CHANPROC_DBINFO(printf("\r\n after : u16CurProgIndex(%u) u16PreProgIndexOfMainList(%u)", u16CurProgIndex, u16PreProgIndexOfMainList));
                                CHANRTN_DBINFO(printf("%u)", u16PreProgIndexOfMainList));
                                return TRUE;
                            }
                        }
                    }
                    CHANPROC_DBINFO(printf("\r\n [MApp_ChanProc_SwitchProgIndex] MAIN->DISP/FAV :: (%u->%u)", u16PreProgIndexOfMainList, iu16Buffer_k));
                    u16PreProgIndexOfMainList = iu16Buffer_k;
                    if(u16NumOfservices != 0)
                    {
                        u16CurProgIndex = 1;
                    }
                    else
                    {
                        u16CurProgIndex = INVALID_SERVICE_IDX;
                    }
                    CHANPROC_DBINFO(printf("\r\n after : u16CurProgIndex(%u) u16PreProgIndexOfMainList(%u)", u16CurProgIndex, u16PreProgIndexOfMainList));
                    CHANRTN_DBINFO(printf("%u)", u16PreProgIndexOfMainList));
                    return TRUE;
                default:
                    break;
            }
            break;

        case DISP_LIST:
        case FAV_LIST:
            switch(enToListType)
            {
                case MAIN_LIST:
                    enCurProgListType = MAIN_LIST;
                    u16NumOfservices = MApp_ChanProc_GetNumOfServices(enFromListType);
                    // search disp/fav list for switch index to main list if can find non-hide service.
                    for(iu16Loop_j=1; iu16Loop_j <= u16NumOfservices; iu16Loop_j++)
                    {
                        if(IS_HIDE_CH_ATSC(stChSetting.au16FavList[u16CurProgIndex] )!= TRUE)
                        {
                            u16CurProgIndex = stChSetting.au16FavList[u16CurProgIndex];
                            if(u16CurProgIndex != MApp_ChanProc_MapProgIndex2MainList(iu16Buffer_k, enFromListType))
                                u16PreProgIndexOfMainList = MApp_ChanProc_MapProgIndex2MainList(iu16Buffer_k, enFromListType);
                            CHANPROC_DBINFO(printf("\r\n after : u16CurProgIndex(%u) u16PreProgIndexOfMainList(%u)", u16CurProgIndex, u16PreProgIndexOfMainList));
                            CHANRTN_DBINFO(printf("%u)", u16PreProgIndexOfMainList));
                            return TRUE;
                        }
                        if(++u16CurProgIndex > u16NumOfservices)
                            u16CurProgIndex = 1;
                    }
                    if(u16NumOfservices == 0)
                    {
                        u16CurProgIndex = MApp_ChanProc_GetPreProgIndexOfMainList();
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    CHANPROC_DBINFO(printf("\r\n xxx after : u16CurProgIndex(%u) u16PreProgIndexOfMainList(%u)", u16CurProgIndex, u16PreProgIndexOfMainList));
    CHANRTN_DBINFO(printf("%u)", u16PreProgIndexOfMainList));

    return FALSE;
#endif
}

BOOLEAN MApp_ChanProc_SetMainListProgIndex(U16 u16ProgIndex)
{
    DEBUG_PROG_IDX(printf(" MApp_ChanProc_SetMainListProgIndex(%u)\n", u16ProgIndex); );

    if (u16ProgIndex == g_u16CurProgIndexOfMainList)
    {
        return FALSE;
    }


    DEBUG_PROG_IDX(printf(" u16PreProgIndexOfMainList: (%u->%u) \n", u16PreProgIndexOfMainList, g_u16CurProgIndexOfMainList));

    u16PreProgIndexOfMainList = g_u16CurProgIndexOfMainList;

    DEBUG_PROG_IDX(printf("g_u16CurProgIndexOfMainList: (%u->%u) \n", g_u16CurProgIndexOfMainList, u16ProgIndex));

    g_u16CurProgIndexOfMainList = u16ProgIndex;

    return TRUE;
}

BOOLEAN MApp_ChanProc_ChRtnProgIndex(void)
{
    DEBUG_PROG_IDX( printf("MApp_ChanProc_ChRtnProgIndex()"); );

    U16 u16CurMainIdx = g_u16CurProgIndexOfMainList;
    U16 u16PreMainIdx = u16PreProgIndexOfMainList;

    // Check same
    if( u16PreMainIdx == u16CurMainIdx )
        return FALSE;


    // Check pre valid ...
    if( !MApp_ChanProc_Is_MainListProgIdxValid(u16PreMainIdx) )
    {
        u16PreProgIndexOfMainList = u16CurMainIdx;
        return FALSE;
    }

    if( IS_HIDE_CH_ATSC(u16PreMainIdx) )
    {
        return FALSE;
    }

    u16PreProgIndexOfMainList = u16CurMainIdx;
    g_u16CurProgIndexOfMainList = u16PreMainIdx;

    DEBUG_PROG_IDX( printf(" Cur=%u, Pre=%u\n", g_u16CurProgIndexOfMainList, u16PreProgIndexOfMainList ); );

    return TRUE;
}

//==============================================================================
U16 MApp_GetPrevNextProgramIndex(BOOLEAN bPreProgram)
{
#if 1
    return MApp_GetPrevNextProgramIndex_ByProgIndex(bPreProgram, g_u16CurProgIndexOfMainList, FALSE);
#else
    U16 u16ChIdx_Tmp;

    iu16Buffer_k = u16CurProgIndex;

    if (bPreProgram==FALSE)
    {
        if((iu16Buffer_k + 1) > MApp_ChanProc_GetNumOfServices(MAIN_LIST))
        {
            iu16Buffer_k = 1;
        }
        else
        {
            iu16Buffer_k += 1;
        }

        //for(iu8Loop_i=1;iu8Loop_i<=MApp_ChanProc_GetNumOfServices(MAIN_LIST);iu8Loop_i++)
        for(u16ChIdx_Tmp=1; u16ChIdx_Tmp <= MApp_ChanProc_GetNumOfServices(MAIN_LIST); u16ChIdx_Tmp++)
        {
            if(!IS_HIDE_CH_ATSC(MApp_ChanProc_MapProgIndex2MainList(iu16Buffer_k,MAIN_LIST)))
            {
                return iu16Buffer_k;
            }
            if(++iu16Buffer_k > MApp_ChanProc_GetNumOfServices(MAIN_LIST))
                iu16Buffer_k = 1;
        }
    }
    else
    {
        if ( iu16Buffer_k <=1 )
        {
            iu16Buffer_k = MApp_ChanProc_GetNumOfServices(MAIN_LIST);
        }
        else
        {
            iu16Buffer_k -= 1;
        }

        //for(iu8Loop_i=1;iu8Loop_i<=MApp_ChanProc_GetNumOfServices(MAIN_LIST);iu8Loop_i++)
        for(u16ChIdx_Tmp=1; u16ChIdx_Tmp <= MApp_ChanProc_GetNumOfServices(MAIN_LIST); u16ChIdx_Tmp++)
        {
            if(!IS_HIDE_CH_ATSC(MApp_ChanProc_MapProgIndex2MainList(iu16Buffer_k,MAIN_LIST)))
            {
                return iu16Buffer_k;
            }
            if(--iu16Buffer_k < 1)
                iu16Buffer_k = MApp_ChanProc_GetNumOfServices(MAIN_LIST);
        }

    }

    return iu16Buffer_k;
#endif
}

U16 MApp_GetPrevNextProgramIndex_ByProgIndex(BOOLEAN bPreProgram, U16 u16FromProgIndex, BOOLEAN bSkipHide)
{
    U16 u16ServiceCount = MApp_ChanProc_GetNumOfServices(MAIN_LIST);

    if( u16ServiceCount <= 1 )
    {
        return 1;
    }

    U16 u16LoopIdx;
    U16 u16MainListIdx = u16FromProgIndex;

    if( bPreProgram == FALSE ) // Find next: ++
    {
        for(u16LoopIdx=1; u16LoopIdx <= u16ServiceCount; u16LoopIdx++)
        {
            // prog index += 1
            u16MainListIdx += 1;

            if( u16MainListIdx > u16ServiceCount )
            {
                u16MainListIdx = 1;
            }

            if( bSkipHide )
            {
                return u16MainListIdx;
            }

            if( !IS_HIDE_CH_ATSC(u16MainListIdx) )
            {
                return u16MainListIdx;
            }

        }

    }
    else // Find pre:  --
    {
        for(u16LoopIdx=1; u16LoopIdx <= u16ServiceCount; u16LoopIdx++)
        {
            // Prog index -= 1
            if( u16MainListIdx <= 1 ) // 0 or 1
            {
                u16MainListIdx = u16ServiceCount;
            }
            else
            {
                u16MainListIdx -= 1;
            }

            if( bSkipHide )
            {
                return u16MainListIdx;
            }

            if( !IS_HIDE_CH_ATSC(u16MainListIdx) )
            {
                return u16MainListIdx;
            }
        }

    }

    return u16MainListIdx;
}

#if (ASSIGN_NTSC_PROGRAM_AS_DEFAULT_CH == ENABLE)
void MApp_ChanProc_AssignNTSCProg2EveryRFChannel(void)
{
    U8 u8TempAntType = ANT_TYPE;
    U8 i;
    MS_CHANNEL_SETTING pstChSetting;
    MS_VIRTUAL_CHANNEL stVirChTmp;

    U16 u16Freq;

    MS_RF_CHANNEL_new stRfChTmp;


    //////////////////////////////////////////////////////////////////////////////////////////////
    // Cable
    //////////////////////////////////////////////////////////////////////////////////////////////
    ANT_TYPE = ANT_CATV;

    memset(&pstChSetting, 0, sizeof(MS_CHANNEL_SETTING));
    //pstChSetting.U32DatabaseMagicCodeEnd = DB_MAGIC_CODE;
    pstChSetting.u32MagicCode_1 = DB_ATSC_CH_SETTING_MAGCI_CODE_1;
    pstChSetting.u32MagicCode_2 = DB_ATSC_CH_SETTING_MAGCI_CODE_2;

    for(i=1; i<=(CHAN_CATV_MAX-CHAN_CATV_MIN+1); i++)
    {
        //au8VirChTbl
        pstChSetting.au8VirChTbl[i/8] |= 1 << (i%8);
    }

    for(i=0; i<MAX_CATV_PHYSICAL_CH_NUM; i++)
    {
        //astPhysicalCh
        if(i<CHAN_CATV_MIN)
        {
            pstChSetting.astPhysicalCh[i].u8NumOfVirCh = 0;
            pstChSetting.astPhysicalCh[i].u16VirChInfoStartIdx = 1;
        }
        else
        {
            pstChSetting.astPhysicalCh[i].u8NumOfVirCh = 1;
            pstChSetting.astPhysicalCh[i].u16VirChInfoStartIdx = (i-CHAN_CATV_MIN+1);
        }
        pstChSetting.astPhysicalCh[i].Reserved = 0;

        // astVirtualChInfo
        pstChSetting.astVirtualChInfo[i].u16VirChIdx = i;
        pstChSetting.astVirtualChInfo[i].fIsDirCh = 0;
        pstChSetting.astVirtualChInfo[i].fIsFavCh = 0;
        pstChSetting.astVirtualChInfo[i].fIsHideCh = 1;
        pstChSetting.astVirtualChInfo[i].Reserved= 0;

        //astMainList
        pstChSetting.astMainList[i].u8PhysicalChIdx = i;
        pstChSetting.astMainList[i].u8VirChInfoIdx = 0;
        pstChSetting.astMainList[i].Reserved =0;

    }

    pstChSetting.u16MainListSrvNum = (CHAN_CATV_MAX-CHAN_CATV_MIN+1);
    pstChSetting.u16DispListSrvNum = (CHAN_CATV_MAX-CHAN_CATV_MIN+1);
    pstChSetting.u16TotalHideSrvNum = (CHAN_CATV_MAX-CHAN_CATV_MIN+1);
    stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = 1;

    MApp_DB_ATSC_InitBaseAddr(ANT_CATV);

    //memcpy((U8*)_PA2VA(u32ChSettingStartAddr),(U8*)&pstChSetting,u16ChSettingLength);
    MApp_DB_ATSC_SaveChSetting( &pstChSetting );

    for(i=CHAN_CATV_MIN; i<(CHAN_CATV_MAX+1); i++)
    {
        memset(&stVirChTmp, 0x00, sizeof(MS_VIRTUAL_CHANNEL));

        stVirChTmp.u8RfNum = i;
        //MApp_ChanProc_GetRfChannelPointer(&stVirChTmp, &stRfChTmp);
        MApp_DB_ATSC_LoadRfChannel(stVirChTmp.u8RfNum, &stRfChTmp);

        if( MapChanToFreq(i, &u16Freq, CABLE_SYSTEM_AUTO) == TRUE )
        {
            stRfChTmp.stTPSetting.u16Frequency = u16Freq;
        }
        else
        {
            stRfChTmp.stTPSetting.u16Frequency = (U16)(55250L/FREQ_STEP);
        }
        stRfChTmp.stTPSetting.fModulation = DEMOD_ATSC_MODE_NTSC;

        stVirChTmp.stVirtualChNum.major_num = i;
        stVirChTmp.stVirtualChNum.minor_num = 0;

        MApp_ChanProc_SetSingleChannel( &stVirChTmp, i);

        MApp_DB_ATSC_SaveRfChannel(stVirChTmp.u8RfNum, &stRfChTmp);

    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Air
    //////////////////////////////////////////////////////////////////////////////////////////////
    ANT_TYPE = ANT_AIR;

    memset(&pstChSetting, 0, sizeof(MS_CHANNEL_SETTING));
    //pstChSetting.U32DatabaseMagicCodeEnd = DB_MAGIC_CODE;
    pstChSetting.u32MagicCode_1 = DB_ATSC_CH_SETTING_MAGCI_CODE_1;
    pstChSetting.u32MagicCode_2 = DB_ATSC_CH_SETTING_MAGCI_CODE_2;


    for(i=1; i<=(CHAN_AIR_MAX-CHAN_AIR_MIN+1); i++)
    {
        //au8VirChTbl
        pstChSetting.au8VirChTbl[i/8] |= 1 << (i%8);
    }

    for(i=0; i<MAX_AIR_PHYSICAL_CH_NUM; i++)
    {
        //astPhysicalCh
        if(i<CHAN_AIR_MIN)
        {
            pstChSetting.astPhysicalCh[i].u8NumOfVirCh = 0;
            pstChSetting.astPhysicalCh[i].u16VirChInfoStartIdx = 1;
        }
        else
        {
            pstChSetting.astPhysicalCh[i].u8NumOfVirCh = 1;
            pstChSetting.astPhysicalCh[i].u16VirChInfoStartIdx = (i-CHAN_AIR_MIN+1);
        }
        pstChSetting.astPhysicalCh[i].Reserved = 0;

        // astVirtualChInfo
        pstChSetting.astVirtualChInfo[i].u16VirChIdx = i;
        pstChSetting.astVirtualChInfo[i].fIsDirCh = 0;
        pstChSetting.astVirtualChInfo[i].fIsFavCh = 0;
        pstChSetting.astVirtualChInfo[i].fIsHideCh = 1;
        pstChSetting.astVirtualChInfo[i].Reserved= 0;

        //astMainList
        if(i>0)
        {
            pstChSetting.astMainList[i].u8PhysicalChIdx = i+1;
        }
        pstChSetting.astMainList[i].u8VirChInfoIdx = 0;
        pstChSetting.astMainList[i].Reserved =0;

    }

    pstChSetting.u16MainListSrvNum = (CHAN_AIR_MAX-CHAN_AIR_MIN+1);
    pstChSetting.u16DispListSrvNum = (CHAN_AIR_MAX-CHAN_AIR_MIN+1);
    pstChSetting.u16TotalHideSrvNum = (CHAN_AIR_MAX-CHAN_AIR_MIN+1);
    stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = 1;

    MApp_DB_ATSC_InitBaseAddr(ANT_AIR);

    //memcpy((U8*)_PA2VA(u32ChSettingStartAddr),(U8*)&pstChSetting,u16ChSettingLength);
    MApp_DB_ATSC_SaveChSetting( &pstChSetting );

    for(i=CHAN_AIR_MIN; i<(CHAN_AIR_MAX+1); i++)
    {
        memset(&stVirChTmp, 0x00, sizeof(MS_VIRTUAL_CHANNEL));

        stVirChTmp.u8RfNum = i;
        //MApp_ChanProc_GetRfChannelPointer(&stVirChTmp, &stRfChTmp);
        MApp_DB_ATSC_LoadRfChannel(stVirChTmp.u8RfNum, &stRfChTmp);

        if( MapChanToFreq(i, &u16Freq, CABLE_SYSTEM_AUTO) == TRUE )
        {
            stRfChTmp.stTPSetting.u16Frequency = u16Freq;
        }
        else
        {
            stRfChTmp.stTPSetting.u16Frequency = (U16)(55250L/FREQ_STEP);
        }

        stRfChTmp.stTPSetting.fModulation = DEMOD_ATSC_MODE_NTSC;

        stVirChTmp.stVirtualChNum.major_num = i;
        stVirChTmp.stVirtualChNum.minor_num = 0;

        MApp_ChanProc_SetSingleChannel( &stVirChTmp, i-1);

        MApp_DB_ATSC_SaveRfChannel(stVirChTmp.u8RfNum, &stRfChTmp);

    }

    ANT_TYPE = u8TempAntType;
    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);

    //memcpy((U8*)&stChSetting,(U8*)_PA2VA(u32ChSettingStartAddr),u16ChSettingLength);
    MApp_DB_ATSC_LoadChSetting( &stChSetting );
}
#endif

BOOLEAN MApp_ChanProc_IsAnyChannelExist(void)
{
    if( stChSetting.u16MainListSrvNum > 0 )
        return TRUE;

    return FALSE;
}

void MApp_CM_PrintServiceName(U8* pu8ServiceName )
{
    U8 i;
    U16 u16Data;

    printf(" ServiceName=[");

    for( i = 0; i < MAX_LENGTH_OF_SERVICE_NAME; i += 2 )
    {
        u16Data = (pu8ServiceName[i]<<8) + pu8ServiceName[i+1];
        if( u16Data == 0 )
        {
            //printf("(%x,%X)", pu8ServiceName[i],pu8ServiceName[i+1]);
            break;
        }
        if( u16Data < 0x80 )
            putchar(u16Data);
        else
            printf("(%x)", u16Data);
    }

#if 0
    U8 u8Data;
    printf("<");
    for( i = 0; i < 6; ++ i )
    {
        u8Data = pu8ServiceName[i];
        printf(" %x", u8Data);
    }
    printf(" >");
#endif

    printf("] ");
}

void MApp_CM_PrintAllCh(void)
{
    U16 u16MainListSrvNum = stChSetting.u16MainListSrvNum;
    U16 u16MainListIdx;
    U8 u8PhyChIdx;
    U16 u16VirChInfoIdx;
    U16 u16VirChIdx;
    MS_VIRTUAL_CHANNEL stVirCh;
    MS_PHYSICAL_CHANNEL* pPhyCh;
    MS_MAINLIST_A* pstMainList;

    MS_RF_CHANNEL_new stRfCh_Tmp;


    printf("\n========== MApp_CM_PrintAllCh() ==========\n");

    printf(" MAX_NUM_OF_CATV_VIR_CH=%u\n", MAX_NUM_OF_CATV_VIR_CH);
    printf(" MAX_CATV_PHYSICAL_CH_NUM=%u\n", MAX_CATV_PHYSICAL_CH_NUM);

    printf(" sizeof(MS_CHANNEL_SETTING)=%u\n", sizeof(MS_CHANNEL_SETTING));
    printf(" sizeof(MS_VIRTUAL_CHANNEL)=%u\n", sizeof(MS_VIRTUAL_CHANNEL));
    printf(" sizeof(MS_RF_CHANNEL_new)=%u\n", sizeof(MS_RF_CHANNEL_new));

    printf(" RM_AIR_CH_SETTING_LEN=0x%X\n", RM_AIR_CH_SETTING_LEN);
    printf(" RM_CATV_CH_SETTING_LEN=0x%X\n", RM_CATV_CH_SETTING_LEN);

    printf(" RM_AIR_VIR_CH_LEN=0x%X\n", RM_AIR_VIR_CH_LEN);
    printf(" RM_CATV_VIR_CH_LEN=0x%X\n", RM_CATV_VIR_CH_LEN);

    printf(" RM_ATSC_AIR_RF_CH_LEN=0x%X\n", RM_ATSC_AIR_RF_CH_LEN);
    printf(" RM_ATSC_CATV_RF_CH_LEN=0x%X\n", RM_ATSC_CATV_RF_CH_LEN);

    printf(" enCurProgListType=%u\n", enCurProgListType);
    printf(" u16PreProgIndexOfMainList=%u\n", u16PreProgIndexOfMainList);
    printf(" g_u16CurProgIndexOfMainList=%u\n", g_u16CurProgIndexOfMainList);

    printf(" u16MainListSrvNum=%u\n", u16MainListSrvNum);


    // Dump Physical channel
    if(1)
    {
        printf("\n========== Physical channel: ==========\n");
        for( u8PhyChIdx = 0; u8PhyChIdx < MAX_CATV_PHYSICAL_CH_NUM; u8PhyChIdx += 1)
        {
            pPhyCh = &(stChSetting.astPhysicalCh[u8PhyChIdx]);
            if( pPhyCh->u8NumOfVirCh > 0 )
            {
                printf(" u8PhyChIdx=%u,", u8PhyChIdx);
                printf(" u8NumOfVirCh=%u,", pPhyCh->u8NumOfVirCh);
                printf(" u16VirChInfoStartIdx=%u\n", pPhyCh->u16VirChInfoStartIdx);
            }
        }
    }


    printf("\n========== Main List: ==========\n");
    if( u16MainListSrvNum == 0 )
    {
        u16MainListSrvNum = 1;
        printf("Force u16MainListSrvNum to 1\n");
    }

    // channel in main list is start from index=1
    for( u16MainListIdx = 1; (u16MainListIdx <= u16MainListSrvNum); u16MainListIdx += 1)
    {
        printf("---------- u16MainListIdx=%u ----------\n", u16MainListIdx);

        pstMainList = &(stChSetting.astMainList[u16MainListIdx]);

    // #define PHY_CH_IDX(ch_idx)          (stChSetting.astMainList[ch_idx].u8PhysicalChIdx)
        u8PhyChIdx = PHY_CH_IDX(u16MainListIdx);
        printf(" PHY_CH_IDX(idx)=%u,", u8PhyChIdx);

        printf(" u8VirChInfoIdx(offset)=%u\n", pstMainList->u8VirChInfoIdx);

        if( u8PhyChIdx == 0 )
            continue;

        pPhyCh = &(stChSetting.astPhysicalCh[u8PhyChIdx]);

        //printf("  u8NumOfVirCh=%u,", pPhyCh->u8NumOfVirCh);
        printf(" u16VirChInfoStartIdx=%u\n", pPhyCh->u16VirChInfoStartIdx);

    // #define VIR_CHINFO_IDX(ch_idx)        (stChSetting.astPhysicalCh[PHY_CH_IDX(ch_idx)].u16VirChInfoStartIdx + stChSetting.astMainList[ch_idx].u8VirChInfoIdx)
        u16VirChInfoIdx = VIR_CHINFO_IDX(u16MainListIdx);
        printf("  VIR_CHINFO_IDX(idx)=%u\n", u16VirChInfoIdx);

    // #define VIR_CH_IDX(ch_idx)            (stChSetting.astVirtualChInfo[VIR_CHINFO_IDX(ch_idx)].u16VirChIdx)
        //u16VirChIdx = VIR_CH_IDX(u16MainListIdx);
        //printf("  VIR_CH_IDX(idx)=%u\n", u16VirChIdx);
        u16VirChIdx = stChSetting.astVirtualChInfo[u16VirChInfoIdx].u16VirChIdx;
        printf("    u16VirChIdx=%u,", u16VirChIdx);
        //printf("    fIsDirCh=%u\n", stChSetting.astVirtualChInfo[u16VirChInfoIdx].fIsDirCh);


        // coverity 94696
        memset(&stVirCh, 0, sizeof(MS_VIRTUAL_CHANNEL));

        //MApp_ChanProc_GetSingleChannel(&stVirCh, u16VriChIdx);
        MApp_DB_ATSC_LoadVirChannel(u16VirChIdx, &stVirCh);

        printf(" u8RfNum=%u, u16ProgramNumber=%u\n", stVirCh.u8RfNum, stVirCh.u16ProgramNumber );

        printf(" VirNum=%u.%u\n", stVirCh.stVirtualChNum.major_num, stVirCh.stVirtualChNum.minor_num);

        printf("  ServiceType=%u, ", stVirCh.u8ServiceType);

        MApp_CM_PrintServiceName(stVirCh.acServiceName);

        printf("\n");

        // RF channel ...
        memset(&stRfCh_Tmp, 0, sizeof(stRfCh_Tmp));
        MApp_DB_ATSC_LoadRfChannel(stVirCh.u8RfNum, &stRfCh_Tmp);

        U32 u32FreqKHz = (U32)(stRfCh_Tmp.stTPSetting.u16Frequency)*FREQ_STEP;
        printf(" Demod=%u, FreqKHz=%u\n", stRfCh_Tmp.stTPSetting.fModulation, u32FreqKHz );

        printf("\n");

    }

    printf("\n");

}

//==============================================================================

U8 msAPI_CM_ATSC_Get_ServiceType(U16 u16VirChIdx)
{
    MS_VIRTUAL_CHANNEL stVirChTmp;

    memset( &stVirChTmp, 0, sizeof(stVirChTmp) );

    MApp_DB_ATSC_LoadVirChannel(u16VirChIdx, &stVirChTmp);

    return stVirChTmp.u8ServiceType;
}

//==============================================================================

U16 msAPI_ChProc_ATSC_Get_MainListIdx_By_ProgPos(U16 u16ProgPosition)
{
    U16 u16MainListIdx = u16ProgPosition + 1;

    return u16MainListIdx;
}

U8 msAPI_ChProc_ATSC_Get_Attr_Lock_By_MainListIdx(U16 u16MainListIdx)
{
    UNUSED(u16MainListIdx);
    return 0;
}

U8 msAPI_ChProc_ATSC_Get_Attr_Fav_By_MainListIdx(U16 u16MainListIdx)
{
    //U16 u16MainListIdx = msAPI_ChProc_ATSC_Get_MainListIdx_By_ProgPos(u16ProgPosition);
    return IS_FAV_CH_ATSC(u16MainListIdx);
}

BOOLEAN msAPI_ChProc_ATSC_Get_VirCh_By_MainListIdx(U16 u16MainListIdx, MS_VIRTUAL_CHANNEL* pstVirCh)
{
    if( pstVirCh == NULL )
    {
        return FALSE;
    }

    memset( pstVirCh, 0, sizeof(MS_VIRTUAL_CHANNEL) );

    //U16 u16MainListIdx = msAPI_ChProc_ATSC_Get_MainListIdx_By_ProgPos(u16ProgPosition);
    if( FALSE == MApp_ChanProc_Is_MainListProgIdxValid(u16MainListIdx) )
    {
        printf("\nError: u16MainListIdx=%u is invalid!\n", u16MainListIdx );
        return FALSE;
    }

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    U16 u16VirChIdx;
    if (u16MainListIdx <= stChSettingDisp[ANT_AIR].u16MainListSrvNum)
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
        u16VirChIdx = VIR_CH_IDX_AIR(u16MainListIdx);
    }
    else
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
        u16VirChIdx = VIR_CH_IDX_CATV(u16MainListIdx-stChSettingDisp[ANT_AIR].u16MainListSrvNum);
    }

    //printf("u16VirChIdx=%u\n", u16VirChIdx );
    MApp_ChanProc_GetSingleChannel( pstVirCh, u16VirChIdx);

    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);

#else

    U16 u16VirChIdx = VIR_CH_IDX(u16MainListIdx);
    //printf("u16VirChIdx=%u\n", u16VirChIdx );

    MApp_ChanProc_GetSingleChannel( pstVirCh, u16VirChIdx);

#endif

    return TRUE;
}

MEMBER_SERVICETYPE msAPI_ChProc_ATSC_Get_ServiceType_By_MainListIdx(U16 u16MainListIdx)
{
    MS_VIRTUAL_CHANNEL stVirChTmp;
    memset( &stVirChTmp, 0, sizeof(stVirChTmp) );

    if( !msAPI_ChProc_ATSC_Get_VirCh_By_MainListIdx( u16MainListIdx, &stVirChTmp) )
    {
        return E_SERVICETYPE_ATV;
    }

    U8 u8ServiceType = stVirChTmp.u8ServiceType;

    MEMBER_SERVICETYPE eServiceType = E_SERVICETYPE_ATV;

    switch(u8ServiceType)
    {
        default:
        case EN_PSIP_SERVICE_ANALOG:
            eServiceType = E_SERVICETYPE_ATV;
            break;

        case EN_PSIP_SERVICE_DTV:
            eServiceType = E_SERVICETYPE_DTV;
            break;

        case EN_PSIP_SERVICE_DATA:
            eServiceType = E_SERVICETYPE_DATA;
            break;

        case EN_PSIP_SERVICE_AUDIO:
            eServiceType = E_SERVICETYPE_RADIO;
            break;
    }

    return eServiceType;
}

void msAPI_ChProc_ATSC_Get_VirChNum_By_MainListIdx(U16 u16MainListIdx, MS_VIRTUAL_CHANNEL_NUM* pstVirChNum)
{
    if( pstVirChNum == NULL )
    {
        return;
    }

    memset( pstVirChNum, 0, sizeof(MS_VIRTUAL_CHANNEL_NUM) );

    MS_VIRTUAL_CHANNEL stVirChTmp;
    memset( &stVirChTmp, 0, sizeof(stVirChTmp) );

    if( !msAPI_ChProc_ATSC_Get_VirCh_By_MainListIdx( u16MainListIdx, &stVirChTmp) )
    {
        return ;
    }

    *pstVirChNum = stVirChTmp.stVirtualChNum;

}

#endif // #if(ENABLE_ATSC)

//------------------------------------------------------------------------------

#undef MAPP_CHANNELPROC_ATSC_C

