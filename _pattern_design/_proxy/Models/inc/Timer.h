#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

class TimerInterface {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual double elapsedMilliseconds() = 0;
        virtual double elapsedSecond() = 0;
    protected:
        std::chrono::time_point<std::chrono::steady_clock> m_startTimer;
        std::chrono::time_point<std::chrono::steady_clock> m_endTimer;
        bool m_isRunning;
};

class Timer : public TimerInterface {
    public:
        virtual void start() override;
        virtual void stop() override;
        virtual double elapsedMilliseconds() override;
        virtual double elapsedSecond();
};

#endif // _TIMER_H_