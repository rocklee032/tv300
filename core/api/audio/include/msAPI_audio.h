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
#ifndef _MSAPI_AUDIO_C_H
#define _MSAPI_AUDIO_C_H

#include "drvAUDIO.h"
#include "apiAUDIO.h"
#include "sys_sif_debug.h"
#include "msAPI_Global.h"
#include "drvVIFInitial_MST.h"

#ifdef _MSAPI_AUDIO_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif


//===================================================================================
#if( ENABLE_DTV )
 #if( ENABLE_ISDBT_AND_DVB )
    #define ENABLE_AUDIO_SYS_A2     1
    #define ENABLE_AUDIO_SYS_BTSC   1
 #elif( ENABLE_ISDBT_NO_DVB || ENABLE_ATSC)
    #define ENABLE_AUDIO_SYS_A2     0
    #define ENABLE_AUDIO_SYS_BTSC   1
 #else
    #define ENABLE_AUDIO_SYS_A2     1
    #define ENABLE_AUDIO_SYS_BTSC   0
 #endif

#else // ATV only
  #if( AUDIO_SYSTEM_SEL == AUDIO_SYSTEM_BTSC )
    #define ENABLE_AUDIO_SYS_A2     0
    #define ENABLE_AUDIO_SYS_BTSC   1
  #else
    #define ENABLE_AUDIO_SYS_A2     1
    #define ENABLE_AUDIO_SYS_BTSC   0
  #endif

#endif

#define ENABLE_AUD_SYS_BTSC_AND_A2  (ENABLE_AUDIO_SYS_A2&&ENABLE_AUDIO_SYS_BTSC)

//===================================================================================

#define ENABLE_AUDIO_MUTE_CONTROL_NEW   1


#define SUPPORT_PEQ_TOOL 1
#define PEQ_BANDS 5
#define MTS_NICAM_UNSTABLE 0    //For NICAM Unstable issue in Indonesia

#define AD_BALANCE_EQUAL 0            //main ad equal
#define AD_BALANCE_ADVOLUME_100 1     //=> ad max, main min
#define AD_BALANCE_ADVOLUME_75 2
#define AD_BALANCE_ADVOLUME_25 3
#define AD_BALANCE_ADVOLUME_0 4       //no ad voice

#define SPDIF_MUTE_LIMITED_TIME   1000//2000

typedef enum
{
    SOUND_MUTE_TV,             ///< SPEAKER/HP Sound Mute
    SOUND_MUTE_SPEAKER,   ///< SPEAKER Sound Mute
    SOUND_MUTE_HP,             ///< HP Sound Mute
    SOUND_MUTE_SCART,      ///< Scart1 Sound Mute
    SOUND_MUTE_SCART2,      ///< Scart2 Sound Mute
    SOUND_MUTE_MONITOR_OUT, ///< Monitor Sound Mute
    SOUND_MUTE_SPDIF,       ///< SPDIF Sound Mute
    SOUND_MUTE_AMP,        ///< Mute Amp
    SOUND_MUTE_ALL_EXCEPT_SCART,    ///< All Source Sound Mute except SCART
    SOUND_MUTE_ALL          ///< All Source Sound Mute
} SOUND_MUTE_SOURCE;

typedef enum
{
    E_MUTE_OFF, //Sound Mute Off
    E_MUTE_ON,  //Sound Mute On
} SOUND_MUTE_TYPE;

