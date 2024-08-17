#include "Context.h"
#include <string>
#include <iostream>

int main() {

	Context context;
	context.initStates();

	std::string str_1("string 1");
	std::string str_2("string 2");

	std::cout << "before parsing" <<std::endl;

	context.parseLine(str_1);
	context.parseLine(str_2);

	return 0;
}