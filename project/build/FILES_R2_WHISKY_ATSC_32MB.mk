
CC_TVOPTS += \
    -DOBA2=0                                                        \
    -DMSOS_TYPE_NOS                                                 \
    -DS4LITE_ENHANCE                                                \
    -DENABLE_DMP=1                                                  \
    -DENABLE_CAPE=0                                                 \
    -DFOR_BENCH_CODE=0                                              \
    -DENCODE_AUDIO_AP=0                                             \
    -DENABLE_PIP=0                                                  \
    -DENABLE_BOOTING_MUSIC=0                                        \
    -DENABLE_MHEG5=0                                                  \
    -DENABLE_NTSC_SYSTEM=1																					\
    -DENABLE_32M_H264=1                                             \
    -DENABLE_HK_PHOTO=1                                             \
#    -DENABLE_DTV=1                                                  \
#   -DENABLE_PVR=0                                                  \
#   -DAEON_VDPLAYER                                                 \
#   -DAP_COWORK
#   -DENABLE_BT                                                     \
#   -DNETWORK_CONFIG                                                \
#   -DMAC_ADDRESS                                                   \
#   -DENABLE_KTV                                                    \
#   -DENABLE_RSS                                                    \
#   -DENABLE_YOUTUBE                                                \
#   -DENABLE_GYM                                                    \
#   -DENABLE_YOUTUBE

AEON_TYPE=aeonR2

#ENABLE_DTV flag is use for ATV_MM model that no need the DTV input source, but need MVD for MM


##################################################################
# Driver / API
##################################################################

# PIP ENABLE need include these 2 files
DRV_FILES += \
        $(ROOT)/core/driver/pq/hal/$(chip_name)/QualityMap_Sub.c              \
        $(ROOT)/core/driver/pq/hal/$(chip_name)/QualityMap_SubEx.c           \


API_FILES += \
        $(ROOT)/core/api/scaler_front/apiXC_Sys.c                   \
        $(ROOT)/core/api/scaler_front/apiXC_Hdmi.c                  \
        $(ROOT)/core/api/scaler_front/apiXC_Cus.c                   \
        $(ROOT)/core/api/scaler_front/msAPI_Mode.c                  \
        $(ROOT)/core/api/scaler_front/msAPI_CEC.c                   \
        $(ROOT)/core/api/scaler_back/msAPI_DCC.c                    \
        $(ROOT)/core/api/scaler_back/msAPI_NR.c                     \
        $(ROOT)/core/api/msAPI_MMap.c                               \
        $(ROOT)/core/api/msAPI_VD.c                                 \
        $(ROOT)/core/api/msAPI_RAM.c                                \
        $(ROOT)/core/api/msAPI_Font.c                               \
        $(ROOT)/core/api/msAPI_Font_Dynamic_MVF.c                   \
        $(ROOT)/core/api/msAPI_OCP.c                                \
        $(ROOT)/core/api/msAPI_FreqTableDTV.c                       \
        $(ROOT)/core/api/msAPI_FreqTableATV.c                       \
        $(ROOT)/core/api/msAPI_Timer.c                              \
        $(ROOT)/core/api/msAPI_IR.c                                 \
        $(ROOT)/core/api/msAPI_Video.c                              \
        $(ROOT)/core/api/msAPI_MIU.c                                \
        $(ROOT)/core/api/msAPI_Tuner.c                              \
        $(ROOT)/core/api/msAPI_Flash.c                              \
        $(ROOT)/core/api/msAPI_ChProc.c                             \
        $(ROOT)/core/api/msAPI_Bootloader.c                         \
        $(ROOT)/core/api/msAPI_OSD.c                                \
        $(ROOT)/core/api/msAPI_BDMA.c                               \
        $(ROOT)/core/api/msAPI_CPU.c                                \
        $(ROOT)/core/api/msAPI_OSD2.c                               \
        $(ROOT)/core/api/msAPI_OSD_Resource.c                       \
        $(ROOT)/core/api/msAPI_DTVSystem.c                          \
        $(ROOT)/core/api/msAPI_ATVSystem.c                          \
        $(ROOT)/core/api/msAPI_MHEG5.c                              \
        $(ROOT)/core/api/msAPI_Memory.c                             \
        $(ROOT)/core/api/msAPI_Tuning.c                             \
        $(ROOT)/core/api/msAPI_DrvInit.c                            \
        $(ROOT)/core/api/msAPI_APEngine.c                           \
        $(ROOT)/core/api/msAPI_WMA.c                                \
        $(ROOT)/core/api/msAPI_Power.c                              \
        $(ROOT)/core/api/msAPI_JPEG_MM.c                            \
        $(ROOT)/core/api/msAPI_Music.c                              \
        $(ROOT)/core/api/msAPI_PVR.c                                \
        $(ROOT)/core/api/msAPI_Player.c                             \
        $(ROOT)/core/api/msAPI_Global.c                             \
        $(ROOT)/core/api/msAPI_MailBox.c                            \
        $(ROOT)/core/api/audio/msAPI_audio.c                        \
        $(ROOT)/core/api/IOUtil.c                                   \
        $(ROOT)/core/api/msAPI_DataStreamIO.c                       \
        $(ROOT)/core/api/msAPI_FreqTableCADTV.c                     \
        $(ROOT)/core/api/msAPI_BulkFileSystem.c                     \
        $(ROOT)/core/api/msAPI_PVRFileSystem.c                      \
        $(ROOT)/core/api/msAPI_MHL.c                                \
	      $(ROOT)/core/api/msAPI_OpCache.c                            \
   	    $(ROOT)/core/api/apiDTVFreqTable.c                      \
        $(ROOT)/core/api/apiDTVSatTable.c			\
        $(ROOT)/core/api/MApp_Compression.c                      \


