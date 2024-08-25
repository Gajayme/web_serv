#include <iostream>
#include <arpa/inet.h>
#include <sstream>

#include "ServerState.h"
#include "Utils.h"


namespace {

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

	template<typename T>
	void setServerInfoValue(Optional<T> &optional, T value, const std::string &line) {
		if (optional.hasValue()) {
			utils::configError(__func__, line, "Value already set");
		}
		optional = value;
	}
}

ServerState::ServerState(ConfigParser *configParser):
		ConfigParserState(configParser) {
}

void ServerState::parseLine(const std::string &line, std::string &lineCopy, std::vector<ServerInfo> &servers) {
	std::vector<std::string> splitLine = utils::split(lineCopy, configTokens::WHITESPACE);

	// TODO стоит подумать над диспетчеризацией методов
	if (splitLine.front() == configTokens::CLOSE_BRACKET) {
		parseCloseBracketLine(splitLine, line, servers);
	} else if (splitLine.front() == configTokens::SERVER_NAME) {
		parseServerNameLine(splitLine, line, servers);
	} else if (splitLine.front() == configTokens::LISTEN) {
		parseListenLine(splitLine, line, servers);
	} else if (splitLine.front() == configTokens::HOST) {
		parseHostLine(splitLine, line, servers);
	} else if (splitLine.front() == configTokens::BODY_SIZE) {
		parseBodySizeLine(splitLine, line, servers);
	} else if (splitLine.front() == configTokens::LOCATION) {
		parseLocationLine(splitLine, line, servers);
	} else {
		utils::configError(__func__, line);
	}
}

void ServerState::parseServerNameLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine,  std::vector<ServerInfo> &servers) {
	if (splitLine.size() != 2) {
		utils::configError(__func__, origLine, "missed server name value");
	}
	setServerInfoValue(servers.back().name, splitLine.back(), origLine);
}

void ServerState::parseListenLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine,  std::vector<ServerInfo> &servers) {
	const std::string &listenStr = splitLine.back();
	if (splitLine.size() != 2) {
		utils::configError(__func__, origLine, "missed listen value");
	} else if (!utils::isStringDigit(listenStr)) {
		utils::configError(__func__, origLine, "listen value should contain only digits");
	}
	setServerInfoValue(servers.back().port, splitLine.back(), origLine);
}

void ServerState::parseHostLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine,  std::vector<ServerInfo> &servers) {
	if (splitLine.size() != 2) {
		utils::configError(__func__, origLine, "missed host value");
	} else if (!validateIpAddress(splitLine.back())) {
		utils::configError(__func__, origLine, "invalid ip address");
	}
	setServerInfoValue(servers.back().ip, splitLine.back(), origLine);
}

void ServerState::parseBodySizeLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine,  std::vector<ServerInfo> &servers) {
	const std::string &maxBodySizeStr = splitLine.back();
	if (splitLine.size() != 2) {
		utils::configError(__func__, origLine, "missed client max body size value");
	} else if (!utils::isStringDigit(maxBodySizeStr)) {
		utils::configError(__func__, origLine, "client_max_body_size value should contain only digits");
	}else if (maxBodySizeStr == configTokens::ZERO) {
		utils::configError(__func__, origLine, "client_max_body_size value should be more than 0");
	}
	size_t clientMaxBodySize = static_cast<size_t>(stoi(splitLine.back()));
	setServerInfoValue(servers.back().clientMaxBodySize, clientMaxBodySize, origLine);
}

void ServerState::parseLocationLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine,  std::vector<ServerInfo> &servers) {
	if (splitLine.size() != 3 || splitLine.back() != configTokens::OPEN_BRACKET) {
		utils::configError(__func__, origLine, "invalid location line");
	}

	LocationInfo locationInfo;
	locationInfo.url_ = splitLine[1];
	servers.back().locations.push_back(locationInfo);
	configParser_->setActiveState(ConfigParser::StateTypeLocation);
}


void ServerState::parseCloseBracketLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, std::vector<ServerInfo> &servers) {
	if (splitLine.size() != 1) {
		utils::configError(__func__, origLine, "close bracket should stand alone");
	}
	configParser_->setActiveState(ConfigParser::StateTypeGlobal);
	if (!servers.back().name.hasValue()) {
		servers.back().name = generateServerDefaultName(servers.size());
	}
	checkServerInfo(servers.back());
}


std::string ServerState::generateServerDefaultName(const size_t serversLength) {
	std::stringstream ss;
	ss << serversLength;
	std::string serverNum(ss.str());
	return configTokens::DEFAULT_SERVER_NAME + serverNum;
}

void ServerState::checkServerInfo(const ServerInfo &serverInfo) {
	if (!serverInfo.ip.hasValue() || !serverInfo.port.hasValue() || !serverInfo.name.hasValue() ||
		!serverInfo.clientMaxBodySize.hasValue()) {
		utils::configError(__func__, "server is not filled correctly");
	}
}