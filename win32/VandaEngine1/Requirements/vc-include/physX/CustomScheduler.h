#ifndef __CUSTOM_SCHEDULER__
#define __CUSTOM_SCHEDULER__


class CustomScheduler : public NxUserScheduler
	{
	public:
	
	CustomScheduler();
	~CustomScheduler();

	void CreateThreads(int count);
	void KillThreads();

	virtual void addTask(NxTask *task);
	virtual void addBackgroundTask(NxTask *task);
	virtual void waitTasksComplete();

	private:

	static DWORD __stdcall threadFuncStatic(LPVOID userParam);
	DWORD threadFunc();

	bool executeTask();

	CRITICAL_SECTION taskQueueCS;
	std::deque<NxTask *> taskQueue;

	int threadCount;
	HANDLE *threadHandles;
	HANDLE quitEvent;
	HANDLE pendingEvent;
	
	volatile long workingCount;
	};
#endif
