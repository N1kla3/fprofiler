#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <thread>


#if (_MSC_VER > 1200)
using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
#else
using TimePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
#endif

namespace omp::prof{

    struct ProfilerData
    {
        std::string Name = "noname";

        float BeginTime;
        float EndTime;
    };

    struct ThreadData
    {
        std::string Name = "noname";
        int8_t IndexInProfiler = -1;
        bool IsMainThread = false;
    };

class ThreadProfiler;
class StompProfiler {
    using ThreadProfPtr = std::shared_ptr<ThreadProfiler>;
public:
    static StompProfiler& GetProfiler();
    TimePoint GetStartTime() const { return ProfilerStartTime; }

private:
    TimePoint ProfilerStartTime;
    StompProfiler();
    ~StompProfiler() = default;
public:
    StompProfiler(const StompProfiler&) = delete;
    StompProfiler& operator=(const StompProfiler&) = delete;

    ThreadProfPtr GetThreadProfiler(std::thread::id ThreadId) const;
    void CreateThreadProfiler(const std::string& name);

private:
    std::vector<ThreadProfPtr> ThreadsProfilers;
    std::unordered_map<std::thread::id, ThreadData> ThreadsInfo;

    // Subroutines //
    int8_t GetIndexFromThreadId(std::thread::id ThreadId) const;
};

class ThreadProfiler
{
public:
    ThreadProfiler() = default;
    ~ThreadProfiler() = default;
public:
    ThreadProfiler(const ThreadProfiler&) = delete;
    ThreadProfiler& operator=(const ThreadProfiler&) = delete;

    template<typename src>
    void addData(const src& Source);
private:
    std::stack<ProfilerData> m_Data;
};
}


template<typename src>
void omp::prof::ThreadProfiler::addData(const src& Source)
{
    ProfilerData data = Source.GetProfilerData();
    m_Data.push(data);
}
