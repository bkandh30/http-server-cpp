#pragma once
#include <string>
#include <unordered_map>
#include <mutex>
#include <list>

class FileCache {
    public:
        explicit FileCache(size_t capacity = 10);

        bool get(const std::string& path, std::string& content);

        void put(const std::string& path, const std::string& content);

    private:
        size_t capacity_;
        std::list<std::string> order_;
        std::unordered_map<std::string, std::pair<std::string, std::list<std::string>::iterator>> cache_;
        std::mutex mutex_;
};