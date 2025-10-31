#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

enum class LogLevel { INFO, WARN, ERROR };

class Logger {
    public:
        static void log(LogLevel level, const std::string& msg);
        static void info(const std::string& msg) { log(LogLevel::INFO, msg); }
        static void warn(const std::string& msg) { log(LogLevel::WARN, msg); }
        static void error(const std::string& msg) { log(LogLevel::ERROR, msg); }
};