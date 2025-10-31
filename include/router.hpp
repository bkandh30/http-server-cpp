#pragma once
#include <functional>
#include <string>
#include <unordered_map>

class Router {
    public:
        using Handler = std::function<std::string()>;

        void get(const std::string& path, Handler handler);
        bool has_route(const std::string& path) const;
        std::string execute(const std::string& path) const;

    private:
        std::unordered_map<std::string, Handler> routes_;
};