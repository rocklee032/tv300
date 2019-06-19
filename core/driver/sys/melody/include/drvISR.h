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
// Description: Interrupt Service Routines
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_ISR_H_
#define _DRV_ISR_H_


#include "drvISR_Common.h"

#if 0

#ifdef _DRV_ISR_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif


#define ISR_TIMER0_PERIOD_US        1000UL  // : 1000us, unit:us, Timer 0 Interrupt period

INTERFACE U32 volatile  gTimerCount0;
INTERFACE U32 volatile  gTimerDownCount0;
INTERFACE U32 volatile  gTimerDownCount1;
INTERFACE U32 volatile  gOutVsyncCount;    //ISR,  //**

INTERFACE U32 volatile      g100msTimeCount;
INTERFACE U8                gu8100msTH;
//INTERFACE U16               gu16SystemTimePeriodTH;
INTERFACE U16        g_u16ElapsedTimeSecond;

INTERFACE U8 gu8MADPlayFile, gu8MADEncodeDone;

#if 1//(ENABLE_SUPPORT_MM_PHOTO_4K_2K == 1)
INTERFACE void MDrv_Photo_Display_Set4K2KMode(BOOLEAN bSetOnOff);
INTERFACE MS_U8 MDrv_Photo_Display_Get4K2KMode(void);
INTERFACE void MDrv_Photo_Display_Set4K2KPhotoBufAdd(MS_U8 gopframeindex, MS_U32 bufaddr);
#endif

#undef INTERFACE

#endif

#endif /* _DRV_ISR_H_ */

