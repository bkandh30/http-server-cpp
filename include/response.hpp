#pragma once
#include <string>

class Response {
    public:
        static std::string build(int status, const std::string& body, const std::string& contentType = "text/plain");
};