#include <string.h>

#if defined(__aeon__)
#include "drvAeonR2.h"
#endif

#if (ENABLE_MSTV_UART_DEBUG)

#if( ENABLE_CUS_UART_CMD )
#include "Cus_UartCmd.h"
#endif


BOOLEAN g_Uart_bEnableMsTVToolRecvData = 1;

UartCommadType g_UartCommand; // Uart command struct


#if(ENABLE_CONSOLE_CMD)
BOOLEAN g_Uart_bEnableConsoleCmdRecvData = 1;
void msAPI_ConsoleCmd_RecvData(U8 u8Data);
#endif

#if( ENABLE_CUS_UART_CMD )
BOOLEAN g_Uart_bEnableCusUartRecvData = 0; // Default is off
#endif


void UART_PrintExtCmdBuf(void)
{
    U8 i;
    printf("UartExcCmd[%u]={", g_UartCommand.u8CmdLen);
    for( i = 0; i < g_UartCommand.u8CmdLen; ++ i )
    {
        printf(" %X,", g_UartCommand.Buffer[i]);
    }
    printf("}\n");
}


// Check uart protocal
bit IsUartCmdValid(U8* au8Buffer)
{
    BYTE i, ucLen;
    BYTE ucCS = 0;

    if( UART_EXT_Buf(au8Buffer) )
    {
        ucLen = UART_CMD_EXT_LENGTH_Buf(au8Buffer);
    }
    else
    {
        ucLen = UART_CMD_LENGTH_Buf(au8Buffer);
    }

    ucCS = 0;
    for( i = 0; i < ucLen; ++ i )
    {
        ucCS += au8Buffer[i];
    }

    if( ucCS == 0xFF )
        return 1;

    return 0;
}

void MDrv_TVTool_1ms_ISR(void)
{
#if(!BLOADER)

  #if (ENABLE_MSTV_UART_DEBUG )
    if (g_Uart0CheckTick)
    {
        --g_Uart0CheckTick;
        if ( g_Uart0CheckTick == 0 )
        {
            g_bUart0Detected = FALSE;
            g_UartCommand.Index = 0;
        }
    }
  #elif 0 //XMODEM_DWNLD_ENABLE //for xmodem
    if ( g_Uart0CheckTick )
    {
        --g_Uart0CheckTick;
        if ( g_Uart0CheckTick == 0 )
        {
            XModem_Rx_Timeout = TRUE;
        }
    }
  #endif


 #if (ENABLE_UART1_INTERRUPT == ENABLE)
   #if(ENABLE_UART1_DEBUG)
    if (g_Uart1CheckTick)
    {
        --g_Uart1CheckTick;
        if ( g_Uart1CheckTick == 0 )
        {
            g_bUart1Detected = FALSE;
            g_ucUart1BufIndex = 0;
        }
    }
   #endif
 #endif

  #if (ENABLE_UART2)
    if (g_Uart2CheckTick)
    {
        --g_Uart2CheckTick;
        if ( g_Uart2CheckTick == 0 )
        {
            g_bUart2Detected = FALSE;
            g_Uart2Command.Index = 0;
        }
    }
  #endif // #if (ENABLE_UART2)

#endif // #if (!BLOADER)
}

