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
/*
++++++++++++++++++++++++++++++++++???????????????++++++++++++++++++++++++++++++++++++++++++??????????????????????++++++++++++++++++++++++++++++++++++++++=++????
++++++++++++++++++++++++++++++++++IIIIIIIIIIIIII????????????????????????????????????????????IIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++++++++++++++++++++++++++++++IIIIIIIIIIII????????????????????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=+IIIIIIIIIII+++++++++++++++?$$$$$$$$$77II??????????I???????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++++DMMMMMMMMMMMZI++++++++++++=NMMMMMMMMMMMZ$?I77$$$$$$I?????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMD7=+++++++++IMMMMMMMMMMMMM8OZZ$7I???????????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMM8++++++++++DMMMMMMMMMMMMMD8$I?????????????????III???????????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++=+?=8MMMMMMMMMMMMMMZZ++++++?DMMMMMMMMMMMMMMZZ???????????????IIIIIIIIIII????????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I=DMMMMMMMMMMMMMMMN?=++++8MMMMMMMMMMMMMMMZ$??????????????IIIIIIIIIIIIII??????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I+8MMMMMMMMMMMMMMMMD?=+IDMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIII????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++?I+8MMMMMMMMMMMMMMMMMOI~OMMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIIII????????????IIIIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++II+8MMMMMMMMMMMNNMMNMND8MMNNMMNNMMMMMMMMMMZ$????????????IZZ8888OZ7IIIIIIIIIIIIIIIIIIIIIIZD7IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++++II+8MMMMMMMMMMII????????OOOOOOZ8MMMMMMMMMMZ$??????????ZDMMMMMDDDNND87IIIIIIIIIIIIIII?Z8MMDIIIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI++++++7$ZZZZZZZOOMMMMMMMMMMZ$??????IINMMMMMMD+IIII7I7DMMIIIIIIII?I8NMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI+++++I$ZZZZZZZZ$ZMMMMMMMMMMZ$??????IMMMMMMMMMI??????IIO87IIIIII?DMMMMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++?III+8MMMMMMMMMMI++=$$ZZZZZZZZZIIZMMMMMMMMMMZ$??????MMMMMMMMMMMZ??????????????IIIMMMMMMMMMMD$ZZZZIIIIIIIIII+Z8DDNMMMDDDOO$I?????????????IIIII$ZZZ7IIII7O8887II
+?IIII+8MMMMMMMMMMI++7ZZZZZZZZZZI+IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMM$????????????OMMMMMMMMMMMMMMMMMMNIIIIIIIII8MMMD888DMMMMMMMND$?????????8MMMMMMMMMMOII78MMMMM8?I
+?IIII+8MMMMMMMMMMI?7ZZZZZZZZZZ?++IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMMMM8??????????+++?MMMMMMMMMM8IIIIIIIIIIIZMMM77IIIIIII8MMMMMMMMND?II????8MMMMMMMMMMOODNZII7Z8I7I
?IIIII+8MMMMMMMMMMZZZZZZZZZZZZI+++IZMMMMMMMMMMZ$??????NMMMMMMMMMMMMMMDII??????????IMMMMMMMMMM8IIIIIIIIIIIO8ZI?IIIIIIIIZDMMMMMMMMMD??????8MMMMMMMMMMN8D7IIIIIIIII
?IIIII+8MMMMMMMMMNZZZZZZZZZZZZ++++?ZMMMMMMMMMMZ$??????ZMMMMMMMMMMMMMMMMN7?????????IMMMMMMMMMM8IIIIIIIIIIIIIII?IIIIIIIIZDMMMMMMMMMMI?????8MMMMMMMMMM8IIIIIIIIIIII
?IIIII+8MMMMMMMMN8ZZZZZZZZZZZ?++++?ZMMMMMMMMMMZ$??????I8MMMMMMMMMMMMMMMM8?????????IMMMMMMMMMMO?IIIIIIIIIIIII7I7777777IODMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMNZZZZZZZZZZZZ7+++++?ZMMMMMMMMMMZ$????????8MMMMMMMMMMMMMMMMDD???????IMMMMMMMMMMO??IIIIIIIII7DMMMMMMMDDMDDNMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNZZZZZZZZZZZZ$++++++?ZMMMMMMMMMMZ$I????????7NMMMMMMMMMMMMMMMMDI?????IMMMMMMMMMMO????IIIIIZ8MMMMMMMM7III7ONMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNOZZZZZZZZZZZ7++++++?ZMMMMMMMMMMZ$III??????+IMMMMMMMMMMMMMMMMN$+????IMMMMMMMMMMO????IIII?NMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMNOZZZZZZZZ?++++++?ZMMMMMMMMMMZ$IIII????????ZMMMMMMMMMMMMMMMO?????IMMMMMMMMMMZ?????III$MMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMM?$ZZZZZZ$+++++++?ZMMMMMMMMMMZ$IIIIIIIIII???ZMMMMMMMMMMMMMMDZ????IMMMMMMMMMMZ?????IIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII=DMMMMMMMMMM?++7ZZZ7?+++++++IZMMMMMMMMMMZ$IIIIIIIIIIIIII7OMMMMMMMMMMMM8?????IMMMMMMMMMMZ????IIIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?II?II+8MMMMMMMMMMI++?ZOZ7?+++++++?ZMMMMMMMMMMZ$IIII7OZIIIIIIIII8MMMMMMMMMMMZ?????IMMMMMMMMMM$???OOD7IIMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIMMMMMMMMMMMMMMNNNN8O$I++++?NMNNMMMMMMMMMMMMMMD8I77NM8IIIIIIIIOMMMMMMMMMO??????+8MMMMMMMMMZ??$MM$?IIZMMMMMMMMM?IIIZNMMMMMMMMMMMZ?????8MMMMMMMMMMOIIIIIIIIIIII
?II?MMMMMMMMMMMMMMMMMM88??++++?MMMMMMMMMMMMMMMMMMD8II7IDMMOIIIIIIOMMMMMMMDOIIII??I??NMMMMMMMMMO8MZ$?IIIIZMMMMMMMMZIZ8MDMMMMMMMMMMMO?????8MMMMMMMMMMOIIIIIIIIIIII
?II?DDDDDDDDDDDDDDD8DDZ$++++++?D8D8DDDDDDDDDDDDDDOZIIIIII?7ODMMMMMMMNDZ7?IIIIIII??????ZDMMMMN8Z7??I?IIIIIIIZ8MMMMN8Z??7$ZZZZZZZZZZZ+????IZZZZZZZZZZ7IIIIIIIIIIII
?IIIII++++++++++++++++=+++++++++++IIIIIIIIIIIIIIIIII???I?????I77ZZ77IIIIIIIIIIIII????I???II??????????IIIIIIII?777IIIIIIII???????????????????????IIIIIIIIIIIIIIII
*/
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

#define MAPP_CIPVR_ADAPTION_C

//system
#include "Board.h"     //For pvr select
#include "MApp_GlobalSettingSt.h"

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "apiXC_Sys.h"

#include "MApp_CIPVR_Adaption.h"               //For itself
#include "msAPI_CI.h"
#include "msAPI_DTVSystem.h"
#include "MApp_CIMMI.h"
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
#include "MApp_TV.h"
#endif
#include "MApp_PVR.h"
#include "MApp_Record.h"
#include "MApp_Playback.h"
#include "MApp_UiPvr.h"            //For timer
#include "msAPI_Timer.h"           //For timer

#define PVR_DBG(x)                 x
#define PVR_TRACE(x)               //x

#define CIPVR_MONITOR_INTERVAL_TIME 300 //ms

EN_CC_PVR_OPERATING_MODE m_eOperatingMode = EN_CC_PVR_OPERATING_MODE_RESERVED;
static EN_CC_PVR_DATATYPE_ID m_eOperatingType = EN_CC_DATATYPE_ID_UNKNOW;
static PinEventHander m_RecordPinEventHander;
static UriLicenseHander m_RecordUriLicenseHander;
static PinEventHander m_PlaybackPinEventHander;
static UriLicenseHander m_PlaybackUriLicenseHander;
static U32 u3RecordIntervalTime;
static U32 u3PlaybackIntervalTime;
static U32 u32LicenseEndTime;
static U8 u8afPineventBuffer[MAX_EVENTINFO_NUM*sizeof(PinEventInfo)+16];
static U8 u8afUriLicenseBuffer[MAX_EVENTINFO_NUM*sizeof(UriLicenseInfo)+16];

static BOOL _MAPP_CIPVR_CICheckOperatingModeStatus(U32 u32Timeout)
{
    if ( (FALSE == msAPI_CI_CardDetect())
         || (EN_CC_VERSION_V2 > msAPI_CI_CC_GetCicamCCVersion()) )
    {
        return FALSE;
    }

    U32 u32Timer = msAPI_Timer_GetTime0();
    EN_CC_SYNC_CNF_STATUS OperatingModeStatus = EN_CC_SYNC_CNF_STATUS_RESERVED;
    while (msAPI_Timer_DiffTimeFromNow(u32Timer) < u32Timeout)
    {
        OperatingModeStatus = EN_CC_SYNC_CNF_STATUS_RESERVED;
        msAPI_CI_MAINLOOP();
        switch (m_eOperatingType)
        {
            case EN_CC_DATATYPE_ID_RECORD_START:
            {
                OperatingModeStatus = msAPI_CI_CC_GetRecordStartStatus();
                if (EN_CC_SYNC_CNF_STATUS_RESERVED == OperatingModeStatus)
                {
                    msAPI_Timer_Delayms(20);
                }
                else
                {
                    if (EN_CC_SYNC_CNF_STATUS_OK != OperatingModeStatus)
                    {
                        PVR_DBG(printf("[CI][PVR] Record Start Stauts Error(%u) \n", OperatingModeStatus));
                        m_eOperatingMode = EN_CC_PVR_OPERATING_MODE_RESERVED;
                    }
                    return (EN_CC_SYNC_CNF_STATUS_OK == OperatingModeStatus);
                }
                break;
            }

            case EN_CC_DATATYPE_ID_MODE_CHANGE:
            {
                OperatingModeStatus = msAPI_CI_CC_GetRecordStartStatus();
                if (EN_CC_SYNC_CNF_STATUS_RESERVED == OperatingModeStatus)
                {
                    msAPI_Timer_Delayms(20);
                }
                else
                {
                    return (EN_CC_SYNC_CNF_STATUS_OK == OperatingModeStatus);
                }
                break;
            }

            case EN_CC_DATATYPE_ID_RECORD_STOP:
            {
                OperatingModeStatus = msAPI_CI_CC_GetRecordStartStatus();
                if (EN_CC_SYNC_CNF_STATUS_RESERVED == OperatingModeStatus)
                {
                    msAPI_Timer_Delayms(20);
                }
                else
                {
                    return (EN_CC_SYNC_CNF_STATUS_OK == OperatingModeStatus);
                }
                break;
            }

            default:
                ASSERT(0);
                break;
        }
    }

    if (EN_CC_DATATYPE_ID_RECORD_START == m_eOperatingType)
    {
#if (ENABLE_CI_PLUS == 1)
        m_eOperatingMode = EN_CC_PVR_OPERATING_MODE_RESERVED;
#endif
    }
    return FALSE;
}

static void _MAPP_CIPVR_PVRTriggerURICopyProtect(CI_CC_URI_LICENSE stUriLicense)
{
    U8 u8URI_RCT, u8URI_EMI, u8URI_APS, u8URI_ICT, u8URI_DOT, u8URI_RL;
    u8URI_RCT = 0;
    u8URI_EMI = 0;
    u8URI_APS = 0;
    u8URI_ICT = 0;
    u8URI_DOT = 0;
    u8URI_RL = 0;
    if(!stUriLicense.m_bUriValid)
    {
        return ;
    }

    msAPI_CI_CC_UriMappingConvert(TRUE, FALSE, TRUE,
                                  stUriLicense, &u8URI_DOT, &u8URI_RCT, &u8URI_EMI, &u8URI_APS, &u8URI_ICT, &u8URI_RL);
    PVR_DBG(printf("[PVRTriggerURICopyProtect]URI(%u, %u, %u, %u, %u, %u) \n",
                  u8URI_DOT, u8URI_RCT, u8URI_EMI, u8URI_APS, u8URI_ICT, u8URI_RL));
    MApp_CI_CC_CopyProtect(u8URI_DOT,u8URI_RCT,u8URI_EMI,u8URI_APS,u8URI_ICT,u8URI_RL);
}

