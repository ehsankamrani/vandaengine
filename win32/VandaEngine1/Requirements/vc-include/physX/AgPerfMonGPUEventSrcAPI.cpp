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

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "AgPerfMonGPUEventSrcAPI.h"
#if AGPERFMON_USES_CUDART
#include "cuda_runtime_api.h"
#else
#include "cuda.h"
#endif

/* AgGPUPerfUtils */

#define DEFINE_GPU_EVENT(name) #name,
const char *AgGPUPerfUtils::mEventNames[] = {
#include "AgPerfMonGPUEventDefs.h"
	""
};
#undef DEFINE_GPU_EVENT

#define ENABLE_GPU_EVENTS						1

#define INITIAL_ALLOCATED_THREADS				4

#ifdef GPU_PERFORMANCE_COUNTERS2
typedef CUresult (CUDAAPI *cuGetNumCountersFnPtr)(CUcontext uCtx, unsigned long *pulCount);
typedef CUresult (CUDAAPI *cuGetCounterNameFnPtr)(CUcontext uCtx, unsigned long ulCounterIndex, char *pcName);
typedef CUresult (CUDAAPI *cuGetNumEventsFnPtr)(CUcontext pCtx, unsigned long *pulCount);
typedef CUresult (CUDAAPI *cuGetEventInfoFnPtr)(CUcontext pCtx, unsigned long ulEventIndex, char *pcName, float *pfTimestamp, float *pfGPUTime);
typedef CUresult (CUDAAPI *cuGetCounterValueFnPtr)(CUcontext uCtx, unsigned long ulEventIndex, unsigned long ulCounterIndex, unsigned long *pulValue);
typedef CUresult (CUDAAPI *cuFlushEventsFnPtr)(CUcontext pCtx);

cuGetNumCountersFnPtr	cuGetNumCounters	= NULL;
cuGetCounterNameFnPtr	cuGetCounterName	= NULL;
cuGetNumEventsFnPtr		cuGetNumEvents		= NULL;
cuFlushEventsFnPtr		cuFlushEvents		= NULL;
cuGetEventInfoFnPtr		cuGetEventInfo		= NULL;
cuGetCounterValueFnPtr	cuGetCounterValue	= NULL;
#endif

#define PMON_SUCCESS	1
#define PMON_FAIL		0
static void ResolveCounterFunctions();
static void pmonEventCreate(pmonCudaEvent *cudaEventId);
static void pmonEventRecord(pmonCudaEvent cudaEventId);
static AgU8 pmonEventQuery(pmonCudaEvent cudaEventId);
static void pmonMemcpyDtoH(int *hostMemory, AgU8* gpuMemory, unsigned int length);
static void pmonEventElapsedTime(float *elapsedTime, pmonCudaEvent refEvent, pmonCudaEvent cudaEventId);
static void pmonEventSynchronize(pmonCudaEvent cudaEvent);
static void pmonContextSynchronize();
static void pmonDeviceMalloc(AgU8 **gpuEventMemory, unsigned int length);
static void pmonHostMalloc(int **hostMemory, unsigned int length);


AgGPUPerfUtils::AgGPUPerfUtils(AgPerfUtils *perfPtr, int gpuNum)
{
	assert(perfPtr);

	if (perfPtr != NULL)
	{
		mhAgPm = perfPtr->getHAgPm();
#ifdef ENABLE_GPU_EVENTS
		if (perfPtr->isLibraryLoaded())  // only initialize if the library is loaded
		{
			// register the perfmon event names
			for (int i = 0; i < AgGPUPerfEventNumEvents; i++)
			{
				mPerfmonEventIds[i] = AgPmRegisterEvent(mhAgPm, mEventNames[i]);
			}

			mPerfmonGPURefEvent		= AgPmRegisterEvent(mhAgPm, "gpuReferenceClockEvent");
			mPerfmonGPUGatherEvents	= AgPmRegisterEvent(mhAgPm, "gpuGatherEvents");
			mPerfmonUtilization		= AgPmRegisterEvent(mhAgPm, "gpustat-Utilization");
			mSmCnt0					= AgPmRegisterEvent(mhAgPm, "gpuSMstat-d0");
			mSmCnt1					= AgPmRegisterEvent(mhAgPm, "gpuSMstat-d1");
			mSmCnt2					= AgPmRegisterEvent(mhAgPm, "gpuSMstat-d2");
			mSmCnt3					= AgPmRegisterEvent(mhAgPm, "gpuSMstat-d3");
			mPerfmonInstructionUtilization		= AgPmRegisterEvent(mhAgPm, "gpustat-InstrUtil");

			mThreadCntx				= (gpuPerfThreadInfo_st *)malloc(INITIAL_ALLOCATED_THREADS*sizeof(gpuPerfThreadInfo_st));
			mNumAllocatedThreads	= INITIAL_ALLOCATED_THREADS;
			mNumCurrentThreads		= 0;

			for(int i=0; i < INITIAL_ALLOCATED_THREADS; i++)
			{
				mThreadCntx[i].threadId				= 0;
				mThreadCntx[i].numSubmittedEvents	= 0;
				mThreadCntx[i].totalAllocatedEvents	= 0;
			}

			getGpuFrequencyInfo(gpuNum);

			mGpuSMData				= (gpuSMData_st *)malloc(4 * sizeof(gpuSMData_st) * mNumSMs); // 4 SMs per TPC max

			//InitializeCriticalSection(&mCriticalSection);
			ResolveCounterFunctions();

			mcuContext = 0;

		}	
	}
#endif
}

