////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    MApp_MenuChannel.c
/// @author MStar Semiconductor Inc.
/// @brief  Channel Menu Helper Function
///
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_DVB_SERVICE_MONITOR_H_
#define _MAPP_DVB_SERVICE_MONITOR_H_

#include "Board.h"

#if(ENABLE_DVB)
void MApp_DVB_ServiceMonitor( void ); // _MApp_Service_Check()
#endif
BOOLEAN MApp_GetEwbsFlag(void);
#endif // _MAPP_DTV_H_

