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

std::vector<std::string> split(const std::string &s, const std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;
	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}
		res.push_back (s.substr (pos_start));
		return res;
	}


std::vector<std::string> split(const std::string &s, const char delimiter) {
	size_t pos_start = 0, pos_end, delim_len = 1;
	std::string token;
	std::vector<std::string> res;
	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}
	res.push_back (s.substr (pos_start));
	return res;
}



void trim(std::string &s) {
	std::string::const_iterator itBegin = s.cbegin();
	std::string::const_iterator itEnd = s.cend();
	while (itBegin < itEnd) {
		if (!std::isspace(*itBegin) && !std::isspace(*itEnd)) {
			break;
		}
		if (std::isspace(*itBegin) ) {
			++itBegin;
		}
		if (std::isspace(*itEnd)) {
			-- itEnd;
		}
	}
	s = std::string(itBegin, itEnd);
}

} // namespace Utils
