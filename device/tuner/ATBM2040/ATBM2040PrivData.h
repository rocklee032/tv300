/********************************************************************************************************
File:ATBM2040PrivData.h
Description:
	ATBMTuner2040 internal data.

(C) Copyright 2016-2030, AltoBeam, Inc. All rights reserved.

History:

*********************************************************************************************************/
#ifndef __ATBMTUNER2040DATA_H__    
#define __ATBMTUNER2040DATA_H__

#if ATBM2040_GAIN_PHASE_COMPENSATION
int ATBM2040LNAPhase[25][32]=
{/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:LNA_phase_table*/
	/*n = round (f/40e6);if(n<1) n=1;end
		params_LNA_phase_vari_table2= LNA_phase_vari_table (n, :);*/
	{ 5,	 3,	 3,	 2,	 1,	  8,	 2,	 1,	 1,	 0,	0,	-1,	 1,	 1,	0,	-1,	  0,	 75,	 5,	 5,	 -10,	 3,	 6,	-16,	 3,	 6,	 -6,	 5,	 5,	 -6,	3,	 3},
	{10,	 9,	 6,	 6,	 3,	 16,	 5,	 3,	 2,	 1,	1,	 0,	 2,	 1,	1,	 0,	 -2,	 60,	 8,	10,	 -17,	 8,	10,	-14,	 8,	10,	-10,	 8,	 9,	-11,	7,	 8},
	{15,	13,	10,	 7,	 6,	 24,	 7,	 6,	 3,	 1,	1,	 1,	 3,	 2,	1,	 0,	 -2,	 67,	13,	15,	 -25,	11,	16,	-14,	11,	16,	-16,	13,	14,	-17,	10,	11},
	{20,	17,	13,	10,	 7,	 28,	 8,	 7,	 5,	 2,	1,	 0,	 6,	 3,	1,	-1,	 -2,	 79,	16,	19,	 -31,	16,	19,	-13,	16,	20,	-19,	15,	18,	-23,	14,	16},
	{27,	23,	18,	15,	10,	 36,	13,	 9,	 6,	 3,	2,	 0,	 7,	 3,	2,	-1,	 -3,	 85,	20,	24,	 -33,	19,	25,	-11,	20,	24,	-24,	19,	22,	-28,	17,	19},
	{33,	26,	22,	18,	13,	 52,	15,	11,	 7,	 5,	2,	 2,	 8,	 6,	1,	 0,	 -3,	 91,	24,	30,	 -39,	23,	30,	-10,	23,	30,	-30,	23,	26,	-34,	19,	22},
	{35,	31,	25,	19,	15,	 63,	17,	13,	 9,	 6,	2,	 3,	 9,	 6,	2,	-1,	 -5,	102,	26,	34,	 -47,	27,	33,	-15,	27,	34,	-34,	26,	30,	-40,	23,	24},
	{40,	33,	27,	22,	17,	 73,	19,	15,	 9,	 7,	2,	 3,	10,	 7,	2,	-1,	 -5,	113,	31,	39,	 -56,	31,	39,	-20,	30,	39,	-39,	28,	35,	-47,	25,	27},
	{42,	36,	30,	24,	18,	 83,	22,	16,	11,	 7,	3,	 2,	13,	 7,	2,	-1,	 -6,	125,	35,	41,	 -63,	34,	42,	-27,	34,	42,	-43,	33,	38,	-52,	28,	30},
	{46,	39,	33,	26,	19,	 92,	24,	18,	11,	 8,	3,	 3,	13,	 8,	3,	-1,	 -8,	139,	38,	46,	 -69,	38,	46,	-34,	38,	46,	-47,	35,	41,	-57,	30,	33},
	{48,	41,	34,	28,	22,	101,	26,	19,	14,	 8,	5,	 2,	15,	 8,	3,	-2,	 -7,	150,	41,	50,	 -77,	41,	49,	-41,	41,	49,	-50,	38,	46,	-64,	33,	35},
	{50,	43,	36,	30,	23,	112,	28,	22,	14,	10,	3,	 3,	15,	 9,	3,	-1,	 -9,	163,	44,	53,	 -84,	44,	52,	-48,	44,	52,	-53,	41,	48,	-68,	35,	38},
	{51,	44,	39,	32,	24,	122,	31,	23,	16,	 9,	5,	 3,	16,	10,	3,	-2,	 -9,	174,	48,	57,	 -91,	48,	57,	-55,	47,	57,	-58,	44,	51,	-74,	38,	40},
	{52,	46,	40,	33,	26,	132,	32,	25,	16,	11,	5,	 3,	17,	11,	3,	-2,	-11,	188,	50,	60,	 -97,	50,	59,	-60,	50,	60,	-61,	47,	55,	-79,	40,	42},
	{52,	48,	41,	34,	27,	142,	34,	26,	18,	11,	5,	 3,	19,	11,	3,	-2,	-11,	198,	53,	63,	-102,	53,	63,	-66,	53,	63,	-64,	50,	56,	-83,	42,	44},
	{52,	49,	42,	35,	27,	152,	36,	28,	19,	11,	6,	 3,	20,	13,	3,	-2,	-13,	209,	57,	65,	-107,	56,	66,	-71,	56,	66,	-67,	52,	59,	-89,	44,	46},
	{52,	49,	43,	36,	28,	163,	39,	30,	20,	13,	6,	 5,	22,	13,	5,	-3,	-13,	220,	59,	68,	-112,	59,	68,	-75,	59,	67,	-68,	55,	60,	-92,	47,	48},
	{52,	49,	44,	36,	30,	174,	41,	31,	20,	14,	6,	 7,	22,	14,	6,	-3,	-14,	231,	61,	71,	-116,	61,	71,	-77,	61,	71,	-72,	57,	64,	-97,	48,	49},
	{51,	49,	44,	38,	30,	187,	42,	32,	23,	14,	7,	 8,	23,	15,	6,	-3,	-14,	239,	65,	73,	-121,	65,	73,	-80,	64,	73,	-74,	59,	66,	-100,	49,	51},
	{51,	49,	44,	38,	31,	197,	44,	34,	23,	15,	7,	10,	25,	15,	6,	-3,	-14,	248,	66,	75,	-123,	67,	74,	-81,	66,	75,	-75,	61,	67,	-104,	51,	52},
	{50,	49,	44,	38,	31,	209,	47,	34,	25,	16,	7,	14,	25,	16,	6,	-2,	-15,	255,	69,	77,	-126,	68,	77,	-82,	68,	77,	-76,	63,	69,	-107,	52,	53},
	{49,	49,	43,	39,	31,	222,	48,	36,	25,	16,	8,	17,	27,	16,	7,	-3,	-14,	261,	71,	79,	-129,	72,	79,	-81,	71,	79,	-77,	65,	71,	-110,	53,	55},
	{49,	47,	44,	38,	31,	234,	49,	39,	26,	17,	7,	24,	27,	17,	7,	-2,	-15,	262,	74,	81,	-131,	73,	81,	-81,	73,	81,	-80,	67,	73,	-115,	56,	56},
	{48,	47,	43,	38,	30,	248,	51,	39,	28,	17,	8,	28,	28,	18,	7,	-2,	-14,	259,	75,	82,	-132,	75,	82,	-80,	75,	82,	-80,	68,	74,	-117,	57,	57},
	{47,	46,	42,	38,	30,	262,	52,	40,	30,	18,	8,	35,	28,	19,	7,	-2,	-14,	256,	77,	83,	-134,	77,	83,	-79,	77,	83,	-81,	71,	74,	-119,	58,	58}
};

