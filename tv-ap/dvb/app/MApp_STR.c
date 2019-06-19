//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and U16ernational treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and U16erest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or U16erest to MStar Software and any
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
#define _MAPP_STR_C_
//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include <string.h>

#include "Board.h"

#if( (STR_ENABLE) )
#include "drvBDMA.h"

#include "MsCommon.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_STR.h"

#if(ENABLE_STR_AUDIO_PATCH)
#include "msAPI_audio.h"
#endif

#if(ENABLE_STR_FONT_PATCH)
#include "msAPI_MIU.h"
#include "MApp_LoadFontInit.h"
#include "msAPI_OSD_Resource.h"
#endif

#if(ENABLE_STR_MHEG5_BIN_PATCH)
#include "MApp_MHEG5_Main.h"
#endif

//=========================================================================
U32 g_u32MHEGBinSize = 0xFFFFFFFF;
StSTRBackup_info g_STRBackup_Info;
//=========================================================================

#if(ENABLE_STR_AUDIO_PATCH)
extern MS_BOOL msAPI_Audio_LoadCpuCode(MS_U8 u8CpuIdx, MS_U32 u32CpuMemAddr, MS_U32 u32CpuMemSize);
void MAPP_Audio_LoadCpuCode_STRBackup(void)
{
#if 1 // Do nothing!

#else
    printf("[STR] backup audio start : %d\n",MsOS_GetSystemTime());

#define ADEC__R2_DDR_SIZE       0x240000             // 2.25 MB,audio_R2 FW size
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
    msAPI_Audio_LoadCpuCode(0x00, MAD_BASE_BUFFER_ADR, ADEC__R2_DDR_SIZE);
    //msAPI_Audio_LoadCpuCode(0x00, POOL_BUFFER_ADR+0x1000000, ADEC__R2_DDR_SIZE);

    printf("[STR] backup audio end : %d\n",MsOS_GetSystemTime());
#endif
}

MS_BOOL MAPP_Audio_LoadCpuCode_STRRecover(MS_U8 u8CpuIdx, MS_U32 u32CpuMemAddr, MS_U32 u32CpuMemSize )
{
    printf("MAPP_Audio_LoadCpuCode_STRRecover(cpu=0x%X,addr=0x%X,size=0x%X),return\n", u8CpuIdx, u32CpuMemAddr, u32CpuMemSize);
    return TRUE;
}

#endif

#if((STR_ENABLE) && ENABLE_STR_FONT_PATCH)
extern OSD_RESOURCE_FONT_INFO   _FontTable[E_RES_GROUP_MAX][MAX_FONT];
#define DBG_FONT_STR(x)    //x

void msAPI_FONT_STR_StBackupToDram(void)
{
    printf("[STR]standby FONT_STRBackup\n");

    DBG_FONT_STR(printf("[STR]sizeof(Font) %d\n",sizeof(Font)));
    memcpy((U8 *)_PA2VA(STR_FONTTABLE0_BACKUP_ADDR), (U8 *)&Font, sizeof(Font));
#if 0
    U8 i = 0;
    printf("Font address :  \n\n");
    for(i=0;i<50;i++)
        printf("0x%x ",msAPI_MIU_ReadMemByte(STR_FONTTABLE0_BACKUP_ADDR+i));
    printf("\n\n");
#endif
    DBG_FONT_STR(printf("[STR]sizeof(_FontTable) %d\n",sizeof(_FontTable)));
    memcpy((U8 *)_PA2VA(STR_FONTTABLE1_BACKUP_ADDR), (U8 *)&_FontTable, sizeof(_FontTable));
#if 0
    printf("_FontTable address :  \n\n");
    for(i=0;i<50;i++)
        printf("0x%x ",msAPI_MIU_ReadMemByte(STR_FONTTABLE1_BACKUP_ADDR+i));
    printf("\n\n");
#endif
}

void msAPI_FONT_STRRecover(void)
{
    printf("[STR]FONT_STRRecover\n");
#if 1
    U32 u32FontAddr = 0;
    U32 u32_FontTableAddr = 0;
    u32FontAddr =  g_STRBackup_Info.stSTRBackup_info[E_STRBKItem_FontTable0].u32StartAddr;
    u32_FontTableAddr = g_STRBackup_Info.stSTRBackup_info[E_STRBKItem_FontTable1].u32StartAddr;
    memcpy(&Font,(U8 *)_PA2VA(u32FontAddr),sizeof(Font));
    memcpy(&_FontTable,(U8 *)_PA2VA(u32_FontTableAddr),sizeof(_FontTable));
#else
    memcpy(&Font,(U8 *)_PA2VA(STR_FONTTABLE0_BACKUP_ADDR),sizeof(Font));
    memcpy(&_FontTable,(U8 *)_PA2VA(STR_FONTTABLE1_BACKUP_ADDR),sizeof(_FontTable));
#endif
    //printf("_FontTable[0][0].start_addr : 0x%x\n",_FontTable[0][0].start_addr);
}

