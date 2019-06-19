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
#include <string.h>

#include "Board.h"

#include "debug.h"

#include "MApp_CustomerInfoInclude.h"

#include "drvIPAUTH.h"

#include "MApp_HashKey.h"

//-------------------------------------------------------------------------------------

#if( ENABLE_HASH_KEY_256BITS)
    #include "MApp_Customer_Info.c"
#endif

//-------------------------------------------------------------------------------------

#define DEBUG_CUSTOMER_INFO_ENABLE  0

#if( ENABLE_HASH_KEY_256BITS)
    unsigned char Customer_info[81]; // 4 + 4 + 4 + 4 + 64 + 1
#else
    unsigned char Customer_info[49]; // 4 + 4 + 4 + 4 + 32 + 1
#endif

//-------------------------------------------------------------------------------------

void MApp_HashKey_Init(void)
{
#if (DEBUG_CUSTOMER_INFO_ENABLE)
    PRINT_CURRENT_LINE();
#endif

    memset(Customer_info, 0, sizeof(Customer_info));

#if (ENABLE_HASH_KEY_256BITS )

  #if (DEBUG_CUSTOMER_INFO_ENABLE)
    printf("INPUT_CUSTOMER_ID=0x%04X\n", INPUT_CUSTOMER_ID);
    printf("INPUT_MODEL_ID=0x%04X\n", INPUT_MODEL_ID);
    printf("INPUT_CHIP_ID=0x%04X\n", INPUT_CHIP_ID);
    printf("INPUT_DOLBY_VERSION=0x%04X\n", INPUT_DOLBY_VERSION);
  #endif

    //<1>.To Prepare the Customer-ID + Model-ID + Chip-ID + DOLBY_VERSION
    sprintf( (char*)Customer_info, "%04X%04X%04X%04X", INPUT_CUSTOMER_ID, INPUT_MODEL_ID, INPUT_CHIP_ID, INPUT_DOLBY_VERSION );
    //printf("Customer_info[]=%s\n", Customer_info);

    U16 u16CUSTOMER_IP_STR_len = strlen(CUSTOMER_IP_STR);
    //printf("u16CUSTOMER_IP_STR_len=%u\n", u16CUSTOMER_IP_STR_len);
    if( u16CUSTOMER_IP_STR_len != (64) )
    {
        printf("\nError: CUSTOMER_IP_STR is wrong!\n");
        msDebug_FatalErrorHandler(FATAL_ERR_ID_HASH_KEY_ERROR, 0);
        return ;
    }

    memcpy(&Customer_info[16], CUSTOMER_IP_STR, u16CUSTOMER_IP_STR_len );

    // Put 0 as the end of string
    Customer_info[80] = 0;  //Important, string end symbol

#else

    unsigned char * pu8Temp;
    U8 i,u8Data;
    U8 u8ASCII_Mapping[16] = {'0','1','2','3','4','5','6','7','8','9','A',
        'B','C','D','E','F'};

    memset(Customer_info, 0, sizeof(Customer_info));

    pu8Temp = &CID_Buf[6];//(Byte6,7: Customer ID)(Byte8,9: Model ID)(Byte1011: Chip ID)

    //<1>.To Prepare the Customer-ID + Model-ID + Chip-ID
    for (i=0;i<3;i++)
    { //Get hight byte
        u8Data = ((*(pu8Temp+1))>> 4);
        Customer_info[0+i*4] = u8ASCII_Mapping[u8Data];
        u8Data = (*(pu8Temp+1) & 0x0F);
        Customer_info[1+i*4] =  u8ASCII_Mapping[u8Data];
        //Get Low byte
        u8Data = ((*(pu8Temp))>>4) ;
        Customer_info[2+i*4] = u8ASCII_Mapping[u8Data];
        u8Data = (*(pu8Temp) & 0x0F);
        Customer_info[3+i*4] = u8ASCII_Mapping[u8Data];
        pu8Temp +=2;
    }

    for (i=0;i<4;i++)
    {
        Customer_info[12+i] = 0x30;
    }

    //<2>.To prepare the Customer IP
    pu8Temp = &IP_Cntrol_Mapping_1[0];
    memcpy(&Customer_info[16], pu8Temp, 8);
    pu8Temp = &IP_Cntrol_Mapping_2[0];
    memcpy(&Customer_info[16+8], pu8Temp, 8);
    pu8Temp = &IP_Cntrol_Mapping_3[0];
    memcpy(&Customer_info[16+16], pu8Temp, 8);
    pu8Temp = &IP_Cntrol_Mapping_4[0];
    memcpy(&Customer_info[16+24], pu8Temp, 8);

    // Put 0 as the end of string
    Customer_info[48] = 0;  //Important, string end symbol

#endif


#if (DEBUG_CUSTOMER_INFO_ENABLE)

    printf("Customer_info[]=%s\n", Customer_info);

    {
        U8 i;
        printf("Customer_hash[]={" );
        for (i=0; i<16; ++ i)
        {
            printf("0x%02x,", Customer_hash[i]);
        }
        printf("\n" );
    }
#endif

#if 0//(DEBUG_CUSTOMER_INFO_ENABLE)
    printf("****** Customer_info ******");
    for (i=0;i<48;i++)
    {
        if (i%8 ==0)
            printf("\n");
        printf("0x%bx,", Customer_info[i]);
    }
#endif

    MApi_AUTH_Process(Customer_info, Customer_hash);

    if( IPAUTH_OK != MApi_AUTH_State() )
    {
        msDebug_FatalErrorHandler(FATAL_ERR_ID_HASH_KEY_ERROR, 0);
        return ;
    }

}

//-------------------------------------------------------------------------------------