AgGPUPerfUtils::~AgGPUPerfUtils()
{
#ifdef TBD
	// free up allocated memory, do we also need to release cuda events?
	for (int i = 0; i < mNumCurrentThreads; i++)
	{
		free(mThreadCntx[i].submittedEvents);
	}
	free(mThreadCntx);
#endif
}

void AgGPUPerfUtils::getGpuFrequencyInfo(int gpuNum)
{
	if(gpuNum >= 0)
	{
#if AGPERFMON_USES_CUDART
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, gpuNum);
		mClockFreq = prop.clockRate;	
		mNumSMs = prop.multiProcessorCount;
#else
		CUdevprop prop;
		int mpCount;
		cuDeviceGetProperties(&prop, gpuNum);
		mClockFreq = prop.clockRate;
		cuDeviceGetAttribute(&mpCount, CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, gpuNum);
		mNumSMs = mpCount;
#endif
	}
	else
	{
		assert(0);
		mClockFreq = 1;
	}
}

#define NUM_CUDA_EVENTS_TO_ALLOC							10

void AgGPUPerfUtils::startEvent(AgGPUPerfEventEnum id)
{
#ifdef ENABLE_GPU_EVENTS
	AgU16 numSubmittedEvents;

	gpuPerfThreadInfo_st *threadContext_p;

	assert(id < AgGPUPerfEventNumEvents);

	if (isEnabled() && isEventEnabled(id))
	{
		threadContext_p = getThreadCtxPtr();

		numSubmittedEvents = threadContext_p->numSubmittedEvents;

		if (numSubmittedEvents == threadContext_p->totalAllocatedEvents)
		{
			threadContext_p->submittedEvents = (gpuPerfSubmittedEvents_st *)realloc(threadContext_p->submittedEvents, sizeof(gpuPerfSubmittedEvents_st)* (threadContext_p->totalAllocatedEvents+NUM_CUDA_EVENTS_TO_ALLOC));
					
			for (int i = 0; i < NUM_CUDA_EVENTS_TO_ALLOC; i++)
			{
				pmonEventCreate(&threadContext_p->submittedEvents[threadContext_p->totalAllocatedEvents].cudaEventId);
				threadContext_p->totalAllocatedEvents++;
			}
		}

		threadContext_p->submittedEvents[numSubmittedEvents].perfmonEnumId = id;
		threadContext_p->submittedEvents[numSubmittedEvents].eventType = 0;//gpuStartEventType
		threadContext_p->submittedEvents[numSubmittedEvents].startOffset = 0xffffffff;

		pmonEventRecord(threadContext_p->submittedEvents[numSubmittedEvents].cudaEventId);

		threadContext_p->numSubmittedEvents++;

	}

#endif
}

