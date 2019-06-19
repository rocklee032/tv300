#include "Board.h"

#include "Cus_UartCmd.h"


#if( ENABLE_CUS_UART_CMD )

U8 g_Cus_Uart_DataCnt = 0;
U8 g_Cus_Uart_DataBuf[CUS_UART_DATA_BUF_SIZE];

// If want to use this function, should turn on "g_Uart_bEnableCusUartRecvData"
void Cus_UartCmd_RecvDataHandler(U8 u8Data)
{
    if( g_Cus_Uart_DataCnt < CUS_UART_DATA_BUF_SIZE )
    {
        g_Cus_Uart_DataBuf[g_Cus_Uart_DataCnt] = u8Data;

        g_Cus_Uart_DataCnt += 1;
    }
}

void Cus_UartCmd_Task(void)
{
    if( g_Cus_Uart_DataCnt == 0 )
        return;

    U8 u8DataIdx;

    printf("Cus_UartCmd[%u]:", g_Cus_Uart_DataCnt);
    for( u8DataIdx = 0; u8DataIdx < g_Cus_Uart_DataCnt; u8DataIdx += 1 )
    {
        printf("%X,", g_Cus_Uart_DataBuf[u8DataIdx] );
    }
    printf("\n");

    g_Cus_Uart_DataCnt = 0;
}

#endif


