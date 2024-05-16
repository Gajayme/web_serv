#include <string>
#include <sstream>
#include <map>
#include <deque>
#include <utility>

#include "Http.h"


class HttpParser
{
    enum {
        REQUEST_LINE,
        HEADERS,
        CONTENT_LENGTH,
        CHUNKED,
    } state;

    HttpRequest req;
    std::deque<HttpRequest> queue;
    std::string line_buffer;
    std::string body_buffer;
    size_t bytes_left;

    bool readline(std::istringstream& data_stream);
    bool read_request_line(std::istringstream& data_stream);
    bool read_headers(std::istringstream& data_stream);
    bool read_plain_body(std::istringstream& data_stream);
    bool read_chunked_body(std::istringstream& data_stream);

    public:

    void read(const char* data);
};