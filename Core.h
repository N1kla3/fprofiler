#pragma once
#include <chrono>
#include "StompProfiler.h"

#define PROFILE_FUNCTION_NAME(CustomName) omp::prof::ScopeTime UnnamedVariableForProfiling{CustomName};
#define PROFILE_FUNCTION() omp::prof::ScopeTime UnnamedVariableForProfiling{__FUNCTION__};

#define PROFILE_THREAD(name) omp::prof::StompProfiler::GetProfiler().CreateThreadProfiler(name);

namespace omp::prof {
    struct ProfilerData;
class ScopeTime
{
private:

    TimePoint m_Start;
    std::string m_Name;
public:
    explicit ScopeTime(const std::string& name);
    ~ScopeTime();

    ProfilerData GetProfilerData() const;

private:
    // Subroutines //
    void SetupTime();
};
}