void AgGPUPerfUtils::stopEvent(AgGPUPerfEventEnum id)
{
#ifdef ENABLE_GPU_EVENTS

	AgU16 numSubmittedEvents;

	gpuPerfThreadInfo_st *threadContext_p;

	assert(id < AgGPUPerfEventNumEvents);

	if (isEnabled() && isEventEnabled(id))
	{
		threadContext_p = getThreadCtxPtr();

		numSubmittedEvents = threadContext_p->numSubmittedEvents;

		if (numSubmittedEvents == threadContext_p->totalAllocatedEvents)
		{		
			threadContext_p->submittedEvents = (gpuPerfSubmittedEvents_st *)realloc(threadContext_p->submittedEvents, sizeof(gpuPerfSubmittedEvents_st) * (threadContext_p->totalAllocatedEvents+NUM_CUDA_EVENTS_TO_ALLOC));
					
			for (int i = 0; i < NUM_CUDA_EVENTS_TO_ALLOC; i++)
			{
				pmonEventCreate(&threadContext_p->submittedEvents[threadContext_p->totalAllocatedEvents].cudaEventId);
				threadContext_p->totalAllocatedEvents++;
			}
		}

		threadContext_p->submittedEvents[numSubmittedEvents].perfmonEnumId	= id;
		threadContext_p->submittedEvents[numSubmittedEvents].eventType		= 1;//gpuStopEventType

		pmonEventRecord(threadContext_p->submittedEvents[numSubmittedEvents].cudaEventId);

		threadContext_p->numSubmittedEvents++;

#ifdef GPU_PERFORMANCE_COUNTERS2_STOP_EVENT
		// we either synchronize in here, or move to the gather call and figure out how to correlate
		// Query the performance counters
        unsigned long ii, dwValue(0), dwCounterCount(0);
        float fTimestamp, fGPUTime;
        unsigned long ulEventCount(0xFFFFFFFF);
        char zName[512];
        
		cudaThreadSynchronize();
        cuGetNumEvents(mcuContext, &ulEventCount);
        if(ulEventCount > 0 && ulEventCount < 0xFFFFFFFF)
		{
			cuGetEventInfo(mcuContext, 0, zName, &fTimestamp, &fGPUTime); 
    
			cuGetNumCounters(mcuContext, &dwCounterCount);
			for(ii = 0; ii < dwCounterCount; ii++)
			{
				cuGetCounterName(mcuContext, ii, zName);
				cuGetCounterValue(mcuContext, 0, ii, &dwValue);
				printf("Counter: %s = %d\n", zName, dwValue);
			}
			cuFlushEvents(mcuContext);
        }
#endif
	}

#endif
}