static void _MAPP_CIPVR_VirtualFwrite(U8 *dest, const U8 *src, U16 u16Size, U8 u8Offset)
{
    memcpy(&dest[u8Offset], src, u16Size);
}

static void _MAPP_CIPVR_VirtualFread(U8 *dest, const U8 *src, U16 u16Size, U8 u8Offset)
{
    memcpy(dest, &src[u8Offset], u16Size);
}

static BOOL _MAPP_CIPVR_PinEventUpdate(BOOL bCreat, PinEventInfo pinEventInfo)
{
    if ( (INVALID_FILE_HANDLE == m_RecordPinEventHander.m_hPineventFile)
        || (0 == m_RecordPinEventHander.m_hPineventFile) )
    {
        return FALSE;
    }

    if (m_RecordPinEventHander.u8PinEventCount >= MAX_EVENTINFO_NUM)
    {
        return FALSE;
    }

    LongLong llSeekLen;
    llSeekLen.Lo = 0;
    llSeekLen.Hi = 0;
    msAPI_PVRFS_FileSeek(m_RecordPinEventHander.m_hPineventFile, llSeekLen, PVRFS_SEEK_OPTION_FROM_BEGIN);

    BOOL bhasSameEvent = FALSE;
    BOOL bneedUpdateEvent = FALSE;
    U8 needUpdateIndex = 0;
    U8 i;

    if (FALSE == bCreat)
    {
        for (i=0; i<m_RecordPinEventHander.u8PinEventCount; i++)
        {
            if (pinEventInfo.u32BlockBeginTime == m_RecordPinEventHander.m_PinEventInfo[i].u32BlockBeginTime)
            {
                bneedUpdateEvent = TRUE;
                needUpdateIndex = i;
            }

            if ( (pinEventInfo.pvrPinEvent.u16program_number == m_RecordPinEventHander.m_PinEventInfo[i].pvrPinEvent.u16program_number)
                 && (pinEventInfo.pvrPinEvent.u8PINcode_status_field == m_RecordPinEventHander.m_PinEventInfo[i].pvrPinEvent.u8PINcode_status_field)
                 && (pinEventInfo.pvrPinEvent.u8rating == m_RecordPinEventHander.m_PinEventInfo[i].pvrPinEvent.u8rating)
                 && (pinEventInfo.pvrPinEvent.u8pin_event_time_centiseconds == m_RecordPinEventHander.m_PinEventInfo[i].pvrPinEvent.u8pin_event_time_centiseconds)
                 && (0 == memcmp(pinEventInfo.pvrPinEvent.au8pin_event_time_utc ,m_RecordPinEventHander.m_PinEventInfo[i].pvrPinEvent.au8pin_event_time_utc  ,CI_UTC_TIME_LEN))
                 && (0 == memcmp(pinEventInfo.pvrPinEvent.au8private_data,m_RecordPinEventHander.m_PinEventInfo[i].pvrPinEvent.au8private_data ,CI_CC_PIN_EVENT_PRIVATE_DATA_LEN)))
            {
                bhasSameEvent = TRUE;
                break;
            }
            else if (bneedUpdateEvent)
            {
                break;
            }
        }

        if (bhasSameEvent)
        {
            return FALSE;
        }
        else if (bneedUpdateEvent)
        {
            if(TRUE == pinEventInfo.pvrPinEvent.bValid)
            {
                memcpy(&m_RecordPinEventHander.m_PinEventInfo[needUpdateIndex], &pinEventInfo, sizeof(PinEventInfo));
            }
        }
        else
        {
            memcpy(&m_RecordPinEventHander.m_PinEventInfo[m_RecordPinEventHander.u8PinEventCount], &pinEventInfo, sizeof(PinEventInfo));
            m_RecordPinEventHander.u8PinEventCount++;
        }
    }
    else
    {
        m_RecordPinEventHander.u8PinEventCount = 0;
        memcpy(&m_RecordPinEventHander.m_PinEventInfo[0], &pinEventInfo, sizeof(PinEventInfo));
    }

    U8* pu8NonCacheBuffer = (U8*)msOS_CacheToNonCache((U32)u8afPineventBuffer);
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, &m_RecordPinEventHander.u8PinEventCount, 1, 0);  // p[0]
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, (U8*)m_RecordPinEventHander.m_PinEventInfo, MAX_EVENTINFO_NUM*sizeof(PinEventInfo), 1); // p[1]

    MsOS_FlushMemory();
    if ( (TRUE == bCreat)
         || (E_PVR_ENCRYPTION_NONE != MApp_PVR_GetEncryptionType()) )
    {
        msAPI_PVR_AESDMAEncryptDecrypt((U32)pu8NonCacheBuffer, sizeof(u8afPineventBuffer), E_ENCRYPT);
    }
    MsOS_FlushMemory();

    U8 j = 0;
    for (j=0; j<m_RecordPinEventHander.u8PinEventCount; j++)
    {
        PVR_DBG( printf("[Record]PinEventUpdate(%u, %u, %u, %u, %u, %u, %u, %u)\n",
            m_RecordPinEventHander.m_PinEventInfo[j].pvrPinEvent.au8private_data[0],
            m_RecordPinEventHander.m_PinEventInfo[j].pvrPinEvent.au8private_data[1],
            m_RecordPinEventHander.m_PinEventInfo[j].pvrPinEvent.au8private_data[2],
            m_RecordPinEventHander.m_PinEventInfo[j].pvrPinEvent.au8private_data[3],
            m_RecordPinEventHander.m_PinEventInfo[j].pvrPinEvent.au8private_data[4],
            m_RecordPinEventHander.m_PinEventInfo[j].u32BlockBeginTime,
            m_RecordPinEventHander.m_PinEventInfo[j].pvrPinEvent.bVideoBlanking,
            m_RecordPinEventHander.m_PinEventInfo[j].pvrPinEvent.bValid); );
    }

    msAPI_CIPVRFS_FileWrite(m_RecordPinEventHander.m_hPineventFile, (U32)pu8NonCacheBuffer, sizeof(u8afPineventBuffer));
    return TRUE;
}

static BOOL _MAPP_CIPVR_PinEventMonitor(PinEventInfo* pinEventInfo, BOOL bPlayback)
{
    int i;
    int curIdx = 0;
    if (TRUE == bPlayback)
    {
        U32 playbacktime = MApp_PVR_GetPlaybackTimeSec();
        U32 u32CurrentTimeID;
        for (i=0; i<m_PlaybackPinEventHander.u8PinEventCount; i++)
        {
            if ( ((i < (m_PlaybackPinEventHander.u8PinEventCount - 1))
                  && (playbacktime > m_PlaybackPinEventHander.m_PinEventInfo[i].u32BlockBeginTime)
                  && (playbacktime < m_PlaybackPinEventHander.m_PinEventInfo[i+1].u32BlockBeginTime))
                 ||
                 ((i == m_PlaybackPinEventHander.u8PinEventCount - 1)
                  && (playbacktime > m_PlaybackPinEventHander.m_PinEventInfo[i].u32BlockBeginTime)) )
            {
                u32CurrentTimeID = m_PlaybackPinEventHander.m_PinEventInfo[i].u32BlockBeginTime;
                if (m_PlaybackPinEventHander.m_u32ActiveID != u32CurrentTimeID)
                {
                    m_PlaybackPinEventHander.m_u32ActiveID = u32CurrentTimeID;
                    m_PlaybackPinEventHander.m_bActive = TRUE;
                    curIdx = i;
                }
                break;
            }
        }

        if (TRUE == m_PlaybackPinEventHander.m_bActive)
        {
            m_PlaybackPinEventHander.m_bActive = FALSE;
            memcpy(pinEventInfo, &m_PlaybackPinEventHander.m_PinEventInfo[curIdx], sizeof(PinEventInfo));
            return TRUE;
        }
    }
    else if (FALSE == bPlayback)
    {
        U32 u32CurrentTimeID;
        U32 recordtime = MApp_PVR_GetCurRecordTimeInSec();
        for (i=0; i<m_RecordPinEventHander.u8PinEventCount; i++)
        {
            if ( ((i < (m_RecordPinEventHander.u8PinEventCount - 1))
                  && (recordtime > m_RecordPinEventHander.m_PinEventInfo[i].u32BlockBeginTime)
                  && (recordtime < m_RecordPinEventHander.m_PinEventInfo[i+1].u32BlockBeginTime) )
                 ||
                  ((i == m_RecordPinEventHander.u8PinEventCount - 1)
                  && (recordtime > m_RecordPinEventHander.m_PinEventInfo[i].u32BlockBeginTime)) )
            {
                u32CurrentTimeID = m_RecordPinEventHander.m_PinEventInfo[i].u32BlockBeginTime;
                if (m_RecordPinEventHander.m_u32ActiveID != u32CurrentTimeID)
                {
                    m_RecordPinEventHander.m_u32ActiveID = u32CurrentTimeID;
                    m_RecordPinEventHander.m_bActive = TRUE;
                    curIdx = i;
                }
                break;
            }
        }

        if (TRUE == m_RecordPinEventHander.m_bActive)
        {
            m_RecordPinEventHander.m_bActive = FALSE;
            memcpy(pinEventInfo, &m_RecordPinEventHander.m_PinEventInfo[curIdx], sizeof(PinEventInfo));
            return TRUE;
        }
    }
    return FALSE;
}

