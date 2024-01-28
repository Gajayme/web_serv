#include "Server.hpp"
#include <string>
#include <iostream>

namespace utils {

	enum Colors {
		RED      = 31,
		GREEN    = 32,
		YELLOW   = 33,
		BLUE     = 34,
		DEFAULT  = 39,
	};

	void colour_out(Colors col, std::string str) {
		std::cout << "\033[1;"<<static_cast<int>(col)<<"m"<< str << "\033[0m" << std::endl;
	}

} // namespace Utils
