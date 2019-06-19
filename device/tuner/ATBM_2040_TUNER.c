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


/**********************************************************************
 Copyright (c) 2006-2009 MStar Semiconductor, Inc.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 MStar Semiconductor Inc. and be kept in strict confidence
 (MStar Confidential Information) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of MStar Confidential
 Information is unlawful and strictly prohibited. MStar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.

* Class : device_tuner_MXL661
* File  : device_tuner_MXL661.cpp
**********************************************************************/
#if 0
#include <stdio.h>
#include "debug.h"
#include "device_tuner_mxl661.h"
#include "mapi_i2c_devTable.h"
#include "mapi_i2c.h"
#include "mapi_interface.h"
#include "mapi_vif_datatype.h"
#include "mapi_audio_datatype.h"
#include "mapi_demodulator_datatype.h"

#include "MxL661/MaxLinearDataTypes.h"
#include "MxL661/MxL661_OEM_Drv.c"
#include "MxL661/MxL661_TunerApi.c"
#include "MxL661/MxL661_TunerCfg.c"
#include "MxL661/MxL661_TunerSpurTable.c"
#endif
#include "drvIIC.h"

#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalVar.h"
#include "MApp_TopStateMachine.h"


#define MXL661_I2C_ADDR                       0xC0

#define TUNER_PLL_STABLE_TIME                   30
#define SECAM_L_PRIME_TUNER_PLL_STABLE_TIME     35

#define TUNER_DTV_IF_FREQ_KHz      DTV_TUNER_IF_FREQ_KHz
#define TUNER_DTV_IQ_SWAP           0

#define TUNER_VHF_LOWMIN_FREQ             47000L
#define TUNER_VHF_LOWMAX_FREQ             160000L
#define TUNER_VHF_HIGHMIN_FREQ            160000L
#define TUNER_VHF_HIGHMAX_FREQ            445000L
#define TUNER_UHF_MIN_FREQ_UK             445000L
#define TUNER_UHF_MIN_FREQ                434000L
#define TUNER_UHF_MAX_FREQ                894000L

//define lock range of AFT value
#define MIN_AFT_VALUE                          24
#define MAX_AFT_VALUE                         38
#define FINE_MIN_AFT_VALUE                  30
#define CENTER_AFT_VALUE                    31
#define FINE_MAX_AFT_VALUE                 2
#define MAX_ZIG_ZAG_NUM                      7
//#define NTSC_TUNER_PLL_STABLE_TIME     20       //normally is smaller then 6ms
#define TUNER_HIBYTE(w)                       ((U8) (((U16) (w) >> 8) & 0xFF))
#define TUNER_LOBYTE(w)                      ((U8) (w & 0xFF))
#if 0
#define VIF_TUNER_TYPE 1     // 0: RF Tuner; 1: Silicon Tuner
#define VIF_CR_RATE_B                   0x000ABDA1 // 5+2.25M   // [21:0], CR_RATE for 6.4 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                     0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x000B7B42  //5+2.75M         // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                    0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000B7B42// //5+2.75M           // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                    0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000B7B42 //5+2.75M          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                     0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x000B7B42 // 5+2.75M         // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                     0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x000B7B42// //5+2.75M          // [21:0], CR_RATE for 7.02 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                    0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x000A0000// //5+1.75M         // [21:0], CR_RATE for 1.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                    0                   // Video carrier position; 0: high side; 1:low side


#define VIF_SOS_21_FILTER_C0            0x032D
#define VIF_SOS_21_FILTER_C1            0x069B
#define VIF_SOS_21_FILTER_C2            0x0209
#define VIF_SOS_21_FILTER_C3            0x04D3
#define VIF_SOS_21_FILTER_C4            0x015C

#define VIF_SOS_22_FILTER_C0            0x034D
#define VIF_SOS_22_FILTER_C1            0x068E
#define VIF_SOS_22_FILTER_C2            0x01F8
#define VIF_SOS_22_FILTER_C3            0x04B3
#define VIF_SOS_22_FILTER_C4            0x017A

#define VIF_SOS_31_FILTER_C0            0x0217
#define VIF_SOS_31_FILTER_C1            0x0754
#define VIF_SOS_31_FILTER_C2            0x00AC
#define VIF_SOS_31_FILTER_C3            0x05E9
#define VIF_SOS_31_FILTER_C4            0x0200

#define VIF_SOS_32_FILTER_C0            0x0000
#define VIF_SOS_32_FILTER_C1            0x0000
#define VIF_SOS_32_FILTER_C2            0x0000
#define VIF_SOS_32_FILTER_C3            0x0000
#define VIF_SOS_32_FILTER_C4            0x0200


