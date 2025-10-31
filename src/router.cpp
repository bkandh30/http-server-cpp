#include "router.hpp"

void Router::get(const std::string& path, Handler handler) {
    routes_[path] = handler;
}

bool Router::has_route(const std::string& path) const {
    return routes_.find(path) != routes_.end();
}

std::string Router::execute(const std::string& path) const {
    auto it = routes_.find(path);
    if (it != routes_.end()) {
        return it->second();
    }
    return "";
}