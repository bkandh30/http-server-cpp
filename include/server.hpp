#pragma once
#include <string>
#include <thread>

#include "router.hpp"
#include "logger.hpp"
#include "metrics.hpp"
#include "cache.hpp"

class Server {
    public:
        explicit Server(int port);
        void start();

    private:
        int port_;
        int server_fd_;
        Router router_;
        FileCache cache_{20};
        std::atomic<bool> running_{true};
        Metrics& metrics_ = Metrics::Instance();
        
        void handle_client(int client_fd);
        std::string serve_static_file(const std::string& path);
        void register_routes();
};