//B_Stereo_A2 ========================
// 1.75Mhz
#define N_A1_C0_B_A2 0x03A4
#define N_A1_C1_B_A2 0x063C
#define N_A1_C2_B_A2 0x0421
// 1.51Mhz
#define N_A2_C0_B_A2 0x03AB
#define N_A2_C1_B_A2 0x063C
#define N_A2_C2_B_A2 0x0419
// 8.75Mhz
#define S_11_C0_B_A2 0x011B
#define S_11_C1_B_A2 0x063C
#define S_11_C2_B_A2 0x0200
#define S_11_C3_B_A2 0x06D3
#define S_11_C4_B_A2 0x0200
// 1.75Mhz
#define S_12_C0_B_A2 0x03A4
#define S_12_C1_B_A2 0x063C
#define S_12_C2_B_A2 0x0200
#define S_12_C3_B_A2 0x0421
#define S_12_C4_B_A2 0x0200

//B_Mono_NICAM ====================
// 1.75Mhz
#define N_A1_C0_B_NICAM 0x03A3
#define N_A1_C1_B_NICAM 0x063C
#define N_A1_C2_B_NICAM 0x0421
// 1.4Mhz
#define N_A2_C0_B_NICAM 0x03AF
#define N_A2_C1_B_NICAM 0x063C
#define N_A2_C2_B_NICAM 0x0415
// 8.75Mhz
#define S_11_C0_B_NICAM 0x011B
#define S_11_C1_B_NICAM 0x063C
#define S_11_C2_B_NICAM 0x0200
#define S_11_C3_B_NICAM 0x06D3
#define S_11_C4_B_NICAM 0x0200
// 1.75Mhz
#define S_12_C0_B_NICAM 0x03A4
#define S_12_C1_B_NICAM 0x063C
#define S_12_C2_B_NICAM 0x0200
#define S_12_C3_B_NICAM 0x0421
#define S_12_C4_B_NICAM 0x0200

//GH_Stereo_A2 =======================
// 2.25Mhz
#define N_A1_C0_GHA2 0x038F
#define N_A1_C1_GHA2 0x063C
#define N_A1_C2_GHA2 0x0436
// 2.01Mhz
#define N_A2_C0_GHA2 0x039A
#define N_A2_C1_GHA2 0x063C
#define N_A2_C2_GHA2 0x042B
// 10.25Mhz
#define S_11_C0_GHA2 0x004D
#define S_11_C1_GHA2 0x063C
#define S_11_C2_GHA2 0x0200
#define S_11_C3_GHA2 0x07AE
#define S_11_C4_GHA2 0x0200
// 2.25Mhz
#define S_12_C0_GHA2 0x038F
#define S_12_C1_GHA2 0x063C
#define S_12_C2_GHA2 0x0200
#define S_12_C3_GHA2 0x0436
#define S_12_C4_GHA2 0x0200

//GH_Mono_NICAM ===================
// 2.25Mhz
#define N_A1_C0_GHMN 0x038F
#define N_A1_C1_GHMN 0x063C
#define N_A1_C2_GHMN 0x0436
// 1.9Mhz
#define N_A2_C0_GHMN 0x039E
#define N_A2_C1_GHMN 0x063C
#define N_A2_C2_GHMN 0x0427
// 10.25Mhz
#define S_11_C0_GHMN 0x004D
#define S_11_C1_GHMN 0x063C
#define S_11_C2_GHMN 0x0200
#define S_11_C3_GHMN 0x07AE
#define S_11_C4_GHMN 0x0200
// 2.25Mhz
#define S_12_C0_GHMN 0x038F
#define S_12_C1_GHMN 0x063C
#define S_12_C2_GHMN 0x0200
#define S_12_C3_GHMN 0x0436
#define S_12_C4_GHMN 0x0200

//DK1_Stero_A2 ======================
// 1.25Mhz
#define N_A1_C0_DK1A2 0x03B3
#define N_A1_C1_DK1A2 0x063C
#define N_A1_C2_DK1A2 0x0411
// 1.49Mhz
#define N_A2_C0_DK1A2 0x03AC
#define N_A2_C1_DK1A2 0x063C
#define N_A2_C2_DK1A2 0x0418
// 9.25Mhz
#define S_11_C0_DK1A2 0x00D7
#define S_11_C1_DK1A2 0x063C
#define S_11_C2_DK1A2 0x0200
#define S_11_C3_DK1A2 0x071B
#define S_11_C4_DK1A2 0x0200
// 1.25Mhz
#define S_12_C0_DK1A2 0x03B3
#define S_12_C1_DK1A2 0x063C
#define S_12_C2_DK1A2 0x0200
#define S_12_C3_DK1A2 0x0411
#define S_12_C4_DK1A2 0x0200

