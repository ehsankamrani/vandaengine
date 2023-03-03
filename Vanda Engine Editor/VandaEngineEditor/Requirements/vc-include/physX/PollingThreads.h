#ifndef __POLLING_THREADS__
#define __POLLING_THREADS__

class PollingThreads
	{
	public:

		PollingThreads()
			{
			threadCount = 0;
			threadArray = NULL;
			quitEvent = NULL;
			simRunningEvent = NULL;
			workingCounter = -1;
			workingMutexEvent = NULL;
			scene=NULL;
			}

		~PollingThreads()
			{
			KillThreads();
			}

		void CreateThreads(int count,NxScene *newScene);
		void KillThreads();

		void ResetPollForWork();

	private:
		static DWORD __stdcall threadFuncStatic(LPVOID userParam);
		DWORD threadFunc();

		int threadCount;
		HANDLE *threadArray;

		HANDLE quitEvent;
		HANDLE simRunningEvent;

		LONG workingCounter;
		CRITICAL_SECTION shieldCS;
		HANDLE workingMutexEvent;

		NxScene *scene;

	};

#endif
