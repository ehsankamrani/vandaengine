// This code contains NVIDIA Confidential Information and is disclosed 
// under the Mutual Non-Disclosure Agreement.
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES 
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO 
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT, 
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
// 
// Information and code furnished is believed to be accurate and reliable. 
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such 
// information or for any infringement of patents or other rights of third parties that may 
// result from its use. No license is granted by implication or otherwise under any patent 
// or patent rights of NVIDIA Corporation. Details are subject to change without notice. 
// This code supersedes and replaces all information previously supplied. 
// NVIDIA Corporation products are not authorized for use as critical 
// components in life support devices or systems without express written approval of 
// NVIDIA Corporation.
//
// Copyright 2008, NVIDIA Corporation. All rights reserved.

#ifndef __AG_PERFMON_GPU_EVENT_SRC_API___
#define __AG_PERFMON_GPU_EVENT_SRC_API___

#include "AgPerfMonEventAPI.h"
#include "AgPerfmonEventSrcAPI.h"
#include "cuda.h"
#include "driver_types.h"
#include "stdlib.h"

#define NOMINMAX
#include "windows.h"

#define DEFINE_GPU_EVENT(name) name,
enum AgGPUPerfEventEnum
{
#include "AgPerfMonGPUEventDefs.h"
	AgGPUPerfEventNumEvents
};
#undef DEFINE_GPU_EVENT

#ifndef __DEVICE_EMULATION__
#define INTERNAL_CUDA_EVENTS					0
#define	KERNEL_USER_DATA						0
#define UTILIZATION_CALCULATION					0
#endif

#define AGPERFMON_USES_CUDART					1

#ifdef PXD_COMPILER_CUDA
	#define CUDA_ALIGN_16 __align__(16)
#else
	#define CUDA_ALIGN_16
#endif

typedef struct CUDA_ALIGN_16 kernelEvent_sd
{
	AgU16 block;
	AgU8  warp;
	AgU8  mpId;
	AgU8  hwWarpId;
	AgU8  userDataCfg;
	AgU16 eventId;
	AgU32 startTime;
	AgU32 endTime;
	AgU32 userData[4];
}kernelEvent_st;

#define KERNEL_DATA_TYPE							1
#define KERNEL_TSTAMP_TYPE							2
#define KERNEL_PM_TYPE								3

#define USER_DATA_FIELD_0							0
#define USER_DATA_FIELD_1							1
#define USER_DATA_FIELD_2							2
#define USER_DATA_FIELD_3							3

#if INTERNAL_CUDA_EVENTS
#define KERNEL_START_EVENT(extMem, kernelEnum)		\
int4 *evPtr;										\
kernelEvent_st ev;									\
{													\
	if (extMem && (threadIdx.x & 0x1F) == 0)		\
	{												\
		int smidVal;								\
		int hwWarpId;								\
		int smclock;								\
		asm("mov.u32" " %0, %clock;" : "=r" (smclock)); \
		asm("mov.u32" " %0, %smid;" : "=r" (smidVal)); \
		asm("mov.u32" " %0, %warpid;" : "=r" (hwWarpId)); \
		ev.block                = blockIdx.x;	    \
		ev.warp                 = threadIdx.x >> 5; \
		ev.mpId                 = smidVal;			\
		ev.eventId			    = kernelEnum;		\
		ev.hwWarpId             = hwWarpId;			\
		ev.startTime    		= smclock;			\
		ev.endTime  		    = smclock;			\
		ev.userDataCfg			= 0;				\
		evPtr = ((int4 *) extMem) + ((blockIdx.x * (blockDim.x>>5) + (threadIdx.x>>5))*2); \
		*evPtr = *(int4 *) &ev;						\
	} else evPtr = 0;								\
}
#if KERNEL_USER_DATA

