#include "Server.hpp"
#include <string>
#include <iostream>

enum class Color: int {
	RED      = 31,
	GREEN    = 32,
	YELLOW   = 33,
	BLUE     = 34,
	DEFAULT  = 39,
};

void colour_out(Color col, std::string str) {
	std::cout << "\033[1;"<<static_cast<int>(col)<<"m"<< str << "\033[0m\n";

}

int main() {
	colour_out(Color::YELLOW, "hut");
	return 0;
}
