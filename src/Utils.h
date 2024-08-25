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

	void ltrim(std::string &s);
	void rtrim(std::string &s);
	void trim(std::string &s);

	std::vector<std::string> split(const std::string &s, const std::string& delimiter, size_t limit = 0);

	std::vector<std::string> splitAndTrim(const std::string &s, std::string delimiter, size_t limit = 0);

	bool isStringDigit(const std::string &s);
	bool isStringHexDigit(const std::string &s);

	bool ft_isspace(char c);

	/**
	 * @brief Print server parsing error and exit.
	 * @param line line in which error occurred.
	 * @param error error description.
	 */
	void configError(const std::string &funkName = "", const std::string &line = "", const std::string &error = "config error");


	template <typename T>
	void clear_stack(std::stack<T> &stackToClear) {
		while (!stackToClear.empty()) {
			stackToClear.pop();
		}
	}

} // namespace Utils
