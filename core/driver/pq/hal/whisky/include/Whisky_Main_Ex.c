////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (; MStar; Confidential; Information; ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
//****************************************************
//   Quality Map CodeGen Version 4.0
// 1920
// Whisky
// 2015/6/22 19:42
// 2008/7/1 10:31
//****************************************************

#ifndef _WHISKY_MAIN_EX_C_
#define _WHISKY_MAIN_EX_C_

#if PQ_SKIPRULE_ENABLE

code U8 MST_SkipRule_IP_Main_Ex[PQ_IP_NUM_Main_Ex]=
{
    /* AFEC_no_comm */ 0, /* SPF_DBK */ 0, /* DMS */ 0, /* VIP_LDE_setting */ 0, 
    /* VIP_LDE_C_win1 */ 0, /* VIP_LDE_C_win2 */ 0, /* VIP_LDE_C_win3 */ 0, /* VIP_LDE_C_win4 */ 0, 
    /* VIP_LDE_suppress */ 0, /* VIP_Peaking_adptive */ 0, /* VIP_Peaking_Pcoring_ad_C */ 0, /* VIP_IBC_weight */ 0, 
    /* VIP_ACK */ 0, 
};

#endif
//****************************************************
// AFEC_no_comm
//****************************************************
code U8 MST_AFEC_no_comm_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_AFEC_no_comm_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_AFEC_no_comm_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_BK35_2A_H), 0x04, 0x04/*ON*/, },
 { PQ_MAP_REG(REG_BK35_2A_H), 0x04, 0x00/*ON*/, },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// SPF_DBK
//****************************************************
code U8 MST_SPF_DBK_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK0C_48_L), 0xFF, 0xEF },
 { PQ_MAP_REG(REG_SC_BK0C_48_H), 0xFF, 0xCD },
 { PQ_MAP_REG(REG_SC_BK0C_49_L), 0xFF, 0xAB },
 { PQ_MAP_REG(REG_SC_BK0C_49_H), 0xFF, 0x89 },
 { PQ_MAP_REG(REG_SC_BK0C_4A_L), 0xFF, 0x67 },
 { PQ_MAP_REG(REG_SC_BK0C_4A_H), 0xFF, 0x45 },
 { PQ_MAP_REG(REG_SC_BK0C_4B_L), 0xFF, 0x23 },
 { PQ_MAP_REG(REG_SC_BK0C_4B_H), 0xFF, 0x01 },
 { PQ_MAP_REG(REG_SC_BK0C_4C_L), 0xFF, 0xEF },
 { PQ_MAP_REG(REG_SC_BK0C_4C_H), 0xFF, 0xCD },
 { PQ_MAP_REG(REG_SC_BK0C_4D_L), 0xFF, 0xAB },
 { PQ_MAP_REG(REG_SC_BK0C_4D_H), 0xFF, 0x89 },
 { PQ_MAP_REG(REG_SC_BK0C_4E_L), 0xFF, 0x67 },
 { PQ_MAP_REG(REG_SC_BK0C_4E_H), 0xFF, 0x45 },
 { PQ_MAP_REG(REG_SC_BK0C_4F_L), 0xFF, 0x23 },
 { PQ_MAP_REG(REG_SC_BK0C_4F_H), 0xFF, 0x01 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_SPF_DBK_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_SPF_DBK_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_SC_BK0C_71_L), 0x01, 0x00/*OFF*/, 
                              0x01/*LON*/, },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// DMS
//****************************************************
code U8 MST_DMS_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_DMS_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_DMS_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_LDE_setting
//****************************************************
code U8 MST_VIP_LDE_setting_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK38_10_L), 0xF0, 0x40 },
 { PQ_MAP_REG(REG_SC_BK38_11_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_11_H), 0x1F, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_12_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_30_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_30_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_31_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_31_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_32_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_32_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_33_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_33_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_34_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_34_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_35_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_35_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_36_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_36_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_37_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_37_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_38_L), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_38_H), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_39_L), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_39_H), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_3A_L), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_3A_H), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_3B_L), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_3B_H), 0xFF, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_50_H), 0x80, 0x00 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_LDE_setting_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_LDE_setting_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_LDE_C_win1