//-----------------------------------------------------------
//Adjust factor for TV/AV
typedef enum
{
//---Common interfaces for both Program storage type and Channel storage type---
    E_ADJUST_VIDEOMUTE,                             ///< Video mute
    E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME,       ///< Video mute during limited time
    E_ADJUST_BRIGHTNESS,                            ///< brightness
    E_ADJUST_CONTRAST,                              ///< contrast
    E_ADJUST_COLOR,                              ///< color
    E_ADJUST_HUE,                              ///< Hue
    E_ADJUST_SHARPNESS,                              ///< sharpness
    E_ADJUST_PSM,                              ///< PSM
    E_ADJUST_CSM,                              ///< CSM
//-- above items are non-used -----------------------------------------------------
    E_ADJUST_WRITE_MAILBOX,                ///< write mailbox (for MHEG5 Audio)
    E_ADJUST_INTERRUPT_MAD,                //< interrupt mad  (for MHEG5 Audio)
    E_ADJUST_AUDIOMUTE,                         ///< audio mute
    E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME,   ///< audio mute during limited time
    E_ADJUST_VOLUME,                        ///< volume
    E_ADJUST_VOLUME_IN_MUTE,
    E_ADJUST_SURROUND,                        ///< surround
    E_ADJUST_AVL,                        ///< AVL
    E_ADJUST_TREBLE,                        ///< Treble
    E_ADJUST_BASS,                        ///< Bass
    E_ADJUST_BALANCE,                        ///< Balance
    E_ADJUST_SET_AUDIOMODE,                ///< Set audio mode
    E_ADJUST_CHANGE_AUDIOMODE,             ///< Change Audio mode
    E_ADJUST_EQUALIZER_BAND,               ///< Equalizer band
    E_ADJUST_SRSWOW,                        ///< SRSWOW
    E_ADJUST_RESET_AUDIOMODE,              ///< Reset audio mode
    E_ADJUST_CHANGE_AUDIOSOURCE,          ///< change audio source
} ADJUST_TVAVFACTOR;

#if 1//(ENABLE_AUDIO_MUTE_CONTROL_NEW)

typedef enum
{
    E_AU_MUTE_CL_PERMANENT          , // For Audio driver
    E_AU_MUTE_CL_MOMENT             , // For Audio driver
    E_AU_MUTE_CL_DURING_LIMITED_TIME,
    E_AU_MUTE_CL_SPDIF_TEMPMUTE     ,
    E_AU_MUTE_CL_INTERNAL_1         , // For Audio driver
    E_AU_MUTE_CL_INTERNAL_2         , // For Audio driver
    E_AU_MUTE_CL_INTERNAL_3         , // For Audio driver
    E_AU_MUTE_CL_INTERNAL_4         , // For Audio driver

    E_AU_MUTE_CL_BYSYNC             , // Check Front-End signal

    E_AU_MUTE_CL_HDMI_AVMUTE        ,
    E_AU_MUTE_CL_HDMI_CEC_ARC       , // This client is only for main speaker

    E_AU_MUTE_CL_MHEGAP             ,
    E_AU_MUTE_CL_PVR                ,
    E_AU_MUTE_CL_CI                 , // This client is for Scart/(spdif?), block audio out by CI
    E_AU_MUTE_CL_CIPVR              ,

    E_AU_MUTE_CL_TTS_Background     , // When TTS speaking, Need mute system sound
    E_AU_MUTE_CL_KTS_BGM            , // When KTS speaking, Need mute system sound

    E_AU_MUTE_CL_BYVCHIP            , // For ATSC-VChip or DVB-ParentControl
    E_AU_MUTE_CL_BLOCK_CHANNEL      , // User can force lock program
    E_AU_MUTE_CL_BLOCK_INPUTSOURCE  , // ATSC-Block inputsource

    E_AU_MUTE_CL_BYUSER             , // IR "Mute" key

    E_AU_MUTE_CL_ALIGN_VIDEO        , // Mute if video mute

    E_AU_MUTE_CL_NUMS,
} EnuAudioMuteClient;
#endif

#define AUDIO_MUTE_CLIENT_TO_MUTEOFF(client)    ((client))
#define AUDIO_MUTE_CLIENT_TO_MUTEON(client)     ((client)|BIT15)

