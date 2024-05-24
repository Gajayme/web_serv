#pragma once

#include <string>
#include <sstream>
#include <map>
#include <utility>

#include "Utils.h"

enum HttpMethod
{
    UNSUPPORTED,
    GET,
    PUT,
    DELETE,
};

enum HttpVersion
{
    HTTP_1_1,
};

class HttpRequest
{
    public:

    HttpMethod method;
    HttpVersion ver;
    std::string target; // URI
    std::map<std::string, std::string> headers;

    HttpRequest() : 
        method(UNSUPPORTED),
        ver(HTTP_1_1)
    {};

    // HttpRequest(const HttpRequest&) = default;

};

// HttpMethod parseMethod(const std::string& str)
// {
//     if (str == "GET")
//         return GET;
//     else if (str == "PUT")
//         return PUT;
//     else if (str == "DELETE")
//         return DELETE;
//     else {
//         return UNSUPPORTED;
//     }
// };