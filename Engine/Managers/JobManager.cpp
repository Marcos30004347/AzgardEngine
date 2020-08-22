/*
    This implementations is based on:
    https://wickedengine.net/2018/11/24/simple-job-system-using-standard-c/
*/

#include<iostream>
#include<assert.h>

#include <algorithm>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <sstream>

#include "JobManager.hpp"

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

template <typename JobType, size_t capacity>
class JobPool
{
    private:

	JobType data[capacity];

	size_t head = 0;
	size_t tail = 0;

	std::mutex lock;
    
    public:

	inline bool push_back(const JobType& item)
	{
		bool result = false;
		lock.lock();
		size_t next = (head + 1) % capacity;
		if (next != tail)
		{
			data[head] = item;
			head = next;
			result = true;
		}
		lock.unlock();
		return result;
	}

	inline bool pop_front(JobType& item)
	{
		bool result = false;
		lock.lock();
		if (tail != head)
		{
			item = data[tail];
			tail = (tail + 1) % capacity;
			result = true;
		}
		lock.unlock();
		return result;
	}

};





JobManager* JobManager::gInstance = nullptr;

unsigned int numThreads = 0;

JobPool<std::function<void()>, 256> jobPool;

std::condition_variable wakeCondition;

std::mutex wakeMutex;

unsigned long int currentLabel = 0;

std::atomic<unsigned long int> finishedLabel;



JobManager::JobManager() {}
JobManager::~JobManager() {}

JobManager* JobManager::GetSingletonPtr(void) {
    assert(JobManager::gInstance);
    return JobManager::gInstance;
}

JobManager& JobManager::GetSingleton(void) {
    assert(JobManager::gInstance);
    return *JobManager::gInstance;
}

void JobManager::StartUp() {
    std::cout << "starting up job manager" << std::endl;

    JobManager::gInstance = new JobManager();

    finishedLabel.store(0);

    unsigned int numCores = std::thread::hardware_concurrency();

    numThreads = std::max(1u, numCores);
    
    #ifdef BROWSER_PLATFORM
    numThreads = std::max(8u, numCores);
    #endif

    for (unsigned int threadID = 0; threadID < numThreads; ++threadID)
    {
        std::thread worker([] {

            std::function<void()> job;

            while (true)
            {
                if (jobPool.pop_front(job))
                {
                    job();
                    finishedLabel.fetch_add(1);
                }
                else
                {
                    // no job, put thread to sleep
                    std::unique_lock<std::mutex> lock(wakeMutex);
                    wakeCondition.wait(lock);
                }
            }

        });

        #ifdef _WIN32
        // Do Windows-specific thread setup:
        HANDLE handle = (HANDLE)worker.native_handle();

        // Put each thread on to dedicated core
        DWORD_PTR affinityMask = 1ull << threadID;
        DWORD_PTR affinity_result = SetThreadAffinityMask(handle, affinityMask);
        assert(affinity_result > 0);

        //// Increase thread priority:
        //BOOL priority_result = SetThreadPriority(handle, THREAD_PRIORITY_HIGHEST);
        //assert(priority_result != 0);

        // Name the thread:
        std::wstringstream wss;
        wss << "JobSystem_" << threadID;
        HRESULT hr = SetThreadDescription(handle, wss.str().c_str());
        assert(SUCCEEDED(hr));
        #endif // _WIN32

        worker.detach(); // forget about this thread, let it do it's job in the infinite loop that we created above
    }

}

void JobManager::ShutDown() {
    std::cout << "shuting down mesh manager" << std::endl;
    delete JobManager::gInstance;
}


void reschedule_self(){
    wakeCondition.notify_one(); // wake one worker thread
    std::this_thread::yield(); // allow this thread to be rescheduled
}

void JobManager::Execute(const std::function<void()>& job) {
    // The main thread label state is updated:
    currentLabel += 1;

    // Try to push a new job until it is pushed successfully:
    while (!jobPool.push_back(job)) {
        reschedule_self();
    }

    wakeCondition.notify_one(); // wake one thread
}

bool JobManager::IsBusy() {
    // Whenever the main thread label is not reached by the workers, it indicates that some worker is still alive
    return finishedLabel.load() < currentLabel;
}

void JobManager::Wait() {
    while (IsBusy()) {
        reschedule_self();
    }
}


void JobManager::Dispatch(unsigned int jobCount, unsigned int groupSize, const std::function<void(JobDispatchArgs)>& job) {
    if (jobCount == 0 || groupSize == 0) {
        return;
    }

    // Calculate the amount of job groups to dispatch (overestimate, or "ceil"):
    const unsigned int groupCount = (jobCount + groupSize - 1) / groupSize;

    // The main thread label state is updated:
    currentLabel += groupCount;

    for (unsigned int groupIndex = 0; groupIndex < groupCount; ++groupIndex) {
        // For each group, generate one real job:
        const auto& jobGroup = [jobCount, groupSize, job, groupIndex]() {

            // Calculate the current group's offset into the jobs:
            const unsigned int groupJobOffset = groupIndex * groupSize;
            const unsigned int groupJobEnd = std::min(groupJobOffset + groupSize, jobCount);

            JobDispatchArgs args;
            args.groupIndex = groupIndex;

            // Inside the group, loop through all job indices and execute job for each index:
            for (unsigned int i = groupJobOffset; i < groupJobEnd; ++i)
            {
                args.jobIndex = i;
                job(args);
            }
        };

        // Try to push a new job until it is pushed successfully:
        while (!jobPool.push_back(jobGroup)) {
            reschedule_self();
        }

        wakeCondition.notify_one(); // wake one thread
    }
}