typedef enum
{
    E_AUDIO_PERMANENT_MUTEOFF               = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_PERMANENT),//0x00,
    E_AUDIO_PERMANENT_MUTEON                = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_PERMANENT),//0x01,

    E_AUDIO_MOMENT_MUTEOFF                  = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_MOMENT),//0x10,
    E_AUDIO_MOMENT_MUTEON                   = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_MOMENT),//0x11,

    E_AUDIO_BYUSER_MUTEOFF                  = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_BYUSER),//0x20, // For Mute Key
    E_AUDIO_BYUSER_MUTEON                   = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_BYUSER),//0x21, // For Mute Key

    E_AUDIO_BYSYNC_MUTEOFF                  = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_BYSYNC),//0x30,
    E_AUDIO_BYSYNC_MUTEON                   = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_BYSYNC),//0x31,

    E_AUDIO_BYVCHIP_MUTEOFF                 = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_BYVCHIP),//0x40, // For VChip
    E_AUDIO_BYVCHIP_MUTEON                  = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_BYVCHIP),//0x41, // For VChip

    E_AUDIO_BYBLOCK_MUTEOFF                 = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_BLOCK_CHANNEL),//0x50,
    E_AUDIO_BYBLOCK_MUTEON                  = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_BLOCK_CHANNEL),//0x51,

    E_AUDIO_INTERNAL_1_MUTEOFF              = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_INTERNAL_1),//0x60,
    E_AUDIO_INTERNAL_1_MUTEON               = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_INTERNAL_1),//0x61,

    E_AUDIO_INTERNAL_2_MUTEOFF              = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_INTERNAL_2),//0x70,
    E_AUDIO_INTERNAL_2_MUTEON               = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_INTERNAL_2),//0x71,

    E_AUDIO_INTERNAL_3_MUTEOFF              = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_INTERNAL_3),//0x80,
    E_AUDIO_INTERNAL_3_MUTEON               = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_INTERNAL_3),//0x81,

    E_AUDIO_INTERNAL_4_MUTEOFF              = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_INTERNAL_4),//0x82,
    E_AUDIO_INTERNAL_4_MUTEON               = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_INTERNAL_4),//0x83,

    E_AUDIO_DURING_LIMITED_TIME_MUTEOFF     = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_DURING_LIMITED_TIME),//0x90,
    E_AUDIO_DURING_LIMITED_TIME_MUTEON      = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_DURING_LIMITED_TIME),//0x91,

    E_AUDIO_MHEGAP_MUTEOFF                  = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_MHEGAP),//0xA0,
    E_AUDIO_MHEGAP_MUTEON                   = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_MHEGAP),//0xA1,

    E_AUDIO_CI_MUTEOFF                      = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_CI),//0xB0,
    E_AUDIO_CI_MUTEON                       = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_CI),//0xB1,

    E_AUDIO_HDMI_AVMUTE_MUTEOFF             = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_HDMI_AVMUTE),//0xC0, // For HDMI AVMute
    E_AUDIO_HDMI_AVMUTE_MUTEON              = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_HDMI_AVMUTE),//0xC1, // For HDMI AVMute

    E_AUDIO_UI_FUNC_MUTEOFF                 = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_BLOCK_INPUTSOURCE),//0xD0, // For UI-Menu function/ ATSC-InputBlock/...
    E_AUDIO_UI_FUNC_MUTEON                  = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_BLOCK_INPUTSOURCE),//0xD1, // For UI-Menu function/ ATSC-InputBlock/...

    // This client is only for main speaker
    E_AUDIO_HDMI_CEC_ARC_MUTEOFF            = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_HDMI_CEC_ARC),//0xD2, // For HDMI CEC ARC
    E_AUDIO_HDMI_CEC_ARC_MUTEON             = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_HDMI_CEC_ARC),//0xD3, // For HDMI CEC ARC

    E_AUDIO_SPDIF_TEMPMUTE_MUTEOFF          = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_SPDIF_TEMPMUTE),//0xD4, // For Spdif Out Mute when PCM->NON PCM
    E_AUDIO_SPDIF_TEMPMUTE_MUTEON           = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_SPDIF_TEMPMUTE),//0xD5, // For Spdif Out Mute when PCM->NON PCM

    E_AUDIO_TTS_Background_MUTEOFF          = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_TTS_Background),//0xF0, // TTS mute background audio
    E_AUDIO_TTS_Background_MUTEON           = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_TTS_Background),//0xF1,

    E_AUDIO_CIPVR_MUTEOFF                   = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_CIPVR),//0xF2, // for cipvr audio
    E_AUDIO_CIPVR_MUTEON                    = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_CIPVR),//0xF3,

#if ENABLE_KEY_TO_SPEECH
    E_AUDIO_KTS_BGM_MUTEOFF                 = AUDIO_MUTE_CLIENT_TO_MUTEOFF(E_AU_MUTE_CL_KTS_BGM),//0xF4, // KTS mute background audio
    E_AUDIO_KTS_BGM_MUTEON                  = AUDIO_MUTE_CLIENT_TO_MUTEON(E_AU_MUTE_CL_KTS_BGM),//0xF5,
