#include "Board.h"

#include "msAPI_MIU.h"
#include "msAPI_Timer.h"

#if( ENABLE_CUS_UART_CMD )
#include "Cus_UartCmd.h"
#endif

#include "Cus_MultiTask.h"

//============================================================================

#define CUS_SLOW_TIMER_1_PERIOD     1000

void Cus_MultiTask_SlowTimer_1(void)
{
    static U32 s_u32SlowTimer_1_LastTime = 0;


    if( msAPI_Timer_DiffTime_2(s_u32SlowTimer_1_LastTime, MsOS_GetSystemTime()) < CUS_SLOW_TIMER_1_PERIOD )
    {
        return;
    }

    s_u32SlowTimer_1_LastTime = MsOS_GetSystemTime();

    //printf("Cus-T1: %u\n", s_u32SlowTimer_1_LastTime);

}

void Cus_MultiTask(void)
{
    CHECK_MIU_PROTECT_LOG_AND_CLEAR();

    U32 u32TimeStart = MsOS_GetSystemTime();


    Cus_MultiTask_SlowTimer_1();

#if( ENABLE_CUS_UART_CMD )
     Cus_UartCmd_Task();
#endif


    U32 u32UseTime = msAPI_Timer_DiffTime_2(u32TimeStart, MsOS_GetSystemTime());
    if( u32UseTime > 20 )
    {
        printf("Cus_MultiTask use %u\n", u32UseTime);
    }

    CHECK_MIU_PROTECT_LOG_AND_CLEAR();
}

