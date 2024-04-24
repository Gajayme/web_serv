#include "ConfigParser.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include "ServerInfo.h"
#include "Utils.h"
#include <arpa/inet.h>
#include <sstream>

namespace {

/**
 * @brief Print server parsing error and exit.
 * @param line line in which error occurred.
 * @param error error description.
 */
void configError(const std::string &funkName = "", const std::string &line = "", const std::string &error = "config error") {
	std::cout << "ConfigParser::" << funkName << ":: " << error << std::endl << "In line: " << line << std::endl;
	exit(1);
}

/**
 * @brief Validate ip address.
 * @param ipAddress id address.
 * @return true if ip correct false otherwise
 */
bool validateIpAddress(const std::string &ip) {
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
	return result != 0;
}

/**
 * @brief Remove comment section from config line.
 * @param s Line, to remove comment from.
 */
void removeComment(std::string &s) {
	const size_t hashtagPos = s.find_first_of(HASHTAG);
	if (hashtagPos != std::string::npos) {
		s.erase(s.cbegin() + static_cast<std::string::difference_type>(hashtagPos), s.cend());
	}
}



} // namespace

ConfigParser::ConfigParser():
		configScope_(),
		servers_(),
		scopeStack_() {
}

ConfigParser::~ConfigParser() {}

void ConfigParser::parseConfig(const std::string &path) {
	configScope_ = ConfigScopeGlobal;
	std::ifstream config;
	config.open(path);

	if (!config.is_open()) {
		std::cout << "ConfigParser::parseConfig::error while opening config file" << std::endl;
		exit(1);
	}

	std::string line;
	while (getline (config, line)) {
		parseLine(line);
	}
	config.close();
}

void ConfigParser::parseLine(std::string &line) {
	removeComment(line);
	utils::trim(line);
	if (line.empty()) {
		return;
	}
	if (configScope_ == ConfigScopeGlobal) {
		parseGlobalScope(line);
	} else if (configScope_ == ConfigScopeServer) {
		parseServerScope(line);
	} else if (configScope_ == ConfigScopeLocation) {
		// TODO implement
		exit (1);
	}
}


void ConfigParser::parseGlobalScope(const std::string &line) {
	std::string lineCopy(line);
	lineCopy.erase(std::remove_if(lineCopy.begin(), lineCopy.end(), utils::ft_isspace), lineCopy.end());
	utils::tolowerString(lineCopy);

	if (lineCopy == SERVER + OPEN_BRACKET and scopeStack_.empty()) {
		scopeStack_.push(SERVER);
		scopeStack_.push(OPEN_BRACKET);
		servers_.push_back(ServerInfo(generateServerDefaultName()));
		configScope_ = ConfigScopeServer;
	} else {
		configError(__func__, line);
	}
}

void ConfigParser::parseServerScope(const std::string &line) {
	std::string lineCopy(line);
	lineCopy.erase(std::remove_if(lineCopy.begin(), lineCopy.end(), utils::ft_isspace), lineCopy.end());
	utils::tolowerString(lineCopy);

	if (lineCopy == CLOSE_BRACKET) {
		if (!servers_.back().checkServerInfo()) {
			configError(__func__, line, "lack of server parameters");
		}
		configScope_ = ConfigScopeGlobal;
		std::cout << "Server Parsed" << std::endl;
		std::cout << servers_.back() << std::endl;
		return;
	}

	std::vector<std::string> splitLine = utils::split(lineCopy, SEMICOLON);
	if (splitLine.size() != 2 || servers_.empty()) {
		configError(__func__ , line);
	}

	ServerInfo &server = servers_.back();
	if (splitLine.front() == SERVER_NAME) {
		server.setName(splitLine.back());
	} else if (splitLine.front() == LISTEN) {
		server.setPort(splitLine.back());
	} else if (splitLine.front() == HOST) {
		if (!validateIpAddress(splitLine.back())) {
			configError(__func__, line, "wrong ip address");
		}
		server.setIp(splitLine.back());
	} else if (splitLine.front() == BODY_SIZE) {
		std::string maxBodySizeStr = splitLine.back();
		if (!utils::isStringDigit(maxBodySizeStr) or maxBodySizeStr == ZERO) {
			configError(__func__, line, "wrong max body size");
		}
		server.setMaxBodySize(stoi(splitLine.back()));
	} else {
		configError(__func__, line);
	}
}

std::string ConfigParser::generateServerDefaultName() {
	std::stringstream ss;
	ss << servers_.size() + 1;
	std::string serverNum(ss.str());
	return DEFAULT_SERVER_NAME + serverNum;
}