#endif
} AUDIOMUTETYPE;

// Audio source type
typedef enum
{
    E_AUDIOSOURCE_MPEG,            ///< Audio source MPEG
    E_AUDIOSOURCE_AC3,             ///< Audio source AC3
    E_AUDIOSOURCE_ATV,             ///< Audio source ATV
    E_AUDIOSOURCE_CVBS1,           ///< Audio source CVBS1
    E_AUDIOSOURCE_CVBS2,           ///< Audio source CVBS2
    E_AUDIOSOURCE_CVBS3,           ///< Audio source CVBS3
    E_AUDIOSOURCE_SVIDEO1,         ///< Audio source SVideo1
    E_AUDIOSOURCE_SVIDEO2,         ///< Audio source SVideo2
    E_AUDIOSOURCE_SCART1,          ///< Audio source SCART1
    E_AUDIOSOURCE_SCART2,          ///< Audio source SCART2
    E_AUDIOSOURCE_PC,              ///< Audio source PC
    E_AUDIOSOURCE_YPbPr,           ///< Audio source YPbPr
    E_AUDIOSOURCE_YPbPr2,          ///< Audio source YPbPr
    E_AUDIOSOURCE_HDMI,            ///< Audio source HDMI
    E_AUDIOSOURCE_HDMI2,           ///< Audio source HDMI
    E_AUDIOSOURCE_HDMI3,           ///< Audio source HDMI
    E_AUDIOSOURCE_DVI,             ///< Audio source HDMI
    E_AUDIOSOURCE_DVI2,            ///< Audio source HDMI
    E_AUDIOSOURCE_DVI3,            ///< Audio source HDMI
#if(ENABLE_FM_RADIO)
    E_AUDIOSOURCE_RADIO,            ///< Audio source RADIO
#endif
    E_AUDIOSOURCE_INVALID          ///< Invalid Audio source
} AUDIOSOURCE_TYPE;

typedef enum
{
    E_AUDIOMUTESOURCE_MPEG         = E_AUDIOSOURCE_MPEG,
    E_AUDIOMUTESOURCE_AC3          = E_AUDIOSOURCE_AC3,
    E_AUDIOMUTESOURCE_ATV          = E_AUDIOSOURCE_ATV,
    E_AUDIOMUTESOURCE_CVBS1        = E_AUDIOSOURCE_CVBS1,
    E_AUDIOMUTESOURCE_CVBS2        = E_AUDIOSOURCE_CVBS2,
    E_AUDIOMUTESOURCE_SVIDEO1      = E_AUDIOSOURCE_SVIDEO1,
    E_AUDIOMUTESOURCE_SVIDEO2      = E_AUDIOSOURCE_SVIDEO2,
    E_AUDIOMUTESOURCE_SCART1       = E_AUDIOSOURCE_SCART1,
    E_AUDIOMUTESOURCE_SCART2       = E_AUDIOSOURCE_SCART2,
    E_AUDIOMUTESOURCE_PC           = E_AUDIOSOURCE_PC,
    E_AUDIOMUTESOURCE_YPbPr        = E_AUDIOSOURCE_YPbPr,
    E_AUDIOMUTESOURCE_HDMI         = E_AUDIOSOURCE_HDMI,
#if(ENABLE_FM_RADIO)
    E_AUDIOMUTESOURCE_RADIO         = E_AUDIOSOURCE_RADIO,
#endif
    E_AUDIOMUTESOURCE_ACTIVESOURCE = 0xFF
} AUDIOMUTESOURCE_TYPE;

///< Audio ChannelMode Decoder type
typedef enum
{
    E_AUDIOSTREAM_INVALID_                  = 0x00,
    E_AUDIOSTREAM_MPEG_                     = 0x01,
    E_AUDIOSTREAM_AC3_                      = 0x02,
    E_AUDIOSTREAM_MPEG_AD_                  = 0x03,
    E_AUDIOSTREAM_MPEG4_                    = 0x04,
    E_AUDIOSTREAM_AAC_                      = 0x05,
    E_AUDIOSTREAM_AC3P_                     = 0x06,
    E_AUDIOSTREAM_AC3_AD_                   = 0x07,
    E_AUDIOSTREAM_AC3P_AD_                  = 0x08,
    E_AUDIOSTREAM_AACP_AD_                  = 0x09
} AUDIOSTREAM_TYPE_;

