#include "response.hpp"
#include <sstream>

std::string Response::build(int status, const std::string& body, const std::string& contentType) {
    std::ostringstream res;
    std::string statusText;

    switch (status) {
        case 200: statusText = "OK"; break;
        case 400: statusText = "Bad Request"; break;
        case 404: statusText = "Not Found"; break;
        default:  statusText = "Internal Server Error"; break;
    }

    res << "HTTP/1.1 " << status << " " << statusText << "\r\n"
        << "Content-Type: " << contentType << "\r\n"
        << "Content-Length: " << body.size() << "\r\n"
        << "\r\n"
        << body;

    return res.str();
}