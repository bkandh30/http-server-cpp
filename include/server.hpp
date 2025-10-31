#pragma once
#include <string>
#include <thread>

class Server {
    public:
        explicit Server(int port);
        void start();

    private:
        int port_;
        int server_fd_;
        void handle_client(int client_fd);
        std::string serve_static_file(const std::string& path);
};