int ATBM2040LNAGain[25][32]=
{/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:LNA_gain_vari_table, value*32 according to S(8,5)*/
	/*n = round (f/40e6);if(n<1) n=1;end
		params_lna_gain_vari_table = LNA_gain_vari_table (n, :);*/
	{ -8,  -4,  -4,  -4,  -4, -20,  -4, -4,  0,  0, 0, -8, -4,  0, 0, 0, 0,   0, 16,   8, -36, 16,   8, -32, 16,   8, -20, 12,   0, 16,   0, -12}, 
	{ -8,  -4,  -4,  -4,  -4, -20,  -4,  0,  0,  0, 0, -8, -4,  0, 0, 0, 0,  -4, 16,   8, -36, 16,   8, -32, 16,   8, -16, 12,   0, 16,   0, -12}, 
	{ -8,  -4,  -4,  -4,  -4, -20,  -4, -4,  0,  0, 0, 12, -4,  0, 0, 0, 0,  -4, 16,   8, -36, 16,   4, -28, 16,   4, -16, 12,   0, 16,   0, -12}, 
	{ -8,  -4,  -4,  -4,  -4, -20,  -4, -4,  0,  0, 0, 12, -4,  0, 0, 0, 0,  -8, 16,   4, -32, 16,   4, -28, 16,   4, -16, 12,   0, 16,   0, -12}, 
	{ -8,  -8,  -4,  -4,  -4, -16,  -4,  0,  0,  0, 0, -8, -4,  0, 0, 0, 0, -12, 16,   4, -32, 16,   4, -28, 16,   4, -16,  8,   0, 16,   0, -12}, 
	{-12,  -8,  -4,  -4,  -4, -16,  -4, -4,  0,  0, 0, -8, -4,  0, 0, 0, 0, -12, 12,   4, -32, 12,   4, -32, 12,   4, -16,  8,   0, 20,   0, -12}, 
	{-12,  -8,  -8,  -4,  -4, -20,  -4, -4,  0,  0, 0, -8, -4,  0, 0, 0, 0, -12, 12,   4, -32, 12,   4, -32, 12,   4, -16,  8,   0, 20,   0, -12}, 
	{-16,  -8,  -8,  -4,  -4, -20,  -4, -4,  0,  0, 0, -8, -4,  0, 0, 0, 0, -16, 12,   4, -32, 12,   4, -36, 12,   4, -16,  8,  -4, 20,   0, -16}, 
	{-16, -12,  -8,  -4,  -4, -20,  -8, -4,  0,  0, 0, -8, -4,  0, 0, 0, 0, -16, 12,   0, -32, 12,   0, -36, 12,   0, -12,  8,  -4, 20,   0, -16}, 
	{-20, -12,  -8,  -8,  -4, -20,  -8, -4,  0,  0, 0, -8, -4,  0, 0, 0, 0, -20, 12,   0, -32, 12,   0, -36, 12,   0, -12,  8,  -4, 20,  -4, -16}, 
	{-20, -12,  -8,  -8,  -4, -20,  -8, -4, -4,  0, 0, -8, -4,  0, 0, 0, 0, -24, 12,   0, -28, 12,   0, -36, 12,   0, -12,  8,  -4, 24,  -4, -16}, 
	{-20, -16, -12,  -8,  -8, -20,  -8, -4,  0,  0, 0, -8, -4,  0, 0, 0, 0, -28, 12,   0, -28, 12,   0, -36, 12,   0,  -8,  8,  -8, 24,  -4, -16}, 
	{-24, -16, -12,  -8,  -8, -24,  -8, -4, -4,  0, 0, -8, -4,  0, 0, 0, 0, -28,  8,  -4, -24,  8,  -4, -32,  8,  -4,  -8,  4,  -8, 24,  -4, -16}, 
	{-24, -16, -12,  -8,  -8, -24,  -8, -4, -4,  0, 0, -8, -4,  0, 0, 0, 0, -36,  8,  -4, -24,  8,  -4, -32,  8,  -4,  -8,  4,  -8, 28,  -4, -20}, 
	{-28, -20, -16, -12,  -8, -24,  -8, -4, -4,  0, 0, -4, -4,  0, 0, 0, 0, -40,  8,  -4, -20,  8,  -4, -32,  8,  -4,  -4,  4,  -8, 28,  -4, -20}, 
	{-28, -20, -16, -12,  -8, -24,  -8, -4, -4,  0, 0, -4, -4, -4, 0, 0, 0, -44,  8,  -8, -20,  8,  -8, -28,  8,  -8,  -4,  4, -12, 28,  -8, -20}, 
	{-28, -24, -16, -12,  -8, -28,  -8, -4, -4,  0, 0, -4, -4,  0, 0, 0, 0, -48,  8,  -8, -16,  8,  -8, -28,  8,  -8,   0,  4, -12, 32,  -8, -20}, 
	{-32, -24, -20, -12, -12, -28,  -8, -4, -4,  0, 0,  0, -4,  0, 0, 0, 0, -56,  4,  -8, -16,  4,  -8, -24,  4,  -8,   0,  0, -12, 32,  -8, -20}, 
	{-32, -24, -20, -16, -12, -28, -12, -4, -4,  0, 0,  0, -4, -4, 0, 0, 0, -60,  4,  -8, -12,  4,  -8, -24,  4,  -8,   0,  0, -12, 32,  -8, -24}, 
	{-32, -24, -20, -16, -12, -32, -12, -4, -4, -4, 0,  4, -4, -4, 0, 0, 0, -68,  4, -12, -12,  4, -12, -20,  4, -12,   4,  0, -16, 36,  -8, -24}, 
	{-36, -28, -20, -16, -12, -32, -12, -8, -4, -4, 0,  4, -4, -4, 0, 0, 0, -76,  4, -12,  -8,  4, -12, -20,  4, -12,   4,  0, -16, 36,  -8, -24}, 
	{-36, -28, -24, -16, -16, -36, -12, -8, -4, -4, 0,  4, -4, -4, 0, 0, 0, -88,  0, -12,  -8,  0, -12, -20,  0, -12,   8,  0, -16, 40, -12, -24}, 
	{-36, -28, -24, -20, -16, -36, -12, -8, -4, -4, 0,  8, -8, -4, 0, 0, 0, -96,  0, -16,  -4,  0, -16, -16,  0, -16,   8, -4, -20, 40, -12, -24}, 
	{-36, -32, -24, -20, -16, -40, -12, -8, -4, -4, 0,  8, -8, -4, 0, 0, 0, 104,  0, -16,  -4,  0, -16, -16,  0, -16,  12, -4, -20, 40, -12, -28}, 
	{-40, -32, -24, -20, -16, -40, -12, -8, -4, -4, 0,  8, -8, -4, 0, 0, 0, 116,  0, -16,   0,  0, -16, -16,  0, -16,  12, -4, -20, 44, -12, -28}	
};

