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

#ifndef _MSKEYPAD_H_
#define _MSKEYPAD_H_


//==================================================================================
#include "msKeypad_common.h"
//==================================================================================

#if 0 // Use "msKeypad_common.h"

#include "c_pm_riubase.h"
#include "Board.h"
#include "datatype.h"

#ifdef  _MSKEYPAD_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define KEYPAD_USE_ISR 0

//#define KeypadRepeatTimerCount 1 //100ms based

#define KEYPAD_LV_STABLE_COUNT 10 //used in drvisr
#define KEYPAD_LV_FIRSTTIME_ELASPED_COUNT (KEYPAD_LV_STABLE_COUNT+38)//used in drvisr

enum KEYPAD_ADC_CHANNEL
{
    KEYPAD_ADC_CHANNEL_1 = 0,
    KEYPAD_ADC_CHANNEL_2,
    KEYPAD_ADC_CHANNEL_3,
    KEYPAD_ADC_CHANNEL_4,
    KEYPAD_ADC_CHANNEL_5,
    KEYPAD_ADC_CHANNEL_6,
    KEYPAD_ADC_CHANNEL_7,
    KEYPAD_ADC_CHANNEL_8,
};
#endif // Use "msKeypad_common.h"

#define SAR_SIGNAL_CH                   KEYPAD_ADC_CHANNEL_5
//------------------------------------------------------------------------------
// SAR define
#define REG_SAR_CTRL0                   (RIUBASE_PM_SAR + 0x00*2)
    #define SAR_SINGLE_CH_MSK           (BIT2|BIT1|BIT0)//[2:0] //select channel for single channel modech0~ch7
    #define SAR_LEVEL_TRIGGER           (BIT3) //keypad level trigger enable. 0:  use edge trigger, 1:  use level trigger
    #define SAR_SINGLE_CH_EN            (BIT4) //enable single channel mode. 0: disable1: enable
    #define SAR_MODE_FREERUN            (BIT5) //select sar digital operation mode. 0: one-shot, 1: freerun
    #define SAR_DIGITAL_PWRDN           (BIT6) //sar digital power down
    #define SAR_START                   (BIT7) //sar start signal
#define REG_SAR_CTRL1                   (RIUBASE_PM_SAR + 0x00*2 + 1)
    #define SAR_ADC_PWRDN               (BIT0)
    #define SAR_ADC_FREERUN             (BIT1)
    #define SAR_LOAD_EN                      (BIT6)

#define REG_SAR_SELCH                   (RIUBASE_PM_SAR + 0x00*2 + 1)
    #define SAR_SEL                     (BIT2)
    #define SAR_NCH_EN                  (BIT3)
#define REG_SAR_CKSAMP_PRD              (RIUBASE_PM_SAR + 0x01*2)
#define REG_SAR1_UPB                    (RIUBASE_PM_SAR + 0x20*2)
#define REG_SAR1_LOB                    (RIUBASE_PM_SAR + 0x30*2)
#define REG_SAR2_UPB                    (RIUBASE_PM_SAR + 0x21*2)
#define REG_SAR2_LOB                    (RIUBASE_PM_SAR + 0x31*2)
#define REG_SAR3_UPB                    (RIUBASE_PM_SAR + 0x22*2)
#define REG_SAR3_LOB                    (RIUBASE_PM_SAR + 0x32*2)
#define REG_SAR4_UPB                    (RIUBASE_PM_SAR + 0x23*2)
#define REG_SAR4_LOB                    (RIUBASE_PM_SAR + 0x33*2)
#define REG_SAR5_UPB                    (RIUBASE_PM_SAR + 0x24*2)
#define REG_SAR5_LOB                    (RIUBASE_PM_SAR + 0x34*2)
#define REG_SAR6_UPB                    (RIUBASE_PM_SAR + 0x25*2)
#define REG_SAR6_LOB                    (RIUBASE_PM_SAR + 0x35*2)
#define REG_SAR7_UPB                    (RIUBASE_PM_SAR + 0x26*2)
#define REG_SAR7_LOB                    (RIUBASE_PM_SAR + 0x36*2)
#define REG_SAR8_UPB                    (RIUBASE_PM_SAR + 0x27*2)
#define REG_SAR8_LOB                    (RIUBASE_PM_SAR + 0x37*2)
#define REG_SAR_ADCOUT1                 (RIUBASE_PM_SAR + 0x40*2)
#define REG_SAR_ADCOUT2                 (RIUBASE_PM_SAR + 0x41*2)
#define REG_SAR_ADCOUT3                 (RIUBASE_PM_SAR + 0x42*2)
#define REG_SAR_ADCOUT4                 (RIUBASE_PM_SAR + 0x43*2)
#define REG_SAR_ADCOUT5                 (RIUBASE_PM_SAR + 0x44*2)
#define REG_SAR_ADCOUT6                 (RIUBASE_PM_SAR + 0x45*2)
#define REG_SAR_ADCOUT7                 (RIUBASE_PM_SAR + 0x46*2)
#define REG_SAR_ADCOUT8                 (RIUBASE_PM_SAR + 0x47*2)
    #define MASK_SAR_ADCOUT             (0x3FF)
#define REG_SAR_AISEL                   (RIUBASE_PM_SAR + 0x11*2)
    #define SAR_AISEL_CH0               (BIT0)
    #define SAR_AISEL_CH1               (BIT1)
    #define SAR_AISEL_CH2               (BIT2)
    #define SAR_AISEL_CH3               (BIT3)
    #define SAR_AISEL_CH4               (BIT4)
    #define SAR_AISEL_ALL               (BIT4|BIT3|BIT2|BIT1|BIT0)