//****************************************************
code U8 MST_VIP_LDE_C_win1_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK38_50_L), 0x01, 0x01 },
 { PQ_MAP_REG(REG_SC_BK38_51_L), 0x03, 0x02 },
 { PQ_MAP_REG(REG_SC_BK38_52_L), 0xFF, 0x83 },
 { PQ_MAP_REG(REG_SC_BK38_53_L), 0xFF, 0x83 },
 { PQ_MAP_REG(REG_SC_BK38_52_H), 0xFF, 0x7E },
 { PQ_MAP_REG(REG_SC_BK38_53_H), 0xFF, 0x7E },
 { PQ_MAP_REG(REG_SC_BK38_5A_L), 0x0F, 0x01 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_LDE_C_win1_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_LDE_C_win1_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_LDE_C_win2
//****************************************************
code U8 MST_VIP_LDE_C_win2_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK38_50_L), 0x02, 0x02 },
 { PQ_MAP_REG(REG_SC_BK38_51_L), 0x0C, 0x0C },
 { PQ_MAP_REG(REG_SC_BK38_54_L), 0xFF, 0xFF },
 { PQ_MAP_REG(REG_SC_BK38_55_L), 0xFF, 0x64 },
 { PQ_MAP_REG(REG_SC_BK38_54_H), 0xFF, 0x8C },
 { PQ_MAP_REG(REG_SC_BK38_55_H), 0xFF, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_5A_L), 0xF0, 0x10 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_LDE_C_win2_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_LDE_C_win2_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_LDE_C_win3
//****************************************************
code U8 MST_VIP_LDE_C_win3_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK38_50_L), 0x04, 0x04 },
 { PQ_MAP_REG(REG_SC_BK38_51_L), 0x30, 0x20 },
 { PQ_MAP_REG(REG_SC_BK38_56_L), 0xFF, 0x6E },
 { PQ_MAP_REG(REG_SC_BK38_57_L), 0xFF, 0xA0 },
 { PQ_MAP_REG(REG_SC_BK38_56_H), 0xFF, 0x64 },
 { PQ_MAP_REG(REG_SC_BK38_57_H), 0xFF, 0x96 },
 { PQ_MAP_REG(REG_SC_BK38_5A_H), 0x0F, 0x01 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_LDE_C_win3_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_LDE_C_win3_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_LDE_C_win4
//****************************************************
code U8 MST_VIP_LDE_C_win4_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK38_50_L), 0x08, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_51_L), 0xC0, 0x80 },
 { PQ_MAP_REG(REG_SC_BK38_58_L), 0xFF, 0x78 },
 { PQ_MAP_REG(REG_SC_BK38_59_L), 0xFF, 0x78 },
 { PQ_MAP_REG(REG_SC_BK38_58_H), 0xFF, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_59_H), 0xFF, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_5A_H), 0xF0, 0xF0 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_LDE_C_win4_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_LDE_C_win4_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_LDE_suppress