int ATBM2040RTFPhase[12][5]=
{/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:RTF_phase_table*/
	/*n = round (f/40e6);if(n<1)   n=1;end
		if (Params.freq_path==0)
		    params_RF_VGA1_phase_vari_table2= RTF_phase_table (n, :);
		else
		params_RF_VGA1_phase_vari_table2=RF_VGA1 2_phase_table (n,:);
		end
		params_RF_VGA2_phase_vari_table2= RF_VGA1 2_phase_table (n,:);
	*/
	{ 4,  5,  4,  7, 0}, 
	{ 8, 10,  8, 13, 0}, 
	{11, 14,  7, 21, 0}, 
	{15, 18, 15, 24, 0}, 
	{18, 23, 18, 30, 0}, 
	{22, 27, 22, 34, 0}, 
	{25, 30, 25, 38, 0}, 
	{28, 34, 28, 41, 0}, 
	{28, 38, 30, 46, 0}, 
	{34, 41, 33, 48, 0}, 
	{36, 44, 36, 50, 0}, 
	{39, 46, 38, 51, 0}
};

int ATBM2040RFVGA12Phase[25][5]=
{/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:RF_VGA1 2_phase_table*/
	/*n = round (f/40e6);if(n<1)   n=1;end
		if (Params.freq_path==0)
		    params_RF_VGA1_phase_vari_table2= RTF_phase_table (n, :);
		else
		params_RF_VGA1_phase_vari_table2=RF_VGA1 2_phase_table (n,:);
		end
		params_RF_VGA2_phase_vari_table2= RF_VGA1 2_phase_table (n,:);
	*/
	{ 4,  3,  2,  1,  0}, 
	{ 9,  7,  4,  3,  1}, 
	{13, 10,  6,  4,  1}, 
	{18, 13,  8,  5,  2}, 
	{22, 16, 10,  7,  2}, 
	{26, 20, 13,  8,  3}, 
	{30, 23, 15,  9,  3}, 
	{35, 26, 17, 10,  3}, 
	{39, 29, 19, 12,  4}, 
	{42, 32, 21, 13,  4}, 
	{46, 35, 23, 14,  4}, 
	{50, 38, 25, 16,  5}, 
	{53, 41, 27, 17,  5}, 
	{56, 44, 29, 18,  6}, 
	{60, 47, 31, 19,  6}, 
	{62, 49, 31, 22,  6}, 
	{65, 52, 34, 22,  7}, 
	{68, 54, 36, 23,  7}, 
	{71, 57, 38, 25,  7}, 
	{73, 59, 40, 26,  8}, 
	{75, 62, 42, 27,  9}, 
	{77, 64, 44, 28,  9}, 
	{79, 66, 45, 29,  9}, 
	{81, 68, 47, 31, 10}, 
	{82, 70, 49, 32, 10}
};

