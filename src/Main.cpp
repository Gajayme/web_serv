#include "Server.h"

#include "ConfigParser.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Invalid amount of arguments" << std::endl;
		exit(1);
	}

	ConfigParser configParser;
	configParser.parseConfig();

//	Server serv;
//	serv.runServer();
	return 0;
}
