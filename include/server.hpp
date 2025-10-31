#pragma once
#include <string>

class Server {
    public:
        explicit Server(int port);
        void start();

    private:
        int port_;
        int server_fd_;
        void handle_client(int client_fd);
};