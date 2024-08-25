#include "ConfigParser.h"
#include "LocationInfo.h"
#include "Optional.h"
#include "GlobalState.h"
#include "ServerState.h"
#include "LocationState.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include "ServerInfo.h"
#include "Utils.h"

namespace {

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


//======
// ConfigParserState
//======

ConfigParserState::ConfigParserState(ConfigParser *configParser):
		configParser_(configParser) {
}

ConfigParserState::~ConfigParserState() {
}


//========
// ConfigParser
//========


ConfigParser::ConfigParser():
		activeState_(StateTypeGlobal),
		states_(),
		servers_() {
	initStates();
}

ConfigParser::~ConfigParser() {}

void ConfigParser::initStates() {
	states_.insert(statesMapValue(StateTypeGlobal, new GlobalState(this)));
	states_.insert(statesMapValue(StateTypeServer, new ServerState(this)));
	states_.insert(statesMapValue(StateTypeLocation, new LocationState(this)));
}

void ConfigParser::setActiveState(const StateType stateType) {
	activeState_ = stateType;
}

const std::vector<ServerInfo> &ConfigParser::getServers() {
	return servers_;
}

void ConfigParser::parseConfig(const std::string &path) {
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

	std::string lineCopy(line);
	utils::trim(lineCopy);
	utils::tolowerString(lineCopy);
//	std::cout << "parse string " << line << std::endl;
	states_[activeState_]->parseLine(line, lineCopy, servers_);
}
