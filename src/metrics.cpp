#include "metrics.hpp"
#include <sstream>

Metrics& Metrics::Instance() {
    static Metrics instance;
    return instance;
}

void Metrics::record_request(double latency_ms, bool cache_hit) {
    std::lock_guard<std::mutex> lock(mutex_);
    total_requests_++;

    if (cache_hit) {
        cache_hits_++;
    }

    avg_latency_ms_ += (latency_ms - avg_latency_ms_) / total_requests_.load();
}

std::string Metrics::json() const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::ostringstream ss;
    ss << "{"
        << "\"total_requests\": " << total_requests_.load() << ","
        << "\"cache_hits\": " << cache_hits_.load() << ","
        << "\"avg_latency_ms\": " << avg_latency_ms_ << "}";
    return ss.str();
}