//****************************************************
code U8 MST_VIP_LDE_suppress_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK38_60_L), 0x01, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_61_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_61_H), 0x03, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_62_L), 0xFF, 0x02 },//Same mark
 { PQ_MAP_REG(REG_SC_BK38_62_H), 0x0F, 0x04 },
 { PQ_MAP_REG(REG_SC_BK38_70_L), 0x1F, 0x06 },
 { PQ_MAP_REG(REG_SC_BK38_70_H), 0x1F, 0x06 },
 { PQ_MAP_REG(REG_SC_BK38_71_L), 0x1F, 0x07 },
 { PQ_MAP_REG(REG_SC_BK38_71_H), 0x1F, 0x08 },
 { PQ_MAP_REG(REG_SC_BK38_72_L), 0x1F, 0x09 },
 { PQ_MAP_REG(REG_SC_BK38_72_H), 0x1F, 0x0A },
 { PQ_MAP_REG(REG_SC_BK38_73_L), 0x1F, 0x0B },
 { PQ_MAP_REG(REG_SC_BK38_73_H), 0x1F, 0x0C },
 { PQ_MAP_REG(REG_SC_BK38_74_L), 0x1F, 0x0D },
 { PQ_MAP_REG(REG_SC_BK38_74_H), 0x1F, 0x0E },
 { PQ_MAP_REG(REG_SC_BK38_75_L), 0x1F, 0x0F },
 { PQ_MAP_REG(REG_SC_BK38_75_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_76_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_76_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_77_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_77_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_78_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_78_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_79_L), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_79_H), 0x1F, 0x10 },
 { PQ_MAP_REG(REG_SC_BK38_7A_L), 0x1F, 0x0E },
 { PQ_MAP_REG(REG_SC_BK38_7A_H), 0x1F, 0x0C },
 { PQ_MAP_REG(REG_SC_BK38_7B_L), 0x1F, 0x0A },
 { PQ_MAP_REG(REG_SC_BK38_7B_H), 0x1F, 0x08 },
 { PQ_MAP_REG(REG_SC_BK38_7C_L), 0x1F, 0x06 },
 { PQ_MAP_REG(REG_SC_BK38_7C_H), 0x1F, 0x04 },
 { PQ_MAP_REG(REG_SC_BK38_7D_L), 0x1F, 0x02 },
 { PQ_MAP_REG(REG_SC_BK38_7D_H), 0x1F, 0x01 },
 { PQ_MAP_REG(REG_SC_BK38_7E_L), 0x1F, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_7E_H), 0x1F, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_7F_L), 0x1F, 0x00 },
 { PQ_MAP_REG(REG_SC_BK38_7F_H), 0x1F, 0x00 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_LDE_suppress_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_LDE_suppress_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_Peaking_adptive
//****************************************************
code U8 MST_VIP_Peaking_adptive_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK19_32_L), 0xFF, 0x44 },//Same mark
 { PQ_MAP_REG(REG_SC_BK19_32_H), 0xFF, 0x44 },//Same mark
 { PQ_MAP_REG(REG_SC_BK19_46_L), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK19_46_H), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK19_47_L), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK19_47_H), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK19_4E_L), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK19_4E_H), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK19_4F_L), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK19_4F_H), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_Peaking_adptive_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_Peaking_adptive_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_SC_BK19_31_L), 0x9F, 0x03/*$RF_NTSC*/, 
                              0x93/*$AV_NTSC*/, 
                              0x03/*$AV_PAL*/, 
                              0x03/*$480i*/, 
                              0x11/*$720p*/, 
                              0x93/*$1080i*/, 
                              0x03/*$H_480i*/, 
                              0x11/*$H_576i*/, 
                              0x11/*$H_720p*/, 
                              0x93/*$H_1080i*/, 
                              0x03/*$DT_MPEG2_480is*/, 
                              0x11/*$DT_MPEG2_576i*/, 
                              0x03/*$DT_MPEG2_1080i*/, 
                              0x03/*$DT_H264_480is*/, 
                              0x11/*$DT_H264_576p*/, 
                              0x11/*$DT_H264_720p*/, 
                              0x03/*$DT_H264_1080i*/, 
                              0x11/*$DT_H264_1080p*/, 
                              0x11/*$PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_40_L), 0x3F, 0x1C/*RF_NTSC*/, 
                              0x1C/*AV_NTSC*/, 
                              0x1C/*AV_PAL*/, 
                              0x1C/*480i*/, 
                              0x1C/*720p*/, 
                              0x1C/*1080i*/, 
                              0x1C/*H_480i*/, 
                              0x1C/*H_576i*/, 
                              0x1C/*H_720p*/, 
                              0x1C/*H_1080i*/, 
                              0x1C/*DT_MPEG2_480is*/, 
                              0x1C/*DT_MPEG2_576i*/, 
                              0x1C/*DT_MPEG2_1080i*/, 
                              0x1C/*DT_H264_480is*/, 
                              0x1C/*DT_H264_576p*/, 
                              0x1C/*DT_H264_720p*/, 
                              0x1C/*DT_H264_1080i*/, 
                              0x1C/*DT_H264_1080p*/, 
                              0x2B/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_40_H), 0x3F, 0x1E/*RF_NTSC*/, 
                              0x1E/*AV_NTSC*/, 
                              0x1E/*AV_PAL*/, 
                              0x1E/*480i*/, 
                              0x1E/*720p*/, 
                              0x1E/*1080i*/, 
                              0x1E/*H_480i*/, 
                              0x1E/*H_576i*/, 
                              0x1E/*H_720p*/, 
                              0x1E/*H_1080i*/, 
                              0x1E/*DT_MPEG2_480is*/, 
                              0x1E/*DT_MPEG2_576i*/, 
                              0x1E/*DT_MPEG2_1080i*/, 
                              0x1E/*DT_H264_480is*/, 
                              0x1E/*DT_H264_576p*/, 
                              0x1E/*DT_H264_720p*/, 
                              0x1E/*DT_H264_1080i*/, 
                              0x1E/*DT_H264_1080p*/, 
                              0x2A/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_41_L), 0x3F, 0x20/*RF_NTSC*/, 
                              0x20/*AV_NTSC*/, 
                              0x20/*AV_PAL*/, 
                              0x20/*480i*/, 
                              0x20/*720p*/, 
                              0x20/*1080i*/, 
                              0x20/*H_480i*/, 
                              0x20/*H_576i*/, 
                              0x20/*H_720p*/, 
                              0x20/*H_1080i*/, 
                              0x20/*DT_MPEG2_480is*/, 
                              0x20/*DT_MPEG2_576i*/, 
                              0x20/*DT_MPEG2_1080i*/, 
                              0x20/*DT_H264_480is*/, 
                              0x20/*DT_H264_576p*/, 
                              0x20/*DT_H264_720p*/, 
                              0x20/*DT_H264_1080i*/, 
                              0x20/*DT_H264_1080p*/, 
                              0x28/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_41_H), 0x3F, 0x22/*RF_NTSC*/, 
                              0x22/*AV_NTSC*/, 
                              0x22/*AV_PAL*/, 
                              0x22/*480i*/, 
                              0x22/*720p*/, 
                              0x22/*1080i*/, 
                              0x22/*H_480i*/, 
                              0x22/*H_576i*/, 
                              0x22/*H_720p*/, 
                              0x22/*H_1080i*/, 
                              0x22/*DT_MPEG2_480is*/, 
                              0x22/*DT_MPEG2_576i*/, 
                              0x22/*DT_MPEG2_1080i*/, 
                              0x22/*DT_H264_480is*/, 
                              0x22/*DT_H264_576p*/, 
                              0x22/*DT_H264_720p*/, 
                              0x22/*DT_H264_1080i*/, 
                              0x22/*DT_H264_1080p*/, 
                              0x27/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_42_L), 0x3F, 0x24/*RF_NTSC*/, 
                              0x24/*AV_NTSC*/, 
                              0x24/*AV_PAL*/, 
                              0x24/*480i*/, 
                              0x24/*720p*/, 
                              0x24/*1080i*/, 
                              0x24/*H_480i*/, 
                              0x24/*H_576i*/, 
                              0x24/*H_720p*/, 
                              0x24/*H_1080i*/, 
                              0x24/*DT_MPEG2_480is*/, 
                              0x24/*DT_MPEG2_576i*/, 
                              0x24/*DT_MPEG2_1080i*/, 
                              0x24/*DT_H264_480is*/, 
                              0x24/*DT_H264_576p*/, 
                              0x24/*DT_H264_720p*/, 
                              0x24/*DT_H264_1080i*/, 
                              0x24/*DT_H264_1080p*/, 
                              0x26/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_42_H), 0x3F, 0x26/*RF_NTSC*/, 
                              0x26/*AV_NTSC*/, 
                              0x26/*AV_PAL*/, 
                              0x26/*480i*/, 
                              0x26/*720p*/, 
                              0x26/*1080i*/, 
                              0x26/*H_480i*/, 
                              0x26/*H_576i*/, 
                              0x26/*H_720p*/, 
                              0x26/*H_1080i*/, 
                              0x26/*DT_MPEG2_480is*/, 
                              0x26/*DT_MPEG2_576i*/, 
                              0x26/*DT_MPEG2_1080i*/, 
                              0x26/*DT_H264_480is*/, 
                              0x26/*DT_H264_576p*/, 
                              0x26/*DT_H264_720p*/, 
                              0x26/*DT_H264_1080i*/, 
                              0x26/*DT_H264_1080p*/, 
                              0x25/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_43_L), 0x3F, 0x28/*RF_NTSC*/, 
                              0x28/*AV_NTSC*/, 
                              0x28/*AV_PAL*/, 
                              0x28/*480i*/, 
                              0x28/*720p*/, 
                              0x28/*1080i*/, 
                              0x28/*H_480i*/, 
                              0x28/*H_576i*/, 
                              0x28/*H_720p*/, 
                              0x28/*H_1080i*/, 
                              0x28/*DT_MPEG2_480is*/, 
                              0x28/*DT_MPEG2_576i*/, 
                              0x28/*DT_MPEG2_1080i*/, 
                              0x28/*DT_H264_480is*/, 
                              0x28/*DT_H264_576p*/, 
                              0x28/*DT_H264_720p*/, 
                              0x28/*DT_H264_1080i*/, 
                              0x28/*DT_H264_1080p*/, 
                              0x24/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_43_H), 0x3F, 0x2A/*RF_NTSC*/, 
                              0x2A/*AV_NTSC*/, 
                              0x2A/*AV_PAL*/, 
                              0x2A/*480i*/, 
                              0x2A/*720p*/, 
                              0x2A/*1080i*/, 
                              0x2A/*H_480i*/, 
                              0x2A/*H_576i*/, 
                              0x2A/*H_720p*/, 
                              0x2A/*H_1080i*/, 
                              0x2A/*DT_MPEG2_480is*/, 
                              0x2A/*DT_MPEG2_576i*/, 
                              0x2A/*DT_MPEG2_1080i*/, 
                              0x2A/*DT_H264_480is*/, 
                              0x2A/*DT_H264_576p*/, 
                              0x2A/*DT_H264_720p*/, 
                              0x2A/*DT_H264_1080i*/, 
                              0x2A/*DT_H264_1080p*/, 
                              0x23/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_44_L), 0x3F, 0x28/*RF_NTSC*/, 
                              0x28/*AV_NTSC*/, 
                              0x28/*AV_PAL*/, 
                              0x28/*480i*/, 
                              0x28/*720p*/, 
                              0x28/*1080i*/, 
                              0x28/*H_480i*/, 
                              0x28/*H_576i*/, 
                              0x28/*H_720p*/, 
                              0x28/*H_1080i*/, 
                              0x28/*DT_MPEG2_480is*/, 
                              0x28/*DT_MPEG2_576i*/, 
                              0x28/*DT_MPEG2_1080i*/, 
                              0x28/*DT_H264_480is*/, 
                              0x28/*DT_H264_576p*/, 
                              0x28/*DT_H264_720p*/, 
                              0x28/*DT_H264_1080i*/, 
                              0x28/*DT_H264_1080p*/, 
                              0x22/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_44_H), 0x3F, 0x26/*RF_NTSC*/, 
                              0x26/*AV_NTSC*/, 
                              0x26/*AV_PAL*/, 
                              0x26/*480i*/, 
                              0x26/*720p*/, 
                              0x26/*1080i*/, 
                              0x26/*H_480i*/, 
                              0x26/*H_576i*/, 
                              0x26/*H_720p*/, 
                              0x26/*H_1080i*/, 
                              0x26/*DT_MPEG2_480is*/, 
                              0x26/*DT_MPEG2_576i*/, 
                              0x26/*DT_MPEG2_1080i*/, 
                              0x26/*DT_H264_480is*/, 
                              0x26/*DT_H264_576p*/, 
                              0x26/*DT_H264_720p*/, 
                              0x26/*DT_H264_1080i*/, 
                              0x26/*DT_H264_1080p*/, 
                              0x21/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_45_L), 0x3F, 0x24/*RF_NTSC*/, 
                              0x24/*AV_NTSC*/, 
                              0x24/*AV_PAL*/, 
                              0x24/*480i*/, 
                              0x24/*720p*/, 
                              0x24/*1080i*/, 
                              0x24/*H_480i*/, 
                              0x24/*H_576i*/, 
                              0x24/*H_720p*/, 
                              0x24/*H_1080i*/, 
                              0x24/*DT_MPEG2_480is*/, 
                              0x24/*DT_MPEG2_576i*/, 
                              0x24/*DT_MPEG2_1080i*/, 
                              0x24/*DT_H264_480is*/, 
                              0x24/*DT_H264_576p*/, 
                              0x24/*DT_H264_720p*/, 
                              0x24/*DT_H264_1080i*/, 
                              0x24/*DT_H264_1080p*/, 
                              0x20/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_45_H), 0x3F, 0x22/*RF_NTSC*/, 
                              0x22/*AV_NTSC*/, 
                              0x22/*AV_PAL*/, 
                              0x22/*480i*/, 
                              0x22/*720p*/, 
                              0x22/*1080i*/, 
                              0x22/*H_480i*/, 
                              0x22/*H_576i*/, 
                              0x22/*H_720p*/, 
                              0x22/*H_1080i*/, 
                              0x22/*DT_MPEG2_480is*/, 
                              0x22/*DT_MPEG2_576i*/, 
                              0x22/*DT_MPEG2_1080i*/, 
                              0x22/*DT_H264_480is*/, 
                              0x22/*DT_H264_576p*/, 
                              0x22/*DT_H264_720p*/, 
                              0x22/*DT_H264_1080i*/, 
                              0x22/*DT_H264_1080p*/, 
                              0x20/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_48_L), 0x3F, 0x1C/*RF_NTSC*/, 
                              0x1C/*AV_NTSC*/, 
                              0x1C/*AV_PAL*/, 
                              0x1C/*480i*/, 
                              0x1C/*720p*/, 
                              0x1C/*1080i*/, 
                              0x1C/*H_480i*/, 
                              0x1C/*H_576i*/, 
                              0x1C/*H_720p*/, 
                              0x1C/*H_1080i*/, 
                              0x1C/*DT_MPEG2_480is*/, 
                              0x1C/*DT_MPEG2_576i*/, 
                              0x1C/*DT_MPEG2_1080i*/, 
                              0x1C/*DT_H264_480is*/, 
                              0x1C/*DT_H264_576p*/, 
                              0x1C/*DT_H264_720p*/, 
                              0x1C/*DT_H264_1080i*/, 
                              0x1C/*DT_H264_1080p*/, 
                              0x2B/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_48_H), 0x3F, 0x1E/*RF_NTSC*/, 
                              0x1E/*AV_NTSC*/, 
                              0x1E/*AV_PAL*/, 
                              0x1E/*480i*/, 
                              0x1E/*720p*/, 
                              0x1E/*1080i*/, 
                              0x1E/*H_480i*/, 
                              0x1E/*H_576i*/, 
                              0x1E/*H_720p*/, 
                              0x1E/*H_1080i*/, 
                              0x1E/*DT_MPEG2_480is*/, 
                              0x1E/*DT_MPEG2_576i*/, 
                              0x1E/*DT_MPEG2_1080i*/, 
                              0x1E/*DT_H264_480is*/, 
                              0x1E/*DT_H264_576p*/, 
                              0x1E/*DT_H264_720p*/, 
                              0x1E/*DT_H264_1080i*/, 
                              0x1E/*DT_H264_1080p*/, 
                              0x2A/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_49_L), 0x3F, 0x20/*RF_NTSC*/, 
                              0x20/*AV_NTSC*/, 
                              0x20/*AV_PAL*/, 
                              0x20/*480i*/, 
                              0x20/*720p*/, 
                              0x20/*1080i*/, 
                              0x20/*H_480i*/, 
                              0x20/*H_576i*/, 
                              0x20/*H_720p*/, 
                              0x20/*H_1080i*/, 
                              0x20/*DT_MPEG2_480is*/, 
                              0x20/*DT_MPEG2_576i*/, 
                              0x20/*DT_MPEG2_1080i*/, 
                              0x20/*DT_H264_480is*/, 
                              0x20/*DT_H264_576p*/, 
                              0x20/*DT_H264_720p*/, 
                              0x20/*DT_H264_1080i*/, 
                              0x20/*DT_H264_1080p*/, 
                              0x28/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_49_H), 0x3F, 0x22/*RF_NTSC*/, 
                              0x22/*AV_NTSC*/, 
                              0x22/*AV_PAL*/, 
                              0x22/*480i*/, 
                              0x22/*720p*/, 
                              0x22/*1080i*/, 
                              0x22/*H_480i*/, 
                              0x22/*H_576i*/, 
                              0x22/*H_720p*/, 
                              0x22/*H_1080i*/, 
                              0x22/*DT_MPEG2_480is*/, 
                              0x22/*DT_MPEG2_576i*/, 
                              0x22/*DT_MPEG2_1080i*/, 
                              0x22/*DT_H264_480is*/, 
                              0x22/*DT_H264_576p*/, 
                              0x22/*DT_H264_720p*/, 
                              0x22/*DT_H264_1080i*/, 
                              0x22/*DT_H264_1080p*/, 
                              0x27/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4A_L), 0x3F, 0x24/*RF_NTSC*/, 
                              0x24/*AV_NTSC*/, 
                              0x24/*AV_PAL*/, 
                              0x24/*480i*/, 
                              0x24/*720p*/, 
                              0x24/*1080i*/, 
                              0x24/*H_480i*/, 
                              0x24/*H_576i*/, 
                              0x24/*H_720p*/, 
                              0x24/*H_1080i*/, 
                              0x24/*DT_MPEG2_480is*/, 
                              0x24/*DT_MPEG2_576i*/, 
                              0x24/*DT_MPEG2_1080i*/, 
                              0x24/*DT_H264_480is*/, 
                              0x24/*DT_H264_576p*/, 
                              0x24/*DT_H264_720p*/, 
                              0x24/*DT_H264_1080i*/, 
                              0x24/*DT_H264_1080p*/, 
                              0x26/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4A_H), 0x3F, 0x26/*RF_NTSC*/, 
                              0x26/*AV_NTSC*/, 
                              0x26/*AV_PAL*/, 
                              0x26/*480i*/, 
                              0x26/*720p*/, 
                              0x26/*1080i*/, 
                              0x26/*H_480i*/, 
                              0x26/*H_576i*/, 
                              0x26/*H_720p*/, 
                              0x26/*H_1080i*/, 
                              0x26/*DT_MPEG2_480is*/, 
                              0x26/*DT_MPEG2_576i*/, 
                              0x26/*DT_MPEG2_1080i*/, 
                              0x26/*DT_H264_480is*/, 
                              0x26/*DT_H264_576p*/, 
                              0x26/*DT_H264_720p*/, 
                              0x26/*DT_H264_1080i*/, 
                              0x26/*DT_H264_1080p*/, 
                              0x25/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4B_L), 0x3F, 0x28/*RF_NTSC*/, 
                              0x28/*AV_NTSC*/, 
                              0x28/*AV_PAL*/, 
                              0x28/*480i*/, 
                              0x28/*720p*/, 
                              0x28/*1080i*/, 
                              0x28/*H_480i*/, 
                              0x28/*H_576i*/, 
                              0x28/*H_720p*/, 
                              0x28/*H_1080i*/, 
                              0x28/*DT_MPEG2_480is*/, 
                              0x28/*DT_MPEG2_576i*/, 
                              0x28/*DT_MPEG2_1080i*/, 
                              0x28/*DT_H264_480is*/, 
                              0x28/*DT_H264_576p*/, 
                              0x28/*DT_H264_720p*/, 
                              0x28/*DT_H264_1080i*/, 
                              0x28/*DT_H264_1080p*/, 
                              0x24/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4B_H), 0x3F, 0x2A/*RF_NTSC*/, 
                              0x2A/*AV_NTSC*/, 
                              0x2A/*AV_PAL*/, 
                              0x2A/*480i*/, 
                              0x2A/*720p*/, 
                              0x2A/*1080i*/, 
                              0x2A/*H_480i*/, 
                              0x2A/*H_576i*/, 
                              0x2A/*H_720p*/, 
                              0x2A/*H_1080i*/, 
                              0x2A/*DT_MPEG2_480is*/, 
                              0x2A/*DT_MPEG2_576i*/, 
                              0x2A/*DT_MPEG2_1080i*/, 
                              0x2A/*DT_H264_480is*/, 
                              0x2A/*DT_H264_576p*/, 
                              0x2A/*DT_H264_720p*/, 
                              0x2A/*DT_H264_1080i*/, 
                              0x2A/*DT_H264_1080p*/, 
                              0x23/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4C_L), 0x3F, 0x28/*RF_NTSC*/, 
                              0x28/*AV_NTSC*/, 
                              0x28/*AV_PAL*/, 
                              0x28/*480i*/, 
                              0x28/*720p*/, 
                              0x28/*1080i*/, 
                              0x28/*H_480i*/, 
                              0x28/*H_576i*/, 
                              0x28/*H_720p*/, 
                              0x28/*H_1080i*/, 
                              0x28/*DT_MPEG2_480is*/, 
                              0x28/*DT_MPEG2_576i*/, 
                              0x28/*DT_MPEG2_1080i*/, 
                              0x28/*DT_H264_480is*/, 
                              0x28/*DT_H264_576p*/, 
                              0x28/*DT_H264_720p*/, 
                              0x28/*DT_H264_1080i*/, 
                              0x28/*DT_H264_1080p*/, 
                              0x22/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4C_H), 0x3F, 0x26/*RF_NTSC*/, 
                              0x26/*AV_NTSC*/, 
                              0x26/*AV_PAL*/, 
                              0x26/*480i*/, 
                              0x26/*720p*/, 
                              0x26/*1080i*/, 
                              0x26/*H_480i*/, 
                              0x26/*H_576i*/, 
                              0x26/*H_720p*/, 
                              0x26/*H_1080i*/, 
                              0x26/*DT_MPEG2_480is*/, 
                              0x26/*DT_MPEG2_576i*/, 
                              0x26/*DT_MPEG2_1080i*/, 
                              0x26/*DT_H264_480is*/, 
                              0x26/*DT_H264_576p*/, 
                              0x26/*DT_H264_720p*/, 
                              0x26/*DT_H264_1080i*/, 
                              0x26/*DT_H264_1080p*/, 
                              0x21/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4D_L), 0x3F, 0x24/*RF_NTSC*/, 
                              0x24/*AV_NTSC*/, 
                              0x24/*AV_PAL*/, 
                              0x24/*480i*/, 
                              0x24/*720p*/, 
                              0x24/*1080i*/, 
                              0x24/*H_480i*/, 
                              0x24/*H_576i*/, 
                              0x24/*H_720p*/, 
                              0x24/*H_1080i*/, 
                              0x24/*DT_MPEG2_480is*/, 
                              0x24/*DT_MPEG2_576i*/, 
                              0x24/*DT_MPEG2_1080i*/, 
                              0x24/*DT_H264_480is*/, 
                              0x24/*DT_H264_576p*/, 
                              0x24/*DT_H264_720p*/, 
                              0x24/*DT_H264_1080i*/, 
                              0x24/*DT_H264_1080p*/, 
                              0x20/*PC_mode*/, },
 { PQ_MAP_REG(REG_SC_BK19_4D_H), 0x3F, 0x22/*RF_NTSC*/, 
                              0x22/*AV_NTSC*/, 
                              0x22/*AV_PAL*/, 
                              0x22/*480i*/, 
                              0x22/*720p*/, 
                              0x22/*1080i*/, 
                              0x22/*H_480i*/, 
                              0x22/*H_576i*/, 
                              0x22/*H_720p*/, 
                              0x22/*H_1080i*/, 
                              0x22/*DT_MPEG2_480is*/, 
                              0x22/*DT_MPEG2_576i*/, 
                              0x22/*DT_MPEG2_1080i*/, 
                              0x22/*DT_H264_480is*/, 
                              0x22/*DT_H264_576p*/, 
                              0x22/*DT_H264_720p*/, 
                              0x22/*DT_H264_1080i*/, 
                              0x22/*DT_H264_1080p*/, 
                              0x20/*PC_mode*/, },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_Peaking_Pcoring_ad_C