static BOOL _MAPP_CIPVR_CicamUriLicenseUpdate(UriLicenseInfo urilicenseInfo)
{
    if ( (INVALID_FILE_HANDLE == m_RecordUriLicenseHander.m_hUrilicenseFile)
         || (0 == m_RecordUriLicenseHander.m_hUrilicenseFile) )
    {
        return FALSE;
    }

    if  (m_RecordUriLicenseHander.u8UrilicenseCount >= MAX_EVENTINFO_NUM)
    {
        return FALSE;
    }

    LongLong llSeekLen;
    llSeekLen.Lo = 0;
    llSeekLen.Hi = 0;
    msAPI_PVRFS_FileSeek(m_RecordUriLicenseHander.m_hUrilicenseFile, llSeekLen, PVRFS_SEEK_OPTION_FROM_BEGIN);

    BOOL bhasSameEvent = FALSE;
    BOOL bneedUpdateEvent = FALSE;
    int needUpdateIndex = 0;
    U8 i;

    for (i=0; i<m_RecordUriLicenseHander.u8UrilicenseCount; i++)
    {
        if (urilicenseInfo.u32BlockBeginTime == m_RecordUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)
        {
            bneedUpdateEvent = TRUE;
            needUpdateIndex = i;
        }

        if ((urilicenseInfo.pvrUriLicense.m_u16program_number == m_RecordUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_u16program_number)
            && (urilicenseInfo.pvrUriLicense.m_u8license_status == m_RecordUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_u8license_status)
            && (urilicenseInfo.pvrUriLicense.m_u8play_count == m_RecordUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_u8play_count)
            && (0 == memcmp(urilicenseInfo.pvrUriLicense.m_stl_license,m_RecordUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_stl_license, MAX_LICENSE_SIZE))
            && (0 == memcmp(urilicenseInfo.pvrUriLicense.m_unUriMessage.au8URI_Message,m_RecordUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_unUriMessage.au8URI_Message, CC_AUTH_URI_SIZE)))
        {
            bhasSameEvent = TRUE;
            break;
        }
        else if (bneedUpdateEvent)
        {
            break;
        }
    }

    if (bhasSameEvent)
    {
        return FALSE;
    }
    else if (bneedUpdateEvent)
    {
        if ( TRUE == urilicenseInfo.pvrUriLicense.m_bLicenseAvailable)
        {
            U32 u32OriginalExpiredTime = m_RecordUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ExpiredTime;
            urilicenseInfo.u32BlockEndTime = m_RecordUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].u32BlockEndTime;

            PVR_DBG(printf("[CicamUriLicenseUpdate] Update \n"));
            memcpy(&m_RecordUriLicenseHander.m_UrilicenseInfo[needUpdateIndex], &urilicenseInfo, sizeof(UriLicenseInfo));
            m_RecordUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ReceivedTime = MApp_GetLocalSystemTime();
            m_RecordUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ExpiredTime = u32OriginalExpiredTime;
        }
        else
        {
            m_RecordUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u8license_status = urilicenseInfo.pvrUriLicense.m_u8license_status;
        }
    }
    else
    {
        if (m_RecordUriLicenseHander.u8UrilicenseCount != 0)
        {
            if (1 == urilicenseInfo.u32BlockBeginTime)
            {
                // Test Case 5.3.1.2
                // URI: 0~1 ; License: 1~59
                // License: 0 ~59
                PVR_DBG(printf("[CicamUriLicenseUpdate] Resave \n"));
                urilicenseInfo.u32BlockBeginTime = 0;
                memcpy(&m_RecordUriLicenseHander.m_UrilicenseInfo[m_RecordUriLicenseHander.u8UrilicenseCount-1], &urilicenseInfo, sizeof(UriLicenseInfo));
            }
            else
            {
                m_RecordUriLicenseHander.m_UrilicenseInfo[m_RecordUriLicenseHander.u8UrilicenseCount-1].u32BlockEndTime = urilicenseInfo.u32BlockBeginTime;
                memcpy(&m_RecordUriLicenseHander.m_UrilicenseInfo[m_RecordUriLicenseHander.u8UrilicenseCount], &urilicenseInfo, sizeof(UriLicenseInfo));
                m_RecordUriLicenseHander.u8UrilicenseCount++;
            }
        }
        else
        {
            memcpy(&m_RecordUriLicenseHander.m_UrilicenseInfo[m_RecordUriLicenseHander.u8UrilicenseCount], &urilicenseInfo, sizeof(UriLicenseInfo));
            m_RecordUriLicenseHander.u8UrilicenseCount++;
        }
    }

    U8* pu8NonCacheBuffer = (U8*)msOS_CacheToNonCache((U32)u8afUriLicenseBuffer);
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, &m_RecordUriLicenseHander.u8UrilicenseCount, 1, 0);  // p[0]
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, m_RecordUriLicenseHander.m_u8CICAMID, CC_AUTH_ID_SIZE, 1); // p[1]
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, (U8*)m_RecordUriLicenseHander.m_UrilicenseInfo, MAX_EVENTINFO_NUM*sizeof(UriLicenseInfo), 1+CC_AUTH_ID_SIZE); // p[9]

    MsOS_FlushMemory();
    if (E_PVR_ENCRYPTION_NONE != MApp_PVR_GetEncryptionType())
    {
        msAPI_PVR_AESDMAEncryptDecrypt((U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer), E_ENCRYPT);
    }
    MsOS_FlushMemory();

    U8 j = 0;
    for (j=0; j<m_RecordUriLicenseHander.u8UrilicenseCount; j++)
    {
        PVR_DBG(printf("[CicamUriLicenseUpdate] UriLicense[%u](Beg:%u, bLicenseAvailable:%u)\n",
                    j,
                    m_RecordUriLicenseHander.m_UrilicenseInfo[j].u32BlockBeginTime,
                    m_RecordUriLicenseHander.m_UrilicenseInfo[j].pvrUriLicense.m_bLicenseAvailable
                    )
        );
    }

    msAPI_CIPVRFS_FileWrite(m_RecordUriLicenseHander.m_hUrilicenseFile, (U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer));
    return TRUE;
}

static BOOL _MAPP_CIPVR_HostUriLicenseUpdate(UriLicenseInfo urilicenseInfo)
{
    if((m_PlaybackUriLicenseHander.m_hUrilicenseFile == INVALID_FILE_HANDLE) || (m_PlaybackUriLicenseHander.m_hUrilicenseFile == 0))
    {
        return FALSE;
    }

    LongLong llSeekLen;
    llSeekLen.Lo = 0;
    llSeekLen.Hi = 0;
    msAPI_PVRFS_FileSeek(m_PlaybackUriLicenseHander.m_hUrilicenseFile, llSeekLen, PVRFS_SEEK_OPTION_FROM_BEGIN);

    BOOL bhasSameEvent = FALSE;
    BOOL bneedUpdateEvent = FALSE;
    U8 needUpdateIndex = 0;

    U8 i;
    for (i=0; i < m_PlaybackUriLicenseHander.u8UrilicenseCount; i++)
    {
        if (urilicenseInfo.u32BlockBeginTime == m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)
        {
            bneedUpdateEvent = TRUE;
            needUpdateIndex = i;
        }
        if ( (urilicenseInfo.pvrUriLicense.m_u16program_number == m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_u16program_number)
             && (urilicenseInfo.pvrUriLicense.m_u8license_status == m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_u8license_status)
             && (urilicenseInfo.pvrUriLicense.m_u8play_count == m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_u8play_count)
             && (0 == memcmp(urilicenseInfo.pvrUriLicense.m_stl_license,m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_stl_license, MAX_LICENSE_SIZE))
             && (0 == memcmp(urilicenseInfo.pvrUriLicense.m_unUriMessage.au8URI_Message,m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_unUriMessage.au8URI_Message, CC_AUTH_URI_SIZE)) )
        {
            bhasSameEvent = TRUE;
            break;
        }
        else if (bneedUpdateEvent)
        {
            break;
        }
    }

    if (bhasSameEvent)
    {
        return FALSE;
    }
    else if (bneedUpdateEvent)
    {
        if ( (TRUE == urilicenseInfo.pvrUriLicense.m_bLicenseAvailable)
             && (TRUE == urilicenseInfo.pvrUriLicense.m_bLicenseValid) )
        {
            U32 u32OriginalExpiredTime = m_PlaybackUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ExpiredTime;
            memcpy(&m_PlaybackUriLicenseHander.m_UrilicenseInfo[needUpdateIndex], &urilicenseInfo, sizeof(UriLicenseInfo));
            m_PlaybackUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ReceivedTime = MApp_GetLocalSystemTime();
            m_PlaybackUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ExpiredTime = u32OriginalExpiredTime;
        }
        else
        {
            m_PlaybackUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u8license_status = urilicenseInfo.pvrUriLicense.m_u8license_status;
        }
    }
    else
    {
        memcpy(&m_PlaybackUriLicenseHander.m_UrilicenseInfo[ m_PlaybackUriLicenseHander.u8UrilicenseCount], &urilicenseInfo, sizeof(UriLicenseInfo));
        m_PlaybackUriLicenseHander.u8UrilicenseCount++;
    }

    U8* pu8NonCacheBuffer = (U8*)msOS_CacheToNonCache((U32)u8afUriLicenseBuffer);
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, &m_PlaybackUriLicenseHander.u8UrilicenseCount, 1, 0);  // p[0]
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, m_PlaybackUriLicenseHander.m_u8CICAMID, CC_AUTH_ID_SIZE, 1); // p[1]
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, (U8*)m_PlaybackUriLicenseHander.m_UrilicenseInfo, MAX_EVENTINFO_NUM*sizeof(UriLicenseInfo), 1+CC_AUTH_ID_SIZE); // p[9]

    MsOS_FlushMemory();
    if (E_PVR_ENCRYPTION_NONE != MApp_PVR_GetEncryptionType())
    {
        msAPI_PVR_AESDMAEncryptDecrypt((U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer), E_ENCRYPT);
    }
    MsOS_FlushMemory();

    U8 j = 0;
    for (j=0; j < m_PlaybackUriLicenseHander.u8UrilicenseCount; j++)
    {
        if (TRUE == m_PlaybackUriLicenseHander.m_UrilicenseInfo[j].pvrUriLicense.m_bLicenseAvailable)
        {
            PVR_DBG(printf("[HostUriLicenseUpdate] LicenseInfo[%u](Beg:%u, End:%u, Count:%u) \n",
                j,
                m_PlaybackUriLicenseHander.m_UrilicenseInfo[j].u32BlockBeginTime,
                m_PlaybackUriLicenseHander.m_UrilicenseInfo[j].u32BlockEndTime,
                m_PlaybackUriLicenseHander.m_UrilicenseInfo[j].pvrUriLicense.m_u8play_count
                ));
        }
        else
        {
            PVR_DBG(printf("[HostUriLicenseUpdate] UriInfo[%u](Beg:%u, End:%u) \n",
                j,
                m_PlaybackUriLicenseHander.m_UrilicenseInfo[j].u32BlockBeginTime,
                m_PlaybackUriLicenseHander.m_UrilicenseInfo[j].u32BlockEndTime
                ));
        }
    }

    msAPI_CIPVRFS_FileWrite(m_PlaybackUriLicenseHander.m_hUrilicenseFile, (U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer));
    return TRUE;
}

static BOOL _MAPP_CIPVR_UriLicenseUpdate(U32 u32TargetTime, U32 u32ExpiredTime)
{
    if ( (INVALID_FILE_HANDLE == m_PlaybackUriLicenseHander.m_hUrilicenseFile)
         || (0 == m_PlaybackUriLicenseHander.m_hUrilicenseFile) )
    {
        return FALSE;
    }

    LongLong llSeekLen;
    llSeekLen.Lo = 0;
    llSeekLen.Hi = 0;
    msAPI_PVRFS_FileSeek(m_PlaybackUriLicenseHander.m_hUrilicenseFile, llSeekLen, PVRFS_SEEK_OPTION_FROM_BEGIN);

    BOOL bneedUpdateEvent = FALSE;
    int needUpdateIndex = 0;
    U8 i = 0;
    for (i=0; i<m_PlaybackUriLicenseHander.u8UrilicenseCount; i++)
    {
        if (u32TargetTime == m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)
        {
            bneedUpdateEvent = TRUE;
            needUpdateIndex = i;
            break;
        }
    }

    if (!bneedUpdateEvent)
    {
        return FALSE;
    }

    if (m_PlaybackUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ExpiredTime < u32ExpiredTime)
    {
        m_PlaybackUriLicenseHander.m_UrilicenseInfo[needUpdateIndex].pvrUriLicense.m_u32ExpiredTime = u32ExpiredTime;
    }

    U8* pu8NonCacheBuffer = (U8*)msOS_CacheToNonCache((U32)u8afUriLicenseBuffer);
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, &m_PlaybackUriLicenseHander.u8UrilicenseCount, 1, 0);  // p[0]
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, m_PlaybackUriLicenseHander.m_u8CICAMID, CC_AUTH_ID_SIZE, 1); // p[1]
    _MAPP_CIPVR_VirtualFwrite(pu8NonCacheBuffer, (U8*)m_PlaybackUriLicenseHander.m_UrilicenseInfo, MAX_EVENTINFO_NUM*sizeof(UriLicenseInfo), 1+CC_AUTH_ID_SIZE); // p[9]

    MsOS_FlushMemory();
    if (E_PVR_ENCRYPTION_NONE != MApp_PVR_GetEncryptionType())
    {
        msAPI_PVR_AESDMAEncryptDecrypt((U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer), E_ENCRYPT);
    }
    MsOS_FlushMemory();

    msAPI_CIPVRFS_FileWrite(m_PlaybackUriLicenseHander.m_hUrilicenseFile, (U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer));
    return TRUE;
}

