#ifndef _SW_CONFIG_DEFAULT_H_
#define _SW_CONFIG_DEFAULT_H_

//===================================================================================

#ifndef ENABLE_CONSOLE_CMD
    #define ENABLE_CONSOLE_CMD      0
#endif

#ifndef ENABLE_CUS_UART_CMD
    #define ENABLE_CUS_UART_CMD     DISABLE
#endif

#ifndef ENABLE_DDCCI
    #define ENABLE_DDCCI            DISABLE
#endif

#ifndef ENABLE_GAMEMODE
    #define ENABLE_GAMEMODE         DISABLE
#endif

#ifndef ENABLE_SCALER_GAMEMODE
    #define ENABLE_SCALER_GAMEMODE  ENABLE_GAMEMODE
#endif

#ifndef GAME_MODE_SUPPORT_SD_P_MODE
    #define GAME_MODE_SUPPORT_SD_P_MODE  1
#endif

#ifndef ENABLE_DECOMP_ZDEC
    #define ENABLE_DECOMP_ZDEC      0
#endif

#ifndef ENABLE_HASH_KEY_256BITS
    #define ENABLE_HASH_KEY_256BITS 0
#endif

//-------------------------------------------------------------------
#ifndef STR_ENABLE
    #define STR_ENABLE      DISABLE
#endif

#ifndef ENABLE_KEY_INFO_PRINT_SYS_INFO
    #define ENABLE_KEY_INFO_PRINT_SYS_INFO  0
#endif

//===================================================================================

#endif // _SW_CONFIG_DEFAULT_H_

