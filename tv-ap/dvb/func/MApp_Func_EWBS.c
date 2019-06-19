
#include "Board.h"

#include "msAPI_Global.h"

#include "MApp_GlobalSettingSt.h"

#include "MApp_Func_EWBS.h"

#if(ENABLE_EWBS)
BOOLEAN MApp_EWBS_Set_Enable(BOOLEAN bEwbsEnable)
{
    PRINT_CURRENT_LINE();

    printf("MApp_EWBS_Set_Enable(En=%u)\n", bEwbsEnable);

    if( stGenSetting.stMiscSetting.g_bEwbsMode == bEwbsEnable )
    {
        return TRUE;
    }

    if( bEwbsEnable )
    {
        stGenSetting.stMiscSetting.g_bEwbsMode = ENABLE;
    }
    else
    {
        stGenSetting.stMiscSetting.g_bEwbsMode = DISABLE;
        stGenSetting.stMiscSetting.g_bEwbsAutomaticStartup = ENABLE;
        stGenSetting.stMiscSetting.g_bEwbsNoOperationOff = ENABLE;
        stGenSetting.stMiscSetting.g_bEwbsBuzzerNotification = ENABLE;
    }

    return TRUE;

}

#endif