void AgGPUPerfUtils::gatherGPUEvents()
{
#ifdef ENABLE_GPU_EVENTS
	gpuPerfSubmittedEvents_st	*submittedEvents_p;
	gpuPerfThreadInfo_st		*threadContext_p;
	float						gpuElapsedTime;
	AgU32						gpu10nSecs;
	AgU8						startStopEvent;
	
	if (isEnabled() && AgPmEventEnabled(mhAgPm, mPerfmonGPUGatherEvents))
	{
		threadContext_p		= getThreadCtxPtr();

		submittedEvents_p	= threadContext_p->submittedEvents;

		if (threadContext_p->numSubmittedEvents == 0)
            return;

		// if the first event has not finished yet, break out
		if (pmonEventQuery(submittedEvents_p[0].cudaEventId) != PMON_SUCCESS)
			return;

		AgPmSubmitEvent(mhAgPm, mPerfmonGPUGatherEvents, GetCurrentThreadId(), 0, AG_PERFMON_EV_START);

		if (threadContext_p->submittedGPUKernelEvents > 0)
		{
			pmonMemcpyDtoH(threadContext_p->hostCopiedGPUEventMemory, threadContext_p->gpuEventMemory,
							(unsigned int)(threadContext_p->currentGPUEventPtr - threadContext_p->gpuEventMemory));
		}

		// go through submitted array
		for (AgU16 i = 0; i < threadContext_p->numSubmittedEvents; i++)
		{	
			// call get cuda elapsed time against reference point
			pmonEventElapsedTime(&gpuElapsedTime, threadContext_p->cudaGPURefEvent, submittedEvents_p[i].cudaEventId);

			// multiply by 100000 to get in 10ns chunks for perfmon tics
			gpu10nSecs = (AgU32)(gpuElapsedTime * 100000);
			if (submittedEvents_p[i].eventType == 0)//gpuStartEventType
				startStopEvent = AG_PERFMON_EV_START;
			else
				startStopEvent = AG_PERFMON_EV_STOP;

			AgPmSubmitEvent(mhAgPm, mPerfmonEventIds[submittedEvents_p[i].perfmonEnumId], GetCurrentThreadId(), gpu10nSecs,  startStopEvent);		

#if INTERNAL_CUDA_EVENTS			
			if (startStopEvent == AG_PERFMON_EV_START)
			{
				if ((threadContext_p->submittedGPUKernelEvents > 0)  && (threadContext_p->submittedEvents[i].startOffset != 0xffffffff))
				{
					processKernelInternalEvents(threadContext_p, threadContext_p->submittedEvents[i].startOffset,
												threadContext_p->submittedEvents[i].endOffset, gpu10nSecs);
				}	
			}
#endif

		}

		threadContext_p->numSubmittedEvents = 0;

		threadContext_p->currentGPUEventPtr = threadContext_p->gpuEventMemory;
		threadContext_p->submittedGPUKernelEvents = 0;

		AgPmSubmitEvent(mhAgPm, mPerfmonGPUGatherEvents, GetCurrentThreadId(), 0, AG_PERFMON_EV_STOP);

#ifdef GPU_PERFORMANCE_COUNTERS2
        unsigned long ii, dwValue(0), dwCounterCount(0);
        float fTimestamp, fGPUTime;
        unsigned long ulEventCount(0xFFFFFFFF);
        char zName[512];
        
        cuGetNumEvents(mcuContext, &ulEventCount);
        if(ulEventCount > 0 && ulEventCount < 0xFFFFFFFF)
		{
			while (ulEventCount > 0)
			{
				cuGetEventInfo(mcuContext, ulEventCount - 1, zName, &fTimestamp, &fGPUTime); 
	    
				cuGetNumCounters(mcuContext, &dwCounterCount);
				for(ii = 0; ii < dwCounterCount; ii++)
				{
					cuGetCounterName(mcuContext, ii, zName);
					cuGetCounterValue(mcuContext, ulEventCount - 1, ii, &dwValue);
					printf("Counter: %s = %d\n", zName, dwValue);
				}
				ulEventCount--;
			}
        }
        
        cuFlushEvents(mcuContext);
#endif

	}
#endif
}

void AgGPUPerfUtils::syncGPUClock()
{
#ifdef ENABLE_GPU_EVENTS
	gpuPerfThreadInfo_st *threadContext_p;

	if (isEnabled() && AgPmEventEnabled(mhAgPm, mPerfmonGPURefEvent))
	{
		threadContext_p = getThreadCtxPtr();
		
		// pmonContextSynchronize();
		
		// issue a perfmon event
		pmonEventRecord(threadContext_p->cudaGPURefEvent);
		// pmonEventSynchronize(threadContext_p->cudaGPURefEvent);
		
		AgPmSubmitEvent(mhAgPm, mPerfmonGPURefEvent, GetCurrentThreadId(), 0, AG_PERFMON_EV_START);

		#ifdef GPU_PERFORMANCE_COUNTERS2
		if (!mcuContext)
		{
			if (cuCtxAttach(&mcuContext, 0) != CUDA_SUCCESS)
				mcuContext = 0;
		}
		#endif
	}
#endif
}

bool AgGPUPerfUtils::isEnabled()
{
	return AgPmEventLoggingEnabled(mhAgPm);
}
bool AgGPUPerfUtils::isEventEnabled(AgGPUPerfEventEnum id)
{
	return AgPmEventEnabled(mhAgPm, mPerfmonEventIds[id]);
}

#define INITIAL_EVENTS_ALLOCATED							32
#define NUM_THREADS_TO_ALLOC								1
#define GPU_INTERNAL_EVENTS_SIZE							(1024*1024)