FS_FILES += \
        $(ROOT)/core/api/n51fs/msAPI_FCtrl.c                        \
        $(ROOT)/core/api/n51fs/msAPI_FAT.c                          \
        $(ROOT)/core/api/n51fs/FAT_Cache.c                          \
        $(ROOT)/core/api/n51fs/FSUtil.c                             \
        $(ROOT)/core/api/n51fs/msAPI_MSDCtrl.c                      \
        $(ROOT)/core/api/n51fs/msAPI_FSEnv.c                        \
        $(ROOT)/core/api/n51fs/msAPI_N51FS.c                         \
        $(ROOT)/core/api/n51fs/N51FS_File.c                          \
        $(ROOT)/core/api/n51fs/N51FS_Index.c                         \
        $(ROOT)/core/api/n51fs/N51FS_Bitmap.c                        \
        $(ROOT)/core/api/msAPI_FS_SysInfo.c                         \


SI_FILES += \
        $(ROOT)/core/middleware/si/dvb/mapp_si_if.c                     \
        $(ROOT)/core/middleware/si/dvb/mapp_si_util.c                   \
        $(ROOT)/core/middleware/demux/msAPI_demux.c                 \
        $(ROOT)/core/middleware/si/dvb/mapp_demux_if.c                 \

OAD_FILES += \
        $(ROOT)/core/middleware/oad/dvb/msAPI_oad_parser.c              \

USB_UPGRADE += \
        $(ROOT)/core/middleware/usbupgrade/mw_usbdownload.c         \
        $(ROOT)/core/middleware/usbupgrade/mapp_swupdate.c             \

UTIL_FILES += \
        $(ROOT)/core/middleware/mwutil/mw_debug.c                   \
        $(ROOT)/core/util/util_minidump.c                           \
        $(ROOT)/core/util/util_symbol.c                             \
        $(ROOT)/core/util/autotest.c                                \
        $(ROOT)/core/api/Thai_Parser/msAPI_Thai_Shaping.c           \
        $(ROOT)/core/api/Thai_Parser/msAPI_Thai_StateTables.c       \
        $(ROOT)/core/api/Arabic_Parser/msAPI_Arabic_Parser.c        \
        $(ROOT)/core/util/mstar_debug.c                             \
        $(ROOT)/core/util/uartdebug.c                               \
        $(ROOT)/core/util/util_checkversion.c                       \


SRC_FILE += \
        $(DRV_FILES)                                                 \
        $(FS_FILES)                                                  \
        $(SI_FILES)                                                 \
        $(API_FILES)                                                \
        $(MM_FILES)                                                 \
        $(MHEG5_FILES)                                              \
        $(TTX_FILES)                                                \
        $(CC_FILES)                                                 \
        $(OAD_FILES)                                                \
        $(SUB_FILES)                                                \
        $(USB_UPGRADE)                                              \
        $(UTIL_FILES)                                               \


