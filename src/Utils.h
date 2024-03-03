#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cctype>


namespace utils {

	enum Colors {
		RED      = 31,
		GREEN    = 32,
		YELLOW   = 33,
		BLUE     = 34,
		DEFAULT  = 39,
	};

	void colour_out(Colors col, const std::string &s);

	void tolowerString(std::string &s);

	std::vector<std::string> split(const std::string &s, std::string delimiter);

} // namespace Utils
