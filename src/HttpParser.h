#pragma once

#include <string>
#include <sstream>
#include <map>
#include <deque>
#include <utility>
#include <stdexcept>


struct ParsedHttpRequest
{
    std::string method;
    std::string ver;
    std::string target; // URI
    std::map<std::string, std::string> headers;
};


struct bad_request : public std::runtime_error 
{
    bad_request(const std::string& s) : std::runtime_error(s) {};
};

class HttpParser
{
    enum {
        REQUEST_LINE,
        HEADERS,
        CONTENT_LENGTH,
        CHUNKED,
    } state;

    ParsedHttpRequest req;
    std::deque<ParsedHttpRequest> queue;
    std::string line_buffer;
    std::string body_buffer;
    size_t bytes_left;

    bool readline(std::istringstream& data_stream);
    bool read_request_line(std::istringstream& data_stream);
    bool read_headers(std::istringstream& data_stream);
    bool read_plain_body(std::istringstream& data_stream);
    bool read_chunked_body(std::istringstream& data_stream);

    static std::pair<std::string, std::string> parseHeader(const std::string& line);

    public:

    void read(const char* data);
};