static BOOL _MAPP_CIPVR_UriLicenseMonitor(UriLicenseInfo* urilicenseInfo)
{
    U32 u32Playbacktime = MApp_PVR_GetPlaybackTimeSec();
    U32 u32TotalTime    = MApp_PVR_GetDurationTime();
    enPlaybackState PlaybackState = MApp_Playback_StateMachineGet();

    U8 i;
    U8 curIdx = 0;
    U32 u32CurrentTimeID = 0;
    if (U32_MAX != m_PlaybackUriLicenseHander.m_u32ActiveID)
    {
        if ( (E_PLAYBACK_STATE_PLAYBACKING == PlaybackState)
             || (E_PLAYBACK_STATE_FASTFORWARD == PlaybackState) )
        {
            if ( (u32Playbacktime < u32CurrentTimeID) || (u32Playbacktime > u32TotalTime) )
            {
                PVR_DBG(printf("[UriLicenseMonitor][NG] Cur=%u, Prev=%u\n", u32Playbacktime, u32CurrentTimeID););
                return FALSE;
            }
        }
    }

    for (i=0; i<m_PlaybackUriLicenseHander.u8UrilicenseCount; i++)
    {
        if ( ((i < (m_PlaybackUriLicenseHander.u8UrilicenseCount-1))
              && (u32Playbacktime > m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)
              && (u32Playbacktime < m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime))
             ||
             ((i == m_PlaybackUriLicenseHander.u8UrilicenseCount - 1)
              && (u32Playbacktime > m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)) )
        {
            u32CurrentTimeID = m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime;
            if (m_PlaybackUriLicenseHander.m_u32ActiveID != u32CurrentTimeID)
            {
                m_PlaybackUriLicenseHander.m_u32ActiveID = u32CurrentTimeID;
                m_PlaybackUriLicenseHander.m_bActive = TRUE;
                curIdx = i;
            }
            break;
        }
    }

    if (TRUE == m_PlaybackUriLicenseHander.m_bActive)
    {
        PVR_DBG(printf("[UriLicenseMonitor][OK] Cur=%u, Beg=%u, End=%u \n",
                u32Playbacktime,
                m_PlaybackUriLicenseHander.m_UrilicenseInfo[curIdx].u32BlockBeginTime,
                m_PlaybackUriLicenseHander.m_UrilicenseInfo[curIdx].u32BlockEndTime););
        m_PlaybackUriLicenseHander.m_bActive = FALSE;
        memcpy(urilicenseInfo, &m_PlaybackUriLicenseHander.m_UrilicenseInfo[curIdx], sizeof(UriLicenseInfo));
        return TRUE;
    }
    return FALSE;
}

static BOOL _MAPP_CIPVR_GetCurUriLicense(U32 u32CurrentTime, PvrUriLicense* stPvrUriLicense, U32* u32BlockBeginTime, U32* u32BlockEndTime)
{
    U8 i = 0;
    for (i=0; i<m_PlaybackUriLicenseHander.u8UrilicenseCount; i++)
    {
        if ( ((i < (m_PlaybackUriLicenseHander.u8UrilicenseCount - 1))
              && (u32CurrentTime >= m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)
              && (u32CurrentTime <= m_PlaybackUriLicenseHander.m_UrilicenseInfo[i+1].u32BlockBeginTime))
              ||
              ((i== m_PlaybackUriLicenseHander.u8UrilicenseCount - 1)
              && (u32CurrentTime >= m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)) )
        {
            *u32BlockBeginTime = m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime;
            *u32BlockEndTime = m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime;
            memcpy(stPvrUriLicense, &m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense,sizeof(PvrUriLicense));
            break;
        }
    }
    return TRUE;
}

static BOOL _MAPP_CIPVR_RecordCICardMonitor(void)
{
    if(FALSE == MApp_PVR_IsRecording())
    {
        return FALSE;
    }
#if (ENABLE_CI == 1)
#if (ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL == 1)
#if (ENABLE_CI_PLUS == 1)
#if (ENABLE_CIPLUS_PVR == 1)
    static BOOL bActiveStandbyMode = FALSE;
    if(bActiveStandbyMode != MApp_GetActiveStandbyMode())
    {
        bActiveStandbyMode = MApp_GetActiveStandbyMode();
        if(TRUE == bActiveStandbyMode)
            MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING, NULL, 0);
        else if(TRUE == MApp_PVR_IsPlaybacking())
        {
            U16 u16RecordFileName[FILE_NAME_LENGTH];
            U16 u16PlaybackFileName[FILE_NAME_LENGTH];
            MApp_PVR_GetPlaybackFileName(u16PlaybackFileName);
            MApp_PVR_GetRecordFileName(u16RecordFileName);
            if(u16RecordFileName ==  u16PlaybackFileName)
                MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,EN_CC_PVR_OPERATING_MODE_TIMESHIFT, NULL, 0);
            else
                MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING, NULL, 0);
        }
        else
            MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,EN_CC_PVR_OPERATING_MODE_WATCH_AND_BUFFER, NULL, 0);
    }
#endif
#endif
#endif

    MEMBER_SERVICETYPE bServiceType;
    WORD wProgramPositon;

    wProgramPositon = msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType());
    bServiceType = msAPI_CM_GetCurrentServiceType();

    // CI card is not detected
    EN_CI_VERSION CicamVersion = msAPI_CI_CC_CAM_Mode();
    BOOL bScrambled = msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED);
    if(0 == bScrambled)
    {
        return FALSE;
    }

    if(TRUE == MAPP_CIPVR_IsCopyFreely(bScrambled))
    {
        CicamVersion = EN_CI_VERSION_CI;
    }

    MApp_PVR_SetCicamCheckLevel((U8)CicamVersion);

    if(TRUE == msAPI_CI_CardDetect())
    {
        return FALSE;
    }
    if(MApp_PVR_IsPlaybacking())
    {
        MApp_UiPvr_PlaybackStop();
    }
    MApp_UiPvr_RecordStop();
#endif
    return TRUE;
}

static BOOL _MAPP_CIPVR_RecordCIPinEventMonitor(void)
{
    if ( (FALSE == msAPI_CI_CardDetect())
         || (EN_CC_VERSION_V2 > msAPI_CI_CC_GetCicamCCVersion()) )
    {
        return FALSE;
    }

    CI_CC_PIN_EVENT PinEvent;
    PinEventInfo curPinEventInfo;
    memset(&PinEvent, 0, sizeof(CI_CC_PIN_EVENT));
    memset(&curPinEventInfo, 0, sizeof(PinEventInfo));

    if ( (TRUE == MApp_PVR_IsRecording())
         && (EN_CC_PVR_OPERATING_MODE_RESERVED != m_eOperatingMode)
         && (TRUE == MAPP_CIPVR_CICheckCCPinCapabilities(TRUE, FALSE, FALSE)) )
    {
        if (TRUE == msAPI_CI_CC_PinEventUpdate(&PinEvent))
        {
            U32 u32EventTimeSec = 0;
            U32 u32CurRecordStartTime = 0;
            U32 u32OffsetTimeSec = 0;
            u32EventTimeSec = MApp_MJDUTC2Seconds(PinEvent.au8pin_event_time_utc);
            u32OffsetTimeSec = (U32)MApp_GetTimeZoneOffset(stGenSetting.g_Time.en_Clock_TimeZone);
            u32EventTimeSec += u32OffsetTimeSec;
            u32CurRecordStartTime = MApp_PVR_GetRecordStartSysTime();

            if (u32CurRecordStartTime < u32EventTimeSec)
            {
                /*
                    for scramble service,
                    if service copy protect mode is COPY_NEVER, COPY_NO_MORE, COPY_ONCE, playback this scramble service must with same CI+ CICAM pluged. ==> follow CI+ spec.
                    if service copy protect mode is COPY_FREELY, but with Pin Event    , playback this scramble service must with same CI+ CICAM pluged. ==> follow CI+ spec.
                    if service copy protect mode is COPY_FREELY, without  Pin Event    , playback this scramble service is not necessary with CICAM pluged. ==> follow Telnet spec.
                 */
                MApp_PVR_SetCicamCheckLevel((U8)EN_CI_VERSION_CI_PLUS);
                memcpy(&curPinEventInfo.pvrPinEvent, &PinEvent, sizeof(PinEvent));
                curPinEventInfo.u32BlockBeginTime = u32EventTimeSec - u32CurRecordStartTime;
                return _MAPP_CIPVR_PinEventUpdate(FALSE, curPinEventInfo);
            }
            else
            {
                return FALSE;
            }
        }

        if (TRUE == _MAPP_CIPVR_PinEventMonitor(&curPinEventInfo, FALSE))
        {
            if ( (EN_CC_PVR_OPERATING_MODE_WATCH_AND_BUFFER == m_eOperatingMode)
                 || (EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING == m_eOperatingMode) )//do not avoid mute process in unattended recording
            {
                if (curPinEventInfo.pvrPinEvent.bValid)
                {
                    if (curPinEventInfo.pvrPinEvent.bVideoBlanking)
                    {
                        PVR_DBG(printf("[CI][Record Pin Event] Set Mute \n"));
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_LIVE_PIN_EVENT, ENABLE, NULL, MAIN_WINDOW);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_CIPVR_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                    else
                    {
                        PVR_DBG(printf("[CI][Record Pin Event] Set Unmute \n"));
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_LIVE_PIN_EVENT, DISABLE, NULL, MAIN_WINDOW);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_CIPVR_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
            }
        }
    }
    return TRUE;
}

static BOOL _MAPP_CIPVR_PlaybackCIPinEventMonitor(void)
{
    if ( (FALSE == msAPI_CI_CardDetect())
        || (EN_CC_VERSION_V2 > msAPI_CI_CC_GetCicamCCVersion()) )
    {
        return FALSE;
    }

    CI_CC_PIN_EVENT PinEvent;
    PinEventInfo curPinEventInfo;
    memset(&PinEvent, 0, sizeof(CI_CC_PIN_EVENT));
    memset(&curPinEventInfo, 0, sizeof(PinEventInfo));

    if ( MAPP_CIPVR_PinEventPlaybackingRunning()
         && (TRUE == _MAPP_CIPVR_PinEventMonitor(&curPinEventInfo, TRUE)) )
    {
        if (curPinEventInfo.pvrPinEvent.bValid)
        {
            PVR_DBG(printf("[CI][Playback Pin Event] Set Mute \n"));
            memcpy(&PinEvent, &curPinEventInfo.pvrPinEvent, sizeof(CI_CC_PIN_EVENT));
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_PLAYBACK_PIN_EVENT, ENABLE, NULL, MAIN_WINDOW);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_CIPVR_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            msAPI_CI_CC_SendPinPlayback(&PinEvent);
        }
    }
    return TRUE;
}

static BOOL _MAPP_CIPVR_RecordCIUriLicenseMonitor(void)
{
    MEMBER_SERVICETYPE bServiceType;
    WORD wProgramPositon;

    if (FALSE == msAPI_CI_CardDetect())
    {
        return FALSE;
    }

    if (TRUE == MApp_PVR_IsRecording())
    {
        wProgramPositon = msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType());
        bServiceType = msAPI_CM_GetCurrentServiceType();

        CI_CC_URI_LICENSE stUriLicense;
        UriLicenseInfo stUriLicenseInfo;
        memset(&stUriLicense, 0, sizeof(CI_CC_URI_LICENSE));
        memset(&stUriLicenseInfo, 0, sizeof(UriLicenseInfo));
        U32 u32TimeStamp = MApp_PVR_GetCurRecordTimeInSec();
        if (TRUE == msAPI_CI_CC_GetCicamUriLicenseUpdate(&stUriLicense, TRUE))
        {
            stUriLicenseInfo.pvrUriLicense.m_u16program_number = stUriLicense.m_u16program_number;
            stUriLicenseInfo.pvrUriLicense.m_u8license_status = stUriLicense.m_u8license_status;
            stUriLicenseInfo.pvrUriLicense.m_bLicenseAvailable = stUriLicense.m_bLicenseAvailable;
            stUriLicenseInfo.pvrUriLicense.m_bLicenseValid = stUriLicense.m_bLicenseValid;
            stUriLicenseInfo.pvrUriLicense.m_bUriValid = stUriLicense.m_bUriValid;
            stUriLicenseInfo.pvrUriLicense.m_u8play_count = stUriLicense.m_u8play_count;
            stUriLicenseInfo.pvrUriLicense.m_u16CicamLicenseLength = stUriLicense.m_u16CicamLicenseLength;
            memcpy(stUriLicenseInfo.pvrUriLicense.m_unUriMessage.au8URI_Message, stUriLicense.m_unUriMessage.au8URI_Message, CC_AUTH_URI_SIZE);
            memcpy(stUriLicenseInfo.pvrUriLicense.m_stl_license, stUriLicense.pu8CicamLicense, stUriLicense.m_u16CicamLicenseLength);

            if (FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED))
            {
                UriLicenseInfo stFTAUriLicense;
                stUriLicenseInfo = stFTAUriLicense;
            }

            stUriLicenseInfo.u32BlockBeginTime = u32TimeStamp;
            stUriLicenseInfo.u32BlockEndTime = 0xFFFFFFFF;
            stUriLicenseInfo.pvrUriLicense.m_u32ReceivedTime = MApp_GetLocalSystemTime();
            stUriLicenseInfo.pvrUriLicense.m_u32ExpiredTime = 0;
            if (FALSE == _MAPP_CIPVR_CicamUriLicenseUpdate(stUriLicenseInfo))
            {
                return FALSE;
            }
            return TRUE;
        }
    }
    return FALSE;
}