///< Audio ChannelMode
typedef enum
{
    AUDIO_DEC_ACMODE_NOTREADY               = 0x0,
    AUDIO_DEC_ACMODE_DUALMONO               = 0x1,
    AUDIO_DEC_ACMODE_MONO                   = 0x2,
    AUDIO_DEC_ACMODE_STEREO                 = 0x3,
    AUDIO_DEC_ACMODE_MULTICH                = 0x4
} AUDIO_DEC_ChannelMOD_Type;

/* Select audio output mode type */
typedef enum
{
    MSAPI_AUD_DVB_SOUNDMODE_STEREO_,
    MSAPI_AUD_DVB_SOUNDMODE_LEFT_,
    MSAPI_AUD_DVB_SOUNDMODE_RIGHT_,
    MSAPI_AUD_DVB_SOUNDMODE_MIXED_,
} En_DVB_soundModeType_;

//==============================================
/// SPDIF SCMS Mode for CI+, use in SPDIF_GetSCMS
typedef enum
{
    /// SPDIF SCMS mode is Copy Once
    SPDIF_SCMS_CopyOnce                     = 0x00,
    /// SPDIF SCMS mode is Freely
    SPDIF_SCMS_CopyFreely                   = 0x01,
    /// SPDIF SCMS mode is Copy No More
    SPDIF_SCMS_CopyNoMore                   = 0x02,
    /// SPDIF SCMS mode is Copy Never
    SPDIF_SCMS_CopyNever                    = 0x02,
} AUDIO_SPDIF_SCMS_MODE;

/// SPDIF SCMS Mode Setting Value for CI+, use in SPDIF_SetSCMS
typedef enum
{
    /// SPDIF SCMS mode is Freely
    SPDIF_SCMS_CopyFreely_,
    /// SPDIF SCMS mode is Copy No More
    SPDIF_SCMS_CopyNoMore_,
    /// SPDIF SCMS mode is Copy Once
    SPDIF_SCMS_CopyOnce_,
    /// SPDIF SCMS mode is Copy Never
    SPDIF_SCMS_CopyNever_,
} AUDIO_SPDIF_SCMS_MODE_;

#if (ENABLE_DOLBY_BULLETIN24)
typedef enum
{
    DolbyBulletin_EDID_Type1,   //Original EDID
    DolbyBulletin_EDID_Type2,   //Apply amplifier's DD+ SAD
}DolbyBulletinEDIDType;
#endif


//========================AQ bin=================
typedef struct
{
    U8 u8AttackTime;
    U8 u8ReleaseTime;
    U8 u8ClippingLevel;
} ST_AVC_PARA;


typedef struct
{
    U8 u8MainSpeaker;
    U8 u8LineOut;
    U8 u8SifOut;
    U8 u8SpdifOut;
} ST_DEVICE_PRESCALE;

typedef struct
{
    U8  u8Enable;
    U8  u8Gain[8];
    U16 u16Fc[8];  //
    U8  u8Qvalue[8];
} ST_PEQ_SETTING;

typedef struct
{
    U8 u8120Hz;
    U8 u8500Hz;
    U8 u81500Hz;
    U8 u85000Hz;
    U8 u810000Hz;
    U8 u8AVCOnOff;
} ST_SmartSound_Para;


typedef struct
{
    U8 u8InputGain;
    U8 u8OutputGain;
    U8 u8DCGain;
    U8 u8TrubassGain;
    U8 u8SpeakerSize;
    U8 u8Definition;
    U8 u8SurroundLevel;
} ST_SRS_THSD_PARA;


