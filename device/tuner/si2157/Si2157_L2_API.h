/***************************************************************************************
                  Silicon Laboratories Broadcast Si2157 Layer 2 API
   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.
   L2 API header for commands and properties
   FILE: Si2157_L2_API.h
   Supported IC : Si2157
   Compiled for ROM 50 firmware 3_4_build_4
   Revision: 0.1
   Date: November 06 2013
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2157_L2_API_H
#define   Si2157_L2_API_H

#include "Si2157_L1_API.h"
#include "Si2157_Properties_Strings.h"

int  Si2157_Init                      (L1_Si2157_Context *api);
int  Si2157_Configure                 (L1_Si2157_Context *api);
int  Si2157_PowerUpWithPatch          (L1_Si2157_Context *api);
int  Si2157_PowerUpUsingBroadcastI2C    (L1_Si2157_Context *Tuner1, L1_Si2157_Context *Tuner2 );
int  Si2157_LoadFirmware              (L1_Si2157_Context *api, unsigned char *fw_table, int lines);
int  Si2157_StartFirmware             (L1_Si2157_Context *api);

int Si2157_LoadFirmware_16       (L1_Si2157_Context *api, firmware_struct fw_table[], int nbLines);
int Si2157_UpdateChannelScanFrequency(int freq,int channelsFound);
int Si2157_GetRF                 (L1_Si2157_Context *api);
int Si2157_Tune                  (L1_Si2157_Context *api, unsigned char mode, unsigned long freq);
int Si2157_ATVTune               (L1_Si2157_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color, unsigned char invert_spectrum);
int Si2157_DTVTune               (L1_Si2157_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_signal);
int Si2157_XoutOn                (L1_Si2157_Context *api);
int Si2157_XoutOff               (L1_Si2157_Context *api);
int Si2157_Standby               (L1_Si2157_Context *api);
int Si2157_Powerdown             (L1_Si2157_Context *api);
int Si2157_LoadVideofilter       (L1_Si2157_Context *api, vid_filt_struct vidFiltTable[], int lines);
int Si2157_ATV_Channel_Scan_M    (L1_Si2157_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
int Si2157_ATV_Channel_Scan_PAL  (L1_Si2157_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
int Si2157_AGC_Override    (L1_Si2157_Context *api, unsigned char mode );
#define Si2157_FORCE_NORMAL_AGC       0
#define Si2157_FORCE_MAX_AGC          1
#define Si2157_FORCE_TOP_AGC          2

#endif /* Si2157_L2_API_H */







