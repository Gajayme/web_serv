#pragma once

#include "ConfigParser.h"


class GlobalState: public ConfigParserState {

public:
	/**
	 * @brief Constructor.
	 * @param configParser execution context
	 */
	explicit GlobalState(ConfigParser *configParser);

	/**
	 * @brief Parse config line of location scope.
	 * @param line orig config line to log errors.
	 * @param lineCopy copy of orig line. To parse.
	 * @param servers container with servers to store parsed info to.
	 */
	virtual void parseLine(const std::string &line, std::string &lineCopy, std::vector<ServerInfo> &servers);

};
