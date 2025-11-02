#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.hpp"
#include "request.hpp"
#include "response.hpp"
#include "logger.hpp"

Server::Server(int port) : port_(port), server_fd_(-1) {
    register_routes();
}

void Server::register_routes() {
    router_.get("/health", []() {
        return Response::build(200, "OK");
    });

    router_.get("/metrics", [this]() {
        return Response::build(200, metrics_.json(), "application/json");
    });
}

void Server::start() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1) {
        Logger::error("Error creating socket");
        return;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    int opt = 1;
    setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    if (bind(server_fd_, (struct sockaddr*)&address, sizeof(address)) < 0) {
        Logger::error("bind failed");
        close(server_fd_);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd_, 10) < 0) {
        Logger::error("listen failed");
        close(server_fd_);
        exit(EXIT_FAILURE);
    }

    Logger::info("Server listening on port " + std::to_string(port_) + "...");

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd_, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            Logger::warn("accept failed");
            continue;
        }

        std::thread([this, client_fd]() {
            Logger::info("Handling client...");
            handle_client(client_fd);
            close(client_fd);
            Logger::info("Done.");
        }).detach();
    }

    close(server_fd_);
    
}

void Server::handle_client(int client_fd) {
    auto start_time = std::chrono::steady_clock::now();
    
    char buffer[4096] = {0};
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));

    if (bytes_read <= 0) return;

    std::string raw_request(buffer);
    Request request = Request::parse(raw_request);

    Logger::info(request.method + " " + request.path + " " + request.version);

    std::string response;

    if (request.method.empty() || request.path.empty()) {
        response = Response::build(400, "Bad Request");
    } else if (request.method == "GET") {
        if (router_.has_route(request.path)) {
            response = router_.execute(request.path);
        } else {
            response = serve_static_file(request.path);
            if (response.empty()) {
                response = Response::build(404, "Not Found");
            }
        }
    } else {
        response = Response::build(405, "Method Not Allowed");
    }

    send(client_fd, response.c_str(), response.size(), 0);

    auto end_time = std::chrono::steady_clock::now();
    double duration = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    metrics_.record_request(duration, !response.empty());
    
    Logger::info(request.method + " " + request.path + " -> " +
                 std::to_string(response.size()) + "B in " +
                 std::to_string(duration) + "ms");
}

std::string Server::serve_static_file(const std::string& path) {
    std::string file_path = "../public" + (path == "/" ? "/index.html" : path);

    std::string cached;
    if (cache_.get(file_path, cached)) {
        Logger::info("Cache hit for " + file_path);
        return cached;
    }

    std::ifstream file(file_path, std::ios::binary);

    if (!file.is_open()) return "";

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string body = buffer.str();

    std::string mime = "text/plain";
    if (file_path.size() >= 5 && file_path.substr(file_path.size() - 5) == ".html") mime = "text/html";
    else if (file_path.size() >= 4 && file_path.substr(file_path.size() - 4) == ".css") mime = "text/css";
    else if (file_path.size() >= 3 && file_path.substr(file_path.size() - 3) == ".js") mime = "application/javascript";
    else if (file_path.size() >= 5 && file_path.substr(file_path.size() - 5) == ".json") mime = "application/json";

    std::string response = Response::build(200, body, mime);

    cache_.put(file_path, response);
    Logger::info("Cache miss for " + file_path);
    return response;
}