//****************************************************
code U8 MST_VIP_Peaking_Pcoring_ad_C_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK19_37_L), 0x3F, 0x00 },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_Peaking_Pcoring_ad_C_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_Peaking_Pcoring_ad_C_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_IBC_weight
//****************************************************
code U8 MST_VIP_IBC_weight_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_IBC_weight_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_IBC_weight_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_SC_BK1C_21_H), 0xFF, 0x66/*$W6*/, 
                              0x88/*$W8*/, },
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

//****************************************************
// VIP_ACK
//****************************************************
code U8 MST_VIP_ACK_COM_Main_Ex[][4] =
{      // Reg           Mask  Value
 { PQ_MAP_REG(REG_SC_BK18_38_L), 0xD0, 0x00 },//Same mark
 { PQ_MAP_REG(REG_SC_BK18_39_L), 0x3F, 0x20 },
 { PQ_MAP_REG(REG_SC_BK18_39_H), 0x3F, 0x0E },
 { PQ_MAP_REG(REG_SC_BK18_3A_L), 0xFF, 0xC0 },//Same mark
 { PQ_MAP_REG(REG_SC_BK18_3A_H), 0x1F, 0x01 },
 { PQ_MAP_REG(REG_SC_BK18_3B_L), 0xFF, 0x3C },//Same mark
 { PQ_MAP_REG(REG_SC_BK18_3B_H), 0x6F, 0x02 },//Same mark
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 MST_VIP_ACK_Main_Ex[][REG_ADDR_SIZE+REG_MASK_SIZE+PQ_IP_VIP_ACK_NUMS_Main_Ex]=
{
 { PQ_MAP_REG(REG_TABLE_END), 0x00, 0x00 }
};


code EN_IPTAB_INFO PQ_IPTAB_INFO_Main_Ex[]=
{
{*MST_AFEC_no_comm_COM_Main_Ex, *MST_AFEC_no_comm_Main_Ex, PQ_IP_AFEC_no_comm_NUMS_Main_Ex, PQ_TABTYPE_GENERAL},
{*MST_SPF_DBK_COM_Main_Ex, *MST_SPF_DBK_Main_Ex, PQ_IP_SPF_DBK_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_DMS_COM_Main_Ex, *MST_DMS_Main_Ex, PQ_IP_DMS_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_LDE_setting_COM_Main_Ex, *MST_VIP_LDE_setting_Main_Ex, PQ_IP_VIP_LDE_setting_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_LDE_C_win1_COM_Main_Ex, *MST_VIP_LDE_C_win1_Main_Ex, PQ_IP_VIP_LDE_C_win1_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_LDE_C_win2_COM_Main_Ex, *MST_VIP_LDE_C_win2_Main_Ex, PQ_IP_VIP_LDE_C_win2_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_LDE_C_win3_COM_Main_Ex, *MST_VIP_LDE_C_win3_Main_Ex, PQ_IP_VIP_LDE_C_win3_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_LDE_C_win4_COM_Main_Ex, *MST_VIP_LDE_C_win4_Main_Ex, PQ_IP_VIP_LDE_C_win4_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_LDE_suppress_COM_Main_Ex, *MST_VIP_LDE_suppress_Main_Ex, PQ_IP_VIP_LDE_suppress_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_Peaking_adptive_COM_Main_Ex, *MST_VIP_Peaking_adptive_Main_Ex, PQ_IP_VIP_Peaking_adptive_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_Peaking_Pcoring_ad_C_COM_Main_Ex, *MST_VIP_Peaking_Pcoring_ad_C_Main_Ex, PQ_IP_VIP_Peaking_Pcoring_ad_C_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_IBC_weight_COM_Main_Ex, *MST_VIP_IBC_weight_Main_Ex, PQ_IP_VIP_IBC_weight_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
{*MST_VIP_ACK_COM_Main_Ex, *MST_VIP_ACK_Main_Ex, PQ_IP_VIP_ACK_NUMS_Main_Ex, PQ_TABTYPE_SCALER},
};

#endif
