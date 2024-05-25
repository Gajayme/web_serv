#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include "HttpParser.h"
#include "Utils.h"

template<>
size_t HttpParser::parse_size_field<10>(const std::string& line)
{
    if (!utils::isStringDigit(line)) throw bad_request("invalid size: " + line);

    unsigned long result = std::strtoul(line.data(), NULL, 10);

    if (errno) throw std::logic_error("out of range");

    // static_assert(sizeof(size_t) == sizeof(long))
    return result;
};

template<>
size_t HttpParser::parse_size_field<16>(const std::string& line)
{
    if (!utils::isStringHexDigit(line)) throw bad_request("invalid size: " + line);

    unsigned long result = std::strtoul(line.data(), NULL, 16);

    if (errno) throw std::logic_error("out of range");

    // static_assert(sizeof(size_t) == sizeof(long))
    return result;
};

std::pair<std::string, std::string> HttpParser::parse_header(const std::string& line)
{
    // RFC 9112: field-line = field-name ":" OWS field-value OWS

    std::vector<std::string> split = utils::splitAndTrim(line, ":", 1); // todo const
    
    if (split.size() != 2 ) throw bad_request("parseHeader size != 2");

    std::string& header = split[0];
    std::string& value = split[1];

    std::cout << "parseHeader " << header << " -- " << value << "\n";

    return std::pair<std::string, std::string>(header, value);
};

bool HttpParser::parse_Transfer_Encoding_Chunked(const std::string& line)
{
    size_t pos = line.find("chunked");
    if (pos == line.npos) return false;
    if (pos != line.npos - std::strlen("chunked")) throw bad_request("chunked is not final encoding");
    return true;
};


bool HttpParser::readline_to_buffer(std::istringstream& data_stream)
{
    while (true)
    {
        char ch = data_stream.get();

        if (ch == std::istringstream::traits_type::eof())
            return false;

        if (ch == '\n')
            return true;

        line_buffer.push_back(ch);

    }
}

bool HttpParser::read_bytes_left(std::istringstream& data_stream)
{
    while (true)
    {
        char ch = data_stream.get();
        
        if (ch == std::istringstream::traits_type::eof())
            return false;

        if (!bytes_left)
            return true;

        req.body.push_back(ch);
        --bytes_left;
    }
}

bool HttpParser::read_plain_body(std::istringstream& data_stream)
{
    if (!read_bytes_left(data_stream)) return false;
    complete_req();
    return true;
}

bool HttpParser::read_chunked_size(std::istringstream& data_stream)
{
    if (!readline_to_buffer(data_stream)) return false;

    // chunk = chunk-size [ chunk-ext ] CRLF
    //         chunk-data CRLF

    // chunk-size = 1*HEXDIG

    // ignoring [ chunk-ext ] 
    std::vector<std::string> split = utils::split(line_buffer, ";", 1);
    std::string& size = split[0];
    utils::trim(size);

    bytes_left = parse_size_field<16>(size);

    if (!bytes_left) state = TRAILERS;
    else state = CHUNKED_DATA;
    
    line_buffer.clear();
    return true;
}

bool HttpParser::read_chunked_data(std::istringstream& data_stream)
{
    if (!read_bytes_left(data_stream)) return false;

    // need to read CRLF
    if (!readline_to_buffer(data_stream)) return false;

    if (line_buffer != "\r")
        throw bad_request("chunked-data is not ending with CRLF");
    
    line_buffer.clear();
    state = CHUNKED_SIZE;
    return true;
}

bool HttpParser::read_trailers(std::istringstream& data_stream)
{
    if (!readline_to_buffer(data_stream)) return false;

    if (line_buffer == "\r")
        strip_chunked();
        complete_req();
    
    line_buffer.clear();
    return true;
}

void HttpParser::complete_req()
{
    std::cout << "request end\n";
    queue.push_back(req);
    state = REQUEST_LINE;
}

void HttpParser::strip_chunked()
{
    std::string& encoding_list = req.headers.at("Transfer-Encoding");
    // remove last encoding, which should be chunked
    for (size_t i = encoding_list.size() - 1; i >= 0 && encoding_list[i] != ','; --i)
    {
        encoding_list.pop_back();
    }
    if (encoding_list.empty())
        req.headers.erase("Transfer-Encoding");
}

bool HttpParser::read_request_line(std::istringstream& data_stream)
{
    if (!readline_to_buffer(data_stream)) return false;

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

    if (split.size() != 3) throw bad_request("read_request_line size != 3");

    std::cout << "method " << split[0] << "\n";
    std::cout << "request-target " << split[1] << "\n";
    std::cout << "HTTP-version " << split[2] << "\n";

    req = ParsedHttpRequest();
    req.method = split[0];
    req.target = split[1];
    req.ver = split[2];

    line_buffer.clear();
    state = HEADERS;

    return true;
}

bool HttpParser::read_headers(std::istringstream& data_stream)
{
    if (!readline_to_buffer(data_stream)) return false;

    if (line_buffer == "\r")
    {
        // we received last CRLF before message body

        headers_map::iterator length_it = req.headers.find("Content-Length");
        headers_map::iterator transfer_encoding_it = req.headers.find("Transfer-Encoding");

        if (transfer_encoding_it != req.headers.end())
        {
            if (length_it != req.headers.end()) 
                throw bad_request("message contains both Content-Length and Transfer-Encoding");
            
            if (parse_Transfer_Encoding_Chunked(transfer_encoding_it->second))
            {
                state = CHUNKED_SIZE;
            }
            else
            {
                complete_req();
            }
            
        }
        else if (length_it != req.headers.end())
        {
            bytes_left = parse_size_field<10>(length_it->second);
            state = PLAIN_BODY;
        }
        else
        {
            std::cout << "request end\n";
            state = REQUEST_LINE;
        }
    }
    else
    {
        std::pair<std::string, std::string> header = parse_header(line_buffer);
        req.headers.insert(header);
    }

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
        case PLAIN_BODY:
            have_data = read_plain_body(data_stream);
            break;
        case CHUNKED_SIZE:
            have_data = read_chunked_size(data_stream);
            break;
        case CHUNKED_DATA:
            have_data = read_chunked_data(data_stream);
            break;
        case TRAILERS:
            have_data = read_trailers(data_stream);
            break;
        
        default:
            throw std::logic_error("pizdec");
        }
    }
}