typedef struct
{
    //-----------10bytes
    ST_AVC_PARA stAVCPara;    //  3
    U8 u8BassGain;
    U8 u8TrebleGain;
    U8 u8ToneEffectEnable;
    U8 u8MStarSurroundEnable;
    U8 u8DRCEnable;
    U8 u8DRCClippingLevel;
    U8 bHPFEnable;           //
    //-----------8 bytes.....total 18bytes
    U16 u16HPFFrequency;
    U8  u8HPFQValue;
    U8  u8KGain;
    U8  u8LPFGain;
    U8  u8BGain;
    U8  u8AGain;
    U8  u8NRThreshold;
    //-----------37Bytes.....total 55bytes
    ST_DEVICE_PRESCALE stDevicePrescale;
    ST_PEQ_SETTING stPEQ;
    //-----------30bytes.....total 85bytes
    ST_SmartSound_Para stStandard;
    ST_SmartSound_Para stMovie;
    ST_SmartSound_Para stSports;
    ST_SmartSound_Para stUser;
    ST_SmartSound_Para stVivid;
    //-----------8 bytes.....total 93bytes
    U8 u8SRSonOff;
    ST_SRS_THSD_PARA stSRSPara;
    //-----------202 bytes....total 295bytes
    U16 u16VolumeTable[101];
    U8 u8Dummy[21]; //dummy for feature use
} ST_AQBIN_PARA;


//==============================================


#define ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY 0

//****************************************************************************
// Public attributes.
//****************************************************************************
extern AUDIOSOURCE_TYPE m_eAudioSource;

//============================================================
// AUDIO_SYSTEM RELATIONAL API FUNCTION
//============================================================
//INTERFACE void msAPI_AuSetPowerOn(BOOLEAN bFlag);

BOOLEAN msAPI_AUD_Is_AudSystemBTSC(void);
void msAPI_AUD_Setup_SystemInfo(void);

INTERFACE void msAPI_AUD_PreInitAudio(void);    //Refine power on sequence for earphone & DAC pop noise issue
#if (ENABLE_SUPPORT_AQBIN_FLOW)
INTERFACE void msAPI_Initial_AQBinPara(void);
INTERFACE BOOLEAN msAPI_AQ_loadBin(void);
INTERFACE void msAPI_SetAQBinParaIntoAudio(void);
#endif
INTERFACE void msAPI_AUD_InitAudioSystem(THR_TBL_TYPE code *ThrTbl);

void msAPI_AUD_SIF_SetThreshold(void);


#if 1
#define msAPI_AUD_AdjustAudioFactor(eFactor, wParam1, wParam2) do {            \
    msAPI_AUD_AdjustAudioFactor2(eFactor, wParam1, wParam2);                   \
} while(0)
#else
#define msAPI_AUD_AdjustAudioFactor(eFactor, wParam1, wParam2) do { \
    printf("\n %lu:%s ", __LINE__, __FILE__);                       \
    if (eFactor == E_ADJUST_AUDIOMUTE)                              \
    {                                                               \
        msDebug_ANSI_SetColorText(E_FONT_COLOR_RED);                \
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW);  \
        printf("\n >> msAPI_AUD_AdjustAudioFactor");                \
        printf("(AUDIOMUTE, 0x%x, 0x%x)", wParam1, wParam2);        \
        msAPI_AUD_PrintMuteClient();                                \
        msDebug_ANSI_AllAttrOffText();                              \
    }                                                               \
    msAPI_AUD_AdjustAudioFactor2(eFactor, wParam1, wParam2);        \
} while(0)
#endif
INTERFACE void msAPI_AUD_AdjustAudioFactor2(ADJUST_TVAVFACTOR eFactor, WORD wParam1, WORD wParam2);

INTERFACE BOOLEAN msAPI_AUD_IsAudioMuted(void);
void msAPI_AUD_PrintMuteClient(void);
BOOLEAN msAPI_AUD_SetAllAudioUnmute(void);
BOOLEAN msAPI_AUD_StoreRestoreAudioMuteStatus(BOOLEAN bStoreStatus, MS_U32 *u32AudioStatus);

