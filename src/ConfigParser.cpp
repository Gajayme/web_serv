#include "ConfigParser.h"
#include "LocationInfo.h"

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
	const size_t hashtagPos = s.find_first_of(configTokens::HASHTAG);
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

//	for (size_t i = 0; i < servers_.size(); ++i) {
//		std::cout << servers_[i] << std::endl;
//	}
}

void ConfigParser::parseLine(std::string &line) {
	removeComment(line);
	utils::trim(line);
	if (line.empty()) {
		return;
	}

	std::string lineCopy(line);
	utils::trim(lineCopy);
	utils::tolowerString(lineCopy);

	if (context_ == ContextGlobal) {
		parseGlobalContext(line, lineCopy);
	} else if (context_ == ContextServer) {
		parseServerContext(line, lineCopy);
	} else if (context_ == ContextLocation) {
		parseLocationContext(line, lineCopy);
	}
}


void ConfigParser::parseGlobalContext(const std::string &line, std::string &lineCopy) {
	lineCopy.erase(std::remove_if(lineCopy.begin(), lineCopy.end(), utils::ft_isspace), lineCopy.end());

	if (lineCopy == configTokens::SERVER + configTokens::OPEN_BRACKET) {
		servers_.push_back(ServerInfo());
		context_ = ContextServer;
	} else {
		configError(__func__, line);
	}
}

void ConfigParser::parseServerContext(const std::string &line, std::string &lineCopy) {
	std::vector<std::string> splitLine = utils::split(lineCopy, configTokens::WHITESPACE);

	// TODO стоит подумать над диспетчеризацией методов
	if (splitLine.front() == configTokens::CLOSE_BRACKET) {
		parseCloseBracketLine(splitLine, line);
	} else if (splitLine.front() == configTokens::SERVER_NAME) {
		parseServerNameLine(splitLine, line);
	} else if (splitLine.front() == configTokens::LISTEN) {
		parseListenLine(splitLine, line);
	} else if (splitLine.front() == configTokens::HOST) {
		parseHostLine(splitLine, line);
	} else if (splitLine.front() == configTokens::BODY_SIZE) {
		parseBodySizeLine(splitLine, line);
	} else if (splitLine.front() == configTokens::LOCATION) {
		parseLocationLine(splitLine, line);
	} else {
		configError(__func__, line);
	}
}

void ConfigParser::parseLocationContext(const std::string &line, std::string &lineCopy) {
	std::vector<std::string> splitLine = utils::split(lineCopy, configTokens::WHITESPACE);

	ServerInfo &lastServer = servers_.back();
	ServerInfo::Locations &locations = lastServer.getLocations();
	if (locations.empty()) {
		configError(__func__, line, "no location to parse location data for");
	} else if (splitLine.front() == configTokens::AUTONDEX) {
		parseAutoindexLine(splitLine, line, locations.back());
	} else if (splitLine.front() == configTokens::METHODS) {
		parseMethodsLine(splitLine, line, locations.back());
	} else if (splitLine.front() == configTokens::ROOT)
		parseRootLine(splitLine, line, locations.back());
	else if (splitLine.front() == configTokens::INDEX) {
		parseIndexLine(splitLine, line, locations.back());
	} else if (splitLine.front() == configTokens::CLOSE_BRACKET) {
		parseCloseBracketLine(splitLine, line);
	} else {
		configError(__func__, line);
	}
}

std::string ConfigParser::generateServerDefaultName() {
	std::stringstream ss;
	ss << servers_.size();
	std::string serverNum(ss.str());
	return configTokens::DEFAULT_SERVER_NAME + serverNum;
}

void ConfigParser::parseCloseBracketLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	if (splitLine.size() != 1) {
		configError(__func__, origLine, "close bracket should stand alone");
	}
	switch (context_) {
		case ContextServer:
			context_ = ContextGlobal;
			if (!servers_.back().hasName()) {
				servers_.back().setName(generateServerDefaultName());
			}
			break;

		case ContextLocation:
			context_ = ContextServer;
			break;

		default:
			configError(__func__, origLine, " invalid config state");
	}
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
	}else if (maxBodySizeStr == configTokens::ZERO) {
		configError(__func__, origLine, "client_max_body_size value should be more than 0");
	}
	servers_.back().setMaxBodySize(stoi(splitLine.back()));
}

void ConfigParser::parseLocationLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	if (splitLine.size() != 3 || splitLine.back() != configTokens::OPEN_BRACKET) {
		configError(__func__, origLine, "invalid location line");
	}
	servers_.back().addLocation(splitLine[1]);
	context_ = ContextLocation;
}

void ConfigParser::parseAutoindexLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() != 2) {
		configError(__func__, origLine, "invalid autoindex line");
	} else if (splitLine.back() == configTokens::ON) {
		location.setListing(true);
	} else if (splitLine.back() == configTokens::OFF) {
		location.setListing(false);
	} else {
		configError(__func__, origLine, "autoindex value should be on/off");
	}
}

void ConfigParser::parseMethodsLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() < 2) {
		configError(__func__, origLine, "invalid  line");
	}

	for (SplitLine::const_iterator cit = splitLine.cbegin() + 1; cit != splitLine.cend(); ++cit) {
		if (*cit == configTokens::GET) {
			location.setHttpMethodOn(constants::HttpMethodGet);
		} else if(*cit == configTokens::POST) {
			location.setHttpMethodOn(constants::HttpMethodPost);
		} else if (*cit == configTokens::DELETE) {
			location.setHttpMethodOn(constants::HttpMethodDelete);
		} else {
			configError(__func__, origLine, "unsupported Http method");
		}
	}
}

void ConfigParser::parseRootLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() != 2) {
		configError(__func__, origLine, "invalid  line");
	}
	location.setRoot(splitLine.back());
}

void ConfigParser::parseIndexLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() < 2) {
		configError(__func__, origLine, "invalid  line");
	}
	location.setIndexes(LocationInfo::Indexes(splitLine.begin() + 1, splitLine.end()));
}