void MAPP_FONT_STRBackup(void)
{
    MApp_LoadFontInit();
    msAPI_FONT_STR_StBackupToDram();
}
#endif

#if (ENABLE_STR_MHEG5_BIN_PATCH&&MHEG5_ENABLE)

BOOLEAN MAPP_MHEG5_STRRecover(U32 u32_ADR) //u32_ADR = dst addr
{
    printf("[STR]MAPP_MHEG5_STRRecover \n");
    U32 u32RealBinSize = 0; // mheg5 bin size
#if 0
    memcpy(&u32RealBinSize,(U8 *)_PA2VA(STR_HEADER_INFO_ADDR),sizeof(u32RealBinSize));
#else
    u32RealBinSize = g_STRBackup_Info.stSTRBackup_info[E_STRBKItem_Mheg5Bin].u32DataSize;
#endif
    if(u32RealBinSize == 0)
    {
        printf("[STR] Warning : can not get mheg5 bin size !!! \n");
        return FALSE;
    }
    else
    {
        printf("[STR] skip MHEG5 load bin when booting\n");
        printf("[STR] Mheg5 bin size : %d\n",u32RealBinSize);
        MApi_BDMA_Copy(STR_MHEG5_BIN_BACKUP_ADDR, u32_ADR, u32RealBinSize, MIU_SDRAM2SDRAM);
        return TRUE;
    }
}


BOOLEAN (*DoDecompressionFuncPlus)(U8 *pSrc, U8 *pDst, U8 *pTmp, U32 srclen);

void MAPP_MHEG5_STRBackup(void)
{
    printf("[STR]MAPP_MHEG5_STRBackup \n");
    //msAPI_COPRO_Init(BIN_ID_CODE_MHEG5,STR_BAK_BUF_ADR+STR_BAK_BUF_LEN,AEON_MEM_LEN);
    BININFO BinInfo;
    BinInfo.B_ID = BIN_ID_CODE_MHEG5;
    BOOLEAN bResult;
    U32 u32_ADR = 0;
    U32 u32_LEN = 0;
    u32_ADR = STR_MHEG5_BIN_BACKUP_ADDR;
    u32_LEN = AEON_MEM_LEN;
    printf("msAPI_MHEG5_STR_Backup(u16BinID=0x%X, u32_ADR=0x%X, u32_LEN=0x%X)\n", BinInfo.B_ID, u32_ADR, u32_LEN);
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if( bResult != PASS )
    {
        printf("\nError: Can not find bin=0x%X\n", BinInfo.B_ID);
        return;
    }
#if 0   // GG
    if(!MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32_ADR), _PA2VA(((MHEG5_BUFFER_MEMORY_TYPE&MIU1)?MHEG5_BUFFER_ADR|MIU_INTERVAL:MHEG5_BUFFER_ADR)), _PA2VA(MHEG5_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1)))
    {
        printf("\r\n !Load Bin Fail!");
    }
