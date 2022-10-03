#pragma once
#include <chrono>

#define PROFILE_FUNCTION_NAME(CustomName) ScopeTime UnnamedVariableForProfiling{CustomName};
#define PROFILE_FUNCTION() ScopeTime UnnamedVariableForProfiling{};

namespace omp::prof {
    struct ProfilerData;
class ScopeTime
{
private:
    using TimePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;

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
