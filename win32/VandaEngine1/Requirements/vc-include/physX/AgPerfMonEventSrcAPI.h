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


#ifndef __AG_PERFMON_EVENT_SRC_API___
#define __AG_PERFMON_EVENT_SRC_API___

#include "AgPerfMonEventAPI.h"

typedef AgPmHANDLE  (AgPmCreateSourceConnection_FUNC)(AgU32 version);
typedef bool        (AgPmDestroySourceConnection_FUNC)(AgPmHANDLE hconn);
typedef AgEventID   (AgPmRegisterEvent_FUNC)(AgPmHANDLE hconn, const char *name);
typedef bool        (AgPmSubmitEvent_FUNC)(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2);
typedef bool        (AgPmEventEnabled_FUNC)(AgPmHANDLE hconn, AgEventID id);
typedef bool        (AgPmEventLoggingEnabled_FUNC)(AgPmHANDLE hconn);


/** Event Source API */
AgPmHANDLE  AgPmCreateSourceConnection();
bool        AgPmDestroySourceConnection(AgPmHANDLE hconn);   
AgEventID   AgPmRegisterEvent(AgPmHANDLE hconn, const char *name);
bool        AgPmSubmitEvent(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2);
bool        AgPmRegisterEventAsPassive(AgPmHANDLE hconn, AgEventID id, void *context, AgPassiveEventCallback funcPtr);
bool        AgPmEventEnabled(AgPmHANDLE hconn, AgEventID id);
bool        AgPmEventLoggingEnabled(AgPmHANDLE hconn);

#define AG_PERFMON_EV_START				0x00
#define AG_PERFMON_EV_STOP				0x01
#define AG_PERFMON_EV_STAT  			0x02
#define AG_PERFMON_EV_DEBUG  			0x03


#define DEFINE_EVENT(name) name,
enum AgPerfEventEnum
{
#include "AgPerfMonEventDefs.h"
	AgPerfEventNumEvents
};
#undef DEFINE_EVENT


class AgPerfUtils
{
public:

	AgPerfUtils();
    ~AgPerfUtils();

	AgEventID registerEvent(const char *);
	bool isEnabled();
	bool isEventEnabled(AgEventID id);
	bool isLibraryLoaded();
	void startEvent(AgEventID id, AgU16 data = 0);
	void stopEvent(AgEventID id, AgU16 data = 0);
	void statEvent(AgEventID id, AgU32 stat);
	void statEvent(AgEventID id, AgU32 stat, AgU32 ident);
	void debugEvent(AgEventID id, AgU32 data0, AgU32 data1);

	inline AgEventID getEventId(int index) { return mEventIds[index]; };

	AgU32 GetThreadPriority();
    unsigned char GetProcID (void);
	inline AgPmHANDLE getHAgPm() {return mhAgPm; };

private:
    typedef struct _THREAD_BASIC_INFORMATION {
        AgU32               ExitStatus;
        void               *TebBaseAddress;
        AgU32               ClientId;
        AgU32               reserved;
        AgU32               AffinityMask;
        AgU32               Priority;
        AgU32               BasePriority;
    } THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

    typedef AgU32 ( __stdcall tinfo_FUNC)(void *ThreadHandle,
        AgU32 ThreadInformationClass,
        PTHREAD_BASIC_INFORMATION ThreadInformation,
        AgU32 ThreadInformationLength,
        AgU32 *ReturnLength);

    tinfo_FUNC			*mNtQueryThreadInfo;
    void				*mhNTDLL;
	static AgPmHANDLE	mhAgPm;

	AgEventID			mEventIds[AgPerfEventNumEvents+1];
	static const char *	mEventNames[AgPerfEventNumEvents+1];
};


/*
 * Example wrapper class.  You must create an instance of class
 * AgPerfUtils named gPerfUtils in order to use AgPerfScope.
 * To use AgPerfScope, place event names in AgPerfMonEventDefs.h,
 * for example:
 *
 * ================ AgPerfMonEventDefs.h ====================
 * DEFINE_EVENT(exampleEvent0)
 * DEFINE_EVENT(exampleEvent1)
 * ================ AgPerfMonEventDefs.h ====================
 *
 * In your source code, you can now declare scope profile zones:
 *
 * if (doEvent0)
 * {
 *      AgPerfScope scope(exampleEvent0);
 *      // event0 stuff
 * }
 * else
 * {
 *      AgPerfScope scope(exampleEvent1);
 *      // event1 stuff
 * }
 *
 * Note that you can store a 16bit data value in both the start and stop
 * events and both datums will be shown in the viewer and can be later
 * analyzed via the DataExtractor.  The most common usage for these
 * values is to store the amount of work done by that scope.  For
 * instance:
 *
 * AgU16 workDone = 0;
 * AgPerfScope scope(exampleEvent0, loopCount);
 * for (int i = 0 ; i < loopCount ; i++)
 *      workDone += doEvent0Stuff(i);
 * scope.stop(workDone);
 *
 * In the viewer, this event bar will have the description:
 * "exampleEvent0 (loopCount-workDone) 3ms"
 *
 */

extern AgPerfUtils* gPerfUtils;

class AgPerfScope
{
public:
    AgPerfScope(AgPerfEventEnum e, AgU16 data = 0)
    {
		stopped = false;
		if(gPerfUtils)
		{
			mEventID = gPerfUtils->getEventId(e);
			gPerfUtils->startEvent(mEventID, data);
		}
    }
    void stop(AgU16 data = 0)
    {
        if(gPerfUtils)
			gPerfUtils->stopEvent(mEventID, data);
        stopped = true;
    }
    ~AgPerfScope()
    {
        if (gPerfUtils && !stopped)
            gPerfUtils->stopEvent(mEventID);
    }
private:
    AgEventID mEventID;
    bool stopped;
};

#endif /** _AG_PERFMON_EVENT_SRC_API___ */
