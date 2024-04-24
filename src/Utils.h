#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <stack>


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

	void trim(std::string &s);

	std::vector<std::string> split(const std::string &s, const std::string &delimiter);

	bool isStringDigit(const std::string &s);

	bool ft_isspace(char c);

	template <typename T>
	void clear_stack(std::stack<T> &stackToClear) {
	while (!stackToClear.empty()) {
		stackToClear.pop();
	}
}

} // namespace Utils
