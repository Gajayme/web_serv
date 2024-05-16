#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <stdexcept>

#include "HttpParser.h"


namespace 
{
    HttpMethod parseMethod(const std::string& str)
    {
        if (str == "GET")
            return GET;
        else if (str == "PUT")
            return PUT;
        else if (str == "DELETE")
            return DELETE;
        else {
            return UNSUPPORTED;
        }
    };

    std::pair<std::string, std::string> parseHeader(const std::string& line)
    {
        // RFC 9112: field-line = field-name ":" OWS field-value OWS

        std::vector<std::string> split = utils::splitAndTrim(line, ":", 1); // todo const
        
        if (split.size() != 2 ) throw std::runtime_error("parseHeader size != 2");

        std::string& header = split[0];
        std::string& value = split[1];

        std::cout << "parseHeader " << header << " -- " << value << "\n";

        return { header, value };
    };
};

bool HttpParser::readline(std::istringstream& data_stream)
{
    for (char ch = data_stream.get(); data_stream && ch != '\n' ; ch = data_stream.get())
    {
        line_buffer.push_back(ch);
    }
    return bool(data_stream);
}

bool HttpParser::read_request_line(std::istringstream& data_stream)
{
    if (!readline(data_stream)) return false;

    if (line_buffer == "\r")
        /*
        RFC 9112:
        In the interest of robustness, a server that is expecting to receive and 
        parse a request-line SHOULD ignore at least one empty line (CRLF) 
        received prior to the request-line.
        */
        return true;

    // RFC 9112: method SP request-target SP HTTP-version

    std::vector<std::string> split = utils::split(line_buffer, " ", 2); // todo const

    if (split.size() != 3) throw std::runtime_error("read_request_line size != 3");

    std::cout << "method " << split[0] << "\n";
    std::cout << "request-target " << split[1] << "\n";
    std::cout << "HTTP-version " << split[2] << "\n";

    req = HttpRequest();
    req.method = parseMethod(split[0]);
    req.target = split[1];
    if (split[2] != "HTTP/1.1\r") throw std::runtime_error("unsupported ver"); // ????

    line_buffer.clear();
    state = HEADERS;

    return true;
}

bool HttpParser::read_headers(std::istringstream& data_stream)
{
    if (!readline(data_stream)) return false;

    if (line_buffer == "\r")
    {
        line_buffer.clear();
        std::cout << "headers end\n";
        // todo resolve next state
        return false;
    }

    std::pair<std::string, std::string> header = parseHeader(line_buffer);

    // todo parse header

    req.headers.insert(header);
    line_buffer.clear();
    return true;
}


void HttpParser::read(const char* data)
{
    std::istringstream data_stream(data);
    bool have_data = true;
    
    while (have_data)
    {
        switch (state)
        {
        case REQUEST_LINE:
            have_data = read_request_line(data_stream);
            break;
        case HEADERS:
            have_data = read_headers(data_stream);
            break;
        case CONTENT_LENGTH:
            //have_data = read_plain_body(data_stream);
            break;
        case CHUNKED:
            //have_data = read_chunked_body(data_stream);
            break;
        
        default:
            throw std::runtime_error("pizdec");
        }
    }
}