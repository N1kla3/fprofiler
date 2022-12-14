#include <chrono>
#include <iostream>
#include "StompProfiler.h"
#include <thread>
#include "Core.h"

using namespace std::chrono;

omp::prof::ScopeTime::~ScopeTime()
{
    SetupTime();
}

omp::prof::ScopeTime::ScopeTime(const std::string &name)
    : m_Name(name)
{
    m_Start = high_resolution_clock::now();
}

void omp::prof::ScopeTime::SetupTime()
{
    std::cout << m_Name << std::endl;
    const auto end = high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(end - m_Start).count();
    std::cout << time << std::endl;
    float time_milli = std::chrono::duration<float, std::chrono::milliseconds ::period>(end - m_Start).count();
    std::cout << time_milli << std::endl;

    auto ThreadId = std::this_thread::get_id();
    std::shared_ptr<omp::prof::ThreadProfiler> profiler = omp::prof::StompProfiler::GetProfiler().GetThreadProfiler(ThreadId);
    profiler->addData(*this);

    std::cout << m_Name << " ended " << std::endl;
}

omp::prof::ProfilerData omp::prof::ScopeTime::GetProfilerData() const
{
    const TimePoint Start = omp::prof::StompProfiler::GetProfiler().GetStartTime();
    omp::prof::ProfilerData data{};
    data.Name = m_Name;
    data.BeginTime = std::chrono::duration<float, std::chrono::seconds::period>(Start - m_Start).count();
    data.EndTime = std::chrono::duration<float, std::chrono::seconds::period>(Start - m_Start).count();
    return data;
}
