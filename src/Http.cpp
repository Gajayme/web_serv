#include <string>
#include <sstream>
#include <map>
#include <utility>

#include "Utils.h"
#include "Http.h"

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

    std::pair<std::string, std::vector<std::string>> parseHeader(const std::string& line)
    {
        std::vector<std::string> split = utils::splitAndTrim(line, ":", 1); // todo const
        
        if (split.size() != 2 ) throw std::exception(); // ????

        std::string& header = split[0];
        std::string& value = split[1];

        std::cout << "parseHeader " << header << " -- " << value << "\n";

        std::vector<std::string> values(1, value); // todo split

        return { header, values };
    };
};


HttpRequest HttpRequest::create(const char* raw)
{
    std::istringstream data_stream(raw);
    std::string str;

    // RFC 9112: method SP request-target SP HTTP-version

    //data_stream >> str; // method
    std::getline(data_stream, str, ' '); // method
    std::cout << "method " << str << "\n";
    HttpMethod method = parseMethod(str);

    //data_stream >> str; // request-target
    std::getline(data_stream, str, ' '); // request-target
    std::cout << "request-target " << str << "\n";

    HttpRequest request(method, str); // this is enough to create request

    //data_stream >> str; // HTTP-version
    std::getline(data_stream, str); // HTTP-version
    std::cout << "HTTP-version " << str << "\n";
    if (str != "HTTP/1.1\r") throw std::exception(); // ????

    while (std::getline(data_stream, str))
    {
        if (str == "\r") break; // headers and body are separated with empty line and we reached it 
        
        std::pair<std::string, std::vector<std::string>> info = parseHeader(str);
        for (std::vector<std::string>::iterator it = info.second.begin(); it != info.second.end(); it++)
            request._headers.insert({info.first, *it});
    }

    return request;
}