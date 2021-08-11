#ifndef SAMPLE_MUTEX_WIN_H
#define SAMPLE_MUTEX_WIN_H

#include <windows.h>

class SampleMutex {
private:
	CRITICAL_SECTION mLock;
public:

	SampleMutex()
	{
		InitializeCriticalSection(&mLock);
	}	

	~SampleMutex()
	{
		DeleteCriticalSection(&mLock);
	}

	void lock()
	{
		EnterCriticalSection(&mLock);
	}

	void unlock()
	{
		LeaveCriticalSection(&mLock);
	}
};


#endif  // SAMPLE_MUTEX_WIN_H