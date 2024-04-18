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
    HttpMethod _method;
    HttpVersion _ver;
    std::string _target; // URI
    std::multimap<std::string, std::string> _headers;

    HttpRequest(HttpMethod method, std::string& target) : 
        _method(method),
        _target(target),
        _ver(HTTP_1_1)
    {};

    // HttpRequest(const HttpRequest&) = default;

    public:

    static HttpRequest create(const char* raw);
};