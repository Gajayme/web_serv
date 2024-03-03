#include "ConfigParser.h"

#include <iostream>
#include <fstream>
#include "Utils.h"

namespace {
	std::string DEFAULT_CONFIG_PATH("/Users/georgii/School_21/web_serv/configs/default.conf");
	std::string SERVER("server");
	std::string NAME("server_name");
	std::string LISTEN("listen");
	std::string HOST("host");
	std::string BODY_SIZE("client_max_body_size");
} // namespace

ConfigParser::ConfigParser() {}

void ConfigParser::parseConfig(const std::string &path) {
	std::ifstream config;
	config.open(path);

	if (!config.is_open()) {
		std::cout << "Error while opening config file" << std::endl;
		exit(1);
	}

	std::string line;
	while (getline (config,line)) {
		parseLine(line);
	}
	config.close();
}

void ConfigParser::parseLine(std::string &line) {
	utils::tolowerString(line);


	if (line.rfind(SERVER, 0)) {

		servers_.emplace_back(ServerInfo());
	} else if () {

	}
}


ConfigParser::~ConfigParser() {
	std::cout << "Destroying config parser" << std::endl;
}