INC_DIR  += \
        -I$(ROOT)/project/image                                     \
        -I$(ROOT)/project/mmap                                      \
        -I$(ROOT)/core/driver/interface                             \
        -I$(ROOT)/core/driver/sys/$(chip_name)/include                   \
        -I$(ROOT)/core/driver/sc/$(chip_name)/include                    \
        -I$(ROOT)/core/bin/$(chip_name)/audio                            \
        -I$(ROOT)/core/util/include                                 \
        -I$(ROOT)/core/api/include                                  \
        -I$(ROOT)/core/middleware/teletext/include                  \
        -I$(ROOT)/core/middleware/teletext/core/include             \
        -I$(ROOT)/core/middleware/cni/include                       \
        -I$(ROOT)/core/api/n51fs/include                            \
        -I$(ROOT)/core/api/audio/include                            \
        -I$(ROOT)/core/middleware/ci/include                        \
        -I$(ROOT)/core/middleware/mwutil/include                    \
        -I$(ROOT)/core/middleware/mheg5/include                     \
        -I$(ROOT)/core/middleware/huffman/dvb/include               \
        -I$(ROOT)/core/middleware/si/dvb/include                    \
        -I$(ROOT)/core/middleware/epg/dvb/include                   \
        -I$(ROOT)/core/middleware/subtitle/include                  \
        -I$(ROOT)/core/middleware/oad/dvb/include                   \
        -I$(ROOT)/core/middleware/demux/include                     \
        -I$(ROOT)/core/middleware/multimedia/include                \
        -I$(ROOT)/core/middleware/multimedia/stillimage/include     \
        -I$(ROOT)/core/middleware/include                           \
        -I$(ROOT)/core/middleware/usbupgrade/include                \
        -I$(ROOT)/include/std                                       \

LINT_INC  += \
        $(ROOT)/project/image                                       \
        $(ROOT)/core/bin/$(chip_name)/audio                              \
        $(ROOT)/core/util/include                                   \
        $(ROOT)/core/api/include                                    \
        $(ROOT)/core/middleware/teletext/include                    \
        $(ROOT)/core/middleware/cni/include                         \
        $(ROOT)/core/api/n51fs/include                              \
        $(ROOT)/core/api/audio/include                              \
        $(ROOT)/core/middleware/ci/include                          \
        $(ROOT)/core/middleware/mheg5/include                       \
        $(ROOT)/core/middleware/huffman/dvb/include                 \
        $(ROOT)/core/middleware/si/dvb/include                      \
        $(ROOT)/core/middleware/demux/include                       \
        $(ROOT)/core/middleware/multimedia/include                  \
        $(ROOT)/core/middleware/multimedia/stillimage/include       \
        $(ROOT)/core/middleware/subtitle/include                    \

##################################################################
# TV-AP
##################################################################
TVAP = $(ROOT)/tv-ap