//DK2_Stero_A2 ======================
// 1.25Mhz
#define N_A1_C0_DK2A2 0x03B3
#define N_A1_C1_DK2A2 0x063C
#define N_A1_C2_DK2A2 0x0411
// 1.01Mhz
#define N_A2_C0_DK2A2 0x03B3
#define N_A2_C1_DK2A2 0x063C
#define N_A2_C2_DK2A2 0x040B
// 9.25Mhz
#define S_11_C0_DK2A2 0x00D7
#define S_11_C1_DK2A2 0x063C
#define S_11_C2_DK2A2 0x0200
#define S_11_C3_DK2A2 0x071B
#define S_11_C4_DK2A2 0x0200
// 1.25Mhz
#define S_12_C0_DK2A2 0x03B3
#define S_12_C1_DK2A2 0x063C
#define S_12_C2_DK2A2 0x0200
#define S_12_C3_DK2A2 0x0411
#define S_12_C4_DK2A2 0x0200

//DK3_Stero_A2=====================
// 1.25Mhz
#define N_A1_C0_DK3A2 0x03B3
#define N_A1_C1_DK3A2 0x063C
#define N_A1_C2_DK3A2 0x0411
// 2.01Mhz
#define N_A2_C0_DK3A2 0x039A
#define N_A2_C1_DK3A2 0x063C
#define N_A2_C2_DK3A2 0x042B
// 9.25Mhz
#define S_11_C0_DK3A2 0x00D7
#define S_11_C1_DK3A2 0x063C
#define S_11_C2_DK3A2 0x0200
#define S_11_C3_DK3A2 0x071B
#define S_11_C4_DK3A2 0x0200
// 1.25Mhz
#define S_12_C0_DK3A2 0x03B3
#define S_12_C1_DK3A2 0x063C
#define S_12_C2_DK3A2 0x0200
#define S_12_C3_DK3A2 0x0411
#define S_12_C4_DK3A2 0x0200

//DK_Mono_NICAM===================
// 1.25Mhz
#define N_A1_C0_DKMN 0x03B3
#define N_A1_C1_DKMN 0x063C
#define N_A1_C2_DKMN 0x0411
// 1.9Mhz
#define N_A2_C0_DKMN 0x039E
#define N_A2_C1_DKMN 0x063C
#define N_A2_C2_DKMN 0x0427
// 9.25Mhz
#define S_11_C0_DKMN 0x00D7
#define S_11_C1_DKMN 0x063C
#define S_11_C2_DKMN 0x0200
#define S_11_C3_DKMN 0x071B
#define S_11_C4_DKMN 0x0200
// 1.25Mhz
#define S_12_C0_DKMN 0x03B3
#define S_12_C1_DKMN 0x063C
#define S_12_C2_DKMN 0x0200
#define S_12_C3_DKMN 0x0411
#define S_12_C4_DKMN 0x0200

//Sound : I ===========================
// 1.75Mhz
#define N_A1_C0_I 0x03A4
#define N_A1_C1_I 0x063C
#define N_A1_C2_I 0x0421
// 1.2Mhz
#define N_A2_C0_I 0x03B4
#define N_A2_C1_I 0x063C
#define N_A2_C2_I 0x0410
// 9.75Mhz
#define S_11_C0_I 0x0092
#define S_11_C1_I 0x063C
#define S_11_C2_I 0x0200
#define S_11_C3_I 0x0764
#define S_11_C4_I 0x0200
// 1.75Mhz
#define S_12_C0_I 0x03A4
#define S_12_C1_I 0x063C
#define S_12_C2_I 0x0200
#define S_12_C3_I 0x0421
#define S_12_C4_I 0x0200
//Sound : MN=========================
// 2.25Mhz
#define N_A1_C0_NTSC 0x038F
#define N_A1_C1_NTSC 0x063C
#define N_A1_C2_NTSC 0x0436
// 2.03Mhz
#define N_A2_C0_NTSC 0x0399
#define N_A2_C1_NTSC 0x063C
#define N_A2_C2_NTSC 0x042C
// 8.25Mhz
#define S_11_C0_NTSC 0x015D
#define S_11_C1_NTSC 0x063C
#define S_11_C2_NTSC 0x0200
#define S_11_C3_NTSC 0x068D
#define S_11_C4_NTSC 0x0200
// 2.25Mhz
#define S_12_C0_NTSC 0x038F
#define S_12_C1_NTSC 0x063C
#define S_12_C2_NTSC 0x0200
#define S_12_C3_NTSC 0x0436
#define S_12_C4_NTSC 0x0200

