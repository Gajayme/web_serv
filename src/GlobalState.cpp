#include "iostream"

#include "GlobalState.h"
#include "Utils.h"

GlobalState::GlobalState(ConfigParser *configParser):
ConfigParserState(configParser) {
}

void GlobalState::parseLine(const std::string &line, std::string &lineCopy, std::vector<ServerInfo> &servers) {
	lineCopy.erase(std::remove_if(lineCopy.begin(), lineCopy.end(), utils::ft_isspace), lineCopy.end());

	if (lineCopy == configTokens::SERVER + configTokens::OPEN_BRACKET) {
		servers.push_back(ServerInfo());
		configParser_->setActiveState(ConfigParser::StateTypeServer);
	} else {
		utils::configError(__func__, line);
	}
}