gpuPerfThreadInfo_st* AgGPUPerfUtils::getThreadCtxPtr()
{
	gpuPerfThreadInfo_st *threadContext_p = NULL;
	DWORD threadID		= GetCurrentThreadId();
	bool threadMatch	= false;

	for (int i = 0; i < mNumCurrentThreads; i++)
	{
		if (mThreadCntx[i].threadId == threadID)
		{
			threadContext_p = &mThreadCntx[i];
			break;
		}
	}

	if (threadContext_p == NULL)
	{
		// need semaphore around this block
		//EnterCriticalSection(&mCriticalSection);

		if (mNumCurrentThreads == mNumAllocatedThreads)
		{
			mThreadCntx = (gpuPerfThreadInfo_st *)realloc((void *)mThreadCntx, (mNumAllocatedThreads+NUM_THREADS_TO_ALLOC)*sizeof(gpuPerfThreadInfo_st));
			mNumAllocatedThreads += NUM_THREADS_TO_ALLOC;
		}

		threadContext_p = &mThreadCntx[mNumCurrentThreads];
		
		mNumCurrentThreads++;
//
		//LeaveCriticalSection(&mCriticalSection);
		// end of semaphore block
			
		threadContext_p->submittedEvents = (gpuPerfSubmittedEvents_st *)malloc(sizeof(gpuPerfSubmittedEvents_st)* INITIAL_EVENTS_ALLOCATED);
				
		for (int i = 0; i < INITIAL_EVENTS_ALLOCATED; i++)
		{
			pmonEventCreate(&threadContext_p->submittedEvents[i].cudaEventId);	
		}
		pmonEventCreate(&threadContext_p->cudaGPURefEvent);

		pmonEventRecord(threadContext_p->cudaGPURefEvent);

		pmonEventSynchronize(threadContext_p->cudaGPURefEvent);

		threadContext_p->totalAllocatedEvents	= INITIAL_EVENTS_ALLOCATED;

		threadContext_p->numSubmittedEvents		= 0;

		threadContext_p->threadId				= threadID;

#if INTERNAL_CUDA_EVENTS
		pmonDeviceMalloc(&threadContext_p->gpuEventMemory, GPU_INTERNAL_EVENTS_SIZE);

		pmonHostMalloc(&threadContext_p->hostCopiedGPUEventMemory, GPU_INTERNAL_EVENTS_SIZE);

		threadContext_p->currentGPUEventPtr = threadContext_p->gpuEventMemory;

#endif
		threadContext_p->submittedGPUKernelEvents = 0;

	}

	return(threadContext_p);
}

int *AgGPUPerfUtils::getGPUPerfmonMemoryPtr(int blocks, int threads)
{
	int *returnPtr = NULL;

#if INTERNAL_CUDA_EVENTS
	if (isEnabled())
	{
		// associate the pointer into the buffer with the wrapped kernel event
		gpuPerfThreadInfo_st *threadContext_p = getThreadCtxPtr();
		AgU32 wrappedEventCnt = threadContext_p->numSubmittedEvents;

		if ((wrappedEventCnt == 0) ||
			(threadContext_p->submittedEvents[wrappedEventCnt-1].startOffset != 0xffffffff))
		{
			assert(!"getGPUPerfmonMemoryPtr already called for this kernel, or forgot to wrap it with cudakernel event");
			return NULL;
		}

		returnPtr = (int *)threadContext_p->currentGPUEventPtr;

		threadContext_p->currentGPUEventPtr += (blocks * ((threads+31)/32) * 32);  // 32 bytes per warp

		if ((threadContext_p->currentGPUEventPtr - threadContext_p->gpuEventMemory) > GPU_INTERNAL_EVENTS_SIZE)
			return NULL;

		threadContext_p->submittedEvents[wrappedEventCnt-1].startOffset = (AgU32)((AgU8 *)returnPtr - threadContext_p->gpuEventMemory);
		threadContext_p->submittedEvents[wrappedEventCnt-1].endOffset	= (AgU32)(threadContext_p->currentGPUEventPtr - threadContext_p->gpuEventMemory);

		threadContext_p->submittedGPUKernelEvents++;

		// check if we are passed the end of the buffer, place a warning
	}
#endif

	return(returnPtr);
}

#define SUBMIT_WARP_PERF_EVENTS 1