#else
    {
        U32 u32BinLen;
        U32 u32BinAddr;
        U32 u32DstVA = 0;
        U32 u32DecVA = 0;
        U32 u32TmpVA = 0;
        int i;
        //U8* pu8DecompTmpBuf = (U8 *)(u32TmpVA & NON_CACHEABLE_TO_CACHEABLE_MASK);
        U8* pu8DecompTmpBuf = (U8 *)msOS_NonCacheToCache(u32TmpVA);

        u32BinLen = BinInfo.B_Len;
        u32BinAddr = BinInfo.B_FAddr;
        u32DstVA = _PA2VA(u32_ADR);
        u32DecVA = _PA2VA(((MHEG5_BUFFER_MEMORY_TYPE&MIU1)?MHEG5_BUFFER_ADR|MIU_INTERVAL:MHEG5_BUFFER_ADR));
        u32TmpVA = _PA2VA(MHEG5_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1);
        CHECK_MIU_PROTECT_LOG_AND_CLEAR();

        switch(BinInfo.B_IsComp)
        {
            case LZSS_COMPRESS:
            {
                // fixme: need to find a buffer to put compressed data => u32DecAddr
            #if 1
                printf("\nError: Not uspport LZSS!\n");
            #else
              #if (ENABLE_BOOTTIME)
                 gU32CompressStepTime = msAPI_Timer_GetTime0();
              #endif

                MApi_BDMA_CopyFromResource(u32BinAddr,u32DecVA,u32BinLen);

              #if (ENABLE_BOOTTIME)
                gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32CompressStepTime);
                printf("[TIME] [CopyFromResource]Bin ID = %x, Copy time = %ld\n",
                            pBinInfo->B_ID, msAPI_Timer_DiffTimeFromNow(gU32TmpTime));
                gU32CompressStepTime = msAPI_Timer_GetTime0();
              #endif

                if (ms_DecompressInit((U8*)u32DstVA) == FALSE)
                {
                    printf("decompress fail!\n");
                    return FAILURE;
                }

                ms_Decompress((U8*)u32DecVA, u32BinLen);
                ms_DecompressDeInit();

              #if (ENABLE_BOOTTIME)
                gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32CompressStepTime);
                gU32CompressTotalStepTime += gU32TmpTime;
                printf("[TIME] [Decompress time]Bin ID = %x, Decompress time = %ld\n", pBinInfo->B_ID, gU32TmpTime);
              #endif
            #endif
                break;
            }

            case MS_COMPRESS:
            case MS_COMPRESS7:
        #if(ENABLE_DECOMP_ZDEC)
            case MS_COMPRESS_ZDEC:
        #endif
            {
                U32 OriginalFileLength = 0;


                MApi_BDMA_CopyFromResource(u32BinAddr, u32DecVA, u32BinLen);

            #if (ENABLE_BIN_FILE_CRC)
                // Check bin CRC16
                //PRINT_CURRENT_LINE();
                MApi_BDMA_CheckBinCRC(BinInfo.B_ID, u32BinLen, u32DecVA);
            #endif


                //Print_Buffer( (U8*)u32DecVA, 16 );

                //search compressed file real length
            #if(ENABLE_DECOMP_ZDEC)
                if( MS_COMPRESS_ZDEC == BinInfo.B_IsComp )
                {
                    for(i=3;i<12;i++)
                    {
                        if ( *((U8 *)(u32DecVA+u32BinLen-i)) == 0xFB )
                        {
                            if ( *((U8 *)(u32DecVA+u32BinLen-i-1)) == 0xBE )
                                u32BinLen -= (i+1);
                        }
                    }
                }
                else
            #endif
                {
                    for(i=3;i<12;i++)
                    {
                        if ( *((U8 *)(u32DecVA+u32BinLen-i)) == 0xEF )
                        {
                            if ( *((U8 *)(u32DecVA+u32BinLen-i-1)) == 0xBE )
                                u32BinLen -= (i+1);
                        }
                    }
                }

                // restore the real length of decompressed bin to Bininfo 20100108EL
                if ( BinInfo.B_IsComp == MS_COMPRESS7 )
                {
                    DoDecompressionFuncPlus = DoMsDecompression7;

                    for (i = 0; i < 8; i++)
                    {
                        OriginalFileLength += ( (U32)((U8 *)u32DecVA)[5 + i] << (i << 3) );
                    }

                    BinInfo.B_Len = OriginalFileLength;

                #if( ENABLE_DECOMP7_USE_HK_MEMORY )
                    pu8DecompTmpBuf = g_au8Decomp7TmpBuf;
                #endif
                }
                else // MS_COMPRESS
                {
                    DoDecompressionFuncPlus = DoMsDecompression;

                    memcpy(&(BinInfo.B_Len), (void*)(u32DecVA+u32BinLen-4), 4);
                    //printf("^^^G3^^^ pBinInfo->B_Len = %ld\n", pBinInfo->B_Len);
                }

                //printf(" CRC2_2=0x%X\n", msAPI_CRC_Cal( (U8*)u32DecVA, u32BinLen) );

                //g_MsDecomp7_u8Debug = 1;

                U32 u32DstVA_Cached = msOS_NonCacheToCache(u32DstVA);//(u32DstVA & NON_CACHEABLE_TO_CACHEABLE_MASK);

                if( !DoDecompressionFuncPlus(
                            //(U8 *)(u32DecVA & NON_CACHEABLE_TO_CACHEABLE_MASK),
                            (U8 *)msOS_NonCacheToCache(u32DecVA),

                            //(U8 *)(u32DstVA & NON_CACHEABLE_TO_CACHEABLE_MASK),
                            (U8 *)u32DstVA_Cached,
                        #if 1
                            pu8DecompTmpBuf,
                        #else
                            (U8 *)(u32TmpVA & NON_CACHEABLE_TO_CACHEABLE_MASK),
                        #endif
                            u32BinLen )
                  )
                {
                    printf("\nError: DoDecompressionFuncPlus fail!\n");
                    return;
                }
                //Store MHEG5 bin size information in memory
                memcpy((U8 *)_PA2VA(STR_HEADER_INFO_ADDR),(U8 *)&OriginalFileLength,sizeof(OriginalFileLength));
                printf("OriginalFileLength : %d\n",OriginalFileLength);
                g_u32MHEGBinSize = OriginalFileLength;
                MsOS_Dcache_Flush( (MS_U32)(u32DstVA_Cached & (~15)),(MS_U32)((BinInfo.B_Len+15) & (~15)));
                MsOS_FlushMemory();

                break;
            }


            default:    //no compressed bin
            {
            #if (!BLOADER)

                if ( (BinInfo.B_ID == BIN_ID_OSDCP_TEXT)
                 #if( VDEC_BIN_IS_FW_VPU )
                   ||(BinInfo.B_ID == BIN_ID_CODE_VDEC_FW_VPU)
                 #else
                  #if(SUPPORT_VDEC_2_0 == 0)
                   ||(BinInfo.B_ID == BIN_ID_CODE_AEON_MVD)
                  #endif
                   ||(BinInfo.B_ID == BIN_ID_CODE_AEON_H264)  //20100422EL Add
                 #endif

                 #if( (CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA)&& (CHIP_SUPPORT_HEVC) ) //IMPLEMENT_DTV_H265
                   ||(BinInfo.B_ID == BIN_ID_CODE_AEON_H265)
                 #endif
                   ||(BinInfo.B_ID == FONT_MSTAR_UNICODE_MVF) //20100301EL
                   )
                {
                    //printf("~~~~~~~~Do nothing at these bins !!\n");
                }
                else
                {
                    MApi_BDMA_CopyFromResource(u32BinAddr,u32DstVA,u32BinLen);
                    //printf(" CRC1=0x%X\n", msAPI_CRC_Cal( (U8*)u32DstVA, u32BinLen) );

                #if(ENABLE_BIN_FILE_CRC)
                    // Cal CRC16
                    //if( pBinInfo->B_ID == BIN_ID_CODE_DEMUX )
                    {
                        //PRINT_CURRENT_LINE();
                        MApi_BDMA_CheckBinCRC(BinInfo.B_ID, u32BinLen, u32DstVA);
                    }
                #endif

                }

            #else
                MApi_BDMA_CopyFromResource(u32BinAddr,u32DstVA,u32BinLen);
            #endif

                break;
            }
        }

        CHECK_MIU_PROTECT_LOG_AND_CLEAR();
    }