static BOOL _MAPP_CIPVR_PlaybackCIUriLicenseMonitor(void)
{
    if (FALSE == msAPI_CI_CardDetect())
    {
        return FALSE;
    }

    if (TRUE == MAPP_CIPVR_UriLicensePlaybackingRunning())
    {
        U32 u32TimeStamp;
        UriLicenseInfo stUriLicenseInfo;
        CI_CC_URI_LICENSE stUriLicense;
        memset(&stUriLicense, 0, sizeof(CI_CC_URI_LICENSE));
        memset(&stUriLicenseInfo, 0, sizeof(stUriLicenseInfo));
        if (_MAPP_CIPVR_UriLicenseMonitor(&stUriLicenseInfo))
        {
            u32LicenseEndTime = stUriLicenseInfo.u32BlockEndTime;
            stUriLicense.pu8CicamLicense = (U8*)msAPI_Memory_Allocate(stUriLicenseInfo.pvrUriLicense.m_u16CicamLicenseLength, BUF_ID_200_FOR_CI_LIB);
            stUriLicense.m_bLicenseAvailable = stUriLicenseInfo.pvrUriLicense.m_bLicenseAvailable;
            stUriLicense.m_bLicenseValid = stUriLicenseInfo.pvrUriLicense.m_bLicenseValid;
            stUriLicense.m_bUriValid = stUriLicenseInfo.pvrUriLicense.m_bUriValid;
            stUriLicense.m_u8play_count = stUriLicenseInfo.pvrUriLicense.m_u8play_count;
            stUriLicense.m_u16CicamLicenseLength = stUriLicenseInfo.pvrUriLicense.m_u16CicamLicenseLength;
            stUriLicense.m_u8license_status = stUriLicenseInfo.pvrUriLicense.m_u8license_status;
            stUriLicense.m_u16program_number = stUriLicenseInfo.pvrUriLicense.m_u16program_number;
            memcpy(&stUriLicense.m_unUriMessage, &stUriLicenseInfo.pvrUriLicense.m_unUriMessage, sizeof(CI_CC_URI_MESSAGE));
            memcpy(stUriLicense.pu8CicamLicense, stUriLicenseInfo.pvrUriLicense.m_stl_license, stUriLicenseInfo.pvrUriLicense.m_u16CicamLicenseLength);

            _MAPP_CIPVR_PVRTriggerURICopyProtect(stUriLicense);

            if (TRUE == msAPI_CI_CC_GetUriValue(stUriLicense, EN_URI_TRICK_MODE))
            {
                PVR_DBG(printf("[UriLicenseMonitor] Trick Mode Control, Stop Playback \n"););
                MApp_UiPvr_PlaybackStop();
                MApp_UiPvr_RecordStop();
            }

            //behavior for CI+ v1.3 Test Extensions Procedure v0.04
            //5.1.1.2. Delayed Playback License Exchange Response
            //5.1.1.4. Invalid Recording With record_start_status Errors
            if( (EN_CC_VERSION_V2 <= msAPI_CI_CC_GetCicamCCVersion())
                && (TRUE == stUriLicense.m_bLicenseAvailable) )
            {
                PVR_DBG(printf("[UriLicenseMonitor]Do ExchangePlaybackLicense \n"););
                msAPI_CI_CC_ExchangePlaybackLicense(stUriLicenseInfo.u32BlockBeginTime, &stUriLicense, TRUE);
            }

            msAPI_Memory_Free(stUriLicense.pu8CicamLicense, BUF_ID_200_FOR_CI_LIB);
        }

        if ( (EN_CC_VERSION_V2 <= msAPI_CI_CC_GetCicamCCVersion())
             && (TRUE == msAPI_CI_CC_GetHostUriLicenseUpdate(&u32TimeStamp, &stUriLicense, TRUE)) )
        {
            //behavior for CI+ v1.3 Test Extensions Procedure v0.04
            //5.1.1.2. Delayed Playback License Exchange Response
            //5.1.1.4. Invalid Recording With record_start_status Errors
            if (FALSE == stUriLicense.m_bLicenseValid)
            {
                //behavior for CI+ v1.3 Test Extensions Procedure v0.04
                //5.1.1.2. Delayed Playback License Exchange Response
                //5.1.1.4. Invalid Recording With record_start_status Errors
                PVR_DBG(printf("License Invalid, Stop Playback \n"););
                MApp_UiPvr_PlaybackStop();
                MApp_UiPvr_RecordStop();
            }
            memset(&stUriLicenseInfo, 0, sizeof(stUriLicenseInfo));
            stUriLicenseInfo.pvrUriLicense.m_bLicenseAvailable = stUriLicense.m_bLicenseAvailable;
            stUriLicenseInfo.pvrUriLicense.m_bLicenseValid = stUriLicense.m_bLicenseValid;
            stUriLicenseInfo.pvrUriLicense.m_bUriValid = stUriLicense.m_bUriValid;
            stUriLicenseInfo.pvrUriLicense.m_u8play_count = stUriLicense.m_u8play_count;
            stUriLicenseInfo.pvrUriLicense.m_u16CicamLicenseLength = stUriLicense.m_u16CicamLicenseLength;
            stUriLicenseInfo.pvrUriLicense.m_u16program_number = stUriLicense.m_u16program_number;
            stUriLicenseInfo.pvrUriLicense.m_u8license_status = stUriLicense.m_u8license_status;
            memcpy(stUriLicenseInfo.pvrUriLicense.m_unUriMessage.au8URI_Message, stUriLicense.m_unUriMessage.au8URI_Message,CC_AUTH_URI_SIZE);
            memcpy(stUriLicenseInfo.pvrUriLicense.m_stl_license, stUriLicense.pu8CicamLicense, stUriLicense.m_u16CicamLicenseLength);
            stUriLicenseInfo.u32BlockBeginTime = u32TimeStamp;
            stUriLicenseInfo.u32BlockEndTime = u32LicenseEndTime;
            stUriLicenseInfo.pvrUriLicense.m_u32ReceivedTime = MApp_GetLocalSystemTime();
            stUriLicenseInfo.pvrUriLicense.m_u32ExpiredTime = 0;
            return _MAPP_CIPVR_HostUriLicenseUpdate(stUriLicenseInfo);
        }
    }
    return TRUE;
}

static BOOL _MAPP_CIPVR_RetentionLimitBlockCompute(PvrUriLicense pvrUriLicense, U32 u32SystemTime, U32 u32RecordStartTime, MAPI_U32 u32DurationTime, U32 u32BlockBeginTime, U32 u32BlockEndTime, RETENTION_LIMIT_BLOCK* RLBlock, BOOL bBlockUpdates)
{
    U32 u32RetentionLimitTime = 0;

    CI_CC_URI_LICENSE stUriLicense;
    memset(&stUriLicense, 0, sizeof(CI_CC_URI_LICENSE));
    stUriLicense.m_u8play_count = pvrUriLicense.m_u8play_count;
    stUriLicense.m_u8license_status = pvrUriLicense.m_u8license_status;
    memcpy(&stUriLicense.m_unUriMessage, &pvrUriLicense.m_unUriMessage, sizeof(CI_CC_URI_MESSAGE));

    msAPI_CI_CC_GetRetentionLimitTime(stUriLicense, &u32RetentionLimitTime);
    if (0 == u32RetentionLimitTime)
    {
        return FALSE;
    }
    if ( (TRUE == pvrUriLicense.m_bLicenseAvailable)
         && (TRUE == pvrUriLicense.m_bLicenseValid) )
    {
        /*
            CI+ Spec v1.3  [5.12.1 Playback Session]
                The URI returned from a CICAM license exchange may change the existing recorded License and URI and shall be associated with the content at the same position as the original, displacing the existing License and URI.
                The new URI shall be used immediately for playback.
                The new URI may alter the retention time limit which shall be applied in a similar way to the recording process, taking into consideration the length of the material when viewed with a normal playback time. e.g.
                Consider a 2 hour (120 minute) programme that changes its retention limit from 30 days to 90 minutes. At the instant the URI is changed then the first byte of the recorded material at the URI transition has a new retention time limit of 90 minutes, the last byte of the 120 minute recorded event has a retention time limit of 120+90 or 210 minutes.
                A URI that exists without a License is not re-presented to the CICAM on playback and is not replaced in the recording.
        */
        u32RecordStartTime = pvrUriLicense.m_u32ReceivedTime;
        PVR_TRACE(printf("[RetentionLimitBlockCompute] Update u32RecordStartTime=%u \n", u32RecordStartTime););
    }

    PVR_TRACE(printf("[RetentionLimitBlockCompute] u32RecordStartTime=%u, u32DurationTime=%u, u32BlockBeginTime=%u, u32BlockEndTime=%u, m_u32ExpiredTime=%u, u32RetentionLimitTime=%u \n",
              u32RecordStartTime, u32DurationTime, u32BlockBeginTime, u32BlockEndTime, pvrUriLicense.m_u32ExpiredTime, u32RetentionLimitTime));

    U32 u32RetentionEndTime = u32BlockBeginTime + pvrUriLicense.m_u32ExpiredTime;
    u32BlockEndTime = (u32DurationTime<u32BlockEndTime)? u32DurationTime : u32BlockEndTime;

    PVR_TRACE(printf("[RetentionLimitBlockCompute] u32RetentionEndTime=%u, u32BlockEndTime=%u \n",
              u32RetentionEndTime, u32BlockEndTime););

    if (0xFFFFFFFF != u32RetentionLimitTime)
    {
        U32 u32RetentionBaseTime = u32RecordStartTime + pvrUriLicense.m_u32ExpiredTime + u32BlockBeginTime + u32RetentionLimitTime;
        PVR_TRACE(printf("[RetentionLimitBlockCompute] u32SystemTime=%u, u32RetentionBaseTime(Start+Expired+Begin+Retention)=%u \n",
                u32SystemTime, u32RetentionBaseTime));

        if (u32SystemTime > u32RetentionBaseTime)
        {
            u32RetentionEndTime += u32SystemTime - u32RetentionBaseTime;
            u32RetentionEndTime = (u32BlockEndTime > u32RetentionEndTime) ? u32RetentionEndTime : u32BlockEndTime;
        }
        else if (FALSE == bBlockUpdates)
        {
            if (u32RetentionEndTime == u32BlockBeginTime)
            {
                PVR_TRACE(printf("[RetentionLimitBlockCompute] Not Expired \n"));
                return FALSE;
            }
        }
    }
    else
    {
        u32RetentionEndTime = u32BlockEndTime;
        PVR_TRACE(printf("[RetentionLimitBlockCompute] Error#3 \n"));
    }

    RETENTION_LIMIT_BLOCK tmpRLBlock;
    if (TRUE == pvrUriLicense.m_bLicenseAvailable)
    {
        tmpRLBlock.bLicense = TRUE;
    }
    else
    {
        tmpRLBlock.bLicense = FALSE;
    }
    tmpRLBlock.u32Begin = u32BlockBeginTime;
    tmpRLBlock.u32End   = u32BlockEndTime;
    tmpRLBlock.u32Cur   = u32RetentionEndTime;
    tmpRLBlock.u8Count  = pvrUriLicense.m_u8play_count;
    memcpy(RLBlock, &tmpRLBlock, sizeof(RETENTION_LIMIT_BLOCK));
    PVR_TRACE(printf("[RetentionLimitBlockCompute] RLBlock(%u, %u, %u, %u) \n",
              tmpRLBlock.u32Begin, tmpRLBlock.u32End, tmpRLBlock.u32Cur, tmpRLBlock.u8Count));
    return TRUE;
}

