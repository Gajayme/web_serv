#include "Utils.h"
#include <algorithm>
#include <cctype>

namespace utils {

void colour_out(Colors col, const std::string &s) {
	std::cout << "\033[1;"<<static_cast<int>(col)<<"m"<< s << "\033[0m" << std::endl;
}

void tolowerString(std::string &s) {
	for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
		*it = static_cast<char>(tolower(*it));
	}
}

static struct c98etokaif
{
	bool operator()(unsigned char ch) {return !std::isspace(ch);}
} lambda;

// trim from start (in place)
void ltrim(std::string &s) 
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), lambda));
}

// trim from end (in place)
void rtrim(std::string &s) 
{
    s.erase(std::find_if(s.rbegin(), s.rend(), lambda).base(), s.end());
}

void trim(std::string &s)
{
	rtrim(s);
	ltrim(s);
}

std::vector<std::string> split(const std::string &s, const std::string& delimiter, size_t limit) 
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;
	for (size_t i = 0; (!limit || i < limit) && ((pos_end = s.find(delimiter, pos_start)) != std::string::npos); ++i)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
		// Note. Made this to correct splitting lines with multiple delimiters going one by one
		pos_start = s.find_first_not_of(delimiter, pos_start);
	}
	res.push_back (s.substr (pos_start));
	return res;
}

std::vector<std::string> splitAndTrim(const std::string &s, const std::string delimiter, size_t limit) 
{
	std::vector<std::string> res = split(s, delimiter, limit);
	for (size_t i = 0; i < res.size(); ++i) trim(res[i]);
	return res;
}


std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;
	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
		// Note. Made this to correct splitting lines with multiple delimiters going one by one
		pos_start = s.find_first_not_of(delimiter, pos_start);
	}
	res.push_back (s.substr (pos_start));
	return res;
}

bool isStringDigit(const std::string &s) {
	for(size_t i = 0; i < s.size(); ++i)
		if(!isdigit(s[i])) {
			return false;
		}
	return true;
}

bool isStringHexDigit(const std::string &s) {
	for(size_t i = 0; i < s.size(); ++i)
		if(!isxdigit(s[i])) {
			return false;
		}
	return true;
}

bool ft_isspace(char x) {
	return std::isspace(x);
}

void configError(const std::string &funkName, const std::string &line, const std::string &error) {
	std::cout << "ConfigParser::" << funkName << ":: " << error << std::endl << "In line: " << line << std::endl;
	exit(1);
}

} // namespace Utils