#endif
}
#endif

void MApp_STR_BackupAll(void)
{
#if(ENABLE_STR_AUDIO_PATCH)
    MAPP_Audio_LoadCpuCode_STRBackup();
#endif

#if (ENABLE_STR_MHEG5_BIN_PATCH&&MHEG5_ENABLE)
    printf("[STR] backup MHEG5 start : %d\n",MsOS_GetSystemTime());
    MAPP_MHEG5_STRBackup();
    printf("[STR] backup MHEG5 end : %d\n",MsOS_GetSystemTime());
#endif

#if(ENABLE_STR_FONT_PATCH)
    MAPP_FONT_STRBackup();
    printf("[STR last status] msAPI_FONT_STANDBY_STRBackup end : %d\n",MsOS_GetSystemTime());
#endif
}

void MAPP_STR_StoreBackupInfo(BOOLEAN bCalCRC)
{
    //StSTRStoredBlock_Info TmpStSTRBackupBlock_Info[STR_AMOUNT_OF_STORED_BLOCK];
    StSTRBackup_info TmpStBackup_info;
    TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable0].u32StartAddr = STR_FONTTABLE0_BACKUP_ADDR;
    TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable1].u32StartAddr = STR_FONTTABLE1_BACKUP_ADDR;
    TmpStBackup_info.stSTRBackup_info[E_STRBKItem_Mheg5Bin].u32StartAddr = STR_MHEG5_BIN_BACKUP_ADDR;

    TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable0].u32DataSize = sizeof(Font);
    TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable1].u32DataSize = sizeof(_FontTable);
    TmpStBackup_info.stSTRBackup_info[E_STRBKItem_Mheg5Bin].u32DataSize = g_u32MHEGBinSize;

    if(bCalCRC == TRUE)
    {
        TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable0].u32CRCValue = MDrv_BDMA_CRC32(STR_FONTTABLE0_BACKUP_ADDR, sizeof(Font), BDMA_CRC32_POLY, BDMA_CRC_SEED_F, E_BDMA_SRCDEV_MIU0, FALSE);
        TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable1].u32CRCValue = MDrv_BDMA_CRC32(STR_FONTTABLE1_BACKUP_ADDR, sizeof(_FontTable), BDMA_CRC32_POLY, BDMA_CRC_SEED_F, E_BDMA_SRCDEV_MIU0, FALSE);
        TmpStBackup_info.stSTRBackup_info[E_STRBKItem_Mheg5Bin].u32CRCValue = MDrv_BDMA_CRC32(STR_MHEG5_BIN_BACKUP_ADDR, g_u32MHEGBinSize, BDMA_CRC32_POLY, BDMA_CRC_SEED_F, E_BDMA_SRCDEV_MIU0, FALSE);
        printf("[STR] StoreBackupInfo DO CRC32\n");
    }
    else
    {
        TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable0].u32CRCValue = 0xFFFFFFFF;
        TmpStBackup_info.stSTRBackup_info[E_STRBKItem_FontTable1].u32CRCValue =  0xFFFFFFFF;
        TmpStBackup_info.stSTRBackup_info[E_STRBKItem_Mheg5Bin].u32CRCValue =  0xFFFFFFFF;
        printf("[STR] StoreBackupInfo NOT DO CRC32\n");
    }
    TmpStBackup_info.NumOfStoredBlock = STR_AMOUNT_OF_STORED_BLOCK;
    TmpStBackup_info.SizeOfStoredBlock = sizeof(TmpStBackup_info);
