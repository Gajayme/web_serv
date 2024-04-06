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

	std::string &trim(std::string &s);

	std::vector<std::string> split(const std::string &s, std::string delimiter);

	std::vector<std::string> split(const std::string &s, char delimiter);

	std::vector<std::string> splitAndTrim(const std::string &s, std::string delimiter);

	std::vector<std::string> splitAndTrim(const std::string &s, char delimiter);

	bool isStringDigit(const std::string &s);

	bool ft_isspace(char c);

	template<class InputIt, class UnaryPred>
	InputIt ft_find_if(InputIt first, InputIt last, UnaryPred p) {
		for (; first != last; ++first) {
			if (p(*first))
				return first;
		}
		return last;
	}

	template<class ForwardIt, class UnaryPred>
	ForwardIt ft_remove_if(ForwardIt first, ForwardIt last, UnaryPred p) {
		first = ft_find_if(first, last, p);
		if (first != last) {
			for (ForwardIt i = first; ++i != last;) {
				if (!p(*i))
					*first++ = *i;
			}
		}
		return first;
	}


} // namespace Utils
