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

#ifndef _MAPP_CUSTOMER_INFO_2_H_
#define _MAPP_CUSTOMER_INFO_2_H_


#include "MApp_Customer_Info_2_hashkey.h"


//-------------------------------------------------------------------------------

//Customer ID [0416b] (Example:0009 = 0x0009) (Example: 20= 0x0014)
#define INPUT_CUSTOMER_ID_LOW_BYTE  LOWBYTE(INPUT_CUSTOMER_ID)//0x01
#define INPUT_CUSTOMER_ID_HIGH_BYTE HIGHBYTE(INPUT_CUSTOMER_ID)//0x00

//Model ID (Example:0001 = 0x0001)
#define INPUT_MODEL_ID_LOW_BYTE     LOWBYTE(INPUT_MODEL_ID)//0x00
#define INPUT_MODEL_ID_HIGH_BYTE    HIGHBYTE(INPUT_MODEL_ID)//0x01

//Chip ID (Example:000B = 0x000B)
#define INPUT_CHIP_ID_LOW_BYTE      LOWBYTE(INPUT_CHIP_ID)//0x67
#define INPUT_CHIP_ID_HIGH_BYTE     HIGHBYTE(INPUT_CHIP_ID)//0x66

//Dolby Version (Example:000B = 0x000B)
#define INPUT_DOLBY_VER_LOW_BYTE     LOWBYTE(INPUT_DOLBY_VERSION)//0x00
#define INPUT_DOLBY_VER_HIGH_BYTE    HIGHBYTE(INPUT_DOLBY_VERSION)//0x00


//Customer IP
// Defined at "MApp_Customer_Info_2_hashkey.h"

//Customer Hash
// Defined at "MApp_Customer_Info_2_hashkey.h"

//-------------------------------------------------------------------------------


/* INPUT_SW_PROJECT
Chakra      -   01
POLLUX      -   02
ARCHIMEDES  -   03
Chakra2     ¡V   04
OBAMA       ¡V   05
*/

/* INPUT_PRODUCT_TYPE
TV-01
STB-02
*/

/* INPUT_TV_SYSTEM
ATSC-01
DVBT-02
DVBC-03
DVBS-04
DMBT-05
ATV Only-06
*/

#define INPUT_SW_PROJECT            0x04
#define INPUT_SW_GENERATION         0x01
#define INPUT_PRODUCT_TYPE          0x01
#define INPUT_TV_SYSTEM             0x02

//Label (Example:00000456 = 0x0001C8)
#define INPUT_LABEL_LOW_BYTE        0x08
#define INPUT_LABEL_MIDDLE_BYTE     0x00
#define INPUT_LABEL_HIGH_BYTE       0x00

//CL(Change-List) (Example:00101234 = 0x18B72)
#define INPUT_CL_LOW_BYTE           0x10
#define INPUT_CL_MIDDLE_BYTE        0x4C
#define INPUT_CL_HIGH_BYTE          0x02


#define DRM_MODEL_ID            0x3130


//  SW Quality
//  01-BOOTLEG
//  02-Demo
//  03-Pre-Alpha
//  04-Alpha
//  05-Beta
//  06-RC
//  07-RTM
//  Quality flag can be modified by release engineer only

#define INPUT_RELEASE_QUALITY       0x01

//CPU TYPE
//01-MIPS
//02-AEON
#if (defined(MIPS_CHAKRA) || defined(ARM_CHAKRA))
#define  INPUT_CPU_TYPE 0x01
#else
#define  INPUT_CPU_TYPE 0x02
#endif


//**************************************************************************
//**************************************************************************
//**************************************************************************


#endif // _MAPP_CUSTOMER_INFO_2_H_