void AgGPUPerfUtils::processKernelInternalEvents(gpuPerfThreadInfo_st *threadContext_p, AgU32 startOffset, AgU32 endOffset, AgU32 startEventTime)
{
	kernelEvent_st *gpuInternalKernelEvent;
	kernelEvent_st *endPtr;
	unsigned long eventTime1, eventTime2;
	unsigned long maxEndTime = 0;
	unsigned long hotClocks;
	unsigned long threadId;

	for (unsigned int i = 0; i < mNumSMs*4; i++)
	{
		mGpuSMData[i].gpuSMTimer		= 0xffffffff;
		mGpuSMData[i].savedEnd			= 0xffffffff;
		mGpuSMData[i].deadtime			= 0;
		mGpuSMData[i].instructionCount	= 0;
	}

	gpuInternalKernelEvent = (kernelEvent_st*)((AgU8*)threadContext_p->hostCopiedGPUEventMemory + startOffset);

	endPtr = (kernelEvent_st *)((AgU8*)threadContext_p->hostCopiedGPUEventMemory + endOffset);
	
	// test for valid data
	if (gpuInternalKernelEvent->mpId > (mNumSMs*4))
	{
		assert(!"Garbage returned from SM perfmon macro");
		return;
	}

	while (gpuInternalKernelEvent < endPtr)
	{
		int smID = gpuInternalKernelEvent->mpId;

		if (gpuInternalKernelEvent->startTime < mGpuSMData[smID].gpuSMTimer)
			mGpuSMData[smID].gpuSMTimer = gpuInternalKernelEvent->startTime;

#if UTILIZATION_CALCULATION
		// if one warp is running on a gpu, we are going to call it utilized
		// assumes blocks and threads are issued sequentially in order on a SM
		if (mGpuSMData[smID].savedEnd == 0xffffffff)
		{
			mGpuSMData[smID].savedEnd = gpuInternalKernelEvent->endTime;
			mGpuSMData[smID].instructionCount = gpuInternalKernelEvent->userData[0];
		}
		
		if (gpuInternalKernelEvent->startTime < mGpuSMData[smID].savedEnd)
		{
			if (gpuInternalKernelEvent->endTime > mGpuSMData[smID].savedEnd)
			{
				mGpuSMData[smID].savedEnd = gpuInternalKernelEvent->endTime;
				mGpuSMData[smID].instructionCount = gpuInternalKernelEvent->userData[0];
			}
		}
		else
		{
			mGpuSMData[smID].deadtime += (gpuInternalKernelEvent->startTime - mGpuSMData[smID].savedEnd);
			mGpuSMData[smID].savedEnd = gpuInternalKernelEvent->endTime;
			mGpuSMData[smID].instructionCount = gpuInternalKernelEvent->userData[0];
		}

#endif

		gpuInternalKernelEvent++;
	}

	gpuInternalKernelEvent = (kernelEvent_st*)((AgU8*)threadContext_p->hostCopiedGPUEventMemory + startOffset);

	threadId = GetCurrentThreadId();

	while (gpuInternalKernelEvent < endPtr)
	{
		// must deal with wrapping on the sm clock
		int smID	= gpuInternalKernelEvent->mpId;
		
		eventTime1 = (AgU32)((AgU64)(gpuInternalKernelEvent->startTime - mGpuSMData[smID].gpuSMTimer) * (AgU64)100000 / mClockFreq);

		
		eventTime1 += startEventTime;
#if SUBMIT_WARP_PERF_EVENTS
		AgPmSubmitEvent(mhAgPm, mPerfmonEventIds[gpuInternalKernelEvent->eventId],
						threadId,
						(gpuInternalKernelEvent->block << 16) | (gpuInternalKernelEvent->hwWarpId << 8) | smID,
						AG_PERFMON_EV_STAT);
#endif
#if KERNEL_USER_DATA
		
		if ((gpuInternalKernelEvent->userDataCfg & 0x3) == KERNEL_TSTAMP_TYPE)
		{
			gpuInternalKernelEvent->userData[0] = (AgU32)((AgU64)(gpuInternalKernelEvent->userData[0] - mGpuSMData[smID].gpuSMTimer) * (AgU64)100000 / mClockFreq);	
			gpuInternalKernelEvent->userData[0] += startEventTime;
		}
		if (((gpuInternalKernelEvent->userDataCfg >> 2) & 0x3) == KERNEL_TSTAMP_TYPE)
		{
			gpuInternalKernelEvent->userData[1] = (AgU32)((AgU64)(gpuInternalKernelEvent->userData[1] - mGpuSMData[smID].gpuSMTimer) * (AgU64)100000 / mClockFreq);	
			gpuInternalKernelEvent->userData[1] += startEventTime;
		}
		if (((gpuInternalKernelEvent->userDataCfg >> 4) & 0x3) == KERNEL_TSTAMP_TYPE)
		{
			gpuInternalKernelEvent->userData[2] = (AgU32)((AgU64)(gpuInternalKernelEvent->userData[2] - mGpuSMData[smID].gpuSMTimer) * (AgU64)100000 / mClockFreq);	
			gpuInternalKernelEvent->userData[2] += startEventTime;
		}
		if (((gpuInternalKernelEvent->userDataCfg >> 6) & 0x3) == KERNEL_TSTAMP_TYPE)
		{
			gpuInternalKernelEvent->userData[3] = (AgU32)((AgU64)(gpuInternalKernelEvent->userData[3] - mGpuSMData[smID].gpuSMTimer) * (AgU64)100000 / mClockFreq);	
			gpuInternalKernelEvent->userData[3] += startEventTime;
		}
#if SUBMIT_WARP_PERF_EVENTS
		AgPmSubmitEvent(mhAgPm, mSmCnt0,
						(gpuInternalKernelEvent->userDataCfg & 0x3),
						gpuInternalKernelEvent->userData[0],
						AG_PERFMON_EV_STAT);

		AgPmSubmitEvent(mhAgPm, mSmCnt1,
						((gpuInternalKernelEvent->userDataCfg >> 2) & 0x3),
						gpuInternalKernelEvent->userData[1],
						AG_PERFMON_EV_STAT);

		AgPmSubmitEvent(mhAgPm, mSmCnt2,
						((gpuInternalKernelEvent->userDataCfg >> 4) & 0x3),
						gpuInternalKernelEvent->userData[2],
						AG_PERFMON_EV_STAT);

		AgPmSubmitEvent(mhAgPm, mSmCnt3,
						((gpuInternalKernelEvent->userDataCfg >> 6) & 0x3),
						gpuInternalKernelEvent->userData[3],
						AG_PERFMON_EV_STAT);
#endif
#endif
#if SUBMIT_WARP_PERF_EVENTS
		AgPmSubmitEvent(mhAgPm, mPerfmonEventIds[gpuInternalKernelEvent->eventId], threadId, eventTime1,  AG_PERFMON_EV_START);
#endif
		hotClocks	= gpuInternalKernelEvent->endTime - mGpuSMData[smID].gpuSMTimer;

		eventTime2	= (AgU32)((AgU64)(hotClocks) * (AgU64)100000 / mClockFreq);

#if UTILIZATION_CALCULATION
		if (hotClocks > maxEndTime)
		{
			maxEndTime = hotClocks;
		}
#endif
		
		eventTime2 += startEventTime;
#if SUBMIT_WARP_PERF_EVENTS		
		AgPmSubmitEvent(mhAgPm, mPerfmonEventIds[gpuInternalKernelEvent->eventId], GetCurrentThreadId(), eventTime2,  AG_PERFMON_EV_STOP);
		// submit a stat with info, the gui can tie this back.
#endif
		gpuInternalKernelEvent++;
	}

#if UTILIZATION_CALCULATION
	unsigned long deadTime=0;
	unsigned long submittedEvents=0;
	float smUtilization;
	float totalUtil = 0;
	AgU32 solInstructions;
	float instructionUtilization = 0;
	solInstructions = maxEndTime >> 2;  // divided by four - four clocks for one instruction

	for (unsigned int i = 0; i < mNumSMs*4; i++)
	{	
		if (mGpuSMData[i].savedEnd != 0xffffffff)
		{
			deadTime = (maxEndTime - (mGpuSMData[i].savedEnd - mGpuSMData[i].gpuSMTimer)) + mGpuSMData[i].deadtime;
			smUtilization = ((maxEndTime - deadTime) / (float)maxEndTime) * 100;

			totalUtil += smUtilization;
			

			// instruction utilization
			instructionUtilization += ((float)mGpuSMData[i].instructionCount / (float)solInstructions) * 100;
			
		}
	}
	totalUtil = totalUtil/mNumSMs;
#if SUBMIT_WARP_PERF_EVENTS
	AgPmSubmitEvent(mhAgPm, mPerfmonUtilization,
					threadId,
					(AgU32)(totalUtil),
					AG_PERFMON_EV_STAT);
#endif

	// instruction utilization
	AgPmSubmitEvent(mhAgPm, mPerfmonInstructionUtilization,
							threadId,
							(AgU32)(instructionUtilization / mNumSMs),
							AG_PERFMON_EV_STAT);
#endif
}

