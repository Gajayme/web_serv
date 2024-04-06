#include "ConfigParser.h"

#include <iostream>
#include <fstream>
#include "ServerInfo.h"
#include "Utils.h"

namespace {

/**
 * @brief Print server parsing error and exit.
 * @param line line in which error occurred.
 * @param error error description.
 */
void configError(const std::string &line = "", const std::string error = "") {
	std::cout << "ConfigParser: " << error << std::endl << "In line: " << line << std::endl;
	exit(1);
}

} // namespace

ConfigParser::ConfigParser():
configScope_(ConfigScopeGlobal),
scopeStack_(),
servers_() {
}

ConfigParser::~ConfigParser() {}

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


void ConfigParser::parseGlobalScope(const std::string &line) {
	std::string lineCopy(line);
	lineCopy.erase(utils::ft_remove_if(lineCopy.begin(), lineCopy.end(), utils::ft_isspace), lineCopy.end());
	utils::tolowerString(lineCopy);

	if (lineCopy == SERVER and scopeStack_.empty()) {
		scopeStack_.push(SERVER);
	} else if (lineCopy == OPEN_BRACKET && scopeStack_.top() == SERVER) {
		scopeStack_.push(OPEN_BRACKET);
		servers_.push_back(ServerInfo());
		configScope_ = ConfigScopeServer;
	} else if (lineCopy == SERVER + OPEN_BRACKET and scopeStack_.empty()) {
		scopeStack_.push(SERVER);
		scopeStack_.push(OPEN_BRACKET);
		servers_.push_back(ServerInfo());
		configScope_ = ConfigScopeServer;
	} else {
		configError("config error", line);
		exit(1);
	}
}

void ConfigParser::parseServerScope(const std::string &line) {
	std::vector<std::string> splitLine = utils::splitAndTrim(line, SEMICOLON);
	if (splitLine.size() != 2 ) {
		configError(line);
		exit(1);
	} else if (servers_.empty()) {
		configError(line, "no servers to parse settings for");
	}
	ServerInfo &server = servers_.back();
	if (splitLine.front() == SERVER_NAME) {
		server.setName(splitLine.back());
	} else if (splitLine.front() == LISTEN) {
		server.setPort(splitLine.back());
	} else if (splitLine.front() == HOST) {
		server.setIp(splitLine.back());
	} else if (splitLine.front() == BODY_SIZE) {
		std::string maxBodySizeStr = splitLine.back();
		if (!utils::isStringDigit(maxBodySizeStr)) {
			configError(line, "client max body size should be digital");
		}
		server.setMaxBodySize(stoi(splitLine.back()));
	} else if (splitLine.front() == CLOSE_BRACKET) {
		if (!server.checkServerInfo())
			configError(line, "lack of server parameters");
	} else {
		configError(line, "config error");
	}
}


void ConfigParser::parseLine(const std::string &line) {
	if (line.empty()) {
		return;
	}
	if (configScope_ == ConfigScopeGlobal) {
		parseGlobalScope(line);
	} else if (configScope_ == ConfigScopeServer) {
		parseServerScope(line);
	} else if (configScope_ == ConfigScopeLocation) {
		//TODO
	}
}
