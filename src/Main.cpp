#include "Server.h"

#include "config_parser/ConfigParser.h"
#include "string"

int main() {

	std::string defaultConfig("./configs/default.conf");

	ConfigParser configParser;
	configParser.parseConfig(defaultConfig);

	// TODO надо засовывать в сервер первое инфо (которое надо провалидировать)
	Server serv(configParser.getServers().front());
	serv.runServer();
	return 0;
}
