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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiDMX.h
/// @brief  Demux API
/// @author MStar Semiconductor,Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef __API_DMX_H__
#define __API_DMX_H__

#include "MsCommon.h"


#ifdef __cplusplus
extern "C"
{
#endif

/// NULL PID definition
#define DMX_PID_NULL               (0x1FFF)

// Please don't change this value if you know exactly what you are doing
/// DMX Filter pattern depth
#define DMX_SECT_FLT_DEPTH         (16)

/// NULL DMX Id
#define DMX_DMXID_NULL             ((MS_U8)0xFF)
#define MSIF_DMX_LIB_CODE                     {'D','M','X','_'}    //Lib code
#define MSIF_DMX_LIBVER                       {'1','4'}            //LIB version
#define MSIF_DMX_BUILDNUM                     {'3','5'}            //Build Number
#define MSIF_DMX_CHANGELIST                   {'0','0','4','5','2','3','0','9'} //P4 ChangeList Number

/// DMX Version
#define DMX_API_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMX_LIB_CODE,                  /* IP__                                             */  \
    MSIF_DMX_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMX_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_DMX_CHANGELIST,  /* CL#                                              */  \
    MSIF_OS

/// DMX status indicator
typedef enum
{
    DMX_FILTER_STATUS_OK,               ///< DMX status OK
    DMX_FILTER_STATUS_ERROR,            ///< DMX status ERROR
} DMX_FILTER_STATUS;

typedef enum
{
    DMX_DBG_NONE,
    DMX_DBG_ERR,
    DMX_DBG_WARN,
    DMX_DBG_INFO,
    DMX_DBG_PVR,
    DMX_DBG_FUNC,
} DMX_DBGMSG_LEVEL;

/// DMX internal startup parameter
typedef struct _DMX_FW_Param
{
    MS_PHYADDR                          phyFWAddr;
    MS_U32                              u32FWSize;

    MS_PHYADDR                          phyVQAddr;
    MS_U32                              u32VQSize;

    MS_U32                              _zero_reserved[4];

} DMX_TSPParam;


#if 0
/// DMX fitler type and source type
typedef enum
{
    DMX_FILTER_TYPE_VIDEO,              ///< DMX video filter type
    DMX_FILTER_TYPE_AUDIO,              ///< DMX audio filter type
    DMX_FILTER_TYPE_AUDIO2,             ///< DMX audio2 filter type
    DMX_FILTER_TYPE_SECTION,            ///< DMX section filter type
    DMX_FILTER_TYPE_PES,                ///< DMX PES filter type
    DMX_FILTER_TYPE_PACKET,             ///< DMX TS packet filter type
    DMX_FILTER_TYPE_PCR,                ///< DMX PCR filter type
    DMX_FILTER_TYPE_TELETEXT,           ///< DMX teletext filter type

    DMX_FILTER_SOURCE_TYPE_MASK  =  0xC0000000,              ///< DMX filter source mask
    DMX_FILTER_SOURCE_TYPE_LIVE  =  0x80000000,              ///< DMX live stream filter source
    DMX_FILTER_SOURCE_TYPE_FILE  =  0x40000000,              ///< DMX file in filter type
} DMX_FILTER_TYPE;
#endif

#define DMX_FILTER_TYPE MS_U32

#define DMX_FILTER_TYPE_VIDEO           0x00000000   ///< DMX video filter type
#define DMX_FILTER_TYPE_AUDIO           0x00000001   ///< DMX audio filter type
#define DMX_FILTER_TYPE_AUDIO2          0x00000002   ///< DMX audio2 filter type
#define DMX_FILTER_TYPE_SECTION         0x00000003   ///< DMX section filter type
#define DMX_FILTER_TYPE_PES             0x00000004   ///< DMX PES filter type
#define DMX_FILTER_TYPE_PACKET          0x00000005   ///< DMX TS packet filter type
#define DMX_FILTER_TYPE_PCR             0x00000006   ///< DMX PCR filter type
#define DMX_FILTER_TYPE_TELETEXT        0x00000007   ///< DMX teletext filter type
#define DMX_FILTER_TYPE_VIDEO3D         0x00000008   ///< DMX V3D filter type
#define DMX_FILTER_TYPE_AUDIO3          0x00000009   ///< DMX audio 3 filter type
#define DMX_FILTER_TYPE_AUDIO4          0x0000000A   ///< DMX audio 4 filter type
#define DMX_FILTER_TYPE_REC             0x0000000B   ///< DMX record filter type no destination needs to be set

#define DMX_FILTER_FLT_MASK                     0xF0EC0000
#define DMX_FILTER_SOURCE_TYPE_MASK             0xF0EC0000                   ///< DMX filter source mask
#define DMX_FILTER_SOURCE_TYPE_LIVE             0x80000000                   ///< DMX live stream filter source
#define DMX_FILTER_SOURCE_TYPE_FILE             0x40000000                   ///< DMX file in filter type
#define DMX_FILTER_SOURCE_TYPE_LIVEB            DMX_FILTER_SOURCE_TYPE_FILE  ///< Input from TS1 to File PID filter
#define DMX_FILTER_SOURCE_TYPE_TS1              0x00800000                   ///< DMX live stream filter source 1
#define DMX_FILTER_SOURCE_TYPE_TS2              0x00400000                   ///< DMX live stream filter source 2
#define DMX_FILTER_SOURCE_TYPE_TS3              0x00200000                   ///< DMX live stream filter source 3
// Only supported by TSP ver3.0
#define DMX_FILTER_SOURCE_TYPE_TSIF_MMFI0       0x00080000                   ///< DMX MMFI0 file in filter type
#define DMX_FILTER_SOURCE_TYPE_TSIF_MMFI1       0x00040000                   ///< DMX MMFI1 file in filter type


// Only supported by TSP ver2.0 driver
#define DMX_FILTER_SOURCE_TYPE_PLAYBACK DMX_FILTER_SOURCE_TYPE_LIVE
#define DMX_FILTER_SOURCE_TYPE_PVR0     0x20000000   ///< DMX PVR0 stream filter source
#define DMX_FILTER_SOURCE_TYPE_PVR1     0x10000000   ///< DMX PVR1 stream filter source

#define DMX_FILTER_FLT_SCMB_MASK   		        0x20000000
#define DMX_FILTER_FLT_TYPE_SCMB                0x20000000      ///< DMX descramble filter type
#define DMX_FILTER_FLT_TYPE_SCMB_SHAREKEY       0x10000000      ///< DMX descramble filter type with sharekey

//--------------------------------------------------
// Debug table
typedef enum
{
    DMX_DEBUG_CMD_NONE,
    DMX_DEBUG_CMD_CLEAR,
    DMX_DEBUG_CMD_ENABLE,
    DMX_DEBUG_CMD_DISABLE,
} DMX_DEBUG_CMD;

typedef enum
{
    DMX_DEBUG_SRC_TS0,
    DMX_DEBUG_SRC_TS1,
    DMX_DEBUG_SRC_TS2,
    DMX_DEBUG_SRC_FILE,
} DMX_DEBUG_SRC;

typedef enum
{
    DMX_DEBUG_TSIF_TS0,
    DMX_DEBUG_TSIF_TS1,
    DMX_DEBUG_TSIF_TSCB,
} DMX_DEBUG_TSIF;

typedef enum
{
    DMX_DEBUG_PKT_DEMUX_0,
    DMX_DEBUG_PKT_DEMUX_0_FILE,
    DMX_DEBUG_PKT_DEMUX_1,
    DMX_DEBUG_PKT_DEMUX_2,
    DMX_DEBUG_MMFI0,
    DMX_DEBUG_MMFI1,
} DMX_DEBUG_FIFO_SRC;

typedef enum
{
    DMX_DEBUG_FIFO_VIDEO,
    DMX_DEBUG_FIFO_AUDIO,
    DMX_DEBUG_FIFO_VIDEO3D,
    DMX_DEBUG_FIFO_AUDIOB,
} DMX_DEBUG_FIFO;

// only one playback flow or PVR flow exist
// Playback flow and PVR flow can exist simultaneously
/// DMX flow type
typedef enum
{
    DMX_FLOW_PLAYBACK                   = 0,                       ///< DMX playback flow
    DMX_FLOW_PVR                        = 1,                       ///< DMX recording flow
    DMX_FLOW_PVR1                       = 2,                       ///< DMX recording flow, note: Not support for all chip

    DMX_FLOW_PVRCA                      = 3,                       ///< CI+ PVR

    DMX_FLOW_FILEIN_MM                  = 4,                       ///< DMX Filein flow with Main path Vido and MMFI path Audio
    DMX_FLOW_MMFI0                      = DMX_FLOW_FILEIN_MM,      ///< DMX Filein flow with MMFI 0 (MMFI version 2.0)
    DMX_FLOW_FILEIN_MM3D                = 5,                       ///< DMX Filein flow with Main path Video, MMFI path 3DVideo, and MMFI Audio
    DMX_FLOW_MMFI1                      = DMX_FLOW_FILEIN_MM3D,    ///< DMX Filein flow with MMFI 1 (MMFI version 2.0)

    DMX_FLOW_CIPHSS_PLAYBACK            = 6,                       ///< Playback flow for CI+ HSS 2 path input for CI+
    DMX_FLOW_CIPHSS_PVRCA               = 7,                       ///< PVR flow for CI+ HSS 2 path input for CI+

    DMX_FLOW_PVR2                       = 8,                       ///< DMX recording flow, note: Not support for all chip, PVR2
    DMX_FLOW_PVR3                       = 9,                       ///< DMX recording flow, note: Not support for all chip
    DMX_FLOW_PVR4                       = 10,                      ///< DMX recording flow, note: Not support for all chip
    DMX_FLOW_PVR5                       = 11,                      ///< DMX recording flow, note: Not support for all chip

    DMX_FLOW_TSO_PLAYBACK               = 12,                      ///< DMX TSO playback flow (version 3.0)
    DMX_FLOW_PLAYBACK1                  = 13,                      ///< DMX playback flow (version 3.0)
    DMX_FLOW_PVRCA1                     = 14,                      ///< CI+ PVR (version 3.0)

    DMX_FLOW_NUM                        = 15,
} DMX_FLOW;

/// DMX input type
typedef enum
{
    DMX_FLOW_INPUT_DEMOD,               ///< DMX input from internal demod
    DMX_FLOW_INPUT_MEM,                 ///< DMX input from memory
    DMX_FLOW_INPUT_EXT_INPUT0,          ///< DMX input from external input 0
    DMX_FLOW_INPUT_EXT_INPUT1,          ///< DMX input from external input 1
    DMX_FLOW_INPUT_EXT_INPUT2,          ///< DMX input from external input 2. note: Not support for all chip
    DMX_FLOW_INPUT_EXT_INPUT3 ,         ///< DMX input from external input 3. note: Not support for all chip
    DMX_FLOW_INPUT_MEM_NOPASSCA,        ///< DMX input from memory, but not pass through CA
    DMX_FLOW_INPUT_TSO,                 ///< DMX input from TSOutput
    DMX_FLOW_INPUT_MEM_PASSCA1,         ///< DMX input from memory, but pass through CA1, not CA0
    DMX_FLOW_INPUT_DISABLE,
} DMX_FLOW_INPUT;

typedef enum
{
    DMX_PVR_EGN0,
    DMX_PVR_EGN1,
    DMX_PVR_EGN2,
    DMX_PVR_EGN3,
    DMX_PVR_EGN4,
    DMX_PVR_EGN5,
} DMX_PVR_ENG;

#if 0
// make sure what you are doing before changing the value
/// DMX callback types
typedef enum
{
    DMX_EVENT_DATA_READY           = 0x00000001, ///< DMX event ready
    DMX_EVENT_BUF_OVERFLOW         = 0x00000002, ///< DMX event overflow
    DMX_EVENT_PVRBUF_FULL          = 0x00000010, ///< DMX event PVR buffer overflow

    /// TSP self task callback // optional --> default is CB by poll
    DMX_EVENT_CB_MASK              = 0x80000000, ///< DMX callback mask
    DMX_EVENT_CB_POLL              = 0x00000000, ///< DMX callback by polling // OBSOLETE
    DMX_EVENT_CB_SELF              = 0x80000000, ///< DMX callback by demux module
    DMX_EVENT_CB_SELF_TYPE2        = 0xC0000000, ///< DMX callback by demux module
} DMX_EVENT;
#endif

#define DMX_EVENT MS_U32
#define DMX_EVENT_DATA_READY          0x00000001 ///< DMX event ready
#define DMX_EVENT_BUF_OVERFLOW        0x00000002 ///< DMX event overflow
#define DMX_EVENT_SEC_CRCERROR        0x00000004 ///< DMX event CRC error
#define DMX_EVENT_PVRBUF_FULL         0x00000010 ///< DMX event PVR buffer overflow
#define DMX_EVENT_PVR1BUF_FULL        0x00000020 ///< DMX event Channel Browser buffer overflow

/// TSP self task callback // optional --> default is CB by poll
#define DMX_EVENT_CB_MASK             0x80000000 ///< DMX callback mask
#define DMX_EVENT_CB_POLL             0x00000000 ///< DMX callback by polling // OBSOLETE
#define DMX_EVENT_CB_SELF             0x80000000 ///< DMX callback by demux module
#define DMX_EVENT_CB_SELF_TYPE2       0xC0000000 ///< DMX callback by demux module

typedef enum
{
    DMX_BURSTSINGLE                = 0x00,
    DMX_BURST2BYTE                 = 0x01,
    DMX_BURST4BYTE                 = 0x02,
    DMX_BURST8BYTE                 = 0x03,
} DMX_BURSTTYPE;

#if 0
// make sure what you are doing before changing the value
/// DMX section mode setting
typedef enum
{
    DMX_SECT_MODE_CONTI            = 0x00000000, ///< DMX receive section contiguously
    DMX_SECT_MODE_ONESHOT          = 0x00000001, ///< DMX only receive one section

    // optional
    DMX_SECT_MODE_CRCCHK           = 0x00000002, ///< DMX enables CRC check
    DMX_SECT_MODE_AUTO_ADDR        = 0x00000004, ///< DMX align read pointer to write pointer when get write pointer // OBSOLETE
} DMX_SECT_MODE;
#endif

#define DMX_SECT_MODE MS_U32
#define DMX_SECT_MODE_CONTI        0x00000000 ///< DMX receive section contiguously
#define DMX_SECT_MODE_ONESHOT      0x00000001 ///< DMX only receive one section
#define DMX_SECT_MODE_PESSCMCHK    0x00000003 ///< DMX checking PES SCMB status

// optional
#define DMX_SECT_MODE_CRCCHK       0x00000002 ///< DMX enables CRC check
#define DMX_SECT_MODE_AUTO_ADDR    0x00000004 ///< DMX align read pointer to write pointer when get write pointer // OBSOLETE

/// for MApi_DMX_AVFifo_Status return value u32FifoStatus
#define DMX_FIFO_STATUS            MS_U32
#define DMX_FIFO_STATUS_LV_MASK    0x0000000F /// use this mask to get fifo level and use below macro to get current fifo status
#define DMX_FIFO_STATUS_LV_EMPTY   0x00000001 /// if fifo level status equal to this macro means fifo is empty
#define DMX_FIFO_STATUS_RST_MASK   0x80000000 /// use this mask to get fifo reset status
#define DMX_FIFO_STATUS_RST_EN     0x80000000 /// if fifo reset status equal to this macro means fifo reset is enabled.


/// DMX filein destination types
typedef enum
{
    DMX_PES_AUDIO2_FIFO 	= 0,              ///< DMX destination is audio2 fifo
    DMX_PES_AUDIO_FIFO  	= 1,              ///< DMX destination is audio fifo
    DMX_PES_VIDEO_FIFO  	= 2,              ///< DMX destination is video fifo
    DMX_PES_NO_BYPASS_FIFO  = 3,              ///< DMX destination with no bypass
    DMX_PES_VIDEO3D_FIFO  	= 4,              ///< DMX destination is video3D fifo
    DMX_PES_AUDIO3_FIFO     = 5,              ///< DMX destination is audio3 fifo
    DMX_PES_AUDIO4_FIFO     = 6,              ///< DMX destination is audio4 fifo
} DMX_FILEIN_DST; //  DMXPESDATAFIFO;

/// DMX callback prototype
typedef void (*DMX_NotifyCb)(MS_U8 u8DmxId, DMX_EVENT enEvent);
typedef void (*DMX_Type2NotifyCb)(MS_U8 u8DmxId, DMX_EVENT enEvent, MS_U32 NotifyParam1);
/// DMX callback used in copy data
typedef MS_BOOL (*DMX_CheckCb)(MS_U8 u8DmxId, MS_U8* start, MS_U8* end, MS_U8* read, MS_U8* write);

// dummy data structure
typedef struct
{
    MS_U32                      streaminfo;
} DMX_Stream_info;

/// DMX section filter information structure
typedef struct
{
    MS_PHYADDR                  SectBufAddr; ///< DMX section buffer in physical address
    MS_U32                      SectBufSize; ///< DMX section buffer size
    DMX_SECT_MODE          		SectMode;         ///< DMX section mode
    DMX_EVENT              		Event;            ///< DMX section event
    DMX_NotifyCb           		pNotify;          ///< DMX section callback
    DMX_Type2NotifyCb           pType2Notify;          ///< DMX section callback
    MS_U32           			Type2NotifyParam1;          ///< DMX section callback
} DMX_Sect_info;

/// DMX filter information structure
typedef struct
{
    union {
        DMX_Stream_info    StreamInfo; ///< DMX stream information for future use
        DMX_Sect_info      SectInfo;   ///< DMX section information
    } Info;
} DMX_Flt_info;

/// DMX PVR information structure
typedef struct
{
    MS_PHYADDR                  pPvrBuf0;       ///< DMX PVR buffer 0 starting address
    MS_PHYADDR                  pPvrBuf1;       ///< DMX PVR buffer 1 starting address
    MS_U32                      PvrBufSize0;    ///< DMX PVR buffer 0 size
    MS_U32                      PvrBufSize1;    ///< DMX PVR buffer 1 size
    DMX_EVENT              		Event;          ///< DMX PVR event
    DMX_NotifyCb           		pNotify;        ///< DMX PVR callback
} DMX_Pvr_info;

/// DMX Channel Browser information structure
typedef struct
{
    MS_PHYADDR                  pPvr1Buf0;       ///< DMX Channel Browser buffer 0 starting address
    MS_U32                      Pvr1BufSize0;    ///< DMX Channel Browser buffer 0 size
    DMX_EVENT              		Event;          ///< DMX Channel Browser event
    DMX_NotifyCb           		pNotify;        ///< DMX Channel Browser callback
} DMX_Pvr1_info;

//----------------------------------
/// DMX debug table information structure
//----------------------------------
typedef struct
{
    DMX_DEBUG_CMD               TspCmd;
    DMX_DEBUG_SRC               TspSrc;
    DMX_DEBUG_FIFO              TspFifo;
} DMX_DisContiCnt_info, DMX_DropPktCnt_info;

typedef struct
{
    DMX_DEBUG_CMD               TspCmd;
    DMX_DEBUG_TSIF              TspTsif;
} DMX_LockPktCnt_info;

typedef struct
{
    DMX_DEBUG_CMD               TspCmd;
    DMX_DEBUG_FIFO              TspFifo;    
    DMX_DEBUG_FIFO_SRC          TspFifoSrc;
} DMX_AVPktCnt_info;


/// DMX capability query type
typedef enum
{
    DMX_CAP_PID_FILTER_NUM          = 0,          ///< Get PID filter number
    DMX_CAP_SEC_FILTER_NUM          = 1,          ///< Get section filter number
    DMX_CAP_SEC_BUF_NUM             = 2,          ///< Get section buffer number

    DMX_CAP_PVR_ENG_NUM             = 3,          ///< Get pvr engine number
    DMX_CAP_PVR_FILTER_NUM          = 4,          ///< Get pvr filter number
    DMX_CAP_PVR1_FILTER_NUM         = 5,          ///< Get pvr1 filter number

    DMX_CAP_MMFI_AUDIO_FILTER_NUM   = 6,          ///< Get MM file in audio path filter number
    DMX_CAP_MMFI_V3D_FILTER_NUM     = 7,          ///< Get MM file in video 3D path filter number

    DMX_CAP_MMFI0_FILTER_NUM        = 6,          ///< Get MM file in 0 path filter number
    DMX_CAP_MMFI1_FILTER_NUM        = 7,          ///< Get MM file in 1 path filter number

    DMX_CAP_TSIF_NUM                = 8,          ///< Get ts interface number
    DMX_CAP_DEMOD_NUM               = 9,          ///< Get demod support number
    DMX_CAP_TS_PAD_NUM              = 10,         ///< Get TS pad support number
    DMX_CAP_VQ_NUM                  = 11,         ///< Get virtual queue support number

    DMX_CAP_CA_FLT_NUM              = 12,         ///< Get descramble filter number
    DMX_CAP_CA_KEY_NUM              = 13,         ///< Get total descramble key number

    DMX_CAP_FW_ALIGN                = 14,         ///< Get MIU alignment in bytes of DMX FW
    DMX_CAP_VQ_ALIGN                = 15,         ///< Get MIU alignment in bytes of Virtual queue
    DMX_CAP_VQ_PITCH                = 16,         ///< Get length in bytes in bytes of one VQ unit
    DMX_CAP_SEC_BUF_ALIGN           = 17,         ///< Get MIU alignment in bytes of section buffer
    DMX_CAP_PVR_ALIGN               = 18,         ///< Get miu alignment in bytes of record buffer

    DMX_CAP_PVRCA_PATH_NUM          = 19,         ///< Get the numbers of descramble record path

    DMX_CAP_SHAREKEY_FLT_RANGE      = 20,         ///< Get the range of sharekey descramble 0  filter id. data0 is start ID, data 1 is end ID
    DMX_CAP_PVRCA0_FLT_RANGE        = 21,         ///< Get the range of PVRCA0 filter id. data0 is start ID, data 1 is end ID
    DMX_CAP_PVRCA1_FLT_RANGE        = 22,         ///< Get the range of PVRCA1 filter id. data0 is start ID, data 1 is end ID
    DMX_CAP_PVRCA2_FLT_RANGE        = 23,         ///< Get the range of PVRCA2 filter id. data0 is start ID, data 1 is end ID
    DMX_CAP_SHAREKEY_FLT1_RANGE     = 24,         ///< Get the range of sharekey descramble 1 filter id. data0 is start ID, data 1 is end ID
    DMX_CAP_SHAREKEY_FLT2_RANGE     = 25,         ///< Get the range of sharekey descramble 2 filter id. data0 is start ID, data 1 is end ID

    DMX_CAP_HW_TYPE                 = 26,         ///< Get the HW architecture type. 0xXXX0: No PVR, 0x100X: TV series, 0x200X: STB series

    DMX_CAP_NULL,
} DMX_QUERY_TYPE;

typedef enum
{
	DMX_HW_TYPE_NONE		     = 0,
    DMX_HW_TYPE_TV_SERIES        = 0x00001000,       ///< The HW architecture is TV series without PVR cunfction
    DMX_HW_TYPE_TV_TYPE1         = 0x00001001,       ///< The HW architecture is TV series with Seperate PVR filters
    DMX_HW_TYPE_TV_TYPE2         = 0x00001002,       ///< The HW architecture is TV series with general PVR filters
    DMX_HW_TYPE_STB_SERIES       = 0x00002000,       ///< The HW architecture is BOX series without PVR cunfction
    DMX_HW_TYPE_STB_TYPE1        = 0x00002001,       ///< The HW architecture is BOX series with RASP PVR filters
    DMX_HW_TYPE_STB_TYPE2        = 0x00002002,       ///< The HW architecture is TV series with general PVR filters
} DMX_HW_TYPE;

typedef enum
{
    DMX_TIMESTAMP_CLK_90K = 0x00000000,
    DMX_TIMESTAMP_CLK_27M = 0x00000001,
} DMX_TimeStamp_Clk;

/// TSP file in Packet mode
typedef enum //_DMX_Filein_Packmode
{
    DMX_PKTMODE_188 = 0x00000000,       ///< DMX file in packet size with 188
    DMX_PKTMODE_192 = 0x00000001,       ///< DMX file in packet size with 192
    DMX_PKTMODE_204 = 0x00000002,       ///< DMX file in packet size with 204
    DMX_PKTMODE_130 = 0x00000003,       ///< DMX file in packet size with 130 (RVU)
    DMX_PKTMODE_134 = 0x00000004,       ///< DMX file in packet size with 134 (RVU with timestamp)
} DMX_Filein_PacketMode;

/// TSP file in information structure
typedef struct
{
    MS_U32                 Rate;   ///< DMX file in rate
    DMX_Filein_PacketMode  PKT_Mode;    ///< DMX file in packet size mode
} DMX_Filein_info;

typedef enum
{
    DMX_MMFI_AUDIO  	= 0,              ///< DMX destination with no bypass to MM Audio path
    DMX_MMFI_VIDEO  	= 1,              ///< DMX destination with no bypass to MM Video path
} DMX_MMFI_PATH;

//MMFI2
#define DMX_MMFI_PATH0      DMX_MMFI_AUDIO
#define DMX_MMFI_PATH1      DMX_MMFI_VIDEO

// must alignment with TSP_FIFO_XXX in halTSP.h
typedef enum
{
    DMX_MMFI_FLTTYPE_AUD    = 0x00,
    DMX_MMFI_FLTTYPE_AUDB   = 0x01,
    DMX_MMFI_FLTTYPE_VD3D   = 0x02,
    DMX_MMFI_FLTTYPE_VD     = 0x03,
    DMX_MMFI_FLTTYPE_AUDC   = 0x04,
    DMX_MMFI_FLTTYPE_AUDD   = 0x05,

    DMX_MMFI1_FLTTYPE_MASK  = 0x80,
}DMX_MMFI_FLTTYPE;

typedef enum
{
	DMX_MMFI_PES_NO_BYPASS_AU 		= 0x0000,
	DMX_MMFI_PES_PS_AU				= 0x0001,
	DMX_MMFI_PES_PS_AUB				= 0x0002,
	DMX_MMFI_PES_APID_BYPASS		= 0x0004,
	DMX_MMFI_PES_APIDB_BYPASS		= 0x0008,
    DMX_MMFI_PES_NO_BYPASS_V3D		= 0x0010,
    DMX_MMFI_PES_PS_V3D				= 0x0020,
	DMX_MMFI_PES_V3DPID_BYPASS		= 0x0040,

    DMX_MMFI_PES_NO_BYPASS_VD       = 0x0080,
    DMX_MMFI_PES_VPID_BYPASS        = 0x0100,
    DMX_MMFI_PES_NO_BYPASS_TS       = 0x0200,
    DMX_MMFI_PES_PS_VD              = 0x0400,

    DMX_MMFI_PES_NO_BYPASS_FIFO     = 0x0800,

    DMX_MMFI1_PES_TYPE_MASK         = 0x8000,
}DMX_MMFI_DST;

// General API
DMX_FILTER_STATUS MApi_DMX_Init(void);
DMX_FILTER_STATUS MApi_DMX_TSPInit(DMX_TSPParam *param);
DMX_FILTER_STATUS MApi_DMX_Exit(void);
DMX_FILTER_STATUS MApi_DMX_ForceExit(void);
DMX_FILTER_STATUS MApi_DMX_Reset(void);
DMX_FILTER_STATUS MApi_DMX_SetFW(MS_PHYADDR pFwAddr, MS_U32 u32FwSize); // In DRAM physical address
DMX_FILTER_STATUS MApi_DMX_Suspend(void);
DMX_FILTER_STATUS MApi_DMX_Resume(MS_U32 u32FWAddr, MS_U32 u32FWSize);
DMX_FILTER_STATUS MApi_DMX_ReleaseSemaphone(void);
DMX_FILTER_STATUS MApi_DMX_SetFwDbgParam(MS_U32 u32Addr, MS_U32 u32Size, MS_U32 u32DbgWord);
DMX_FILTER_STATUS MApi_DMX_SetDbgLevel(DMX_DBGMSG_LEVEL level);
DMX_FILTER_STATUS MApi_TSP_Get_FW_VER(MS_U32* u32FWVer);
DMX_FILTER_STATUS MApi_DMX_Get_Intr_Count(MS_U32* pu32Count);
DMX_FILTER_STATUS MApi_DMX_GetLibVer(const MSIF_Version **ppVersion);
DMX_FILTER_STATUS MApi_DMX_GetCap(DMX_QUERY_TYPE DmxQueryType, void* pOutput);
DMX_FILTER_STATUS MApi_DMX_Get_FlowInput_Status(DMX_FLOW DmxFlow, DMX_FLOW_INPUT *pDmxFlowInput, MS_BOOL *pbClkInv, MS_BOOL *pbExtSync, MS_BOOL *pbParallel);
DMX_FILTER_STATUS MApi_DMX_STC64_Mode_Enable(MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_VQ_Enable(MS_BOOL bEnable);

DMX_FILTER_STATUS MApi_DMX_FlowSet(DMX_FLOW DmxFlow, DMX_FLOW_INPUT DmxFlowInput, MS_BOOL bClkInv, MS_BOOL bExtSync, MS_BOOL bParallel);
DMX_FILTER_STATUS MApi_DMX_Open(DMX_FILTER_TYPE DmxFltType, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Start(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Stop(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_IsStart(MS_U8 u8DmxId, MS_BOOL* pbEnable);
DMX_FILTER_STATUS MApi_DMX_Get_PesScmbSts(MS_U8 u8DmxId, MS_U8* pu8scmb);
DMX_FILTER_STATUS MApi_DMX_Get_TsScmbSts(MS_U8 u8DmxId, MS_U8* pu8ScmSts);
DMX_FILTER_STATUS MApi_DMX_ChkAlive(void);
DMX_FILTER_STATUS MApi_DMX_Info(MS_U8 u8DmxId, DMX_Flt_info* pDmxFltInfo, DMX_FILTER_TYPE* pDmxFltType, MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Pid(MS_U8 u8DmxId, MS_U16* pu16Pid, MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Stc_Get(MS_U32* pu32Stc32, MS_U32* pu32Stc);
DMX_FILTER_STATUS MApi_DMX_Stc_Set(MS_U32 u32Stc32, MS_U32 u32Stc);
DMX_FILTER_STATUS MApi_DMX_Stc_Eng_Get(MS_U8 u8Eng, MS_U32* pu32Stc32, MS_U32* pu32Stc);
DMX_FILTER_STATUS MApi_DMX_Stc_Eng_Set(MS_U8 u8Eng, MS_U32 u32Stc32, MS_U32 u32Stc);
DMX_FILTER_STATUS MApi_DMX_Pcr_Get(MS_U32* pu32Pcr32, MS_U32* pu32Pcr);
DMX_FILTER_STATUS MApi_DMX_Proc(MS_U8 u8DmxId, DMX_EVENT* pEvent);
DMX_FILTER_STATUS MApi_DMX_Parl_Invert(DMX_FLOW DmxFlow, MS_BOOL bInvert);
//DMX_FILTER_STATUS MApi_DMX_Proc(MS_U8 u8DmxId); // 0xFF for u8DmxId means check the last un-check filter
DMX_FILTER_STATUS MApi_DMX_CopyData(MS_U8 u8DmxId, MS_U8* pu8Buf, MS_U32 u32BufSize, MS_U32* pu32ActualSize, MS_U32* pu32RmnSize, DMX_CheckCb pfCheckCB);
DMX_FILTER_STATUS MApi_DMX_RemoveDupAVPkt(MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_RemoveDupAVFifoPkt(DMX_FILTER_TYPE DmxFltType, MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_Change_FilterSource(MS_U8 u8DmxId, DMX_FILTER_TYPE DmxFltSrcType);


// Section API
DMX_FILTER_STATUS MApi_DMX_SectPatternSet(MS_U8 u8DmxId, MS_U8* pPattern, MS_U8* pMask, MS_U8 *pu8NotMask, MS_U32 MatchSize);
// DMX_FILTER_STATUS MApi_DMX_SectGet(MS_U8 u8DmxId, MS_U8* pu8Buf, MS_U32 u32BufSize, MS_U32* pu32SectSize);
DMX_FILTER_STATUS MApi_DMX_SectReset(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_SectReadSet(MS_U8 u8DmxId, MS_PHYADDR Read);
DMX_FILTER_STATUS MApi_DMX_SectReadGet(MS_U8 u8DmxId, MS_PHYADDR* pRead);
DMX_FILTER_STATUS MApi_DMX_SectWriteGet(MS_U8 u8DmxId, MS_PHYADDR* pWrite);
DMX_FILTER_STATUS MApi_DMX_SectStartGet(MS_U8 u8DmxId, MS_PHYADDR* pStart);
DMX_FILTER_STATUS MApi_DMX_SectEndGet(MS_U8 u8DmxId, MS_PHYADDR* pEnd);


// PVR API Old
DMX_FILTER_STATUS MApi_DMX_Pvr_Open(DMX_Pvr_info* pPvrInfo);
DMX_FILTER_STATUS MApi_DMX_Pvr_Close(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_Pause(MS_BOOL bPause);
DMX_FILTER_STATUS MApi_DMX_Pvr_Pid_Open(MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Pid_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Start(MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_Pvr_Stop(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_WriteGet(MS_U32* pu32Write);
DMX_FILTER_STATUS MApi_DMX_PVR_SetPacketMode(MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Pvr_SetRecordStamp(MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_GetRecordStamp(MS_U32* pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_SetPlaybackStamp(MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_GetPlaybackStamp(MS_U32* pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_TimeStampEnable(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_TimeStampDisable(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_MOBF_Enable(MS_BOOL bEnable, MS_U32 u32key0, MS_U32 u32key1);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_MOBF_Enable(MS_U8 u8Eng, MS_BOOL bEnable, MS_U32 u32key0, MS_U32 u32key1);

// PVR API New
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Open(DMX_PVR_ENG Eng ,DMX_Pvr_info* pPvrInfo);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Close(DMX_PVR_ENG Eng );
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Pause(DMX_PVR_ENG Eng ,MS_BOOL bPause);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Pid_Open(DMX_PVR_ENG Eng ,MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Pid_Close(DMX_PVR_ENG Eng ,MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Pid(DMX_PVR_ENG Eng ,MS_U8 u8DmxId , MS_U32 *Pid, MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Start(DMX_PVR_ENG Eng ,MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Stop(DMX_PVR_ENG Eng );
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_WriteGet(DMX_PVR_ENG Eng ,MS_U32* pu32Write);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_SetPacketMode(DMX_PVR_ENG Eng ,MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_SetRecordStamp(DMX_PVR_ENG Eng ,MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_GetRecordStamp(DMX_PVR_ENG Eng ,MS_U32* pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_SetPlaybackStampClk(MS_U8 u8Eng, DMX_TimeStamp_Clk eClk);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_SetRecordStampClk(DMX_PVR_ENG Eng, DMX_TimeStamp_Clk eClk);

// File-in API
DMX_FILTER_STATUS MApi_DMX_Filein_Start(DMX_FILEIN_DST Dst, MS_PHYADDR pBuf, MS_U32 u32BufSize);   // msAPI_DMX_PESPlayback/msAPI_DMX_TSPlayback will integrate into it
DMX_FILTER_STATUS MApi_DMX_Filein_Stop(void);
DMX_FILTER_STATUS MApi_DMX_Filein_Info(DMX_Filein_info *pFileinInfo);
DMX_FILTER_STATUS MApi_DMX_Filein_Pause(void);
DMX_FILTER_STATUS MApi_DMX_Filein_Resume(void);
MS_BOOL           MApi_DMX_Filein_IsIdle(void);
MS_BOOL           MApi_DMX_Filein_IsBusy(void);
MS_BOOL           MApi_DMX_Filein_IsPause(void);
DMX_FILTER_STATUS MApi_DMX_Filein_CMDQ_Reset(void);
DMX_FILTER_STATUS MApi_DMX_Filein_CMDQ_GetEmptyNum(MS_U32 *pu32EmptySlot);
void              MApi_DMX_BypassFileInTimeStamp(MS_BOOL bbypass);
DMX_FILTER_STATUS MApi_DMX_Filein_CMDQ_FIFOWriteLevel(MS_U8 *pu8CmdQStatus);
DMX_FILTER_STATUS MApi_DMX_GetFileInTimeStamp(MS_U32 *pu32FileInTS);
DMX_FILTER_STATUS MApi_DMX_Filein_GetReadAddr(MS_U32* pu32Read);
DMX_FILTER_STATUS MApi_DMX_Filein_MOBF_Enable(MS_BOOL bEnable, MS_U32 u32key);

//MMFI & MINITSP
MS_BOOL 		  MApi_DMX_MMFI_Filein_IsIdle(DMX_MMFI_PATH ePath);
MS_BOOL           MApi_DMX_MMFI_Filein_IsBusy(DMX_MMFI_PATH ePath);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_CMDQ_Reset(DMX_MMFI_PATH ePath);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_CMDQ_GetEmptyNum(DMX_MMFI_PATH ePath, MS_U32 *pu32EmptySlot);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_Start(DMX_MMFI_DST eDst, MS_PHYADDR pBuf, MS_U32 u32BufSize);
DMX_FILTER_STATUS MApi_DMX_MMFI_GetFileInTimeStamp(DMX_MMFI_PATH ePath, MS_U32 *pu32FileInTS);

//MMFI
DMX_FILTER_STATUS MApi_DMX_MMFI_Pid_Open(DMX_MMFI_FLTTYPE flttype, MS_U16 u16Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_MMFI_Pid_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_CMDQ_FIFOWriteLevel(DMX_MMFI_PATH ePath, MS_U8 *pu8CmdQStatus);
DMX_FILTER_STATUS MApi_DMX_MMFI_SetPcr2(DMX_MMFI_PATH ePath, MS_U32 u32pcr2);
DMX_FILTER_STATUS MApi_DMX_MMFI_GetPcr2(DMX_MMFI_PATH ePath, MS_U32 *pu32pcr2);
DMX_FILTER_STATUS MApi_DMX_MMFI_RemoveDupAVPkt(MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_MMFI_MOBF_Enable(DMX_MMFI_PATH ePath, MS_BOOL bEnable, MS_U32 u32key);
DMX_FILTER_STATUS MApi_DMX_MMFI_MOBF_SetLevel(DMX_MMFI_PATH epath, MS_U8 u8level);
DMX_FILTER_STATUS MApi_DMX_MMFI_TimeStampClk(DMX_MMFI_PATH ePath, DMX_TimeStamp_Clk eClk);

//PVR CA API
#if (!(defined(TSP_VERSION) && (TSP_VERSION == TSP_VER_2_0)))
DMX_FILTER_STATUS MApi_DMX_PvrCA_Pid_Open(MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Pid_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Start(MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Stop(void);

DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Pid_Open(DMX_PVR_ENG Eng, MS_U32 Pid, MS_U8* pu8DmxId, MS_U8 u8ShareKeyType);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Pid_Close(DMX_PVR_ENG Eng, MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Start(DMX_PVR_ENG Eng, MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Stop(DMX_PVR_ENG Eng);
#endif

// owner ship set/checking
DMX_FILTER_STATUS MApi_DMX_SetOwner(MS_U8 u8DmxIdStart, MS_U8 u8DmxIdEnd, MS_BOOL bOwner); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_GetOwner(MS_U8 u8DmxId, MS_BOOL* pbOwner); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_GetAccess(MS_U32 u32Try); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_ReleaseAccess(void); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_SetHK(MS_BOOL bIsHK); // OBSOLETE

// AVFIFO control
DMX_FILTER_STATUS MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE DmxFltType, MS_BOOL bFlush);
DMX_FILTER_STATUS MApi_DMX_AVFifo_Status(DMX_FILTER_TYPE DmxFltType, DMX_FIFO_STATUS* u32FifoLevel);

#if (defined(TSP_VERSION) && (TSP_VERSION == TSP_VER_3_0))
DMX_FILTER_STATUS MApi_DMX_AVFifo_BlockEnable(DMX_FILTER_TYPE DmxFltType, MS_BOOL bEnable);
#endif

DMX_FILTER_STATUS MApi_DMX_SetBurstLen(DMX_BURSTTYPE BurstType);
DMX_FILTER_STATUS MApi_DMX_TTX_WriteGet(MS_U8 u8DmxId, MS_PHYADDR* pWrite);
DMX_FILTER_STATUS MApi_DMX_GetDbgPortInfo(MS_U32 u32DbgSel,MS_U32* u32DbgInfo);

DMX_FILTER_STATUS MApi_DMX_Drop_Enable(MS_BOOL bSet);

// ---------------- [NOTE] API for TSP Ver2.0 HW architecture.-------------
DMX_FILTER_STATUS MApi_DMX_Open_MultiFlt( DMX_FILTER_TYPE DmxFltType , MS_U8* pu8DmxId, MS_U8 u8TargetDmxId);
DMX_FILTER_STATUS MApi_DMX_LiveSrcSwitch(DMX_FILTER_TYPE TgtFlow);
//--------------------------------------------------------------------------------

DMX_FILTER_STATUS MApi_DMX_AU_BD_Mode_Enable(MS_BOOL bEnable);

//------------------------ TSO -----------------------------
DMX_FILTER_STATUS MApi_DMX_TSO_Filein_Info(MS_U8 u8Eng, DMX_Filein_info *pFileinInfo);
MS_BOOL           MApi_DMX_TSO_Filein_IsIdle(MS_U8 u8Eng);
DMX_FILTER_STATUS MApi_DMX_TSO_Filein_CMDQ_GetEmptyNum(MS_U8 u8Eng, MS_U32 *pu32EmptySlot);
DMX_FILTER_STATUS MApi_DMX_TSO_Filein_Start(MS_U8 u8Eng, MS_PHYADDR pBuf, MS_U32 u32BufSize);
DMX_FILTER_STATUS MApi_DMX_TSO_Filein_Stop(MS_U8 u8Eng);
DMX_FILTER_STATUS MApi_DMX_TSO_SetPlaybackTimeStamp(MS_U8 u8Eng, MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_TSO_GetPlaybackStamp(MS_U8 u8Eng, MS_U32* pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_TSO_GetFileInTimeStamp(MS_U8 u8Eng, MS_U32 *pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_TSO_BypassFileInTimeStamp(MS_U8 u8Eng, MS_BOOL bbypass);
DMX_FILTER_STATUS MApi_DMX_TSO_TimeStampEnable(MS_U8 u8Eng);
DMX_FILTER_STATUS MApi_DMX_TSO_TimeStampDisable(MS_U8 u8Eng);


//---  Common Interface for TSP config and Api commands ------------//
DMX_FILTER_STATUS MApi_DMX_CMD_Run(MS_U32 u32Cmd, MS_U32 u32Config, MS_U32 u32DataNum, void *pData);

//---  Debug table ------------//
DMX_FILTER_STATUS MApi_DMX_Get_DisContiCnt(DMX_DisContiCnt_info* pDmxInfo, MS_U32* pu32Cnt);
DMX_FILTER_STATUS MApi_DMX_Get_DropPktCnt(DMX_DropPktCnt_info* pDmxInfo, MS_U32* pu32Cnt);
DMX_FILTER_STATUS MApi_DMX_Get_LockPktCnt(DMX_LockPktCnt_info* pDmxInfo, MS_U32* pu32Cnt);
DMX_FILTER_STATUS MApi_DMX_Get_AVPktCnt(DMX_AVPktCnt_info* DmxInfo, MS_U32* pu32Cnt);

#if 0
DMX_FILTER_STATUS MApi_DMX_ResetFileinTimestamp(void)
#endif


#ifdef __cplusplus
}
#endif

#endif // #ifndef __API_DMX_H__
