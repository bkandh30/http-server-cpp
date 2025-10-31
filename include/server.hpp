#pragma once
#include <string>
#include <thread>

#include "router.hpp"

class Server {
    public:
        explicit Server(int port);
        void start();

    private:
        int port_;
        int server_fd_;
        Router router_;

        void handle_client(int client_fd);
        std::string serve_static_file(const std::string& path);
        void register_routes();
};