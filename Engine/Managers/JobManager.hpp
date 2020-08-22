/*
    This implementations is based on:
    https://wickedengine.net/2018/11/24/simple-job-system-using-standard-c/
*/

#ifndef JOB_MANAGER_H
#define JOB_MANAGER_H

#include <functional>

struct JobDispatchArgs
{
	uint32_t jobIndex;
	uint32_t groupIndex;
};

class JobManager {
    friend class Engine; 

    private:
    static JobManager* gInstance;

    JobManager();
    ~JobManager();
    static void StartUp();
    static void ShutDown();

    public:

    static JobManager& GetSingleton(void);
    static JobManager* GetSingletonPtr(void);

	void Execute(const std::function<void()>& job);
	void Dispatch(unsigned int jobCount, unsigned int groupSize, const std::function<void(JobDispatchArgs)>& job);
	bool IsBusy();
	void Wait();
};

#endif