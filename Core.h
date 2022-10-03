#pragma once
#include <chrono>
#include "StompProfiler.h"

#define PROFILE_FUNCTION_NAME(CustomName) omp::prof::ScopeTime UnnamedVariableForProfiling{CustomName};
#define PROFILE_FUNCTION() omp::prof::ScopeTime UnnamedVariableForProfiling{};

#define PROFILE_THREAD(name) omp::prof::StompProfiler::GetProfiler().CreateThreadProfiler(name);

namespace omp::prof {
    struct ProfilerData;
class ScopeTime
{
private:

#if (_MSC_VER > 1200)
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
#else
    using TimePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
#endif

    TimePoint m_Start;
public:
    ScopeTime();
    explicit ScopeTime(const std::string& name);
    ~ScopeTime();

    ProfilerData GetProfilerData() const;

private:
    // Subroutines //
    void SetupTime();
};
}
