#include "StompProfiler.h"

omp::prof::StompProfiler& omp::prof::StompProfiler::GetProfiler()
{
    static StompProfiler prof{};
    return prof;
}

omp::prof::StompProfiler::ThreadProfPtr omp::prof::StompProfiler::GetThreadProfiler(std::thread::id ThreadId) const
{
    int8_t index = GetIndexFromThreadId(ThreadId);
    return ThreadsData.at(index);
}

int8_t omp::prof::StompProfiler::GetIndexFromThreadId(std::thread::id ThreadId) const
{
    return 0;
}

void omp::prof::StompProfiler::CreateThreadProfilerAt(int8_t index)
{
    auto profiler = std::make_shared<ThreadProfiler>();
    ThreadsData[index] = profiler;
}
