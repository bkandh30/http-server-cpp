#include "cache.hpp"

FileCache::FileCache(size_t capacity) : capacity_(capacity) {}

bool FileCache::get(const std::string& path, std::string& content) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = cache_.find(path);
    if (it == cache_.end()) return false;

    order_.erase(it->second.second);
    order_.push_front(path);
    it->second.second = order_.begin();

    content = it->second.first;
    return true;
};

void FileCache::put(const std::string& path, const std::string& content) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = cache_.find(path);
    if (it != cache_.end()) {
        order_.erase(it->second.second);
        cache_.erase(it);
    }

    if (order_.size() >= capacity_) {
        cache_.erase(order_.back());
        order_.pop_back();
    }

    order_.push_front(path);
    cache_[path] = {content, order_.begin()};
};