#include "StompProfiler.h"

omp::prof::StompProfiler& omp::prof::StompProfiler::GetProfiler()
{
    static StompProfiler prof{};
    return prof;
}

omp::prof::StompProfiler::ThreadProfPtr omp::prof::StompProfiler::GetThreadProfiler(std::thread::id ThreadId) const
{
    int8_t index = GetIndexFromThreadId(ThreadId);
    return ThreadsProfilers.at(index);
}

int8_t omp::prof::StompProfiler::GetIndexFromThreadId(std::thread::id ThreadId) const
{
    if (ThreadsInfo.find(ThreadId) != ThreadsInfo.end())
    {
        return ThreadsInfo.at(ThreadId).IndexInProfiler;
    }
    return -1;
}

void omp::prof::StompProfiler::CreateThreadProfiler(const std::string& name)
{
    static int8_t index = 0;
    auto profiler = std::make_shared<ThreadProfiler>();
    auto thread_id = std::this_thread::get_id();
    ThreadData data;
    data.IndexInProfiler = index;
    data.Name = name;

    ThreadsInfo[thread_id] = data;
    ThreadsProfilers.push_back(profiler);
    index++;
}
