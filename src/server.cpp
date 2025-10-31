#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.hpp"
#include "request.hpp"
#include "response.hpp"

Server::Server(int port) : port_(port), server_fd_(-1) {}

void Server::start() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    int opt = 1;
    setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    if (bind(server_fd_, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd_);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd_, 10) < 0) {
        perror("listen failed");
        close(server_fd_);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port_ << "..." << std::endl;

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd_, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        std::cout << "New connection accepted." << std::endl;
        handle_client(client_fd);
        close(client_fd);
    }

    close(server_fd_);
    
}

void Server::handle_client(int client_fd) {
    char buffer[4096] = {0};
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));

    if (bytes_read <= 0) return;

    std::string raw_request(buffer);
    Request request = Request::parse(raw_request);

    std::cout << req.method << " " << req.path << " " << req.version << std::endl;

    std::string response;

    if (req.method.empty() || req.path.empty()) {
        response = Response::build(400, "Bad Request");
    } else if (req.path == "/" || req.path == "/index.html") {
        response = Response::build(200, "Hello from C++ HTTP Server!");
    } else {
        response = Response::build(404, "Not Found");
    }

    send(client_fd, response.c_str(), response.size(), 0);
}