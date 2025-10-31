#include "request.hpp"
#include <sstream>
#include <algorithm>

Request Request::parse(const std::string& raw) {
    std::istringstream stream(raw);
    Request req;
    std::string line;

    if (std::getline(stream, line)) {
        std::istringstream line_stream(line);
        line_stream >> req.method >> req.path >> req.version;
    }

    while (std::getline(stream, line) && line != "\r") {
        std::size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            key.erase(std::remove(key.begin(), key.end(), '\r'), key.end());
            value.erase(0, value.find_first_not_of(" \t\r\n"));
            value.erase(value.find_last_not_of(" \t\r\n") + 1);
            req.headers[key] = value;
        }
    }

    if (stream.peek() == EOF) {
        std::getline(stream, req.body, '\0');
    }

    return req;
}