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
		context_(),
		servers_() {
}

ConfigParser::~ConfigParser() {}

void ConfigParser::parseConfig(const std::string &path) {
	context_ = ContextGlobal;
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
	if (context_ == ContextGlobal) {
		parseGlobalContext(line);
	} else if (context_ == ContextServer) {
		parseServerContext(line);
	} else if (context_ == ContextLocation) {
		// TODO implement
		std::cout << "server parsed:" << std::endl;
		std::cout << servers_.back() << std::endl;
		exit (1);
	}
}


void ConfigParser::parseGlobalContext(const std::string &line) {
	std::string lineCopy(line);
	lineCopy.erase(std::remove_if(lineCopy.begin(), lineCopy.end(), utils::ft_isspace), lineCopy.end());
	utils::tolowerString(lineCopy);

	if (lineCopy == SERVER + OPEN_BRACKET) {
		servers_.push_back(ServerInfo());
		context_ = ContextServer;
	} else {
		configError(__func__, line);
	}
}

void ConfigParser::parseServerContext(const std::string &line) {
	std::string lineCopy(line);
	utils::trim(lineCopy);
	utils::tolowerString(lineCopy);

	std::vector<std::string> splitLine = utils::split(lineCopy, WHITESPACE);

	if (splitLine.front() == CLOSE_BRACKET) {
		parseCloseBracketLine(splitLine, line);
	} else if (splitLine.front() == SERVER_NAME) {
		parseServerNameLine(splitLine, line);
	} else if (splitLine.front() == LISTEN) {
		parseListenLine(splitLine, line);
	} else if (splitLine.front() == HOST) {
		parseHostLine(splitLine, line);
	} else if (splitLine.front() == BODY_SIZE) {
		parseBodySizeLine(splitLine, line);
	} else if (splitLine.front() == LOCATION) {
		parseLocationLine(splitLine, line);
	} else {
		configError(__func__, line);
	}
}

std::string ConfigParser::generateServerDefaultName() {
	std::stringstream ss;
	ss << servers_.size();
	std::string serverNum(ss.str());
	return DEFAULT_SERVER_NAME + serverNum;
}

void ConfigParser::parseCloseBracketLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	if (splitLine.size() != 1) {
		configError(__func__, origLine, "close bracket should stand alone");
	}
	if (!servers_.back().hasName())
		servers_.back().setName(generateServerDefaultName());
	context_ = ContextGlobal;
}

void ConfigParser::parseServerNameLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	if (splitLine.size() != 2) {
		configError(__func__, origLine, "missed server name value");
	}
	servers_.back().setName(splitLine.back());
}

void ConfigParser::parseListenLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	const std::string &listenStr = splitLine.back();
	if (splitLine.size() != 2) {
		configError(__func__, origLine, "missed listen value");
	} else if (!utils::isStringDigit(listenStr)) {
		configError(__func__, origLine, "listen value should contain only digits");
	}
	servers_.back().setPort(splitLine.back());
}

void ConfigParser::parseHostLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	if (splitLine.size() != 2) {
		configError(__func__, origLine, "missed host value");
	} else if (!validateIpAddress(splitLine.back())) {
		configError(__func__, origLine, "invalid ip address");
	}
	servers_.back().setIp(splitLine.back());
}

void ConfigParser::parseBodySizeLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	const std::string &maxBodySizeStr = splitLine.back();
	if (splitLine.size() != 2) {
		configError(__func__, origLine, "missed client max body size value");
	} else if (!utils::isStringDigit(maxBodySizeStr)) {
		configError(__func__, origLine, "client_max_body_size value should contain only digits");
	}else if (maxBodySizeStr == ZERO) {
		configError(__func__, origLine, "client_max_body_size value should be more than 0");
	}
	servers_.back().setMaxBodySize(stoi(splitLine.back()));
}

void ConfigParser::parseLocationLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	if (splitLine.size() != 3 || splitLine.back() != OPEN_BRACKET) {
		configError(__func__, origLine, "invalid location line");
	}
	servers_.back().addLocation(splitLine[1]);
	context_ = ContextLocation;
}