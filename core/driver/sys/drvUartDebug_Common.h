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

#ifndef _DRV_UART_DEBUG_COMMON_H_
#define _DRV_UART_DEBUG_COMMON_H_

#include "Board.h"


#if (ENABLE_MSTV_UART_DEBUG)

#define ENABLE_UART_CHECKSUM    1


// Uart command list:

//----------------------------------------------------------------
// Basic command for Cus_UART_DecodeCommand/MDrv_UART_DecodeNormalCommand

#define uartWrite_MST_Bank_n    0x01
#define uartRead_MST_Bank_n     0x02
#define uartXC_Read_MST_Bank    0x20
#define uartXC_Write_MST_Bank   0x21

#define uartRead_MCU_XDATA      0x04
#define uartWrite_MCU_XDATA     0x05

#define uartRead_Demod          0x06
#define uartWrite_Demod         0x07
#define uartRead_Tuner          0x0A
#define uartWrite_Tuner         0x0B
#if (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
#define uartRead_PI2C           0x0C
#define uartWrite_PI2C          0x0D
#endif

#define uartTest_Command        0x09

#define uartI2C_Device_Write    0x10
#define uartI2C_Device_Read     0x11

#define uartEEPROM_Write        0x12
#define uartEEPROM_Read         0x13

//----------------------------------------------------------------
// Ext command for Cus_UART_DecodeExtCommand/MDrv_UART_DecodeExtCommand

#define uartExtDev_I2C_DEVICE               0x00
#define uartExtDev_Other_Tuner_Debug        0x02
#define uartExtDev_EEPROM_HDCP              0x03
#define uartExtDev_MstDlcTest               0x05
#define uartExtDev_ACE_REPORT               0x07
#define DEV_MST_DBC_TEST                    0x0A
#define uartExtDev_XC_rw                    0x0B

#define uartExtDev_SAMSUNG_S5H1409_DEMODE   0x10
#define uartExtDev_MstAutoBench             0x15
#if ((CHANNEL_SCAN_AUTO_TEST) || (SFU_AUTO_TEST))
#define uartExtDev_I2C_DEVICE_NEW           0x20
#define uartExtDev_SCAN_TUNER               0x30
#define uartExtDev_AUDIO_DEBUG              0x80
#endif

#define uartExtDev_Autotest_Key             0x36 //'6'
#define uartExtDev_Autotest_Sp              0x37 //'7'
#define uartExtDev_USB_Download             0x38 //'8'
#define uartExtDev_Power_Test               0x39 //'9'

#define UART_EXT_DEV_CPU                0x40

//----------------------------------------------------------------

//----------------------------------------------------------------

/////////////////////////////////////////////
// Uart command structure
/////////////////////////////////////////////
typedef enum _UartCommadEnumType
{
    _UART_CMD_CODE_,
    _UART_CMD_INDEX1_,
    _UART_CMD_INDEX2_,
    _UART_CMD_INDEX3_,
    _UART_CMD_INDEX4_,
    _UART_CMD_INDEX5_,
    _UART_CMD_INDEX6_,
    _UART_CMD_INDEX7_,
    _UART_CMD_INDEX8_,
    _UART_CMD_INDEX9_,
    _UART_CMD_INDEX10_,
    _UART_CMD_INDEX11_,
    _UART_CMD_INDEX12_,
    _UART_CMD_INDEX13_,
    _UART_CMD_INDEX14_,
    _UART_CMD_INDEX15_,
    _UART_CMD_INDEX16_,
    _UART_CMD_INDEX17_,
    _UART_CMD_INDEX18_,
    _UART_CMD_INDEX19_,
    _UART_CMD_INDEX20_,

    _UART_CMD_LENGTH_
}UartCommadEnumType;

typedef struct _UartCommadType
{
    U8 au8Buffer_Rx[_UART_CMD_LENGTH_];  // command buffer
                                     // [Length+Command] - [Byte 2] - [Byte 3] - [Byte 4] - [Byte 5]

    U8 Buffer[_UART_CMD_LENGTH_];  // command buffer
                                     // [Length+Command] - [Byte 2] - [Byte 3] - [Byte 4] - [Byte 5]

    U8 Index;                     // buffer index

    U8 u8CmdLen;

}UartCommadType;

extern UartCommadType g_UartCommand; // Uart command struct

#define UART_RX_BUF (g_UartCommand.au8Buffer_Rx)


#define UART_CMD_LENGTH     (g_UartCommand.Buffer[_UART_CMD_CODE_] >> 5)
#define UART_CMD_LENGTH_Buf(buf)  (((buf)[_UART_CMD_CODE_]) >> 5)

#define UART_CMD            (g_UartCommand.Buffer[_UART_CMD_CODE_] & 0x1F)
#define UART_CMD_MS_REG     (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MS_DAT     (g_UartCommand.Buffer[_UART_CMD_INDEX2_])

// for EXT Command
#define UART_EXT            (UART_CMD_LENGTH == 7)
#define UART_EXT_Buf(buf)   (UART_CMD_LENGTH_Buf(buf) == 7)

#define UART_CMD_EXT_LENGTH         (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_EXT_LENGTH_Buf(buf) ((buf)[_UART_CMD_INDEX1_])

#define UART_EXT_DEV         (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_EXT_CMD         (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_EXT_CMD_MS_DAT1 (g_UartCommand.Buffer[_UART_CMD_INDEX4_])
#define UART_EXT_CMD_MS_DAT2 (g_UartCommand.Buffer[_UART_CMD_INDEX5_])
#define UART_EXT_CMD_MS_DAT3 (g_UartCommand.Buffer[_UART_CMD_INDEX6_])
#define UART_EXT_CMD_MS_DAT4 (g_UartCommand.Buffer[_UART_CMD_INDEX7_])
#define UART_EXT_CMD_MS_DAT5 (g_UartCommand.Buffer[_UART_CMD_INDEX8_])
#define UART_EXT_CMD_MS_DAT6 (g_UartCommand.Buffer[_UART_CMD_INDEX9_])
#define UART_EXT_CMD_MS_DAT7 (g_UartCommand.Buffer[_UART_CMD_INDEX10_])
#define UART_EXT_CMD_MS_DAT8 (g_UartCommand.Buffer[_UART_CMD_INDEX11_])
#define UART_EXT_CMD_MS_DAT9 (g_UartCommand.Buffer[_UART_CMD_INDEX12_])
#define UART_EXT_CMD_MS_DAT10 (g_UartCommand.Buffer[_UART_CMD_INDEX13_])
#define UART_EXT_CMD_MS_DAT11 (g_UartCommand.Buffer[_UART_CMD_INDEX14_])
#define UART_EXT_CMD_MS_DAT12 (g_UartCommand.Buffer[_UART_CMD_INDEX15_])
#define UART_EXT_CMD_MS_DAT13 (g_UartCommand.Buffer[_UART_CMD_INDEX16_])

#define UART_CMD_FLASH_LENGTH    (g_UartCommand.Buffer[_UART_CMD_CODE_] >> 3)
#define UART_CMD_FLASH_ADDR0    (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_FLASH_ADDR1    (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_FLASH_ADDR2    (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_CMD_FLASH_DATA     (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_FLASH_CMD          (g_UartCommand.Buffer[_UART_CMD_CODE_] & 0x07)

//=======================================================================

void UART_PrintExtCmdBuf(void);

void MDrv_TVTool_1ms_ISR(void);

//=======================================================================

#endif // ENABLE_MSTV_UART_DEBUG

#endif // _DRV_UART_DEBUG_COMMON_H_

