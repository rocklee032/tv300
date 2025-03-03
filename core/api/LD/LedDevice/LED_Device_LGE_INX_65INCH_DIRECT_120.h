#ifndef _LED_Device_LGE_INX_65INCH_DIRECT_120_H_
#define _LED_Device_LGE_INX_65INCH_DIRECT_120_H_


#ifdef _LED_Device_LGE_INX_65INCH_DIRECT_120_C_
    #define _LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_
#else
    #define _LED_Device_LGE_INX_650INCH_DIRECT_120_DEC_  extern
#endif


#include "datatype.h"
#include "leddevice.h"


// div 2
//duty 80.88
//shift 290.86

#if 1

    #define LD_LGE_INX65_VSYNC_PWM_CH_SEL       PWM_CH5

/*
#if(LD_ENABLE) //85inch 120Hz
    #define LD_VSYNC_PWM_CH_SEL       PWM_CH5
    #define LD_VSYNC_PWM_DUTYx100   (0x01 * 10)
    #define LD_VSYNC_PWM_SHIFTx100        0
    #define LD_VSYNC_PWM_DIV                    12
    #define LD_VSYNC_PWM_POLARITY           0

    #define LD_3D_VSYNC_DIV2_ENABLE     1

    #define LD_CS_PWM_CH_SEL       PWM_CH0
    #define LD_CS_PWM_DUTYx100   (0x7D * 10)
    #define LD_CS_PWM_SHIFTx100        6
    #define LD_CS_PWM_DIV                   12
    #define LD_CS_PWM_POLARITY          0
#endif
*/


//========  2D Timing  ========
    #define LD_LGE_INX65_PERIOD_2D_SCLK_TO_VSYNC      (0x80)
//2D 50Hz
    #define LD_LGE_INX65_VSYNC_2D50Hz_PWM_DUTYx100    (20)//(8)//(7)
    #define LD_LGE_INX65_VSYNC_2D50Hz_PWM_SHIFTx100   (0)
    #define LD_LGE_INX65_VSYNC_2D50Hz_PWM_DIV         (12)
    #define LD_LGE_INX65_VSYNC_2D50Hz_PWM_POLARITY    (0)

//2D 60Hz
    #define LD_LGE_INX65_VSYNC_2D60Hz_PWM_DUTYx100    (20)//(8)
    #define LD_LGE_INX65_VSYNC_2D60Hz_PWM_SHIFTx100  (0)
    #define LD_LGE_INX65_VSYNC_2D60Hz_PWM_DIV         (12)
    #define LD_LGE_INX65_VSYNC_2D60Hz_PWM_POLARITY    (0)

//========  3D Timing  ========
    #define LD_LGE_INX65_PERIOD_3D_SCLK_TO_VSYNC      (0x80)

    #define LD_LGE_INX65_VSYNC_3D_PWM_DUTYx100        (9)
    #define LD_LGE_INX65_VSYNC_3D_PWM_SHIFTx100       (0)//(28416)
    #define LD_LGE_INX65_VSYNC_3D_PWM_DIV             (12)
    #define LD_LGE_INX65_VSYNC_3D_PWM_POLARITY        (0)

#endif

extern  t_sDrvLdCusPtrMap sCusPtrMap_LED_LGE_INX65;

_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ void _LED_LGE_INX65_Set_OutputVFreq(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ void _LED_LGE_INX65_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ void  _LED_LGE_INX65_Set_OutputPWMData(U8 ch, t_LD_Signal OutputSignal);

_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ U16  LED_LGE_INX65_Get_OutputVFreq(U8 ch);
_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ U16  LED_LGE_INX65_Get_SyncRstCnt(U8 ch);

_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ void LED_LGE_INX65_Config_OutputSignal_To_LED(U16 u16OutVFreqX10, BOOL Is3D);
_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ void  LED_LGE_INX65_Set_OutputSPI_Signal(const U16* SPI_blocks);
_LED_Device_LGE_INX_65INCH_DIRECT_120_DEC_ void LED_UIchange_smooth_flag(BOOL smooth_flag_en);

#endif // #ifndef _LED_Device_LGE_INX_65INCH_DIRECT_120_H_


