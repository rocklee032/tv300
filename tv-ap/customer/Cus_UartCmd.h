#ifndef _CUS_UART_CMD_H_
#define _CUS_UART_CMD_H_

#include "Board.h"

#if( ENABLE_CUS_UART_CMD )

#define CUS_UART_DATA_BUF_SIZE  10

extern U8 g_Cus_Uart_DataCnt;
extern U8 g_Cus_Uart_DataBuf[CUS_UART_DATA_BUF_SIZE];

void Cus_UartCmd_RecvDataHandler(U8 u8Data);
void Cus_UartCmd_Task(void);


#endif // ENABLE_CUS_UART_CMD

#endif // _CUS_UART_CMD_H_

