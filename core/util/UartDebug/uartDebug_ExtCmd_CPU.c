#include "Board.h"

#if ENABLE_UART_EXT_CMD_CPU

#if 1
    #define DEBUG_CMD_READ_VM(x)    do{ if(g_CPU_CMD_bDebugMode) { x } } while(0)
#else
    #define DEBUG_CMD_READ_VM(x)    x
#endif



#define EXTCMD_CPU_CMD_READ_VM      0
#define EXTCMD_CPU_CMD_DEBUG_ENABLE 0xD8


//=================================================================

static BOOLEAN g_CPU_CMD_bDebugMode = 0;//FALSE;

void putcharb(MS_U8 byte);

//=================================================================

void UART_ExtCmd_CPU(void)
{
    DEBUG_CMD_READ_VM( UART_PrintExtCmdBuf(); );

    U8 u8Cmd = g_UartCommand.Buffer[3];
    U32 u32Addr = ((g_UartCommand.Buffer[4])
                |(g_UartCommand.Buffer[5]<<8)
                |(g_UartCommand.Buffer[6]<<16)
                |(g_UartCommand.Buffer[7]<<24));
    U8 u8DataSize = g_UartCommand.Buffer[8] + 1;

#if 0
    U8 au8OutBuf[16] = {0};
    U8 i;
    U8 u8CheckSum;
#endif

    DEBUG_CMD_READ_VM( printf("u8Cmd=0x%X\n", u8Cmd); );

    if( u8Cmd == EXTCMD_CPU_CMD_READ_VM )
    {
        DEBUG_CMD_READ_VM( printf("u32Addr=0x%X\n", u32Addr); );
        DEBUG_CMD_READ_VM( printf("u8DataSize=%u\n", u8DataSize); );

        U8* pu8Data = (U8*)u32Addr;

        if( u8DataSize > 10 )
            u8DataSize = 10;

    #if 1
        UART_CMD_SendData( u8DataSize, pu8Data);
    #else
        au8OutBuf[0] = 0xF0 + u8DataSize + 2;
        u8CheckSum = au8OutBuf[0];
        for( i = 0; i < u8DataSize; i += 1 )
        {
            au8OutBuf[1+i] = pu8Data[i];
            u8CheckSum += pu8Data[i];
        }
        au8OutBuf[1 + u8DataSize] = u8CheckSum;

        DEBUG_CMD_READ_VM( printf("Out[%u]={", u8DataSize+2 ); );
        for( i = 0; i < (u8DataSize+2); ++ i )
        {
            DEBUG_CMD_READ_VM( printf(" %X,", au8OutBuf[i]); );
        }
        DEBUG_CMD_READ_VM( printf("}\n"); );

        for( i = 0; i < (u8DataSize+2); i += 1 )
        {
            putcharb(au8OutBuf[i]);
        }
    #endif
    }
    else if(u8Cmd == EXTCMD_CPU_CMD_DEBUG_ENABLE)
    {
        g_CPU_CMD_bDebugMode = !g_CPU_CMD_bDebugMode;
        printf("g_CPU_CMD_bDebugMode=%u\n", g_CPU_CMD_bDebugMode);
    }

}

#endif