static void ResolveCounterFunctions()
{
#ifdef GPU_PERFORMANCE_COUNTERS2
	HMODULE hMod = LoadLibrary("nvcuda.dll");
            
    if(hMod)
	{
        cuGetNumCounters = (cuGetNumCountersFnPtr) GetProcAddress(hMod, "cuGetNumCounters");
        cuGetCounterName = (cuGetCounterNameFnPtr) GetProcAddress(hMod, "cuGetCounterName");
        cuGetEventInfo = (cuGetEventInfoFnPtr) GetProcAddress(hMod, "cuGetEventInfo");
        cuFlushEvents = (cuFlushEventsFnPtr) GetProcAddress(hMod, "cuFlushEvents");
        cuGetNumEvents = (cuGetNumEventsFnPtr) GetProcAddress(hMod, "cuGetNumEvents");
        cuGetCounterValue = (cuGetCounterValueFnPtr) GetProcAddress(hMod, "cuGetCounterValue");
    }
#endif
}

static void pmonEventCreate(pmonCudaEvent *cudaEventId)
{
#if AGPERFMON_USES_CUDART
	cudaEventCreate(cudaEventId);
#else
	cuEventCreate(cudaEventId, 0);
#endif
}
static void pmonEventRecord(pmonCudaEvent cudaEventId)
{
#if AGPERFMON_USES_CUDART
	cudaEventRecord(cudaEventId, 0);
#else
	cuEventRecord(cudaEventId, 0);
#endif
}
static AgU8 pmonEventQuery(pmonCudaEvent cudaEventId)
{
	AgU8 status = PMON_SUCCESS;

#if AGPERFMON_USES_CUDART
	if (cudaEventQuery(cudaEventId) != cudaSuccess)
		status = PMON_FAIL;
#else
	if (cuEventQuery(cudaEventId) != CUDA_SUCCESS)
		status = PMON_FAIL;
#endif
	return(status);

}
static void pmonEventElapsedTime(float *elapsedTime, pmonCudaEvent refEvent, pmonCudaEvent cudaEventId)
{
#if AGPERFMON_USES_CUDART
	cudaEventElapsedTime(elapsedTime, refEvent, cudaEventId);
#else
	cuEventElapsedTime(elapsedTime, refEvent, cudaEventId);
#endif
}