void MDrv_TVTool_RecvHandler(int c)
{
    g_Uart0CheckTick = 50;// time-out control ms

    if (g_UartCommand.Index >= _UART_CMD_LENGTH_ )
    {
        g_UartCommand.Index = 0;
    }

#if 0//(ENABLE_MMS)
    // detect dash
    if ((0x2D == c)&& (1 == DbgMenuMode))
    {
        InputPara = 1;
    }

    // recieve byte
    if (!InputPara)
    {
#endif
        UART_RX_BUF[g_UartCommand.Index] = c;
#if 0//(ENABLE_MMS)
    } else
    {
        MDrv_MMS_ParseCmdParm(c);
    }

    // receive for menu mode
    if (1 == DbgMenuMode)
    {
        MDrv_MMS_UARTRecvHandler(c);
        return;
    }

#endif

    // check command buffer index
    if( UART_EXT_Buf(UART_RX_BUF) )
    {
        if (g_UartCommand.Index == 0) // check 1st data
        {
            g_UartCommand.Index++; // for get UART_CMD_EXT_LENGTH
        }
        else
        {
            if (g_UartCommand.Index < UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF)) // still read command
            {
                g_UartCommand.Index++; // next index of command buffer
            }

            if (g_UartCommand.Index >= UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF)) // read command ok
            {
                if( IsUartCmdValid((UART_RX_BUF)) )
                {
                    memcpy(g_UartCommand.Buffer, UART_RX_BUF, UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF));
                    g_UartCommand.u8CmdLen = UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF);
                    g_bUart0Detected = TRUE; // command  buffer recieve ok
                }

                g_UartCommand.Index = 0; // reset index of command buffer
                g_Uart0CheckTick = 0;
            }
        }
    }
    else
    {
        if (g_UartCommand.Index < UART_CMD_LENGTH_Buf(UART_RX_BUF)) // still read command
        {
            g_UartCommand.Index ++; // next index of command buffer
        }

        if (g_UartCommand.Index >= UART_CMD_LENGTH_Buf(UART_RX_BUF)) // read command ok
        {
            // check if Enter Key. (0x0D)
        #if 0//(ENABLE_MMS)
            if (g_UartCommand.Buffer[_UART_CMD_CODE_] == 0x0D) {

                //set flag to enter menu mode
                DbgMenuMode = 1;
                MDrv_LogoPrint();
                if (!(DbgMenuLevel ||CatMenuLevel || CfgMenuLevel || UntMenuLevel))
                    MDrv_MainPagePrint();
            }
        #endif

        #if 1//( ENABLE_UART_CHECKSUM )
            if( IsUartCmdValid((UART_RX_BUF)) )
        #endif
            {
                memcpy(g_UartCommand.Buffer, UART_RX_BUF, UART_CMD_LENGTH_Buf(UART_RX_BUF));
                g_bUart0Detected = TRUE; // command  buffer recieve ok
                g_UartCommand.u8CmdLen = UART_CMD_LENGTH_Buf(UART_RX_BUF);
            }

            g_UartCommand.Index = 0; // reset index of command buffer
            g_Uart0CheckTick = 0;
        }
    }

}


#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)\
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)\
   )
    #define OLD_UART_INTERFACE  1
#else
    #define OLD_UART_INTERFACE  0
#endif

