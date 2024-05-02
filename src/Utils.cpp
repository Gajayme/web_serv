#include "Utils.h"

namespace utils {

void colour_out(Colors col, const std::string &s) {
	std::cout << "\033[1;"<<static_cast<int>(col)<<"m"<< s << "\033[0m" << std::endl;
}

void tolowerString(std::string &s) {
	for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
		*it = static_cast<char>(tolower(*it));
	}
}

void trim(std::string &s) {
	size_t i = 0;
	while (isspace(s[i]))
		i++;
	s = s.substr(i, s.length() - i);

	i = s.length() - 1;
	while (isspace(s[i]))
		i--;
	s = s.substr(0, i + 1);
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

bool ft_isspace(char x) {
	return std::isspace(x);
}

} // namespace Utils
