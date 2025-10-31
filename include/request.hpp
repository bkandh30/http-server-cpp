#pragma once
#include <string>
#include <unordered_map>

struct Request {
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    static Request parse(const std::string& raw);
};