INTERFACE BOOLEAN msAPI_AUD_IsAudioMutedByUser(void);
INTERFACE void msAPI_AUD_CheckExpirationOfAudioMute(void);
#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
INTERFACE void msAPI_AUD_SetByPassDelayFlag(BOOLEAN flag);
#endif
INTERFACE void msAPI_AUD_SwitchAudioDSPSystem(AUDIO_DSP_SYSTEM eAudioDSPSystem);
INTERFACE AUDIO_DEC_ChannelMOD_Type msAPI_AUD_DECODER_GetChannelMode(AUDIOSTREAM_TYPE_ eAudioStreamType);
INTERFACE void msAPI_AUD_DECODER_SetOutputMode(En_DVB_soundModeType_ mode);
INTERFACE En_DVB_soundModeType_ msAPI_AUD_DECODER_GetCurrOutputMode(void);
INTERFACE BOOLEAN msAPI_AUD_DECODER_GetMAD_LOCK(void);
INTERFACE MS_U32 msAPI_AUD_DECODER_GetMAD_PCMBufLevel(AUDIOSTREAM_TYPE_ eAudioStreamType);
INTERFACE MS_U32 msAPI_AUD_GetDspMadBaseAddr(MS_U8);
INTERFACE void msAPI_AUD_MPEG_Monitor(void);

//============================================================
// AUDIO_ATV RELATIONAL API FUNCTION
//============================================================
INTERFACE AUDIOSTANDARD_TYPE msAPI_AUD_GetAudioStandard(void);
INTERFACE void msAPI_AUD_SetAudioStandard(AUDIOSTANDARD_TYPE eStandard);
INTERFACE void msAPI_AUD_ForceAudioStandard(AUDIOSTANDARD_TYPE eStandard);
INTERFACE AUDIOSOURCE_TYPE msAPI_AUD_GetAudioSource(void);
#if 0//(VIF_TUNER_TYPE==1)
INTERFACE void msAPI_AUD_ChangeProgSetAudioStandard(AUDIOSTANDARD_TYPE eStandard);
#endif
INTERFACE AUDIOSTANDARD_TYPE msAPI_AUD_GetResultOfAutoStandardDetection(void);
INTERFACE void msAPI_AUD_ForceAudioMode(AUDIOMODE_TYPE eAudioMode);
INTERFACE AUDIOMODE_TYPE msAPI_AUD_ChangeAudioMode(void);
INTERFACE BOOLEAN msAPI_AUD_IsAudioModeChanged(void);
INTERFACE BOOLEAN msAPI_AUD_IsAudioDetected(void);

//=============================================================
// AUDIO_HDMI RELATIONAL API FUNCTION
//=============================================================
INTERFACE void msAPI_AUD_HDMI_SetNonpcm(BYTE nonPCM_en);
INTERFACE void msAPI_AUD_HDMI_SetDownSample(void);

//=============================================================
// AUDIO_SPDIF RELATIONAL API FUNCTION
//=============================================================
INTERFACE void msAPI_AUD_SPDIF_SetSCMS(AUDIO_SPDIF_SCMS_MODE_ scms_mode);
INTERFACE AUDIO_SPDIF_SCMS_MODE msAPI_AUD_SPDIF_GetSCMS(void);

//=============================================================
// AUDIO_SOUND RELATIONAL API FUNCTION
//=============================================================
INTERFACE void MApi_AUDIO_SetMute( U8 u8Path, BOOLEAN EnMute);
INTERFACE void MApi_AUDIO_AseSetBinAddress(MS_U8 u8Index, MS_U32 BinAddr);
INTERFACE void MApi_AUDIO_SetNormalPath(AUDIO_PATH_TYPE path, AUDIO_INPUT_TYPE input, AUDIO_OUTPUT_TYPE output);

//=============================================================
// AUDIO_OTHERS FUNCTION (Temp)
//=============================================================
void msAPI_AUD_SetAudioSource(AUDIOSOURCE_TYPE eSource);
void msApi_AUD_SIF_Shift(En_AUD_VIF_Type type);
//=============================================================
// AUDIO_Miscellany FUNCTION
//=============================================================
void msAPI_AUD_I2S_Amp_Reset(void);
void msAPI_AUD_I2S_Amp_UnReset(void);
void msAPI_AUD_SW_Reset(void);