//Sound : L ==========================
// 1.25Mhz
#define N_A1_C0_L 0x03B3
#define N_A1_C1_L 0x063C
#define N_A1_C2_L 0x0411
// 1.9Mhz
#define N_A2_C0_L 0x039E
#define N_A2_C1_L 0x063C
#define N_A2_C2_L 0x0427
// 9.25Mhz
#define S_11_C0_L 0x00D7
#define S_11_C1_L 0x063C
#define S_11_C2_L 0x0200
#define S_11_C3_L 0x071B
#define S_11_C4_L 0x0200
// 1.25Mhz
#define S_12_C0_L 0x03B3
#define S_12_C1_L 0x063C
#define S_12_C2_L 0x0200
#define S_12_C3_L 0x0411
#define S_12_C4_L 0x0200

//End of Table===================
#endif
#define IF_OUT_CFG_GAIN_LEVEL_DVB        6 //4
#define IF_OUT_CFG_GAIN_LEVEL_DVB_T2     6
#define IF_OUT_CFG_GAIN_LEVEL_DTMB       10 // 15 //for external ATBM886x DTMB demod must use 15
#define IF_OUT_CFG_GAIN_LEVEL_ISDB       12//6 //13 update by sj.rao for RF
#define IF_OUT_CFG_GAIN_LEVEL_ATV_NORMAL 9 //8 //7
#define IF_OUT_CFG_GAIN_LEVEL_ATV_SCAN   9
#define IF_OUT_CFG_GAIN_LEVEL_ATV_SECAM  6//8
#define IF_OUT_CFG_GAIN_LEVEL_ATSC       12
#define IF_OUT_CFG_GAIN_LEVEL_QAM        8


#define DBG_TUNER(x)   // x

ATBM2040InitConfig_t InitConfig;
ATBM2040CfgCMD_t Config;
bool m_bInATVScanMode;
bool m_bLastInATVScanMode;
bool m_bNeedResetAGCMode;
EN_TUNER_MODE m_eLastTunerMode;
U8 m_u8LastOtherMode;
static U8 m_bDeviceBusy = 0;
U32 DevId = 0;
static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

extern IF_FREQ MDrv_IFDM_GetIF(void);
static BOOLEAN DTV_SetTune(double FreqMHz, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode);
static BOOLEAN ATV_SetTune(UINT32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,UINT8 u8OtherMode);

// #define ATV_VC_B   7250L
const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03B7,0x0628,0x0421,
 0x03BF,0x0628,0x0419,
 0x0121,0x0628,0x0200,0x06D3,0x0200,
 0x03B7,0x0628,0x0200,0x0421,0x0200
};

// #define ATV_VC_B   7250L
const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03B7,0x0628,0x0421,
 0x03C3,0x0628,0x0415,
 0x0121,0x0628,0x0200,0x06D3,0x0200,
 0x03B7,0x0628,0x0200,0x0421,0x0200

};

// #define ATV_VC_GH  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x03A3,0x0628,0x0436,
 0x03AD,0x0628,0x042B,
 0x004F,0x0628,0x0200,0x07AE,0x0200,
 0x03A3,0x0628,0x0200,0x0436,0x0200
};

// #define ATV_VC_GH  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x03A3,0x0628,0x0436,
 0x03B2,0x0628,0x0427,
 0x004F,0x0628,0x0200,0x07AE,0x0200,
 0x03A3,0x0628,0x0200,0x0436,0x0200
};

// #define ATV_VC_DK  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03C7,0x0628,0x0411,
 0x03C0,0x0628,0x0418,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// #define ATV_VC_DK  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03C7,0x0628,0x0411,
 0x03CC,0x0628,0x040B,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// #define ATV_VC_DK  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03C7,0x0628,0x0411,
 0x03AD,0x0628,0x042B,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// #define ATV_VC_DK  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03C7,0x0628,0x0411,
 0x03B2,0x0628,0x0427,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// #define ATV_VC_I   7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x03B7,0x0628,0x0421,
 0x03C8,0x0628,0x0410,
 0x0096,0x0628,0x0200,0x0764,0x0200,
 0x03B7,0x0628,0x0200,0x0421,0x0200
};

// #define ATV_VC_MN  6750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x03A3,0x0628,0x0436,
 0x03AD,0x0628,0x042C,
 0x0164,0x0628,0x0200,0x068D,0x0200,
 0x03A3,0x0628,0x0200,0x0436,0x0200
};

// #define ATV_VC_MN  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_MN_7750[16]=
{
 0x036B,0x0628,0x0470,
 0x0379,0x0628,0x0462,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x036B,0x0628,0x0200,0x0470,0x0200
};

// #define ATV_VC_L   7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03C7,0x0628,0x0411,
 0x03B2,0x0628,0x0427,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// #define ATV_VC_LL  7750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x03C7,0x0628,0x0411,
 0x03B2,0x0628,0x0427,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};


