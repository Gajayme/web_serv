#pragma once

#include <string>
#include <sstream>
#include <map>
#include <deque>
#include <utility>
#include <stdexcept>


typedef std::map<std::string, std::string> headers_map;

struct ParsedHttpRequest
{
    std::string method;
    std::string ver;
    std::string target; // URI
    headers_map headers;
    std::string body;
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
        PLAIN_BODY,
        CHUNKED_SIZE,
        CHUNKED_DATA,
        TRAILERS,
    } state;

    ParsedHttpRequest req;
    std::deque<ParsedHttpRequest> queue;
    std::string line_buffer;
    std::string body_buffer;
    size_t bytes_left;

    bool readline_to_buffer(std::istringstream& data_stream);
    bool read_request_line(std::istringstream& data_stream);
    bool read_headers(std::istringstream& data_stream);
    bool read_bytes_left(std::istringstream& data_stream);
    bool read_chunked_data(std::istringstream& data_stream);
    bool read_chunked_size(std::istringstream& data_stream);
    bool read_trailers(std::istringstream& data_stream);
    bool read_plain_body(std::istringstream& data_stream);

    void complete_req();
    void strip_chunked();
   
    static std::pair<std::string, std::string> parse_header(const std::string& line);
    static bool parse_Transfer_Encoding_Chunked(const std::string& line);

    template<int BASE>
    static size_t parse_size_field(const std::string& line); // = delete;

    public:

    void read(const char* data);
};