//=============================================================
// AUDIO_Miscellany FUNCTION
//=============================================================
INTERFACE void msAPI_AUD_SetSpdifMuteDuringLimitedTime(WORD w1ms);
INTERFACE void msAPI_AUD_CheckExpirationOfSpdifMute(void);
INTERFACE void MW_AUD_AudioProcessor(void);
INTERFACE void MW_AUD_SetMadAddress(void);
INTERFACE void MW_AUD_SetSoundMute(SOUND_MUTE_SOURCE eSoundMuteSource, SOUND_MUTE_TYPE eOnOff);
INTERFACE void msAPI_AUD_SetPEQ(MS_U8 Band, MS_U8 Gain, MS_U8 Foh, MS_U8 Fol, MS_U8 QValue);
#if 1//(CHIP_FAMILY_TYPE != CHIP_FAMILY_EDEN)
INTERFACE BOOLEAN msAPI_AUD_SetPEQBand(MS_U8 Band, MS_S16 Gain, MS_U16 Fo, MS_U8 QValue, MS_BOOL Enable, AUDIO_PRECISION_TYPE Precision);
INTERFACE BOOLEAN msAPI_AUD_SetHLPF(MS_U8 type, MS_U16 Fo, MS_U8 QValue);
INTERFACE BOOLEAN msAPI_AUD_SetTONE(MS_U8 Type, MS_S16 Gain, MS_U16 Fo, MS_U8 QValue);
#endif

#if 0//ENABLE_ATV_AUDIOCHECK_IN_OTHER_SRC
//for CheckAudioStandard in other source except DTV and ATV.
INTERFACE void Mapi_ATV_AudioProcessor(void);
#endif
void msAPI_Audio_Standard_and_SoundMode_Task(void);

//=============================================================

#if (ENABLE_DOLBY_BULLETIN24)
INTERFACE void msAPI_DolbyBulletin24_process_EDID(void);
INTERFACE void msAPI_DolbyBulletin24_Init(void);
INTERFACE void msAPI_DolbyBulletin24_receive_SAD(U8* pu8SAD, U8 u8Len);
INTERFACE void msAPI_DolbyBulletin24_remove_SAD(void);
#endif

//=============================================================
// AUDIO_BENCH_CODE
//=============================================================
#ifdef BENCH_CODE_USAGE
void msAPI_AUD_Bench_Check_Main(void);
BOOLEAN  msAPI_AUD_Bench_Check_Counter(void);
#endif


const char* msAPI_AUD_Get_StdString(AUDIOSTANDARD_TYPE eAudioStd);

//=============================================================

#define ENABLE_DEBUG_AU_PATH_MUTE  1
#if( ENABLE_DEBUG_AU_PATH_MUTE )
typedef enum
{
    AU_PATH_OUT_SPEAKER = BIT0,
    AU_PATH_OUT_HP      = BIT1,
    AU_PATH_OUT_SPDIF   = BIT2,
    AU_PATH_OUT_LINEOUT = BIT3,
    AU_PATH_OUT_SIFOUT  = BIT4,
    AU_PATH_IN_MAIN     = BIT5,
} EnuAuPathMute;
void msAPI_Audio_Set_PathMuteStatus(U32 u32PathId, BOOLEAN bMute);
U32 msAPI_Audio_Get_PathMuteStatus(void);

    #define DEBUG_AU_PATH_MUTE(x)   x

#else
    #define DEBUG_AU_PATH_MUTE(x)

#endif

//=============================================================

#define ENABLE_DEBUG_AU_LOAD_CODE   0

#if(ENABLE_DEBUG_AU_LOAD_CODE)
    #define DEBUG_AU_LOAD_CODE(x)   do{ PRINT_CURRENT_LINE(); x; } while(0)
#else
    #define DEBUG_AU_LOAD_CODE(x)
#endif

void msAPI_AUD_Set_CurDspSystem( AUDIO_DSP_SYSTEM eAudioDSPSystem );
AUDIO_DSP_SYSTEM msAPI_AUD_Get_CurDspSystem(void);

//=============================================================

#if 1//(ENABLE_AUDIO_MUTE_CONTROL_NEW)
BOOLEAN msAPI_AUD_Is_MuteClientActive(EnuAudioMuteClient eMuteClient);

#define AU_MUTE_DISABLE 0
#define AU_MUTE_ENABLE  1

void msAPI_AUD_Set_Mute(EnuAudioMuteClient eMuteClient, BOOLEAN bMute, AUDIOMUTESOURCE_TYPE eAudioMuteSource);

#endif //(ENABLE_AUDIO_MUTE_CONTROL_NEW)
//=============================================================

#undef INTERFACE
#endif

