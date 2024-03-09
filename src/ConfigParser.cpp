#include "ConfigParser.h"

#include <iostream>
#include <fstream>
#include "ServerInfo.h"
#include "Utils.h"

namespace {

void configError(const std::string &line) {
	std::cout << "Invalid config format: " << line << std::endl;
	exit(1);
}

} // namespace

ConfigParser::ConfigParser():
configScope_(ConfigScopeGlobal),
brackets_(),
servers_() {

}

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


bool ConfigParser::isSeverScope(const std::vector<std::string> &toParse) {
	std::string fullString;
	for (std::vector<std::string>::const_iterator it = toParse.begin(); it != toParse.end(); ++it) {
		fullString += *it;
	}
	return !brackets_.empty() && fullString == (SERVER+OPENBRACKET);
}

void ConfigParser::parseLine(std::string &line) {
	std::string stringToParse(line);
	utils::trim(stringToParse);
	utils::tolowerString(stringToParse);
	if (line.empty()) {
		return;
	}

	if (configScope_ == ConfigScopeGlobal) {
		std::vector<std::string> splitLine = utils::split(line, WHITESPACE);
		if (!isSeverScope(splitLine)) {
			configError(line);
		}
		else {
			configScope_ = ConfigScopeServer;
			servers_.push_back(ServerInfo());
			brackets_.push(OPENBRACKET);
		}

	} else if (configScope_ == ConfigScopeServer) {
		//TODO
	} else if (configScope_ == ConfigScopeLocation) {
		//TODO
	}
}




ConfigParser::~ConfigParser() {
	std::cout << "Destroying config parser" << std::endl;
}