void device_tuner_ATBM2040(void)
{
    m_bDeviceBusy = 0;
    m_bInATVScanMode = FALSE;
    m_bLastInATVScanMode = m_bInATVScanMode;
    m_eLastTunerMode = E_TUNER_INVALID;
    m_u8LastOtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;
}

#if 0
MAPI_BOOL device_tuner_MXL661::TunerInit(void)
{
    if (m_bDeviceBusy == 0)
        Connect();

    return MAPI_TRUE;
}
#endif

static BOOLEAN Connect(void)
{

    if (m_bDeviceBusy==1)
        return TRUE;

    device_tuner_ATBM2040();


     ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;

    /*Get the default configuration from ATBM2040 SDK. */
    if(ATBM2040_NO_ERROR != ATBM2040DefaultCfgGet(&InitConfig))
    {
    	printf("Error! ATBM2040DefaultCfgGet\n");
    	return FALSE;
    }
    /*Change some setting according to actual requirement.*/
	InitConfig.I2CParam.I2CSlaveAddr = 0xC0;
	InitConfig.I2CParam.Param = 0; /*user parameter, which may be used in ATBM2040I2CRead/Write. */
    InitConfig.OSCCap.CalibValue = 0x10; /*OSC PPM calibration, from 0x00 to 0x1F. The larger the value, the higher the clock frequency*/
    InitConfig.Mode = ATBM2040_SIGNAL_MODE_DTMB;
    InitConfig.DtvIFOut.IFOutFreqHz = 5000000;//5MHz;
    InitConfig.DtvIFOut.IFOutLevel = ATBM2040_IF_OUT_LEVEL4;	
    InitConfig.AtvIFOut.IFOutFreqHz = 5000000;//5MHz;
    InitConfig.AtvIFOut.IFOutLevel = ATBM2040_IF_OUT_LEVEL2;
    /*Initialize with custumer parameters.*/
    printf("! ATBM2040Init QQQQ\n");
    ret = ATBM2040Init(DevId,&InitConfig);
    if(ATBM2040_NO_ERROR != ret)
    {
        printf("Error! ATBM2040Init\n");
        return FALSE;
    }
    printf("! ATBM2040Init End\n");

    m_eLastTunerMode = E_TUNER_INVALID;
    m_u8LastOtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

    m_bDeviceBusy=1;

    return TRUE;
}

#define DEBUG_ATV_TUNE(x)   x

char* _Tuner_Get_RFBANDStr(RFBAND eBand)
{
    switch(eBand)
    {
        case E_RFBAND_VHF_LOW:
            return "VHF-L";

        case E_RFBAND_VHF_HIGH:
            return "VHF-H";

        case E_RFBAND_UHF:
            return "UHF";

        default:
            break;
    }

    return "Unknown";
}

/*
/// the tuner mode
typedef enum
{
    /// DTV, DVBT
    E_TUNER_DTV_DVB_T_MODE = 0x00,
    /// DTV, DVBC
    E_TUNER_DTV_DVB_C_MODE ,
    /// DTV, DVBS
    E_TUNER_DTV_DVB_S_MODE ,
    /// DTV, DTMB
    E_TUNER_DTV_DTMB_MODE ,
    /// DTV, ATSC
    E_TUNER_DTV_ATSC_MODE ,
    /// ATV, PAL
    E_TUNER_ATV_PAL_MODE ,
    /// ATV, SECAM-L'
    E_TUNER_ATV_SECAM_L_PRIME_MODE ,
    /// ATV, NTSC
    E_TUNER_ATV_NTSC_MODE ,
    /// DTV, ISDB
    E_TUNER_DTV_ISDB_MODE ,
    /// DTV, DVBT2
    E_TUNER_DTV_DVB_T2_MODE,
    /// ATV, SECAM-L
    E_TUNER_ATV_SECAM_L_MODE ,
    /// ATV, SECAM-L
    E_TUNER_DTV_QAM_US_MODE ,
    /// invalid
    E_TUNER_INVALID
} EN_TUNER_MODE;
*/
char* _Tuner_Get_TunerModeStr(EN_TUNER_MODE eMode)
{
    switch(eMode)
    {
        case E_TUNER_DTV_ATSC_MODE:
            return "ATSC";

        case E_TUNER_ATV_PAL_MODE:
            return "PAL";

        case E_TUNER_ATV_NTSC_MODE:
            return "NTSC";

        default:
            break;
    }

    return "Unknown";
}