#if UTILIZATION_CALCULATION
#define KERNEL_STOP_EVENT(extMem, kernelEnum)			\
{														\
    if (evPtr)											\
	{													\
		asm("mov.u32" " %0, %clock;" : "=r" (ev.endTime));	\
		ev.userDataCfg |= (KERNEL_PM_TYPE << (0 << 1));			\
		asm("mov.u32" " %0, %pm0;" : "=r" (ev.userData[0]));	\
		*evPtr = *(int4 *) &ev;							\
		evPtr++;										\
		*evPtr = *(int4 *) &ev.userData[0];			\
	}													\
}
#else
#define KERNEL_STOP_EVENT(extMem, kernelEnum)			\
{														\
    if (evPtr)											\
	{													\
		asm("mov.u32" " %0, %clock;" : "=r" (ev.endTime));	\
		*evPtr = *(int4 *) &ev;							\
		evPtr++;										\
		*evPtr = *(int4 *) &ev.userData[0];				\
	}													\
}
#endif //utilization calculation

#define KERNEL_DATA_EVENT(dataIndex, val)				\
{														\
	if (evPtr)											\
	{													\
		ev.userDataCfg |= (KERNEL_DATA_TYPE << (dataIndex << 1)); \
		ev.userData[dataIndex] = val;					\
	}													\
}

#define KERNEL_TSTAMP_EVENT(dataIndex)					\
{														\
	if (evPtr)											\
	{													\
		ev.userDataCfg |= (KERNEL_TSTAMP_TYPE << (dataIndex << 1));		\
		asm("mov.u32" " %0, %clock;" : "=r" (ev.userData[dataIndex]));	\
	}													\
}

#define KERNEL_PERF_CNT_0_EVENT(dataIndex)				\
{														\
	if (evPtr)											\
	{													\
		ev.userDataCfg |= (KERNEL_PM_TYPE << (dataIndex << 1));			\
		asm("mov.u32" " %0, %pm0;" : "=r" (ev.userData[dataIndex]));	\
	}													\
}

#define KERNEL_PERF_CNT_1_EVENT(dataIndex)				\
{														\
	if (evPtr)											\
	{													\
		ev.userDataCfg |= (KERNEL_PM_TYPE << (dataIndex << 1));			\
		asm("mov.u32" " %0, %pm1;" : "=r" (ev.userData[dataIndex]));	\
	}\
}
#define KERNEL_PERF_CNT_2_EVENT(dataIndex)				\
{														\
	if (evPtr)											\
	{													\
		ev.userDataCfg |= (KERNEL_PM_TYPE << (dataIndex << 1));			\
		asm("mov.u32" " %0, %pm2;" : "=r" (ev.userData[dataIndex]));	\
	}\
}
#define KERNEL_PERF_CNT_3_EVENT(dataIndex)				\
{														\
	if (evPtr)											\
	{													\
		ev.userDataCfg |= (KERNEL_PM_TYPE << (dataIndex << 1));			\
		asm("mov.u32" " %0, %pm3;" : "=r" (ev.userData[dataIndex]));	\
	}\
}

#define KERNEL_MEMORY_EVENT(extMem, kernelEnum)

#else
#define KERNEL_STOP_EVENT(extMem, kernelEnum)			\
{														\
    if (evPtr)											\
	{													\
		int regVal;										\
		asm("mov.u32" " %0, %clock;" : "=r" (regVal));	\
		evPtr->w = regVal;								\
	}\
}

#define KERNEL_DATA_EVENT(dataIndex, val)
#define KERNEL_TSTAMP_EVENT(dataIndex)
#define KERNEL_PERF_CNT_0_EVENT(dataIndex)
#define KERNEL_PERF_CNT_1_EVENT(dataIndex)
#define KERNEL_PERF_CNT_2_EVENT(dataIndex)
#define KERNEL_PERF_CNT_3_EVENT(dataIndex)
#endif


#else
#define KERNEL_START_EVENT(extMem, kernelEnum)
#define KERNEL_STOP_EVENT(extMem, kernelEnum)
#define KERNEL_DATA_EVENT(dataIndex, val)

