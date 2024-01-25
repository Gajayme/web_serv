#include "Server.hpp"
#include <string>
#include <iostream>

namespace Color {
	enum color{
		RED      = 31,
		GREEN    = 32,
		YELLOW   = 33,
		BLUE     = 34,
		DEFAULT  = 39,
	};

	void colour_out(color col, std::string & str) {
	std::cout << "\033[1;"<<static_cast<int>(col)<<"m"<< str << "\033[0m\n";
}
}



int main() {
	std::string a = "tut";
	colour_out(Color::BLUE, a);
	return 0;
}