#if 0
    printf("TmpStBackup_info.NumOfStoredBlock :%d\n",TmpStBackup_info.NumOfStoredBlock);
    printf("TmpStBackup_info.SizeOfStoredBlock :%d\n",TmpStBackup_info.SizeOfStoredBlock);
    U8 i=0;
    for(i=0 ;i< E_STRBKItem_MaxNum; i++)
    {
        printf("TmpStBackup_info.stSTRBackup_info[%d].u32StartAddr : 0x%x\n",i,TmpStBackup_info.stSTRBackup_info[i].u32StartAddr);
        printf("TmpStBackup_info.stSTRBackup_info[%d].u32DataSize : %d\n",i,TmpStBackup_info.stSTRBackup_info[i].u32DataSize);  
        printf("TmpStBackup_info.stSTRBackup_info[%d].u32CRCValue : 0x%x\n",i,TmpStBackup_info.stSTRBackup_info[i].u32CRCValue);  
    }
    //printf("sizeof(g_STRBackup_Info) : %d\n",sizeof(g_STRBackup_Info));
#endif
    memcpy((U8 *)_PA2VA(STR_HEADER_INFO_ADDR),(U8 *)&TmpStBackup_info,sizeof(TmpStBackup_info));
    //printf("0x%x \n",msAPI_MIU_ReadMemByte(STR_HEADER_INFO_ADDR));
    //printf("0x%x \n",msAPI_MIU_ReadMemByte(STR_HEADER_INFO_ADDR+1));
    //TmpStBackup_info.stSTRBackup_info
    //memcpy((U8 *)_PA2VA(STR_HEADER_INFO_ADDR),(U8 *)&TmpStSTRBackupBlock_Info,sizeof(TmpStSTRBackupBlock_Info));

}

void MAPP_STR_FetchBackupInfo(void)
{
    U8 u8NumOfStoredBlock = 0;
    U8 u8SizeOfStoredBlock = 0;
    u8NumOfStoredBlock = msAPI_MIU_ReadMemByte(STR_HEADER_INFO_ADDR);
    u8SizeOfStoredBlock = msAPI_MIU_ReadMemByte(STR_HEADER_INFO_ADDR+1);
    memcpy(&g_STRBackup_Info,(U8 *)_PA2VA(STR_HEADER_INFO_ADDR),u8SizeOfStoredBlock);
}


#endif // #if( (STR_ENABLE) )

#undef _MAPP_STR_C_

