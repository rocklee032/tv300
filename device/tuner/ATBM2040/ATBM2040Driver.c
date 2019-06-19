/********************************************************************************************************
(C) Copyright 2016-2030, AltoBeam, Inc. All rights reserved.
File:ATBM2040Driver.c
Description:
    ATBM2040 Tuner internal implement.

History:

*********************************************************************************************************/
#include "ATBM2040Porting.h"
#include "ATBM2040Driver.h"
#include "ATBM2040PrivData.h"

static UINT8 ATBM2040Ver = 107;
#ifdef ATBM2040_CHIP_DEBUG_OPEN
static UINT8 ATBM2040ChipID = 0;
#endif
static ATBM2040HalfAddrRegGroup_t BGReg =
{
    0x0C,
    20,
    {
        0x0D, 0x01, /* 0x0C,0x0D, 0x01, bg_lna_100u_pdn */
        0x17, 0x01, /* 0x0C,0x17, 0x01, bg_uhf_60u_pdn */
        0x21, 0x01, /* 0x0C,0x21, 0x01, bg_rssi_100u_pdn */
        0x23, 0x01, /* 0x0C,0x23, 0x01, bg_vhf_80u_src_pdn */
        0x25, 0x01, /* 0x0C,0x25, 0x01, bg_vhf_100u_sink_pdn */
        0x27, 0x01, /* 0x0C,0x27, 0x01, bg_uhf_80u_pdn */
        0x29, 0x01, /* 0x0C,0x29, 0x01, bg_uhf_90u_pdn */
        0x2B, 0x01, /* 0x0C,0x2B, 0x01, bg_mixr_20u_pdn */
        0x2D, 0x01, /* 0x0C,0x2D, 0x01, bg_mixr_50u_pdn */
        0x2F, 0x01, /* 0x0C,0x2F, 0x01, bg_rf_12ldo_50u_pdn */
    }   
};

static ATBM2040HalfAddrRegGroup_t AdcDivReg =
{
    0x12,
    14,
    {
        0x22, 0x00,  /* 0x12,0x22, 0x00, adc_div_ldo_pd */
        0x42, 0x01,  /* 0x12,0x42, 0x01, adc_div_cal_en */
        0x30, 0x01,  /* 0x12,0x30, 0x01, adc_div_pm */
        0x43, 0x01,  /* 0x12,0x43, 0x01, adc_div_mode_en */
        0x20, 0x01,  /* 0x12,0x20, 0x01, adc_div_core_pd */
        0x44, 0x01,  /* 0x12,0x44, 0x01, adc_div_ldo_bias_en */
        0x45, 0x04,  /* 0x12,0x45, 0x04, adc_div_ldo_s[4:0] */
    }   
};


static ATBM2040Reg_t LnaAttenReg[]=
{
    {0x04,0x00, 0x00}, /*lna_pd */
    {0x04,0x01, 0x00}, /*lna_ldo_pd */
};
#define ATBM2040_ATTEN_CNT ATBM2040_ARRAY_NUM(LnaAttenReg)

static ATBM2040NLOMixer_t NLOMixer[] = {
/* frequency range    Mixer    NLO */
    {0,          60499,        8,        7},
    {60500,      68499,        8,        6},
    {68500,      70499,        8,        6},
    {70500,     118499,        8,        4},
    {118500,    150499,        8,        3},
    {150500,    246499,        8,        2},
    {246500,    333499,        8,        1},
    {333500,    400000,        8,        1},
    {400001,    500499,        4,        2},
    {500500,   1200499,        4,        1},
};/*Vensus_DivRatio.xls*/
#define ATBM2040_NLO_MIXER_CNT ATBM2040_ARRAY_NUM(NLOMixer)

static ATBM2040NLOMixer_t NLOMixerLeoEHMD[] = {
/* frequency range    Mixer    NLO */
    {     0,      49999,     8,        8},
    { 50000,      55999,     8,        5},
    { 56000,      60999,     8,        6},
    { 61000,      65499,     8,        4},
    { 65500,      70999,     8,        6},
    { 71000,     112999,     8,        4},
    {113000,     150999,     8,        3},
    {151000,     238499,     8,    	   2},
    {238500,     400000,     8,    	   1},
    {400001,     474999,     4,        2},
    {475000,    1200000,     4,        1},
};/*Vensus_DivRatio.xls*/
#define ATBM2040_NLO_MIXER_LEOE_HMD_CNT ATBM2040_ARRAY_NUM(NLOMixerLeoEHMD)

static ATBM2040NLOMixer_t NLOMixerLeoELMD[] = {
/* frequency range    Mixer    NLO */
    { 40000,      44999,    8,    8 },
    { 45000,      49999,    8,    10},
    { 50000,      52999,    8,    6 },
    { 53000,      55999,    8,    5 },
    { 56000,      57999,    8,    6 },
    { 58000,      65499,    8,    5 },
    { 65500,      70999,    8,    6 },
    { 71000,     112999,    8,    4 },
    {113000,     150999,    8,    3 },
    {151000,     238499,	8,	  2 },
    {238500,     400000,	8,	  1 },
    {400001,     474999,    4,    2 },
    {475000,    1200000,    4,    1 },
};/*Vensus_DivRatio.xls*/
#define ATBM2040_NLO_MIXER_LEOE_LMD_CNT ATBM2040_ARRAY_NUM(NLOMixerLeoELMD)

static ATBM2040Reg_t PLLSettingReg[] = {
    {0x0F,0x0F, 0x00}, /* pll_kvco[3:0] */
    {0x0E,0x0C, 0x01}, /* osc_pll_en */
    {0x0F,0x03, 0x00}, /* pll_pd_ldo_pfd */
    {0x0F,0x09, 0x00}, /* pll_pd_ldo_cp */
    {0x0F,0x12, 0x00}, /* pll_pd_ldo_vco */
    {0x0F,0x15, 0x00}, /* pll_pd_ldo_mmd */
    {0x0F,0x30, 0x00}, /* pll_rn_mmd */
    {0x0F,0x30, 0x01}, /* pll_rn_mmd */
    {0x0F,0x16, 0x00}, /* pll_pd_ldo_dig */
    {0x0F,0x01, 0x00}, /* pll_en_pfd */
    {0x0F,0x0A, 0x00}, /* pll_pd_cp */
    {0x0F,0x0B, 0x00}, /* pll_pd_fastload */
    {0x0F,0x13, 0x00}, /* pll_pd_vco */
    {0x0F,0x14, 0x00}, /* pll_pd_sx */
    {0x12,0x09, 0x00}, /* pll_ld_pd */
    {0x12,0x07, 0x01}, /* pll_ld_rst */
    {0x12,0x08, 0x01}, /* pll_ld_sel */
    {0x0F,0x0E, 0x00}, /* pll_test_open */

};
#define ATBM2040_PLL_SETTING_REG_CNT ATBM2040_ARRAY_NUM(PLLSettingReg)

static ATBM2040ADCDivider_t ADCDividerHMD[] = {
    {/*40000 */ 0 ,   46000,        7 },
    {46000,           53500,        8 },
    {53500,           60500,        9 },
    {60500,           62000,        8 },
    {62000,           70500,        9 },
    {70500,           74000,        6 },
    {74000,           87500,        7 },
    {87500,           98500,        8 },
    {98500,          107000,        9 },
    {107000,         118500,        10},
    {118500,         129500,        8 },
    {129500,         144500,        9 },
    {144500,         150500,        10},
    {150500,         152000,        6 },
    {152000,         174500,        7 },
    {174500,         197000,        8 },
    {197000,         219500,        9 },
    {219500,         246500,        10},
    {246500,         264500,        5 },
    {264500,         309500,        6 },
    {309500,         357000,        7 },
    {357000,         405000,        8 },
    {405000,         468500,        9 },
    {468500,         500500,        10},
    {500500,         534500,        5 },
    {534500,         638000,        6 },
    {638000,         732500,        7 },
    {732500,         857500,        8 },
    {857500,         962000,        9 },
    {962000,        1200000,        10}
};/*Fs_setting.xlsx*/
#define ATBM2040_ADC_DIVIDER_HMD_CNT ATBM2040_ARRAY_NUM(ADCDividerHMD)

static ATBM2040ADCDivider_t ADCDividerLMD[] = {
    {/*40000 */0,     43500,        5 },
    {43500,           50500,        6 },
    {50500,           58500,        7 },
    {58500,           60500,        8 },
    {60500,           65000,        7 },
    {65000,           70500,        8 },
    {70500,           72500,        5 },
    {72500,           83500,        6 },
    {83500,           94500,        7 },
    {94500,          107000,        8 },
    {107000,         118500,        9 },
    {118500,         125000,        7 },
    {125000,         139500,        8 },
    {139500,         150500,        9 },
    {150500,         165000,        6 },
    {165000,         184500,        7 },
    {184500,         207000,        8 },
    {207000,         229500,        9 },
    {229500,         246500,        10},
    {246500,         274500,        5 },
    {274500,         319500,        6 },
    {319500,         372500,        7 },
    {372500,         423500,        8 },
    {423500,         468500,        9 },
    {468500,         500500,        10},
    {500500,         548500,        5 },
    {548500,         647500,        6 },
    {647500,         732500,        7 },
    {732500,         857500,        8 },
    {857500,         962000,        9 },
    {962000,        1200000,        10},
};/*Fs_setting.xlsx*/
#define ATBM2040_ADC_DIVIDER_LMD_CNT ATBM2040_ARRAY_NUM(ADCDividerLMD)

static ATBM2040ADCDivider_t LeoEADCDividerHMD[] = {
    {     0,      49500,    8 },
    { 49500,      49999,    9 },
    { 49999,      55999,    6 },
    { 55999,      60999,    8 },
    { 60999,      62999,    5 },
    { 62999,      65499,    6 },
    { 65499,      70999,    9 },
    { 70999,      74499,    6 },
    { 74499,      87999,    7 },
    { 87999,      98999,    8 },
    { 98999,     107499,    9 },
    {107499,     112999,    10},
    {112999,     114999,    7 },
    {114999,     129999,    8 },
    {129999,     144999,    9 },
    {144999,     150999,    10},
    {150999,     152499,    6 },
    {152499,     174999,    7 },
    {174999,     197499,    8 },
    {197499,     219999,    9 },
    {219999,     238499,	10},
    {238499,     264999,	5 },
    {264999,     309999,    6 },
    {309999,     357499,    7 },
    {357499,     405499,    8 },
    {405499,     474999,    9 },
    {474999,     534999,    5 },
    {534999,     638499,    6 },
    {638499,     732999,    7 },
    {732999,     857999,    8 },
    {857999,     962499,    9 },
    {962499,    1200000,    10}
};/*Fs_setting.xlsx*/
#define ATBM2040_LEOE_ADC_DIVIDER_HMD_CNT ATBM2040_ARRAY_NUM(LeoEADCDividerHMD)

static ATBM2040ADCDivider_t LeoEADCDividerLMD[] = {
    {     0,      44999,    6 },
    { 44999,      49500,    8 },
    { 49500,      49999,    9 },
    { 49999,      52999,    6 },
    { 52999,      55999,    5 },
    { 55999,      57999,    6 },
    { 57999,      58999,    5 },
    { 58999,      65499,    6 },
    { 65499,      70999,    8 },
    { 70999,      72999,    5 },
    { 72999,      83999,    6 },
    { 83999,      94999,    7 },
    { 94999,     107499,    8 },
    {107499,     112999,    9 },
    {112999,     125499,    7 },
    {125499,     139999,    8 },
    {139999,     150999,    9 },
    {150999,     165999,    6 },
    {165999,     184999,    7 },
    {184999,     207499,    8 },
    {207499,     229999,    9 },
    {229999,     238499,	10},
    {238499,     274999,	5 },
    {274999,     319999,    6 },
    {319999,     372999,    7 },
    {372999,     423999,    8 },
    {423999,     474999,    9 },
    {474999,     548999,    5 },
    {548999,     647999,    6 },
    {647999,     732999,    7 },
    {732999,     857999,    8 },
    {857999,     962499,    9 },
    {962499,    1200000,    10}
};/*Fs_setting.xlsx*/
#define ATBM2040_LEOE_ADC_DIVIDER_LMD_CNT ATBM2040_ARRAY_NUM(LeoEADCDividerLMD)

static ATBM2040Reg_t VHFFilterReg[] = {
    {0x06,0x0C, 0x00}, /* vhf_fltr_ldo_pd  */
    {0x05,0x00, 0x01}, /*uhf_fltr_pwdn_ldo  */
    {0x06,0x1C, 0x01}, /*vhf_fltr_bias_pd */
    {0x06,0x1F, 0x00}, /* vhf_fltr_gm*/
    {0x12,0x2E, 0x01}, /*vhf_filt_cal_clk_en*/
    {0x04,0x0A, 0x00}, /*lna_band*/
    {0x12,0x41, 0x00}, /*mixr_vhf_pd*/

    {0x06,0x20, 0x00}, /*vhf_fltr_osc_rst_sel*/
    {0x06,0x1E, 0x00}, /*vhf_fltr_cap_code_sel*/
};
#define ATBM2040_VHF_FILTER_REG_CNT ATBM2040_ARRAY_NUM(VHFFilterReg)


static ATBM2040Reg_t UHFFltCalibReg[]=
{
    {0x06,0x0C, 0x00}, /* vhf_fltr_ldo_pd */
    {0x05,0x00, 0x00}, /* uhf_fltr_pwdn_ldo */
    {0x04,0x0A, 0x00}, /* lna_band */
    {0x12,0x41, 0x01}, /* mixr_vhf_pd */

    {0x05,0x16, 0x00}, /* Uhf_filt_manual_en=1'b0 */
    /*{0x05,0x14, 0x03},*/ /* uhf_filt_fb_adj_ldo[1:0] */
    {0x05,0x08, 0x1D}, /* uhf_filt_bias_ctrl[4:0] */
    {0x05,0x09, 0x0C}, /* uhf_filt_bias_adj[4:0] */
    {0x05,0x12, 0x00}, /*uhf_fltr_gm_switch[5:0]*/

    {0x05,0x0C, 0x13}, /* uhf_filt_cal_ctrl[4:0] */
    {0x05,0x0E, 0x00}, /* uhf_filt_en_cal */
    {0x12,0x2F, 0x01}, /* uhf_filt_cal_clk_en */
};
#define ATBM2040_UHF_FILTER_REG_CNT ATBM2040_ARRAY_NUM(UHFFltCalibReg)

static ATBM2040Reg_t VHF1FilterReg[] = {
    {0x04,0x01, 0x01}, /*lna_ldo_pd*/
    {0x04,0x0A, 0x01}, /*lna_band*/
    {0x06,0x24, 0x01}, /*Vhf_fltr_reset*/
    {0x06,0x25, 0x01}, /*Vhf_fltr_cal_sel*/
    {0x06,0x26, 0x00}, /*Vhf_fltr_start */

    {0x06,0x29, 0x80}, /*vhf_fltr_code_ref*/

    {0x06,0x2E, 0x01}, /*Vhf_fltr_vcasc_en*/

    {0x06,0x0C, 0x00}, /*Vhf_fltr_ldo_pd*/
    {0x06,0x1C, 0x00}, /*Vhf_fltr_bias_pd*/
};
#define ATBM2040_VHF1_FILTER_REG_CNT ATBM2040_ARRAY_NUM(VHF1FilterReg)

static ATBM2040Reg_t VHF1FilterInitReg[] = {
    {0x06,0x27, 0xFF}, /*Vhf_fltr_code_cal[7:0]*/
    {0x06,0x28, 0x4C}, /*Vhf_fltr_code_osc[7:0]*/

    {0x06,0x2A, 0x1C}, /*Vhf_fltr_shift_cap1[4:0]*/
    {0x06,0x2B, 0x00}, /*Vhf_fltr_shift_cap2[4:0]*/
    {0x06,0x2C, 0x0F}, /*Vhf_fltr_shift_cap3[4:0]*/

    {0x06,0x2D, 0x00}, /*Vhf_fltr_mode_sel*/
    {0x06,0x2F, 0x03}, /*Vhf_fltr_vcasc_adj[1:0]*/
    {0x06,0x30, 0x01}, /*Vhf_fltr_vtail_aux_en*/
    {0x06,0x31, 0x02}, /*Vhf_fltr_iadj_aux[2:0]*/

    {0x06,0x08, 0x01}, /*Vhf_fltr_vref_sel[1:0]*/

};
#define ATBM2040_VHF1_FILTER_INIT_REG_CNT ATBM2040_ARRAY_NUM(VHF1FilterInitReg)

static ATBM2040Reg_t LeoEVHF2FltCalibReg[]=
{
    {0x06,0x0C, 0x00}, /* vhf_fltr_ldo_pd */
    {0x05,0x00, 0x01}, /* uhf_fltr_pwdn_ldo */
    {0x04,0x0A, 0x01}, /* lna_band */
    {0x12,0x41, 0x01}, /* mixr_vhf_pd */
    /*{0x05,0x0E, 0x00},*/ /* uhf_filt_en_cal */

    /*step 1*/
    {0x05,0x16, 0x00}, /* Uhf_filt_manual_en=1'b0 */
    {0x05,0x22, 0x1D}, /* vhf2_filt_bias_ctrl[4:0] */
    {0x05,0x09, 0x0B}, /* uhf_filt_bias_adj[4:0] */
    /*{0x05,0x14, 0x03},*/ /* uhf_filt_fb_adj_ldo[1:0] */
    {0x05,0x21, 0x00}, /* vhf2_fltr_pwdn_ldo */

    /*step 2*/
    {0x05,0x12, 0x00}, /* uhf_fltr_gm_switch[5:0] */

    /*step 3*/
    {0x05,0x23, 0x11}, /* vhf2_filt_cal_ctrl[4:0] */
    {0x12,0x2F, 0x01}, /* uhf_filt_cal_clk_en */

};
#define ATBM2040_LEOE_VHF2_FILTER_REG_CNT ATBM2040_ARRAY_NUM(LeoEVHF2FltCalibReg)


static ATBM2040UHFChIndex_t UHFFreqIndex[] = {
   {1200,     19,    25,     9},
    {946,     21,    25,     9},
    {938,     23,    25,     9},
    {930,     25,    25,     9},
    {922,     27,    25,     9},
    {914,     29,    25,     9},
    {906,     31,    25,     9},
    {898,     33,    25,     9},
    {890,     35,    25,     9},
    {882,     38,    25,     9},
    {874,     41,    25,     9},
    {866,     43,    25,    10},
    {858,     45,    25,    10},
    {850,     48,    26,    10},
    {842,     50,    26,    10},
    {834,     54,    26,    10},
    {826,     56,    26,    10},
    {818,     60,    26,    10},
    {810,     62,    26,    11},
    {802,     65,    26,    11},
    {794,     69,    26,    11},
    {786,     72,    26,    11},
    {778,     75,    26,    11},
    {770,     79,    26,    11},
    {762,     83,    27,    11},
    {754,     87,    27,    12},
    {746,     91,    27,    12},
    {738,     95,    27,    12},
    {730,     99,    27,    12},
    {722,    104,    27,    12},
    {714,    108,    27,    12},
    {706,    112,    27,    12},
    {698,    117,    27,    13},
    {690,    122,    27,    13},
    {682,    127,    28,    14},
    {674,    132,    29,    14},
    {666,    138,    29,    14},
    {658,    143,    29,    14},
    {650,    149,    29,    14},
    {642,    155,    29,    15},
    {634,    162,    30,    15},
    {626,    168,    30,    15},
    {618,    176,    30,    15},
    {610,    183,    30,    16},
    {602,    190,    30,    16},
    {594,    198,    30,    16},
    {586,    206,    31,    16},
    {578,    214,    31,    17},
    {570,    223,    31,    17},
    {562,    232,    31,    17},
    {554,    241,    32,    18},
    {546,    252,    32,    18},
    {538,    261,    35,    20},
    {530,    272,    35,    20},
    {522,    283,    35,    21},
    {514,    295,    36,    21},
    {506,    308,    36,    21},
    {498,    320,    36,    22},
    {490,    334,    36,    22},
    {482,    349,    37,    22},
    {474,    364,    37,    23},
    {466,    380,    37,    24},
    {458,    396,    38,    24},
    {450,    414,    38,    25},
    {442,     434,     38,    25},
    {434,     456,     39,    25},
    {426,     478,     39,    26},
    {418,     500,     40,    26},
    {410,     511,     41,    26},
    {402,     511,     42,    26},
};/*uhf_filter_gm_and_cap_index.xlsx*/
#define ATBM2040_UHF_FREQ_INDEX_CNT ATBM2040_ARRAY_NUM(UHFFreqIndex)

static ATBM2040UHFCalResult_t ATBM2040UHFCalRes[]=
{
    {1000,0,0,0,0},
    {900,0,0,0,0},
    {800,0,0,0,0},
    {700,0,0,0,0},
    {600,0,0,0,0},
    {500,0,0,0,0},
    {400,0,0,0,0},
};
#define ATBM2040_UHF_CAL_RES_CNT ATBM2040_ARRAY_NUM(ATBM2040UHFCalRes)


static ATBM2040VHF2ChIndex_t VHF2FreqIndex[] = {
    {160, 405,    20},
    {168, 362,    19},
    {176, 326,    17},
    {184, 294,    16},
    {192, 265,    15},
    {200, 241,    14},
    {208, 217,    13},
    {216, 197,    13},
    {224, 179,    12},
    {232, 162,    11},
    {240, 147,    11},
    {248, 133,    10},
    {256, 121,    10},
    {264, 109,    9 },
    {272,  98,    9 },
    {280,  89,    9 },
    {288,  80,    8 },
    {296,  71,    8 },
    {304,  64,    8 },
    {312,  57,    7 },
    {320,  51,    7 },
    {328,  45,    7 },
    {336,  39,    7 },
    {344,  34,    6 },
    {352,  29,    6 },
    {360,  24,    6 },
    {368,  20,    6 },
    {376,  15,    6 },
    {384,  12,    6 },
    {392,  8,     6 },
    {400,  5,     5 },
};
#define ATBM2040_VHF2_FREQ_INDEX_CNT ATBM2040_ARRAY_NUM(VHF2FreqIndex)

static ATBM2040VHF2CalResult_t ATBM2040VHF2CalRes[]=
{
    {160, 0,    0,    0,    0 },
    {200, 0,    0,    0,    0 },
    {240, 0,    0,    0,    0 },
    {280, 0,    0,    0,    0 },
    {320, 0,    0,    0,    0 },
    {360, 0,    0,    0,    0 },
    {400, 0,    0,    0,    0 },

};
#define ATBM2040_VHF2_CAL_RES_CNT ATBM2040_ARRAY_NUM(ATBM2040VHF2CalRes)


static UINT8 ADCSettingReg[] = {
    0x0B,0x00, 0x00, /* adc_pd */
    0x0B,0x03, 0x00, /* adc_pd_1p3vldo_i */
    0x0B,0x04, 0x00, /* adc_pd_1p3vldo_q */
    0x0B,0x27, 0x00, /* adc_pd_2p6vldo */
    0x0B,0x25, 0x00, /* adc_rstn */
};
#define ATBM2040_ADC_REG_CNT ATBM2040_ARRAY_NUM(ADCSettingReg)

static UINT8 ADCSettingReg2[] = {
    0x0B,0x25, 0x01, /* adc_rstn */
    /*ADC calibration*/
    0x12,0x2A, 0x01, /* adc_ck_rc_tune_en */
    0x0B,0x06, 0x00, /* adc_rc_tuning_pd */
    0x0B,0x05, 0x00, /* adc_tuning_start */
};
#define ATBM2040_ADC_REG2_CNT ATBM2040_ARRAY_NUM(ADCSettingReg2)


static ATBM2040Reg_t DACSettingReg[] = {
    {0x10,0x00, 0x00}, /*    [0] 0    dac_pd        */
    {0x10,0x02, 0x00}, /*    [0] 0    dac_fltr_pd */
    {0x10,0x0E, 0x00}, /*    [0] 0    dac_rst_n    */
    {0x10,0x0E, 0x01}, /*    [0] 1    dac_rst_n    */

    {0x10,0x0B, 0x01}, /*dac_fltr_ctrl_sel*/
    {0x10,0x04, 0x15}, /*dac_fltr_manul_ctrl*/

};
#define ATBM2040_DAC_REG_CNT ATBM2040_ARRAY_NUM(DACSettingReg)

static ATBM2040VHFChIndex_t VHFChannelIndex[] = {
    { 40000,    7,    220,    12},
    { 52500,    5,    210,    15},
    { 60500,    5,    180,    16},
    { 68500,    3,    160,    17},
    { 80000,    3,    130,    18},
    { 88000,    3,    118,    19},
    {115000,    3,     92,    23},
    {123000,    3,     88,    25},
    {131000,    3,     75,    26},
    {139000,    3,     68,    27},
    {147000,    3,     61,    28},
    {155000,    3,     55,    29},
    {163000,    3,     50,    30},
    {171000,    3,     47,    31},
    {179000,    3,     45,    32},
    {187000,    3,     43,    33},
    {195000,    3,     41,    34},
    {203000,    3,     38,    35},
    {211000,    0,     36,    36},
    {219000,    0,     33,    36},
    {227000,    0,     30,    37},
    {235000,    0,     28,    37},
    {243000,    0,     26,    37},
    {251000,    0,     24,    38},
    {259000,    0,     22,    38},
    {267000,    0,     20,    38},
    {275000,    0,     18,    39},
    {283000,    0,     16,    39},
    {291000,    0,     15,    40},
    {299000,    0,     14,    40},
    {307000,    0,     20,    40},
    {315000,    0,     12,    41},
    {323000,    0,     11,    41},
    {331000,    0,     10,    42},
    {339000,    0,      9,    42},
    {347000,    0,      8,    43},
    {355000,    0,      7,    43},
    {363000,    0,      6,    44},
    {371000,    0,      5,    44},
    {379000,    0,      4,    44},
    {387000,    0,      3,    45},
    {395000,    0,      2,    45},
    {403000,    0,      1,    46},
    {411000,    0,      0,    48},
    {419000,    0,      0,    48},
    {427000,    0,      0,    48},
    {431000,    0,      0,    48},
    {443000,    0,      0,    48},
    {451000,    0,      0,    48},
    {459000,    0,      0,    48},
    {467000,    0,      0,    48},
    {475000,    0,      0,    48},
    {483000,    0,      0,    48},
};/*Leo tuner RTF channel index_wo_cal.xlsx*/
#define ATBM2040_VHF_CH_INDEX_CNT ATBM2040_ARRAY_NUM(VHFChannelIndex)

static ATBM2040VHF1ChIndex_t VHF1ChannelIndex[] = {
/* freq(MHz)    code_ref<7:0>*/
    { 40,    215},
    { 48,    176},
    { 56,    146},
    { 64,    128},
    { 72,    113},
    { 80,    102},
    { 88,    89 },
    { 96,    82 },
    {104,    75 },
    {112,    68 },
    {120,    64 },
    {128,    61 },
    {136,    56 },
    {144,    52 },
    {152,    50 },
    {160,    48 },
    {168,    45 },
    {176,    42 },
    {184,    41 },
    {192,    39 },
    {200,    38 },

};/*vhf_bw_code.xlsx*/
#define ATBM2040_VHF1_CH_INDEX_CNT ATBM2040_ARRAY_NUM(VHF1ChannelIndex)

typedef struct
{
    UINT32 FreqMHz;
    UINT16 Intercept;
}ATBM2040RSSIIntercept_t;

static ATBM2040RSSIIntercept_t RSSIIntercept[] =
{
    {100,    0x0044},
    {200,    0x0043},
    {300,    0x003C},
    {400,    0x0035},
    {500,    0x0030},
    {600,    0x002E},
    {700,    0x0026},
    {800,    0x001C},
    {900,    0x0015},
};
#define ATBM2040_RSSI_INTERCEPT_CNT ATBM2040_ARRAY_NUM(RSSIIntercept)


static ATBM2040Reg_t AGCReg[]=
{
    {0x14,0x4D, 0x1E}, /*params_lna_gain_max[6:0]*/
    {0x14,0x80, 0x08},/*params_thr_rssi_lna_out_ini[3:0]*/
    
    {0x16,0xDE, 0x01}, /*params_agc_mode_change*/
};
#define ATBM2040_AGC_REG_CNT ATBM2040_ARRAY_NUM(AGCReg)

static ATBM2040Reg_t MisReg[]=
{
    {0x16,0x33, 0xC8}, /*params_rssi_slope[7:0]*/
    {0x16,0x40, 0x06}, /* params_inital_a_d_thr[3:0] */
    {0x14,0x00, 0x16}, /* params_adc_quantize_gain[6:0] */
    {0x14,0x43, 0x10}, /* params_lo_change_thr_db */

};
#define ATBM2040_MIS_REG_CNT ATBM2040_ARRAY_NUM(MisReg)

static ATBM2040Reg_t LeoCMisReg[]=
{
    /*{0x19,0xB7, 0x08},*/ /* params_lte_dect_num        */
    {0x19,0xB8, 0x02}, /* params_lte_undect_num    */
    {0x19,0xC8, 0x00}, /* params_use_double_thr_n_m_large    */
    {0x19,0xC9, 0xF1}, /* params_rf_input_power_thr_n_m_large_h    */
    {0x19,0xCA, 0xEC}, /* params_rf_input_power_thr_n_m_large_l    */
    {0x19,0xCB, 0x6C}, /* params_rssi_lna_out_aci_status_4_target_for_n_m_large_h    */
    {0x19,0xCC, 0x62}, /* params_rssi_lna_out_aci_status_4_target_for_n_m_large_l    */
    {0x19,0xCF, 0x01}, /* params_use_full_speed    */
    {0x19,0xE5, 0x00}, /* params_aci_status_target_setting_solely    */

};
#define ATBM2040_LEOC_MIS_REG_CNT ATBM2040_ARRAY_NUM(LeoCMisReg)

static ATBM2040Reg_t LeoCATVMisReg[]=
{
    {0x14,0x14, 0x03}, /* params_banalog_change_num_tracking[3:0]    */
    {0x19,0xB5, 0x08}, /* params_thr_rssi_papr_lte_h    */
    {0x19,0xB6, 0x02}, /* params_thr_rssi_papr_lte_l    */
    {0x19,0xBA, 0x00}, /* params_probablity_rssi_papr_judge_n[7:0]    */
    {0x19,0xBB, 0x01}, /* params_probablity_rssi_papr_judge_n[12:8]    */
    {0x19,0xBC, 0x62}, /* params_rssi_lna_out_aci_status_2_lte_nplus1    */
    {0x19,0xBE, 0x01}, /* params_lte_dect_mode    */
    {0x1A,0x62, 0x76}, /* params_thr_iq_narw_band_filter_l    */
    {0x1A,0x63, 0x7D}, /* params_thr_iq_narw_band_filter_h    */
    {0x1A,0x17, 0x2F}, /* params_in_band_aci_thr_peak    */
};
#define ATBM2040_LEOC_ATV_MIS_REG_CNT ATBM2040_ARRAY_NUM(LeoCATVMisReg)

static ATBM2040Reg_t LeoCDTVMisReg[]=
{
    {0x14,0x14, 0x0F}, /* params_banalog_change_num_tracking[3:0]    */
    {0x19,0xB5, 0x07}, /* params_thr_rssi_papr_lte_h    */
    {0x19,0xB6, 0x03}, /* params_thr_rssi_papr_lte_l    */
    {0x19,0xBA, 0x02}, /* params_probablity_rssi_papr_judge_n[7:0]    */
    {0x19,0xBB, 0x00}, /* params_probablity_rssi_papr_judge_n[12:8]    */
    /*{0x19,0xBC, 0x60},*/ /* params_rssi_lna_out_aci_status_2_lte_nplus1    */
    {0x19,0xBE, 0x00}, /* params_lte_dect_mode    */
    {0x1A,0x62, 0x14}, /* params_thr_iq_narw_band_filter_l    */
    {0x1A,0x63, 0x19}, /* params_thr_iq_narw_band_filter_h    */
    {0x1A,0x17, 0x03}, /* params_in_band_aci_thr_peak    */
};
#define ATBM2040_LEOC_DTV_MIS_REG_CNT ATBM2040_ARRAY_NUM(LeoCDTVMisReg)

typedef struct
{
	UINT32 FreqKHz;
	UINT32 RegNum;
	ATBM2040Reg_t RegList[10];
}ATBM2040AtvSet_t;
static ATBM2040AtvSet_t AtvSettingReg[]=
{
    {52500 , 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {60500 , 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {80000 , 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {88000 , 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {115000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {123000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {131000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {139000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {155000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {163000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {187000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {211000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {235000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {283000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {315000, 4,{{0x14,0x6F, 0x00}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x01}}},
    {331000, 4,{{0x14,0x6F, 0x01}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {363000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x01}}},
    {379000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {395000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x07}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {427000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {451000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {506000, 4,{{0x14,0x6F, 0x00}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {530000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {570000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {578000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {665870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {666000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {673870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {674000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {697870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {698000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {721870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {722000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {753870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {754000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {761870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {762000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {769870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {770000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {785870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {786000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {817870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x01}}},
    {818000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x01}}},
    {825870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {826000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {841870, 4,{{0x14,0x6F, 0x00}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {842000, 4,{{0x14,0x6F, 0x00}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {849870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {850000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x04}, {0x12, 0x2D, 0x00}}},
    {865870, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
    {866000, 4,{{0x14,0x6F, 0x20}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},

    {0 ,     4,{{0x14,0x6F, 0x00}, {0x14,0x70, 0x08}, {0x15, 0x5F, 0x00}, {0x12, 0x2D, 0x00}}},
};
#define ATBM2040_ATV_SETTING_REG_CNT ATBM2040_ARRAY_NUM(AtvSettingReg)

/** Phase and Gain Registers start****/
#if ATBM2040_GAIN_PHASE_COMPENSATION
static ATBM2040Reg_t LNAPhaseReg[]=
{
    {0x15,0xB1, 0x00},
    {0x15,0xB2, 0x00},
    {0x15,0xB3, 0x00},
    {0x15,0xB4, 0x00},
    {0x15,0xB5, 0x00},
    {0x15,0xB6, 0x00},
    {0x15,0xB7, 0x00},
    {0x15,0xB8, 0x00},
    {0x15,0xB9, 0x00},
    {0x15,0xBA, 0x00},
    {0x15,0xBB, 0x00},
    {0x15,0xBC, 0x00},
    {0x15,0xBD, 0x00},
    {0x15,0xBE, 0x00},
    {0x15,0xBF, 0x00},
    {0x15,0xC0, 0x00},
    {0x15,0xC1, 0x00},
    {0x15,0xC2, 0x00},
    {0x15,0xC3, 0x00},
    {0x15,0xC4, 0x00},
    {0x15,0xC5, 0x00},
    {0x15,0xC6, 0x00},
    {0x15,0xC7, 0x00},
    {0x15,0xC8, 0x00},
    {0x15,0xC9, 0x00},
    {0x15,0xCA, 0x00},
    {0x15,0xCB, 0x00},
    {0x15,0xCC, 0x00},
    {0x15,0xCD, 0x00},
    {0x15,0xCE, 0x00},
    {0x15,0xCF, 0x00},
    {0x15,0xD0, 0x00},
    {0x15,0xD1, 0x00},
    {0x15,0xD2, 0x00},
    {0x15,0xD3, 0x00},
    {0x15,0xD4, 0x00},
    {0x15,0xD5, 0x00},
    {0x15,0xD6, 0x00},
    {0x15,0xD7, 0x00},
    {0x15,0xD8, 0x00},
    {0x15,0xD9, 0x00},
    {0x15,0xDA, 0x00},
    {0x15,0xDB, 0x00},
    {0x15,0xDC, 0x00},
    {0x15,0xDD, 0x00},
    {0x15,0xDE, 0x00},
    {0x15,0xDF, 0x00},
    {0x15,0xE0, 0x00},
    {0x15,0xE1, 0x00},
    {0x15,0xE2, 0x00},
    {0x15,0xE3, 0x00},
    {0x15,0xE4, 0x00},
    {0x15,0xE5, 0x00},
    {0x15,0xE6, 0x00},
    {0x15,0xE7, 0x00},
    {0x15,0xE8, 0x00},
    {0x15,0xE9, 0x00},
    {0x15,0xEA, 0x00},
    {0x15,0xEB, 0x00},
    {0x15,0xEC, 0x00},
    {0x15,0xED, 0x00},
    {0x15,0xEE, 0x00},
    {0x15,0xEF, 0x00},
    {0x15,0xF0, 0x00}
};
#define ATBM2040_LNA_PHASE_REG_CNT ATBM2040_ARRAY_NUM(LNAPhaseReg)

static ATBM2040Reg_t RFVGA1PhaseReg[]=
{
    {0x15,0x94, 0x00},
    {0x15,0x95, 0x00},
    {0x15,0x96, 0x00},
    {0x15,0x97, 0x00},
    {0x15,0x77, 0x00}
};
#define ATBM2040_RFVGA1_PHASE_REG_CNT ATBM2040_ARRAY_NUM(RFVGA1PhaseReg)


static ATBM2040Reg_t RFVGA2PhaseReg[]=
{
    {0x15,0x98, 0x00},
    {0x15,0x99, 0x00},
    {0x15,0x9A, 0x00},
    {0x15,0x9B, 0x00},
    {0x15,0x9C, 0x00}
};
#define ATBM2040_RFVGA2_PHASE_REG_CNT ATBM2040_ARRAY_NUM(RFVGA2PhaseReg)

static ATBM2040Reg_t IFVGA2PhaseReg[]=
{
    {0x15,0x9D, 0x00},
    {0x15,0x9E, 0x00},
    {0x15,0x9F, 0x00},
    {0x15,0xA0, 0x00},
    {0x15,0xA1, 0x00},
    {0x15,0xA2, 0x00},
    {0x15,0xA3, 0x00},
    {0x15,0xA4, 0x00},
    {0x15,0xA5, 0x00},
    {0x15,0xA6, 0x00},
    {0x15,0xA7, 0x00},
    {0x15,0xA8, 0x00},
    {0x15,0xA9, 0x00},
    {0x15,0xAA, 0x00},
    {0x15,0xAB, 0x00},
    {0x15,0xAC, 0x00},
    {0x15,0xAD, 0x00},
    {0x15,0xAE, 0x00},
    {0x15,0xAF, 0x00},
    {0x15,0xB0, 0x00}
};
#define ATBM2040_IFVGA2_PHASE_REG_CNT ATBM2040_ARRAY_NUM(IFVGA2PhaseReg)

static ATBM2040Reg_t LNAGainReg[]=
{
    {0x16,0x97, 0x00},
    {0x16,0x98, 0x00},
    {0x16,0x99, 0x00},
    {0x16,0x9A, 0x00},
    {0x16,0x9B, 0x00},
    {0x16,0x9C, 0x00},
    {0x16,0x9D, 0x00},
    {0x16,0x9E, 0x00},
    {0x16,0x9F, 0x00},
    {0x16,0xA0, 0x00},
    {0x16,0xA1, 0x00},
    {0x16,0xA2, 0x00},
    {0x16,0xA3, 0x00},
    {0x16,0xA4, 0x00},
    {0x16,0xA5, 0x00},
    {0x16,0xA6, 0x00},
    {0x16,0xA7, 0x00},
    {0x16,0xA8, 0x00},
    {0x16,0xA9, 0x00},
    {0x16,0xAA, 0x00},
    {0x16,0xAB, 0x00},
    {0x16,0xAC, 0x00},
    {0x16,0xAD, 0x00},
    {0x16,0xAE, 0x00},
    {0x16,0xAF, 0x00},
    {0x16,0xB0, 0x00},
    {0x16,0xB1, 0x00},
    {0x16,0xB2, 0x00},
    {0x16,0xB3, 0x00},
    {0x16,0xB4, 0x00},
    {0x16,0xB5, 0x00},
    {0x16,0xB6, 0x00}
};
#define ATBM2040_LNA_GAIN_REG_CNT ATBM2040_ARRAY_NUM(LNAGainReg)

static ATBM2040Reg_t RFVGA1GainReg[]=
{
    {0x16,0xB7, 0x00},
    {0x16,0xB8, 0x00},
    {0x16,0xB9, 0x00},
    {0x16,0xBA, 0x00},
    {0x16,0xBB, 0x00}
};
#define ATBM2040_RFVGA1_GAIN_REG_CNT ATBM2040_ARRAY_NUM(RFVGA1GainReg)

static ATBM2040Reg_t RFVGA2GainReg[]=
{
    {0x16,0xBC, 0x00},
    {0x16,0xBD, 0x00},
    {0x16,0xBE, 0x00},
    {0x16,0xBF, 0x00},
    {0x16,0xC0, 0x00}
};
#define ATBM2040_RFVGA2_GAIN_REG_CNT ATBM2040_ARRAY_NUM(RFVGA2GainReg)

static ATBM2040Reg_t IFVGA2GainReg[]=
{
    {0x16,0xC1, 0x00},
    {0x16,0xC2, 0x00},
    {0x16,0xC3, 0x00},
    {0x16,0xC4, 0x00},
    {0x16,0xC5, 0x00},
    {0x16,0xC6, 0x00},
    {0x16,0xC7, 0x00},
    {0x16,0xC8, 0x00},
    {0x16,0xC9, 0x00},
    {0x16,0xCA, 0x00},
    {0x16,0xCB, 0x00},
    {0x16,0xCC, 0x00},
    {0x16,0xCD, 0x00},
    {0x16,0xCE, 0x00},
    {0x16,0xCF, 0x00},
    {0x16,0xD0, 0x00},
    {0x16,0xD1, 0x00},
    {0x16,0xD2, 0x00},
    {0x16,0xD3, 0x00},
    {0x16,0xD4, 0x00}
};
#define ATBM2040_IFVGA2_GAIN_REG_CNT ATBM2040_ARRAY_NUM(IFVGA2GainReg)
#endif
/** Phase and Gain Registers end****/



static ATBM2040AgcPowerTarget_t AgcPowerTargetDTMB[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-25,    -18,    -22,    -21,    -17,        -25,    -18,    -22,    -21,    -17,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {100,    200,    {-27,    -19,    -21,    -22,    -18,        -27,    -19,    -21,    -22,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {200,    300,    {-27,    -19,    -22,    -22,    -16,        -27,    -19,    -22,    -22,    -16,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {300,    400,    {-28,    -20,    -21,    -21,    -16,        -28,    -20,    -21,    -21,    -16,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {400,    480,    {-28,    -20,    -25,    -24,    -18,        -28,    -20,    -25,    -24,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {480,    600,    {-30,    -21,    -26,    -26,    -18,        -30,    -21,    -26,    -26,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {600,    650,    {-32,    -22,    -28,    -24,    -18,        -32,    -22,    -28,    -24,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {650,    700,    {-30,    -23,    -26,    -26,    -18,        -30,    -23,    -26,    -26,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {700,    750,    {-32,    -24,    -28,    -26,    -18,        -32,    -24,    -28,    -26,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {750,    800,    {-32,    -26,    -27,    -27,    -18,        -32,    -26,    -27,    -27,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {800,    850,    {-31,    -27,    -26,    -26,    -16,        -31,    -27,    -26,    -26,    -16,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {850,    900,    {-31,    -27,    -27,    -26,    -20,        -31,    -27,    -27,    -26,    -20,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {900,    950,    {-32,    -28,    -26,    -27,    -22,        -32,    -28,    -26,    -27,    -22,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},
    {950,   2000,    {-32,    -28,    -28,    -28,    -22,        -32,    -28,    -28,    -28,    -22,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x70,    0x03,0x60}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};
static ATBM2040AgcPowerTarget_t AgcPowerTargetDVBT[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
     {000,    100,    {-28,    -26,    -26,    -23,    -18,        -28,    -28,    -26,    -23,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {100,    200,    {-29,    -26,    -27,    -23,    -17,        -29,    -28,    -27,    -23,    -17,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {200,    300,    {-28,    -28,    -25,    -24,    -16,        -28,    -28,    -25,    -24,    -16,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {300,    400,    {-29,    -20,    -24,    -24,    -16,        -29,    -28,    -24,    -24,    -16,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {400,    480,    {-29,    -24,    -26,    -24,    -18,        -29,    -28,    -26,    -24,    -18,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {480,    600,    {-30,    -20,    -28,    -26,    -20,        -30,    -28,    -28,    -26,    -20,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {600,    650,    {-30,    -22,    -28,    -26,    -19,        -30,    -28,    -28,    -26,    -19,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {650,    750,    {-30,    -22,    -28,    -26,    -21,        -30,    -28,    -28,    -26,    -21,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {750,    850,    {-30,    -24,    -29,    -27,    -21,        -30,    -28,    -29,    -27,    -21,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {850,    900,    {-32,    -26,    -29,    -27,    -23,        -32,    -28,    -29,    -27,    -23,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
     {900,   2000,    {-33,    -28,    -30,    -28,    -22,        -33,    -28,    -30,    -28,    -22,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};
static ATBM2040AgcPowerTarget_t AgcPowerTargetDVBC[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-28,    -16,    -27,    -26,    -22,        -28,    -28,    -27,    -26,    -22,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {100,    200,    {-28,    -15,    -26,    -26,    -23,        -28,    -28,    -26,    -26,    -23,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {200,    300,    {-28,    -14,    -26,    -26,    -23,        -28,    -28,    -26,    -26,    -23,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {300,    400,    {-28,    -13,    -25,    -27,    -24,        -28,    -28,    -25,    -27,    -24,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {400,    480,    {-30,    -12,    -28,    -28,    -23,        -30,    -28,    -28,    -28,    -23,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {480,    600,    {-32,    -26,    -29,    -30,    -24,        -32,    -28,    -29,    -30,    -24,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {600,    650,    {-32,    -25,    -28,    -30,    -24,        -32,    -28,    -28,    -30,    -24,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {650,    750,    {-33,    -24,    -29,    -32,    -23,        -33,    -28,    -29,    -32,    -23,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {750,    850,    {-33,    -23,    -30,    -29,    -25,        -33,    -28,    -30,    -29,    -25,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {850,    900,    {-34,    -21,    -32,    -31,    -23,        -34,    -28,    -32,    -31,    -23,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {900,   2000,    {-32,    -19,    -32,    -32,    -26,        -32,    -28,    -32,    -32,    -26,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};


static ATBM2040AgcPowerTarget_t AgcPowerTargetATV[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {100,    200,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {200,    300,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {300,    400,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {400,    480,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {480,    600,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {600,    650,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {650,    700,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {700,    750,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {750,    800,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {800,    850,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {850,    900,    {-28,    -28,    -28,    -28,    -28,        -28,    -28,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {900,    950,    {-32,    -32,    -32,    -32,    -32,        -28,    -32,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
    {950,   2000,    {-32,    -32,    -32,    -32,    -32,        -28,    -32,    -28,    -28,    -28,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x80}},
 
    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoCAgcPowerTargetDTMB[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-24,    -18,    -20,    -17,    -13,        -24,    -18,    -20,    -17,    -13,        0x03,0x40,    0x03,0x80,    0x03,0x30,    0x03,0x60,    0x03,0x30}},
    {100,    200,    {-24,    -19,    -20,    -19,    -12,        -24,    -19,    -20,    -19,    -12,        0x03,0x40,    0x03,0x80,    0x03,0x30,    0x03,0x70,    0x03,0x30}},
    {200,    300,    {-24,    -19,    -20,    -19,    -12,        -24,    -19,    -20,    -19,    -12,        0x03,0x30,    0x03,0x80,    0x03,0x20,    0x03,0x70,    0x03,0x20}},
    {300,    400,    {-24,    -20,    -20,    -21,    -12,        -24,    -20,    -20,    -21,    -12,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x60,    0x03,0x20}},
    {400,    480,    {-24,    -20,    -22,    -22,    -12,        -24,    -20,    -22,    -22,    -12,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x40,    0x03,0x10}},
    {480,    600,    {-26,    -21,    -22,    -22,    -12,        -26,    -21,    -22,    -22,    -12,        0x03,0x20,    0x03,0x80,    0x03,0x10,    0x03,0x20,    0x03,0x10}},
    {600,    700,    {-26,    -22,    -23,    -22,    -14,        -26,    -22,    -23,    -22,    -14,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x70,    0x03,0x30}},
    {700,    800,    {-27,    -23,    -25,    -24,    -15,        -27,    -23,    -25,    -24,    -15,        0x03,0x30,    0x03,0x80,    0x03,0x20,    0x03,0x60,    0x03,0x30}},
    {800,    900,    {-27,    -24,    -28,    -26,    -18,        -27,    -24,    -28,    -26,    -18,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x20}},
    {900,   2000,    {-26,    -28,    -27,    -28,    -19,        -26,    -28,    -27,    -28,    -19,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x20}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};
static ATBM2040AgcPowerTarget_t LeoCAgcPowerTargetDVBT[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-27,    -26,    -25,    -18,    -14,        -27,    -28,    -25,    -18,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x30}},
    {100,    200,    {-31,    -26,    -24,    -16,    -14,        -31,    -28,    -24,    -16,    -14,        0x03,0x20,    0x03,0x80,    0x03,0x20,    0x03,0x20,    0x03,0x30}},
    {200,    300,    {-28,    -28,    -24,    -16,    -14,        -28,    -28,    -24,    -16,    -14,        0x03,0x40,    0x03,0x80,    0x03,0x00,    0x03,0x20,    0x03,0x30}},
    {300,    400,    {-28,    -20,    -20,    -18,    -14,        -28,    -28,    -20,    -18,    -14,        0x03,0x40,    0x03,0x80,    0x03,0x60,    0x03,0x40,    0x03,0x30}},
    {400,    480,    {-30,    -24,    -23,    -18,    -14,        -30,    -28,    -23,    -18,    -14,        0x03,0x10,    0x03,0x80,    0x03,0x20,    0x03,0x30,    0x03,0x30}},
    {480,    600,    {-30,    -20,    -20,    -19,    -14,        -30,    -28,    -20,    -19,    -14,        0x03,0x40,    0x03,0x80,    0x03,0x00,    0x03,0x40,    0x03,0x30}},
    {600,    650,    {-31,    -22,    -21,    -20,    -15,        -31,    -28,    -21,    -20,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x10,    0x03,0x40,    0x03,0x50}},
    {650,    750,    {-31,    -22,    -23,    -22,    -17,        -31,    -28,    -23,    -22,    -17,        0x03,0x30,    0x03,0x80,    0x03,0x30,    0x03,0x40,    0x03,0x40}},
    {750,    850,    {-30,    -24,    -24,    -22,    -18,        -30,    -28,    -24,    -22,    -18,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x40,    0x03,0x30}},
    {850,    900,    {-33,    -26,    -23,    -22,    -18,        -33,    -28,    -23,    -22,    -18,        0x03,0x50,    0x03,0x80,    0x03,0x20,    0x03,0x50,    0x03,0x30}},
    {900,   2000,    {-30,    -28,    -24,    -22,    -18,        -30,    -28,    -24,    -22,    -18,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x60,    0x03,0x50}},
    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoCAgcPowerTargetATV[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-28,    -16,    -28,    -18,    -15,        -28,    -16,    -28,    -18,    -15,        0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {100,    200,    {-28,    -17,    -28,    -18,    -16,        -28,    -17,    -28,    -18,    -16,        0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {200,    300,    {-28,    -17,    -28,    -18,    -16,        -28,    -17,    -28,    -18,    -16,        0x03,0x80,    0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x40}},
    {300,    400,    {-28,    -17,    -28,    -18,    -17,        -28,    -17,    -28,    -18,    -17,        0x03,0x80,    0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {400,    480,    {-28,    -17,    -28,    -19,    -17,        -28,    -17,    -28,    -19,    -17,        0x03,0x80,    0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {480,    600,    {-28,    -16,    -28,    -19,    -16,        -28,    -16,    -28,    -19,    -16,        0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {600,    700,    {-28,    -16,    -28,    -19,    -16,        -28,    -16,    -28,    -19,    -16,        0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {700,    800,    {-28,    -16,    -28,    -19,    -15,        -28,    -16,    -28,    -19,    -15,        0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {800,    900,    {-28,    -16,    -28,    -19,    -16,        -28,    -16,    -28,    -19,    -16,        0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {900,   2000,    {-28,    -16,    -28,    -19,    -16,        -28,    -16,    -28,    -19,    -16,        0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
 
    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoEAgcPowerTargetDTMB[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-22,    -18,    -21,    -20,    -14,        -22,    -18,    -21,    -20,    -14,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x60,    0x03,0x30}},
    {100,    160,    {-22,    -19,    -21,    -20,    -14,        -22,    -19,    -21,    -20,    -14,        0x03,0x40,    0x03,0x80,    0x03,0x30,    0x03,0x70,    0x03,0x30}},
    {160,    300,    {-22,    -19,    -19,    -18,    -17,        -22,    -19,    -19,    -18,    -17,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x70,    0x03,0x20}},
    {300,    400,    {-22,    -20,    -19,    -18,    -17,        -22,    -20,    -19,    -18,    -17,        0x03,0x40,    0x03,0x80,    0x03,0x30,    0x03,0x80,    0x03,0x20}},
    {400,    480,    {-22,    -20,    -15,    -14,    -16,        -22,    -20,    -15,    -14,    -16,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x60,    0x03,0x10}},
    {480,    600,    {-22,    -21,    -15,    -14,    -16,        -22,    -21,    -15,    -14,    -16,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x10}},
    {600,    700,    {-22,    -22,    -15,    -14,    -16,        -22,    -22,    -15,    -14,    -16,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x30}},
    {700,    800,    {-22,    -23,    -14,    -14,    -15,        -22,    -23,    -14,    -14,    -15,        0x03,0x30,    0x03,0x80,    0x03,0x40,    0x03,0x80,    0x03,0x30}},
    {800,    900,    {-22,    -24,    -14,    -14,    -15,        -22,    -24,    -14,    -14,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x20}},
    {900,   2000,    {-22,    -28,    -14,    -14,    -15,        -22,    -28,    -14,    -14,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x20}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};
static ATBM2040AgcPowerTarget_t LeoEAgcPowerTargetDVBT[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
     {000,    100,    {-25,    -26,    -20,    -20,    -14,        -25,    -28,    -20,    -20,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x20,    0x03,0x80,    0x03,0x30}},
     {100,    160,    {-25,    -26,    -20,    -20,    -14,        -25,    -28,    -20,    -20,    -14,        0x03,0x20,    0x03,0x80,    0x03,0x20,    0x03,0x20,    0x03,0x30}},
     {160,    300,    {-23,    -28,    -20,    -18,    -15,        -23,    -28,    -20,    -18,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x00,    0x03,0x20,    0x03,0x30}},
     {300,    400,    {-23,    -20,    -20,    -18,    -15,        -23,    -28,    -20,    -18,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x60,    0x03,0x40,    0x03,0x30}},
     {400,    480,    {-23,    -24,    -16,    -14,    -16,        -23,    -28,    -16,    -14,    -16,        0x03,0x10,    0x03,0x80,    0x03,0x20,    0x03,0x30,    0x03,0x30}},
     {480,    600,    {-23,    -20,    -16,    -14,    -16,        -23,    -28,    -16,    -14,    -16,        0x03,0x40,    0x03,0x80,    0x03,0x00,    0x03,0x40,    0x03,0x30}},
     {600,    700,    {-22,    -22,    -15,    -14,    -15,        -22,    -28,    -15,    -14,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x10,    0x03,0x40,    0x03,0x50}},
     {700,    800,    {-22,    -22,    -15,    -14,    -15,        -22,    -28,    -15,    -14,    -15,        0x03,0x30,    0x03,0x80,    0x03,0x40,    0x03,0x40,    0x03,0x20}},
     {800,    900,    {-22,    -24,    -15,    -14,    -15,        -22,    -28,    -15,    -14,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x40,    0x03,0x30}},
     {900,   2000,    {-22,    -28,    -15,    -14,    -15,        -22,    -28,    -15,    -14,    -15,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x60,    0x03,0x50}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoEAgcPowerTargetDVBC[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
     {000,    100,    {-22,    -16,    -20,    -20,    -13,        -22,    -28,    -20,    -20,    -13,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {100,    160,    {-22,    -15,    -20,    -20,    -13,        -22,    -28,    -20,    -20,    -13,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {160,    300,    {-21,    -14,    -15,    -16,    -15,        -21,    -28,    -15,    -16,    -15,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {300,    400,    {-21,    -13,    -15,    -16,    -15,        -21,    -28,    -15,    -16,    -15,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {400,    480,    {-20,    -12,    -16,    -17,    -17,        -20,    -28,    -16,    -17,    -17,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {480,    600,    {-20,    -26,    -16,    -17,    -17,        -20,    -28,    -16,    -17,    -17,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {600,    700,    {-20,    -25,    -16,    -16,    -16,        -20,    -28,    -16,    -16,    -16,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {700,    800,    {-20,    -23,    -16,    -16,    -16,        -20,    -28,    -16,    -16,    -16,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {800,    900,    {-20,    -21,    -16,    -16,    -16,        -20,    -28,    -16,    -16,    -16,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},
     {900,   2000,    {-20,    -19,    -16,    -16,    -16,        -20,    -28,    -16,    -16,    -16,        0x03,0x40,    0x03,0x40,    0x03,0x60,    0x03,0xA0,    0x03,0x80}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};
static ATBM2040AgcPowerTarget_t LeoEAgcPowerTargetATV[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-28,    -21,    -28,    -26,    -15,        -28,    -21,    -28,    -26,    -15,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {100,    160,    {-28,    -21,    -28,    -26,    -15,        -28,    -21,    -28,    -26,    -15,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {160,    200,    {-28,    -22,    -28,    -26,    -14,        -28,    -22,    -28,    -26,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x40}},
    {200,    300,    {-28,    -22,    -28,    -26,    -14,        -28,    -22,    -28,    -26,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x40}},
    {300,    400,    {-28,    -22,    -28,    -26,    -14,        -28,    -22,    -28,    -26,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {400,    480,    {-28,    -19,    -28,    -24,    -14,        -28,    -19,    -28,    -24,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {480,    600,    {-28,    -19,    -28,    -24,    -14,        -28,    -19,    -28,    -24,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20}},
    {600,    700,    {-28,    -19,    -28,    -24,    -14,        -28,    -19,    -28,    -24,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {700,    800,    {-28,    -18,    -28,    -20,    -14,        -28,    -18,    -28,    -20,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {800,    900,    {-28,    -18,    -28,    -20,    -14,        -28,    -18,    -28,    -20,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00}},
    {900,   2000,    {-28,    -18,    -28,    -20,    -14,        -28,    -18,    -28,    -20,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoGAgcPowerTargetDTMB[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-20,    -26,    -20,    -18,    -14,        -20,    -26,    -20,    -18,    -14,        0x03,0x20,    0x03,0x20,    0x03,0x40,    0x03,0x60,    0x03,0x20,  -12,  -12,  - 9,  - 9,  - 9}}, 
    {100,    160,    {-20,    -26,    -20,    -17,    -14,        -20,    -26,    -20,    -17,    -14,        0x03,0x20,    0x03,0x20,    0x03,0x30,    0x03,0x70,    0x03,0x20,  -14,  -14,  -11,  -11,  -11}}, 
    {160,    300,    {-20,    -28,    -20,    -15,    -15,        -20,    -28,    -20,    -15,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x70,    0x03,0x20,  - 9,  - 9,  - 9,  - 9,  - 9}}, 
    {300,    400,    {-20,    -20,    -17,    -14,    -15,        -20,    -20,    -17,    -14,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x30,    0x03,0x80,    0x03,0x20,  - 8,  - 8,  - 9,  - 9,  - 9}}, 
    {400,    480,    {-20,    -24,    -17,    -20,    -16,        -20,    -24,    -17,    -20,    -16,        0x03,0x20,    0x03,0x20,    0x03,0x40,    0x03,0x60,    0x03,0x20,  - 8,  - 8,  - 7,  - 8,  - 8}}, 
    {480,    600,    {-19,    -20,    -18,    -20,    -16,        -19,    -20,    -18,    -20,    -16,        0x03,0x20,    0x03,0x20,    0x03,0x40,    0x03,0x70,    0x03,0x20,  -12,  -12,  - 8,  - 7,  - 7}}, 
    {600,    700,    {-20,    -22,    -19,    -20,    -15,        -20,    -22,    -19,    -20,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x40,    0x03,0x70,    0x03,0x20,  -13,  -13,  - 9,  - 8,  - 8}}, 
    {700,    800,    {-18,    -22,    -17,    -18,    -15,        -18,    -22,    -17,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x40,    0x03,0x80,    0x03,0x20,  -10,  -10,  - 7,  - 6,  - 6}}, 
    {800,    900,    {-18,    -24,    -17,    -18,    -15,        -18,    -24,    -17,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x40,    0x03,0x70,    0x03,0x20,  -10,  -10,  - 6,  - 6,  - 6}}, 
    {900,   2000,    {-16,    -28,    -19,    -21,    -15,        -16,    -28,    -19,    -21,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x40,    0x03,0x70,    0x03,0x20,  -13,  -13,  -13,  -13,  -13}}, 

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoGAgcPowerTargetDVBC[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-23,    -26,    -17,    -18,    -14,        -23,    -26,    -17,    -18,    -14,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -12,  - 9,  - 9,  - 9}},
    {100,    160,    {-23,    -26,    -19,    -18,    -14,        -23,    -26,    -19,    -18,    -14,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -14,  -11,  -11,  -11}},
    {160,    300,    {-22,    -28,    -18,    -18,    -15,        -22,    -28,    -18,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -11,  - 9,  - 9,  - 9}},
    {300,    400,    {-21,    -20,    -17,    -18,    -15,        -21,    -20,    -17,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -11,  - 9,  - 9,  - 9}},
    {400,    480,    {-24,    -24,    -18,    -20,    -16,        -24,    -24,    -18,    -20,    -16,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -11,  - 7,  - 8,  - 8}},
    {480,    600,    {-22,    -20,    -19,    -20,    -16,        -22,    -20,    -19,    -20,    -16,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -12,  - 8,  - 7,  - 7}},
    {600,    679,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -13,  - 9,  - 8,  - 8}},
    {679,    700,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x02,0x80,  -15,  -13,  - 9,  - 8,  - 8}},
    {700,    779,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -10,  - 7,  - 6,  - 6}},
    {779,    800,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x02,0x80,  -15,  -10,  - 7,  - 6,  - 6}},
    {800,    900,    {-22,    -24,    -17,    -18,    -15,        -22,    -24,    -17,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -10,  - 6,  - 6,  - 6}},
    {900,   2000,    {-17,    -28,    -19,    -18,    -15,        -17,    -28,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -13,  -13,  -13,  -13}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoGAgcPowerTargetDVBT[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-23,    -26,    -17,    -18,    -14,        -23,    -26,    -17,    -18,    -14,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -12,  - 9,  - 9,  - 9}},
    {100,    160,    {-23,    -26,    -19,    -18,    -14,        -23,    -26,    -19,    -18,    -14,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -14,  -11,  -11,  -11}},
    {160,    300,    {-22,    -28,    -18,    -18,    -15,        -22,    -28,    -18,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -11,  - 9,  - 9,  - 9}},
    {300,    400,    {-21,    -20,    -17,    -18,    -15,        -21,    -20,    -17,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -11,  - 9,  - 9,  - 9}},
    {400,    480,    {-24,    -24,    -18,    -20,    -16,        -24,    -24,    -18,    -20,    -16,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -11,  - 7,  - 8,  - 8}},
    {480,    600,    {-22,    -20,    -19,    -20,    -16,        -22,    -20,    -19,    -20,    -16,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -12,  - 8,  - 7,  - 7}},
    {600,    679,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -13,  - 9,  - 8,  - 8}},
    {679,    700,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x02,0x80,  -15,  -13,  - 9,  - 8,  - 8}},
    {700,    779,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -10,  - 7,  - 6,  - 6}},
    {779,    800,    {-23,    -22,    -19,    -18,    -15,        -23,    -22,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x02,0x80,  -15,  -10,  - 7,  - 6,  - 6}},
    {800,    900,    {-22,    -24,    -17,    -18,    -15,        -22,    -24,    -17,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -10,  - 6,  - 6,  - 6}},
    {900,   2000,    {-17,    -28,    -19,    -18,    -15,        -17,    -28,    -19,    -18,    -15,        0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,    0x03,0x20,  -15,  -13,  -13,  -13,  -13}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoGAgcPowerTargetATV[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-28,    -24,    -28,    -12,    -15,        -28,    -24,    -28,    -12,    -15,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00,  -12,  -12,  - 9,  - 9,  - 9}},   
    {100,    160,    {-28,    -24,    -28,    -12,    -15,        -28,    -24,    -28,    -12,    -15,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20,  -14,  -14,  -11,  -11,  -11}},    
    {160,    200,    {-28,    -23,    -28,    -12,    -14,        -28,    -23,    -28,    -12,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x40,  - 9,  - 9,  - 9,  - 9,  - 9}},    
    {200,    300,    {-28,    -23,    -28,    -12,    -14,        -28,    -23,    -28,    -12,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x40,  - 9,  - 9,  - 9,  - 9,  - 9}},    
    {300,    400,    {-28,    -23,    -28,    -12,    -14,        -28,    -23,    -28,    -12,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20,  - 8,  - 8,  - 9,  - 9,  - 9}},    
    {400,    480,    {-28,    -22,    -28,    -15,    -22,        -28,    -26,    -28,    -15,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20,  - 8,  - 8,  - 7,  - 8,  - 8}},    
    {480,    600,    {-28,    -22,    -28,    -15,    -20,        -28,    -26,    -28,    -15,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x20,  -12,  -12,  - 8,  - 7,  - 7}},    
    {600,    700,    {-28,    -22,    -28,    -15,    -17,        -28,    -26,    -28,    -15,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00,  -13,  -13,  - 9,  - 8,  - 8}},    
    {700,    800,    {-28,    -22,    -28,    -13,    -17,        -28,    -24,    -28,    -13,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00,  -10,  -10,  - 7,  - 6,  - 6}},    
    {800,    900,    {-28,    -22,    -28,    -13,    -17,        -28,    -24,    -28,    -13,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00,  -10,  -10,  - 6,  - 6,  - 6}},    
    {900,   2000,    {-28,    -22,    -28,    -13,    -17,        -28,    -24,    -28,    -13,    -14,        0x03,0x80,    0x03,0x80,    0x03,0x80,    0x03,0x40,    0x03,0x00,  -13,  -13,  -13,  -13,  -13}}, 

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};

static ATBM2040AgcPowerTarget_t LeoGAgcPowerTargetATSC[]=
{
/*    start    end                     rssi_lna_out                                    rssi_lna_out2                                    bb_power_target
                                     DTV     ATV     DTV     ATV    N+-M        DTV          ATV           DTV           ATV        N+-M
                                    aci_0    aci_1    aci_2    aci_3    aci_4        aci_0    aci_1    aci_2    aci_3    aci_4             aci 0         aci 1      aci 2             aci 3             aci_4*/
    {000,    100,    {-20,    -26,    -20,    -18,    -10,        -20,    -26,    -20,    -20,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x60,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {100,    160,    {-20,    -26,    -20,    -17,    -10,        -20,    -26,    -20,    -22,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x30,    0x03,0x70,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {160,    300,    {-20,    -28,    -20,    -15,    -10,        -20,    -28,    -20,    -20,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x20,    0x03,0x70,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {300,    400,    {-20,    -20,    -20,    -14,    -10,        -20,    -20,    -20,    -19,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x30,    0x03,0x80,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {400,    480,    {-20,    -24,    -20,    -17,    -10,        -20,    -24,    -20,    -22,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x60,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {480,    600,    {-19,    -20,    -20,    -18,    -10,        -19,    -20,    -20,    -22,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {600,    700,    {-20,    -22,    -20,    -20,    -10,        -20,    -22,    -20,    -22,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {700,    800,    {-18,    -22,    -20,    -16,    -10,        -18,    -22,    -20,    -20,    -10,        0x03,0x30,    0x03,0x80,    0x03,0x40,    0x03,0x80,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {800,    900,    {-18,    -24,    -20,    -17,    -10,        -18,    -24,    -20,    -20,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},
    {900,   2000,    {-16,    -28,    -20,    -21,    -10,        -16,    -28,    -20,    -20,    -10,        0x03,0x40,    0x03,0x80,    0x03,0x40,    0x03,0x70,    0x03,0x80,  -13,  -11,  -6,  -6,  -6}},

    {0,  0,	{0,	0,	0,	0,	0,		0,	0,	0,	0,	0,		0,0,	0,0,	0,0,	0,0,	0,0}}, /* End Flag */
};


#ifdef ATBM2040_CHIP_DEBUG_OPEN
static ATBM2040Reg_t AgcPowerTargetReg[]=
{
    {0x14,0x58, 0x67}, /* -25dB for rssi_lna_out_aci_0 */
    {0x14,0x59, 0x69}, /* -23dB for rssi_lna_out aci_1 */
    {0x14,0x5A, 0x67}, /* -25dB for rssi_lna_out aci_2 */
    {0x14,0x5B, 0x69}, /* -23dB for rssi_lna_out aci_3   */
    {0x14,0x5C, 0x67}, /* aci_4 */

    {0x17,0xF1, 0x64}, /* params_rssi_lna_out_aci_status_0_alter */
    {0x17,0xF2, 0x64}, /* params_rssi_lna_out_aci_status_1_alter */
    {0x17,0xF3, 0x64}, /* params_rssi_lna_out_aci_status_2_alter */
    {0x17,0xF4, 0x64}, /* params_rssi_lna_out_aci_status_3_alter */
    {0x17,0xF5, 0x64}, /* params_rssi_lna_out_aci_status_4_alter */

    {0x14,0x19, 0x03}, /* bb_power_target for aci 0 high byte */
    {0x14,0x18, 0xA0}, /*  58  */
    {0x14,0x1B, 0x03}, /* bb_power_target for aci 1 high byte */
    {0x14,0x1A, 0xA0}, /* 58 */
    {0x14,0x1D, 0x03}, /* bb_power_target for aci 2 high byte */
    {0x14,0x1C, 0xA0}, /*  58 */
    {0x14,0x1F, 0x03}, /* bb_power_target for aci 3 high byte */
    {0x14,0x1E, 0xA0}, /*  e0 58  */
    {0x14,0x21, 0x03}, /* bb_power_target for aci 4 high byte */
    {0x14,0x20, 0xA0}, /*  e0 58 */
    
    {0x23,0x48, 0x00}, /* params_rssi_lna_out_aci_status_4_n_2_4_co_exsit */
    {0x23,0x49, 0x00}, /* params_rssi_lna_out_aci_status_4_n_2_large */
    {0x23,0x4A, 0x00}, /* params_rssi_lna_out_aci_status_4_n_3_large */
    {0x23,0x4B, 0x00}, /* params_rssi_lna_out_aci_status_4_n_large_m_large */
    {0x23,0x4C, 0x00}, /* params_rssi_lna_out_aci_status_4_normal_mode */

};
#define ATBM2040_AGC_POW_TARGET_REG_CNT ATBM2040_ARRAY_NUM(AgcPowerTargetReg)
#endif

typedef struct
{
    /*PAPR LIMIT    */
    UINT8 Ana2DigThr;/*0x14,0x11*/
    UINT8 Dig2AnaThr;/*0x14,0x36*/
    UINT8 IntialAnaDigJudge;/*0x16,0x3F*/
    /*BB POWER*/
    UINT8 BBPowerAnaSumNum;/*0x14,0x24*/
    UINT8 BBSumLen;/*0x14,0x25*/

    UINT8 Dagc1AmpRef1Low;/*0x15,0x70*/
    UINT8 Dagc1AmpRef1High;/*0x15,0x71*/
    UINT8 Dagc1AmpRef0Low;/*0x15,0x5D*/
    UINT8 Dagc1AmpRef0High;/*0x15,0x5E*/
    UINT8 Dagc2AmpRef1Low;/*0x15,0x40*/
    UINT8 Dagc2AmpRef1High;/*0x15,0x41*/
    UINT8 Dagc2AmpRef0Low;/*0x13,0xA6*/
    UINT8 Dagc2AmpRef0High;/*0x13,0xA7*/

}DagcAmpRef_t;
static DagcAmpRef_t DagcAmpRefDTMB =
{
    0x08, /*ana2dig thr*/
    0x04, /*ana2dig thr*/
    0x00, /*initial a/d judge*/
    0x0F, /*bb power sum num analog*/
    0x12, /*bb power sum len*/
    0x80, /*params_dagc1_amp_ref_1[7:0]*/
    0x04, /*params_dagc1_amp_ref_1[9:8]*/
    0x80, /*params_dagc1_amp_ref_0[7:0]*/
    0x04, /*params_dagc1_amp_ref_0[9:8]*/
    0x80, /*params_dagc2_amp_ref_1[7:0]*/
    0x04, /*params_dagc2_amp_ref_1[9:8]*/
    0x80, /*params_dagc2_amp_ref_0[7:0]*/
    0x04, /*params_dagc2_amp_ref_0[9:8]*/
};
static DagcAmpRef_t DagcAmpRefDVBT =
{
    0x08, /*ana2dig thr*/
    0x04, /*ana2dig thr*/
    0x00, /*initial a/d judge*/
    0x0F, /*bb power sum num analog*/
    0x12, /*bb power sum len*/
    0x40, /*params_dagc1_amp_ref_1[7:0]*/
    0x04, /*params_dagc1_amp_ref_1[9:8]*/
    0x40, /*params_dagc1_amp_ref_0[7:0]*/
    0x04, /*params_dagc1_amp_ref_0[9:8]*/
    0x40, /*params_dagc2_amp_ref_1[7:0]*/
    0x04, /*params_dagc2_amp_ref_1[9:8]*/
    0x40, /*params_dagc2_amp_ref_0[7:0]*/
    0x04, /*params_dagc2_amp_ref_0[9:8]*/
};
static DagcAmpRef_t DagcAmpRefDVBC =
{
    0x08, /*ana2dig thr*/
    0x04, /*ana2dig thr*/
    0x00, /*initial a/d judge*/
    0x0F, /*bb power sum num analog*/
    0x12, /*bb power sum len*/
    0x80, /*params_dagc1_amp_ref_1[7:0]*/
    0x04, /*params_dagc1_amp_ref_1[9:8]*/
    0x80, /*params_dagc1_amp_ref_0[7:0]*/
    0x04, /*params_dagc1_amp_ref_0[9:8]*/
    0x80, /*params_dagc2_amp_ref_1[7:0]*/
    0x04, /*params_dagc2_amp_ref_1[9:8]*/
    0x80, /*params_dagc2_amp_ref_0[7:0]*/
    0x04, /*params_dagc2_amp_ref_0[9:8]*/
};
static DagcAmpRef_t DagcAmpRefAnalog =
{
    0x09, /*ana2dig thr*/
    0x06, /*dig2ana thr*/
    0x00, /*initial a/d judge    */
    0x1F, /* bb power sum num analog*/
    0x12, /* bb power sum len*/
    0x80, /*params_dagc1_amp_ref_1[7:0]*/
    0x04, /*params_dagc1_amp_ref_1[9:8]*/
    0x80, /*params_dagc1_amp_ref_0[7:0]*/
    0x04, /*params_dagc1_amp_ref_0[9:8]*/
    0x80, /*params_dagc2_amp_ref_1[7:0]*/
    0x04, /*params_dagc2_amp_ref_1[9:8]*/
    0x80, /*params_dagc2_amp_ref_0[7:0]*/
    0x04, /*params_dagc2_amp_ref_0[9:8]*/
};
static ATBM2040Reg_t DagcAmpRefReg[]=
{/*the register value will be repleaced by 'DagcAmpRefxxx'*/
    {0x14,0x11, 0x08},     /* ana2dig thr */
    {0x14,0x36, 0x04},     /* dig2ana thr */
    {0x16,0x3F, 0x00},    /* initial a/d judge     */

    {0x14,0x24, 0x0F},     /* bb power sum num analog */
    {0x14,0x25, 0x12},     /* bb power sum len */

    {0x15,0x70, 0x80},     /*params_dagc1_amp_ref_1[7:0]*/
    {0x15,0x71, 0x04},     /*params_dagc1_amp_ref_1[9:8]*/
    {0x15,0x5D, 0x80},     /*params_dagc1_amp_ref_0[7:0]*/
    {0x15,0x5E, 0x04},     /*params_dagc1_amp_ref_0[9:8]*/
    {0x15,0x40, 0x80},     /*params_dagc2_amp_ref_1[7:0]*/
    {0x15,0x41, 0x04},     /*params_dagc2_amp_ref_1[9:8]*/
    {0x13,0xA6, 0x80},     /*params_dagc2_amp_ref_0[7:0]*/
    {0x13,0xA7, 0x04},     /*params_dagc2_amp_ref_0[9:8]*/
};
#define ATBM2040_DAGC_AMP_REF_REG_CNT ATBM2040_ARRAY_NUM(DagcAmpRefReg)

static ATBM2040RegGroup_t DTVRSSIReg =
{/*from 0x16,0x23 to 0x16,0x2A*/
    0x16,0x23,
    {   0x06, /* 0x16,0x23 rssi lna out alpha n analog ini  */
        0x09, /* 0x16,0x24 rssi lna out alpha n analog tracking */
        0x06, /* 0x16,0x25 rssi lna out alpha n digital ini */
        0x09, /* 0x16,0x26 rssi lna out alpha n digital tracking */
        0x00, /* 0x16,0x27 params_rssi_lna_out_filter_swap */  
        0x00, /* 0x16,0x28 rssi lna out sum len [7:0] */    
        0x01, /* 0x16,0x29 rssi lna out sum len [13:8]  */
        0x18, /* 0x16,0x2A params_rssi_lna_out_sum_len_db[5:0]  */
    },
    8
};

static ATBM2040RegGroup_t ATVRSSIReg =
{/*from 0x16,0x23 to 0x16,0x2A*/
    0x16,0x23,
    {   0x03, /* 0x16,0x23 rssi lna out alpha n analog ini  */
        0x03, /* 0x16,0x24 rssi lna out alpha n analog tracking */
        0x03, /* 0x16,0x25 rssi lna out alpha n digital ini */
        0x03, /* 0x16,0x26 rssi lna out alpha n digital tracking */
        0x00, /* 0x16,0x27 params_rssi_lna_out_filter_swap */  
        0x00, /* 0x16,0x28 rssi lna out sum len [7:0] */    
        0x01, /* 0x16,0x29 rssi lna out sum len [13:8]  */
        0x18, /* 0x16,0x2A params_rssi_lna_out_sum_len_db[5:0]  */
    },
    8
};


static ATBM2040Reg_t DSPMiscReg[]=
{
    {0x14,0x95, 0x30}, /* data 12bit gain */
    {0x14,0x96, 0x04}, /* params_if_filter_gain_aci_db[6:0] */

    {0x17,0x46, 0x01}, /*  papr_spec_logic 0:papr 1:spectrum */

    {0x17,0x90, 0x01}, /* params_aci_status_judge_double_thr */

    {0x17,0x96, 0x1E}, /* params_use_preset_lo_thr_dynamic */

    {0x18,0x00, 0x01}, /* params_fir0_bypass */    

    {0x19,0xB0, 0x2C}, /* inband_aci_db */

    {0x23,0x08, 0x00}, /* params_use_lte_n_2_4_diff_joint */
};
#define ATBM2040_DSP_MISC_REG_CNT ATBM2040_ARRAY_NUM(DSPMiscReg)

static ATBM2040Reg_t DSPDTVReg[]=
{
    {0x14,0x15, 0x00}, /* b_analog_default */
    {0x14,0x4E, 0x12}, /* params_lo_change_thr_db[4:0] */
    {0x16,0x1B, 0x31},/*params_lar2sma_thr[5:0]  lar2sma  -12  -20    -25  -20*/
    {0x16,0x35, 0x2C},/*params_sma2lar_thr[5:0]  sma2lar  -14  -25    -20  -25*/

    {0x17,0x42, 0x00}, /*  bypass notch aci detection */
    {0x17,0x43, 0x20}, /* thr for peak power */
    {0x1A,0x5A, 0x00}, /* params_use_narrow_band_filter_iq_compensation */

    /*{0x1A,0x70, 0x01}, */ /* bypass lna gain thr change */
    {0x1A,0x41, 0x01}, /* bypass sfi_1_detect */

};
#define ATBM2040_DSP_DTV_REG_CNT ATBM2040_ARRAY_NUM(DSPDTVReg)

static ATBM2040Reg_t DSPATVReg[]=
{
    {0x13,0x03, 0x03}, /* params_dagc_k[2:0] */
    {0x13,0x04, 0x04}, /* params_dagc_alpha_0[2:0]  */
    
    {0x14,0x15, 0x01}, /* b_analog_default */
    {0x14,0x4E, 0x10}, /* params_lo_change_thr_db[4:0] */
    {0x16,0x1B, 0x31},/*params_lar2sma_thr[5:0]  lar2sma  -12  -20    -25  -20*/
    {0x16,0x35, 0x27},/*params_sma2lar_thr[5:0]  sma2lar  -14  -25    -20  -25*/

    /* narw band filter */
    {0x1A,0x5A, 0x01}, /* params_use_narrow_band_filter_iq_compensation    [0]        1    U(1,0) */
    {0x1A,0x5F, 0x0D}, /* params_iir_filter_gen_bw[7:0]    U(16,-8),28; */
    {0x1A,0x60, 0x03}, /* params_iir_filter_gen_bw[15:8]    ,09 */
    {0x1A,0x62, 0x57}, /* params_thr_iq_narw_band_filter_l    [6:0]    S(7,0),14 */
    {0x1A,0x63, 0x5C}, /* params_thr_iq_narw_band_filter_h    [6:0]    S(7,0),19 */

    {0x1A,0x17, 0x1F}, /* thr_peak */
    {0x1A,0x18, 0x03}, /* delta_peak */


     /* aci ad judge */
    {0x17,0x42, 0x01}, /*  bypass notch aci detection */
    {0x17,0x43, 0x25}, /* ad_peak_power_thr */
    {0x1A,0x6D, 0x04},  /* notch_iir_a_aci */

    /*{0x1A,0x70, 0x01},*/ /* bypass lna gain thr change */
    {0x1A,0x72, 0x14}, /* thr_change_lna_gain2 20 */
    {0x1A,0x73, 0x01}, /* thr_change_gain_set */

    {0x1A,0x78, 0x08}, /* third_thr_lna_l */
    {0x1A,0x41, 0x01}, /* bypass sfi_1_detect */

    /*{0x1A,0x00, 0x00},*/ /* bypass sfi1 notch filter */
    /*{0x1A,0x01, 0x01},*/ /* bypass sfi2 notch filter */
    {0x1A,0x54, 0x00}, /* sfi_1_user_set */
    {0x1A,0x55, 0x00}, /* sfi_2_user_set */
    {0x1A,0x42, 0x28},  /* sfi_delta_thr */
    {0x1A,0x43, 0x0A},  /* sfi_peak_thr */

    {0x1A,0x02, 0xFF}, /* sfi_1_r */
    {0x1A,0x03, 0x07}, /* sfi_1_r */

    {0x1A,0x34, 0xC8}, /* sfi_1_freq */
    {0x1A,0x35, 0x10}, /*params_sfi_detect_freq_1[15:8]*/
    {0x1A,0x36, 0x00}, /*params_sfi_detect_freq_1[16]*/
};
#define ATBM2040_DSP_ATV_REG_CNT ATBM2040_ARRAY_NUM(DSPATVReg)

static ATBM2040RegGroup_t VGAGainThrDTMBReg[]=
{
    {   0x16,0xD9,
        {0x03,0x04,0x04},
        3},
    {   0x17,0x91,
        {0x71,0x6C},
        2},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t VGAGainThrDVBTReg[]=
{
    {   0x16,0xD9,
        {0x03,0x03,0x03},
        3},
    {   0x17,0x91,
        {0x71,0x6C},
        2},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t VGAGainThrDVBCReg[]=
{
    {   0x16,0xD9,
        {0x04,0x04,0x04},
        3},
    {   0x17,0x91,
        {0x74,0x6F},
        2},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t VGAGainThrATVReg[]=
{
    {   0x16,0xD9,
        {0x04,0x04,0x04},
        3},
    {   0x17,0x91,
        {0x71,0x6C},
        2},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t LeoEVGAGainThrATVReg[]=
{
    {   0x16,0xD9,
        {0x04,0x04,0x04},
        3},
    {   0x17,0x91,
        {0x76,0x6F},
        2},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t LeoGVGAGainThrATVReg[]=
{
    {   0x16,0xD9,
        {0x04,0x04,0x04},
        3},
    {   0x17,0x91,
        {0x74,0x70},
        2},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040Reg_t StandbyReg[]=
{
    {0x00,0x04, 0x02}, /* i2c_clk_sel */
    {0x00,0x0B, 0x01}, /* soft_rst_lo */
    {0x04,0x01, 0x01}, /* lna_ldo_pd */
    {0x08,0x00, 0x01}, /* rssi_pd */
    {0x09,0x00, 0x01}, /* if_fltr_pd */
    {0x09,0x0D, 0x01}, /* if_fltr_core_pd */
    {0x0B,0x00, 0x01}, /* adc_pd */
    {0x12,0x22, 0x01}, /* adc_div_ldo_pd */
    {0x0D,0x00, 0x01}, /* sar_adc_pd */
    {0x0F,0x09, 0x01}, /* pll_pd_ldo_cp */
    {0x0F,0x12, 0x01}, /* pll_pd_ldo_vco */
    {0x0F,0x15, 0x01}, /* pll_pd_ldo_mmd */
    {0x0F,0x16, 0x01}, /* pll_pd_ldo_dig */
    {0x10,0x00, 0x01}, /* dac_pd */
    {0x10,0x02, 0x01}, /* dac_fltr_pd */
    {0x12,0x0B, 0x01}, /* mixr_ldo_pd */
    {0x12,0x1F, 0x01}, /* mixr_div_ldo_pd */
    {0x12,0x3E, 0x01}, /* rf_ldo12_pd */

    {0x04,0x0B, 0x03},
    {0x04,0x07, 0x05},
    {0x04,0x08, 0x02},
    {0x04,0x05, 0x0B},
    {0x14,0x2B, (UINT8)-36},
    {0x14,0x2F, 0x00},
    {0x09,0x1A, 0x00},
    {0x14,0x2E, (UINT8)-4},

};
#define ATBM2040_STANDBY_REG_CNT ATBM2040_ARRAY_NUM(StandbyReg)

#if 0
static ATBM2040Reg_t WakeupReg[]=
{
    {0x04,0x01, 0x00}, /* lna_ldo_pd */
    {0x08,0x00, 0x00}, /* rssi_pd */
    {0x09,0x00, 0x00}, /* if_fltr_pd */
    {0x09,0x0D, 0x00}, /* if_fltr_core_pd */
    {0x12,0x22, 0x00}, /* adc_div_ldo_pd */
    {0x0B,0x00, 0x00}, /* adc_pd */
    {0x0B,0x25, 0x00}, /* adc_resetn */
    {0x0B,0x25, 0x01}, /* adc_resetn */
    {0x0D,0x00, 0x00}, /* sar_adc_pd */
    {0x0F,0x09, 0x00}, /* pll_pd_ldo_cp */
    {0x0F,0x12, 0x00}, /* pll_pd_ldo_vco */
    {0x0F,0x15, 0x00}, /* pll_pd_ldo_mmd */
    {0x0F,0x16, 0x00}, /* pll_pd_ldo_dig */
    {0x10,0x00, 0x00}, /* dac_pd */
    {0x10,0x02, 0x00}, /* dac_fltr_pd */
    {0x12,0x0B, 0x00}, /* mixr_ldo_pd */
    {0x12,0x1F, 0x00}, /* mixr_div_ldo_pd */
    {0x00,0x04, 0x03}, /* i2c_clk_sel */
    {0x00,0x0B, 0x00}, /* soft_rst_lo */
};
#define ATBM2040_WAKEUP_REG_CNT ATBM2040_ARRAY_NUM(WakeupReg)
#endif

static ATBM2040HalfAddrRegGroup_t ATBM2040DspStopReg=
{
    0x00,
    8,
    {
        0x0D, 0x00,/*0x00,0x0D, sw_cfg_done*/        
        0x04, 0x02,/*0x00,0x04, [0] I2c_clk_sel    [1] i2c_sys_clk_lck_enb*/        
        0x07, 0x01,/*0x00,0x07, soft_rst_dsp*/        
        0x0B, 0x01 /*0x00,0x0B, soft_rst_lo*/        
    }
};

static ATBM2040RegGroup_t RxFltBw8MRCReg1 =
{
    0x13,0x1A,
    {0x0F,0x79,0x00,0x26,0xBD,0x7B,0x00,0x08,0xF5,0x1B,0x00,0x00},/*from 131AH to 1325H*/
    12
};
static ATBM2040RegGroup_t RxFltBw8MRCReg2 =
{
    0x19,0xAC,
    {0x03,0x03,0x02,0x02},/*from 19ACH to 19AF*/
    4
};

static ATBM2040RegGroup_t LeoGRxFltBw8MRCReg2 =
{
    0x19,0xAC,
    {0x02,0x02,0x02,0x02},/*from 19ACH to 19AF*/
    4
};

static ATBM2040RegGroup_t RxFltBw7MRCReg1 =
{
    0x13,0x1A,
    {0x5B,0x6A,0x00,0x2C,0x7B,0x6C,0x00,0x0C,0x36,0xE8,0x9C,0xF5},/*from 131AH to 1325H*/
    12
};
static ATBM2040RegGroup_t RxFltBw7MRCReg2 =
{
    0x19,0xAC,
    {0x01,0x01,0x01,0x01},/*from 19ACH to 19AF*/
    4
};

static ATBM2040RegGroup_t RxFltBw6MRCReg1 =
{
    0x13,0x1A,
    {0x22,0x5C,0x00,0x38,0x39,0x5D,0x00,0x10,0x99,0x36,0x00,0x00},/*from 131AH to 1325H*/
    12
};
static ATBM2040RegGroup_t RxFltBw6MRCReg2 =
{
    0x19,0xAC,
    {0x00,0x00,0x00,0x00},/*from 19ACH to 19AF*/
    4
};

static ATBM2040RegGroup_t AlterThrRssiLnaOutTracking =
{
    0x1A,0x74,
    {0x05,0x05,0x05,0x05,0x05,0x05},/*from 1A74H to 1A79H*/
    6
};

static ATBM2040RegGroup_t DVBTAciN234Judge =
{
    0x23,0x29,/*from 2329H to 234FH*/
    {
        0xDC,0xD4,0xDE,0xD8,0xDE,0xD8,0x0A,0x0A,0x0F,0x78,0x73,0xDD,0xD8,0x14,0x0F,0x7B,
        0x76,0xDD,0xD8,0x14,0x0F,0x7A,0x75,0xDD,0xD8,0x15,0x10,0x18,0x10,0xDD,0xD8,0xEA,
        0xEA,0xF1,0xF1,0xEF,0x0A,0x0A,0x0F
    },
    39
};

static ATBM2040RegGroup_t ATSCAciN234JudgeThr =
{
    0x23,0x29,/*from 2329H to 234FH*/
    {
        0xF0,0xEC,0xF0,0xEC,0xF0,0xEC,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x20,0x20,0x76,
        0x70,0xE4,0xDD,0x14,0x0F,0x7D,0x78,0xE4,0xDD,0x17,0x12,0x1C,0x14,0xE7,0xE0,0xEA,
        0xEA,0xF1,0xF1,0xEF,0x00,0x00,0x00
    },
    39
};


static ATBM2040RegGroup_t OtherAciN234Judge =
{
    0x23,0x29,/*from 2329H to 234FH*/
    {
        0xE2,0xDC,0xE8,0xE2,0xE8,0xE2,0x0F,0x0F,0x0F,0x7A,0x74,0xE2,0xD3,0x14,0x0F,0x7B,
        0x76,0xE8,0xE2,0x1E,0x19,0x7A,0x74,0xE8,0xE2,0x1E,0x19,0x20,0x1A,0xEC,0xE6,0x64,
        0x6C,0x6C,0x6C,0x66,0x00,0x00,0x00
    },
    39
};

static ATBM2040RegGroup_t IIRCoefSA10M3rdSOSHmd = 
{
    0x22,0x49,
    {
        0xC4,0x0C,0x7F,0x01,0x89,0x03,0xFB,0x0C,0x1E,0x00,0xD5,0x04,0x1C,0x0E,0xB4,0x05,0x4C,0x00,0xDD,0x02,0x3D,0x0C,0x87,0x0E
    },
    24
};

static ATBM2040RegGroup_t IIRCoefSA10M3rdSOSLmd = 
{   
    0x22,0xA9,
    {
        0xC4,0x0C,0x7F,0x01,0x89,0x03,0xFB,0x0C,0x1E,0x00,0xD5,0x04,0x1C,0x0E,0xB4,0x05,0x4C,0x00,0xDD,0x02,0x3D,0x0C,0x87,0x0E
    },
    24

};

static ATBM2040RegGroup_t ATSCIIRCoefSA10M3rdSOSHmd = 
{
    0x22,0x49,
    {
        0x1E,0x0A,0x02,0x0A,0x5A,0x06,0x9C,0x0C,0x0D,0x0B,0x75,0x06,0x3E,0x0D,0x3A,0x01,0x46,0x00,0x5A,0x06,0x27,0x0C,0x2D,0x0A
    },
    24
};

static ATBM2040RegGroup_t ATSCIIRCoefSA10M3rdSOSLmd = 
{   
    0x22,0xA9,
    {
        0x1E,0x0A,0x02,0x0A,0x5A,0x06,0x9C,0x0C,0x0D,0x0B,0x75,0x06,0x3E,0x0D,0x3A,0x01,0x46,0x00,0x5A,0x06,0x27,0x0C,0x2D,0x0A
    },
    24

};

static ATBM2040RegGroup_t IIRCoefSA8M3rdSOSHmd = 
{   
    0x22,0x31,
    {
        0x99,0x07,0xCB,0x04,0x65,0x07,0x5A,0x0C,0x20,0x09,0x4D,0x07,0xA1,0x0C,0x25,0x0D,0x28,0x00,0x84,0x07,0x1A,0x0C,0xB9,0x08
    },
    24

};

static ATBM2040RegGroup_t IIRCoefSA8M3rdSOSLmd = 
{   
    0x22,0x91,
    {
        0x99,0x07,0xCB,0x04,0x65,0x07,0x5A,0x0C,0x20,0x09,0x4D,0x07,0xA1,0x0C,0x25,0x0D,0x28,0x00,0x84,0x07,0x1A,0x0C,0xB9,0x08
    },
    24

};

static ATBM2040RegGroup_t AciN234CalResultUHF[]=
{
    {   0x14,0x96,
        {0xFA,0x19},
        2},
    {   0x19,0xA4,
        {0xF6},
        1},
    {   0x19,0xB0,
        {0xF7},
        1},    
    {   0x22,0xFB,
        {0x00,0x00,0xEC,0xDF,0xCE},
        5},
    {   0x23,0x0F, 
        {0x00,0xFE,0xF2,0xE6,0x00},
        5},
    {   0x23,0x19,
        {0x2A,0x00,0x1B,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,0x5C,0x00,0xAE,0x00,0xB2,0x00},
        16},
    {   0x23,0xC0,
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        10},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t AciN234CalResultVHF2[]=
{
    {   0x14,0x96,
        {0xFA,0x17},
        2},
    {   0x19,0xA4,
        {0xF8},
        1},
    {   0x19,0xB0,
        {0xFB},
        1},    
    {   0x22,0xFB,
        {0x00,0x00,0xE8,0xDD,0xD1},
        5},
    {   0x23,0x0F, 
        {0x00,0xFA,0xEA,0xDF,0x00},
        5},
    {   0x23,0x19,
        {0x1C,0x00,0x0E,0x00,0x3D,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x58,0x00,0x75,0x00},
        16},
    {   0x23,0xC0,
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        10},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t AciN234CalResultVHF1[]=
{
    {   0x14,0x96,
        {0xF9,0x18},
        2},
    {   0x19,0xA4,
        {0xF3},
        1},
    {   0x19,0xB0,
        {0x04},
        1},    
    {   0x22,0xFB,
        {0x00,0x00,0xE4,0xD8,0xC9},
        5},
    {   0x23,0x0F, 
        {0x00,0xF6,0xE7,0xDC,0x00},
        5},
    {   0x23,0x19,
        {0x0A,0x00,0x1E,0x00,0x5E,0x00,0x00,0x00,0x00,0x00,0x2B,0x00,0x6A,0x00,0x60,0x00},
        16},
    {   0x23,0xC0,
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        10},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t AciN234CalResultATV[]=
{
    {   0x14,0x96,
        {0x04,0x15},
        2},
    {   0x19,0xA4,
        {0x7F},
        1},
    {   0x19,0xB0,
        {0xB0},
        1},    
    {   0x22,0xFB,
        {0xFF,0xF6,0xD7,0xC3,0xB4},
        5},
    {   0x23,0x0F, 
        {0xFF,0xFB,0xDE,0xC7,0xB7},
        5},
    {   0x23,0x19,
        {0x07,0x00,0x07,0x00,0x14,0x00,0x74,0x00,0x09,0x00,0x20,0x00,0xA0,0x00,0xA4,0x01},
        16},
    {   0x23,0xC0,
        {0x1E,0x00,0x00,0x00,0x00,0x00,0x1E,0x1C,0x1A,0x18},
        10},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t AciN234CalResultATSC[]=
{
    {   0x14,0x96,
        {0x76,0x15},
        2},
    {   0x19,0xA4,
        {0x76},
        1},
    {   0x19,0xB0,
        {0xE8},
        1},    
    {   0x22,0xFB,
        {0x00,0x00,0xDE,0xC0,0xC7},
        5},
    {   0x23,0x0F, 
        {0x00,0xE0,0xD9,0xDE,0x00},
        5},
    {   0x23,0x19,
        {0x14,0x00,0x87,0x00,0x87,0x00,0x00,0x00,0x00,0x00,0x9C,0x00,0xA7,0x00,0xA7,0x00},
        16},
    {   0x23,0xC0,
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        10},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040RegGroup_t AciN234CalResult[]=
{
    {   0x14,0x96,
        {0x04,0x15},
        2},
    {   0x19,0xA4,
        {0x7F},
        1},
    {   0x19,0xB0,
        {0x2C},
        1},    
    {   0x22,0xFB,
        {0xFF,0xF6,0xD7,0xC3,0xB4},
        5},
    {   0x23,0x0F, 
        {0xFF,0xFB,0xDE,0xC7,0xB7},
        5},
    {   0x23,0x19,
        {0x07,0x00,0x07,0x00,0x14,0x00,0x74,0x00,0x09,0x00,0x20,0x00,0xA0,0x00,0xA4,0x01},
        16},
    {   0x23,0xC0,
        {0x1E,0x00,0x00,0x00,0x00,0x00,0x1E,0x1C,0x1A,0x18},
        10},
    
    {   0x00,0x00,{0x00},0}/* End */
};

static ATBM2040Reg_t FEFInternalReg[]=
{
    {0x16,0x00, 0x01}, /* params_add_fef_detect       [0]      Read write       1'b1 */
    {0x16,0x39, 0x0F}, /* params_thr_fef_judge[5:0]           [5:0] Read write       6'b00_1010 */
    {0x16,0x3A, 0x0F}, /* params_thr_fef_judge_aci[5:0] [5:0] Read write       6'b00_1010 */
};
#define ATBM2040_FEF_INTERNAL_REG_CNT ATBM2040_ARRAY_NUM(FEFInternalReg)

#if ATBM2040_FIRMWARE_LOAD
static ATBM2040Firmware_t ATBM2040Firmware =
{
    0x21,0x00,
    {
        0xA7,0x4A,0xC0,0x68,0x00,0xA7,0x4A,0xC0,0x70,0x05,0x5F,0xFF,0x44,0x01,0x08,0xD0,0x02,0x58,0x11,0x70,0x0A,0xAB,0x4C,0x26,0x44,0x14,0x15,0x70,0x00,0x17,0x87,0x42,
        0x70,0x5F,0xFF,0xA3,0x4A,0xA1,0x44,0x02,0x11,0x70,0x21,0x0E,0x2C,0xA2,0x02,0x21,0x44,0x01,0x0A,0x82,0x02,0x20,0x5F,0xFF,0x5F,0xFF,0x0A,0x82,0x02,0x20,0x5F,0xFF,
        0x5F,0xFF,0x5F,0xFF,0xA7,0x4B,0x60,0x70,0x42,0x0E,0x5F,0xFF,0x5F,0xFF,0x44,0x01,0x08,0xD0,0x02,0x58,0x11,0x70,0x4A,0x28,0x44,0x01,0x08,0x15,0x68,0x68,0x44,0x02,
        0x15,0x68,0x72,0x44,0x03,0x15,0x68,0x7C,0x2C,0xBB,0x4D,0x0B,0x93,0x69,0x70,0x28,0x60,0x2C,0x2C,0xBB,0x4D,0x0B,0x93,0x69,0x90,0x28,0x60,0x2C,0xBB,0x4D,0x0B,0x93,
        0x69,0xB0,0xBD,0x69,0x9B,0x10,0x39,0x2C,0x29,0xBB,0x69,0x7B,0x10,0x39,0x2C,0x29,0x2D,0x28,0x44,0xA0,0x09,0x2C,0x29,0x2D,0xA2,0x02,0x21,0x44,0x01,0x0A,0x82,0x02,
        0x20,0x5F,0xFF,0x5F,0xFF,0x0A,0x82,0x02,0x20,0x5F,0xFF,0xA7,0x4B,0x60,0x70,0xA9,0x0E,0x5F,0xFF,0x5F,0xFF,0x44,0x01,0x08,0xD0,0x4E,0x20,0x11,0x70,0xB1,0xBB,0x4D,
        0x0B,0x29,0x11,0x3B,0x1E,0x8B,0x42,0x70,0x68,0x00,0x60,0x98
    },/**/
    204
};

#if ATBM2040_CUSTOMER1_CONFIG
static ATBM2040Firmware_t ATBM2040GFirmware =
{
    0x21,0x00,
    {
        0x1F,0x42,0xFF,0x83,0x21,0x80,0xA3,0x4A,0xA1,0x5F,0xFF,0x44,0x02,0x11,0x70,0x06,0xA7,0x21,0x30,0x70,0xB6,0xA3,0x4D,0xF2,0x44,0x01,0x15,0x68,0x7B,0x44,0x70,0x60,
        0xAE,0xA3,0x21,0xA7,0x44,0x40,0x0C,0x15,0x70,0x79,0xA3,0x4D,0xF2,0x16,0x22,0x70,0x3B,0x83,0x21,0x90,0x44,0x00,0x15,0x68,0x4B,0x70,0x69,0xA5,0x21,0x92,0x83,0x21,
        0x90,0x14,0x70,0x79,0x44,0x00,0x15,0x68,0x4B,0x70,0x69,0x16,0x86,0x91,0xC0,0x86,0x90,0x50,0x17,0x87,0x22,0xD0,0xA2,0x90,0xF5,0x44,0x04,0x09,0x82,0x91,0xC0,0x17,
        0x86,0x90,0x50,0x16,0x87,0x22,0xD0,0x60,0x78,0x16,0x86,0x91,0xC0,0x86,0x90,0x50,0x17,0x87,0x22,0xD0,0x16,0x87,0x22,0xD0,0x1E,0x60,0x06,0xA3,0x4C,0x93,0xA5,0x21,
        0x87,0x83,0x21,0x80,0x09,0x44,0x02,0x10,0x68,0x91,0x45,0xFE,0x12,0x68,0x91,0x60,0x21,0xA3,0x21,0x83,0x44,0x0C,0x11,0x3B,0x44,0x46,0x60,0xAE,0x44,0x0A,0x11,0x3B,
        0x44,0x70,0x60,0xAE,0x44,0x08,0x11,0x3B,0x44,0x9A,0x60,0xAE,0x44,0xA0,0x85,0x3A,0x60,0x85,0x54,0x00,0x60,0x21,0x0E,0x82,0x00,0xD0,0x42,0x02,0x82,0x00,0x40,0x0E,
        0x82,0xF2,0x10,0x82,0xF1,0xF0,0x50,0x0F,0x0F,0x82,0xF2,0x10,0x82,0xF1,0xF0,0x5F,0xFF,0x5F,0xFF,0x82,0x00,0x70,0x82,0x00,0xB0,0x42,0x07,0x82,0x00,0xD0,0x42,0x03,
        0x82,0x00,0x40,0x0E,0x82,0x00,0x70,0x82,0x00,0xB0,0x60,0x06
    },/**/
    236
};
#else
static ATBM2040Firmware_t ATBM2040GFirmware =
{
    0x21,0x00,
    {
        0x1F,0xA3,0x4A,0xA1,0x5F,0xFF,0x44,0x02,0x11,0x70,0x01,0xA7,0x21,0x30,0x70,0x6A,0xA3,0x21,0xA7,0x44,0x40,0x0C,0x15,0x70,0x68,0xA3,0x4D,0xF2,0x16,0x22,0x70,0x2A,
        0x83,0x21,0x90,0x44,0x00,0x15,0x68,0x3A,0x70,0x58,0xA5,0x21,0x92,0x83,0x21,0x90,0x14,0x70,0x68,0x44,0x00,0x15,0x68,0x3A,0x70,0x58,0x16,0x86,0x91,0xC0,0x86,0x90,
        0x50,0x17,0x87,0x22,0xD0,0xA2,0x90,0xF5,0x44,0x04,0x09,0x82,0x91,0xC0,0x17,0x86,0x90,0x50,0x16,0x87,0x22,0xD0,0x60,0x67,0x16,0x86,0x91,0xC0,0x86,0x90,0x50,0x17,
        0x87,0x22,0xD0,0x16,0x87,0x22,0xD0,0x1E,0x60,0x01,0x0E,0x82,0x00,0xD0,0x42,0x02,0x82,0x00,0x40,0x0E,0x82,0xF2,0x10,0x82,0xF1,0xF0,0x50,0x0F,0x0F,0x82,0xF2,0x10,
        0x82,0xF1,0xF0,0x5F,0xFF,0x5F,0xFF,0x82,0x00,0x70,0x82,0x00,0xB0,0x42,0x07,0x82,0x00,0xD0,0x42,0x03,0x82,0x00,0x40,0x0E,0x82,0x00,0x70,0x82,0x00,0xB0,0x60,0x01
    },/**/
    160
};
#endif
#endif
#define ATBM2040_BURST_BUFF_MAX (45)
static UINT8 ATBM2040BurstBuff[ATBM2040_BURST_BUFF_MAX+2] = {0};

#define ATBM2040_HALF_ADDR_BURST_BUFF_MAX (46)
static UINT8 ATBM2040BurstBuff2[ATBM2040_HALF_ADDR_BURST_BUFF_MAX+3] = {0};


/**********************2 32bit data multipe,then use the next fuction *****************/
static void ATBM64Mult(ATBM2040Data64_t *pstRst,UINT32 m1, UINT32 m2)
{
    UINT32 ui32LowPart,ui32Tmp;
    pstRst->Low = (m1&0xFFFF) * (m2&0xFFFF);
    pstRst->High = (m1>>16) * (m2>>16);

    ui32LowPart = pstRst->Low;
    ui32Tmp = (m1>>16) * (m2&0xFFFF);
    pstRst->Low  += (ui32Tmp<<16);
    pstRst->High += (ui32Tmp>>16);
    if(ui32LowPart > pstRst->Low)
    {
        pstRst->High++;
    }

    ui32LowPart = pstRst->Low;
    ui32Tmp = (m2>>16) * (m1&0xFFFF);
    pstRst->Low  += (ui32Tmp<<16);
    pstRst->High += (ui32Tmp>>16);
    if(ui32LowPart > pstRst->Low)
    {
        pstRst->High++;
    }
}

static UINT8  ATBM64ComPare(ATBM2040Data64_t stPara,ATBM2040Data64_t stPara1)
{
    UINT8 ui8Flag = 0;/* default :stPara<=stPara1 */
    if (stPara.Low>=stPara1.Low)
    {
        if (stPara.High >= stPara1.High)
        {
            ui8Flag = 1;
        }
    }
    else
    {
        if (stPara.High > stPara1.High)
        {
            ui8Flag = 1;
        }
    }
    return ui8Flag;

}
static UINT32 ATBM64Div(ATBM2040Data64_t stDivisor,ATBM2040Data64_t stDividend)
{
    UINT32  ui32DivLeftShit = 0;
    UINT32 ui32Rst = 0;
    UINT32 ui32flag = 1;
    ATBM2040Data64_t stDataTmp = stDividend;
    if (stDivisor.High == 0&&stDivisor.Low == 0)
    {
        return 0;
    }
    else if (stDividend.High == 0&&stDividend.Low == 0)
    {
        return 0;
    }
    else if (stDividend.High > stDivisor.High)
    {
        return 0;
    }
    else if (!ATBM64ComPare(stDivisor,stDividend))
    {
        return 0;
    }
    else if (stDividend.High == 0 && stDivisor.High == 0)
    {
        return stDivisor.Low/stDividend.Low;
    }
    else/*  normal condition  stDivisor >= stDividend */
    {
        while(ui32flag)
        {
            ++ui32DivLeftShit;
            stDataTmp.High<<=1;
            if(stDataTmp.Low&0x80000000)
            {
                stDataTmp.High +=1;
            }
            stDataTmp.Low<<=1;

            if (!ATBM64ComPare(stDivisor,stDataTmp)||stDataTmp.High>=0x80000000)
            {
                if (stDataTmp.High<0x80000000)
                {
                    stDataTmp.Low>>=1;
                    if (stDataTmp.High&1)
                    {
                        stDataTmp.Low |= 0x80000000;
                    }
                    stDataTmp.High>>=1;
                    ui32DivLeftShit--;
                }


                stDivisor.High -= stDataTmp.High;
                if(stDivisor.Low >= stDataTmp.Low)
                {
                    stDivisor.Low -= stDataTmp.Low;
                }
                else
                {
                    stDivisor.Low +=0xFFFFFFFF - stDataTmp.Low;
                    stDivisor.Low += 1;
                    stDivisor.High -= 1;
                }
                ui32Rst = (((UINT32)1)<<ui32DivLeftShit);
                break;
            }
        }
        ui32Rst += ATBM64Div(stDivisor,stDividend);
    }
    return ui32Rst;
}

ATBM2040_ERROR_e ATBM2040RegWrite(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 Value)
{
    return ATBM2040I2CWrite(pI2CAddr,BaseReg,OffReg, &Value,1);
}

ATBM2040_ERROR_e ATBM2040RegRead(ATBM2040I2CAddr_t *pI2CAddr,UINT8 BaseReg,UINT8 OffReg,UINT8 *pValue)
{
    return ATBM2040I2CRead(pI2CAddr,BaseReg,OffReg, pValue,1);
}


/************************************************************
*Description: Latch on or off for some read only registers. After latch on, registers will not
*            refresh until latch off
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvRegLatch(ATBM2040I2CAddr_t *pI2CAddr,BOOL OnOff)
{
    return ATBM2040RegWrite(pI2CAddr,0x01,0x0D, (OnOff)?(0x01):(0x00)); /*ro_latch*/
}

/************************************************************
*Description: Find mixer divider according to center frequency
*************************************************************/
void ATBM2040DrvNLOMixer(ATBM2040_t *pTuner)
{
    UINT32 i = 0,MixDivCnt = 0;
    ATBM2040NLOMixer_t *pNLOMixer = NULL;
#define MIXER_DIVIDER_SEARCH()     for(i=0;i<MixDivCnt;i++)\
    {\
        if((pNLOMixer[i].FreqStart <= pTuner->FreqKHz)&&(pTuner->FreqKHz <= pNLOMixer[i].FreqEnd))\
        {\
            break;\
        }\
    }\
    if(i >= MixDivCnt)\
    {\
        i = MixDivCnt-1;\
    }

    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID))
    {
        pNLOMixer = NLOMixerLeoEHMD;
        MixDivCnt = ATBM2040_NLO_MIXER_LEOE_HMD_CNT;
        MIXER_DIVIDER_SEARCH();
        pTuner->pNLOMixerHMD = (pNLOMixer + i);

        pNLOMixer = NLOMixerLeoELMD;
        MixDivCnt = ATBM2040_NLO_MIXER_LEOE_LMD_CNT;
        MIXER_DIVIDER_SEARCH();
        pTuner->pNLOMixerLMD = (pNLOMixer + i);

        if(pTuner->HighMD)
        {
            pTuner->pNLOMixer = pTuner->pNLOMixerHMD;
        }
        else
        {
            pTuner->pNLOMixer = pTuner->pNLOMixerLMD;
        }
    }
    else
    {
        pNLOMixer = NLOMixer;
        MixDivCnt = ATBM2040_NLO_MIXER_CNT;
        MIXER_DIVIDER_SEARCH();
        pTuner->pNLOMixer = pTuner->pNLOMixerHMD = pTuner->pNLOMixerLMD = (pNLOMixer + i);
    }

}

/************************************************************
*Description: Calculate PLLDiv according to center frequency and LO selection
*************************************************************/
void ATBM2040DrvPLLDivCal(ATBM2040_t *pTuner,UINT8 *pNInt,UINT32 *pNFrac,BOOL HighMD)
{
    ATBM2040NLOMixer_t *pNLOMixer = NULL;
    UINT32 IFKHz = pTuner->MixerIF/1000;
    UINT32 Fref = 24000; /*24 MHz*/
    ATBM2040Data64_t i64DataF, i64DataF1;
    UINT32  Product = 0,Remainder = 0;
    UINT32 CenterFreqKHz = pTuner->FreqKHz; /* Frequency calculation should be less KHz */

    Fref = pTuner->Config.OSCFreqKHz;
    if(0 == pTuner->PllDivMode)
    {
        Fref *= 2;
    }

    if(HighMD)
    {
        pNLOMixer = pTuner->pNLOMixerHMD;
        Product = (CenterFreqKHz + IFKHz) * pNLOMixer->NLO * pNLOMixer->NMixer ;/*  NLO *  NMixer < 256 */
    }
    else
    {
        pNLOMixer = pTuner->pNLOMixerLMD;
        Product = (CenterFreqKHz - IFKHz) * pNLOMixer->NLO * pNLOMixer->NMixer ;/*  NLO *  NMixer < 256 */
    }

    *pNInt = (UINT8)(Product / Fref);

    Remainder = Product % Fref;
    ATBM64Mult(&i64DataF,Remainder, 0x1000000/*FixPow(2, 24)*/);/* KHz */
    i64DataF1.High = 0;
    i64DataF1.Low = Fref;
    *pNFrac = ATBM64Div(i64DataF,i64DataF1);
}

/************************************************************
*Description: Find ADC divider according to center frequency and LO selection
*************************************************************/
ATBM2040ADCDivider_t *ATBM2040DrvADCDivider(ATBM2040_t *pTuner,BOOL HMD)
{
    UINT32 i = 0;
    UINT32 loopNum = 0;
    ATBM2040ADCDivider_t *pDivider = NULL;
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        pDivider = LeoEADCDividerHMD;
        if(HMD)
        {
            pDivider = LeoEADCDividerHMD;
            loopNum = ATBM2040_LEOE_ADC_DIVIDER_HMD_CNT;
        }
        else
        {
            pDivider = LeoEADCDividerLMD;
            loopNum = ATBM2040_LEOE_ADC_DIVIDER_LMD_CNT;
        }
    }
    else
    {
        pDivider = ADCDividerHMD;
        if(HMD)
        {
            pDivider = ADCDividerHMD;
            loopNum = ATBM2040_ADC_DIVIDER_HMD_CNT;
        }
        else
        {
            pDivider = ADCDividerLMD;
            loopNum = ATBM2040_ADC_DIVIDER_LMD_CNT;
        }
    }
    for(i=0;i<loopNum;i++)
    {
        if((pDivider[i].FreqStart < pTuner->FreqKHz)&&(pTuner->FreqKHz <= pDivider[i].FreqEnd))
        {
            return (pDivider+i);
        }
    }

    pDivider = pDivider + (loopNum-1);

    return pDivider;
}

/************************************************************
*Description: Find UHF channel index according to center frequency
*************************************************************/
static ATBM2040UHFChIndex_t *ATBM2040DrvUHFFreqIndex(UINT32 FreqKHz)
{
    UINT32 i = 0;
    UINT32 center = 0;
    ATBM2040UHFChIndex_t *pIndex = NULL;
    UINT32 FreqMHz = FreqKHz/1000;

    pIndex = UHFFreqIndex;
    if(FreqMHz >= pIndex->FreqMHz)
    {
        return pIndex;
    }
    pIndex = &UHFFreqIndex[ATBM2040_UHF_FREQ_INDEX_CNT-1];
    if(FreqMHz <= pIndex->FreqMHz)
    {
        return pIndex;
    }
    pIndex = UHFFreqIndex;
    for(i=0;i<ATBM2040_UHF_FREQ_INDEX_CNT-1;i++)
    {
         if((FreqMHz <= pIndex->FreqMHz)&&(FreqMHz > (pIndex+1)->FreqMHz))
         {
             break;
         }
        pIndex++;
    }
    center = (pIndex->FreqMHz + (pIndex+1)->FreqMHz)/2;
    if(FreqMHz < center)
    {/*near to next index*/
        pIndex++;
    }
    return pIndex;
}

static void ATBM2040DrvVHF2CalResult(UINT32 FreqKHz,
        ATBM2040VHF2CalResult_t **pHighRes,ATBM2040VHF2CalResult_t **pLowRes)
{
    UINT32 i = 0;
    ATBM2040VHF2CalResult_t *pIndex = NULL;
    UINT32 FreqMHz = FreqKHz/1000;

    pIndex = ATBM2040VHF2CalRes;
    if(FreqMHz <= pIndex->FreqMHz)
    {
        *pHighRes = pIndex + 1;
        *pLowRes = pIndex;
        return;
    }
    pIndex = &ATBM2040VHF2CalRes[ATBM2040_VHF2_CAL_RES_CNT-1];
    if(FreqMHz >= pIndex->FreqMHz)
    {
        *pHighRes = pIndex;
        *pLowRes = pIndex - 1;
        return;
    }
    pIndex = ATBM2040VHF2CalRes;
    for(i=0;i<ATBM2040_VHF2_CAL_RES_CNT - 1;i++)
    {
        if((FreqMHz >= pIndex->FreqMHz)&&(FreqMHz < (pIndex+1)->FreqMHz))
        {
            *pHighRes = pIndex + 1;
            *pLowRes = pIndex;
            return;
        }
        pIndex++;
    }
    pIndex = ATBM2040VHF2CalRes;
    *pHighRes = pIndex + 1;
    *pLowRes = pIndex;
}

static void ATBM2040DrvUHFCalResult(UINT32 FreqKHz,
    ATBM2040UHFCalResult_t **pHighRes,ATBM2040UHFCalResult_t **pLowRes)
{
    UINT32 i = 0;
    ATBM2040UHFCalResult_t *pIndex = NULL;
    UINT32 FreqMHz = FreqKHz/1000;

    pIndex = ATBM2040UHFCalRes;
    if(FreqMHz >= pIndex->FreqMHz)
    {
        *pHighRes = pIndex;
        *pLowRes = pIndex + 1;
        return;
    }
    pIndex = &ATBM2040UHFCalRes[ATBM2040_UHF_CAL_RES_CNT-1];
    if(FreqMHz <= pIndex->FreqMHz)
    {
        *pHighRes = pIndex - 1;
        *pLowRes = pIndex;
        return;
    }
    pIndex = ATBM2040UHFCalRes;
    for(i=0;i<ATBM2040_UHF_CAL_RES_CNT-1;i++)
    {
        if((FreqMHz <= pIndex->FreqMHz)&&(FreqMHz > (pIndex+1)->FreqMHz))
        {
            *pHighRes = pIndex;
            *pLowRes = pIndex + 1;
            return;
        }
        pIndex++;
    }
    pIndex = &ATBM2040UHFCalRes[ATBM2040_UHF_CAL_RES_CNT-1];
    *pHighRes = pIndex - 1;
    *pLowRes = pIndex;
}


/************************************************************
*Description: Find VHF2 channel index according to center frequency
*************************************************************/
static ATBM2040VHF2ChIndex_t *ATBM2040DrvVHF2FreqIndex(UINT32 FreqKHz)
{
    UINT32 i = 0;
    UINT32 center = 0;
    ATBM2040VHF2ChIndex_t *pIndex = NULL;
    UINT32 FreqMHz = FreqKHz/1000;

    pIndex = VHF2FreqIndex;
    if(FreqMHz <= pIndex->FreqMHz)
    {
        return pIndex;
    }
    pIndex = &VHF2FreqIndex[ATBM2040_VHF2_FREQ_INDEX_CNT-1];
    if(FreqMHz >= pIndex->FreqMHz)
    {
        return pIndex;
    }
    pIndex = VHF2FreqIndex;
    for(i=0;i<ATBM2040_VHF2_FREQ_INDEX_CNT-1;i++)
    {
        if((FreqMHz >= pIndex->FreqMHz)&&(FreqMHz < (pIndex+1)->FreqMHz))
        {
            break;
        }
        pIndex++;
    }
    center = (pIndex->FreqMHz + (pIndex+1)->FreqMHz)/2;
    if(FreqMHz < center)
    {/*near to next index*/
        pIndex++;
    }
    return pIndex;
}

/************************************************************
*Description: Find VHF channel index according to center frequency
*************************************************************/
static ATBM2040VHFChIndex_t *ATBM2040DrvVHFFreqIndex(UINT32 FreqKHz)
{
    UINT32 i = 0;
    UINT32 center = 0;
    ATBM2040VHFChIndex_t *pIndex = NULL;

    pIndex = VHFChannelIndex;
    if(FreqKHz <= pIndex->FreqKHz)
    {
        return pIndex;
    }
    pIndex = &VHFChannelIndex[ATBM2040_VHF_CH_INDEX_CNT-1];
    if(FreqKHz >= pIndex->FreqKHz)
    {
        return pIndex;
    }
    pIndex = VHFChannelIndex;
    for(i=0;i<ATBM2040_VHF_CH_INDEX_CNT-1;i++)
    {
        if((FreqKHz >= pIndex->FreqKHz)&&(FreqKHz < (pIndex+1)->FreqKHz))
        {
            break;
        }
        pIndex++;
    }
    center = (pIndex->FreqKHz + (pIndex+1)->FreqKHz)/2;
    if(FreqKHz > center)
    {/*near to next index*/
        pIndex++;
    }
    return pIndex;
}

/************************************************************
*Description: Find VHF1 channel index according to center frequency
*************************************************************/
static ATBM2040VHF1ChIndex_t *ATBM2040DrvVHF1FreqIndex(UINT32 FreqKHz)
{
    UINT32 i = 0;
    UINT32 center = 0;
    ATBM2040VHF1ChIndex_t *pIndex = NULL;

    pIndex = VHF1ChannelIndex;
    if(FreqKHz <= pIndex->FreqKHz)
    {
        return pIndex;
    }
    pIndex = &VHF1ChannelIndex[ATBM2040_VHF1_CH_INDEX_CNT-1];
    if(FreqKHz >= pIndex->FreqKHz)
    {
        return pIndex;
    }
    pIndex = VHF1ChannelIndex;
    for(i=0;i<ATBM2040_VHF1_CH_INDEX_CNT-1;i++)
    {
        if((FreqKHz >= pIndex->FreqKHz)&&(FreqKHz < (pIndex+1)->FreqKHz))
        {
            break;
        }
        pIndex++;
    }
    center = (pIndex->FreqKHz + (pIndex+1)->FreqKHz)/2;
    if(FreqKHz > center)
    {/*near to next index*/
        pIndex++;
    }
    return pIndex;
}


/************************************************************
*Description: PLL and Mixer divider setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvPLLMixDivSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 PLLDivInt = 0,PLLDivInt2 = 0;
    UINT32 PLLDivFrac = 0,PLLDivFrac2 = 0;
    UINT8 reg121c = 0,reg121e = 0;
    UINT8 reg1215 = 0,reg1240 = 0;
    UINT8 val = 0;
    UINT8 mixr_pll_mixr_div_mode_l = 0,mixr_pll_mixr_div_mode_h = 0;
    UINT8 Data[10] = {0};
    UINT8 PllDivComp = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    /*PLL divider calculate*/
    ATBM2040DrvPLLDivCal(pTuner,&PLLDivInt,&PLLDivFrac,pTuner->HighMD);
    ATBM2040DrvPLLDivCal(pTuner,&PLLDivInt2,&PLLDivFrac2,!pTuner->HighMD);

    if(PLLDivInt >160)
    {
        Data[0] = 0x00; /*0x0F,0x2C,  pll freq rang adjust */
        Data[1] = 0x07; /*0x0F,0x2D,  pll freq rang adjust */
    }
    else
    {
        Data[0] = 0x01; /*0x0F,0x2C,  pll freq rang adjust */
        Data[1] = 0x06; /*0x0F,0x2D,  pll freq rang adjust */
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x0F,0x2C, Data,2);
    
    if(PLLDivInt > 160)
    {
        PllDivComp = 0x07;            
    }
    else if(PLLDivInt >107)
    {
        PllDivComp = 0x06;            
    }
    else if(PLLDivInt > 87)
    {
        PllDivComp = 0x05;            
    }
    else if(PLLDivInt > 82)
    {
        PllDivComp = 0x04;            
    }
    else if(PLLDivInt > 80)
    {
        PllDivComp = 0x02;            
    }
    else if(PLLDivInt > 79)
    {
        PllDivComp = 0x01;        
    }
    else
    {
        PllDivComp = 0x00;        
    }
    PllDivComp |= 0x10;
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)||(ATBM_LEOC_CHIP_ID == pTuner->ChipID))
    {
        Data[0] = (PllDivComp>>4)&0x01; /*0x0F,0x39, pll_sivco*/
        Data[1] = PllDivComp&0x07; /*0x0F,0x3A, pll_divco[2:0]*/
        Data[2] = 0x02; /*0x0F,0x3B, pll_vref_ctrl[1:0]*/
        Data[3] = 0x00; /*0x0F,0x3C, pll_rc_byp*/
        Data[4] = (PllDivComp>>3)&0x01; /*0x0F,0x3D, pll_pd_vco_opa1*/
        Data[5] = (PllDivComp>>7)&0x01; /*0x0F,0x3E, pll_pd_vco_r_byp*/
        Data[6] = 0x00; /*0x0F,0x3F, pll_path_mode*/
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x0F,0x39, Data,7);
    }
    else if(ATBM_LEOB_CHIP_ID == pTuner->ChipID)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x14, PllDivComp); /*rsv0, PLL Divider compensation*/
    }

    ret |= ATBM2040RegRead(pI2CAddr,0x12,0x15, &reg1215);
    reg1215 &= 0x9F; /*clear <6:5>*/
    reg1215 |= 0x40;
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x15, reg1215); /*rsv1<6:5> , ldo voltage for vco*/

    
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x15, 0x01); /*pll_pd_ldo_mmd, power down*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x00, 0x01); /* [0]    1    ADC_PD */
    /*ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x0D, 0x01);*/ /* [0]    1    IF_CORE_PD */
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x0B, 0x01); /* [0]    1    MIXR_ANALOG_PD */

    ATBM2040Delay(3000);
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x1D, 0x00); /* [0]    0    pll_rst_sdm */
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x21, 0x00); /* [0]    0    pll_rst_afc_dft */
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x1F, 0x00); /* [0]    0    pll_en_afc_dft */

    /*PLL divider set*/
    Data[0] = PLLDivInt; /*0x0F,0x17, pll_n_int_dft[7:0] */
    Data[1] = (UINT8)(PLLDivFrac&0xFF); /*0x0F,0x18, pll_n_frac_dft[7:0] */
    Data[2] = (UINT8)((PLLDivFrac>>8)&0xFF); /*0x0F,0x19, pll_n_frac_dft[15:8] */
    Data[3] = (UINT8)((PLLDivFrac>>16)&0xFF); /*0x0F,0x1A, pll_n_frac_dft[23:16] */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x0F,0x17, Data,4);

    if(!pTuner->HighMD)
    {/*make sure that PLLDivInt and PLLDivFrac are HMD divider, so swap PLLDivInt and PLLDivInt2 in case of LMD*/
        UINT8 tmpPLLDivInt = 0;
        UINT32 tmpPLLDivFrac = 0;
        tmpPLLDivInt = PLLDivInt;
        PLLDivInt = PLLDivInt2;
        PLLDivInt2 = tmpPLLDivInt;

        tmpPLLDivFrac = PLLDivFrac;
        PLLDivFrac = PLLDivFrac2;
        PLLDivFrac2 = tmpPLLDivFrac;

    }
    /*HMD*/
    Data[0] = (UINT8)(PLLDivFrac&0xFF); /*0x14,0x9E,  ndiv_n[7:0] */
    Data[1] = (UINT8)((PLLDivFrac>>8)&0xFF); /*0x14,0x9F, ndiv_n[15:8] */
    Data[2] = (UINT8)((PLLDivFrac>>16)&0xFF); /*0x14,0xA0, ndiv_n[23:16] */
    Data[3] = PLLDivInt; /*0x14,0xA1, ndiv_n[31:24] */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x9E, Data,4);

    /*LMD*/
    Data[0] = (UINT8)(PLLDivFrac2&0xFF); /*0x14,0x9A,  ndiv_p[7:0] */
    Data[1] = (UINT8)((PLLDivFrac2>>8)&0xFF); /*0x14,0x9B, ndiv_p[15:8] */
    Data[2] = (UINT8)((PLLDivFrac2>>16)&0xFF); /*0x14,0x9C, ndiv_p[23:16] */
    Data[3] = PLLDivInt2; /*0x14,0x9D, ndiv_p[31:24] */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x9A, Data,4);


    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x1D, 0x01); /* pll_rst_sdm */
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x21, 0x01); /* pll_rst_afc_dft */
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x1F, 0x01); /* pll_en_afc_dft */
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x15, 0x00); /*pll_pd_ldo_mmd, power on*/

    ret |= ATBM2040RegRead(pI2CAddr,0x0F,0x26, &val);
    if(0x00 == val)
    {
        ATBM2040Delay(1000);
    }
    ATBM2040Delay(1000);
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x00, 0x00); /* [0]    1    ADC_ON */
    /*ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x0D, 0x00);*/ /* [0]    1    IF_CORE_ON */
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x0B, 0x00); /* [0]    1    MIXR_ANALOG_ON */
    /*Mixer divider */
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ATBM2040NLOMixer_t *pNLOMixer = NULL;
        UINT8 MixDivTableLeoF[11][3] = {
            /*121CH  1240H  121EH*/
            {0x00,    0x01,  0x01},  /*dummy*/
            {0x00,    0x01,  0x01},  /*NLO: 1*/
            {0x00,    0x01,  0x00},  /*NLO: 2*/
            {0x01,    0x01,  0x00},  /*NLO: 3*/
            {0x06,    0x01,  0x00},  /*NLO: 4*/
            {0x07,    0x01,  0x00},  /*NLO: 5*/
            {0x27,    0x01,  0x00},  /*NLO: 6*/
            {0x27,    0x01,  0x00},  /*NLO: 7*/
            {0x0A,    0x00,  0x00},  /*NLO: 8*/
            {0x0A,    0x00,  0x00},  /*NLO: 9*/
            {0x0F,    0x00,  0x00},  /*NLO: 10*/
        };
        UINT8 MixDivTableLeoE[11][3] = {
            /*121CH  1240H  121EH*/
            {0x02, 0x00, 0x00}, /*dummy*/
            {0x02, 0x00, 0x01}, /*NLO: 1*/
            {0x02, 0x00, 0x00}, /*NLO: 2*/
            {0x03, 0x00, 0x00}, /*NLO: 3*/
            {0x04, 0x00, 0x00}, /*NLO: 4*/
            {0x05, 0x00, 0x00}, /*NLO: 5*/
            {0x25, 0x00, 0x00}, /*NLO: 6*/
            {0x08, 0x00, 0x00}, /*NLO: 7*/
            {0x08, 0x00, 0x00}, /*NLO: 8*/
            {0x08, 0x00, 0x00}, /*NLO: 9*/
            {0x0D, 0x00, 0x00}, /*NLO: 10*/
        };

        if(pTuner->HighMD)
        {
            pNLOMixer = pTuner->pNLOMixerHMD;
        }
        else
        {
            pNLOMixer = pTuner->pNLOMixerLMD;
        }
        if(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
        {
            reg121c = MixDivTableLeoE[pNLOMixer->NLO][0];
            reg1240 = MixDivTableLeoE[pNLOMixer->NLO][1];
            reg121e = MixDivTableLeoE[pNLOMixer->NLO][2];

            mixr_pll_mixr_div_mode_l = MixDivTableLeoE[pTuner->pNLOMixerLMD->NLO][0];
            mixr_pll_mixr_div_mode_h = MixDivTableLeoE[pTuner->pNLOMixerHMD->NLO][0];
        }
        else
        {/*ATBM_LEOF_CHIP_ID, ATBM_LEOG_CHIP_ID*/
            reg121c = MixDivTableLeoF[pNLOMixer->NLO][0];
            reg1240 = MixDivTableLeoF[pNLOMixer->NLO][1];
            reg121e = MixDivTableLeoF[pNLOMixer->NLO][2];

            mixr_pll_mixr_div_mode_l = MixDivTableLeoF[pTuner->pNLOMixerLMD->NLO][0];
            mixr_pll_mixr_div_mode_h = MixDivTableLeoF[pTuner->pNLOMixerHMD->NLO][0];
        }

        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x40, reg1240); /*mixr_div_mode_en*/
        if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
        {/*ATBM_LEOE_CHIP_ID  ATBM_LEOF_CHIP_ID*/
            ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x4A, (pTuner->pNLOMixerLMD->NLO != pTuner->pNLOMixerHMD->NLO)?(0x01):(0x00)); /*params_div_new_en*/
        }
    }
    else
    {
        switch(pTuner->pNLOMixer->NLO)
        {
            case 7:
                reg121c = 0x03; reg121e = 0x00; 
                break;
            case 6:
                reg121c = 0x02; reg121e = 0x00; 
                break;
            case 5:
                reg121c = 0x01; reg121e = 0x00; 
                break;
            case 4:
                reg121c = 0x00; reg121e = 0x00; 
                break;
            case 3:
                reg121c = 0x05; reg121e = 0x00; 
                break;
            case 2:
                reg121c = 0x04; reg121e = 0x00; 
                break;
            case 1:
                reg121c = 0x00; reg121e = 0x01; 
                break;
        }

        mixr_pll_mixr_div_mode_l = reg121c;
        mixr_pll_mixr_div_mode_h = reg121c;
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1C, reg121c); /*mixr_pll_mixr_div_mode[2:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1E, reg121e); /*mixr_pll_mixr_div_mux*/
    Data[0] = mixr_pll_mixr_div_mode_l; /* 0x16,0x44,  mixr_pll_mixr_div_mode_l */
    Data[1] = mixr_pll_mixr_div_mode_h; /* 0x16,0x45,  mixr_pll_mixr_div_mode_h */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x44, Data,2);
    Data[0] = reg121e; /* 0x16,0x48,  params_mixr_pll_mixr_div_mux_l */
    Data[1] = reg121e; /* 0x16,0x49,  params_mixr_pll_mixr_div_mux_h */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x48, Data,2);

    return ret;

}

static UINT8 ATBM2040DrvNAdc2AdcDivPDft(UINT32 NAdc)
{
    UINT8 adc_div_p_dft = 0;
    adc_div_p_dft = (UINT8)NAdc;
    return adc_div_p_dft;
}


/************************************************************
*Description: ADC clk module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvADCCLKSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 FsMode = 0;
    UINT8 Data[4] = {0};
    UINT32 invFsMul = 0;
    UINT32 FS_H = (UINT32)((pTuner->HMDAdcClkHz/100000 + 10)/20),FS_L = (UINT32)((pTuner->LMDAdcClkHz/100000+10)/20);
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    ATBM2040Data64_t i64Data, i64Data1;

    /*ADC divider */
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x05, ATBM2040DrvNAdc2AdcDivPDft(pTuner->pAdcDiv->N_ADC)); /*adc_div_p_dft*/

    /*Set params_adc_div_p_dft_l and params_adc_div_p_dft_h*/
    Data[0] = ATBM2040DrvNAdc2AdcDivPDft(pTuner->pAdcDivLMD->N_ADC); /* 0x16,0x42, params_adc_div_p_dft_l[3:0]*/
    Data[1] = ATBM2040DrvNAdc2AdcDivPDft(pTuner->pAdcDivHMD->N_ADC); /* 0x16,0x43, params_adc_div_p_dft_h[3:0]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x42, Data,2);

    if((ATBM_LEOB_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        /*HMD*/
        if(FS_H <= 190)
        {
            FsMode = 0x00;
        }
        else if((FS_H > 190)&&(FS_H < 210))
        {
            FsMode = 0x01;
        }
        else if(FS_H >= 210)
        {
            FsMode = 0x02;
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x3B, FsMode); /*params_fs_mode_1[1:0]*/
    }

    /*params_inv_fs_mul4_1[9:0] = (4/Fs)*2^34 = 2^36/Fs = 2^37/(AdcClk*1000000) = 0x80000000/AdcClk/15625*/
    /*invFsMul = (UINT32)(0x80000000/(pTuner->HMDAdcClkHz/(1000*1000))/15625);*/ 
    i64Data.High = 0x20;
    i64Data.Low = 0x00;

    i64Data1.High = 0;
    i64Data1.Low = pTuner->HMDAdcClkHz;
    invFsMul = ATBM64Div(i64Data,i64Data1);
    Data[2] = invFsMul&0xFF; /* 0x14,0x4A, params_inv_fs_mul4_1[7:0]*/
    Data[3] = (invFsMul>>8)&0x03; /* 0x14,0x4B, params_inv_fs_mul4_1[9:8]*/

    if((ATBM_LEOB_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        /*LMD*/
        if(FS_L <= 190)
        {
            FsMode = 0x00;
        }
        else if((FS_L > 190)&&(FS_L < 210))
        {
            FsMode = 0x01;
        }
        else if(FS_L >= 210)
        {
            FsMode = 0x02;
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x3A, FsMode); /*params_fs_mode_0[1:0]*/
    }
    /*params_inv_fs_mul4_0[9:0] = (4/Fs)*2^34 = 2^36/Fs = 2^37/(AdcClk*1000000) = 0x80000000/AdcClk/15625*/
    /* invFsMul = (UINT32)(0x80000000/(pTuner->LMDAdcClkHz/(1000*1000))/15625); */
    i64Data1.High = 0;
    i64Data1.Low = pTuner->LMDAdcClkHz;
    invFsMul = ATBM64Div(i64Data,i64Data1);
    Data[0] = invFsMul&0xFF; /* 0x14,0x48, params_inv_fs_mul4_0[7:0]*/
    Data[1] = (invFsMul>>8)&0x03; /* 0x14,0x49, params_inv_fs_mul4_0[9:8]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x48, Data,4);

    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)&&(ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode))
    {
        UINT32 i = 0, j = 0;
        ATBM2040AtvSet_t *p = AtvSettingReg;
        if((384000000 == pTuner->HMDAdcClkHz)||(384000000 == pTuner->LMDAdcClkHz))
        {
            Data[0] = 0x01;
            Data[1] = 0x08;
        }
        else
        {
            Data[0] = 0x00;
            Data[1] = 0x08;
        }
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x6F, Data,2); /*params_t_sample_rssi[7:0]*/
        for(i=0;i<ATBM2040_ATV_SETTING_REG_CNT;i++)
        {
            /*if(ATBM2040ABS((SINT32)p->FreqKHz - (SINT32)pTuner->FreqKHz) <= 500)*/
            if(p->FreqKHz == pTuner->FreqKHz)
            {
                break;
            }
            p++;
        }
        if(i>=ATBM2040_ATV_SETTING_REG_CNT)
        {
            p = &AtvSettingReg[ATBM2040_ATV_SETTING_REG_CNT-1];
        }
        for(j=0;j<p->RegNum;j++)
        {
            ret |= ATBM2040RegWrite(pI2CAddr,p->RegList[j].BaseReg,p->RegList[j].OffReg, p->RegList[j].Val);
        }

        i = pTuner->FreqKHz%pTuner->Config.OSCFreqKHz;
        if((786000 == pTuner->FreqKHz)||((785870 == pTuner->FreqKHz)))/*(ATBM2040ABS((SINT32)786000 - (SINT32)pTuner->FreqKHz) <= 500)*/
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x08);
        }
        else if((866000 == pTuner->FreqKHz)||((865870 == pTuner->FreqKHz)))/*(ATBM2040ABS((SINT32)866000 - (SINT32)pTuner->FreqKHz) <= 500)*/
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x02);
        }
        else if((i <= pTuner->BWKHz/2)||((pTuner->Config.OSCFreqKHz - i) <= pTuner->BWKHz/2))
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x08);
        }
        else
        {
            if(ATBM2040_CLK_MODE_EXT == pTuner->Config.ClkMode)
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x0F);
            }
            else
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x02);
            }
        }
    }
    return ret;
}

/************************************************************
*Description: Calculate ADC clk
*************************************************************/
void ATBM2040DrvADCClkCal(ATBM2040_t *pTuner, UINT32 *pHMDAdcClkHz, UINT32  *pLMDAdcClkHz)
{
    ATBM2040NLOMixer_t *pNLOMixer = NULL;
    UINT32 Multiplier, Multiplier1;
    ATBM2040Data64_t i64Data, i64Data1;

    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        if(ATBM2040_VHF_CHECK(pTuner->FreqKHz))
        {
            if(pTuner->FreqKHz < ATBM2040_VHF2_LOW_KHZ)
            {/*VHF1*/
                pTuner->Band = ATBM2040_RF_BAND_VHF1;
            }
            else
            {/*VHF2*/
                pTuner->Band = ATBM2040_RF_BAND_VHF2;
            }
        }
        else
        {
            pTuner->Band = ATBM2040_RF_BAND_UHF;
        }
    }
#ifndef ATBM2040_CHIP_DEBUG_OPEN
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {    
        /*Setting IF frequency*/
        if(((ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode))&&(!ATBM2040_VHF_CHECK(pTuner->FreqKHz)))
        {
            pTuner->MixerIF = 7000000;
        }
        else if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
        {
            pTuner->MixerIF = 7000000;
        }
        else
        {
            pTuner->MixerIF = 5000000;
        }
    }
#endif

    pNLOMixer = pTuner->pNLOMixerHMD;
    pTuner->pAdcDivHMD = ATBM2040DrvADCDivider(pTuner,TRUE);


    Multiplier =  pTuner->FreqKHz *1000 + pTuner->MixerIF;
    Multiplier1 = pNLOMixer->NMixer * pNLOMixer->NLO;
    ATBM64Mult(&i64Data,Multiplier, Multiplier1);/* KHz */
    i64Data1.High = 0;
    i64Data1.Low = pTuner->pAdcDivHMD->N_ADC; 
    pTuner->HMDAdcClkHz = *pHMDAdcClkHz = ATBM64Div(i64Data,i64Data1);


    /* pTuner->LMDAdcClk = *pLMDAdcClk = ((pTuner->FreqKHz/1000.0 - pTuner->MixerIF/1000000.0) * pNLOMixer->NMixer  * pNLOMixer->NLO)/pADCDivider->N_ADC; */
    pNLOMixer = pTuner->pNLOMixerLMD;
    pTuner->pAdcDivLMD = ATBM2040DrvADCDivider(pTuner,FALSE);
    Multiplier =  pTuner->FreqKHz *1000 - pTuner->MixerIF;
    Multiplier1 = pNLOMixer->NMixer * pNLOMixer->NLO;
    ATBM64Mult(&i64Data,Multiplier, Multiplier1);/* KHz */
    i64Data1.High = 0;
    i64Data1.Low = pTuner->pAdcDivLMD->N_ADC; 
    pTuner->LMDAdcClkHz = *pLMDAdcClkHz = ATBM64Div(i64Data,i64Data1);

    if(pTuner->HighMD)
    {
        pTuner->pAdcDiv = pTuner->pAdcDivHMD;
    }
    else
    {
        pTuner->pAdcDiv = pTuner->pAdcDivLMD;
    }
    Multiplier = (pTuner->pAdcDivHMD->N_ADC)%(pTuner->pNLOMixerHMD->NMixer*pTuner->pNLOMixerHMD->NLO);
    Multiplier1 = (pTuner->pAdcDivLMD->N_ADC)%(pTuner->pNLOMixerLMD->NMixer*pTuner->pNLOMixerLMD->NLO);
    if((0 == Multiplier)&&(0 == Multiplier1))
    {
        pTuner->ModeTrend = 0x00;
    }
    else if(0 == Multiplier)
    {
        pTuner->ModeTrend = 0xF0;
    }
    else if(0 == Multiplier1)
    {
        pTuner->ModeTrend = 0x10;
    }
    else
    {
        pTuner->ModeTrend = 0x00;
    }
}

/************************************************************
*Description: Phase and gain compensation setting
*************************************************************/
#if ATBM2040_GAIN_PHASE_COMPENSATION
static ATBM2040_ERROR_e ATBM2040DrvPhaseAndGainConfig(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 n = 0,i = 0;
    ATBM2040Reg_t *pReg = NULL;
    SINT32 *pData = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    n = (pTuner->FreqKHz+20000)/40000;
    if(n > 0)
    {
        n = n - 1;
    }
    if(n > 24)
    {
        n = 24;
    }
    /*LNA phase compensation*/
    pData = &ATBM2040LNAPhase[n][0];
    for(i=0;i<ATBM2040_LNA_PHASE_REG_CNT/2;i++)
    {
        pReg = &LNAPhaseReg[2*i];
        ret |= ATBM2040RegWrite(pI2CAddr,pReg->BaseReg,pReg->OffReg,pData[i]&0xFF);
        ret |= ATBM2040RegWrite(pI2CAddr,(pReg+1)->BaseReg,(pReg+1)->OffReg,(pData[i]&0xFF00)>>8);
    }
    /*RTF/RF_VGA1/2  phase compensation*/
    if(ATBM2040_VHF_CHECK(pTuner->FreqKHz))
    {
        pData = &ATBM2040RTFPhase[n][0];
    }
    else
    {
        pData = &ATBM2040RFVGA12Phase[n][0];
    }
    pReg = RFVGA1PhaseReg;
    for(i=0;i<ATBM2040_RFVGA1_PHASE_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,(UINT8)pData[i]);
    }

    pReg = RFVGA2PhaseReg;
    pData = &ATBM2040RFVGA12Phase[n][0];
    for(i=0;i<ATBM2040_RFVGA2_PHASE_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,(UINT8)pData[i]);
    }

    /*IF_VGA  phase compensation */
    pReg = IFVGA2PhaseReg;
    pData = ATBM2040IFVGAPhase;
    for(i=0;i<ATBM2040_IFVGA2_PHASE_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,(UINT8)pData[i]);
    }

    /*LNA_gain compensation*/
    pReg = LNAGainReg;
    pData = &ATBM2040LNAGain[n][0];
    for(i=0;i<ATBM2040_LNA_GAIN_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,(UINT8)pData[i]);
    }

    /*RTF/RF_VGA1/2  delta gain compensation*/
    if(ATBM2040_VHF_CHECK(pTuner->FreqKHz))
    {
        pData = &ATBM2040RTFGain[n][0];
    }
    else
    {
        pData = &ATBM2040RFVGA12Gain[n][0];
    }
    pReg = RFVGA1GainReg;
    for(i=0;i<ATBM2040_RFVGA1_GAIN_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,(UINT8)pData[i]);
    }

    pReg = RFVGA2GainReg;
    pData = &ATBM2040RFVGA12Gain[n][0];
    for(i=0;i<ATBM2040_RFVGA2_GAIN_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,(UINT8)pData[i]);
    }

    /*IF_VGA  delta gain compensation */
    pReg = IFVGA2GainReg;
    pData = ATBM2040IFVGAGain;
    for(i=0;i<ATBM2040_IFVGA2_GAIN_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,(UINT8)pData[i]);
    }

    return ret;
}
#endif

static ATBM2040_ERROR_e ATBM2040DrvFreqShiftFromBBtoIF(ATBM2040_t *pTuner,BOOL OnlyCalculate,UINT8 *pHilbertF1_1,UINT8 *pHilbertF1_0)
{
/* hilbert_f1_L = (SINT32)(IF_DSP*(1/(FS_L))*2*(0x01<<17) + 0.5); */
/* hilbert_f1_H = (SINT32)(IF_DSP*(1/(FS_H))*2*(0x01<<17) + 0.5); */
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 FS_L = 0,FS_H = 0;
    SINT32 hilbert_f1_L = 0,hilbert_f1_H = 0;
    UINT32 IF_DSP = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    UINT32 Multiplier, Multiplier1;
    ATBM2040Data64_t i64Data, i64Data1;

    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
    {
        IF_DSP = pTuner->Config.AtvIFOut.IFOutFreqHz;
    }
    else
    {
        IF_DSP = pTuner->Config.DtvIFOut.IFOutFreqHz;
    }

    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)||(ATBM_LEOC_CHIP_ID == pTuner->ChipID))
    {
        IF_DSP *= 4;
    }

    FS_L = pTuner->LMDAdcClkHz/2;
    FS_H = pTuner->HMDAdcClkHz/2;


    Multiplier =  IF_DSP;
    Multiplier1 = 0x80000; /* 4*(0x01<<17) */
    ATBM64Mult(&i64Data,Multiplier, Multiplier1);/* KHz */
    i64Data1.High = 0;
    i64Data1.Low = FS_L; 
    hilbert_f1_L = ATBM64Div(i64Data,i64Data1);
    hilbert_f1_L = ((hilbert_f1_L + 1)/2);


    Multiplier =  IF_DSP;
    Multiplier1 = 0x80000; /* 4*(0x01<<17) */
    ATBM64Mult(&i64Data,Multiplier, Multiplier1);/* KHz */
    i64Data1.High = 0;
    i64Data1.Low = FS_H; 
    hilbert_f1_H = ATBM64Div(i64Data,i64Data1);
    hilbert_f1_H = ((hilbert_f1_H + 1)/2);


    if(OnlyCalculate)
    {
        pHilbertF1_1[0] = hilbert_f1_H&0xFF;
        pHilbertF1_1[1] = (hilbert_f1_H>>8)&0xFF;
        pHilbertF1_1[2] = (hilbert_f1_H>>16)&0x07;
        
        pHilbertF1_0[0] = hilbert_f1_L&0xFF;
        pHilbertF1_0[1] = (hilbert_f1_L>>8)&0xFF;
        pHilbertF1_0[2] = (hilbert_f1_L>>16)&0x07;
    }
    else
    {   
        UINT8 Data[3] ={0};
        Data[0] = hilbert_f1_H&0xFF; /* 0x13,0xAD, params_hilbert_f1_1[7:0] */
        Data[1] = (hilbert_f1_H>>8)&0xFF; /* 0x13,0xAE, params_hilbert_f1_1[15:8] */
        Data[2] = (hilbert_f1_H>>16)&0x07; /* 0x13,0xAF, params_hilbert_f1_1[18:16] */
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x13,0xAD, Data,3); /*params_hilbert_f1_1*/
        
        Data[0] = hilbert_f1_L&0xFF; /* 0x13,0xA3, params_hilbert_f1_0[7:0] */
        Data[1] = (hilbert_f1_L>>8)&0xFF; /* 0x13,0xA4, params_hilbert_f1_0[15:8] */
        Data[2] = (hilbert_f1_L>>16)&0x07; /* 0x13,0xA5, params_hilbert_f1_0[18:16] */
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x13,0xA3, Data,3); /*params_hilbert_f1_0*/
    }
    return ret;
}

/************************************************************
*Description: Signal frequency parameters setting in DSP module
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvDSPSignalFreqParamSetting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    SINT32 TmpParam = 0,TmpParam2 = 0;
    SINT32 path1_hlo = 0,path1_llo = 0;
    UINT32 LMDAdcClk = 0,HMDAdcClk = 0;
    SINT32 MixerIF = 0, BandWidth = 0;
    ATBM2040Data64_t i64Data, i64Data1;
    UINT32 i = 0,DataLen = 0;
    UINT32 SigDown21Freq = 21000000,SignalN1Out = 2000000;
    UINT32 SigDown21FreqH = 0x280,SigDown21FreqL = 0xDE800000;
    UINT8 Data[64] = {0};
    ATBM2040RegGroup_t *pGrp = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        if(((ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
                ||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)
                ||(ATBM2040_SIGNAL_MODE_DVBC == pTuner->SignalMode))
            &&(pTuner->BandBak != pTuner->Band))
        {
            switch(pTuner->Band)
            {
                case ATBM2040_RF_BAND_UHF:
                    pGrp = AciN234CalResultUHF;
                    break;
                case ATBM2040_RF_BAND_VHF2:
                    pGrp = AciN234CalResultVHF2;
                    break;                
                case ATBM2040_RF_BAND_VHF1:
                    pGrp = AciN234CalResultVHF1;
                    break;
                default:
                    pGrp = AciN234CalResultUHF;
                    break;
            }
            while(0 != pGrp->Len)
            {
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pGrp->BaseReg,pGrp->OffReg,pGrp->Data,pGrp->Len);
                pGrp++;
            }
        }
    }

    LMDAdcClk = pTuner->LMDAdcClkHz;
    HMDAdcClk = pTuner->HMDAdcClkHz;
    if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
    {
        SigDown21Freq = 28000000;
        SigDown21FreqH = 0x356; /*2^17 * SigDown21Freq*/
        SigDown21FreqL = 0x7E000000;
    }
    else if(7000000 == pTuner->MixerIF)
    {
        SigDown21Freq = 24000000;
        SignalN1Out = 1000000;
        SigDown21FreqH = 0x2DC; /*2^17 * SigDown21Freq*/
        SigDown21FreqL = 0x6C000000;
    }

    i = 0;
    /*sig_down_2_1_fo_sa_path1_hlo*/
    i64Data.High = SigDown21FreqH;
    i64Data.Low = SigDown21FreqL; 
    i64Data1.High = 0;
    i64Data1.Low = HMDAdcClk; 
    path1_hlo = ATBM64Div(i64Data,i64Data1);
    TmpParam = -path1_hlo;
    Data[i++] = (UINT8)(TmpParam&0xFF);
    Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
    /*sig_down_2_1_fo_sa_path1_llo*/
    i64Data.High = SigDown21FreqH;
    i64Data.Low = SigDown21FreqL;
    i64Data1.High = 0;
    i64Data1.Low = LMDAdcClk; 
    path1_llo = ATBM64Div(i64Data,i64Data1);
    TmpParam = -path1_llo;
    Data[i++] = (UINT8)(TmpParam&0xFF);
    Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
    /*sig_down_2_1_fo_sa_path2_hlo*/
    TmpParam = path1_hlo;
    Data[i++] = (UINT8)(TmpParam&0xFF);
    Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
    /*sig_down_2_1_fo_sa_path2_llo*/
    TmpParam = path1_llo;
    Data[i++] = (UINT8)(TmpParam&0xFF);
    Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
    DataLen = i;
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x23,0x50,Data,DataLen);

    if((pTuner->BWKHzBak == pTuner->BWKHz)&&(pTuner->MixerIFBak == pTuner->MixerIF))
    {
        return ret;
    }
    
    MixerIF = pTuner->MixerIF;
    BandWidth = pTuner->BWKHz*1000;

    i = 0;
    if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
    {
        /*signal_n_1_llo*/
        TmpParam = (2*MixerIF - 3*BandWidth);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_n_1_hlo*/
        TmpParam = -TmpParam;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_n_1_out_llo*/
        TmpParam = ((2*MixerIF + 3*BandWidth) + 256)>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_n_1_out_hlo*/
        TmpParam = -TmpParam;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        
    }
    else
    {
        /*signal_n_1_llo*/
        TmpParam = ((MixerIF - BandWidth - 2000000) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_n_1_hlo*/
        TmpParam = -TmpParam;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_n_1_out_llo*/
        TmpParam = ((MixerIF + BandWidth + SignalN1Out) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_n_1_out_hlo*/
        TmpParam = -TmpParam;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
    }
    DataLen = i;
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0x84,Data,DataLen);

    i = 0;
    if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
    {
        /*signal_nplus1_llo*/
        TmpParam = ((2*MixerIF + 3*BandWidth) + 256)>>9;
        TmpParam2 = -TmpParam;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus1_llo*/
        TmpParam = (2*MixerIF - 3*BandWidth);        
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus1_hlo*/
        TmpParam = -TmpParam;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus1_hlo*/
        TmpParam = TmpParam2;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
    }
    else
    {
        /*signal_nplus1_llo*/
        TmpParam = ((MixerIF + BandWidth) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus1_llo*/
        TmpParam = ((MixerIF - BandWidth) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus1_hlo*/
        TmpParam = -TmpParam;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus1_hlo*/
        TmpParam = ((-MixerIF - BandWidth) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
    }
    DataLen = i;
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x19,0x98,Data,DataLen);

    i = 0;
    if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
    {
        /*signal_nminus1_llo_sa*/
        TmpParam = (2*MixerIF - 3*BandWidth);        
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus1_hlo_sa*/
        TmpParam = ((-2*MixerIF - 3*BandWidth) + 256)>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus2_llo_sa*/
        TmpParam = (2*MixerIF - 7*BandWidth + 2*SigDown21Freq);        
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus2_hlo_sa*/
        TmpParam = (-2*MixerIF - 7*BandWidth + 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus3_llo_sa*/
        TmpParam = (2*MixerIF - 11*BandWidth + 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus3_hlo_sa*/
        TmpParam = (-2*MixerIF - 11*BandWidth + 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus4_llo_sa*/
        TmpParam = (2*MixerIF - 11*BandWidth + 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus4_hlo_sa*/
        TmpParam = (-2*MixerIF - 11*BandWidth + 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus1_llo_sa*/
        TmpParam = ((2*MixerIF + 3*BandWidth) + 256)>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus1_hlo_sa*/
        TmpParam = ((-2*MixerIF + 3*BandWidth) + 256)>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus2_llo_sa*/
        TmpParam = (2*MixerIF + 7*BandWidth - 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus2_hlo_sa*/
        TmpParam = (-2*MixerIF + 7*BandWidth - 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus3_llo_sa*/
        TmpParam = (2*MixerIF + 11*BandWidth - 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus3_hlo_sa*/
        TmpParam = (-2*MixerIF + 11*BandWidth - 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus4_llo_sa*/
        TmpParam = (2*MixerIF + 11*BandWidth - 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus4_hlo_sa*/
        TmpParam = (-2*MixerIF + 11*BandWidth - 2*SigDown21Freq);
        TmpParam = (TmpParam + ((TmpParam>=0)?(256):(-256)))>>9;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
    }
    else
    {
        /*signal_nminus1_llo_sa*/
        TmpParam = ((MixerIF - BandWidth) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus1_hlo_sa*/
        TmpParam = ((-MixerIF - BandWidth) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus2_llo_sa*/
        TmpParam = ((MixerIF - BandWidth*2 + SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus2_hlo_sa*/
        TmpParam = ((-MixerIF - BandWidth*2 + SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus3_llo_sa*/
        /*TmpParam = ((MixerIF - BandWidth*3 + SigDown21Freq) + 128)>>8;*/
        TmpParam = ((MixerIF*4 - BandWidth*13 + SigDown21Freq*4) + 512)>>10;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus3_hlo_sa*/
        /*TmpParam = ((-MixerIF - BandWidth*3 + SigDown21Freq) + 128)>>8;*/
        TmpParam = ((-MixerIF*4 - BandWidth*13 + SigDown21Freq*4) + 512)>>10;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus4_llo_sa*/
        TmpParam = ((MixerIF - BandWidth*4 + SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nminus4_hlo_sa*/
        TmpParam = ((-MixerIF - BandWidth*4 + SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus1_llo_sa*/
        TmpParam = ((MixerIF + BandWidth) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus1_hlo_sa*/
        TmpParam = ((-MixerIF + BandWidth) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus2_llo_sa*/
        TmpParam = ((MixerIF + BandWidth*2 - SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus2_hlo_sa*/
        TmpParam = ((-MixerIF + BandWidth*2 - SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus3_llo_sa*/
        /*TmpParam = ((MixerIF + BandWidth*3 - SigDown21Freq) + 128)>>8;*/
        TmpParam = ((MixerIF*4 + BandWidth*13 - SigDown21Freq*4) + 512)>>10;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus3_hlo_sa*/
        /*TmpParam = ((-MixerIF + BandWidth*3 - SigDown21Freq) + 128)>>8;*/
        TmpParam = ((-MixerIF*4 + BandWidth*13 - SigDown21Freq*4) + 512)>>10;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus4_llo_sa*/
        TmpParam = ((MixerIF + BandWidth*4 - SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
        /*signal_nplus4_hlo_sa*/
        TmpParam = ((-MixerIF + BandWidth*4 - SigDown21Freq) + 128)>>8;
        Data[i++] = (UINT8)(TmpParam&0xFF);
        Data[i++] = (UINT8)((TmpParam>>8)&0xFF);
        Data[i++] = (UINT8)((TmpParam>>16)&0xFF);
    }
    DataLen = i;
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x22,0xC1,Data,DataLen);


    return ret;
}


/************************************************************
*Description: DSP module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvDSPRegConfig(ATBM2040_t *pTuner,UINT32 HMDAdcClk,UINT32 LMDAdcClk)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    SINT32 hilbert_f0_L = 0;
    SINT32 hilbert_f0_H = 0;
    SINT32 Fs_ADC_H = 0,Fs_ADC_L = 0;
    UINT32 FS_L = 0,FS_H = 0;
    SINT32 MixerIF = 0;
    UINT8 Data1[6] = {0};
    UINT8 Data2[6] = {0};

    UINT32 Multiplier, Multiplier1;
    ATBM2040Data64_t i64Data, i64Data1;

    /* SINT32 hilbert_f1_L = 0,hilbert_f1_H = 0; */
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    FS_L = LMDAdcClk/2;
    FS_H = HMDAdcClk/2;
    MixerIF = pTuner->MixerIF;


    /* hilbert_f0_H = (SINT32)(-MixerIF*(1/(FS_H/4))*2*(0x01<<17) - offset); */
    /* hilbert_f0_L = (SINT32)(MixerIF*(1/(FS_L/4))*2*(0x01<<17) + offset); */
    Multiplier =  MixerIF;
    Multiplier1 = 0x200000; /* 16*(0x01<<17) */
    ATBM64Mult(&i64Data,Multiplier, Multiplier1);/* KHz */
    i64Data1.High = 0;
    i64Data1.Low = FS_H; 
    hilbert_f0_H = ATBM64Div(i64Data,i64Data1);
    hilbert_f0_H = ((hilbert_f0_H + 1)/2)*(-1);


    Multiplier =  MixerIF;
    Multiplier1 = 0x200000; /* 16*(0x01<<17) */
    ATBM64Mult(&i64Data,Multiplier, Multiplier1);/* KHz */
    i64Data1.High = 0;
    i64Data1.Low = FS_L; 
    hilbert_f0_L = ATBM64Div(i64Data,i64Data1);
    hilbert_f0_L = ((hilbert_f0_L + 1)/2);
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)||(ATBM_LEOC_CHIP_ID == pTuner->ChipID))
    {
        hilbert_f0_H = 0 - hilbert_f0_H;
        hilbert_f0_L = 0 - hilbert_f0_L;
    }
    else
    {
        if(pTuner->ADCIQSwap)
        {
            hilbert_f0_H = 0 - hilbert_f0_H;
            hilbert_f0_L = 0 - hilbert_f0_L;
        }
    }

    /*frequency shift from IF to BB in DSP*/
    Data1[0] = hilbert_f0_L&0xFF;
    Data1[1] = (hilbert_f0_L>>8)&0xFF;
    Data1[2] = (hilbert_f0_L>>16)&0x07;
    Data2[0] = hilbert_f0_H&0xFF;
    Data2[1] = (hilbert_f0_H>>8)&0xFF;
    Data2[2] = (hilbert_f0_H>>16)&0x07;


    /*frequency shift from BB to IF in DSP*/
    ret |= ATBM2040DrvFreqShiftFromBBtoIF(pTuner,TRUE,&Data2[3],&Data1[3]);

    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x13,0xA0, Data1,6);
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x13,0xAA, Data2,6);

    /*RC filte sampling rate setting*/
    Fs_ADC_H = (SINT32)(FS_H + 0x1000)/0x2000; /*(FS_H/8/(0x01<<9) + 1)/2*/
    Fs_ADC_L = (SINT32)(FS_L + 0x1000)/0x2000; /*(FS_L/8/(0x01<<9) + 1)/2*/
    Data1[0] = Fs_ADC_L&0xFF; /* 0x13,0x18, params_rc_fs_adc_0[7:0]*/
    Data1[1] = (Fs_ADC_L>>8)&0xFF; /*0x13,0x19,  params_rc_fs_adc_0[15:8]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x13,0x18, Data1,2);
    Data1[0] = Fs_ADC_H&0xFF; /* 0x13,0xB8, params_rc_fs_adc_0[7:0]*/
    Data1[1] = (Fs_ADC_H>>8)&0xFF; /* 0x13,0xB9, params_rc_fs_adc_0[7:0]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x13,0xB8, Data1,2);

    /*Signal frequency parameters setting*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040DrvDSPSignalFreqParamSetting(pTuner);
    }

    return ret;
}

/************************************************************
*Description: VHF module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvVHFSetting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040VHFChIndex_t *pIndex = NULL;
    UINT8 tmpReg = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    if((ATBM_LEOB_CHIP_ID == pTuner->ChipID)||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x12,0x16, &tmpReg); /*Rsv2*/
        tmpReg = ((tmpReg&0xF0)|0x05);
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x16, tmpReg); /*Rsv2<3:0>=4'b0101*/
    }
    /*VHF filter registers setting*/
    ATBM2040RegListWrite(pI2CAddr,VHFFilterReg,ATBM2040_VHF_FILTER_REG_CNT);
    pIndex = ATBM2040DrvVHFFreqIndex(pTuner->FreqKHz);
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x00, pIndex->vhf_fltr_data); /*vhf_fltr_data[7:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x01, pIndex->vhf_fltr_ref_code); /*vhf_fltr_ref_code[7:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x16,0xF9, pIndex->vhf_fltr_data);    /*params_vhf_fltr_data[7:0] */

    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x21, pIndex->vhf_fltr_res1_sel);    /*vhf_fltr_res1_sel[2:0]*/

    /*GmC calibration */
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x1D, 0x01); /*vhf_fltr_cal_rst*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x1D, 0x00); /*vhf_fltr_cal_rst*/

    ATBM2040Delay(1000);
    ret |= ATBM2040RegRead(pI2CAddr,0x06,0x22, &tmpReg); /*vhf_fltr_ready_reg*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2E, 0x00); /*vhf_filt_cal_clk_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x1C, 0x00); /*vhf_fltr_bias_pd*/
    if(0x01 != tmpReg)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x1E, 0x01); /*vhf_fltr_cap_code_sel*/
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x00); /*params_freq_path*/

    return ret;
}

/************************************************************
*Description: VHF1 module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvVHF1Setting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040VHF1ChIndex_t *pIndex = NULL;
    ATBM2040Reg_t TmpReg;
    UINT8 Val = 0,cap_cal = 0;
    UINT8 i = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    pIndex = ATBM2040DrvVHF1FreqIndex((pTuner->FreqKHz+500)/1000);

    /*VHF filter registers setting*/
    ATBM2040_REG_ADDR_SET(TmpReg,0x06,0x29);
    TmpReg.Val = pIndex->vhf_fltr_ref_code;
    ATBM2040RegListWriteExt(pI2CAddr,VHF1FilterReg,ATBM2040_VHF1_FILTER_REG_CNT,TmpReg);
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x01); /*vhf2_fltr_pwdn_ldo*/
    }

    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2E, 0x01); /*Vhf_fltr_cal_clk_en*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x24, 0x00); /*Vhf_fltr_cal_reset*/
    ATBM2040Delay(1000);
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x24, 0x01); /*Vhf_fltr_cal_reset*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x26, 0x01); /*Vhf_fltr_start*/

    while(i < 10)
    {
        ATBM2040Delay(10);
        ret |= ATBM2040RegRead(pI2CAddr,0x06,0x32, &Val); /*vhf_fltr_cal_busy*/
        if(0x00 == Val)
        {
            break;
        }
        i++;
    }

    ret |= ATBM2040RegRead(pI2CAddr,0x06,0x34, &cap_cal); /*vhf_fltr_ref_code_out*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2E, 0x00); /*Vhf_fltr_cal_clk_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x25, 0x00); /*Vhf_fltr_cal_sel*/

    ret |= ATBM2040RegRead(pI2CAddr,0x06,0x33, &Val); /*vhf_fltr_cal_fail*/
    if(0x00 == Val)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x29, cap_cal); /*vhf_fltr_code_ref*/
    }

    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0A, 0x00); /*lna_band*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x00); /*lna_ldo_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x00); /*params_freq_path*/
    return ret;
}


/************************************************************
*Description: VHF2 module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvVHF2Setting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 filt_fcal_busy = 0,filt_fcal_fail = 0;
    UINT8 uhf_filt_cal_ctrl_fail = 0,uhf_filt_cal_ctrl_suc = 0;
    UINT32 CenterFreqMHz = 0;
    UINT32 FltrGmSwitch = 0,FltrManual = 0;
    ATBM2040VHF2ChIndex_t *pIndex = NULL;
    UINT8 vhf2_fltr_fcal_gm_gain = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    CenterFreqMHz = (pTuner->FreqKHz+500)/1000;
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x01); /*lna_ldo_pd*/

    /*Setting the VHF2 filter and  Calibration*/ 
    if((0 != pTuner->LowCousumMd)&&(ATBM_LEOG_CHIP_ID == pTuner->ChipID))
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x04};
        ATBM2040RegListWriteExt(pI2CAddr,LeoEVHF2FltCalibReg,ATBM2040_LEOE_VHF2_FILTER_REG_CNT,TmpReg);
    }
    else
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x0B};
        ATBM2040RegListWriteExt(pI2CAddr,LeoEVHF2FltCalibReg,ATBM2040_LEOE_VHF2_FILTER_REG_CNT,TmpReg);
    }

    /* VHF2 filter frequency index setting*/
    pIndex = ATBM2040DrvVHF2FreqIndex(pTuner->FreqKHz);
    FltrGmSwitch = pIndex->vhf2_fltr_gm_switch;
    uhf_filt_cal_ctrl_fail = 0x1C;
    uhf_filt_cal_ctrl_suc = 0x1D;

    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, (UINT8)(CenterFreqMHz&0xFF)); /*uhf_filt_freq[7:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (UINT8)((CenterFreqMHz>>8)&0x03)); /*uhf_filt_freq[9:8]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x1C, 0x00); /*uhf_fltr_count_h[1:0]*/

    /*reset VHF2 filter calibration module*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 0); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 1); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0E, 1); /*uhf_filt_en_cal*/
    
    ATBM2040Delay(400);
    ret |= ATBM2040RegRead(pI2CAddr,0x05,0x24, &filt_fcal_busy);/*uhf_filt_fcal_busy*/
    if(0x01 == filt_fcal_busy)
    {
        ATBM2040Delay(200);/*waiting the state changed!*/
    }
    ret |= ATBM2040RegRead(pI2CAddr,0x05,0x25, &filt_fcal_fail);/*uhf_filt_fcal_fail*/
    if(0x01 == filt_fcal_fail)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x23, uhf_filt_cal_ctrl_fail); /*vhf2_filt_cal_ctrl[4:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2F, 0x00); /*uhf_filt_cal_clk_en*/

        /* UHF filter frequency index setting*/ 
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, pIndex->vhf2_filt_freq&0xFF); /*uhf_filt_freq[7:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (pIndex->vhf2_filt_freq>>8)&0x03); /*uhf_filt_freq[9:8]*/

        if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        {
            FltrGmSwitch = ((pIndex->vhf2_fltr_gm_switch + 1)*15 + 5)/10;
            FltrManual = (UINT8)((pIndex->vhf2_fltr_gm_switch*7 + 5)/10);
        }
        else
        {
            FltrManual = (UINT8)((FltrGmSwitch*6+5)/10);
        }
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x23, uhf_filt_cal_ctrl_suc); /*uhf_filt_cal_ctrl[5:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2F, 0x00); /*uhf_filt_cal_clk_en*/

        ret |= ATBM2040RegRead(pI2CAddr,0x05,0x28, &vhf2_fltr_fcal_gm_gain);/*vhf2_fltr_fcal_gm_gain[5:0] */
        if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        {
            FltrGmSwitch = ((vhf2_fltr_fcal_gm_gain + 1)*15 + 5)/10;
            FltrManual = (UINT8)((vhf2_fltr_fcal_gm_gain*7 + 5)/10);
        }
        else
        {
            FltrGmSwitch = ((vhf2_fltr_fcal_gm_gain + 1)*18 + 5)/10;
            FltrManual = (UINT8)((vhf2_fltr_fcal_gm_gain*6+5)/10);
        }
    }

    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x12, (UINT8)FltrGmSwitch); /*uhf_fltr_gm_switch[5:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x15, (UINT8)FltrManual); /*uhf_filt_manual[5:0]*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0A, 0x00); /*lna_band*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x00); /*lna_ldo_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x00); /*params_freq_path*/
    return ret;
}



/************************************************************
*Description: UHF module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvUHFSetting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 filt_fcal_busy = 0,filt_fcal_fail = 0;
    UINT8 uhf_filt_cal_ctrl_fail = 0,uhf_filt_cal_ctrl_suc = 0;
    UINT32 CenterFreqMHz = 0;
    UINT32 FltrGmSwitch = 0,FltrManual = 0;
    ATBM2040UHFChIndex_t *pIndex = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
#ifdef ATBM2040_CHIP_DEBUG_OPEN
    BOOL DebugOpen = FALSE;
    double GmRatio = 1,ManaulRatio = 1;
    double RFRatio = 1;
    SINT32 RFOffset = 0;
#endif
    CenterFreqMHz = (pTuner->FreqKHz+500)/1000;
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x01); /*lna_ldo_pd*/

    /*Setting the UHF filter and  Calibration*/     
    if((0 != pTuner->LowCousumMd)&&(ATBM_LEOG_CHIP_ID == pTuner->ChipID))
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x04};
        ATBM2040RegListWriteExt(pI2CAddr,UHFFltCalibReg,ATBM2040_UHF_FILTER_REG_CNT,TmpReg);
    }
    else
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x0C};
        ATBM2040RegListWriteExt(pI2CAddr,UHFFltCalibReg,ATBM2040_UHF_FILTER_REG_CNT,TmpReg);
    }
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x01); /*vhf2_fltr_pwdn_ldo*/
    }

    /* UHF filter frequency index setting*/
    pIndex = ATBM2040DrvUHFFreqIndex(pTuner->FreqKHz);
    FltrGmSwitch = pIndex->uhf_fltr_gm_switch;
    FltrManual = pIndex->uhf_fltr_manual;
    uhf_filt_cal_ctrl_fail = 0x1E;
    uhf_filt_cal_ctrl_suc = 0x1F;

#ifdef ATBM2040_CHIP_DEBUG_OPEN
    ATBM2040DrvChipDebugUHFFilterGMManaulRatioGet(pTuner,&GmRatio,&ManaulRatio,&RFRatio,&RFOffset,&DebugOpen);
    if(DebugOpen)
    {
        /*ATBM2040DrvChipDebugUHFFilterCalibrate(pTuner,pIndex,&CenterFreqMHz,&FltrGmSwitch,&FltrManual,&DebugOpen);*/
        CenterFreqMHz = (UINT32)(CenterFreqMHz*RFRatio + RFOffset + 0.5);
        uhf_filt_cal_ctrl_fail = 0x16;
        uhf_filt_cal_ctrl_suc = 0x17;
    }
#endif
    if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
    {
        uhf_filt_cal_ctrl_fail = 0x16;
        uhf_filt_cal_ctrl_suc = 0x17;
    }

    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, (UINT8)(CenterFreqMHz&0xFF)); /*uhf_filt_freq[7:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (UINT8)((CenterFreqMHz>>8)&0x03)); /*uhf_filt_freq[9:8]*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x1C, 0x02); /*uhf_fltr_count_h[1:0]*/
    }

    /*reset UHF filter calibration module*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 0); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 1); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0E, 1); /*uhf_filt_en_cal*/

    ATBM2040Delay(400);
    ret |= ATBM2040RegRead(pI2CAddr,0x05,0x10, &filt_fcal_busy);/*uhf_filt_fcal_busy*/
    if(0x01 == filt_fcal_busy)
    {
        ATBM2040Delay(200);/*waiting the state changed!*/
    }
    ret |= ATBM2040RegRead(pI2CAddr,0x05,0x11, &filt_fcal_fail);/*uhf_filt_fcal_fail*/
    if(0x01 == filt_fcal_fail)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0C, uhf_filt_cal_ctrl_fail); /*uhf_filt_cal_ctrl[5:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2F, 0x00); /*uhf_filt_cal_clk_en*/

        /* UHF filter frequency index setting*/ 
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, pIndex->uhf_filt_freq&0xFF); /*uhf_filt_freq[7:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (pIndex->uhf_filt_freq>>8)&0x03); /*uhf_filt_freq[9:8]*/
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0C, uhf_filt_cal_ctrl_suc); /*uhf_filt_cal_ctrl[5:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2F, 0x00); /*uhf_filt_cal_clk_en*/

        if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        {
            UINT8 uhf_fltr_fcal_gm_gain = 0;
            ret |= ATBM2040RegRead(pI2CAddr,0x05,0x1D, &uhf_fltr_fcal_gm_gain);/*uhf_fltr_fcal_gm_gain */
            FltrGmSwitch = (((UINT32)uhf_fltr_fcal_gm_gain + 1)*225 + 50)/100;
            FltrManual = uhf_fltr_fcal_gm_gain;
        }
    }

#ifdef ATBM2040_CHIP_DEBUG_OPEN
    if(DebugOpen)
    {
        FltrManual = (UINT32)(FltrManual * ManaulRatio + 0.5);
        FltrGmSwitch = (UINT32)(FltrGmSwitch * GmRatio + 0.5);
    }
    else
#endif
    {
        if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
        {
            FltrManual = (FltrManual*8 + 5)/10;
            FltrGmSwitch = (FltrGmSwitch*6 + 5)/10;
        }
        else if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        {
            FltrManual = (FltrManual*7 + 5)/10;
        }
        else
        {
            FltrManual = (FltrManual*6 + 5)/10;
        }
        /*FltrGmSwitch = FltrGmSwitch * 1;*/
    }

    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x14, 0x03); /*uhf_filt_fb_adj_ldo*/

    if(FltrGmSwitch > 0x3F)
    {
        FltrGmSwitch = 0x3F;
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x12, (UINT8)FltrGmSwitch); /*uhf_fltr_gm_switch[5:0]*/

#ifdef ATBM2040_CHIP_DEBUG_OPEN
    if(DebugOpen)
    {
        if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
            ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)||(ATBM_LEOC_CHIP_ID == pTuner->ChipID))
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x29, 0x1F); /*params_agc_set_en[5:0]*/
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x16, 0x01); /*uhf_filt_manual_en*/        
    }
#endif
    if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
    {    
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x29, 0x1F); /*params_agc_set_en[5:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x16, 0x01); /*uhf_filt_manual_en*/        
    }
    
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x15, (UINT8)FltrManual); /*uhf_filt_manual[5:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0A, 0x01); /*lna_band*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x00); /*lna_ldo_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x01); /*params_freq_path*/

    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        if(((ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
            ||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)
            ||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode))
                &&(pTuner->FreqKHz <= 800000))
        {
            FltrGmSwitch |= 0x40;
        }
#if ATBM2040_CUSTOMER1_CONFIG
        else if(ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode)
        {
            FltrGmSwitch |= 0x80;
        }
#endif
        else
        {
            FltrGmSwitch &= 0xBF; /*b'1011 1111*/
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1A, (UINT8)FltrGmSwitch);
    }
    return ret;
}


/************************************************************
*Description: UHF module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvFastUHFSetting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 filt_fcal_fail = 0;
    UINT32 FltrGmSwitch = 0;
    ATBM2040UHFChIndex_t *pIndex = NULL;
    ATBM2040UHFCalResult_t *pHighIndex = NULL;
    ATBM2040UHFCalResult_t *pLowIndex = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    /* UHF filter frequency index setting*/
    pIndex = ATBM2040DrvUHFFreqIndex(pTuner->FreqKHz);

    ATBM2040DrvUHFCalResult(pTuner->FreqKHz,&pHighIndex,&pLowIndex);

    if((0x01 == pHighIndex->uhf_filt_fcal_fail)||(0x01 == pLowIndex->uhf_filt_fcal_fail))
    {
        filt_fcal_fail = 1;
    }
    else
    {
        filt_fcal_fail = 0;
    }
    
    if(0x01 == filt_fcal_fail)
    {
        FltrGmSwitch = (((UINT32)pIndex->uhf_fltr_manual + 1)*225 + 50)/100;        
        if(FltrGmSwitch > 0x3F)
        {
            FltrGmSwitch = 0x3F;
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x12, (UINT8)FltrGmSwitch); /*uhf_fltr_gm_switch[5:0]*/
        
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, pIndex->uhf_filt_freq&0xFF); /*uhf_filt_freq[7:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (pIndex->uhf_filt_freq>>8)&0x03); /*uhf_filt_freq[9:8]*/
    }  
    else
    {  
        UINT32 uhf_filt_freq = 0;
        UINT32 cap_h,cap_l,freq_h,freq_l,freq_x;
        UINT32 freq1,freq2;
        
        cap_h = pHighIndex->uhf_filt_fcal_cap_ctrl;
        cap_l = pLowIndex->uhf_filt_fcal_cap_ctrl;
        freq_h = pHighIndex->FreqMHz;
        freq_l = pLowIndex->FreqMHz;
        freq_x = (pTuner->FreqKHz+500)/1000;
        freq1 = freq_l*freq_l/10000;
        freq2 = (freq_h +freq_l) * (freq_h -freq_l)/10000;
        uhf_filt_freq = cap_h + ((cap_l-cap_h)*freq1 * (freq_h +freq_x) * (freq_h -freq_x) ) /(freq2 *freq_x*freq_x );        
 
        FltrGmSwitch = (pHighIndex->uhf_fltr_fcal_gm_gain*1000/pHighIndex->uhf_fltr_manual + \
                            pLowIndex->uhf_fltr_fcal_gm_gain*1000/pLowIndex->uhf_fltr_manual)*pIndex->uhf_fltr_manual;
        FltrGmSwitch = FltrGmSwitch/2000;
        FltrGmSwitch = (FltrGmSwitch*225 + 50)/100;
        if(FltrGmSwitch > 0x3F)
        {
            FltrGmSwitch = 0x3F;
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x12, (UINT8)FltrGmSwitch); /*uhf_fltr_gm_switch[5:0]*/
        
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, uhf_filt_freq&0xFF); /*uhf_filt_freq[7:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (uhf_filt_freq>>8)&0x03); /*uhf_filt_freq[9:8]*/
    }

    
    if(ATBM2040_RF_BAND_UHF != pTuner->BandBak)
    {
        /*Open UHF*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0A, 0x01); /*lna_band*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x01); /*params_freq_path*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x00, 0x00); /* uhf_fltr_pwdn_ldo */
                
        /*Close VHF1&VHF2*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x01); /* vhf2_fltr_pwdn_ldo */
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x2E, 0x00); /*Vhf_fltr_vcasc_en*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x1C, 0x01); /*Vhf_fltr_bias_pd*/
    }

    if(((ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
        ||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)
        ||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode))
            &&(pTuner->FreqKHz <= 800000))
    {
        FltrGmSwitch |= 0x40;
    }
#if ATBM2040_CUSTOMER1_CONFIG
    else if(ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode)
    {
        FltrGmSwitch |= 0x80;
    }
#endif
    else
    {
        FltrGmSwitch &= 0xBF; /*b'1011 1111*/
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1A, (UINT8)FltrGmSwitch);

    return ret;
}

/************************************************************
*Description: VHF1 module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvFastVHF1Setting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040VHF1ChIndex_t *pIndex = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    pIndex = ATBM2040DrvVHF1FreqIndex((pTuner->FreqKHz+500)/1000);


    if(0x01 == pTuner->vhf_fltr_cal_fail)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x29, pIndex->vhf_fltr_ref_code); /*vhf_fltr_code_ref*/
    }
    else
    {
       ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x29, (pIndex->vhf_fltr_ref_code * pTuner->vhf_fltr_ref_code_out)/0x80); /*vhf_fltr_code_ref*/
    }    

    if(ATBM2040_RF_BAND_VHF1 != pTuner->BandBak)
    {
        /*Open VHF1*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x2E, 0x01); /*Vhf_fltr_vcasc_en*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x1C, 0x00); /*Vhf_fltr_bias_pd*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0A, 0x00); /*lna_band*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x00); /*params_freq_path*/
        
        
        /*Close VHF2&UHF*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x01); /* vhf2_fltr_pwdn_ldo */
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x00, 0x01); /* uhf_fltr_pwdn_ldo */
    }
    return ret;
}

/************************************************************
*Description: VHF2 Filter calibration for one channel
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvLeoGVHF2FreqCal(ATBM2040_t *pTuner,ATBM2040VHF2CalResult_t *pCalResult)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 filt_fcal_busy = 0,filt_fcal_fail = 0;
    UINT32 CenterFreqMHz = 0;
    UINT8 i = 0;
    ATBM2040VHF2ChIndex_t *pChIndex = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    pChIndex = ATBM2040DrvVHF2FreqIndex(pTuner->FreqKHz);

    pCalResult->vhf2_fltr_gm_switch = pChIndex->vhf2_fltr_gm_switch;
    
    CenterFreqMHz = (pTuner->FreqKHz+500)/1000;
    /* VHF2 filter frequency index setting*/


    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0E, 0); /*uhf_filt_en_cal*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, (UINT8)(CenterFreqMHz&0xFF)); /*uhf_filt_freq[7:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (UINT8)((CenterFreqMHz>>8)&0x03)); /*uhf_filt_freq[9:8]*/

    /*reset VHF2 filter calibration module*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 0); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 1); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);

    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0E, 1); /*uhf_filt_en_cal*/


   /*waiting the state changed!*/
    for(i=0;i<6;i++)
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x05,0x24, &filt_fcal_busy);/*uhf_filt_fcal_busy*/
        if(0x00 == filt_fcal_busy)
        {
            break;
        }
        ATBM2040Delay(100);
    }


    ret |= ATBM2040I2CRead(pI2CAddr,0x05,0x26, (UINT8 *)&pCalResult->uhf_filt_fcal_cap_ctrl,2);/*uhf_filt_fcal_cap_ctrl*/
    ret |= ATBM2040RegRead(pI2CAddr,0x05,0x25, &pCalResult->uhf_filt_fcal_fail);/*vhf2_filt_fcal_fail*/
    if(0x00 == filt_fcal_fail)
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x05,0x28, &pCalResult->uhf_fltr_fcal_gm_gain);/*vhf2_fltr_fcal_gm_gain[5:0] */
    }
    
    return ret;
}

/************************************************************
*Description: UHF Filter calibration for one channel
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvLeoGUHFFreqCal(ATBM2040_t *pTuner,ATBM2040UHFCalResult_t *pCalResult)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0;
    UINT8 filt_fcal_busy = 0,filt_fcal_fail = 0;
    UINT32 CenterFreqMHz = 0;
    ATBM2040UHFChIndex_t *pChIndex = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    pChIndex = ATBM2040DrvUHFFreqIndex(pTuner->FreqKHz);
    pCalResult->uhf_fltr_manual = pChIndex->uhf_fltr_manual;

    CenterFreqMHz = (pTuner->FreqKHz+500)/1000;
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x01); /*lna_ldo_pd*/

    /* UHF filter frequency index setting*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, (UINT8)(CenterFreqMHz&0xFF)); /*uhf_filt_freq[7:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (UINT8)((CenterFreqMHz>>8)&0x03)); /*uhf_filt_freq[9:8]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x1C, 0x02); /*uhf_fltr_count_h[1:0]*/

    /*reset UHF filter calibration module*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 0); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0D, 1); /*uhf_filt_rst_fcal*/
    ATBM2040Delay(10);

    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0E, 1); /*uhf_filt_en_cal*/

    /*waiting the state changed!*/
    for(i=0;i<6;i++)
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x05,0x10, &filt_fcal_busy);/*uhf_filt_fcal_busy*/
        if(0x00 == filt_fcal_busy)
        {
            break;
        }
        ATBM2040Delay(100);
    }

    ret |= ATBM2040I2CRead(pI2CAddr,0x05,0x17, (UINT8 *)&pCalResult->uhf_filt_fcal_cap_ctrl,2);/*uhf_filt_fcal_cap_ctrl*/
    ret |= ATBM2040RegRead(pI2CAddr,0x05,0x11, &pCalResult->uhf_filt_fcal_fail);/*uhf_filt_fcal_fail*/
    if(0x00 == filt_fcal_fail)
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x05,0x1D, &pCalResult->uhf_fltr_fcal_gm_gain);/*uhf_fltr_fcal_gm_gain */
    }
    
    return ret;
}


/************************************************************
*Description: VHF1 Band calibration
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvLeoGV1BandCal(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 tmpReg = 0;
    UINT8 i = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    /*VHF filter registers setting*/
    ATBM2040RegListWrite(pI2CAddr,VHF1FilterReg,ATBM2040_VHF1_FILTER_REG_CNT);
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x01); /*vhf2_fltr_pwdn_ldo*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2E, 0x01); /*Vhf_fltr_cal_clk_en*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x24, 0x00); /*Vhf_fltr_cal_reset*/
    ATBM2040Delay(1000);
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x24, 0x01); /*Vhf_fltr_cal_reset*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x26, 0x01); /*Vhf_fltr_start*/

    while(i < 10)
    {
        ATBM2040Delay(10);
        ret |= ATBM2040RegRead(pI2CAddr,0x06,0x32, &tmpReg); /*vhf_fltr_cal_busy*/
        if(0x00 == tmpReg)
        {
            break;
        }
        i++;
    }

    ret |= ATBM2040RegRead(pI2CAddr,0x06,0x34, &pTuner->vhf_fltr_ref_code_out); /*vhf_fltr_ref_code_out*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2E, 0x00); /*Vhf_fltr_cal_clk_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x25, 0x00); /*Vhf_fltr_cal_sel*/

    ret |= ATBM2040RegRead(pI2CAddr,0x06,0x33, &pTuner->vhf_fltr_cal_fail); /*vhf_fltr_cal_fail*/


    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0A, 0x00); /*lna_band*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x00); /*lna_ldo_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x00); /*params_freq_path*/
    return ret;
}

/************************************************************
*Description: VHF2 Band calibration
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvLeoGV2BandCal(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0,FreqKHz = pTuner->FreqKHz;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x01, 0x01); /*lna_ldo_pd*/

    /*Setting the VHF2 filter and  Calibration*/ 
    if(0 != pTuner->LowCousumMd)
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x04};
        ATBM2040RegListWriteExt(pI2CAddr,LeoEVHF2FltCalibReg,ATBM2040_LEOE_VHF2_FILTER_REG_CNT,TmpReg);
    }
    else
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x0B};
        ATBM2040RegListWriteExt(pI2CAddr,LeoEVHF2FltCalibReg,ATBM2040_LEOE_VHF2_FILTER_REG_CNT,TmpReg);
    }
    
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x1C, 0x00); /*uhf_fltr_count_h[1:0]*/

    for(i=0;i<ATBM2040_VHF2_CAL_RES_CNT;i++)
    {
        pTuner->FreqKHz = ATBM2040VHF2CalRes[i].FreqMHz*1000;
        ret |= ATBM2040DrvLeoGVHF2FreqCal(pTuner,&ATBM2040VHF2CalRes[i]);
    }
    pTuner->FreqKHz = FreqKHz;
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x23, 0x1C); /*vhf2_filt_cal_ctrl[4:0]*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2F, 0x00); /*uhf_filt_cal_clk_en*/
    

    /*ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x14, 0x03); *//*uhf_filt_fb_adj_ldo*/
    return ret;
}

/************************************************************
*Description: UHF Band calibration
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvLeoGUBandCal(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0,FreqKHz = pTuner->FreqKHz;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    /*Setting the UHF filter and  Calibration*/     
    if(0 != pTuner->LowCousumMd)
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x04};
        ATBM2040RegListWriteExt(pI2CAddr,UHFFltCalibReg,ATBM2040_UHF_FILTER_REG_CNT,TmpReg);
    }
    else
    {
        ATBM2040Reg_t TmpReg = {0x05,0x09, 0x0C};
        ATBM2040RegListWriteExt(pI2CAddr,UHFFltCalibReg,ATBM2040_UHF_FILTER_REG_CNT,TmpReg);
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x01); /*vhf2_fltr_pwdn_ldo*/

    for(i=0;i<ATBM2040_UHF_CAL_RES_CNT;i++)
    {
        pTuner->FreqKHz = ATBM2040UHFCalRes[i].FreqMHz*1000;
        ret |= ATBM2040DrvLeoGUHFFreqCal(pTuner,&ATBM2040UHFCalRes[i]);
    }
    pTuner->FreqKHz = FreqKHz;
    ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0C, 0x1E); /*uhf_filt_cal_ctrl[5:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2F, 0x00); /*uhf_filt_cal_clk_en*/
    

    /*ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x14, 0x03);*/ /*uhf_filt_fb_adj_ldo*/
    return ret;
}

/************************************************************
*Description: VHF2 module setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvFastVHF2Setting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 filt_fcal_fail = 0;
    UINT32 FltrGmSwitch = 0;
    ATBM2040VHF2ChIndex_t *pIndex = NULL;
    ATBM2040VHF2CalResult_t *pHighIndex = NULL;
    ATBM2040VHF2CalResult_t *pLowIndex = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;


    /* UHF filter frequency index setting*/
    pIndex = ATBM2040DrvVHF2FreqIndex(pTuner->FreqKHz);

    ATBM2040DrvVHF2CalResult(pTuner->FreqKHz,&pHighIndex,&pLowIndex);

    if((0x01 == pHighIndex->uhf_filt_fcal_fail)||(0x01 == pLowIndex->uhf_filt_fcal_fail))
    {
        filt_fcal_fail = 1;
    }
    else
    {
        filt_fcal_fail = 0;
    }
    
    if(0x01 == filt_fcal_fail)
    {
        FltrGmSwitch = (((UINT32)pIndex->vhf2_fltr_gm_switch+ 1)*225 + 50)/100;        
        if(FltrGmSwitch > 0x3F)
        {
            FltrGmSwitch = 0x3F;
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x12, (UINT8)FltrGmSwitch); /*uhf_fltr_gm_switch[5:0]*/
        
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, pIndex->vhf2_filt_freq&0xFF); /*uhf_filt_freq[7:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (pIndex->vhf2_filt_freq>>8)&0x03); /*uhf_filt_freq[9:8]*/
    }  
    else
    {  
        UINT32 uhf_filt_freq = 0;
        UINT32 cap_h,cap_l,freq_h,freq_l,freq_x;
        UINT32 freq1,freq2;
        
        cap_h = pHighIndex->uhf_filt_fcal_cap_ctrl;
        cap_l = pLowIndex->uhf_filt_fcal_cap_ctrl;
        freq_h = pHighIndex->FreqMHz;
        freq_l = pLowIndex->FreqMHz;
        freq_x = (pTuner->FreqKHz+500)/1000;
        freq1 = freq_l*freq_l/1600;
        freq2 = (freq_h +freq_l) * (freq_h -freq_l)/1600;
        uhf_filt_freq = cap_h + ((cap_l-cap_h)*freq1 * (freq_h +freq_x) * (freq_h -freq_x) ) /(freq2 *freq_x*freq_x );
        
        FltrGmSwitch = (pHighIndex->uhf_fltr_fcal_gm_gain*10000/pHighIndex->vhf2_fltr_gm_switch+ pLowIndex->uhf_fltr_fcal_gm_gain*10000/pLowIndex->vhf2_fltr_gm_switch)/2 *\
            pIndex->vhf2_fltr_gm_switch;
        FltrGmSwitch = (FltrGmSwitch*150 + 50)/1000000;
        if(FltrGmSwitch > 0x3F)
        {
            FltrGmSwitch = 0x3F;
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x12, (UINT8)FltrGmSwitch); /*uhf_fltr_gm_switch[5:0]*/
        
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0A, uhf_filt_freq&0xFF); /*uhf_filt_freq[7:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x0B, (uhf_filt_freq>>8)&0x03); /*uhf_filt_freq[9:8]*/
    }

    
    if(ATBM2040_RF_BAND_VHF2 != pTuner->BandBak)
    {
        /*Open VHF2*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0A, 0x00); /*lna_band*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x39, 0x00); /*params_freq_path*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x00); /* vhf2_fltr_pwdn_ldo */
        
        
        /*Close UHF&VHF2*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x2E, 0x00); /*Vhf_fltr_vcasc_en*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x1C, 0x01); /*Vhf_fltr_bias_pd*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x00, 0x01); /* uhf_fltr_pwdn_ldo */
    }
   
    return ret;
}

/************************************************************
*Description: Analog Filter Setting
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvAnaFltSetting(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 tmpReg = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    /*VHF/UHF filter setting*/
    if(ATBM2040_VHF_CHECK(pTuner->FreqKHz))
    {
        if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
        {
            if(pTuner->FreqKHz < ATBM2040_VHF2_LOW_KHZ)
            {/*VHF1*/
                if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
                {
                    if(ATBM2040_FAST_TUNE_MODE_FAST == pTuner->Config.FastTuneMD)
                    {
                        ret |= ATBM2040DrvFastVHF1Setting(pTuner);
                    }
                    else
                    {
                        ret |= ATBM2040DrvVHF1Setting(pTuner);
                    }
                    tmpReg = 0x00;
#if ATBM2040_CUSTOMER1_CONFIG
                    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode)
                    {
                        tmpReg = 0x80;
                    }
#endif
                    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1A, tmpReg);
                }
                else
                {
                    ret |= ATBM2040DrvVHF1Setting(pTuner);
                }
            }
            else
            {/*VHF2*/
                if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
                {
                    if(ATBM2040_FAST_TUNE_MODE_FAST == pTuner->Config.FastTuneMD)
                    {
                        ret |= ATBM2040DrvFastVHF2Setting(pTuner);
                    }
                    else
                    {
                        ret |= ATBM2040DrvVHF2Setting(pTuner);
                    }
                    tmpReg = 0x00;
                    if((ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
                        ||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)
                        ||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode))
                    {
                        tmpReg = 0x40;
                    }
#if ATBM2040_CUSTOMER1_CONFIG
                    else if(ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode)
                    {
                        tmpReg = 0x80;
                    }
#endif
                    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1A, tmpReg);
                }
                else
                {
                    ret |= ATBM2040DrvVHF2Setting(pTuner);
                }
            }
        }
        else
        {
            ret |= ATBM2040DrvVHFSetting(pTuner);
        }
    }
    else
    {
        if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        {
            if(ATBM2040_FAST_TUNE_MODE_FAST == pTuner->Config.FastTuneMD)
            {
                ret |= ATBM2040DrvFastUHFSetting(pTuner);
            }
            else
            {
                ret |= ATBM2040DrvUHFSetting(pTuner);
            }
        }
        else
        {
            ret |= ATBM2040DrvUHFSetting(pTuner);
        }
    }
    return ret;
}

/************************************************************
*Description: Software reset, all registers will be reset
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvSwReset(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 tmpReg = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    /*Reset All*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0F, 0x00); /*soft_rst_cfg[4:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x04, 0x02);    /*[0] I2c_clk_sel    [1] i2c_sys_clk_lck_enb*/
    /*Switch I2C clock to OSC clock*/
    ret |= ATBM2040RegRead(pI2CAddr,0x00,0x04, &tmpReg); /*[0] I2c_clk_sel    [1] i2c_sys_clk_lck_enb*/
    if(0x02 != tmpReg)
    {
        ATBM2040Delay(500);
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x04, 0x02);    /*[0] I2c_clk_sel     [1] i2c_sys_clk_lck_enb*/
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0C, 0x01); /*soft_rst_all*/
    ATBM2040Delay(500);
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0C, 0x00); /*soft_rst_all*/

    ret |= ATBM2040RegRead(pI2CAddr,0x00,0x00, &pTuner->ChipID);
    if(ATBM_LEOC_CHIP_ID == pTuner->ChipID)
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x10,0x15, &tmpReg);
        if(0xFF != tmpReg)
        {
            pTuner->ChipID = ATBM_LEOD_CHIP_ID;
            ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x00, ATBM_LEOD_CHIP_ID);
        }
    }
#ifdef ATBM2040_CHIP_DEBUG_OPEN
    if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)&&(0xFF != pTuner->ForceChipID))
    {
        pTuner->ChipID = pTuner->ForceChipID;
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x00, pTuner->ForceChipID);
    }
    ATBM2040ChipID = pTuner->ChipID;
#endif
#if ATBM2040_DEBUG_PRINT
    ATBM2040Print(("[ATBM2040] ChipID:0x%02X\n",pTuner->ChipID));
#endif
    return ret;
}

/************************************************************
*Description: BB power target setting
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvAgcPowerTargetSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0;
    SINT32 *pData = NULL;
    ATBM2040AgcPowerTarget_t *pTarget = AgcPowerTargetDTMB;
    UINT32 FreqMHz = (pTuner->FreqKHz+500)/1000;
    UINT32 Cnt = ATBM2040_ARRAY_NUM(AgcPowerTargetDTMB);
    UINT8 Data[64] = {0};
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

#ifdef ATBM2040_CHIP_DEBUG_OPEN
{ 
    if(0 == ATBM2040DrvChipDebugPowerTargetSet(pTuner,AgcPowerTargetReg,ATBM2040_AGC_POW_TARGET_REG_CNT))
    {
        return ATBM2040_NO_ERROR;
    }
}
#endif

    switch(pTuner->SignalMode)
    {
        case ATBM2040_SIGNAL_MODE_ATSC:
            pTarget = LeoGAgcPowerTargetATSC;
            Cnt = ATBM2040_ARRAY_NUM(LeoGAgcPowerTargetATSC);
            break;
        case ATBM2040_SIGNAL_MODE_DTMB:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                pTarget = LeoGAgcPowerTargetDTMB;
                Cnt = ATBM2040_ARRAY_NUM(LeoGAgcPowerTargetDTMB);
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                pTarget = LeoEAgcPowerTargetDTMB;
                Cnt = ATBM2040_ARRAY_NUM(LeoEAgcPowerTargetDTMB);
            }
            else if((ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
            {
                pTarget = LeoCAgcPowerTargetDTMB;
                Cnt = ATBM2040_ARRAY_NUM(LeoCAgcPowerTargetDTMB);
            }
            else
            {
                pTarget = AgcPowerTargetDTMB;
                Cnt = ATBM2040_ARRAY_NUM(AgcPowerTargetDTMB);
            }
            break;
        case ATBM2040_SIGNAL_MODE_DVBT:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                pTarget = LeoGAgcPowerTargetDVBT;
                Cnt = ATBM2040_ARRAY_NUM(LeoGAgcPowerTargetDVBT);
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                pTarget = LeoEAgcPowerTargetDVBT;
                Cnt = ATBM2040_ARRAY_NUM(LeoEAgcPowerTargetDVBT);
            }
            else if((ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
            {
                pTarget = LeoCAgcPowerTargetDVBT;
                Cnt = ATBM2040_ARRAY_NUM(LeoCAgcPowerTargetDVBT);
            }
            else
            {
                pTarget = AgcPowerTargetDVBT;
                Cnt = ATBM2040_ARRAY_NUM(AgcPowerTargetDVBT);
            }
            break;
        case ATBM2040_SIGNAL_MODE_DVBC:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                pTarget = LeoGAgcPowerTargetDVBC;
                Cnt = ATBM2040_ARRAY_NUM(LeoGAgcPowerTargetDVBC);
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                pTarget = LeoEAgcPowerTargetDVBC;
                Cnt = ATBM2040_ARRAY_NUM(LeoEAgcPowerTargetDVBC);
            }
            else
            {
                pTarget = AgcPowerTargetDVBC;
                Cnt = ATBM2040_ARRAY_NUM(AgcPowerTargetDVBC);
            }
            break;
        case ATBM2040_SIGNAL_MODE_ATV:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                pTarget = LeoGAgcPowerTargetATV;
                Cnt = ATBM2040_ARRAY_NUM(LeoGAgcPowerTargetATV);
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                pTarget = LeoEAgcPowerTargetATV;
                Cnt = ATBM2040_ARRAY_NUM(LeoEAgcPowerTargetATV);
            }
            else if((ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
            {
                pTarget = LeoCAgcPowerTargetATV;
                Cnt = ATBM2040_ARRAY_NUM(LeoCAgcPowerTargetATV);
            }
            else
            {
                pTarget = AgcPowerTargetATV;
                Cnt = ATBM2040_ARRAY_NUM(AgcPowerTargetATV);
            }
            break;
        default:
            break;
    }
    for(i=0;i<Cnt;i++)
    {
        if((FreqMHz > pTarget->StartFreqMHz)
            &&(FreqMHz <= pTarget->EndFreqMHz))
        {
            break;
        }
        pTarget++;
    }
    /*Check frequency band*/
    if((pTuner->SignalMdBak == pTuner->SignalMode)
        &&((NULL != pTuner->pTargetBak)&&(pTuner->pTargetBak->StartFreqMHz == pTarget->StartFreqMHz)&&(pTuner->pTargetBak->EndFreqMHz == pTarget->EndFreqMHz)))
    {
        return ret;
    }
    pTuner->pTargetBak = pTarget;
    
    pData = pTarget->RegVal;
    for(i=0;i<5;i++)
    {
        Data[i] = (UINT8)pData[i];
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x58, Data,5);

    for(i=0;i<5;i++)
    {
        Data[i] = (UINT8)pData[i+5];
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0xF1, Data,5);

    for(i=0;i<10;i+=2)
    {
        Data[i] = (UINT8)pData[i+11];
        Data[i+1] = (UINT8)pData[i+10];
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x18, Data,10);    
    
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        for(i=0;i<5;i++)
        {
            Data[i] = (UINT8)pData[20+i];
        }
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x23,0x48, Data,5);
    }

    return ret;
}

static ATBM2040_ERROR_e ATBM2040DrvDagcAmpRefSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0;
    ATBM2040Reg_t *pReg = NULL;
    UINT8 *pData = NULL;
    DagcAmpRef_t *pDagcAmpRef = &DagcAmpRefDTMB;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    switch(pTuner->Config.Mode)
    {
        case ATBM2040_SIGNAL_MODE_DTMB:
        case ATBM2040_SIGNAL_MODE_ATSC:
            pDagcAmpRef = &DagcAmpRefDTMB;
            break;
        case ATBM2040_SIGNAL_MODE_DVBT:
            pDagcAmpRef = &DagcAmpRefDVBT;
            break;
        case ATBM2040_SIGNAL_MODE_DVBC:
            pDagcAmpRef = &DagcAmpRefDVBC;
            break;
        case ATBM2040_SIGNAL_MODE_ATV:
            pDagcAmpRef = &DagcAmpRefAnalog;
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                pDagcAmpRef->Dagc2AmpRef0Low = 0x70;
            }
            else
            {
                pDagcAmpRef->Dagc2AmpRef0Low = 0x80;
            }
            break;
        default:
            break;
    }

    pReg = DagcAmpRefReg;
    pData = (UINT8 *)pDagcAmpRef;
    for(i=0;i<ATBM2040_DAGC_AMP_REF_REG_CNT;i++)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,pReg[i].BaseReg,pReg[i].OffReg,pData[i]);
    }

#if ATBM2040_CUSTOMER1_CONFIG
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
        {
            /* 0x14,0x76, 0x40, params_thr_papr_judge_0 */
            /* 0x14,0x77, 0x32, params_thr_papr_judge_1 */
            /* 0x14,0x78, 0x28, params_thr_papr_judge_2 */
            /* 0x14,0x79, 0x20, params_thr_papr_judge_3 */
            /* 0x14,0x7A, 0x19, params_thr_papr_judge_4 */
            /* 0x14,0x7B, 0x14, params_thr_papr_judge_5 */
            /* 0x14,0x7C, 0x10, params_thr_papr_judge_6 */
            /* 0x14,0x7D, 0x0D, params_thr_papr_judge_7 */
            /* 0x14,0x7E, 0x0A, params_thr_papr_judge_8 */
            /* 0x14,0x7F, 0x08, params_thr_papr_judge_9 */
            UINT8 Data[10] = {0x40,0x32,0x28,0x20,0x19,0x14,0x10,0x0D,0x0A,0x08};
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x76, Data,10);
        }
    }
#endif
    return ret;
}

static ATBM2040_ERROR_e ATBM2040DrvVGAGainThrSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040RegGroup_t *pRegGroup = VGAGainThrDTMBReg;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    
    switch(pTuner->Config.Mode)
    {
        case ATBM2040_SIGNAL_MODE_DTMB:
        case ATBM2040_SIGNAL_MODE_ATSC:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                pRegGroup = VGAGainThrDVBTReg;
            }
            else
            {
                pRegGroup = VGAGainThrDTMBReg;
            }
            break;
        case ATBM2040_SIGNAL_MODE_DVBT:
            pRegGroup = VGAGainThrDVBTReg;
            break;
        case ATBM2040_SIGNAL_MODE_DVBC:
            pRegGroup = VGAGainThrDVBCReg;
            break;
        case ATBM2040_SIGNAL_MODE_ATV:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                pRegGroup = LeoGVGAGainThrATVReg;
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                pRegGroup = LeoEVGAGainThrATVReg;
            }
            else
            {
                pRegGroup = VGAGainThrATVReg;
            }
            break;
        default:
            break;
    }
    while(0 != pRegGroup->Len)
    {
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
        pRegGroup++;
    }

    return ret;
}


/************************************************************
*Description: from  IF level to dac_fltr_gain_ctrl(1003H)
*************************************************************/
static UINT8 ATBM2040DrvDACGainCode(ATBM2040_t *pTuner,ATBM2040_IF_OUT_LEVEL_e IFLevel)
{
    UINT8 GainCode = 0x05;
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        switch(IFLevel)
        {
            case ATBM2040_IF_OUT_LEVEL1:
                GainCode = 0x00 ; /*850 mV */
                break;
            case ATBM2040_IF_OUT_LEVEL2:
                GainCode = 0x01 ; /*1150mV*/
                break;
            case ATBM2040_IF_OUT_LEVEL3:
                GainCode = 0x02 ; /*1650mV*/
                break;
            case ATBM2040_IF_OUT_LEVEL4:
                GainCode = 0x03 ; /*1650mV*/
                break;
            default:
                GainCode = 0x00;
                break;
        }
    }
    else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
            ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
    {
        switch(IFLevel)
        {
            case ATBM2040_IF_OUT_LEVEL1:
                GainCode = 0x00 ; /*850 mV */
                break;
            case ATBM2040_IF_OUT_LEVEL2:
                GainCode = 0x02 ; /*1200mV*/
                break;
            case ATBM2040_IF_OUT_LEVEL3:
            case ATBM2040_IF_OUT_LEVEL4:
                GainCode = 0x03 ; /*1600mV*/
                break;
            default:
                GainCode = 0x00;
                break;
        }
    }
    else
    {
        switch(IFLevel)
        {
            case ATBM2040_IF_OUT_LEVEL1:
                GainCode = 0x00 + (UINT8)((pTuner->IFLevelSpinner>0x02)?(0x02):(pTuner->IFLevelSpinner));
                break;
            case ATBM2040_IF_OUT_LEVEL2:
                GainCode = 0x03 + (UINT8)((pTuner->IFLevelSpinner>0x03)?(0x03):(pTuner->IFLevelSpinner));
                break;
            case ATBM2040_IF_OUT_LEVEL3:
            case ATBM2040_IF_OUT_LEVEL4:
                GainCode = 0x07;
                break;
            default:
                GainCode = 0x04;
                break;
        }
    }
    return GainCode;
}

/************************************************************
*Description: set pin config
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvGPOStateSet(ATBM2040_t *pTuner,ATBM2040PinCfg_t *pPinCfg,UINT32 PinNum)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    for(i=0;i<PinNum;i++)
    {
        if((ATBM2040_PIN_NAME_GPO1 == pPinCfg->PinName)&&(pTuner->Config.FEFMode != ATBM2040_FEF_EXTERNAL_GPO1))
        {
            ret = ATBM2040RegWrite(pI2CAddr,0x03,0x00, (ATBM2040_GPO_STATE_LOW==pPinCfg->PinState)?(0x01):(0x03)); /*gpo1_oe,gpo1_dat*/
        }
        else if((ATBM2040_PIN_NAME_GPO2 == pPinCfg->PinName)&&(pTuner->Config.FEFMode != ATBM2040_FEF_EXTERNAL_GPO2))
        {
            ret = ATBM2040RegWrite(pI2CAddr,0x03,0x01, (ATBM2040_GPO_STATE_LOW==pPinCfg->PinState)?(0x01):(0x03)); /*gpo2_oe,gpo2_dat*/
        }
        pPinCfg++;
    }

    return ret;
}

/************************************************************
*Description: set IF data output path
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvIFOutPath(ATBM2040_t *pTuner,ATBM2040_IF_PATH_e IFPath)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    switch(IFPath)
    {
        case ATBM2040_IF_PATH_1:
            ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x08, 0x00); /*params_analog_t_hlo*/
            ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x3F, 0x01); /*params_dagc_set_0*/
            break;
        case ATBM2040_IF_PATH_2:
            ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x08, 0x01); /*params_analog_t_hlo*/
            ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x3F, 0x00); /*params_dagc_set_0*/
            break;
        default:
            break;
    }
    return ret;
}
/************************************************************
*Description: set clock out config
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvClkOutControl(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    if(ATBM2040_CLK_OUT_ENABLE == pTuner->Config.ClkOut.ClkOutEnable)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x09, 0x00); /*osc_pd_out*/
        if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID))
        {
            switch(pTuner->Config.ClkOut.ClkOutAmp)
            {
                case ATBM2040_CLK_OUT_AMP_L1:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x0F, 0x10); /*osc_clk_out_res_a*/
                    break;
                case ATBM2040_CLK_OUT_AMP_L2:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x0F, 0x08); /*osc_clk_out_res_a*/
                    break;
                case ATBM2040_CLK_OUT_AMP_L3:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x0F, 0x04); /*osc_clk_out_res_a*/
                    break;
                case ATBM2040_CLK_OUT_AMP_L4:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x0F, 0x02); /*osc_clk_out_res_a*/
                    break;
                case ATBM2040_CLK_OUT_AMP_L5:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x0F, 0x01); /*osc_clk_out_res_a*/
                    break;
                default:
                    break;
            }
        }
        else
        {
            switch(pTuner->Config.ClkOut.ClkOutAmp)
            {
                case ATBM2040_CLK_OUT_AMP_L1:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x10, 0x01); /*osc_clk_out_res_b*/
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x06); /*osc_core_current*/
                    break;
                case ATBM2040_CLK_OUT_AMP_L2:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x10, 0x01); /*osc_clk_out_res_b*/
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x06); /*osc_core_current*/
                    break;
                case ATBM2040_CLK_OUT_AMP_L3:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x10, 0x01); /*osc_clk_out_res_b*/
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x06); /*osc_core_current*/
                    break;
                case ATBM2040_CLK_OUT_AMP_L4:
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x10, 0x01); /*osc_clk_out_res_b*/
                    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x06); /*osc_core_current*/
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x09, 0x01); /*osc_pd_out*/
        if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID))
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x0F, 0x01); /*osc_clk_out_res_a*/
        }
        else
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x10, 0x01); /*osc_clk_out_res_b*/
            ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x12, 0x02); /*osc_core_current*/
        }
    }

    return ret;
}
static ATBM2040_ERROR_e ATBM2040DrvMixerReset(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040HalfAddrRegGroup_t TmpReg;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    if(pTuner->FreqKHz <= ATBM2040_MIXER_MD_DIVISION_KHZ)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x29, 0x01); /*mixr_pd_8x(RFin>333MHz 1:4x;RFin<=333MHz,0:8x) */
        ATBM2040Delay(3000);
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x29, 0x00); /*mixr_pd_8x(RFin>333MHz 1:4x;RFin<=333MHz,0:8x) */
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x29, 0x00); /*mixr_pd_8x(RFin>333MHz 1:4x;RFin<=333MHz,0:8x) */
        ATBM2040Delay(3000);
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x29, 0x01); /*mixr_pd_8x(RFin>333MHz 1:4x;RFin<=333MHz,0:8x) */
    }
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        UINT8 mixr_vhf_pd = 0,mixr_vhf2_pd = 0,mixr_uhf_pd = 0;
        if(pTuner->BandBak != pTuner->Band)
        {
            if(pTuner->FreqKHz < ATBM2040_VHF2_LOW_KHZ)
            {/*VHF1*/
                mixr_vhf_pd = 0x00;
                mixr_vhf2_pd = 0x01;
                mixr_uhf_pd = 0x01;
            }
            else if(pTuner->FreqKHz <= ATBM2040_UHF_LOW_KHZ)
            {/*VHF2*/
                mixr_vhf_pd = 0x01;
                mixr_vhf2_pd = 0x00;
                mixr_uhf_pd = 0x01;
            }
            else
            {/*UHF*/
                mixr_vhf_pd = 0x01;
                mixr_vhf2_pd = 0x01;
                mixr_uhf_pd = 0x00;
            }
            TmpReg.BaseAddr = 0x12;
            TmpReg.Len = 6;
            TmpReg.Data[0] = 0x41; /*0x12,0x41, mixr_vhf_pd */
            TmpReg.Data[1] = mixr_vhf_pd;        
            TmpReg.Data[2] = 0x46; /*0x12,0x46, mixr_uhf_pd */
            TmpReg.Data[3] = mixr_uhf_pd;
            TmpReg.Data[4] = 0x47; /*0x12,0x47, mixr_vhf2_pd */
            TmpReg.Data[5] = mixr_vhf2_pd;
            ret |= ATBM2040DrvRegHalfAddrBurstWrite(pTuner,TmpReg.BaseAddr,TmpReg.Data,TmpReg.Len);
        }
        
    }
    if(pTuner->FreqKHz <= ATBM2040_MIXER_MD_DIVISION_KHZ)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x22, 0x02);
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x22, 0x03);
    }
    
    return ret;
}

static ATBM2040_ERROR_e ATBM2040DrvBWSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 BandWidth = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    UINT8 Reg146C = 0;
    UINT8 Data[3];

    if(pTuner->BWKHzBak == pTuner->BWKHz)
    {
        return ret;
    }
    /*BandWidth*/
    Reg146C = 0x02;
    BandWidth = (8000000 + 128)/256;
    if(pTuner->BWKHz <= 6000)
    {
        Reg146C = 0x00;
        BandWidth = (6000000 + 128)/256;
        Data[0] = 0x45;
        Data[1] = 0x3C;
        Data[2] = 0x00;
    }
    else if(pTuner->BWKHz <= 7000)
    {
        Reg146C = 0x01;
        BandWidth = (7000000 + 128)/256;
        Data[0] = 0xE7;
        Data[1] = 0x43;
        Data[2] = 0x00;
    }
    else if(pTuner->BWKHz <= 8000)
    {
        Reg146C = 0x02;
        BandWidth = (8000000 + 128)/256;
        Data[0] = 0x4B;
        Data[1] = 0x4C;
        Data[2] = 0x00;
    }
    
    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
    {
        /*0x1A,0x21, sweep_freq_start_sfo */
        /*0x1A,0x22, params_sweep_freq_start_sfo[15:8] */
        /*0x1A,0x23, params_sweep_freq_start_sfo[16]*/
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x1A,0x21, Data,3);
        ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x29, Reg146C); /*BW_MODE*/
    }
    
    if((ATBM_LEOB_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x6C, Reg146C); /*params_sig_bw_mode [1:0]*/
    }
    
    Data[0] = BandWidth&0xFF; /* 0x14,0x6D params_signal_filter_bandwidth[7:0]*/
    Data[1] = (BandWidth>>8)&0xFF; /* 0x14,0x6E params_signal_filter_bandwidth[15:8]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x6D, Data,2);

    return ret;
}

/************************************************************
*Description: Find Intercept according to center frequency
*************************************************************/
UINT16 ATBM2040DrvRSSIInterceptGet(ATBM2040_t *pTuner)
{
    UINT32 i = 0;
    UINT32 FreqMHz = 0;
    UINT32 FreqMHzTmp = 0xFFFFFFFF;
    UINT32 FreqMHzMin = 0xFFFFFFFF;
    ATBM2040RSSIIntercept_t *pIntercept_t = RSSIIntercept;

    FreqMHz = (pTuner->FreqKHz + 500)/1000;
    for(i=0;i<ATBM2040_RSSI_INTERCEPT_CNT;i++)
    {
        FreqMHzTmp = ATBM2040ABS((SINT32)FreqMHz-(SINT32)RSSIIntercept[i].FreqMHz);
         if(FreqMHzTmp < FreqMHzMin)
         {
             FreqMHzMin = FreqMHzTmp;
            pIntercept_t = &RSSIIntercept[i];
         }
    }


    return pIntercept_t->Intercept;
}

/************************************************************
*Description: set DWA
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvADCDwaSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    UINT32 i = 0;
    UINT8 agcState = 0, LoFinish = 0;
    for(i=0;i<400;i++)
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xAC,&LoFinish);
        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xAA,&agcState);
        if((0x01 == LoFinish)&&(0x02 == agcState))
        {
            break;
        }
        ATBM2040Delay(1000);
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x0A, 0x00);  /*adc_dwa_disable*/
    return ret;
}

/*Description: Setting the IF frequency calibration registers */
ATBM2040_ERROR_e ATBM2040DrvIFFilterSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 SignalIFFreq = 0;
    UINT8 tmpReg = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {    
        if(pTuner->MixerIFBak != pTuner->MixerIF)
        {
            UINT8 Data[4] = {0};
            /*Setting IF frequency*/
            SignalIFFreq = pTuner->MixerIF>>8;/* MixerIF/256 */
            Data[0] = (0-SignalIFFreq)&0xFF; /*0x16,0x0C, params_desired_signal_if_freq_h[7:0]*/
            Data[1] = ((0-SignalIFFreq)>>8)&0xFF; /*0x16,0x0D, params_desired_signal_if_freq_h[15:8]*/
            Data[2] = SignalIFFreq&0xFF; /*0x16,0x0E, params_desired_signal_if_freq_l[7:0]*/
            Data[3] = (SignalIFFreq>>8)&0xFF; /*0x16,0x0F, params_desired_signal_if_freq_l[15:8]*/
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x0C, Data,4);
        }
    }
#if 0
    if((pTuner->MixerIFBak == pTuner->MixerIF)&&(pTuner->BWKHzBak == pTuner->BWKHz))
    {
        return ret;
    }
#endif
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        &&((ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
            ||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)
            ||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode))
        &&(!ATBM2040_VHF_CHECK(pTuner->FreqKHz)))
    {
        tmpReg = 0x70;
    }
    else if(((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
        &&((ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)))
    {
        tmpReg = 0x70;
    }
    else if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)&&(ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode))
    {
        if((pTuner->MixerIF/500 + pTuner->BWKHz) <= 16000)
        {
            tmpReg = 0x72;
        }
        else if((pTuner->MixerIF/500 + pTuner->BWKHz) <= 18000)
        {
            tmpReg = 0x71;
        }
        else
        {
            tmpReg = 0x70;
        }
    }
    else
    {
        if((pTuner->MixerIF/1000 + pTuner->BWKHz/2) <= 8000)
        {
            tmpReg = 0x72;
        }
        else if((pTuner->MixerIF/1000 + pTuner->BWKHz/2) <= 9000)
        {
            tmpReg = 0x72; /*mingqing , from 0x71 to 0x72*/
        }
        else if((pTuner->MixerIF/1000 + pTuner->BWKHz/2) <= 10000)
        {
            tmpReg = 0x70;
        }
        else
        {
            tmpReg = 0x70;
        }
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x05, 0x00); /*if_fltr_ctrl_sel*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x04, 0x00); /*if_fltr_cali_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x14, tmpReg); /*if_filt_bw_ctrl[6:0]*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2D, 0x01); /*if_filtr_cal_clk_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x07, 0x01); /*if_fltr_cali_disable, FILTER_CALI_DISABLE_3d3*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x07, 0x00); /*if_fltr_cali_disable*/
    ret |= ATBM2040RegRead(pI2CAddr,0x12,0x16, &tmpReg);
    tmpReg |= 0x40; /*bit6: set 1*/
    tmpReg &= 0x7F; /*bit7: set 0*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x16, tmpReg);  /*SAMPLE_DELAY<1:0>*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x04, 0x01); /*if_fltr_cali_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x1C, 0x00); /*if_fltr_cap_dctrl[5:0], FILTER_CAP_CTRL_L*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2D, 0x00); /*if_filtr_cal_clk_en*/

    return ret;
}

/************************************************************
*Description: Config FEF and LTE
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvFEFSourceAndLTESet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    if(ATBM2040_SIGNAL_MODE_DVBT == pTuner->Config.Mode)
    {
        UINT8 Data[8] = {0};
        ret |= ATBM2040RegWrite(pI2CAddr,0x19,0xC2, 0x01); /*params_use_lte_operation  */
        ret |= ATBM2040RegWrite(pI2CAddr,0x19,0xBC, 0x69); /*params_rssi_lna_out_aci_status_2_lte_nplus1  */
        Data[0] = 0x03; /*0x13,0x03, params_dagc_k[2:0] */ 
        Data[1] = 0x04; /*0x13,0x04, params_dagc_alpha_0[2:0] */   
        Data[2] = 0x02; /*0x13,0x05, params_dagc_window_len_reg_0[1:0] */                         
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x13,0x03, Data,3);
        Data[0] = 0x04; /*0x15,0x42, params_dagc_alpha_1[2:0] */ 
        Data[1] = 0x02; /*0x15,0x43, params_dagc_window_len_reg_1[1:0] */   
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x15,0x42, Data,2);
        Data[0] = 0x03; /*0x15,0x56, params_dagc1_k[2:0] */ 
        Data[1] = 0x04; /*0x15,0x57, params_dagc1_alpha_0[2:0] */   
        Data[2] = 0x02; /*0x15,0x58, params_dagc1_window_len_reg_0[1:0] */                         
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x15,0x56, Data,3);
        Data[0] = 0x40; /*0x15,0x5D, params_dagc1_amp_ref_1[7:0] */ 
        Data[1] = 0x04; /*0x15,0x5E, params_dagc1_amp_ref_1[10:8] */   
        Data[2] = 0x04; /*0x15,0x5F, params_dagc1_alpha_1[2:0] */                         
        Data[3] = 0x02; /*0x15,0x60, params_dagc1_window_len_reg_1[1:0] */                         
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x15,0x5D, Data,4);
        
        switch(pTuner->Config.FEFMode)
        {
            case ATBM2040_FEF_INTERNAL:
                ATBM2040RegListWrite(pI2CAddr,FEFInternalReg,ATBM2040_FEF_INTERNAL_REG_CNT);                
                Data[0] = 0xA0; /*0x16,0x12,  params_fef_detect_length[7:0] */ 
                Data[1] = 0x0F; /*0x16,0x13,  params_fef_detect_length[15:8] */   
                Data[2] = 0x01; /*0x16,0x14,  params_fef_freeze */                         
                Data[3] = 0x4B; /*0x16,0x15,  params_fef_max_length_samples[7:0] */
                Data[4] = 0x8C; /*0x16,0x16,  params_fef_max_length_samples[15:8] */ 
                Data[5] = 0x00; /*0x16,0x17,  params_fef_sum_len[7:0] */               
                Data[6] = 0x04; /*0x16,0x18,  params_fef_sum_len[15:8] */       
                Data[7] = 0x00; /*0x16,0x19,  params_fef_use_mode[2:0] */
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x12, Data,8);
                break;
            case ATBM2040_FEF_EXTERNAL_GPO1:
                ret = ATBM2040RegWrite(pI2CAddr,0x03,0x03, 0x01); /*fef_sel: 0--no FEF input; 1--GPO1; 2--GPO2*/
                ret = ATBM2040RegWrite(pI2CAddr,0x03,0x00, 0x00); /*gpo1_oe*/
                ret = ATBM2040RegWrite(pI2CAddr,0x16,0x00, 0x01); /*params_add_fef_detect*/
                ret = ATBM2040RegWrite(pI2CAddr,0x16,0x19, 0x02); /*params_fef_use_mode: 0--internal; 1--internal and external; 2--external GPO*/
                break;
            case ATBM2040_FEF_EXTERNAL_GPO2:
                ret = ATBM2040RegWrite(pI2CAddr,0x03,0x03, 0x02); /*fef_sel: 0--no FEF input; 1--GPO1; 2--GPO2*/
                ret = ATBM2040RegWrite(pI2CAddr,0x03,0x01, 0x00); /*gpo2_oe*/
                ret = ATBM2040RegWrite(pI2CAddr,0x16,0x00, 0x01); /*params_add_fef_detect*/
                ret = ATBM2040RegWrite(pI2CAddr,0x16,0x19, 0x02); /*params_fef_use_mode: 0--internal; 1--internal and external; 2--external GPO*/
                break;
            case ATBM2040_FEF_IGNORE:
                ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x00, 0x00); /*params_add_fef_detect */
                break;
            default:
                break;
        }
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x19,0xC2, 0x00); /*params_use_lte_operation  */
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x00, 0x00); /*params_add_fef_detect */
    }
    return ret;
}

/************************************************************
*Description: Stop DSP
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvStopDSP(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040HalfAddrRegGroup_t *pRegGroup = &ATBM2040DspStopReg;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

#ifdef ATBM2040_CHIP_DEBUG_OPEN
    ret |= ATBM2040DrvFirmwareDisable(pTuner);
#else
#if ATBM2040_FIRMWARE_LOAD
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x20,0x1F, 0x00);
    }
#endif
#endif

    if(ATBM2040_FAST_TUNE_MODE_NORMAL == pTuner->Config.FastTuneMD)
    {
        ret |= ATBM2040DrvRegHalfAddrBurstWrite(pTuner,pRegGroup->BaseAddr,pRegGroup->Data,pRegGroup->Len);
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x04, 0x02);
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x41, 0x01); /* params_freeze_agc */
    }

#if 0 /* ATBM2040_FIRMWARE_LOAD */
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        UINT8 tmpReg = 0;
        tmpReg = (ATBM2040_FAST_TUNE_MODE_FAST == pTuner->Config.FastTuneMD)?(0x02):(0x00);
        ret |= ATBM2040RegWrite(pI2CAddr,0x17,0x74, tmpReg);    
    }
#endif
    return ret;
}

/************************************************************
*Description: Start DSP
*************************************************************/
static ATBM2040_ERROR_e ATBM2040DrvStartDSP(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    if(ATBM2040_FAST_TUNE_MODE_FAST == pTuner->Config.FastTuneMD)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x41, 0x00); /* params_freeze_agc */
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0D, 0x00);
    }

#ifdef ATBM2040_CHIP_DEBUG_OPEN
    ret |= ATBM2040DrvChipDebugSwConfigDone(pTuner);
#else
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x07, 0x01); /*soft_rst_dsp*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0B, 0x01); /*soft_rst_lo*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0D, 0x07); /*sw_cfg_done*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x04, 0x03); /*[0] I2c_clk_sel  [1] i2c_sys_clk_lck_enb*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x07, 0x00); /*soft_rst_dsp*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0B, 0x00); /*soft_rst_lo*/
#if ATBM2040_FIRMWARE_LOAD
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x20,0x1F, 0x01);
    }
#endif
    if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040DrvADCDwaSet(pTuner);
    }
    /*ret |= ATBM2040DrvRSSICalibration(pTuner);*/
    ATBM2040Delay(10000);
#endif
    return ret;
}

/************************************************************
*Description: Hardware init setting with configs
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvInit(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 tmpReg = 0x47;
    UINT8 Data[16] = {0};
    ATBM2040RegGroup_t *pRegGroup = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    /*Init internal debug parameters*/
    pTuner->Inited = FALSE;
    pTuner->MixerIF = 5000000;
    pTuner->HighMD = FALSE;
    pTuner->ADCIQSwap = TRUE;
    pTuner->PllDivMode = 0x01;/*pll_mod_mmd, 0:div/2; 1:div/1*/
    pTuner->DSPClkSel = 0;
    pTuner->BWKHzBak = 0;
    pTuner->MixerIFBak= 0;
    pTuner->Band = ATBM2040_RF_BAND_MAX;
    pTuner->BandBak = ATBM2040_RF_BAND_MAX;
    pTuner->SignalMode = pTuner->Config.Mode;    
    pTuner->SarAdcClk = ATBM2040_SAR_ADC_CLK_6MHZ;
    pTuner->LowCousumMd = 0;
    pTuner->SignalMdBak = ATBM2040_SIGNAL_MODE_MAX;
    pTuner->pTargetBak = NULL;
#ifdef ATBM2040_CHIP_DEBUG_OPEN
    ret |= ATBM2040DrvChipDebugOption(pTuner);
#endif

    /*Soft reset*/
    ret |= ATBM2040DrvSwReset(pTuner);
#if ATBM2040_FIRMWARE_LOAD
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        ATBM2040Firmware_t *pFwm = NULL;
        pFwm = &ATBM2040GFirmware;
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pFwm->BaseReg,pFwm->OffReg,pFwm->Data,pFwm->Len);
    }
    else if(ATBM_LEOB_CHIP_ID == pTuner->ChipID)
    {
        ATBM2040Firmware_t *pFwm = NULL;
        pFwm = &ATBM2040Firmware;
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pFwm->BaseReg,pFwm->OffReg,pFwm->Data,pFwm->Len);
    }
#endif
    if(ATBM2040_SIGNAL_MODE_ISDBT == pTuner->Config.Mode)
    {
        pTuner->SignalMode = pTuner->Config.Mode = ATBM2040_SIGNAL_MODE_DTMB;
    }
    /*Clock mode setting*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)&&(ATBM2040_CLK_MODE_EXT == pTuner->Config.ClkMode))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x08, 0x01); /* osc_pd_core */
        Data[0] = 0x00; /* 0x0E,0x11, osc_core_cap */
        Data[1] = 0x0F; /* 0x0E,0x12, osc_core_current */
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x0E,0x11, Data,2);
    }
    /* ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x0E, 0x00);*/ /*self_rst_cfg[3:0]*/
    Data[0] = 0x00; /*0x00,0x12, params_long_afc_rst*/
    Data[1] = 0x08; /*0x00,0x13, enable pll wdog*/
    Data[2] = 0x1E; /*0x00,0x14, only reset dsp*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x00,0x12, Data,3);
    
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x19, 0x00); /*close watch dog*/

    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x16, pTuner->DSPClkSel); /*osc_dsp_clk_sel*/

    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x10,0x14, 0x00); /*dac_sequence_sel*/
        if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x22,0x00, 0x67); /*params_use_leod*/

            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->Config.Mode)
                {
                    ret |= ATBM2040RegWrite(pI2CAddr,0x23,0xBE, 0x01); /*params_use_leoe*/
                }
                else
                {
                    ret |= ATBM2040RegWrite(pI2CAddr,0x23,0xBE, 0x05); /*params_use_leoe*/
                }
                ret |= ATBM2040RegWrite(pI2CAddr,0x20,0x63, 0x00); /*params_uhf_filter_on_nplusm*/
            }
            else
            {
                if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
                {
                    ret |= ATBM2040RegWrite(pI2CAddr,0x20,0x63, 0x00); /*params_uhf_filter_on_nplusm*/
                    ret |= ATBM2040RegWrite(pI2CAddr,0x23,0xBE, 0x05); /*params_use_leoe*/
                }
                else
                {
                    ret |= ATBM2040RegWrite(pI2CAddr,0x20,0x63, 0x01); /*params_uhf_filter_on_nplusm*/
                    ret |= ATBM2040RegWrite(pI2CAddr,0x23,0xBE, 0x07); /*params_use_leoe*/
                }
            }

            Data[0] = 0x00; /*0x19,0xDC, params_add_n_plus_minus_m_db_offset*/
            Data[1] = 0x00; /*0x19,0xDD, params_n_plus_minus_m_db_offset[6:0]*/            
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x19,0xDC, Data,2);

        }
        else
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x22,0x00, 0x6F); /*params_use_leod*/
        }
    }

    /*Bias center setting*/
    ret |= ATBM2040DrvRegHalfAddrBurstWrite(pTuner,BGReg.BaseAddr,BGReg.Data,BGReg.Len);
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x12,0x15, &tmpReg);
        tmpReg &= 0xEF;
        tmpReg |= 0x10;
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x15, tmpReg); /* rsv1<4>: mixr_ldo_div_h_en*/
    }
    else
    {
        ret |= ATBM2040RegRead(pI2CAddr,0x12,0x15, &tmpReg);
        tmpReg &= 0xE0;
        tmpReg |= 0x11;
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x15, tmpReg); /*Rsv1<4:0> = 5'b10001*/
    }
    /*RF_LDO power up*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        Data[0] = 0x00; /*0x12,0x48, dvdd_ldo_24m_psrr_en*/
        Data[1] = 0x00; /*0x12,0x49, dvdd_ldo_24m_psrr_adj[1:0]*/            
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x12,0x48, Data,2);
        ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x06, 0x00); /*lna_ldo_psrr_en*/
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x03, 0x00); /*Vhf_fltr_ldo_psrr_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x12, 0x01); /*temp_snsr_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x3E, 0x00); /*rf_ldo12_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x0D, 0x01); /*osc_test_en*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x17, 0x00); /*osc_por_en, output disable*/
    
    ATBM2040RegListWrite(pI2CAddr,VHF1FilterInitReg,ATBM2040_VHF1_FILTER_INIT_REG_CNT);

    if(ATBM2040_CLK_MODE_CRYSTAL == pTuner->Config.ClkMode)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x11, pTuner->Config.OSCCap.CalibValue); /*osc_core_cap*/
    }   

    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)&&(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode))
    {
        /*VHF1 Filter Cal*/
        ret |= ATBM2040DrvLeoGV1BandCal(pTuner);
        /*VHF2 Filter Cal*/
        ret |= ATBM2040DrvLeoGV2BandCal(pTuner);
        /*UHF Filter Cal*/
        ret |= ATBM2040DrvLeoGUBandCal(pTuner);
    }
    
    /*Mode selection*/
    if(pTuner->HighMD)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x1A, 0x01);
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x1A, 0x00);
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x4F, 0x00);

    /*Lna Attenuator setting */    
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        pTuner->LNAGainMD = 1;
    }   
    if(0 == pTuner->LNAGainMD)
    {/* LNAGainMode B */
        ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x71, 0x7C); /*thr_lna_gain1  */
    }
    else
    {/* LNAGainMode A */
        ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x71, 0x00); /*thr_lna_gain1  */
    }
    ATBM2040RegListWrite(pI2CAddr,LnaAttenReg,ATBM2040_ATTEN_CNT);
    
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x2B, (UINT8)-36); /* [6:0]     -36 params_default_atten_gain[6:0] */
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x2F, 0x00); /* [6:0]     0     params_default_lna_gain[6:0] */
    ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x2E, (UINT8)-4); /* [6:0]    -4 params_default_if_vga2_gain_step[6:0] */

    ret |= ATBM2040RegRead(pI2CAddr,0x12,0x16, &tmpReg);
    tmpReg |= 0x10; /*bit4: set 0*/
    tmpReg &= 0xBF; /*bit5: set 1*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x16, tmpReg);  /*Rsv2<5:4> b'10*/
    
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1F, 0x00);  /* mixr_div_ldo_pd */
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x0B, 0x00); /*mixr_ldo_pd*/

    /*Setting IF filter */
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x00, 0x00); /*if_fltr_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x0D, 0x00); /*if_fltr_core_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x0C, 0x00); /*if_fltr_q_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x11, 0x00); /*if_filt_input_short*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        Data[0] = 0x00; /*0x09,0x02, if_fltr_vcmh_adj*/
        Data[1] = 0x00; /*0x09,0x03, if_fltr_vldoh_adj*/            
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x09,0x02, Data,2);
        ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x06, 0x02); /*if_fltr_vcmo_sel[2:0], 0x01--0.7V;0x02--0.8V;0x04--0.9V;*/
    }

    /*IF filter DCOC calibration*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x16, 0x02); /*if_fltr_dcoc_bw_adj*/
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x16, 0x04); /*if_fltr_dcoc_bw_adj*/
    }

    ATBM2040_BURST_WRITE_START
    ATBM2040HalfAddrRegGroup_t TmpReg = {0x09,6,
        {
            0x18, 0x00, /* 0x09,0x18, 0x00, if_fltr_dcoc_rc_cali_disable,power down DCOC calibration circuit */
            0x15, 0x00, /* 0x09,0x15, 0x00, if_fltr_dcoc_pd */
            0x1C, 0x15, /* 0x09,0x1C, 0x15, if_fltr_cap_dctrl */
        }
    };
    ret |= ATBM2040DrvRegHalfAddrBurstWrite(pTuner,TmpReg.BaseAddr,TmpReg.Data,TmpReg.Len);
    ATBM2040_BURST_WRITE_END;

    if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID)
            ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)
            ||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        UINT32 SignalIFFreq = 0;
        /*Setting IF frequency*/
        SignalIFFreq = pTuner->MixerIF>>8;/* MixerIF/256 */
        Data[0] = (0-SignalIFFreq)&0xFF; /*0x16,0x0C, params_desired_signal_if_freq_h[7:0]*/
        Data[1] = ((0-SignalIFFreq)>>8)&0xFF; /*0x16,0x0D, params_desired_signal_if_freq_h[15:8]*/
        Data[2] = SignalIFFreq&0xFF; /*0x16,0x0E, params_desired_signal_if_freq_l[7:0]*/
        Data[3] = (SignalIFFreq>>8)&0xFF; /*0x16,0x0F, params_desired_signal_if_freq_l[15:8]*/
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x0C, Data,4);
        pTuner->MixerIFBak = pTuner->MixerIF;
    }

    /*Setting DAC and Filter*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)&&(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode))
    {
        Data[0] = 0x01; /*0x10,0x12, dac_div_sel*/
        Data[1] = 0x01; /*0x10,0x13, dac_output_drive_up*/
        Data[2] = 0x01; /*0x10,0x14, dac_sequence_sel*/
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x10,0x12, Data,3);
    }
    ATBM2040RegListWrite(pI2CAddr,DACSettingReg,ATBM2040_DAC_REG_CNT);

    /*Select IF path*/
    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
    {/*ATV*/
        pTuner->IFLevelSpinner = pTuner->Config.AtvIFOut.LevelSpinner;
        ret |= ATBM2040RegWrite(pI2CAddr,0x10,0x03, ATBM2040DrvDACGainCode(pTuner,pTuner->Config.AtvIFOut.IFOutLevel)); /*dac_fltr_gain_ctrl[2:0]*/
    }
    else
    {/*DTV*/
        pTuner->IFLevelSpinner = pTuner->Config.DtvIFOut.LevelSpinner;
        ret |= ATBM2040RegWrite(pI2CAddr,0x10,0x03, ATBM2040DrvDACGainCode(pTuner,pTuner->Config.DtvIFOut.IFOutLevel)); /*dac_fltr_gain_ctrl[2:0]*/
    }

    ret |= ATBM2040DrvIFOutPath(pTuner,ATBM2040_IF_PATH_1); /*DTV and ATV IF data share one path*/

    ret |= ATBM2040DrvDagcAmpRefSet(pTuner); /*PAPR LIMIT    , BB POWER, dagc_amp_ref*/
    ret |= ATBM2040DrvVGAGainThrSet(pTuner);

    /*PLL Registers Setting*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x15, 0x0D); /*osc_core_gm[3:0]*/
        ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x18, 0x03); /*osc_ldo_ps[1:0]*/
        /* ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x3B, 0x02);*/ /*pll_vref_ctrl[1:0]*/
        ret |= ATBM2040RegRead(pI2CAddr,0x12,0x14, &tmpReg);
        if(ATBM_LEOE_CHIP_ID == pTuner->ChipID)
        {
            tmpReg = ((tmpReg&0xE0)|0x06); /*rsv0[4:0]*/
        }
        else
        {
            tmpReg = ((tmpReg&0xC0)|0x26); /*Rsv0<5>: 1, adc_div_h_en; rsv0[4:0]:5'b00110 */
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x14, tmpReg);
    }
    Data[0] = 0x7F; /*0x0F,0x22, pll_n_count_ref_afc*/
    Data[1] = 0x3F; /*0x0F,0x23, pll_n_hold_afc*/            
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x0F,0x22, Data,2);
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x04, 0x00);
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x2A, 0x00); /*pll_dither_bit_sel_sdm*/

    
    ATBM2040_BURST_WRITE_START
    ATBM2040HalfAddrRegGroup_t TmpReg = {0x0F,6,
        {
            0x10, 0x01, /* 0x0F,0x10, 0x00  pll_skvco */
            0x08, 0x00, /* 0x0F,0x08, 0x01  pll_sicp ,the cp current is provided by the ext */
            0x05, 0x80, /* 0x0F,0x05, 0x05  pll_icp[7:0],  the extra current ctrl word 10#:16uA TYP:81# */
        }
    };
    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
    {/*ATV, close temperature compensation*/
        TmpReg.Data[1] = 0x00;
        TmpReg.Data[3] = 0x01;
        TmpReg.Data[5] = 0x05;
    }
    else
    {
    }
    ret |= ATBM2040DrvRegHalfAddrBurstWrite(pTuner,TmpReg.BaseAddr,TmpReg.Data,TmpReg.Len);
    ATBM2040_BURST_WRITE_END;

    ATBM2040RegListWrite(pI2CAddr,PLLSettingReg,ATBM2040_PLL_SETTING_REG_CNT);
    ret |= ATBM2040RegWrite(pI2CAddr,0x0F,0x29, (UINT8)pTuner->PllDivMode); /*pll_mod_mmd, 0:div/2; 1:div/1*/

    if((ATBM_LEOB_CHIP_ID == pTuner->ChipID)||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x40, 0x01); /*mixr_div_mode_en*/
    }
    Data[0] = 0x01; /*0x16,0x46, params_mixr_pd_pll_mixr_div_l*/
    Data[1] = 0x01; /*0x16,0x47, params_mixr_pd_pll_mixr_div_h*/            
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x46, Data,2);
    
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x4A, 0x01); /*params_div_new_en*/
    }

    /*ADC Div setting*/    
    ret |= ATBM2040DrvRegHalfAddrBurstWrite(pTuner,AdcDivReg.BaseAddr,AdcDivReg.Data,AdcDivReg.Len);

    /*Setting ADC*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x1E, 0x00); /* adc_comp    ref current adjust*/
    ret |= ATBM2040DrvRegDataBurstWrite(pTuner,ADCSettingReg,ATBM2040_ADC_REG_CNT);
    ret |= ATBM2040DrvRegDataBurstWrite(pTuner,ADCSettingReg2,ATBM2040_ADC_REG2_CNT);    
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x05, 0x01); /* adc_tuning_start */
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x05, 0x00); /* adc_tuning_start */
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        Data[0] = 0x01; /*0x12,0x5D, adc_clk_sys_pd*/
        Data[1] = 0x00; /*0x12,0x5E, adc_clk_sys_mux*/            
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x12,0x5D, Data,2);
    }

    /*ADC RCTuning use manual mode*/
    ret |= ATBM2040RegRead(pI2CAddr,0x0B,0x09, &tmpReg); /*adc_rctuning_results*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x18, tmpReg); /* adc_rctuning_manual*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x17, 0x01); /* adc_rctuning_manual_en, use Manual RC tuning*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x06, 0x01); /* adc_rc_tuning_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2A, 0x00); /* adc_ck_rc_tune_en*/

    /*RSSI setting*/
    if((ATBM_LEOB_CHIP_ID == pTuner->ChipID)||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x21, 0x30); /*rssi intercept*/
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x08,0x00, 0x00); /*rssi_pd*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x4B, 0x00); /*bypass RSSI calibration*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0C,0x22, 0x0A); /*bg_rssi_100u_con*/

    /*SAR_ADC setting*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x2B, 0x01); /*sar_adc_ck_en*/ /*Turn on SAR_ADC clk*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0D,0x01, (ATBM2040_SAR_ADC_CLK_6MHZ==pTuner->SarAdcClk)?(0x00):(0x01)); /*sar_adc_clkin_sel, 0: 6M; 1: 1.5M*/
    Data[0] = 0x01; /*0x0D,0x04, sar_adc_sample_rssi_en*/
    Data[1] = 0x00; /*0x0D,0x05, sar_adc_ref_range_sel. setting 1, the reference voltage (Vref) is 2.666V,setting 0 the Vref is 2V*/            
    Data[2] = 0x01; /*0x0D,0x06, sar_adc_format_sel. *setting 1,the output format is binary code*/            
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x0D,0x04, Data,3);
    ret |= ATBM2040RegWrite(pI2CAddr,0x0D,0x00, 0x00); /*sar_adc_pd*/ /*Power on SAR ADC*/

#if ATBM2040_GAIN_PHASE_COMPENSATION
    ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x76, 0x01); /*params_phase_compensation*/
    /*Gain offset compensation*/    
    Data[0] = 0x01; /* 0x16,0x93, 0x01  params_digital_gain_offset_lna_debug */
    Data[1] = 0x01; /* 0x16,0x94, 0x01  params_digital_gain_offset_rf_vga1_debug */            
    Data[2] = 0x01; /* 0x16,0x95, 0x01  params_digital_gain_offset_rf_vga2_debug */            
    Data[3] = 0x01; /* 0x16,0x96, 0x01  params_digital_gain_offset_if_vga2_debug */            
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x93, Data,4);
#else
    ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x76, 0x00); /*params_phase_compensation*/
#endif

    /*About AGC*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x89, 0x00); /*params_dagc1_freeze_ini*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x8B, 0x00); /*params_dagc2_freeze_ini*/
    ret |= ATBM2040DrvFastTuneModeSet(pTuner);
    Data[0] = 0x67; /* 0x14,0x72, 0x67 params_thr_aci_status_sig_above_aci[6:0]*/
    Data[1] = 0x08; /* 0x14,0x73, 0x08 params_thr_bb_power_ini[3:0]*/ 
    Data[2] = 0x04; /* 0x14,0x74, 0x04 params_thr_bb_power_ready_ini[3:0]*/ 
    Data[3] = 0x08; /* 0x14,0x75, 0x08 params_thr_bb_power_tracking[3:0]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x72, Data,4);
    Data[0] = 0x14; /* 0x14,0x45, 0x14 params_if_vga2_gain_step_max[6:0]*/
    Data[1] = 0x7C; /* 0x14,0x46, 0x7C params_if_vga2_gain_step_min[6:0]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x45, Data,2);
    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
    {
        Data[0] = 0x0F; /* 0x14,0x89, 0xFF params_waiting_samples_if_vga2_setting[7:0]*/
        Data[1] = 0x00; /* 0x14,0x8A, 0xFF params_waiting_samples_if_vga2_setting[15:8]*/
        Data[2] = 0x00; /* 0x14,0x8B, 0x01 params_waiting_samples_if_vga2_setting[17:16]*/ 
        Data[3] = 0x0F; /* 0x14,0x8C, 0xFF params_waiting_samples_lna_setting[7:0]*/
        Data[4] = 0x00; /* 0x14,0x8D, 0xFF params_waiting_samples_lna_setting[15:8]*/
        Data[5] = 0x00; /* 0x14,0x8E, 0x01 params_waiting_samples_lna_setting[17:16]*/ 
    }
    else
    {
        Data[0] = 0xFF; /* 0x14,0x89, 0xFF params_waiting_samples_if_vga2_setting[7:0]*/
        Data[1] = 0xFF; /* 0x14,0x8A, 0xFF params_waiting_samples_if_vga2_setting[15:8]*/
        Data[2] = 0x01; /* 0x14,0x8B, 0x01 params_waiting_samples_if_vga2_setting[17:16]*/ 
        Data[3] = 0xFF; /* 0x14,0x8C, 0xFF params_waiting_samples_lna_setting[7:0]*/
        Data[4] = 0xFF; /* 0x14,0x8D, 0xFF params_waiting_samples_lna_setting[15:8]*/
        Data[5] = 0x01; /* 0x14,0x8E, 0x01 params_waiting_samples_lna_setting[17:16]*/ 
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x89, Data,6);

    ATBM2040RegListWrite(pI2CAddr,AGCReg,ATBM2040_AGC_REG_CNT);

    /*RSSI threshold*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID))
    {
        Data[0] = 0x5A; /*0x14,0x64, params_rssi_thr1[7:0]*/
        Data[1] = 0x5C; /*0x14,0x65, params_rssi_thr2[7:0]*/            
    }
    else
    {
        Data[0] = 0x4A; /*0x14,0x64, params_rssi_thr1[7:0]*/
        Data[1] = 0x4C; /*0x14,0x65, params_rssi_thr2[7:0]*/            
    }    
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x14,0x64, Data,2);

    ATBM2040RegListWrite(pI2CAddr,MisReg,ATBM2040_MIS_REG_CNT);
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        ATBM2040RegListWrite(pI2CAddr,LeoCMisReg,ATBM2040_LEOC_MIS_REG_CNT);
        if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
        {
            ATBM2040RegListWrite(pI2CAddr,LeoCATVMisReg,ATBM2040_LEOC_ATV_MIS_REG_CNT);            
            pRegGroup = &IIRCoefSA10M3rdSOSHmd;
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
            pRegGroup = &IIRCoefSA10M3rdSOSLmd;
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
        }
        else
        {
            ATBM2040RegListWrite(pI2CAddr,LeoCDTVMisReg,ATBM2040_LEOC_DTV_MIS_REG_CNT);
            if((ATBM2040_SIGNAL_MODE_DVBT == pTuner->Config.Mode)
                ||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->Config.Mode)
                ||(ATBM2040_SIGNAL_MODE_DVBC == pTuner->Config.Mode))
            {
                pRegGroup = &IIRCoefSA10M3rdSOSHmd;
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                pRegGroup = &IIRCoefSA10M3rdSOSLmd;
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
            }
        }
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x14, 0x07); /*params_banalog_change_num_tracking */
    }

    /*FEF And LTE config*/
    ret |= ATBM2040DrvFEFSourceAndLTESet(pTuner);

    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
    {
        Data[0] = 0x0F; /*0x16,0x3B,  params_waiting_samples_digital_gain_setting[7:0] */
        Data[1] = 0x00; /*0x16,0x3C,  params_waiting_samples_digital_gain_setting[15:8]*/
        Data[2] = 0x00; /*0x16,0x3D,  params_waiting_samples_digital_gain_setting[17:16]*/
    }
    else
    {
        Data[0] = 0xFF; /*0x16,0x3B,  params_waiting_samples_digital_gain_setting[7:0] */
        Data[1] = 0x08; /*0x16,0x3C,  params_waiting_samples_digital_gain_setting[15:8]*/
        Data[2] = 0x01; /*0x16,0x3D,  params_waiting_samples_digital_gain_setting[17:16]*/
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x16,0x3B, Data,3);

    /*watch_dog*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x17,0x00, 0x20); /*params_watch_dog_bypass_bbpow[7:0] */
    Data[0] = 0x20; /*0x17,0x02,  params_watch_dog_bypass_rssi1[7:0]*/
    Data[1] = 0x20; /*0x17,0x03,  params_watch_dog_bypass_rssi2[7:0]*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0x02, Data,2);

    /*other DSP registers*/
    if(ATBM2040_SIGNAL_MODE_ATV != pTuner->Config.Mode)
    {/*DTV*/
        ATBM2040RegListWrite(pI2CAddr,DSPDTVReg,ATBM2040_DSP_DTV_REG_CNT);
    }
    else
    {/*ATV*/
        ATBM2040RegListWrite(pI2CAddr,DSPATVReg,ATBM2040_DSP_ATV_REG_CNT);
        if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        {            
            Data[0] = 0xC1; /*0x1A,0x62, params_thr_iq_narw_band_filter_l  [6:0]*/
            Data[1] = 0xC1; /*0x1A,0x63, params_thr_iq_narw_band_filter_h  [6:0]*/            
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x1A,0x62, Data,2);
        }
    }

    ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x8F, 0x01); /*params_phase_com_lna       */
    ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x92, 0x01); /*params_phase_com_IF_VGA2   */

    ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x36, 0x1A); /*params_thr_analog_t_hlo  */

    if((ATBM_LEOB_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x8F, 0x14); /*params_thr_vhf_filter_max_n_plus_minus_m_aci_l  */
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x90, 0x0A); /*params_thr_vhf_filter_max_n_plus_minus_m_aci_s  */
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x91, 0x00); /*params_vhf_filter_max_set_en  */
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x17,0x20, 0x00); /*params_bb_inband_detect_enable  */

    ATBM2040RegListWrite(pI2CAddr,DSPMiscReg,ATBM2040_DSP_MISC_REG_CNT);    
    Data[0] = 0x19; /*0x17,0x40,  thr delta power */
    Data[1] = 0x00; /*0x17,0x41,  ad judge logic  1:delta power 2:total power/peak power */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0x40, Data,2);
                  
    Data[0] = 0x20; /*0x17,0x4D,  sweep_n */
    Data[1] = 0x10; /*0x17,0x4E,   aci large for aci apec analyssis */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0x4D, Data,2);
                  
    Data[0] = 0x00; /*0x17,0x54,  use old dagc1 ref */
    Data[1] = 0xD3; /*0x17,0x55,  params_used_old_dagc_ref */
    Data[2] = 0x6E; /*0x17,0x56,  params_if_filter_gain_aci_db_analog,need to be checked */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0x54, Data,3);
                  
    Data[0] = 0x1E; /*0x17,0x81,  params_use_preset_lo_thr[6:0],30 */
    Data[1] = 0x00; /*0x17,0x82,  params_lo_selection_preset_value */
    Data[2] = 0x01; /*0x17,0x83,  f_signal_user_set */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0x81, Data,3);
                  
    Data[0] = 0x01; /*0x17,0xED,  params_use_leo */
    if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->Config.Mode)
    {
        Data[1] = 0x0D; /*0x17,0xEE,  params_uhf_vhf_filter_gain[5:0] */
    }
    else
    {
        Data[1] = 0x02; /*0x17,0xEE,  params_uhf_vhf_filter_gain[5:0] */
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0xED, Data,2);
                  
    Data[0] = 0x5A; /*0x17,0xF6,  params_rf_input_power_thr1_mode0 */
    Data[1] = 0x64; /*0x17,0xF7,  params_rf_input_power_thr2_mode0 */
    Data[2] = 0x5A; /*0x17,0xF8,  params_rf_input_power_thr1_mode1 */
    Data[3] = 0x64; /*0x17,0xF9,  params_rf_input_power_thr2_mode1 */
    Data[4] = 0x5A; /*0x17,0xFA,  params_rf_input_power_thr1_mode2 */
    Data[5] = 0x64; /*0x17,0xFB,  params_rf_input_power_thr2_mode2 */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0xF6, Data,6);

    Data[0] = 0x7F; /*0x19,0xA4,  if_filter_gain_aci_db_lo */
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)&&(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode))
    {
        Data[1] = 0x06; /*0x19,0xA5,  if_filter_gain_aci_db_analog_llo */
        Data[2] = 0x7C; /*0x19,0xA6,  if_filter_gain_aci_db_analog_hlo */
        Data[3] = 0x6F; /*0x19,0xA7,  if_filter_gain_aci_db_analog_llo_lo */
        Data[4] = 0x65; /*0x19,0xA8,  if_filter_gain_aci_db_analog_hlo_lo */        
    }
    else
    {
        Data[1] = 0x06; /*0x19,0xA5,  if_filter_gain_aci_db_analog_llo */
        Data[2] = 0x7E; /*0x19,0xA6,  if_filter_gain_aci_db_analog_hlo */
        Data[3] = 0x73; /*0x19,0xA7,  if_filter_gain_aci_db_analog_llo_lo */
        Data[4] = 0x7A; /*0x19,0xA8,  if_filter_gain_aci_db_analog_hlo_lo */
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x19,0xA4, Data,5);
    
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        ATBM2040RegGroup_t *pRegGrp = &AlterThrRssiLnaOutTracking;
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x97, 0x15); /*params_mixer_if_filter_gain[5:0]    */
        ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x70, 0x00); /*bypass lna gain thr change    */
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGrp->BaseReg,pRegGrp->OffReg,pRegGrp->Data,pRegGrp->Len);
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x97, 0x18); /*params_mixer_if_filter_gain[5:0]    */
        ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x70, 0x01); /*bypass lna gain thr change    */
    }
    
    /*long AGC bus */
    Data[0] = 0x01; /*0x00,0x34, params_agc_cmd_adj_enable*/
    Data[1] = 0x1F; /*0x00,0x35,  lo cycle */
    Data[2] = 0x04; /*0x00,0x36,  other cycle */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x00,0x34, Data,3);

    Data[0] = 0x40; /*0x02,0x1B, intf_sample_n */
    Data[1] = 0x1D; /*0x02,0x1C,  intf_sample_m */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x02,0x1B, Data,2);
    ret |= ATBM2040RegWrite(pI2CAddr,0x02,0x21, 0x02); /* intf_sample_m_start */

    ret |= ATBM2040RegWrite(pI2CAddr,0x18,0x40, 0x05); /* lo set zero and juse pll lock flag */
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x24, 0xFF); /* maximum time for judge lock */
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x26, 0x0F); /* long to judge pll lock */
    ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x03, 0x00); /*  directly use pll lock from pll, and delay 128cycle , and combine with time */
    ret |= ATBM2040RegWrite(pI2CAddr,0x02,0x1F, 0x1F); /* pll_200us_cfg[15:8] */
    Data[0] = 0x01; /*0x00,0x2A, use fifo  */
    Data[1] = 0x00; /*0x00,0x2B, params_agc_keep */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x00,0x2A, Data,2);


    ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x2D, 0x01); /* params_analog_cfo_bypass */
    /* ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x41, 0x01);*/ /* params_sfi_detect_notch_bypass_1 */
    ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x49, 0x01); /* params_sfi_detect_notch_bypass_2 */
    ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x16, 0x00); /* params_aci_in_band_analysis_bypass */
    ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x6C, 0x01); /* params_notch_iir_a_aci */

    if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        Data[0] = 0x19; /*0x17,0x93, params_thr_aci_status_n_m_large_h[6:0]*/
        Data[1] = 0x0F; /*0x17,0x94, params_thr_aci_status_n_m_large_l[6:0]*/            
    }
    else
    {
        Data[0] = 0x14; /*0x17,0x93, params_thr_aci_status_n_m_large_h[6:0]*/
        Data[1] = 0x0F; /*0x17,0x94, params_thr_aci_status_n_m_large_l[6:0]*/            
    }    
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x17,0x93, Data,2);

    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        if((ATBM2040_SIGNAL_MODE_DVBT == pTuner->Config.Mode)
            ||(ATBM2040_SIGNAL_MODE_DTMB == pTuner->Config.Mode)
            ||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->Config.Mode))
        {
            if(2 == pTuner->LowCousumMd)
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x22,0x00, 0x67); /*params_use_leod*/
            }
            else
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x22,0x00, 0x7F); /*params_use_leod*/
            }
            ret |= ATBM2040RegWrite(pI2CAddr,0x23,0xCB, 0x01); /*params_lo_sign_map_mode[2:0]*/
            if((ATBM2040_SIGNAL_MODE_DTMB == pTuner->Config.Mode)||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->Config.Mode))
            {/*DTMB calibration and LO change thr*/
                ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x4E, 0x0C);
            }
  
            if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
            {
                pRegGroup = &IIRCoefSA8M3rdSOSHmd;
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                pRegGroup = &IIRCoefSA8M3rdSOSLmd;
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                
                pRegGroup = &ATSCIIRCoefSA10M3rdSOSHmd;
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                pRegGroup = &ATSCIIRCoefSA10M3rdSOSLmd;
                ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                
                pRegGroup = AciN234CalResultATSC;
                while(0 != pRegGroup->Len)
                {
                    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                    pRegGroup++;
                }
            }   
            if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->Config.Mode)
            {
                pRegGroup = &ATSCAciN234JudgeThr;
            }
            else
            {
                pRegGroup = &DVBTAciN234Judge;
            }
        }
        else
        {
            if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
            {
                pRegGroup = AciN234CalResultATV;
                while(0 != pRegGroup->Len)
                {
                    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                    pRegGroup++;
                }
            }
            else if(ATBM2040_SIGNAL_MODE_DVBC != pTuner->Config.Mode)
            {
                pRegGroup = AciN234CalResult;
                while(0 != pRegGroup->Len)
                {
                    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
                    pRegGroup++;
                }
            }
            ret |= ATBM2040RegWrite(pI2CAddr,0x22,0x00, 0x61); /*params_use_leod*/
            ret |= ATBM2040RegWrite(pI2CAddr,0x23,0xCB, 0x00); /*params_lo_sign_map_mode[2:0]*/
            pRegGroup = &OtherAciN234Judge;
        }
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGroup->BaseReg,pRegGroup->OffReg,pRegGroup->Data,pRegGroup->Len);
        
        switch(pTuner->LowCousumMd)
        {
            case 0:
                Data[0] = 0x00;
                Data[1] = 0x00;
                Data[2] = 0x00;
                Data[3] = 0x02;
                Data[4] = 0x0F;
                Data[5] = 0x0A;
                break;
            case 1:
                Data[0] = 0x01;
                Data[1] = 0x01;
                Data[2] = 0x01;
                Data[3] = 0x02;
                Data[4] = 0x0F;
                Data[5] = 0x08;
                break;
            case 2:
                Data[0] = 0x01;
                Data[1] = 0x01;
                Data[2] = 0x01;
                Data[3] = 0x00;
                Data[4] = 0x09;
                Data[5] = 0x08;
                break;
            default:
                break;
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x10,0x10, Data[0]); 
        ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x0E, Data[1]); 
        ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x1F, Data[2]); 
        
        ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x01, Data[3]); 
        ret |= ATBM2040RegWrite(pI2CAddr,0x0C,0x2E, Data[4]); 

        ret |= ATBM2040RegWrite(pI2CAddr,0x0C,0x0E, Data[5]); 

        
        ret |= ATBM2040RegWrite(pI2CAddr,0x23,0xE7, 0x00);
    }

    if(ATBM2040_SIGNAL_MODE_ATV == pTuner->Config.Mode)
    {/*ATV*/
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,ATVRSSIReg.BaseReg,ATVRSSIReg.OffReg, ATVRSSIReg.Data,ATVRSSIReg.Len);
    }
    else
    {/*DTV*/
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,DTVRSSIReg.BaseReg,DTVRSSIReg.OffReg, DTVRSSIReg.Data,DTVRSSIReg.Len);
    }

    /*write SDK version into register*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x1B, ATBM2040Ver); /*SDK version*/

    /*Clock out control*/
    ret |= ATBM2040DrvClkOutControl(pTuner);

    /*GPO state set*/
    ret |= ATBM2040DrvGPOStateSet(pTuner,pTuner->Config.PinsCfg,(UINT32)ATBM2040_PIN_MAX);

    /*LTA*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x02, (ATBM2040_RF_LTA_OUT_ENABLE==pTuner->Config.LTAOut)?(0x00):(0x01)); /*lta_pd*/
    
    ret |= ATBM2040RegRead(pI2CAddr,0x12,0x15, &tmpReg);
    tmpReg &= 0xFE;
    tmpReg |= ((ATBM2040_RF_LTA_OUT_ENABLE==pTuner->Config.LTAOut)?(0x00):(0x01));
    ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x15, tmpReg); /*rsv1[0], LTA_LDO_PD*/

    pTuner->StandbyState = FALSE;

    if(ATBM2040_NO_ERROR == ret)
    {
        pTuner->Inited = TRUE;
    }
    return ret;
}

/************************************************************
*Description: frequency tune
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvFreqTune(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 HMDAdcClk = 0,LMDAdcClk = 0;
    UINT8 tmpReg = 0;
    UINT8 RXFltIQSwap = 0x00,ADCIQSwap = 0x00;
    UINT8 Data[6] = {0x00};
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    /*SDK version check */
    ret |= ATBM2040RegRead(pI2CAddr,0x12,0x1B, &tmpReg);
    if(tmpReg != ATBM2040Ver)
    {
        ret |= ATBM2040DrvInit(pTuner);
    }

    ATBM2040DrvNLOMixer(pTuner); /*Mixer Divider select*/
    ATBM2040DrvADCClkCal(pTuner,&HMDAdcClk,&LMDAdcClk);/*ADC CLK calculate*/

    if(pTuner->StandbyState)
    {/*Wakeup it first if in standby state*/
        ret |= ATBM2040DrvWakeup(pTuner);
    }

    /*Stop DSP*/
    ret |= ATBM2040DrvStopDSP(pTuner);

    /*Signal mode check*/
    if(ATBM2040_SIGNAL_MODE_ISDBT == pTuner->Config.Mode)
    {
        pTuner->SignalMode = ATBM2040_SIGNAL_MODE_DTMB;
    }
    if(pTuner->Config.Mode != pTuner->SignalMode)
    {/*new mode is different from old mode*/
        pTuner->Config.Mode = pTuner->SignalMode;
        ret |= ATBM2040DrvInit(pTuner);
    }
    /*adc_dwa*/
    if((ATBM_LEOE_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID))
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x0A, 0x01);  /*adc_dwa_disable*/
    }

    /*LNA Gain setting*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x0B, 0x03); /*lna_mode*/
    Data[0] = 0x05; /*0x04,0x07, 0x05  att_gain_fine[2:0] */
    Data[1] = 0x02; /*0x04,0x08, 0x02  att_gain_coarse[1:0] */
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x04,0x07, Data,2);

    if(ATBM_LEOB_CHIP_ID == pTuner->ChipID)
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x05, 0x0B); /* [1:0]    10    lna_gain_fine[1:0] */
    }
    else
    {
        Data[0] = 0x01; /*0x04,0x03, 0x01  lna_gm_ctrl<1:0>  */
        Data[1] = 0x06; /*0x04,0x04, 0x06  lna_rl_ctrl<4:0> */
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x04,0x03, Data,2);
    }

    /*IF Filter Gain setting*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x09,0x1A, 0x00); /*if_fltr_gain_ctrl*/

    /*ADC clock setting*/
    ret |= ATBM2040DrvADCCLKSet(pTuner);

    /*VHF/UHF filter setting*/
    ret |= ATBM2040DrvAnaFltSetting(pTuner);

    /*PLL and Mixer divider setting*/
    ret |= ATBM2040DrvPLLMixDivSet(pTuner);
    ret |= ATBM2040DrvMixerReset(pTuner);

    /*Setting the IF frequency calibration registers*/
    ret |= ATBM2040DrvIFFilterSet(pTuner);

    /*Init ADC*/
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x25, 0x00);
    ret |= ATBM2040RegWrite(pI2CAddr,0x0B,0x25, 0x01);


    /*DSP register config*/
    ret |= ATBM2040DrvDSPRegConfig(pTuner,HMDAdcClk,LMDAdcClk);
#if ATBM2040_GAIN_PHASE_COMPENSATION
    /*Phase and gain compensation config*/
    ret |= ATBM2040DrvPhaseAndGainConfig(pTuner);
#endif

    /*iq_swap*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        if(ATBM2040_VHF_CHECK(pTuner->FreqKHz))
        {
            pTuner->ADCIQSwap = TRUE;
            ADCIQSwap = 0x01;
            RXFltIQSwap = (pTuner->InvertSpectrum)?(0x01):(0x00);
        }
        else
        {
            pTuner->ADCIQSwap = FALSE;
            ADCIQSwap = 0x00;
            RXFltIQSwap = (pTuner->InvertSpectrum)?(0x01):(0x00);
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x48, ADCIQSwap); /*params_adc_iq_swap */
    }
    else
    {
        if(pTuner->ADCIQSwap)
        {
            RXFltIQSwap = (pTuner->InvertSpectrum)?(0x01):(0x00);
        }
        else
        {
            RXFltIQSwap = (pTuner->InvertSpectrum)?(0x00):(0x01);
        }
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x15,0x3E, RXFltIQSwap); /*params_rxflt_iq_swap [0] */

    /*BandWidth*/
    ret |= ATBM2040DrvBWSet(pTuner);

    /*RSSI Intercept*/
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        UINT16 Intercept = 0;
        Intercept = ATBM2040DrvRSSIInterceptGet(pTuner);
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x21, (UINT8)(Intercept&0xFF)); /*rssi intercept*/
        /* ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x22, (UINT8)((Intercept>>8)&0xFF)); */
    }

    /*RXFLT rc filter bandwidth and spectrum parse setting*/
    ret |= ATBM2040DrvRxFltAndSpectrumParse(pTuner);

    /*BB power target setting*/
    ret |= ATBM2040DrvAgcPowerTargetSet(pTuner);

    if(ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
    {
        ret |= ATBM2040DrvLteTargetSet(pTuner);
    }
    ret |= ATBM2040DrvIIRCoefJudge(pTuner);

    /*Start tune*/
    ret |= ATBM2040DrvStartDSP(pTuner);

    return ret;
}

/************************************************************
*Description: detect if chip exist
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvDetect(ATBM2040I2CAddr_t *pI2CAddr)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 Value = 0;
    ret = ATBM2040I2CRead(pI2CAddr,0x00,0x00, &Value,1);
    if(ATBM2040_NO_ERROR != ret)
    {
        return ret;
    }
    if((ATBM_LEOG_CHIP_ID == Value)
        ||(ATBM_LEOF_CHIP_ID == Value)
        ||(ATBM_LEOB_CHIP_ID == Value))
    {
        return ATBM2040_NO_ERROR;
    }
    else
    {
        return ATBM2040_ERROR_NO_DEVICE;
    }
}

/************************************************************
*Description: RxFlt and Spectrum setting
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvRxFltAndSpectrumParse(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040RegGroup_t RegSigBwMode;
    BOOL SigBwMdSetFlag = FALSE;
    ATBM2040RegGroup_t *pRegGrp = NULL;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;

    if(pTuner->BWKHzBak == pTuner->BWKHz)
    {
        return ret;
    }
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        if(ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode)
        {
            UINT32 BandWidth = (pTuner->BWKHz+500)/1000;
            ATBM2040_REG_ADDR_SET(RegSigBwMode,0x19,0xAC);
            RegSigBwMode.Len = 4; /*from 0x19,0xAC to 0x19,0xAF */
            
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                RegSigBwMode.Data[0] = 0x03;/*(UINT8)(BandWidth-6)*/
                RegSigBwMode.Data[1] = 0x03;/*(UINT8)(BandWidth-6)*/
            }
            else
            {
                RegSigBwMode.Data[0] =  (UINT8)(BandWidth-6);
                RegSigBwMode.Data[1] =  (UINT8)(BandWidth-6);
            }
            RegSigBwMode.Data[2] =  (UINT8)(BandWidth-6);
            RegSigBwMode.Data[3] =  (UINT8)(BandWidth-6);
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,RegSigBwMode.BaseReg,RegSigBwMode.OffReg, RegSigBwMode.Data, RegSigBwMode.Len);
            SigBwMdSetFlag = TRUE;
        }
        else if(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode)
        {            
            ATBM2040_REG_ADDR_SET(RegSigBwMode,0x19,0xAC);
            RegSigBwMode.Len = 4; /*from 0x19,0xAC to 0x19,0xAF */
            
            RegSigBwMode.Data[0] = 0x03;
            RegSigBwMode.Data[1] = 0x03;            
            RegSigBwMode.Data[2] = 0x03;
            RegSigBwMode.Data[3] = 0x03;
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,RegSigBwMode.BaseReg,RegSigBwMode.OffReg, RegSigBwMode.Data, RegSigBwMode.Len);
            SigBwMdSetFlag = TRUE;
        }
    }

    if(pTuner->BWKHz <= 6000)
    {
        pRegGrp = &RxFltBw6MRCReg1;
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGrp->BaseReg,pRegGrp->OffReg,pRegGrp->Data,pRegGrp->Len);
        if(!SigBwMdSetFlag)
        {
            pRegGrp = &RxFltBw6MRCReg2;
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGrp->BaseReg,pRegGrp->OffReg,pRegGrp->Data,pRegGrp->Len);
        }
    }
    else if(pTuner->BWKHz <= 7000)
    {
        pRegGrp = &RxFltBw7MRCReg1;
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGrp->BaseReg,pRegGrp->OffReg,pRegGrp->Data,pRegGrp->Len);
        if(!SigBwMdSetFlag)
        {
            pRegGrp = &RxFltBw7MRCReg2;
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGrp->BaseReg,pRegGrp->OffReg,pRegGrp->Data,pRegGrp->Len);
        }
    }
    else /* if(pTuner->BWKHz <= 8000)*/
    {
        pRegGrp = &RxFltBw8MRCReg1;
        ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGrp->BaseReg,pRegGrp->OffReg,pRegGrp->Data,pRegGrp->Len);
        if(!SigBwMdSetFlag)
        {
            if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)&&(ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode))
            {
                pRegGrp = &LeoGRxFltBw8MRCReg2;
            }
            else
            {
                pRegGrp = &RxFltBw8MRCReg2;
            }
            ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,pRegGrp->BaseReg,pRegGrp->OffReg,pRegGrp->Data,pRegGrp->Len);
        }
    }
    return ret;
}

/************************************************************
*Description: Fast tune mode setting
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvFastTuneModeSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    if(ATBM2040_FAST_TUNE_MODE_FAST == pTuner->Config.FastTuneMD)
    {   
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x2A, 0x10);/*params_data_length_spectrum_analysis_4x[4:0]*/
    }
    else
    {
        ret |= ATBM2040RegWrite(pI2CAddr,0x14,0x2A, 0x12);/*params_data_length_spectrum_analysis_4x[4:0]*/
    }
    return ret;
}


/************************************************************
*Description: Change some config
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvCfgSet(ATBM2040_t *pTuner,ATBM2040CfgCMD_t *pCfg)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 tmpReg = 0x00;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    switch(pCfg->CfgCmd)
    {
        case ATBM2040_CFG_CMD_DTV_IF_OUT_SETTING:
            if(pCfg->Cfg.IFOut.IFOutFreqHz != pTuner->Config.DtvIFOut.IFOutFreqHz)
            {
                pTuner->Config.DtvIFOut.IFOutFreqHz = pCfg->Cfg.IFOut.IFOutFreqHz;
                ret = ATBM2040DrvFreqShiftFromBBtoIF(pTuner,FALSE,NULL,NULL);
            }
            if((pCfg->Cfg.IFOut.IFOutLevel != pTuner->Config.DtvIFOut.IFOutLevel)||(pCfg->Cfg.IFOut.LevelSpinner != pTuner->Config.DtvIFOut.LevelSpinner))
            {
                pTuner->Config.DtvIFOut.IFOutLevel = pCfg->Cfg.IFOut.IFOutLevel;
                pTuner->IFLevelSpinner = pTuner->Config.DtvIFOut.LevelSpinner;
                ret |= ATBM2040RegWrite(pI2CAddr,0x10,0x03, ATBM2040DrvDACGainCode(pTuner,pCfg->Cfg.IFOut.IFOutLevel)); /*dac_fltr_gain_ctrl[2:0]*/
            }
            break;
        case ATBM2040_CFG_CMD_ATV_IF_OUT_SETTING:
            if(pCfg->Cfg.IFOut.IFOutFreqHz != pTuner->Config.AtvIFOut.IFOutFreqHz)
            {
                pTuner->Config.AtvIFOut.IFOutFreqHz = pCfg->Cfg.IFOut.IFOutFreqHz;
                ret = ATBM2040DrvFreqShiftFromBBtoIF(pTuner,FALSE,NULL,NULL);
            }
            if((pCfg->Cfg.IFOut.IFOutLevel != pTuner->Config.AtvIFOut.IFOutLevel)||(pCfg->Cfg.IFOut.LevelSpinner != pTuner->Config.AtvIFOut.LevelSpinner))
            {
                pTuner->Config.AtvIFOut.IFOutLevel = pCfg->Cfg.IFOut.IFOutLevel;
                pTuner->IFLevelSpinner = pTuner->Config.AtvIFOut.LevelSpinner;
                ret |= ATBM2040RegWrite(pI2CAddr,0x10,0x03, ATBM2040DrvDACGainCode(pTuner,pCfg->Cfg.IFOut.IFOutLevel)); /*dac_fltr_gain_ctrl[2:0]*/
            }
            break;
        case ATBM2040_CFG_CMD_CLK_OUT:
            pTuner->Config.ClkOut = pCfg->Cfg.ClkOut;
            ret = ATBM2040DrvClkOutControl(pTuner);
            break;
        case ATBM2040_CFG_CMD_PIN_SETTING:
            ret = ATBM2040DrvGPOStateSet(pTuner,&pCfg->Cfg.PinCfg,1);
            break;
        case ATBM2040_CFG_CMD_OSC_CAP_SET:
            if(ATBM2040_CLK_MODE_CRYSTAL == pTuner->Config.ClkMode)
            {
                pTuner->Config.OSCCap = pCfg->Cfg.OSCCap;
                ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x11, pTuner->Config.OSCCap.CalibValue); /*osc_core_cap*/
            }
            break;
        case ATBM2040_CFG_CMD_RF_LTA:
            pTuner->Config.LTAOut = pCfg->Cfg.LTAOut;
            ret |= ATBM2040RegWrite(pI2CAddr,0x04,0x02, (ATBM2040_RF_LTA_OUT_ENABLE==pCfg->Cfg.LTAOut)?(0x00):(0x01)); /*lta_pd*/
            
            ret |= ATBM2040RegRead(pI2CAddr,0x12,0x15, &tmpReg);
            tmpReg &= 0xFE;
            tmpReg |= ((ATBM2040_RF_LTA_OUT_ENABLE==pTuner->Config.LTAOut)?(0x00):(0x01));
            ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x15, tmpReg); /*rsv1[0], LTA_LDO_PD*/
            break;
        case ATBM2040_CFG_CMD_FAST_TUNE:
            if(pTuner->Config.FastTuneMD != pCfg->Cfg.FastTuneMD)
            {
                pTuner->Config.FastTuneMD = pCfg->Cfg.FastTuneMD;
                ret |= ATBM2040DrvFastTuneModeSet(pTuner);
            }
            break;    
        default:
            break;
    }
    return ret;
}

/************************************************************
*Description: Get current RSSI value
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvGetRSSI(ATBM2040I2CAddr_t *pI2CAddr,SINT16 *pRSSIx16)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 Val = 0;
    SINT16 SignalPow = 0;

    ret |= ATBM2040DrvRegLatch(pI2CAddr,TRUE);
    ret |= ATBM2040RegRead(pI2CAddr,0x14,0xD0, &Val);
    SignalPow = Val;
    ret |= ATBM2040RegRead(pI2CAddr,0x14,0xD1, &Val);
    ret |= ATBM2040DrvRegLatch(pI2CAddr,FALSE);
    SignalPow |= ((Val&0x0F)<<8);
    SignalPow <<= 4;
    SignalPow >>= 4;
    *pRSSIx16 = SignalPow;

    return ret;
}

/************************************************************
*Description: Get ATV CFO(KHz)
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvGetATVCfo(ATBM2040I2CAddr_t *pI2CAddr,SINT32 *pCfoKHz)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 Val = 0;
    SINT16 Cfo = 0;

    ret |= ATBM2040DrvRegLatch(pI2CAddr,TRUE);
    ret |= ATBM2040RegRead(pI2CAddr,0x1A,0xDB, &Val);
    if(0x01 != Val)
    {
        *pCfoKHz = 0;
        ret |= ATBM2040DrvRegLatch(pI2CAddr,FALSE);
        ret |= ATBM2040_ERROR_CFO_NOT_READY;
        return ret;
    }
    ret |= ATBM2040RegRead(pI2CAddr,0x1A,0xD9, &Val);
    Cfo = Val;
    ret |= ATBM2040RegRead(pI2CAddr,0x1A,0xDA, &Val);
    ret |= ATBM2040DrvRegLatch(pI2CAddr,FALSE);
    Cfo |= ((Val&0x7F)<<8);
    Cfo <<= 1;
    Cfo >>= 1;
    *pCfoKHz = (((SINT32)Cfo)*256 + 500)/1000;
    /* *pCfoKHz = ((*pCfoKHz+50)/100)*100; */
    return ret;
}

/************************************************************
*Description: Enter standby state
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvStandby(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    if(!pTuner->StandbyState)
    {    
#ifdef ATBM2040_CHIP_DEBUG_OPEN
        ret |= ATBM2040DrvFirmwareDisable(pTuner);
#else
#if ATBM2040_FIRMWARE_LOAD
        if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID))
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x20,0x1F, 0x00);
        }
#endif
#endif
        ATBM2040RegListWrite(pI2CAddr,StandbyReg,ATBM2040_STANDBY_REG_CNT);
        if(pTuner->FreqKHz < ATBM2040_VHF2_LOW_KHZ)
        {
            /* ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x0C, 0x01); */ /*vhf_fltr_ldo_pd*/
        }
        else if(pTuner->FreqKHz <= ATBM2040_UHF_LOW_KHZ)
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x01); /* vhf2_fltr_pwdn_ldo */
        }
        else
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x00, 0x01); /*uhf_fltr_pwdn_ldo*/
        }
        pTuner->StandbyState = TRUE;
    }
    return ret;
}

/************************************************************
*Description: Wakeup from standby state
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvWakeup(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    /*ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;*/
    if(pTuner->StandbyState)
    {
#if 1
        ret |= ATBM2040DrvInit(pTuner);
        ret |= ATBM2040DrvFreqTune(pTuner);
#else
        if(pTuner->FreqKHz < ATBM2040_VHF2_LOW_KHZ)
        {
            /* ret |= ATBM2040RegWrite(pI2CAddr,0x06,0x0C, 0x00); */ /*vhf_fltr_ldo_pd*/
        }
        else if(pTuner->FreqKHz <= ATBM2040_UHF_LOW_KHZ)
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x21, 0x00); /* vhf2_fltr_pwdn_ldo */
        }
        else
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x05,0x00, 0x00); /*uhf_fltr_pwdn_ldo*/
        }
        ATBM2040RegListWrite(pI2CAddr,WakeupReg,ATBM2040_WAKEUP_REG_CNT);
#ifdef ATBM2040_CHIP_DEBUG_OPEN
        ret |= ATBM2040DrvFirmwareEnable(pTuner);
#else
#if ATBM2040_FIRMWARE_LOAD
        if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID))
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x20,0x1F, 0x01);
        }
#endif
#endif
#endif
        pTuner->StandbyState = FALSE;
    }
    return ret;
}

/************************************************************
*Description: Get SDK version
*************************************************************/
ATBM2040_ERROR_e ATBM2040DrvGetSDKVer(ATBM2040_t *pTuner,UINT32 *pVer)
{
    (void)pTuner;
    *pVer = (UINT32)ATBM2040Ver;
    return ATBM2040_NO_ERROR;
}


static BOOL IIRCoefJudgeOpen = FALSE;
void ATBM2040DrvIIRCoefJudgeStateSet(BOOL Open)
{
    IIRCoefJudgeOpen = Open;
}

static BOOL ATBM2040DrvIIRCoefJudgeStateGet(void)
{
    return IIRCoefJudgeOpen;
}

static UINT8 IIRCodeJudgeHMD[3][64]=
{
/*(Params.fs_H/4 <= 47.5e6)*/
    {0xB0,0x04, 0x3F,0x00, 0xEA,0x08, 0x34,0x03, 0xA6,0x0D, 0xA9,0x08, 0xB7,0x03, 0x84,0x09,
     0x63,0x05, 0x41,0x00, 0x20,0x09, 0x0C,0x03, 0x38,0x0F, 0xE6,0x08, 0xA8,0x03, 0x2E,0x0A,
     0x37,0x06, 0x43,0x00, 0x57,0x09, 0xE5,0x02, 0x97,0x00, 0x2A,0x09, 0x9A,0x03, 0xE9,0x0A,
     0xFF,0x07, 0x48,0x00, 0xC6,0x09, 0x9D,0x02, 0xBA,0x02, 0xC7,0x09, 0x80,0x03, 0x7D,0x0C},

/*(Params.fs_H/4 <= 52.5e6)*/
    {0x6C,0x04, 0x3F,0x00, 0xD2,0x08, 0x46,0x03, 0xE5,0x0C, 0x90,0x08, 0xBE,0x03, 0x3F,0x09,
     0xFC,0x04, 0x40,0x00, 0x02,0x09, 0x21,0x03, 0x61,0x0E, 0xC3,0x08, 0xB0,0x03, 0xCE,0x09,
     0xA9,0x05, 0x42,0x00, 0x33,0x09, 0xFE,0x02, 0xB9,0x0F, 0xFD,0x08, 0xA3,0x03, 0x6E,0x0A,
     0x56,0x07, 0x46,0x00, 0x96,0x09, 0xBB,0x02, 0xEA,0x01, 0x81,0x09, 0x8B,0x03, 0xCF,0x0B},

/*else*/
    {0x39,0x04, 0x3E,0x00, 0xBF,0x08, 0x56,0x03, 0x44,0x0C, 0x7D,0x08, 0xC4,0x03, 0x0B,0x09,
     0xB0,0x04, 0x3F,0x00, 0xEA,0x08, 0x34,0x03, 0xA6,0x0D, 0xA9,0x08, 0xB7,0x03, 0x84,0x09,
     0x40,0x05, 0x41,0x00, 0x16,0x09, 0x13,0x03, 0xF2,0x0E, 0xDA,0x08, 0xAB,0x03, 0x0D,0x0A,
     0xA3,0x06, 0x44,0x00, 0x70,0x09, 0xD4,0x02, 0x25,0x01, 0x4B,0x09, 0x94,0x03, 0x42,0x0B},

};

static UINT8 IIRCodeJudgeLMD[3][64]=
{
/*(Params.fs_L/4 <= 47.5e6)*/
    {0xB0,0x04, 0x3F,0x00, 0xEA,0x08, 0x34,0x03, 0xA6,0x0D, 0xA9,0x08, 0xB7,0x03, 0x84,0x09,
     0x63,0x05, 0x41,0x00, 0x20,0x09, 0x0C,0x03, 0x38,0x0F, 0xE6,0x08, 0xA8,0x03, 0x2E,0x0A,
     0x37,0x06, 0x43,0x00, 0x57,0x09, 0xE5,0x02, 0x97,0x00, 0x2A,0x09, 0x9A,0x03, 0xE9,0x0A,
     0xFF,0x07, 0x48,0x00, 0xC6,0x09, 0x9D,0x02, 0xBA,0x02, 0xC7,0x09, 0x80,0x03, 0x7D,0x0C},

/*(Params.fs_L/4 <= 52.5e6)*/
    {0x6C,0x04, 0x3F,0x00, 0xD2,0x08, 0x46,0x03, 0xE5,0x0C, 0x90,0x08, 0xBE,0x03, 0x3F,0x09,
     0xFC,0x04, 0x40,0x00, 0x02,0x09, 0x21,0x03, 0x61,0x0E, 0xC3,0x08, 0xB0,0x03, 0xCE,0x09,
     0xA9,0x05, 0x42,0x00, 0x33,0x09, 0xFE,0x02, 0xB9,0x0F, 0xFD,0x08, 0xA3,0x03, 0x6E,0x0A,
     0x56,0x07, 0x46,0x00, 0x96,0x09, 0xBB,0x02, 0xEA,0x01, 0x81,0x09, 0x8B,0x03, 0xCF,0x0B},

/*else*/
    {0x39,0x04, 0x3E,0x00, 0xBF,0x08, 0x56,0x03, 0x44,0x0C, 0x7D,0x08, 0xC4,0x03, 0x0B,0x09,
     0xB0,0x04, 0x3F,0x00, 0xEA,0x08, 0x34,0x03, 0xA6,0x0D, 0xA9,0x08, 0xB7,0x03, 0x84,0x09,
     0x40,0x05, 0x41,0x00, 0x16,0x09, 0x13,0x03, 0xF2,0x0E, 0xDA,0x08, 0xAB,0x03, 0x0D,0x0A,
     0xA3,0x06, 0x44,0x00, 0x70,0x09, 0xD4,0x02, 0x25,0x01, 0x4B,0x09, 0x94,0x03, 0x42,0x0B},


};

ATBM2040_ERROR_e ATBM2040DrvRegDataFlushWrite(ATBM2040I2CAddr_t *pSlvAddr,UINT8 BaseAddr,UINT8 OffAddr,UINT8 *pData,UINT32 Size)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0,SizeBak = Size;
    for(i=0;i<SizeBak;i+=32)
    {
        ret |= ATBM2040I2CWrite(pSlvAddr,BaseAddr,(UINT8)(OffAddr + i),pData+i,(Size<32)?(Size):(32));
        if(Size>32)
        {
            Size -= 32;
        }
        else
        {
            Size = 0;
        }
    }
    if(Size>0)
    {
        ret |= ATBM2040I2CWrite(pSlvAddr,BaseAddr,(UINT8)(OffAddr + i),pData+i,Size);
    }
    return ret;
}

static ATBM2040_ERROR_e ATBM2040DrvBurstWrite(ATBM2040I2CAddr_t *pSlvAddr,UINT8 *pData,UINT32 Length)
{/*Length max is 45*/
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 *pBuff = NULL;
    UINT32 i = 0;

    if(Length > ATBM2040_BURST_BUFF_MAX)
    {
        Length = ATBM2040_BURST_BUFF_MAX;
    }
    pBuff = ATBM2040BurstBuff;
    pBuff[0] = (UINT8)(Length/3)|0x40; /*0x02<<5 full addr mode*/
    pBuff[Length + 1] = 0x01;
    
    pBuff++;
    for(i=0;i<Length;i++)
    {
        pBuff[i] = pData[i];
    }    

    pBuff--;
    ret |= ATBM2040DrvRegDataFlushWrite(pSlvAddr,0x18,0x80,pBuff,Length + 2);
    return ret;
}

ATBM2040_ERROR_e ATBM2040DrvRegDataBurstWrite(ATBM2040_t *pTuner,UINT8 *pData,UINT32 Length)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 i = 0,LengthBak = Length;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID))
    {
        for(i=0;i<LengthBak;i+=ATBM2040_BURST_BUFF_MAX)
        {
            ret |= ATBM2040DrvBurstWrite(pI2CAddr,pData+i,(Length<ATBM2040_BURST_BUFF_MAX)?(Length):(ATBM2040_BURST_BUFF_MAX));
            if(Length > ATBM2040_BURST_BUFF_MAX)
            {
                Length -= ATBM2040_BURST_BUFF_MAX;
            }
            else
            {
                Length = 0;
            }
        }
        if(Length > 0)
        {
            ret |= ATBM2040DrvBurstWrite(pI2CAddr,pData+i,Length);
        }
    }
    else
    {
        for(i=0;i<Length;i+=3)
        {
            ret |= ATBM2040I2CWrite(pI2CAddr,pData[i],pData[i+1], pData+i+2,1);
        }
    }
    
    return ret;
}

static ATBM2040_ERROR_e ATBM2040DrvHalfAddrBurstWrite(ATBM2040I2CAddr_t *pSlvAddr,UINT8 BaseAddr,UINT8 *pData,UINT8 Length)
{/*Length max is 46*/
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 *pBuff = NULL;
    UINT32 i = 0;

    if(Length > ATBM2040_HALF_ADDR_BURST_BUFF_MAX)
    {
        Length = ATBM2040_HALF_ADDR_BURST_BUFF_MAX;
    }
    pBuff = ATBM2040BurstBuff2;
    pBuff[0] = (UINT8)(Length/2)|0x60; /*0x03<<5 part addr mode*/
    pBuff[1] = BaseAddr;
    pBuff[Length + 2] = 0x01;
    
    pBuff += 2;
    for(i=0;i<Length;i++)
    {
        pBuff[i] = pData[i];
    }    

    pBuff -= 2;
    ret |= ATBM2040DrvRegDataFlushWrite(pSlvAddr,0x18,0x80,pBuff,Length + 3);
    return ret;
}

ATBM2040_ERROR_e ATBM2040DrvRegHalfAddrBurstWrite(ATBM2040_t *pTuner,UINT8 BaseAddr,UINT8 *pData,UINT8 Length)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 i = 0,LengthBak = Length;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)||(ATBM_LEOB_CHIP_ID == pTuner->ChipID))
    {
        for(i=0;i<LengthBak;i+=ATBM2040_HALF_ADDR_BURST_BUFF_MAX)
        {
            ret |= ATBM2040DrvHalfAddrBurstWrite(pI2CAddr,BaseAddr,pData+i,(Length<ATBM2040_HALF_ADDR_BURST_BUFF_MAX)?(Length):(ATBM2040_HALF_ADDR_BURST_BUFF_MAX));
            if(Length > ATBM2040_HALF_ADDR_BURST_BUFF_MAX)
            {
                Length -= ATBM2040_HALF_ADDR_BURST_BUFF_MAX;
            }
            else
            {
                Length = 0;
            }
        }
        if(Length > 0)
        {
            ret |= ATBM2040DrvHalfAddrBurstWrite(pI2CAddr,BaseAddr,pData+i,Length);
        }
    }
    else
    {
        for(i=0;i<Length;i+=2)
        {
            ret |= ATBM2040I2CWrite(pI2CAddr,BaseAddr,pData[i], &pData[i+1],1);
        }
    }
    
    return ret;
}

ATBM2040_ERROR_e ATBM2040DrvIIRCoefJudge(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    UINT8 *pData = NULL;

#ifdef ATBM2040_CHIP_DEBUG_OPEN
    if(ATBM_LEOG_CHIP_ID != pTuner->ChipID)
    {
        if(0 == pTuner->LNAGainMD)
        {/* LNAGainMode B */
            ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x71, 0x7C); /*thr_lna_gain1  */
        }
        else
        {/* LNAGainMode A */
            ret |= ATBM2040RegWrite(pI2CAddr,0x1A,0x71, 0x00); /*thr_lna_gain1  */
        }
    }   
#endif
    if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
    {
        UINT8 Reg2200 = 0x7F, Reg1638 = 0x00;
        if((pTuner->FreqKHz >= 230000)&&(pTuner->FreqKHz <= 237499))
        {
            if((ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)
                ||(ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
                ||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode))
            {
                Reg2200 = 0x6F;
            }
            else
            {
                Reg2200 = 0x61;
            }
            Reg1638 = 0xF6;
        }
        else
        {
            if((ATBM2040_SIGNAL_MODE_DTMB == pTuner->SignalMode)
                ||(ATBM2040_SIGNAL_MODE_DVBT == pTuner->SignalMode)
                ||(ATBM2040_SIGNAL_MODE_ATSC == pTuner->SignalMode))
            {
                Reg2200 = 0x7F;
            }
            else
            {
                Reg2200 = 0x61;
            }
        }
        ret |= ATBM2040RegWrite(pI2CAddr,0x22,0x00, Reg2200); /* params_use_leod */
        ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x38, Reg1638); /* params_thr_comp_lo_sel */
    }
    else if((ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
    {
        if(pTuner->FreqKHz < 700000)
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x24, 0xFF); /* maximum time for judge lock */
        }
        else
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x24, 0x0D); /* maximum time for judge lock */
        }
    }
    else if((ATBM_LEOE_CHIP_ID == pTuner->ChipID)||(ATBM_LEOF_CHIP_ID == pTuner->ChipID))
    {
        if(pTuner->FreqKHz < 760000)
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x24, 0xFF); /* maximum time for judge lock */
        }
        else
        {
            ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x24, 0x0D); /* maximum time for judge lock */
        }
        if(ATBM_LEOF_CHIP_ID == pTuner->ChipID)
        {
            if((ATBM2040_SIGNAL_MODE_ATV == pTuner->SignalMode)&&(pTuner->FreqKHz == 768000))
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x16, 0x01);
            }
            else
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x0E,0x16, pTuner->DSPClkSel);
            }
        }
    }



    if(!ATBM2040DrvIIRCoefJudgeStateGet())
    {
        return ret;
    }
    if(pTuner->HMDAdcClkHz <= 47500000*8)
    {
        pData = IIRCodeJudgeHMD[0];
    }
    else if(pTuner->HMDAdcClkHz <= 52500000*8)
    {
        pData = IIRCodeJudgeHMD[1];
    }
    else
    {
        pData = IIRCodeJudgeHMD[2];
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x19,0x02,pData,64);

    if(pTuner->LMDAdcClkHz <= 47500000*8)
    {
        pData = IIRCodeJudgeLMD[0];
    }
    else if(pTuner->LMDAdcClkHz <= 52500000*8)
    {
        pData = IIRCodeJudgeLMD[1];
    }
    else
    {
        pData = IIRCodeJudgeLMD[2];
    }
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x19,0x42,pData,48);/*0x71-0x42+1*/
    ret |= ATBM2040DrvRegDataFlushWrite(pI2CAddr,0x19,0x82,pData+48,16);/*0x91-0x82+1*/

    return ret;
}

ATBM2040_ERROR_e ATBM2040DrvLteTargetSet(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 Target = 0;
    UINT8 DectNum = 0;
    UINT8 BBPow = 0;
    UINT8 FEFDect = 0;
    UINT8 Reg1742 = 0;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    
    if((pTuner->FreqKHz >= 680000)&&(pTuner->FreqKHz <= 700000))
    {
        Target = 0x6C;
        DectNum = 0x05;
        BBPow = 0xFF;
        FEFDect = 0x00;
        Reg1742 = 0x01;
    }
    else if((pTuner->FreqKHz >= 780000)&&(pTuner->FreqKHz <= 800000))
    {
        Target = 0x73;
        DectNum = 0x08;
        BBPow = 0xF0;
        FEFDect = 0x00;
        Reg1742 = 0x01;
    }
    else
    {
        Target = 0x70;
        DectNum = 0x08;
        BBPow = 0xC0;
        if(ATBM2040_FEF_IGNORE != pTuner->Config.FEFMode)
        {
            FEFDect = 0x01;
        }
        else
        {
            FEFDect = 0x00;
        }
        Reg1742 = 0x00;
    }
    ret |= ATBM2040RegWrite(pI2CAddr,0x19,0xBD, Target); /*params_rssi_lna_out_aci_status_4_lte_nplusm  */
    ret |= ATBM2040RegWrite(pI2CAddr,0x19,0xB7, DectNum); /*params_lte_dect_num  */
    ret |= ATBM2040RegWrite(pI2CAddr,0x19,0x94, BBPow); /*params_bb_power_alpha_digital[7:0]  */

    ret |= ATBM2040RegWrite(pI2CAddr,0x16,0x00, FEFDect); /*params_add_fef_detect */
    ret |= ATBM2040RegWrite(pI2CAddr,0x17,0x42, Reg1742); /*params_ad_notch_spec_analysis_bypass */

    return ret;
}


ATBM2040_ERROR_e ATBM2040DrvRSSICalibration(ATBM2040_t *pTuner)
{
    ATBM2040I2CAddr_t *pI2CAddr;
    UINT8 Val = 0,Val0022 = 0,CfgDone = 0;
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT32 n = 0;
    SINT8 IFVGAGain = 0;
    SINT16 RFPower = 0;
    SINT16 RFPowerTmp[3] = {0};

    pI2CAddr = &pTuner->Config.I2CParam;
    ret |= ATBM2040RegRead(pI2CAddr,0x00,0x0D, &CfgDone); /*sw_cfg_done*/

    if((ATBM_LEOB_CHIP_ID != pTuner->ChipID)||(0x07 != CfgDone))
    {
        return ATBM2040_NO_ERROR;
    }

    ATBM2040Delay(60000);
    ret |= ATBM2040RegRead(pI2CAddr,0x14,0xC2,&Val);  /*S(7,0)*/
    IFVGAGain = Val&0x7F;
    IFVGAGain <<= 1;
    IFVGAGain >>= 1;
    if(IFVGAGain < 32)
    {
        ret |= ATBM2040DrvRegLatch(pI2CAddr,TRUE);
        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xD0,&Val);
        RFPower = Val;
        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xD1,&Val);
        ret |= ATBM2040DrvRegLatch(pI2CAddr,FALSE);
        RFPower |= ((Val&0x0F)<<8);
        RFPower <<= 4;
        RFPower >>= 8;
        pTuner->RFPower = RFPower;
        return ret;
    }
    ret |= ATBM2040RegRead(pI2CAddr,0x00,0x22,&Val0022);

    for(n=0;n<3;n++)
    {
        Val0022 ^= 0x01;
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x22, Val0022);
        Val0022 ^= 0x01;
        ret |= ATBM2040RegWrite(pI2CAddr,0x00,0x22, Val0022);
        ATBM2040Delay(60000);

        ret |= ATBM2040DrvRegLatch(pI2CAddr,TRUE);
        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xD0,&Val);
        RFPowerTmp[n] = Val;
        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xD1,&Val);
        ret |= ATBM2040DrvRegLatch(pI2CAddr,FALSE);
        RFPowerTmp[n] |= ((Val&0x0F)<<8);
        RFPowerTmp[n] <<= 4;
        RFPowerTmp[n] >>= 8;

        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xC2,&Val);  /*S(7,0)*/
        IFVGAGain = Val&0x7F;
        IFVGAGain <<= 1;
        IFVGAGain >>= 1;
        if(IFVGAGain < 32)
        {
            pTuner->RFPower = RFPowerTmp[n];
            return ret;
        }
    }

    pTuner->RFPower = RFPowerTmp[0];
    for(n=0;n<3;n++)
    {
        if(RFPowerTmp[n] > pTuner->RFPower)
        {
            pTuner->RFPower = RFPowerTmp[n];
        }
    }

    return ret;
}

ATBM2040_ERROR_e ATBM2040DrvProcess(ATBM2040_t *pTuner)
{
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    ATBM2040I2CAddr_t *pI2CAddr = &pTuner->Config.I2CParam;
    
    if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        UINT8 selection_finish = 0, selection = 0;
        UINT8 curAdcDiv = 0, HMDAdcDiv = 0, LMDAdcDiv = 0;

        ret |= ATBM2040RegRead(pI2CAddr,0x14,0xAC,&selection_finish);
        if(0x01 == selection_finish)
        {
            ret |= ATBM2040RegRead(pI2CAddr,0x14,0xAD,&selection);
            ret |= ATBM2040RegRead(pI2CAddr,0x12,0x05,&curAdcDiv);

            ret |= ATBM2040RegRead(pI2CAddr,0x16,0x42,&LMDAdcDiv);
            ret |= ATBM2040RegRead(pI2CAddr,0x16,0x43,&HMDAdcDiv);
            if((0x00 == selection)&&(curAdcDiv != HMDAdcDiv))
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x05,HMDAdcDiv);
            }
            else if((0x01 == selection)&&(curAdcDiv != LMDAdcDiv))
            {
                ret |= ATBM2040RegWrite(pI2CAddr,0x12,0x05,LMDAdcDiv);
            }
            
        }
    }
    return ret;
}


#ifdef ATBM2040_CHIP_DEBUG_OPEN
UINT8 ATBM2040DrvSoftwareVerGet(void)
{
    return ATBM2040Ver;
}
ATBM2040ADCDivider_t *ATBM2040DrvADCDividerGet(UINT32 FreqKHz,BOOL HMD)
{
    UINT32 i = 0;
    UINT32 loopNum = 0;
    ATBM2040ADCDivider_t *pDivider = NULL;
    if((ATBM_LEOG_CHIP_ID == ATBM2040ChipID)||(ATBM_LEOF_CHIP_ID == ATBM2040ChipID)
        ||(ATBM_LEOE_CHIP_ID == ATBM2040ChipID))
    {
        pDivider = LeoEADCDividerHMD;
        if(HMD)
        {
            pDivider = LeoEADCDividerHMD;
            loopNum = ATBM2040_LEOE_ADC_DIVIDER_HMD_CNT;
        }
        else
        {
            pDivider = LeoEADCDividerLMD;
            loopNum = ATBM2040_LEOE_ADC_DIVIDER_LMD_CNT;
        }
    }
    else
    {
        pDivider = ADCDividerHMD;
        if(HMD)
        {
            pDivider = ADCDividerHMD;
            loopNum = ATBM2040_ADC_DIVIDER_HMD_CNT;
        }
        else
        {
            pDivider = ADCDividerLMD;
            loopNum = ATBM2040_ADC_DIVIDER_LMD_CNT;
        }
    }
    for(i=0;i<loopNum;i++)
    {
        if((pDivider[i].FreqStart < FreqKHz)&&(FreqKHz <= pDivider[i].FreqEnd))
        {
            return (pDivider+i);
        }
    }

    pDivider = pDivider + (loopNum-1);

    return pDivider;
}

void ATBM2040DrvMixDivGet(ATBM2040_t *pTuner,UINT32 *pNMix,UINT32 *pNLO)
{
    ATBM2040DrvNLOMixer(pTuner);
    if((ATBM_LEOG_CHIP_ID == pTuner->ChipID)
        ||(ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
    {
        if(pTuner->HighMD)
        {
            *pNMix = pTuner->pNLOMixerHMD->NMixer;
            *pNLO = pTuner->pNLOMixerHMD->NLO;
        }
        else
        {
            *pNMix = pTuner->pNLOMixerLMD->NMixer;
            *pNLO = pTuner->pNLOMixerLMD->NLO;
        }
    }
    else
    {
        *pNMix = pTuner->pNLOMixer->NMixer;
        *pNLO = pTuner->pNLOMixer->NLO;
    }

}


void ATBM2040DrvPLLFreqGet(UINT32 FreqKHz,UINT32 MixIFKHz,double *pHLOFreq,double *pLLOFreq)
{
    ATBM2040NLOMixer_t *pNLOMixer = NULL;
    UINT32 IFKHz = MixIFKHz;
    UINT32 CenterFreqKHz = FreqKHz; /* Frequency calculation should be less KHz */
    UINT32 i = 0;
    UINT32 MixDivCnt = 0;

#define MIXER_DIVIDER_SEARCH_()     for(i=0;i<MixDivCnt;i++)\
    {\
        if((pNLOMixer[i].FreqStart <= FreqKHz)&&(FreqKHz <= pNLOMixer[i].FreqEnd))\
        {\
            break;\
        }\
    }\
    if(i >= MixDivCnt)\
    {\
        i = MixDivCnt-1;\
    }

    if((ATBM_LEOG_CHIP_ID == ATBM2040ChipID)
        ||(ATBM_LEOF_CHIP_ID == ATBM2040ChipID)||(ATBM_LEOE_CHIP_ID == ATBM2040ChipID))
    {
        pNLOMixer = NLOMixerLeoEHMD;
        MixDivCnt = ATBM2040_NLO_MIXER_LEOE_HMD_CNT;
        MIXER_DIVIDER_SEARCH_();
        pNLOMixer = (pNLOMixer + i);
        *pHLOFreq = (CenterFreqKHz + IFKHz) * pNLOMixer->NLO * pNLOMixer->NMixer /1000.0;/*  NLO *    NMixer < 256 */

        pNLOMixer = NLOMixerLeoELMD;
        MixDivCnt = ATBM2040_NLO_MIXER_LEOE_LMD_CNT;
        MIXER_DIVIDER_SEARCH_();
        pNLOMixer = (pNLOMixer + i);
        *pLLOFreq = (CenterFreqKHz - IFKHz) * pNLOMixer->NLO * pNLOMixer->NMixer /1000.0;/*  NLO *    NMixer < 256 */
    }
    else
    {
        pNLOMixer = NLOMixer;
        for(i=0;i<ATBM2040_NLO_MIXER_CNT;i++)
        {
            if((pNLOMixer->FreqStart <= FreqKHz)&&(FreqKHz <= pNLOMixer->FreqEnd))
            {
                break;
            }
            pNLOMixer++;
        }
        if(i >= ATBM2040_NLO_MIXER_CNT)
        {
            pNLOMixer = &NLOMixer[ATBM2040_NLO_MIXER_CNT-1];
        }
        *pHLOFreq = (CenterFreqKHz + IFKHz) * pNLOMixer->NLO * pNLOMixer->NMixer /1000.0;/*  NLO *    NMixer < 256 */
        *pLLOFreq = (CenterFreqKHz - IFKHz) * pNLOMixer->NLO * pNLOMixer->NMixer /1000.0;/*  NLO *    NMixer < 256 */
    }
}

ATBM2040AgcPowerTarget_t* ATBM2040DrvPowerTargetListGet(ATBM2040_t *pTuner)
{
    switch(pTuner->Config.Mode)
    {
        case ATBM2040_SIGNAL_MODE_DTMB:
        case ATBM2040_SIGNAL_MODE_ATSC:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                return LeoGAgcPowerTargetDTMB;
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                return LeoEAgcPowerTargetDTMB;
            }
            else if((ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
            {
                return LeoCAgcPowerTargetDTMB;
            }
            else
            {
                return AgcPowerTargetDTMB;
            }
            break;
        case ATBM2040_SIGNAL_MODE_DVBT:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                return LeoGAgcPowerTargetDVBT;
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                return LeoEAgcPowerTargetDVBT;
            }
            else if((ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
            {
                return LeoCAgcPowerTargetDVBT;
            }
            else
            {
                return AgcPowerTargetDVBT;
            }
            break;
        case ATBM2040_SIGNAL_MODE_DVBC:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                return LeoGAgcPowerTargetDVBC;
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                return LeoEAgcPowerTargetDVBC;
            }
            else
            {
                return AgcPowerTargetDVBC;
            }
            break;
        case ATBM2040_SIGNAL_MODE_ATV:
            if(ATBM_LEOG_CHIP_ID == pTuner->ChipID)
            {
                return LeoGAgcPowerTargetATV;
            }
            else if((ATBM_LEOF_CHIP_ID == pTuner->ChipID)||(ATBM_LEOE_CHIP_ID == pTuner->ChipID))
            {
                return LeoEAgcPowerTargetATV;
            }
            else if((ATBM_LEOC_CHIP_ID == pTuner->ChipID)||(ATBM_LEOD_CHIP_ID == pTuner->ChipID))
            {
                return LeoCAgcPowerTargetATV;
            }
            else
            {
                return AgcPowerTargetATV;
            }
            break;
        default:
            break;
    }
    return NULL;
}

#endif


/************************************************************
*Description: Print configs of ATBM2040 SDK
*************************************************************/
void ATBM2040CfgPrint(ATBM2040_t *pTuner)
{
#if ATBM2040_DEBUG_PRINT
    ATBM2040_ERROR_e ret = ATBM2040_NO_ERROR;
    UINT8 Val = 0;
    ATBM2040I2CAddr_t *pI2CAddr = NULL;
    SINT8 *SignalMode[ATBM2040_SIGNAL_MODE_MAX] = {(SINT8 *)"DTMB",(SINT8 *)"DVBT",(SINT8 *)"DVBC",(SINT8 *)"ANALOG"};

	(void)ret;
	(void)Val;
	(void)pI2CAddr;
	(void)SignalMode;

    pI2CAddr = &pTuner->Config.I2CParam;
    ATBM2040Print(("------------------ATBM2040 configurations:------------------\n"));

    ret = ATBM2040RegRead(pI2CAddr,0x00,0x00, &Val);
    if(ATBM2040_NO_ERROR != ret)
    {
        ATBM2040Print(("[ATBM2040] ChipID read fail!\n"));
    }
    ATBM2040Print(("[ATBM2040] ChipID:0x%02X,SDK Version:%d\n",Val,ATBM2040Ver));

    ATBM2040Print(("[ATBM2040] I2CAddr: 0x%X\n",pTuner->Config.I2CParam.I2CSlaveAddr));
    ATBM2040Print(("[ATBM2040] SignalMode: %s\n",
                    (pTuner->Config.Mode<ATBM2040_SIGNAL_MODE_MAX)?(SignalMode[pTuner->Config.Mode]):((SINT8 *)"Invalid")));
    ATBM2040Print(("[ATBM2040] IFOutFreqHz: %d Hz\n",pTuner->Config.DtvIFOut.IFOutFreqHz));

    ret = ATBM2040I2CRead(pI2CAddr,0x10,0x03, &Val,1);
    if(ATBM2040_NO_ERROR != ret)
    {
        ATBM2040Print(("[ATBM2040] DAC gain read fail!\n"));
    }
    ATBM2040Print(("[ATBM2040] IFOutLevel: 0x%02X\n",Val));

    ATBM2040Print(("[ATBM2040] ClkOut: %s\n",(pTuner->Config.ClkOut.ClkOutEnable==ATBM2040_CLK_OUT_ENABLE)?("Enable"):("Disable")));

    ATBM2040Print(("==============================================================\n"));
#else
    (void)pTuner;
#endif
}