/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:IF_VGA_phase_table*/
int ATBM2040IFVGAPhase[20] = {1, 2, -4, 2, 2, -4, 3, 2, -4, 2, 2, -4, 2, 0, -4, 2, 3, -3, 4, -2};

int ATBM2040RTFGain[12][5]=
{/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:RTF_gain_vari_table, value*32 according to S(8,5)*/
	{  0,  0,  0,  8, 0}, 
	{-36, 36,  0,  8, 0},
	{	 0,  0,  0,  8, 0},
	{	 0,  0,  0,  4, 0},
	{	 0,  0,  0,  4, 0},
	{	 0,  0,  0,  4, 0},
	{	-4,  0,  0,  4, 0},
	{	-4, -4,  0,  0, 0},
	{	-4, -4, -4,  0, 0},
	{	-4, -4, -4,  0, 0},
	{	-4, -4, -4, -4, 0},
	{	-4, -4, -4, -4, 0}
};

int ATBM2040RFVGA12Gain[25][5]=
{/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:RF_VGA12_gain_vari_table, value*32 according to S(8,5)*/
	{  4,  4,  4,  8, -8}, 
	{  4,  4,  4,  8, -8},
	{  4,  4,  4,  8, -8},
	{  4,  4,  4,  8, -8},
	{-12,  4,  4,  8, -8},
	{  4,  4,  4,  8, -8},
	{  0,  4,  4,  8, -8},
	{  0,  4,  4,  8, -8},
	{  0,  4,  0, 12, -8},
	{  0,  0,  4,  8, -8},
	{  0,  0,  4,  8, -8},
	{ -4,  0,  4,  8, -8},
	{ -4,  0,  0,  8, -8},
	{ -4,  0,  0,  8, -8},
	{ -4,  0,  0,  8, -8},
	{ -8,  0, -8, 20, -8},
	{ -8, -4,  0,  8, -8},
	{ -8, -4,  0,  8, -8},
	{-12, -4,  0,  8, -8},
	{-12, -4,  0,  8, -8},
	{-12, -4,  0,  8, -8},
	{-12, -8,  0,  8, -8},
	{-16, -8,  0,  8, -8},
	{-16, -8, -4,  8, -8},
	{-16, -8, -4,  8, -8}
};

/*"table for software venusb.xlsx" from dingrui's email:2015/4/23 (周四) 19:12 ,sheet:IF_VGA_gain_vari_table, value*32 according to S(8,5)*/
int ATBM2040IFVGAGain[20] = {4, -4, 0, 0, -4, 0, -4, -4, 0, 4, -4, 0, 4, -8, 0, 4, -4, 0, 0, -4};

#endif




#endif

