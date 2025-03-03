//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
#if (defined(USB_HEADPHONE) && defined(CHIP_T3))
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/soundcard.h>
#include <sys/ioctl.h>
#include "apiAUDIO.h"
#include "MApp_UsbHeadphone.h"
#include "datatype.h"

#define MAPP_USBDOWNLOAD_C

#define DEVICE_NAME "/dev/dsp"
#define SAMPLE_RATE 48000
#define DATA_FORMAT AFMT_S16_NE
#define CHANNEL_NUM 2

static int device_fd = 0;
static MS_BOOL _bEnabled = FALSE;
static pthread_t a_thread;

static MS_BOOL MApp_UsbHeadphoen_WriteData2Device(MS_U8 * pu8Buffer, MS_U32 u32Len)
{
    if (device_fd <= 0)
    {
        printf("MApp_UsbHeadphoen_WriteData2Device - Device is not exist!!\n");
        return FALSE;
    }

    // write data
    write(device_fd, pu8Buffer, u32Len);
    return TRUE;
}

static MS_BOOL MApp_UsbHeadphone_SetSpeed(MS_U32 u32Speed)
{
    int speed;

    if (device_fd <= 0)
    {
        printf("MApp_UsbHeadphone_SetSpeed - Device is not exist!!\n");
        return FALSE;
    }

    speed = u32Speed;
    if (ioctl(device_fd, SNDCTL_DSP_SPEED, &speed) == -1)
    {
       /* Fatal error */
       printf("ioctl failed - SNDCTL_DSP_SPEED\n");
       return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static MS_BOOL MApp_UsbHeadphone_SetChannel(MS_U32 u32Channel)
{
    int channel;

    if (device_fd <= 0)
    {
        printf("MApp_UsbHeadphone_SetChannel - Device is not exist!!\n");
        return FALSE;
    }

    channel = u32Channel;
    if (ioctl(device_fd, SNDCTL_DSP_CHANNELS, &channel) == -1)
    {
       /* Fatal error */
       printf("ioctl failed - SNDCTL_DSP_CHANNELS\n");
       return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static MS_BOOL MApp_UsbHeadphone_SetFormat(MS_U32 u32Format)
{
    int format;

    if (device_fd <= 0)
    {
        printf("MApp_UsbHeadphone_SetFormat - Device is not exist!!\n");
        return FALSE;
    }

    format = u32Format;
    if (ioctl(device_fd, SNDCTL_DSP_SETFMT, &format) == -1)
    {
       /* Fatal error */
       printf("ioctl failed - SNDCTL_DSP_SETFMT\n");
       return FALSE;
    }
    else
    {
        return TRUE;
    }
}
static MS_BOOL MApp_UsbHeadphone_OpenDevice(MS_U8 * pu8DeviceName)
{
    // open device
    if ((device_fd = open((char*)pu8DeviceName, O_WRONLY, 0)) == -1)
    {
       printf("MApp_UsbHeadphone_OpenDevice - open device \"%s\" falied!!\n", pu8DeviceName);
       return FALSE;
    }

    return TRUE;
}

static MS_BOOL MApp_UsbHeadphone_CloseDevice(void)
{
    if (device_fd > 0)
    {
        close(device_fd);
        device_fd = 0;
    }

    return TRUE;
}

static void* MApp_UsbHeadphone_ThreadFunc(void * arg)
{
    MS_U32 addr;
    MS_U32 size;

    UNUSED(arg);

    // polling that is data ready or not, then write the data to device
    while(_bEnabled)
    {
        // The data is ready
        if (MApi_AUDIO_USBPCM_GetFlag())
        {
            // get the data info
            MApi_AUDIO_USBPCM_GetMemInfo(&addr, &size);
            // write to device
            MApp_UsbHeadphoen_WriteData2Device((MS_U8 *)_PA2VA(addr), size);
            // clear the flag
            MApi_AUDIO_USBPCM_SetFlag(0);
        }
    }

    pthread_exit(NULL);
}

void MApp_UsbHeadphone_Enable(MS_BOOL bEnable)
{
    if (bEnable)
    {
        // Already enabled, don't do it again.
        if (_bEnabled == TRUE)
            return;

        _bEnabled = TRUE;

        // open device
        MApp_UsbHeadphone_OpenDevice((MS_U8*)DEVICE_NAME);

        // set format
        MApp_UsbHeadphone_SetFormat(DATA_FORMAT);

        // set channel
        MApp_UsbHeadphone_SetChannel(CHANNEL_NUM); /* 1=mono, 2=stereo */

        // set speed
        MApp_UsbHeadphone_SetSpeed(SAMPLE_RATE);

        // Enable audio driver
        MApi_AUDIO_USBPCM_Enable(TRUE);

        // create thread function to polling and play
        if (pthread_create(&a_thread, NULL, MApp_UsbHeadphone_ThreadFunc, NULL) != 0)
        {
            printf("MApp_UsbHeadphone_Enable - Create thread failed!!\n");
            MApp_UsbHeadphone_CloseDevice();
            return;
        }
    }
    else
    {
        void * thread_result;

        if (_bEnabled == FALSE)
            return;

        _bEnabled = FALSE;

        // Enable audio driver
        MApi_AUDIO_USBPCM_Enable(FALSE);

        MApp_UsbHeadphone_CloseDevice();

        if (pthread_join(a_thread, &thread_result) != 0)
        {
            printf("MApp_UsbHeadphone_Enable - Thread join failed!!\n");
        }
    }
}
#endif  //#if (defined(USB_HEADPHONE) && defined(CHIP_T3))