/*
/// Audio SIF Standard Type
typedef enum
{
    ///< Audio standard BG
    E_AUDIOSTANDARD_BG_                     = 0x00,
    ///< Audio standard BG A2
    E_AUDIOSTANDARD_BG_A2_                  = 0x01,
    ///< Audio standard BG NICAM
    E_AUDIOSTANDARD_BG_NICAM_               = 0x02,
    ///< Audio standard I
    E_AUDIOSTANDARD_I_                      = 0x03,
    ///< Audio standard DK
    E_AUDIOSTANDARD_DK_                     = 0x04,
    ///< Audio standard DK1 A2
    E_AUDIOSTANDARD_DK1_A2_                 = 0x05,
    ///< Audio standard DK2 A2
    E_AUDIOSTANDARD_DK2_A2_                 = 0x06,
    ///< Audio standard DK3 A2
    E_AUDIOSTANDARD_DK3_A2_                 = 0x07,
    ///< Audio standard DK NICAM
    E_AUDIOSTANDARD_DK_NICAM_               = 0x08,
    ///< Audio standard L
    E_AUDIOSTANDARD_L_                      = 0x09,
    ///< Audio standard M
    E_AUDIOSTANDARD_M_                      = 0x0A,
    ///< Audio standard M BTSC
    E_AUDIOSTANDARD_M_BTSC_                 = 0x0B,
    ///< Audio standard M A2
    E_AUDIOSTANDARD_M_A2_                   = 0x0C,
    ///< Audio standard M EIA J
    E_AUDIOSTANDARD_M_EIA_J_                = 0x0D,
#if (ENABLE_FM_RADIO)
    ///< Audio standard FM radio
    E_AUDIOSTANDARD_FM_                       = 0x0E,
#endif
    ///< Not Audio standard
    E_AUDIOSTANDARD_NOTSTANDARD_            = 0x0F
} AUDIOSTANDARD_TYPE_;
*/
char* _Tuner_Get_AtvOtherModeStr(U8 u8OtherMode)
{
    switch(u8OtherMode)
    {
        case E_AUDIOSTANDARD_I_:
            return "AU_I";

        case E_AUDIOSTANDARD_DK_:
            return "AU_DK";

        case E_AUDIOSTANDARD_M_:
            return "AU_M";

        default:
            break;
    }

    return "Unknown";
}