APP_FILES += \
        $(TVAP)/dvb/app/MApp_LoadFontInit.c                        \
        $(TVAP)/dvb/app/MApp_XC_PQ.c                               \
        $(TVAP)/dvb/app/MApp_XC_Sys.c                              \
        $(TVAP)/dvb/app/MApp_Scaler.c                              \
        $(TVAP)/dvb/app/MApp_MVDMode.c                             \
        $(TVAP)/dvb/app/MApp_VDMode.c                              \
        $(TVAP)/dvb/app/MApp_Standby.c                             \
        $(TVAP)/dvb/app/MApp_DataBase.c                            \
        $(TVAP)/dvb/app/MApp_Init.c                                \
        $(TVAP)/dvb/app/MApp_IR.c                                  \
        $(TVAP)/dvb/app/MApp_MultiTasks.c                          \
        $(TVAP)/dvb/app/MApp_TV.c                                  \
        $(TVAP)/dvb/app/MApp_RestoreToDefault.c                    \
        $(TVAP)/dvb/app/MApp_DDC2BI.c                              \
        $(TVAP)/dvb/app/MApp_SaveData.c                            \
        $(TVAP)/dvb/app/MApp_ATV_Scan.c                            \
        $(TVAP)/dvb/app/MApp_SignalMonitor.c                       \
        $(TVAP)/dvb/app/MApp_TopStateMachine.c                     \
        $(TVAP)/dvb/app/MApp_AnalogInputs.c                        \
        $(TVAP)/dvb/app/MApp_GlobalFunction.c                      \
        $(TVAP)/dvb/app/MApp_Sleep.c                               \
        $(TVAP)/dvb/app/MApp_CharTable.c                           \
        $(TVAP)/dvb/app/MApp_Scan.c                                \
        $(TVAP)/dvb/app/MApp_OAD.c                                 \
        $(TVAP)/dvb/app/MApp_USBDownload.c                         \
        $(TVAP)/dvb/app/MApp_OSDPage_Main.c                        \
        $(TVAP)/dvb/app/MApp_Subtitle.c                            \
        $(TVAP)/dvb/app/MAPP_ChannelChange.c                       \
        $(TVAP)/dvb/app/MApp_SI_Parse.c                            \
        $(TVAP)/dvb/app/MApp_Audio.c                               \
        $(TVAP)/dvb/app/MApp_ATVProc.c                             \
        $(TVAP)/dvb/app/MApp_InputSource.c                         \
        $(TVAP)/dvb/app/MApp_CIMMI_Input.c                         \
        $(TVAP)/dvb/app/MApp_MSD.c                                 \
        $(TVAP)/dvb/app/MApp_AVSync.c                              \
        $(TVAP)/dvb/app/MApp_Main.c                                \
        $(TVAP)/dvb/app/MApp_MassStorage.c                         \
        $(TVAP)/dvb/app/MApp_FileBrowser.c                         \
        $(TVAP)/dvb/app/MApp_Font_Dynamic_MVF.c                    \
        $(TVAP)/dvb/app/MApp_APEngine.c                            \
        $(TVAP)/dvb/app/MApp_BlueScreen.c                          \
        $(TVAP)/dvb/app/MApp_PVR.c                                 \
        $(TVAP)/dvb/app/MApp_TimeShift.c                           \
        $(TVAP)/dvb/app/MApp_Record.c                              \
        $(TVAP)/dvb/app/MApp_Playback.c                            \
        $(TVAP)/dvb/app/MApp_PVR_Browser.c                         \
        $(TVAP)/dvb/app/MApp_CADTV_Proc.c                          \
        $(TVAP)/dvb/app/MApp_CIMMI.c                               \
        $(TVAP)/dvb/app/MApp_BlockSys.c                            \
        $(TVAP)/dvb/app/MApp_ChannelList.c                         \
        $(TVAP)/dvb/app/MApp_ChList_Main.c                         \
        $(TVAP)/dvb/app/MApp_PrEdit_Main.c                         \
        $(TVAP)/dvb/app/MApp_EpgTimer.c                            \
        $(TVAP)/dvb/app/MApp_PIP.c                                 \
        $(TVAP)/dvb/app/MApp_MenuChannel.c                     \
	$(TVAP)/dvb/app/MApp_GammaAdjust.c                         \
UI_FILES += \
        $(TVAP)/dvb/ui2/MApp_ATV_ManualTuning_Main.c                \
        $(TVAP)/dvb/ui2/MApp_DTV_ManualTuning_Main.c                \
        $(TVAP)/dvb/ui2/MApp_CADTV_ManualTuning_Main.c              \
        $(TVAP)/dvb/ui2/MApp_InputSource_Main.c                     \
        $(TVAP)/dvb/ui2/MApp_Install_Main.c                         \
        $(TVAP)/dvb/ui2/MApp_Menu_Main.c                            \
        $(TVAP)/dvb/ui2/MApp_PVR_Main.c                             \
        $(TVAP)/dvb/ui2/MApp_UiEpg.c                                \
        $(TVAP)/dvb/ui2/MApp_UiPvr.c                                \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACToad.c                           \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTcoexistWin.c                    \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTatvmanualtuning.c               \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTaudiovolume.c                   \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTaudlang.c                       \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTautotuning.c                    \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTchannelinfo.c                   \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTchlist.c                        \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTcimmi.c                         \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTcadtvmanualtuning.c             \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTdtvmanualtuning.c               \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTexpertmenu.c                    \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTeffectsetting.c                 \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTepg.c                           \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTepop.c                          \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTfactorymenu.c                   \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTdesignmenu.c                   \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTflippage.c                      \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTglobal.c                        \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACThotkey.c                        \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTinputsource.c                   \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTinstall.c                       \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTmainpage.c                      \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTmenudlgfunc.c                   \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTmenufunc.c                      \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTmsgbox.c                        \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTnetconfig.c                     \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTpredit.c                        \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTscreensaver.c                   \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTsetclockfunc.c                  \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTsublang.c                       \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTtenkey.c                        \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTtuneconfirmfunc.c               \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTpvr.c                           \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTpvrBrowser.c                    \
        $(TVAP)/dvb/ui2/MApp_ZUI_Main.c                             \
        $(TVAP)/dvb/ui2/MApp_ZUI_GlobalFunction.c                   \
        $(TVAP)/dvb/ui2/MApp_UiMenuDef.c                            \
        $(TVAP)/dvb/ui2/osdcomposer/OSDcp_readbin.c                 \
        $(TVAP)/dvb/ui2/osdcomposer/OSDcp_global.c                  \
        $(TVAP)/dvb/ui2/osdcomposer/OSDcp_loadfont.c                \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTDishSetup.c                  \


