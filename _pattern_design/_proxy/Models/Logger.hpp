#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <iostream>

#define LOG_INFO(M, N) \
    std::cout << "[\033[1;31m" << M->getName() << "\033[0m][\033[1;32m" << __FUNCTION__ << "\033[0m][" << __LINE__ << "]: " << N << std::endl; \

class LoggerService {
    public:
        /// @brief 
        /// @param name 
        /// @return 
        static LoggerService* getInstance(const std::string& name) {
            static LoggerService ins(name);
            return &ins;
        }

        std::string getName() const { return m_app; }

    private:
        LoggerService(const std::string& name)
        : m_app(name) {}
        std::string m_app;
};

#endif