static void _MAPP_CIPVR_DisplayUriLicenseRegion(void)
{
    URI_LICENSE_REGION_INFO stUriLicenseRegionInfo;
    memset(&stUriLicenseRegionInfo, 0, sizeof(stUriLicenseRegionInfo));
    MAPP_CIPVR_GetUriLicenseRegionInfo(&stUriLicenseRegionInfo);

    U8 i = 0;
    for (i=0; i<stUriLicenseRegionInfo.u8UriLicenseCount; i++)
    {
        if (TRUE == stUriLicenseRegionInfo.m_RetentionLimitBlock[i].bLicense)
        {
            PVR_DBG(printf("LicenseInfo[%u](Count:%u, Beg:%u, Cur:%u, End:%u) \n",
                          i,
                          stUriLicenseRegionInfo.m_RetentionLimitBlock[i].u8Count,
                          stUriLicenseRegionInfo.m_RetentionLimitBlock[i].u32Begin,
                          stUriLicenseRegionInfo.m_RetentionLimitBlock[i].u32Cur,
                          stUriLicenseRegionInfo.m_RetentionLimitBlock[i].u32End
                          );
                   );
        }
        else
        {
            PVR_DBG(printf("UriInfo[%u](Beg:%u, Cur:%u, End:%u) \n",
                          i,
                          stUriLicenseRegionInfo.m_RetentionLimitBlock[i].u32Begin,
                          stUriLicenseRegionInfo.m_RetentionLimitBlock[i].u32Cur,
                          stUriLicenseRegionInfo.m_RetentionLimitBlock[i].u32End
                          );
                   );
        }
    }
}

BOOL MAPP_CIPVR_CISendCCPin(BOOL bMmiReq, U16 PinCode)
{
    U8 u8CiPinCode[4];
    sprintf((char*)u8CiPinCode, "%d", PinCode);

    if(FALSE == msAPI_CI_CardDetect())
    {
        return FALSE;
    }

    if (bMmiReq &&
            MAPP_CIPVR_CICheckCCPinCapabilities(false, false, true))
    {
        return msAPI_CI_CC_ReqPinMMI(u8CiPinCode, 4);
    }
    else if ((!bMmiReq) &&(MAPP_CIPVR_CICheckCCPinCapabilities(true, false, true)))
    {
        return msAPI_CI_CC_SendPinCmd(u8CiPinCode, 4);
    }
    return FALSE;
}

BOOL MAPP_CIPVR_CICheckPinEventStatus(BOOL *bPinCodeCorrect, U16 *u16CachedPinCode)
{
    if( (FALSE == msAPI_CI_CardDetect())
        || (EN_CC_VERSION_V2 > msAPI_CI_CC_GetCicamCCVersion()))
    {
        return FALSE;
    }
    if(FALSE == MAPP_CIPVR_CICheckCCPinCapabilities(true, false, false))
    {
        return FALSE;
    }

    BOOL bTimeout = FALSE;
#if WATCH_DOG
    MDrv_Sys_DisableWatchDog();
#endif
    while(FALSE == bTimeout)
    {
        msAPI_CI_MAINLOOP();
        EN_CC_PIN_CODE_STATUS ePinCodeStatus = msAPI_CI_CC_GetPINcodeStatus(TRUE, &bTimeout);
        switch (ePinCodeStatus)
        {
            case EN_CC_PIN_CODE_STATUS_PIN_CODE_CORRECT:
            {
            #if WATCH_DOG
                MDrv_Sys_EnableWatchDog();
            #endif
                *bPinCodeCorrect = TRUE;
                *u16CachedPinCode = msAPI_CI_CC_GetPINcodeCache();
                PVR_DBG(printf("<<MAPP_CIPVR_CICheckPinEventStatus EN_CC_PIN_CODE_STATUS_PIN_CODE_CORRECT %d>>..\n",*u16CachedPinCode));
                return TRUE;
            }
            break;
            case EN_CC_PIN_CODE_STATUS_BAD_PIN_CODE:
            {
            #if WATCH_DOG
                MDrv_Sys_EnableWatchDog();
            #endif
                *bPinCodeCorrect = FALSE;
                PVR_DBG(printf("<<MAPP_CIPVR_CICheckPinEventStatus EN_CC_PIN_CODE_STATUS_BAD_PIN_CODE>>..\n"));
                return TRUE;
            }
            break;
            case EN_CC_PIN_CODE_STATUS_UNKNOW:
                break;
            default:
            #if WATCH_DOG
                MDrv_Sys_EnableWatchDog();
            #endif
                *bPinCodeCorrect = FALSE;
                PVR_DBG(printf("<<MAPP_CIPVR_CICheckPinEventStatus Invalid Case in Pin Cmd Reply %d>>..\n",ePinCodeStatus));
                return TRUE;
        }
    }
#if WATCH_DOG
    MDrv_Sys_EnableWatchDog();
#endif
    PVR_DBG(printf("[CI+][CC]getCCPINcodeStatus already timeout.\n"));
    return FALSE;
}

BOOL MAPP_CIPVR_IsCopyFreely(BOOL bIsScramble)
{
#if (ENABLE_CI_PLUS == 1)
    U8 u8URI_DOT, u8URI_RCT, u8URI_EMI, u8URI_APS, u8URI_ICT, u8URI_RL;
    u8URI_DOT = 0;
    u8URI_RCT = 0;
    u8URI_EMI = 0;
    u8URI_APS = 0;
    u8URI_ICT = 0;
    u8URI_RL = 0;

    CI_CC_URI_LICENSE stUriLicense;
    msAPI_CI_CC_GetCicamUriLicenseUpdate(&stUriLicense, FALSE);
    msAPI_CI_CC_UriMappingConvert(bIsScramble, TRUE, FALSE,
                                  stUriLicense, &u8URI_DOT, &u8URI_RCT, &u8URI_EMI, &u8URI_APS, &u8URI_ICT, &u8URI_RL);

    return (CC_URI_EMI_COPY_FREELY == u8URI_EMI);
#else
    //CI plus not support, all of the content be treat as copy freely
    return TRUE;
#endif
}

BOOL MAPP_CIPVR_CICheckCCPinCapabilities(BOOL bPVRprocess, BOOL bScrambleServiceCheck, BOOL bSendCCPin)
{
    EN_CC_CICAM_PIN_CAPABILITIES eCicamPinCapability;
    U8 u8CicamRating;
    MEMBER_SERVICETYPE bServiceType;
    WORD wProgramPositon;

    if( (FALSE == msAPI_CI_CardDetect())
        || (EN_CC_VERSION_V2 > msAPI_CI_CC_GetCicamCCVersion()))
    {
        return FALSE;
    }

    eCicamPinCapability = msAPI_CI_CC_GetCicamPinCapability();
    u8CicamRating = msAPI_CI_CC_GetCicamRating();
    wProgramPositon = msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType());
    bServiceType = msAPI_CM_GetCurrentServiceType();
    if (bPVRprocess)
    {
        switch (eCicamPinCapability)
        {
            case EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY_CACHED:
            case EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN_CACHED:
            {
                if (TRUE == bScrambleServiceCheck)//check current is scramble service or not
                {
                    return (TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED));
                }
                else//by pass checking
                {
                    return TRUE;
                }
            }
            default:
                break;
        }
    }
    else
    {
        switch (eCicamPinCapability)
        {
            case EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY:
            case EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY_CACHED:
            {
                if(bSendCCPin)//all do not send CC MMI
                {
                    return FALSE;
                }
                if(FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED))
                {
                    return FALSE;
                }
                else//mute by host in below condition
                {
                    return !(stGenSetting.g_BlockSysSetting.u8ParentalControl<u8CicamRating);
                }
            }
            case EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN:
            case EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN_CACHED:
            {
                if(TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED))
                {
                    if(bSendCCPin)//do not send CC MMI in below condition
                    {
                        return (stGenSetting.g_BlockSysSetting.u8ParentalControl<u8CicamRating);
                    }
                    else
                    {
                        return TRUE;
                    }
                }
                else
                {
                    return TRUE;
                }
            }
            default:
                break;
        }
    }
    return FALSE;
}

BOOL MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_PVR_DATATYPE_ID eOperatingType, EN_CC_PVR_OPERATING_MODE eOperatingMode, U8* pu8PinCode, U16 u16PinCodeLen)
{
    MEMBER_SERVICETYPE bServiceType;
    WORD wProgramPositon;

    wProgramPositon = msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType());
    bServiceType = msAPI_CM_GetCurrentServiceType();

    if( (FALSE == msAPI_CI_CardDetect())
        || (EN_CC_VERSION_V2 > msAPI_CI_CC_GetCicamCCVersion()))
    {
        PVR_DBG(printf("Cam CC Version(%u) < V2 \n", msAPI_CI_CC_GetCicamCCVersion()));
        return FALSE;
    }

    switch (eOperatingType)
    {
        case EN_CC_DATATYPE_ID_RECORD_START:
        {
            if(FALSE == MAPP_CIPVR_CICheckCCPinCapabilities(true, false, false))
            {
                pu8PinCode = NULL;
                u16PinCodeLen = 0;
            }
            msAPI_CI_CC_SendRecordStart(eOperatingMode, msAPI_CM_GetService_ID(bServiceType,wProgramPositon), pu8PinCode, u16PinCodeLen);
            m_eOperatingMode = eOperatingMode;
            m_eOperatingType = eOperatingType;
            return TRUE;
        }
        case EN_CC_DATATYPE_ID_MODE_CHANGE:
        {
            if(EN_CC_PVR_OPERATING_MODE_RESERVED == m_eOperatingMode)
            {
                return MAPI_FALSE;
            }
            if(eOperatingMode == m_eOperatingMode)
            {
                return MAPI_FALSE;
            }
            msAPI_CI_CC_ChangeRecordOperatingMode(eOperatingMode, msAPI_CM_GetService_ID(bServiceType,wProgramPositon));
            m_eOperatingMode = eOperatingMode;
            m_eOperatingType = eOperatingType;
            return TRUE;
        }
        case EN_CC_DATATYPE_ID_RECORD_STOP:
        {
            if(EN_CC_PVR_OPERATING_MODE_RESERVED == m_eOperatingMode)
            {
                return MAPI_FALSE;
            }
            msAPI_CI_CC_SendRecordStop(msAPI_CM_GetService_ID(bServiceType,wProgramPositon));
            m_eOperatingMode = EN_CC_PVR_OPERATING_MODE_RESERVED;
            m_eOperatingType = eOperatingType;
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_LIVE_PIN_EVENT, DISABLE, NULL, MAIN_WINDOW);
            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_CIPVR_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            return TRUE;
        }
        default:
            ASSERT(0);
            break;
    }
    return FALSE;
}

void MAPP_CIPVR_PVRReTriggerURICopyProtect(void)
{
    msAPI_CI_CC_Retrigger_URI();
}

