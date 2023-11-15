#include "Timer.h"

void Timer::start()
{
    m_startTimer = std::chrono::steady_clock::now();
    m_isRunning = true;
}

void Timer::stop()
{
    m_endTimer = std::chrono::steady_clock::now();
    m_isRunning = false;
}

double Timer::elapsedMilliseconds()
{
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    if (m_isRunning)
    {
        endTime = std::chrono::steady_clock::now();
    }
    else
    {
        endTime = m_endTimer;
    }

    return std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTimer).count();
}

double Timer::elapsedSecond()
{
    return elapsedMilliseconds() / 1000.0;
}