void MDrv_UART_RecvHandler( int c
#if( OLD_UART_INTERFACE )
#else
    , MS_U32 pHalReg
#endif
)
{
#if defined(__arm__)
    UNUSED(pHalReg);
#endif

#if 0
    if( c < 0x80 )
    {
        putchar(c);
    }
#endif

#if 0//( ENABLE_R2_BACKTRACE )
    if( MDrv_R2BT_RecvDataHandler(c, pHalReg) )
    {
        return;
    }
#endif


#if( CHAKRA3_AUTO_TEST )
    MApp_AT_RecvDataHandler(c);

    if( MApp_AT_Is_NeedDisableOtherUartFunction() )
        return;
#endif

#if(ENABLE_CONSOLE_CMD)
    if( g_Uart_bEnableConsoleCmdRecvData )
    {
        msAPI_ConsoleCmd_RecvData(c);
    }
#endif

#if( ENABLE_CUS_UART_CMD )
    if( g_Uart_bEnableCusUartRecvData )
    {
        Cus_UartCmd_RecvDataHandler(c);
    }
#endif


#if 1 // Use new API
    if( g_Uart_bEnableMsTVToolRecvData )
    {
        if( (c == 0x7F) && (g_UartCommand.Index==0) )// Press "Delete" to get PC & RA
        {
        #if( defined(__mips__) )
            msDebug_mips_BackTrace(pHalReg);
        #endif

        #if( defined(__aeon__) &&( !OLD_UART_INTERFACE ) )
            MDrv_AeonR2_Backtrace(pHalReg);
        #endif
        }

        MDrv_TVTool_RecvHandler(c);
    }

#else // Move to MDrv_TVTool_RecvHandler()

    g_Uart0CheckTick = 50;// time-out control ms

    if (g_UartCommand.Index >= _UART_CMD_LENGTH_ )
    {
        g_UartCommand.Index = 0;
    }

    if( (c == 0x7F) && (g_UartCommand.Index==0) )// Press "Delete" to get PC & RA
    {
    #if( defined(__mips__) )
        msDebug_mips_BackTrace(pHalReg);
    #endif

    #if( defined(__aeon__) &&( !OLD_UART_INTERFACE ) )
        MDrv_AeonR2_Backtrace(pHalReg);
    #endif
    }

#if 0//(ENABLE_MMS)
    // detect dash
    if ((0x2D == c)&& (1 == DbgMenuMode))
    {
        InputPara = 1;
    }

    // recieve byte
    if (!InputPara)
    {
#endif
        UART_RX_BUF[g_UartCommand.Index] = c;
#if 0//(ENABLE_MMS)
    } else
    {
        MDrv_MMS_ParseCmdParm(c);
    }

    // receive for menu mode
    if (1 == DbgMenuMode)
    {
        MDrv_MMS_UARTRecvHandler(c);
        return;
    }
#endif

    // check command buffer index
    if (UART_EXT_Buf(UART_RX_BUF))
    {
        if (g_UartCommand.Index == 0) // check 1st data
        {
            g_UartCommand.Index++; // for get UART_CMD_EXT_LENGTH
        }
        else
        {
            if (g_UartCommand.Index < UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF)) // still read command
            {
                g_UartCommand.Index++; // next index of command buffer
            }

            if (g_UartCommand.Index >= UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF)) // read command ok
            {
                if( IsUartCmdValid((UART_RX_BUF)) )
                {
                    memcpy(g_UartCommand.Buffer, UART_RX_BUF, UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF));
                    g_UartCommand.u8CmdLen = UART_CMD_EXT_LENGTH_Buf(UART_RX_BUF);
                    g_bUart0Detected = TRUE; // command  buffer recieve ok
                }

                g_UartCommand.Index = 0; // reset index of command buffer
                g_Uart0CheckTick = 0;
            }
        }
    }
    else
    {
        if (g_UartCommand.Index < UART_CMD_LENGTH_Buf(UART_RX_BUF)) // still read command
        {
            g_UartCommand.Index ++; // next index of command buffer
        }

        if (g_UartCommand.Index >= UART_CMD_LENGTH_Buf(UART_RX_BUF)) // read command ok
        {
            // check if Enter Key. (0x0D)
        #if 0//(ENABLE_MMS)
            if (g_UartCommand.Buffer[_UART_CMD_CODE_] == 0x0D) {

                //set flag to enter menu mode
                DbgMenuMode = 1;
                MDrv_LogoPrint();
                if (!(DbgMenuLevel ||CatMenuLevel || CfgMenuLevel || UntMenuLevel))
                    MDrv_MainPagePrint();
            }
        #endif

        #if 1//( ENABLE_UART_CHECKSUM )
            if( IsUartCmdValid((UART_RX_BUF)) )
        #endif
            {
                memcpy(g_UartCommand.Buffer, UART_RX_BUF, UART_CMD_LENGTH_Buf(UART_RX_BUF));
                g_bUart0Detected = TRUE; // command  buffer recieve ok
                g_UartCommand.u8CmdLen = UART_CMD_LENGTH_Buf(UART_RX_BUF);
            }

            g_UartCommand.Index = 0; // reset index of command buffer
            g_Uart0CheckTick = 0;
        }
    }
#endif

    MsOS_EnableInterrupt(E_INT_IRQ_UART0);

}

#endif // ENABLE_MSTV_UART_DEBUG

