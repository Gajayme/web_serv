#pragma once

#include "ConfigParser.h"

class LocationState: public ConfigParserState {

public:
	/**
	 * @brief Constructor.
	 * @param configParser execution context
	 */
	explicit LocationState(ConfigParser *configParser);

	/**
	 * @brief Parse config line of global scope.
	 * @param line orig config line to log errors.
	 * @param lineCopy copy of orig line. To parse.
	 * @param servers container with servers to store parsed info to.
	 */

	virtual void parseLine(const std::string &line, std::string &lineCopy, std::vector<ServerInfo> &servers);

private:

	/**
	 * @brief Parse line that starts with AUTONDEX token.
	 * @param splitLine split line that started with AUTONDEX token.
	 * @param origLine unformatted line in case of an error.
	 * @param location location to set AUTONDEX for.
	 */
	void parseAutoindexLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location);

	/**
	 * @brief Parse line that starts with METHODS token.
	 * @param splitLine split line that started with METHODS token.
	 * @param origLine unformatted line in case of an error.
	 * @param location location to set METHODS for.
	 */
	void parseMethodsLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location);

	/**
	 * @brief Parse line that starts with ROOT token.
	 * @param splitLine split line that started with ROOT token.
	 * @param origLine unformatted line in case of an error.
	 * @param location location to set ROOT for.
	 */
	void parseRootLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location);

	/**
	 * @brief Parse line that starts with INDEX token.
	 * @param splitLine split line that started with INDEX token.
	 * @param origLine unformatted line in case of an error.
	 * @param location location to set INDEX for.
	 */
	void parseIndexLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, LocationInfo &location);

	/**
	 * @brief Parse line that starts with CLOSE_BRACKET token.
	 * @param splitLine split line that started with CLOSE_BRACKETS token.
	 * @param origLine unformatted line in case of an error.
	 */
	void parseCloseBracketLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine);

};