static BOOLEAN ATV_SetTune( U32 u32FreqKHz, RFBAND eBand, EN_TUNER_MODE eMode, U8 u8OtherMode )
{
    DEBUG_ATV_TUNE( printf("[ATBM2040]ATV_SetTune(u32FreqKHz=%u, eBand=%u(%s), eMode=%u(%s), u8Other=%u(%s))\n", (U32)u32FreqKHz,
        eBand, _Tuner_Get_RFBANDStr(eBand),
        eMode, _Tuner_Get_TunerModeStr(eMode),
        u8OtherMode, _Tuner_Get_AtvOtherModeStr(u8OtherMode)
        ); );

    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    U32 BandWidthKHz = 8000;
    U32 IFOutFreqHz = 5000000;
    BOOL LockStatus;
    SINT32 RSSI_;
    ATBM2040_SPECTRUM_MODE_e SpectrumMode = ATBM2040_SPECTRUM_INVERT;
    ATBM2040CfgCMD_t Atbm2040Cfg;

    if (m_bDeviceBusy == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }

    switch (eMode)
    {
        case E_TUNER_ATV_PAL_MODE:
        {
            switch(u8OtherMode)
            {
                case E_AUDIOSTANDARD_BG_: //PAL-B
                case E_AUDIOSTANDARD_BG_A2_:
					//m_AtvSys = TV_SYSTEM_B;
					IFOutFreqHz = 5000000; /*5MHz*/
					BandWidthKHz = 7000; /*7M*/					
					u32FreqKHz += 2250;
					break;
                case E_AUDIOSTANDARD_BG_NICAM_: //GH
                    //m_AtvSys = TV_SYSTEM_GH;
					IFOutFreqHz = 5000000; /*5MHz*/
					BandWidthKHz = 8000; /*8M*/					
					u32FreqKHz += 2750;
                    break;
                case E_AUDIOSTANDARD_I_:
                    //m_AtvSys = TV_SYSTEM_I;
					IFOutFreqHz = 5000000;/*5MHz*/
					BandWidthKHz = 8000; /*8M*/					
					u32FreqKHz += 2750;
                    break;
                case E_AUDIOSTANDARD_DK_:
                case E_AUDIOSTANDARD_DK1_A2_:
                case E_AUDIOSTANDARD_DK2_A2_:
                case E_AUDIOSTANDARD_DK3_A2_:
                case E_AUDIOSTANDARD_DK_NICAM_:
                    //m_AtvSys = TV_SYSTEM_DK;
					IFOutFreqHz = 5000000;/*5MHz*/
					BandWidthKHz = 8000; /*8M*/
					u32FreqKHz += 2750;
                    break;
                case E_AUDIOSTANDARD_L_:
                    //m_AtvSys = TV_SYSTEM_L;					
					IFOutFreqHz = 5000000;/*5MHz*/
					BandWidthKHz = 8000; /*8M*/					
					u32FreqKHz += 2750;
                    break;
                case E_AUDIOSTANDARD_M_:
                case E_AUDIOSTANDARD_M_BTSC_:
                case E_AUDIOSTANDARD_M_A2_:
                case E_AUDIOSTANDARD_M_EIA_J_:
                    //m_AtvSys = TV_SYSTEM_M;
					IFOutFreqHz = 5000000;/*5MHz*/
					BandWidthKHz = 6000; /*6M*/					
					u32FreqKHz += 1750;
                    break;
                case E_AUDIOSTANDARD_NOTSTANDARD_:
                default:
                    //m_AtvSys = TV_SYSTEM_DK;					
					IFOutFreqHz = 5000000;/*5MHz*/
					BandWidthKHz = 8000; /*8M*/					
					u32FreqKHz += 2750;
                    break;
            }
        }
	        break;
	    case E_TUNER_ATV_SECAM_L_PRIME_MODE:
	       // m_AtvSys = TV_SYSTEM_LP;
			IFOutFreqHz = 5000000;/*5MHz*/
			BandWidthKHz = 8000; /*8M*/
			u32FreqKHz += 2750;
	        break;
	//        case E_TUNER_ATV_SECAM_L_MODE:
	//            m_AtvSys = si_tv_system_l;
	//            break;
	    case E_TUNER_ATV_NTSC_MODE:
	        //m_AtvSys = TV_SYSTEM_M;			
			IFOutFreqHz = 5000000;/*5MHz*/
			BandWidthKHz = 6000; /*6M*/
			u32FreqKHz += 1750;
	        break;
	    case E_TUNER_DTV_ISDB_MODE:
	    case E_TUNER_DTV_DVB_T_MODE:
	    case E_TUNER_DTV_DVB_C_MODE:
	    case E_TUNER_DTV_DVB_S_MODE:
	    case E_TUNER_DTV_DTMB_MODE:
	    case E_TUNER_DTV_ATSC_MODE:
	    case E_TUNER_DTV_DVB_T2_MODE:
	    default:
	        break;
	}
	
	/*Change the IF output frequency of ATBM2040 according to ATV signal mode*/
	if(IFOutFreqHz != InitConfig.AtvIFOut.IFOutFreqHz)
	{
		Atbm2040Cfg.CfgCmd = ATBM2040_CFG_CMD_ATV_IF_OUT_SETTING;
		Atbm2040Cfg.Cfg.IFOut.IFOutFreqHz = IFOutFreqHz;	
		Atbm2040Cfg.Cfg.IFOut.IFOutLevel = InitConfig.AtvIFOut.IFOutLevel;
		ret = ATBM2040CfgSet(DevId,&Atbm2040Cfg); 
		if(ATBM2040_NO_ERROR != ret)
		{
			printf("Error! ATBM2040CfgSet\n");
			return FALSE;
		}
		InitConfig.AtvIFOut.IFOutFreqHz = IFOutFreqHz;
	}

    ret = ATBM2040ChannelTune(DevId,ATBM2040_SIGNAL_MODE_ATV,u32FreqKHz,BandWidthKHz,SpectrumMode);
    if(ATBM2040_NO_ERROR != ret)
    {
        printf("Error! ATBM2040ChannelTune\n");
        return FALSE;
    }
	/*Check tuner lock status.*/
	ret = ATBM2040GetLockStatus(DevId,&LockStatus);
	if(LockStatus)
	{
		printf("Tuner is locked!\n");
	}
	else
	{
		printf("Tuner is not locked!\n");
	}
    /*Get RSSI*/
    ret = ATBM2040GetRSSI(DevId,&RSSI_);
    if(ATBM2040_NO_ERROR != ret)
    {
        printf("Error! ATBM2040GetRSSI\n");
        return FALSE;
    }
    printf("RSSI:%d dBm\n",RSSI_);


    return TRUE;

}

#define DEBUG_DTV_TUNE(x)   x

static char* _Tuner_Get_DtvBWStr(RF_CHANNEL_BANDWIDTH eBandWidth)
{
    switch(eBandWidth)
    {
        case E_RF_CH_BAND_6MHz:
            return "6M";

        case E_RF_CH_BAND_7MHz:
            return "7M";

        case E_RF_CH_BAND_8MHz:
            return "8M";

        default:
            break;
    }

    return "Unknown";
}

