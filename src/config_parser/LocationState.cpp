#include "iostream"

#include "LocationState.h"
#include "../Utils.h"

LocationState::LocationState(ConfigParser *configParser):
ConfigParserState(configParser) {
}

void LocationState::parseLine(const std::string &line, std::string &lineCopy, std::vector<ServerInfo> &servers) {
	std::vector<std::string> splitLine = utils::split(lineCopy, configTokens::WHITESPACE);

	ServerInfo &lastServer = servers.back();
	ServerInfo::Locations &locations = lastServer.locations;
	if (locations.empty()) {
		utils::configError(__func__, line, "no location to parse location data for");
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
		utils::configError(__func__, line);
	}
}

void LocationState::parseAutoindexLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() != 2) {
		utils::configError(__func__, origLine, "invalid autoindex line");
	} else if (splitLine.back() == configTokens::ON) {
		location.isListingOn_ = true;
	} else if (splitLine.back() == configTokens::OFF) {
		location.isListingOn_ = false;
	} else {
		utils::configError(__func__, origLine, "autoindex value should be on/off");
	}
}

void LocationState::parseMethodsLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() < 2) {
		utils::configError(__func__, origLine, "invalid  line");
	}

	for (ConfigParser::SplitLine::const_iterator cit = splitLine.cbegin() + 1; cit != splitLine.cend(); ++cit) {
		if (*cit == configTokens::GET) {
			SetHttpMethodOn(location, constants::HttpMethodGet);
		} else if(*cit == configTokens::POST) {
			SetHttpMethodOn(location, constants::HttpMethodPost);
		} else if (*cit == configTokens::DELETE) {
			SetHttpMethodOn(location, constants::HttpMethodDelete);
		} else {
			utils::configError(__func__, origLine, "unsupported Http method");
		}
	}
}

void LocationState::parseRootLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() != 2) {
		utils::configError(__func__, origLine, "invalid  line");
	}
	location.root_ = splitLine.back();
}

void LocationState::parseIndexLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location) {
	if (splitLine.size() < 2) {
		utils::configError(__func__, origLine, "invalid  line");
	}
	location.indexes_ = LocationInfo::Indexes(splitLine.begin() + 1, splitLine.end());
}


void LocationState::parseCloseBracketLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine) {
	if (splitLine.size() != 1) {
		utils::configError(__func__, origLine, "close bracket should stand alone");
	}
	configParser_->setActiveState(ConfigParser::StateTypeServer);
}