enPvrApiStatus MAPP_CIPVR_CIPlusPVRHandling(EN_PVR_PATH_TYPE enPVRPath, BOOL bIsTimeshift,U16 u16CiPinCode)
{
#if (ENABLE_CI_PLUS == 1)
    if (PVR_PATH_RECORD == enPVRPath)
    {
        if (msAPI_CI_CardDetect())
        {
            if (EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode())
            {
                if (msAPI_CI_CC_RecordingAcceptable(TRUE)) //CA_PVR: Copy No More can't PVR
                {
#if (ENABLE_CIPLUS_PVR == 1)
                    BOOL bCICheckOperatingModeStatus = FALSE;
                    EN_CC_PVR_OPERATING_MODE eOperatingMode = EN_CC_PVR_OPERATING_MODE_RESERVED;
                    if (TRUE == bIsTimeshift)
                        eOperatingMode = EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING;
                    else
                        eOperatingMode = EN_CC_PVR_OPERATING_MODE_WATCH_AND_BUFFER;
#if (ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL == 1)
                    if( TRUE == MApp_GetActiveStandbyMode())
                        eOperatingMode = EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING;
#endif
                    if (0xFFFF != u16CiPinCode)
                    {
                        U8 u8CiPinCode[4];
                        sprintf((char*)u8CiPinCode, "%d", u16CiPinCode);
                        bCICheckOperatingModeStatus = MAPP_CIPVR_PVRCIPlusOperatingMode( EN_CC_DATATYPE_ID_RECORD_START,
                                                      eOperatingMode,
                                                      u8CiPinCode,
                                                      4);
                        PVR_DBG(printf("[PVRCIPlusOperatingMode][Have PinCode](%d, %d, %d, %d)\n", eOperatingMode, bCICheckOperatingModeStatus, u8CiPinCode[0], u8CiPinCode[1]));
                    }
                    else
                    {
                        bCICheckOperatingModeStatus = MAPP_CIPVR_PVRCIPlusOperatingMode( EN_CC_DATATYPE_ID_RECORD_START,
                                                      eOperatingMode, NULL, 0);
                        PVR_DBG(printf("[PVRCIPlusOperatingMode2][Don't Have PinCode](%d, %d)\n", eOperatingMode, bCICheckOperatingModeStatus));
                    }

                    if ( (FALSE == bCICheckOperatingModeStatus)
                         || (TRUE == _MAPP_CIPVR_CICheckOperatingModeStatus(CI_OPERATORING_MAX_TIME)) )
                    {
                        return E_PVR_API_STATUS_SUCCESS_CIPLUS_COPY_PROTECTION;
                    }
                    else
                    {
                        PVR_DBG(printf("ERROR_CIPLUS_COPY_PROTECTION#1\n"));
                        return E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                    }
#endif
                }
                else
                {
                    PVR_DBG(printf("[ERROR] Recording Unacceptable\n"));
                    return E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                }
            }
        }
        else
        {
            ///for some nonstandard TS, it need check scramble bit directly for determine the TS is scrambled or not
            BOOL bScrambled = FALSE;
            MEMBER_SERVICETYPE bServiceType;
            WORD wProgramPositon;
            wProgramPositon = msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType());
            bServiceType = msAPI_CM_GetCurrentServiceType();
            bScrambled = msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED);

            if (FALSE == bScrambled)
            {
                return E_PVR_API_STATUS_OK;
            }
            return E_PVR_API_STATUS_ERROR_CIPLUS_UNPLUGIN;
        }
    }
    else if(PVR_PATH_PLAYBACK == enPVRPath)
    {
        if(msAPI_CI_CardDetect())
        {
            if(EN_CI_VERSION_CI_PLUS ==msAPI_CI_CC_CAM_Mode())
            {
                //check by secured pattern by MAPP_CIPVR_PlaybackCiSecuredPatternCheck
            }
            else
            {
                PVR_DBG(printf("ERROR_CIPLUS_COPY_PROTECTION#4\n"));
                return E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
            }
        }
        else
        {
            PVR_DBG(printf("ERROR_CIPLUS_COPY_PROTECTION#5\n"));
            return E_PVR_API_STATUS_ERROR_CIPLUS_UNPLUGIN;
        }
    }
    else
    {
        return E_PVR_API_STATUS_ERROR_CIPLUS_UNSUPPORT;
    }
#endif
    return E_PVR_API_STATUS_OK;
}

BOOL MAPP_CIPVR_CIPVRActionMonitor()
{
    MEMBER_SERVICETYPE bServiceType;
    WORD wProgramPositon;
    BOOL bScrambled = FALSE;
    wProgramPositon = msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType());
    bServiceType = msAPI_CM_GetCurrentServiceType();

    if (TRUE == MApp_PVR_IsRecording())
    {
        bScrambled = msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED);
        if (FALSE == bScrambled)
        {
            return FALSE;
        }

        _MAPP_CIPVR_RecordCICardMonitor();
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        if (msAPI_Timer_DiffTimeFromNow(u3RecordIntervalTime) <= CIPVR_MONITOR_INTERVAL_TIME)
        {
            return FALSE;
        }
        else
        {
            u3RecordIntervalTime = msAPI_Timer_GetTime0();
        }

        _MAPP_CIPVR_RecordCIPinEventMonitor();
        _MAPP_CIPVR_RecordCIUriLicenseMonitor();
#endif
    }

    if (TRUE == MApp_PVR_IsPlaybacking())
    {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        if (msAPI_Timer_DiffTimeFromNow(u3PlaybackIntervalTime) <= CIPVR_MONITOR_INTERVAL_TIME)
        {
            return FALSE;
        }
        else
        {
            u3PlaybackIntervalTime = msAPI_Timer_GetTime0();
        }

        _MAPP_CIPVR_PlaybackCIPinEventMonitor();
        _MAPP_CIPVR_PlaybackCIUriLicenseMonitor();
#endif
    }
    return TRUE;
}

BOOL MAPP_CIPVR_RetentionLimitMonitor(U32 u32CurrentTime, U32* u32JumpTime)
{
    if (FALSE == msAPI_CI_CardDetect())
    {
        return FALSE;
    }

    if (INVALID_FILE_HANDLE == m_PlaybackUriLicenseHander.m_hUrilicenseFile)
    {
        return FALSE;
    }

    U32 u32SystemTime = MApp_GetLocalSystemTime();
    U32 u32RecordStartTime = MApp_PVR_GetRecordStartSysTime();
    U32 u32DurationTime = MApp_PVR_GetDurationTime();

    PvrUriLicense stPvrUriLicense;
    U32 u32BlockBeginTime = 0;
    U32 u32BlockEndTime = 0;
    // Get Current RL Time Scope
    _MAPP_CIPVR_GetCurUriLicense(u32CurrentTime, &stPvrUriLicense, &u32BlockBeginTime, &u32BlockEndTime);
    PVR_TRACE(printf("[RetentionLimitMonitor]Curret Region(%u, %u) \n", u32BlockBeginTime, u32BlockEndTime));

    // Compute Current RL Block Time Range
    RETENTION_LIMIT_BLOCK RLBlock;
    if (FALSE == _MAPP_CIPVR_RetentionLimitBlockCompute(stPvrUriLicense, u32SystemTime,
                 u32RecordStartTime,
                 u32DurationTime,
                 u32BlockBeginTime,
                 u32BlockEndTime,
                 &RLBlock,
                 FALSE))
    {
        return FALSE;
    }

    //If the license_status is invalid, do not update the expired time
    if(!((TRUE == stPvrUriLicense.m_bLicenseAvailable) && (FALSE == stPvrUriLicense.m_bLicenseValid)
        && (EN_CC_PVR_LICENSE_STATUS_OK != stPvrUriLicense.m_u8license_status)))
    {
        PVR_TRACE(printf("[RetentionLimitMonitor] Save ExpiredTime=%u \n", RLBlock.u32Cur - RLBlock.u32Begin));
        _MAPP_CIPVR_UriLicenseUpdate(u32BlockBeginTime,RLBlock.u32Cur-RLBlock.u32Begin);
    }

    // Do not active in non-block range
    if ( (u32CurrentTime >= RLBlock.u32Cur) || (u32CurrentTime < RLBlock.u32Begin) )
    {
        PVR_TRACE(printf("[RetentionLimitMonitor] u32CurrentTime=%d, Block.Cur=%d, Block.Beg=%d \n",u32CurrentTime, RLBlock.u32Cur, RLBlock.u32Begin));
        return FALSE;
    }

    if (!MApp_PVR_IsFastBackwardPlaybacking())
    {
        *u32JumpTime = RLBlock.u32Cur + PVR_INVISIBLE_SKIP_CAP;
        if (u32DurationTime < *u32JumpTime)
        {
            *u32JumpTime = u32DurationTime;
        }
        PVR_TRACE(printf("[RetentionLimitMonitor][Forward] Jump To RLBlock.u32Cur \n"););
    }
    else
    {
        if (RLBlock.u32Begin > PVR_INVISIBLE_SKIP_CAP)
        {
            *u32JumpTime = RLBlock.u32Begin - PVR_INVISIBLE_SKIP_CAP;
        }
        else
        {
            *u32JumpTime = RLBlock.u32Begin;
        }
        PVR_TRACE(printf("[RetentionLimitMonitor][Backward] Jump To RLBlock.u32Begin \n"););
    }
    PVR_TRACE(printf("[RetentionLimitMonitor] CurrTime=%u, JumpTime=%u \n", u32CurrentTime, *u32JumpTime));
    if(u32CurrentTime != *u32JumpTime)
    {
        u32CurrentTime = *u32JumpTime;
        MAPP_CIPVR_RetentionLimitMonitor(u32CurrentTime, u32JumpTime);
        return TRUE;
    }

    return FALSE;
}

BOOL MAPP_CIPVR_CIPVRFS_RecordFileCreate(U16* pu16FileName)
{
    memset(&m_RecordPinEventHander,0,sizeof(PinEventHander));
    memset(&m_RecordUriLicenseHander,0,sizeof(UriLicenseHander));
    m_RecordPinEventHander.m_bActive = FALSE;
    m_RecordPinEventHander.m_u32ActiveID = U32_MAX;
    m_RecordPinEventHander.m_hPineventFile = INVALID_FILE_HANDLE;
    m_RecordUriLicenseHander.m_bActive = FALSE;
    m_RecordUriLicenseHander.m_u32ActiveID = U32_MAX;
    m_RecordUriLicenseHander.m_hUrilicenseFile = INVALID_FILE_HANDLE;
    u3RecordIntervalTime = msAPI_Timer_GetTime0();;

    msAPI_CIPVRFS_FileCreate(pu16FileName, &m_RecordPinEventHander.m_hPineventFile, &m_RecordUriLicenseHander.m_hUrilicenseFile);
    return TRUE;
}

BOOL MAPP_CIPVR_CIPVRFS_PlaybackFileOpen(U16* pu16FileName, EN_PVRFS_OPEN_MODE mode)
{
    memset(&m_PlaybackPinEventHander,0,sizeof(PinEventHander));
    memset(&m_PlaybackUriLicenseHander,0,sizeof(UriLicenseHander));
    m_PlaybackPinEventHander.m_bActive = FALSE;
    m_PlaybackPinEventHander.m_u32ActiveID = U32_MAX;
    m_PlaybackPinEventHander.m_hPineventFile = INVALID_FILE_HANDLE;
    m_PlaybackUriLicenseHander.m_bActive = FALSE;
    m_PlaybackUriLicenseHander.m_u32ActiveID = U32_MAX;
    m_PlaybackUriLicenseHander.m_hUrilicenseFile = INVALID_FILE_HANDLE;
    BOOL bret = FALSE;
    bret = msAPI_CIPVRFS_FileOpen(pu16FileName, mode, &m_PlaybackPinEventHander.m_hPineventFile, &m_PlaybackUriLicenseHander.m_hUrilicenseFile);
    return bret;
}

