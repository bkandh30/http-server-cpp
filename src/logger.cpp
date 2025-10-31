#include "logger.hpp"

void Logger::log(LogLevel level, const std::string& msg) {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::string levelStr;

    switch (level) {
        case LogLevel::INFO:  levelStr = "\033[32m[INFO]\033[0m "; break;
        case LogLevel::WARN:  levelStr = "\033[33m[WARN]\033[0m "; break;
        case LogLevel::ERROR: levelStr = "\033[31m[ERROR]\033[0m "; break;
    }

    std::cout << levelStr << std::ctime(&time) << " - " << msg << std::endl;
};
