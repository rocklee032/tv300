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

#ifndef DAI4W500G_C
#define DAI4W500G_C

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#define DIVIDER_RATIO_31_25KHz  0x02
#define DIVIDER_RATIO_62_5KHz   0x06
#define DIVIDER_RATIO_166_7KHz  0x04
#define DIVIDER_RATIO_50KHz     0x00

#if (TN_FREQ_STEP == FREQ_STEP_31_25KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_31_25KHz
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#elif (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#endif

#define DEBUG_PAL_TUNER   0

#define  PAL_DBG_MSG(x)  x

static FREQSTEP m_eFrequencyStep;


void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    case FREQSTEP_31_25KHz:
    case FREQSTEP_62_5KHz:
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_31_25KHz;
        break;
    }
}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
    BYTE cTunerData[5];

    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);

    cTunerData[2] = 0x80|DIVIDER_RATIO;

    if(eBand == E_RFBAND_VHF_LOW)
        cTunerData[3] = 0x11;
    else if(eBand == E_RFBAND_VHF_HIGH)
        cTunerData[3] = 0x12;
    else
        cTunerData[3] = 0x14;

    cTunerData[4] = 0x40;

    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);

     {
        WORD i;
        i = cTunerData[0]<<8 |cTunerData[1];
        i = i*0.0625 - 38;
        printf("%d ",i);
        printf("\n\r");
     }

}

void devTunerInit(void)
{
    BYTE cTunerData[4];

    devTunerSetFreqStep(TN_FREQ_STEP);
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    cTunerData[2] = 0xC0|DIVIDER_RATIO;
    cTunerData[3] = 0x11;
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);
}

#define DIGITAL_TUNER_IF    36.13



/*************************************************************************
  Subject:    DAI4W500G tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init()
{
}


void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[6];

    //MDrv_Set_Digital_TUNER1(Freq, eBandWidth);


    // Step 166.7 Khz   1000/166.7 = 6
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6 + 0.5);
    //value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 32);

    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );
    if(eBandWidth == E_RFBAND_VHF_LOW)
    {
        if (Freq < FREQ_VL_END){
            CONFIG[2] = 0xbc;
        }
        else {
            CONFIG[2] = 0xf4;
        }
        CONFIG[3]  = 0x01;
    }
    else if(eBandWidth == E_RFBAND_VHF_HIGH)
    {
        if (Freq < FREQ_VH_END){
            CONFIG[2]  = 0xbc;
        }
        else {
            CONFIG[2]  = 0xf4;
        }
        CONFIG[3] = 0x02;
    }
    else
    {
        if (Freq < FREQ_U_END){
            CONFIG[2]  = 0xbc;
        }
        else if (Freq < FREQ_UH_BEGIN){
            CONFIG[2] = 0xf4;
        }
        else{
            CONFIG[2]  = 0xfc;
        }
        CONFIG[3] = 0x04;
    }
       CONFIG[4] = 0xa0;

    //printf("Tuner: %bx, %bx, %bx, %bx, %bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4]);
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, CONFIG);
}


#endif

