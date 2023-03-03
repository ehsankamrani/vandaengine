#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#include <windows.h>
#include <stdio.h>
#include "AgPerfMonEventSrcAPI.h"

static HMODULE AgPmDllHandle=0;

static AgPmCreateSourceConnection_FUNC  *createFunc;
static AgPmDestroySourceConnection_FUNC *destroyFunc;
static AgPmRegisterEvent_FUNC           *registerEventFunc;
static AgPmSubmitEvent_FUNC             *submitEventFunc;
static AgPmEventEnabled_FUNC            *eventEnabledFunc;
static AgPmEventLoggingEnabled_FUNC     *eventLoggingEnabledFunc;


/** macros */
#define AgPmLibLoaded() (0 != AgPmDllHandle)


AgPmHANDLE AgPmCreateSourceConnection()
{
    /** load the DLL */
    AgPmDllHandle = LoadLibrary(AG_PERFMON_LIB_NAME);

    if(!AgPmDllHandle)
    {
        /* printf("Could not load AgPerfMon Library\n"); */
        return 0;
    }

    /** get the function pointers to the event src api */
    createFunc              = (AgPmCreateSourceConnection_FUNC*)GetProcAddress(AgPmDllHandle, "AgPmCreateSourceConnection");
    destroyFunc             = (AgPmDestroySourceConnection_FUNC*)GetProcAddress(AgPmDllHandle, "AgPmDestroySourceConnection");
    registerEventFunc       = (AgPmRegisterEvent_FUNC*)GetProcAddress(AgPmDllHandle, "AgPmRegisterEvent");
    submitEventFunc         = (AgPmSubmitEvent_FUNC*)GetProcAddress(AgPmDllHandle, "AgPmSubmitEvent");
    eventEnabledFunc        = (AgPmEventEnabled_FUNC*)GetProcAddress(AgPmDllHandle, "AgPmEventEnabled");
    eventLoggingEnabledFunc = (AgPmEventLoggingEnabled_FUNC*)GetProcAddress(AgPmDllHandle, "AgPmEventLoggingEnabled");

    if(!createFunc          ||
       !destroyFunc         ||
       !registerEventFunc   ||
       !submitEventFunc     ||
       !eventEnabledFunc    ||
       !eventLoggingEnabledFunc)
    {
#ifdef UNICODE
        MessageBox(NULL, L"The AGEIA PerfMON DLL does not contain all required entrypoints, PerfMON is disabled.  Install the latest AgPerfMon.dll.", L"AGEIA PerfMON ERROR", MB_OK|MB_ICONSTOP);
#else
        MessageBox(NULL, "The AGEIA PerfMON DLL does not contain all required entrypoints, PerfMON is disabled.  Install the latest AgPerfMon.dll.", "AGEIA PerfMON ERROR", MB_OK|MB_ICONSTOP);
#endif
        FreeLibrary(AgPmDllHandle);
        AgPmDllHandle = 0;
        return 0;
    }

    return createFunc(AG_PERFMON_VERSION);
}

bool AgPmDestroySourceConnection(AgPmHANDLE hconn)
{
    if(!AgPmLibLoaded())
        return false;

    bool retVal = destroyFunc(hconn);
    FreeLibrary(AgPmDllHandle);
    AgPmDllHandle = 0;
    
    return retVal;
}

AgEventID AgPmRegisterEvent(AgPmHANDLE hconn, const char *name)
{
    if(!AgPmLibLoaded())
        return AG_INVALID_EVENT_ID;

    return registerEventFunc(hconn, name);
}

bool AgPmSubmitEvent(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2)
{
    if(!AgPmLibLoaded())
        return false;

    return submitEventFunc(hconn, id, data0, data1, data2);
}

bool AgPmEventEnabled(AgPmHANDLE hconn, AgEventID id)
{
    if(!AgPmLibLoaded())
        return false;

    return eventEnabledFunc(hconn, id);
}

bool AgPmEventLoggingEnabled(AgPmHANDLE hconn)
{
    if(!AgPmLibLoaded())
        return false;

    return eventLoggingEnabledFunc(hconn);
}

//** AgPerfUtils */


#define DEFINE_EVENT(name) #name,
const char *AgPerfUtils::mEventNames[] = {
#include "AgPerfMonEventDefs.h"
	""
};
#undef DEFINE_EVENT


