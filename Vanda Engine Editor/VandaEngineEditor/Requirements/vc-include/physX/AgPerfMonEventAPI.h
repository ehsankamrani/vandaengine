/*----------------------------------------------------------------------
    This Software and Related Documentation are Proprietary to NVIDIA
    Corporation

    Copyright 2010 NVIDIA Corporation
    Unpublished -
    All Rights Reserved Under the Copyright Laws of the United States.

    Restricted Rights Legend:  Use, Duplication, or Disclosure by
    the Government is Subject to Restrictions as Set Forth in
    Paragraph (c)(1)(ii) of the Rights in Technical Data and
    Computer Software Clause at DFARS 252.227-7013.  NVIDIA
    Corporation
-----------------------------------------------------------------------*/


#ifndef __AG_PERFMON_EVENT_API___
#define __AG_PERFMON_EVENT_API___

#include "AgTypes.h"

/** version info */
#define AG_PERFMON_VERSION                  0x06121900

/** Required for Event Sink/Src */
#ifdef UNICODE
#   define AG_PERFMON_LIB_NAME                 L"AgPerfMon.dll"
#else
#   define AG_PERFMON_LIB_NAME                 "AgPerfMon.dll"
#endif

#define AG_PERFMON_API_INIT_EVENT_NAME      "AgPerfMonApiInitEvent"
#define AG_EVENT_NAME_LEN                   129
#define AG_INVALID_EVENT_ID                 ((AgU16)0xffff)
#define AG_INVALID_PCM_ID                   ((AgU8)0xff)

typedef AgU16 AgEventID;
typedef AgU32 AgPCMID;
typedef void* AgPmHANDLE;

typedef enum AgPcmEventGroup
{
	_agMipsEvent,
	_agVcuEvent,
	_agVpuEvent,
} AgPcmEventGroup;


typedef union AgPerfMonEvent
{
    struct 
    {
        AgU16 eventID;
        AgU8  destMask;
        AgU8  vpeID;
        AgU32 timeStamp;
        AgU8  taskListID;
        AgU8  pcmID;
        AgU8  taskSeq;
        AgU8  vpuID;
        AgU32 vpeTime;
    };
    struct
    {
        AgU64 data[2];
    };
} AgPerfMonRemoteEvent;

typedef enum AgPerfMonAppType
{
    _agEventSrc,
    _agEventSink,
    _agEventCollector,
} AgPerfMonAppType;

#if defined(WIN32)
#define AG_PERFMON_DLL_API      extern "C" __declspec(dllexport)
#else
#define AG_PERFMON_DLL_API
#endif

typedef bool (*AgPassiveEventCallback)(void *context, AgEventID id);

/** Event Source API */
AG_PERFMON_DLL_API AgPmHANDLE   AgPmCreateSourceConnection(AgU32 version);
AG_PERFMON_DLL_API bool         AgPmDestroySourceConnection(AgPmHANDLE hconn);
AG_PERFMON_DLL_API AgEventID    AgPmRegisterEvent(AgPmHANDLE hconn, char *name);
AG_PERFMON_DLL_API bool         AgPmSubmitEvent(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2);
AG_PERFMON_DLL_API bool         AgPmRegisterEventAsPassive(AgPmHANDLE hconn, AgEventID id, void *context, AgPassiveEventCallback funcPtr);
AG_PERFMON_DLL_API bool         AgPmEventEnabled(AgPmHANDLE hconn, AgEventID id);
AG_PERFMON_DLL_API bool         AgPmEventLoggingEnabled(AgPmHANDLE hconn);

/** Event Sink API */
AG_PERFMON_DLL_API AgPmHANDLE       AgPmCreateSinkConnection(AgU32 version);
AG_PERFMON_DLL_API bool             AgPmDestroySinkConnection(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool				AgPmStartLogging(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool				AgPmStopLogging(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool             AgPmEventAvailable(AgPmHANDLE hconn);
AG_PERFMON_DLL_API AgPerfMonEvent*  AgPmGetCurrentEventPtr(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool				AgPmPopEventPtr(AgPmHANDLE hconn);
AG_PERFMON_DLL_API AgEventID		AgPmGetEventID(AgPmHANDLE hconn, char *name);
AG_PERFMON_DLL_API char*			AgPmGetEventName(AgPmHANDLE hconn, AgEventID id);

/** Event Filtering API */
AG_PERFMON_DLL_API bool				AgPmEnableEvent(AgPmHANDLE hconn, AgEventID id);			
AG_PERFMON_DLL_API bool				AgPmDisableEvent(AgPmHANDLE hconn, AgEventID id);
AG_PERFMON_DLL_API bool				AgPmEnableAllEvents(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool				AgPmDisableAllEvents(AgPmHANDLE hconn, AgEventID id);
AG_PERFMON_DLL_API bool				AgPmEnablePcmEvents(AgPmHANDLE hconn, AgPCMID pcmID, AgPcmEventGroup procID);
AG_PERFMON_DLL_API bool				AgPmDisablePcmEvents(AgPmHANDLE hconn, AgPCMID pcmID, AgPcmEventGroup procID);

/** Event Chaining API */
AG_PERFMON_DLL_API bool				AgPmChainEvent(AgPmHANDLE hconn, AgEventID leadID, AgEventID followerID);
AG_PERFMON_DLL_API bool				AgPmRemoveEventChain(AgPmHANDLE hconn, AgEventID leadID);



#endif /* __AG_PERFMON_EVENT_API___ */