PROJS_FILES += \
        $(ROOT)/project/image/dvbt/InfoBlock.c                      \
        $(ROOT)/project/image/imginfo.c                            \

CHIP_FILES += \
        $(ROOT)/chip/$(chip_name)/device/gpio/GPIO.c                     \
        $(ROOT)/core/driver/power/$(chip_name)/drvPower_cus.c            \
        $(ROOT)/core/driver/power/$(chip_name)/drvPower.c                \
        $(ROOT)/chip/$(chip_name)/color/color.c                          \

DEVICES_FILES += \
        $(ROOT)/device/keypad/$(chip_name)/msKeypad.c                    \
        $(ROOT)/device/ir/$(chip_name)/msIR.c                            \
        $(ROOT)/device/flash/msFlash.c                              \
        $(ROOT)/device/hdmiswitch/HdmiSwitch.c                      \
        $(ROOT)/device/if_demodulator/IF_Demodulator.c              \
        $(ROOT)/device/cofdm/COFDM_Demodulator.c                    \
        $(ROOT)/device/qam/QAM_Demodulator.c                        \
        $(ROOT)/device/cofdm/drvDemod.c			                        \
        $(ROOT)/device/cofdm/apiDigiTuner.c                         \
        $(ROOT)/device/cofdm/halVif.c                               \
        $(ROOT)/device/tuner/Tuner.c                                \
        $(ROOT)/device/panel/Panel.c                                \
        $(ROOT)/device/panel_dft/DemoFineTune.c                     \
        $(ROOT)/device/audioamp/Audio_amplifier.c                   \
        $(ROOT)/device/ursa/drvUrsaMFC.c                            \
        $(ROOT)/device/ursa/MAPP_ISP.c                              \
        $(ROOT)/device/ursa/drvUrsa6M30.c                           \
        $(ROOT)/device/ursa/drvUrsa6M40.c                           \
        $(ROOT)/device/mhl/Mhl.c                                   \
        $(ROOT)/device/cofdm/demodulator_T2.c            \
        $(ROOT)/device/ursa/drvTcon_Inx8903.c                         \

#ifeq ($(ENABLE_DVBS),ENABLE)
DVBS_FILES += $(ROOT)/device/cofdm/INTERN_DVBS.c
#endif

# Source files
SRC_FILE += \
        $(APP_FILES)                                               \
        $(ZUI_FILES)                                               \
        $(UI_FILES)                                                \
        $(PROJS_FILES)                                             \
        $(CHIP_FILES)                                              \
        $(DEVICES_FILES)                                           \

ifeq ($(ENABLE_DVBS),ENABLE)
SRC_FILE += $(DVBS_FILES)
endif

# Add "Header (include) file" directories here ...
INC_DIR  += \
        -I$(ROOT)/project/boarddef                                 \
        -I$(ROOT)/project/swdef                                    \
        -I$(ROOT)/project/image/dvbt                               \
        -I$(ROOT)/project/image/bininfo/$(chip_name)                    \
        -I$(ROOT)/project/mmap                                     \
        -I$(ROOT)/chip/$(chip_name)/color/include                       \
        -I$(ROOT)/chip/$(chip_name)/device/gpio                         \
        -I$(ROOT)/chip/$(chip_name)/image                               \
        -I$(ROOT)/device/panel                                     \
        -I$(ROOT)/device/panel/include                             \
        -I$(ROOT)/device/panel_dft                                 \
        -I$(ROOT)/device/flash                                     \
        -I$(ROOT)/device/keypad/$(chip_name)                            \
        -I$(ROOT)/device/ir/$(chip_name)                                \
        -I$(ROOT)/device/hdmiswitch                                \
        -I$(ROOT)/device/cofdm                                     \
        -I$(ROOT)/device/cofdm/EXTERN_DTMB                         \
        -I$(ROOT)/device/qam                                       \
        -I$(ROOT)/device/tuner                                     \
        -I$(ROOT)/device/if_demodulator                            \
        -I$(ROOT)/device/include                                   \
        -I$(ROOT)/device/audioamp                                  \
        -I$(ROOT)/core/drv_bsp/include                             \
        -I$(ROOT)/device/ursa                                      \
        -I$(TVAP)/common/app/include                               \
        -I$(TVAP)/common/zui/include                               \
        -I$(TVAP)/common/dmp/include                               \
        -I$(TVAP)/dvb/app/include                                  \
        -I$(TVAP)/dvb/ui2/include                                  \
        -I$(TVAP)/dvb/ui2/osdcomposer/include                      \
        -I$(TVAP)/dvb/ui2/res960x540x565/osdcomposer/include      \
        -I$(ROOT)/device/mhl                                       \


