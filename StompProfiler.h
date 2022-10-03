#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <thread>

namespace omp::prof{

    struct ProfilerData
    {
        std::string Name;

        float BeginTime;
        float EndTime;
    };

    struct ThreadData
    {
        std::string Name;
        int8_t IndexInProfiler;
        bool IsMainThread;
    };

class ThreadProfiler;
class StompProfiler {
    using ThreadProfPtr = std::shared_ptr<ThreadProfiler>;
public:
    static StompProfiler& GetProfiler();

private:
    StompProfiler() = default;
    ~StompProfiler() = default;
public:
    StompProfiler(const StompProfiler&) = delete;
    StompProfiler& operator=(const StompProfiler&) = delete;

    ThreadProfPtr GetThreadProfiler(std::thread::id ThreadId) const;

private:
    std::vector<ThreadProfPtr> ThreadsData;
    std::unordered_map<int16_t, ThreadData> ThreadsInfo;

    // Subroutines //
    int8_t GetIndexFromThreadId(std::thread::id ThreadId) const;
    void CreateThreadProfilerAt(int8_t index);
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