static void pmonEventSynchronize(pmonCudaEvent cudaEvent)
{
#if AGPERFMON_USES_CUDART
	cudaEventSynchronize(cudaEvent);
#else
	cuEventSynchronize(cudaEvent);
#endif
}

static void pmonContextSynchronize()
{
#if AGPERFMON_USES_CUDART
	cudaThreadSynchronize();
#else
	cuCtxSynchronize();
#endif
}

static void pmonMemcpyDtoH(int *hostMemory, AgU8 *gpuMemory, unsigned int length)
{
#if AGPERFMON_USES_CUDART
			cudaMemcpy(hostMemory, (void *)gpuMemory, length, cudaMemcpyDeviceToHost);
#else
			
			cuMemcpyDtoH(hostMemory, (CUdeviceptr)gpuMemory, length);
#endif
}

static void pmonDeviceMalloc(AgU8 **gpuEventMemory, unsigned int length)
{
#if AGPERFMON_USES_CUDART

	cudaError_t err = cudaMalloc((void **)gpuEventMemory, length);
	if( cudaSuccess != err)
	{
		fprintf(stderr, "Cuda error: cudaMalloc in file '%s' in line %i : %s.\n",
				__FILE__, __LINE__, cudaGetErrorString( err) );
#else
	CUresult memReturnVal;
	CUdeviceptr gpuMemory;
	memReturnVal = cuMemAlloc(&gpuMemory, length);
	*gpuEventMemory = (AgU8 *)gpuMemory;
	if (memReturnVal != CUDA_SUCCESS)
	{
#endif
		exit(1);
	}
}

static void pmonHostMalloc(int **hostMemory, unsigned int length)
{
#if AGPERFMON_USES_CUDART
	cudaError_t err = cudaMallocHost((void**)hostMemory, length);
	if( cudaSuccess != err)
	{
		fprintf(stderr, "Cuda error: cudaMallocHost in file '%s' in line %i : %s.\n",
				__FILE__, __LINE__, cudaGetErrorString( err) );
#else
	if (cuMemAllocHost((void**)hostMemory, length) != CUDA_SUCCESS)
	{
#endif
		exit(1);
	}
}
