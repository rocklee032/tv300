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

#include "Board.h"

#if(ENABLE_HASH_KEY_256BITS)

#include "MApp_Customer_Info_2.h"

unsigned char code Customer_hash[16] = {CUSTOMER_HASH};


U16 u16DRMModelID = DRM_MODEL_ID;


unsigned char code CID_Buf[32] =  {
//Fix Value: Do not Modify
        'M', 'S', 'I', 'F',         // (Do not modify)Mstar Information:MSIF
        '0', '1',                   // (Do not modifyCustomer Info Class: 01

//Customer Info area
        INPUT_CUSTOMER_ID_LOW_BYTE,
        INPUT_CUSTOMER_ID_HIGH_BYTE,

        INPUT_MODEL_ID_LOW_BYTE,
        INPUT_MODEL_ID_HIGH_BYTE,

        INPUT_CHIP_ID_LOW_BYTE,
        INPUT_CHIP_ID_HIGH_BYTE,

        INPUT_SW_PROJECT,
        INPUT_SW_GENERATION,
        INPUT_PRODUCT_TYPE,
        INPUT_TV_SYSTEM,

        INPUT_LABEL_LOW_BYTE,
        INPUT_LABEL_MIDDLE_BYTE,
        INPUT_LABEL_HIGH_BYTE,

        INPUT_CL_LOW_BYTE,
        INPUT_CL_MIDDLE_BYTE,
        INPUT_CL_HIGH_BYTE,

        INPUT_RELEASE_QUALITY,

        INPUT_CPU_TYPE,
//Reserve
        '0', '0', '0', '0', '0', '0', '0', '0'   // Reserve
        };



#endif