LINT_INC  += \
        $(ROOT)/project/boarddef                                   \
        $(ROOT)/project/swdef                                      \
        $(ROOT)/project/image/dvbt                                 \
        $(ROOT)/project/image/bininfo/$(chip_name)                      \
        $(ROOT)/project/mmap                                       \
        $(ROOT)/chip/$(chip_name)/device/gpio                           \
        $(ROOT)/chip/$(chip_name)/image                                 \
        $(ROOT)/chip/$(chip_name)/color/include                         \
        $(ROOT)/device/panel                                       \
        $(ROOT)/device/panel_dft                                   \
        $(ROOT)/device/panel/include                               \
        $(ROOT)/device/flash                                       \
        $(ROOT)/device/keypad/$(chip_name)                              \
        $(ROOT)/device/ir/$(chip_name)                                  \
        $(ROOT)/device/hdmiswitch                                  \
        $(ROOT)/device/cofdm                                       \
        $(ROOT)/device/qam                                         \
        $(ROOT)/device/tuner                                       \
        $(ROOT)/device/if_demodulator                              \
        $(ROOT)/device/include                                     \
        $(ROOT)/device/audioamp                                    \
        $(ROOT)/device/ursa                                    \
        $(TVAP)/dvb/app/include                                    \
        $(TVAP)/dvb/ui2/include                                    \
        $(TVAP)/dvb/ui2/osdcomposer/include                        \
        $(TVAP)/dvb/ui2/res960x540x565/osdcomposer/include        \
        $(ROOT)/device/mhl                                         \

#LDLIB += -Wl,--whole-archive $(ROOT)/core/lib/milan/libprana_milan_a.a -Wl,--no-whole-archive
#PRANA_LIB   = $(ROOT)/core/lib/milan/libprana_milan.a
ifeq ($(AEON_TYPE),aeonR2)
LDLIB += -Wl,--whole-archive $(ROOT)/core/lib/$(chip_name)/libprana_$(chip_name)_aeonR2.a -Wl,--no-whole-archive
else
LDLIB += -Wl,--whole-archive $(ROOT)/core/lib/$(chip_name)/libprana_$(chip_name)_a.a -Wl,--no-whole-archive
endif


DRV_LIB_PATH   = $(ROOT)/core/driver
API_LIB_PATH   = $(ROOT)/core/api
DRV_BSP_PATH   = $(ROOT)/core/drv_bsp/$(chip_name)_nos_r2m_32m/lib
MIDDLE_LIB_PATH   = $(ROOT)/core/middleware



DTV_LIB += \
    $(API_LIB_PATH)/mvf/libmvf.a                                   \
    $(API_LIB_PATH)/crc/libcrc.a                                   \


#Middleware libraries


DTV_LIB += \
    $(MIDDLE_LIB_PATH)/cni/libcni_aeonR2.a                     		\
    $(API_LIB_PATH)/mvf/libmvf_aeonR2.a                        		\
    $(MIDDLE_LIB_PATH)/teletext/core/libttx_core_aeonR2.a         \
    $(MIDDLE_LIB_PATH)/subtitle/libsub_aeonR2.a						        \
    $(MIDDLE_LIB_PATH)/huffman/dvb/libdvbhuffman_aeonR2.a         \
    $(MIDDLE_LIB_PATH)/si/dvb/libdvbsi_aeonR2.a                   \
    $(MIDDLE_LIB_PATH)/epg/dvb/libdvbepgdb_aeonR2.a               \
    $(MIDDLE_LIB_PATH)/oad/dvb/libdvboad_aeonR2.a                 \



ENABLE_HK_DRM_GENCODE=0

BIN_INFO = $(ROOT)/project/image/bininfo/$(chip_name)/BinInfo.h

REBUILD_FILES=$(TVAP)/dvb/ui2/MApp_ZUI_ACTmenufunc.c

#include project/build/FILES_COMMON_WHISKY.mk
include project/build/FILES_COMMON_$(CHIP_FAMILY).mk

DTV_LIB += \
    $(COMMON_DTV_LIB)                   \
