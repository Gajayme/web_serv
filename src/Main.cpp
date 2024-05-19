#include "Server.h"

#include "ConfigParser.h"
#include "string"

int main() {

	std::string defaultConfig("./configs/default.conf");

	ConfigParser configParser;
	configParser.parseConfig(defaultConfig);

	Server serv;
	serv.runServer();
	return 0;
}
