/*
 *           Copyright 2010 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be 
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */


/*
 *           Copyright 2010 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be 
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */


#ifndef LockSignal_source_h_h
    #define LockSignal_source_h_h

    #include "avl_dvbsx.h"

	#ifdef AVL_CPLUSPLUS
extern "C" {
	#endif

    struct Signal_Level
    {
	    AVL_uint16 SignalLevel;
        AVL_int16 SignalDBM;
    };

    void AVL_DVBSx_Error_Dispose(AVL_DVBSx_ErrorCode r);
    AVL_DVBSx_ErrorCode Initialize(struct AVL_DVBSx_Chip * pAVLChip,struct AVL_Tuner * pTuner);
    AVL_DVBSx_ErrorCode LockSignal(void);

	#ifdef AVL_CPLUSPLUS
}
	#endif
#endif