#define REG_SAR_GPIOOEN                 (RIUBASE_PM_SAR + 0x11*2 + 1)
    #define SAR_GPIOOEN_CH0             (BIT0)
    #define SAR_GPIOOEN_CH1             (BIT1)
    #define SAR_GPIOOEN_CH2             (BIT2)
    #define SAR_GPIOOEN_CH3             (BIT3)
    #define SAR_GPIOOEN_CH4             (BIT4)
    #define SAR_GPIOOEN_ALL             (BIT4|BIT3|BIT2|BIT1|BIT0)

#define REG_SAR_INT_MASK                (RIUBASE_PM_SAR + 0x14*2 )
    #define SAR_INT_MASK                (BIT0)
    #define SAR_INT_CLR                 (BIT1)
    #define SAR_INT_FORCE               (BIT2)
    #define SAR_INT_STATUS              (BIT3)

#define REG_SAR_CH_INT_MASK             (RIUBASE_PM_SAR + 0x15*2 )
    #define SAR_INT_MSK_CH0             (BIT0)
    #define SAR_INT_MSK_CH1             (BIT1)
    #define SAR_INT_MSK_CH2             (BIT2)
    #define SAR_INT_MSK_CH3             (BIT3)
    #define SAR_INT_MSK_CH4             (BIT4)
    #define SAR_INT_MSK_ALL             (BIT4|BIT3|BIT2|BIT1|BIT0)

#define REG_SAR_INT_CLR                 (RIUBASE_PM_SAR + 0x16*2 )
    #define SAR_INT_CLR_CH0             (BIT0)
    #define SAR_INT_CLR_CH1             (BIT1)
    #define SAR_INT_CLR_CH2             (BIT2)
    #define SAR_INT_CLR_CH3             (BIT3)
    #define SAR_INT_CLR_CH4             (BIT4)
    #define SAR_INT_CLR_ALL             (BIT4|BIT3|BIT2|BIT1|BIT0)

#define REG_SAR_INT_FORCE               (RIUBASE_PM_SAR + 0x17*2 )
    #define SAR_INT_FORCE_CH0           (BIT0)
    #define SAR_INT_FORCE_CH1           (BIT1)
    #define SAR_INT_FORCE_CH2           (BIT2)
    #define SAR_INT_FORCE_CH3           (BIT3)
    #define SAR_INT_FORCE_CH4           (BIT4)
    #define SAR_INT_FORCE_ALL           (BIT4|BIT3|BIT2|BIT1|BIT0)

#define REG_SAR_INT_STATUS              (RIUBASE_PM_SAR + 0x18*2 )
    #define SAR_INT_STATUS_CH0          (BIT0)
    #define SAR_INT_STATUS_CH1          (BIT1)
    #define SAR_INT_STATUS_CH2          (BIT2)
    #define SAR_INT_STATUS_CH3          (BIT3)
    #define SAR_INT_STATUS_CH4          (BIT4)
    #define SAR_INT_STATUS_ALL          (BIT4|BIT3|BIT2|BIT1|BIT0)

#define REG_SAR_SW_PACK                 (RIUBASE_PM_SAR + 0x19*2 )
    #define SAR_IRQ_CTRL                (BIT0) //Set 1 for New

//PM_SLEEP
#define REG_PM_WK_IRQ_MSK               (RIUBASE_PM_SLEEP+ 0x8*2 )
    #define PM_WK_IRQ_CEC               (BIT0)
    #define PM_WK_IRQ_SAR               (BIT1)
    #define PM_WK_IRQ_SYNCDET           (BIT3)
    #define PM_WK_IRQ_RTC0              (BIT4)
    #define PM_WK_IRQ_DDC               (BIT5)
    #define PM_WK_IRQ_AVLINK            (BIT6)
    #define PM_WK_IRQ_RTC1              (BIT7)

#if 0 // Use "msKeypad_common.h"

#if (KEYPAD_TYPE_SEL == KEYPAD_TYPE_NONE)

#define msKeypad_Init()                 _FUNC_NOT_USED()
#define msKeypad_Get_ADC_Channel(Channel, pvalue)   _FUNC_NOT_USED()
#define msKeypad_GetKey(pkey, pflag)    MSRET_ERROR
#define MDrv_Power_CheckPowerOnKeyPad() FALSE
#define msKeypad_ClearBuffer()          _FUNC_NOT_USED()
#else

INTERFACE void  msKeypad_Init(void);
INTERFACE U8    msKeypad_Get_ADC_Channel(U8 Channel, U8 *pvalue);
INTERFACE BOOLEAN msKeypad_GetKey(U8 *pkey, U8 *pflag);
INTERFACE BOOLEAN MDrv_Power_CheckPowerOnKeyPad(void);
INTERFACE void msKeypad_ClearBuffer(void);
INTERFACE U8 KEYPAD_LV_CHANNEL[ADC_KEY_CHANNEL_NUM];
INTERFACE U8 KEYPAD_PREVIOUS_LV_CHANNEL[ADC_KEY_CHANNEL_NUM];
INTERFACE U8 KEYPAD_LV_COUNT_CHANNEL[ADC_KEY_CHANNEL_NUM];
INTERFACE void msKeypad_ClearBuffer(void);

INTERFACE BOOLEAN msKeypad_CheckFactoryModeKey(void);

#if( POWER_KEY_PAD_BY_INTERRUPT )
INTERFACE U8 msKeypad_Get_PwrKey_IntFlag(void);
INTERFACE void msKeypad_Set_PwrKey_IntFlag(U8 u8Val);
#endif

#endif

#undef INTERFACE
#endif // Use "msKeypad_common.h"

#endif // _MSKEYPAD_H_

