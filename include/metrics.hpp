#pragma once
#include <chrono>
#include <string>
#include <atomic>
#include <mutex>

class Metrics {
    public:
        static Metrics& Instance();

        void record_request(double latency_ms, bool cache_hit);
        std::string json() const;

    private:
        Metrics() = default;
        mutable std::mutex mutex_;
        std::atomic<size_t> total_requests_{0};
        std::atomic<size_t> cache_hits_{0};
        
        double avg_latency_ms_{0.0};
};