AgPmHANDLE	AgPerfUtils::mhAgPm = 0;

AgPerfUtils::AgPerfUtils():
   mNtQueryThreadInfo(0),
#ifdef UNICODE
   mhNTDLL(LoadLibrary(L"NTDLL.DLL"))
#else
   mhNTDLL(LoadLibrary("NTDLL.DLL"))
#endif
{
    if(mhNTDLL)
        mNtQueryThreadInfo = (tinfo_FUNC *)GetProcAddress((HMODULE)mhNTDLL, "NtQueryInformationThread");

	if (!mhAgPm)
	{
		mhAgPm = AgPmCreateSourceConnection();
		
		if (mhAgPm)
		{
			for (int i = 0; i < AgPerfEventNumEvents; i++)
				mEventIds[i] = AgPmRegisterEvent(mhAgPm, mEventNames[i]);
		}
	}
}

AgPerfUtils::~AgPerfUtils()
{
    if(mhNTDLL)
        FreeLibrary((HMODULE)mhNTDLL);

	if (mhAgPm)
	{
		AgPmDestroySourceConnection(mhAgPm);
		mhAgPm = 0;
	}
}

AgU32 AgPerfUtils::GetThreadPriority()
{
    AgU32 retVal = 0;
    
    if(mNtQueryThreadInfo)
    {
        /** call into the Native API to get the dynamic thread priority */
        AgU32 len;
        THREAD_BASIC_INFORMATION tbi;
        AgU32 status = mNtQueryThreadInfo(GetCurrentThread(), 0, &tbi, sizeof(tbi), &len); //740ns
        if(!status)
            retVal = tbi.Priority;
    }
    
    return retVal;
}

#include <intrin.h>
unsigned char AgPerfUtils::GetProcID()
{
   int CPUInfo[4];
   int InfoType = 1;
	__cpuid(CPUInfo, InfoType);

    return CPUInfo[1] >> 24; // APIC Physical ID
}

AgEventID AgPerfUtils::registerEvent(const char *name)
{
	return AgPmRegisterEvent(mhAgPm, name);
}

bool AgPerfUtils::isEnabled()
{
	return AgPmEventLoggingEnabled(mhAgPm);
}

void AgPerfUtils::startEvent(AgEventID id, AgU16 data)
{
	if (AgPmEventLoggingEnabled(mhAgPm))
	{
		AgU32 threadCpuData = 0;
		((AgU8*)(&threadCpuData))[0] = GetThreadPriority();
		((AgU8*)(&threadCpuData))[1] = GetProcID();
		((AgU16*)(&threadCpuData))[1] = data;
		AgPmSubmitEvent(mhAgPm, id, GetCurrentThreadId(), threadCpuData, AG_PERFMON_EV_START);
	}
}

void AgPerfUtils::stopEvent(AgEventID id, AgU16 data)
{
	if (AgPmEventLoggingEnabled(mhAgPm))
	{
		AgU32 threadCpuData = 0;
		((AgU8*)(&threadCpuData))[0] = GetThreadPriority();
		((AgU8*)(&threadCpuData))[1] = GetProcID();
		((AgU16*)(&threadCpuData))[1] = data;
		AgPmSubmitEvent(mhAgPm, id, GetCurrentThreadId(), threadCpuData, AG_PERFMON_EV_STOP);
	}
}

void AgPerfUtils::statEvent(AgEventID id, AgU32 stat)
{
	AgPmSubmitEvent(mhAgPm, id, stat, GetCurrentThreadId(), AG_PERFMON_EV_STAT);
}

void AgPerfUtils::statEvent(AgEventID id, AgU32 stat, AgU32 ident)
{
	AgPmSubmitEvent(mhAgPm, id, stat, ident, AG_PERFMON_EV_STAT);
}

void AgPerfUtils::debugEvent(AgEventID id, AgU32 data0, AgU32 data1)
{
	AgPmSubmitEvent(mhAgPm, id, data0, data1, AG_PERFMON_EV_DEBUG);
}

bool AgPerfUtils::isEventEnabled(AgEventID id)
{
	return AgPmEventEnabled(mhAgPm, id);
}

bool AgPerfUtils::isLibraryLoaded()
{
	if(!AgPmLibLoaded())
        return false;
	else
		return true;
}
