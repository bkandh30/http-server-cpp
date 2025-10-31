#include "server.hpp"
#include "logger.hpp"
#include <cstdlib>

int main(int argc, char* argv[]) {
    int port = 8080;
    if (argc > 1) port = std::stoi(argv[1]);
    else if (const char* env_port = std::getenv("PORT")) port = std::stoi(env_port);

    Logger::info("Launching server...");
    Server server(port);
    server.start();
    return 0;
}