static BOOLEAN DTV_SetTune( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    DEBUG_DTV_TUNE( printf("[ATBM2040]DTV_SetTune(freq=%u, BW=%u(%s), Mode=%u(%s))\n",
        (U32)Freq,
        eBandWidth, _Tuner_Get_DtvBWStr(eBandWidth),
        eMode, _Tuner_Get_TunerModeStr(eMode) ); );
	ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;	
	U32 BandWidthKHz = 8000;/*Default 8M*/
	U32 FreqKHz = Freq*1000;
	
    if (m_bDeviceBusy == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }

	ATBM2040_SIGNAL_MODE_e Mode;
	if(eMode == E_TUNER_DTV_DVB_T_MODE)
    {
		Mode= ATBM2040_SIGNAL_MODE_DVBT;
    }
    else if(eMode == E_TUNER_DTV_DTMB_MODE)
    {
        Mode= ATBM2040_SIGNAL_MODE_DTMB;
    }
    else if(eMode == E_TUNER_DTV_DVB_C_MODE)
    {
		Mode= ATBM2040_SIGNAL_MODE_DVBC;
    }
	else if(eMode == E_TUNER_ATV_PAL_MODE)
    {
		Mode= ATBM2040_SIGNAL_MODE_ATV;
    }
    else
    {
		Mode= ATBM2040_SIGNAL_MODE_DTMB;
    }

	switch(eBandWidth)
	{
		case E_RF_CH_BAND_6MHz: /*6M*/
			BandWidthKHz = 6000;
			break;
		case E_RF_CH_BAND_7MHz: /*7M*/
			BandWidthKHz = 7000;
			break;
		case E_RF_CH_BAND_8MHz: /*8M*/
			BandWidthKHz = 8000;
			break;
		default:
			break;
		
	}
    ret = ATBM2040ChannelTune(DevId,Mode,FreqKHz,BandWidthKHz,ATBM2040_SPECTRUM_INVERT);
    if(ATBM2040_NO_ERROR != ret)
    {
		printf("Error! ATBM2040ChannelTune DTMB\n");
        return FALSE;
    }

    return TRUE;
}

BOOLEAN SetTunerInScanMode(BOOLEAN bScan)
{
    if(m_bInATVScanMode != bScan)
    {
        m_bInATVScanMode = bScan;
        m_bNeedResetAGCMode = TRUE;
    }

    return TRUE;
}



void devTunerInit(void)
{
    if (Connect() == false)
    {
        printf("[Error]MxL661 init fail...\n");
    }
    return;
}

// DTV init..........
void devDigitalTuner_Init(void)
{
    devTunerInit();
    return;
}

void devTunerSetFreq(U32 u32Freq)
{
    //printf("devTunerSetFreq(u32Freq=%u)\n", u32Freq);

    BOOLEAN retb = TRUE;

    if (m_bDeviceBusy == 0)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

    //printf("CurrentStandard=%u\n", CurrentStandard);

#if(ENABLE_ATSC)
    if( CurrentStandard != IF_FREQ_MN )
    {
        printf("\nWarning: IF != IF_FREQ_MN\n");
    }
#endif

    //printf("[CurrentStandard],%d\n",CurrentStandard);
    if(CurrentStandard==IF_FREQ_B)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_G)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_I)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_I_;
    }
    else if  (CurrentStandard==IF_FREQ_DK)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_DK_;
    }
    else if  (CurrentStandard==IF_FREQ_L)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_L_PRIME)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_PRIME_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_MN)
    {
        m_eMode = E_TUNER_ATV_NTSC_MODE;

    #if (ENABLE_FM_RADIO)
        if( UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_FMRADIO )
            m_OtherMode = E_AUDIOSTANDARD_FM_;
        else
    #endif
            m_OtherMode = E_AUDIOSTANDARD_M_;
    }
    else
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }

    DBG_TUNER(printf("[devTunerSetFreq]%s, %d,  m_OtherMode=%d, u32Freq=%ld, CurrentStandard=%d\n",__FILE__,__LINE__,m_OtherMode,u32Freq,CurrentStandard);)

    retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(UINT8)m_OtherMode);

    if (retb == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}

void devDigitalTuner_SetFreq( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{
    BOOLEAN bRet = TRUE;

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%d, eBandWidth=%d, m_eMode=%d\n",(UINT16)Freq,(UINT8)eBandWidth,(UINT8)m_eMode);)

    if (m_bDeviceBusy == 0)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    // Freq (MHz)
    bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}

BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode)
{
    BOOLEAN bRet = TRUE;
    m_eMode = eMode;
    m_OtherMode = OtherMode;

    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);)

    return bRet;
}

// return dbm value, 0dBm~-98dBm
BOOLEAN mdev_GetSignalStrength(float* s16_strength)
{
   //unuse(s16_strength)l
   //s16_strength=100;
   *s16_strength=100;
    return true;
}
