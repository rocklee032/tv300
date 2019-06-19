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

#ifndef _MAPP_CUSTOMER_INFO_2_HASHKEY_H_
#define _MAPP_CUSTOMER_INFO_2_HASHKEY_H_

//**************************************************************************
//********************** Customer Info Input Area **************************
//**************************************************************************
//Customer ID [0416b] (Example:0009 = 0x0009) (Example: 20= 0x0014)
#define INPUT_CUSTOMER_ID           (0x0001)

//Model ID (Example:0001 = 0x0001)
#define INPUT_MODEL_ID              (0x0100)

//Chip ID (Example:000B = 0x000B)
#define INPUT_CHIP_ID               (0x6667)

//Dolby Version (Example:000B = 0x000B)
#define INPUT_DOLBY_VERSION         (0x0000)


//Customer IP
#define CUSTOMER_IP_STR     "1000000000000000000000000000000000400000080028622000010638FC1000"

#define CUSTOMER_HASH       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

#endif // _MAPP_CUSTOMER_INFO_2_HASHKEY_H_

