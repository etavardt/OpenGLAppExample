#pragma once

#include <iostream>
#include <ostream>
#include "String.hpp"

// Severity level enum.
enum LogLevel {
    FATAL = 0,
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    DEBUG = 4,
    TRACE = 5
};

//String loggerLevel[] = {
//        "Fatal",
//        "Error",
//        "Warning",
//        "Info",
//        "Debug",
//        "Trace"
//};

class Logger {
private:
    std::ostream& m_Log = std::cout;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    Logger() {};

    std::ostream& operator <<(const auto& data) {
#if defined KEWLF_DEBUG
        m_Log << data;
#endif
        return m_Log;
    }

    static Logger& getInstance() { static Logger log; return log; };

};

#define LOG(x) Logger::getInstance() << #x  << ": " << __FILE__ << "(" <<  __LINE__ << "): " 