#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <iostream>

#define LOG_INFO(M, N) \
    std::cout << "[\033[1;30mINFO\033[0m][\033[1;31m" << M->getName() << "\033[0m][\033[1;32m" << __FUNCTION__ << "\033[0m][" << __LINE__ << "]: " << N << std::endl;

#define LOG_DEBUG(M, N) \
    std::cout << "[\033[1;174mDEBUG\033[0m][\033[1;31m" << M->getName() << "\033[0m][\033[1;32m" << __FUNCTION__ << "\033[0m][" << __LINE__ << "]: " << N << std::endl;

#define LOG_WARN(M, N) \
    std::cout << "[\033[1;62mWARN\033[0m][\033[1;31m" << M->getName() << "\033[0m][\033[1;32m" << __FUNCTION__ << "\033[0m][" << __LINE__ << "]: " << N << std::endl;

#define LOG_ERROR(M, N) \
    std::cout << "[\033[1;9mERROR\033[0m][\033[1;31m" << M->getName() << "\033[0m][\033[1;32m" << __FUNCTION__ << "\033[0m][" << __LINE__ << "]: " << N << std::endl;

class LoggerService
{
    public:
        static LoggerService *getInstance(const std::string &name);
        std::string getName() const;
    private:
        LoggerService(const std::string &name)
            : m_app(name) {}
        std::string m_app;
};
#endif