#define KERNEL_TSTAMP_EVENT(dataIndex)
#define KERNEL_PERF_CNT_0_EVENT(dataIndex)
#define KERNEL_PERF_CNT_1_EVENT(dataIndex)
#define KERNEL_PERF_CNT_2_EVENT(dataIndex)
#define KERNEL_PERF_CNT_3_EVENT(dataIndex)
#endif

#if AGPERFMON_USES_CUDART
typedef cudaEvent_t			pmonCudaEvent;
#else
typedef CUevent				pmonCudaEvent;
#endif


typedef struct gpuPerfSubmittedEvents_sd
{
	AgGPUPerfEventEnum	perfmonEnumId;									// id of submitted events
	pmonCudaEvent		cudaEventId;									// id of submitted events
	AgU8				eventType;										// start/stop
	AgU32				startOffset;
	AgU32				endOffset;
}gpuPerfSubmittedEvents_st;


typedef struct gpuPerfThreadInfo_sd
{
	gpuPerfSubmittedEvents_st	*submittedEvents;						// submitted events
	pmonCudaEvent		cudaGPURefEvent;								// ref for gpu events to get elapsed time	
	AgU8				*gpuEventMemory;
	DWORD				threadId;
	int					*hostCopiedGPUEventMemory;
	int					*currentHostGPUEventMemory;
	AgU8				*currentGPUEventPtr;
	AgU32				submittedGPUKernelEvents;
	AgU16				numSubmittedEvents;								// tracks events initiated but not yet sent to perfmon
	AgU16				totalAllocatedEvents;							// number of submitted events allocated
	
}gpuPerfThreadInfo_st;

typedef struct gpuSMData_sd
{
	unsigned long gpuSMTimer;
	unsigned long savedEnd;
	unsigned long deadtime;
	unsigned long instructionCount;
}gpuSMData_st;

class AgGPUPerfUtils
{
public:

	AgGPUPerfUtils(AgPerfUtils *agPerfPtr, int gpuNum);
    ~AgGPUPerfUtils();
	bool isEnabled();
	bool isEventEnabled(AgGPUPerfEventEnum id);
	void startEvent(AgGPUPerfEventEnum id);
	void stopEvent(AgGPUPerfEventEnum id);
	void gatherGPUEvents();
	void syncGPUClock();
	int *getGPUPerfmonMemoryPtr(int blocks, int threads);

private:
	gpuPerfThreadInfo_st* getThreadCtxPtr();
	void getGpuFrequencyInfo(int gpuNum);
	void processKernelInternalEvents(gpuPerfThreadInfo_st *threadContext_p, AgU32 startOffset, AgU32 endOffset, AgU32 startEventTime);
	
    
	AgPmHANDLE			mhAgPm;

	AgEventID			mPerfmonEventIds[AgGPUPerfEventNumEvents+1];		// perfmon event
	static const char	*mEventNames[AgGPUPerfEventNumEvents+1];			// perfmon event names

	AgEventID			mPerfmonUtilization;
	AgEventID			mPerfmonGPURefEvent;								// perfmon event for reference clock
	AgEventID           mPerfmonGPUGatherEvents;                            // perfmon event for gathering internal events
	AgEventID			mSmCnt0;
	AgEventID			mSmCnt1;
	AgEventID			mSmCnt2;
	AgEventID			mSmCnt3;
	AgEventID			mPerfmonInstructionUtilization;
	gpuPerfThreadInfo_st *mThreadCntx;										// tracks cuda events per thread
	AgU16				mNumAllocatedThreads;
	AgU16				mNumCurrentThreads;
	CRITICAL_SECTION	mCriticalSection;
	unsigned long		mClockFreq;
	unsigned long		mNumSMs;
	gpuSMData_st		*mGpuSMData;
	CUcontext			mcuContext;
};

#endif /** _AG_PERFMON_GPU_EVENT_SRC_API___ */