BOOL MAPP_CIPVR_CIPVRFS_PlaybackFileRead(enPvrEncryptType enEncryptionType)
{
    if ( (m_PlaybackPinEventHander.m_hPineventFile == INVALID_FILE_HANDLE)
         || (m_PlaybackUriLicenseHander.m_hUrilicenseFile == INVALID_FILE_HANDLE) )
    {
        return FALSE;
    }

    U8* pu8NonCacheBuffer = NULL;

    //////////////////////////////////pin event///////////////////////////////////////////
    pu8NonCacheBuffer = (U8*)msOS_CacheToNonCache((U32)u8afPineventBuffer);
    msAPI_PVRFS_FileRead(m_PlaybackPinEventHander.m_hPineventFile, (U32)pu8NonCacheBuffer, sizeof(u8afPineventBuffer));

    MsOS_FlushMemory();
    if (E_PVR_ENCRYPTION_NONE != enEncryptionType)
    {
        msAPI_PVR_AESDMAEncryptDecrypt((U32)pu8NonCacheBuffer, sizeof(u8afPineventBuffer), E_DECRYPT);
    }
    MsOS_FlushMemory();

    _MAPP_CIPVR_VirtualFread(&m_PlaybackPinEventHander.u8PinEventCount, pu8NonCacheBuffer, 1, 0);
    _MAPP_CIPVR_VirtualFread((U8*)m_PlaybackPinEventHander.m_PinEventInfo, pu8NonCacheBuffer, MAX_EVENTINFO_NUM*sizeof(PinEventInfo), 1);

    ///////////////////////////////////uri license/////////////////////////////////////////
    pu8NonCacheBuffer = (U8*)msOS_CacheToNonCache((U32)u8afUriLicenseBuffer);
    msAPI_PVRFS_FileRead(m_PlaybackUriLicenseHander.m_hUrilicenseFile, (U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer));

    MsOS_FlushMemory();
    if (E_PVR_ENCRYPTION_NONE != enEncryptionType)
    {
        msAPI_PVR_AESDMAEncryptDecrypt((U32)pu8NonCacheBuffer, sizeof(u8afUriLicenseBuffer), E_DECRYPT);
    }
    MsOS_FlushMemory();

    _MAPP_CIPVR_VirtualFread(&m_PlaybackUriLicenseHander.u8UrilicenseCount, pu8NonCacheBuffer, 1, 0);
    _MAPP_CIPVR_VirtualFread(m_PlaybackUriLicenseHander.m_u8CICAMID, pu8NonCacheBuffer, CC_AUTH_ID_SIZE, 1);
    _MAPP_CIPVR_VirtualFread((U8*)m_PlaybackUriLicenseHander.m_UrilicenseInfo, pu8NonCacheBuffer, MAX_EVENTINFO_NUM*sizeof(UriLicenseInfo), 1+CC_AUTH_ID_SIZE);

    U8 u8Index = m_PlaybackUriLicenseHander.u8UrilicenseCount;
    if (0xFFFFFFFF == m_PlaybackUriLicenseHander.m_UrilicenseInfo[u8Index - 1].u32BlockEndTime)
    {
        m_PlaybackUriLicenseHander.m_UrilicenseInfo[u8Index - 1].u32BlockEndTime = MApp_PVR_GetDurationTime();
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    u32LicenseEndTime = 0;
    u3PlaybackIntervalTime = msAPI_Timer_GetTime0();
    _MAPP_CIPVR_DisplayUriLicenseRegion();

    return TRUE;
}

BOOL MAPP_CIPVR_CIPVRFS_RecordFileClose(void)
{
    BOOL ret = FALSE;
    ret = msAPI_CIPVRFS_FileClose(m_RecordPinEventHander.m_hPineventFile, m_RecordUriLicenseHander.m_hUrilicenseFile);
    m_RecordPinEventHander.m_hPineventFile = INVALID_FILE_HANDLE;
    m_RecordUriLicenseHander.m_hUrilicenseFile = INVALID_FILE_HANDLE;
    u32LicenseEndTime = 0;
    u3RecordIntervalTime = 0;
    return ret;
}

BOOL MAPP_CIPVR_CIPVRFS_PlaybackFileClose(void)
{
    BOOL ret = FALSE;
    ret = msAPI_CIPVRFS_FileClose(m_PlaybackPinEventHander.m_hPineventFile, m_PlaybackUriLicenseHander.m_hUrilicenseFile);
    m_PlaybackPinEventHander.m_hPineventFile = INVALID_FILE_HANDLE;
    m_PlaybackUriLicenseHander.m_hUrilicenseFile = INVALID_FILE_HANDLE;
    u3PlaybackIntervalTime = 0;
    return ret;
}

BOOL MAPP_CIPVR_SetMuteFlag(BOOL bMute, E_SCREEN_MUTE_STATUS enFlag)
{
    if (bMute)
    {
        msAPI_Scaler_SetScreenMute(enFlag, ENABLE, NULL, MAIN_WINDOW);
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_CIPVR_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    else
    {
        msAPI_Scaler_SetScreenMute(enFlag, DISABLE, NULL, MAIN_WINDOW);
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_CIPVR_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    return TRUE;
}

BOOL MAPP_CIPVR_PinEventPlaybackingRunning(void)
{
    if (INVALID_FILE_HANDLE == m_PlaybackPinEventHander.m_hPineventFile)
    {
        return FALSE;
    }

    if (0 == m_PlaybackPinEventHander.u8PinEventCount)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL MAPP_CIPVR_UriLicensePlaybackingRunning(void)
{
    if (INVALID_FILE_HANDLE == m_PlaybackUriLicenseHander.m_hUrilicenseFile)
    {
        return FALSE;
    }

    if (0 == m_PlaybackUriLicenseHander.u8UrilicenseCount)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL MAPP_CIPVR_PlaybackCiSecuredPatternCheck(U8* u8aCICAMID)
{
    // CI+1.3 Default: 7E FC BA 6E 96 44 BC BB
    PVR_DBG(printf("[MAPP_CIPVR_PlaybackCiSecuredPatternCheck] CICAM ID=(%x %x %x %x %x %x %x %x), SAVE ID=(%x %x %x %x %x %x %x %x) \n",
                      u8aCICAMID[0], u8aCICAMID[1], u8aCICAMID[2], u8aCICAMID[3], u8aCICAMID[4], u8aCICAMID[5], u8aCICAMID[6],  u8aCICAMID[7],
                      m_PlaybackUriLicenseHander.m_u8CICAMID[0],m_PlaybackUriLicenseHander.m_u8CICAMID[1],m_PlaybackUriLicenseHander.m_u8CICAMID[2],m_PlaybackUriLicenseHander.m_u8CICAMID[3],
                      m_PlaybackUriLicenseHander.m_u8CICAMID[4],m_PlaybackUriLicenseHander.m_u8CICAMID[5],m_PlaybackUriLicenseHander.m_u8CICAMID[6],m_PlaybackUriLicenseHander.m_u8CICAMID[7]);
    );

    if (0 == memcmp(u8aCICAMID, &m_PlaybackUriLicenseHander.m_u8CICAMID, CC_AUTH_ID_SIZE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL MAPP_CIPVR_RecordStartEventUpdate(U8* u8aCICAMID)
{
    // Pin Evnet
    PinEventInfo stPinEventInfo;
    memset(&stPinEventInfo, 0, sizeof(PinEventInfo));
    stPinEventInfo.u32BlockBeginTime = 0;
    _MAPP_CIPVR_PinEventUpdate(TRUE, stPinEventInfo);

    // UriLicense
    memcpy(m_RecordUriLicenseHander.m_u8CICAMID, u8aCICAMID, CC_AUTH_ID_SIZE);
    return TRUE;
}

BOOL MAPP_CIPVR_GetUriLicenseRegionInfo(URI_LICENSE_REGION_INFO *stUriLicenseRegionInfo)
{
    if( (INVALID_FILE_HANDLE == m_PlaybackUriLicenseHander.m_hUrilicenseFile)
        || (0 == m_PlaybackUriLicenseHander.m_hUrilicenseFile) )
    {
        return FALSE;
    }

    U8 i = 0;
    U8 j = 0;
    U32 u32SystemTime = MApp_GetLocalSystemTime();
    U32 u32RecordStartTime = MApp_PVR_GetRecordStartSysTime();
    U32 u32DurationTime = MApp_PVR_GetDurationTime();
    U32 u32PlaybackTime = MApp_Playback_GetPlaybackTimeSec();
    RETENTION_LIMIT_BLOCK RLBlock;

    for (i = 0; i<m_PlaybackUriLicenseHander.u8UrilicenseCount; i++)
    {
        if ( (u32PlaybackTime >= m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)
             && (u32PlaybackTime < m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime) )
        {
            stUriLicenseRegionInfo->u8Index = i;
        }

        if (_MAPP_CIPVR_RetentionLimitBlockCompute(
              m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense,
              u32SystemTime,
              u32RecordStartTime,
              u32DurationTime,
              m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime,
              m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime,
              &RLBlock,
              TRUE))
        {
            memcpy(&(stUriLicenseRegionInfo->m_RetentionLimitBlock[j]), &RLBlock, sizeof(RETENTION_LIMIT_BLOCK));

            if (TRUE == stUriLicenseRegionInfo->m_RetentionLimitBlock[j].bLicense)
            {
                PVR_TRACE(printf("RL: LicenseInfo[%u-%u](Count:%u, Beg:%u, Cur:%u, End:%u) \n",
                              i,
                              j,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u8Count,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Begin,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Cur,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32End
                              );
                       );
            }
            else
            {
                PVR_TRACE(printf("RL: UriInfo[%u-%u](Beg:%u, Cur:%u, End:%u) \n",
                              i,
                              j,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Begin,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Cur,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32End
                              );
                       );
            }
            j++;

        }
        else
        {
            if (TRUE == m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_bLicenseAvailable)
            {
                stUriLicenseRegionInfo->m_RetentionLimitBlock[j].bLicense = TRUE;
                stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u8Count = m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].pvrUriLicense.m_u8play_count;
                stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Begin = m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime;
                stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Cur = m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime;
                stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32End = m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime;
                PVR_TRACE(printf("LicenseInfo[%u-%u](Count:%u, Beg:%u, Cur:%u, End:%u) \n",
                              i,
                              j,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u8Count,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Begin,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32Cur,
                              stUriLicenseRegionInfo->m_RetentionLimitBlock[j].u32End
                              );
                       );
                j++;
            }
        }
    }
    stUriLicenseRegionInfo->u8UriLicenseCount = j;
    return TRUE;
}

BOOL MAPP_CIPVR_RetentionLimitBlockUpdates(RETENTION_LIMIT_BLOCK *RLBlockInfo)
{
    if( (INVALID_FILE_HANDLE == m_PlaybackUriLicenseHander.m_hUrilicenseFile) ||
        (0 == m_PlaybackUriLicenseHander.m_hUrilicenseFile) )
    {
        return FALSE;
    }

    U8 i = 0;
    U8 u8Index = 0;
    U32 u32PlaybackTime = MApp_Playback_GetPlaybackTimeSec();
    U32 u32DurationTime = MApp_PVR_GetDurationTime();
    U32 u32SystemTime = MApp_GetLocalSystemTime();
    U32 u32RecordStartTime = MApp_PVR_GetRecordStartSysTime();

    for (i = 0; i<m_PlaybackUriLicenseHander.u8UrilicenseCount; i++)
    {
        if (0xFFFFFFFF == m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime)
        {
            m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime = u32DurationTime;
        }

        if ( (u32PlaybackTime > m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockBeginTime)
             && (u32PlaybackTime < m_PlaybackUriLicenseHander.m_UrilicenseInfo[i].u32BlockEndTime) )
        {
            u8Index = i;
        }
    }

    if (_MAPP_CIPVR_RetentionLimitBlockCompute(
           m_PlaybackUriLicenseHander.m_UrilicenseInfo[u8Index].pvrUriLicense,
           u32SystemTime,
           u32RecordStartTime,
           u32DurationTime,
           m_PlaybackUriLicenseHander.m_UrilicenseInfo[u8Index].u32BlockBeginTime,
           m_PlaybackUriLicenseHander.m_UrilicenseInfo[u8Index].u32BlockEndTime,
           RLBlockInfo,
           TRUE))
    {
        return TRUE;
    }

    return FALSE;
}

#endif//((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#undef MAPP_CIPVR_ADAPTION_C
