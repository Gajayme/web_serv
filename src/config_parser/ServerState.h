#pragma once

#include "ConfigParser.h"


class ServerState: public ConfigParserState {

public:
	/**
	 * @brief Constructor.
	 * @param configParser execution context
	 */
	explicit ServerState(ConfigParser *configParser);

	/**
	 * @brief Parse config line of server scope.
	 * @param line orig config line to log errors.
	 * @param lineCopy copy of orig line. To parse.
	 * @param servers container with servers to store parsed info to.
	 */
	virtual void parseLine(const std::string &line, std::string &lineCopy, std::vector<ServerInfo> &servers);

private:

	/**
	 * @brief Parse line that starts with SERVER_NAME token.
	 * @param splitLine split line that started with SERVER_NAME token.
	 * @param origLine unformat line in case of an error.
	 * @param servers Servers container to store parsed info to.
	 */
	void parseServerNameLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, std::vector<ServerInfo> &servers);

	/**
	 * @brief Parse line that starts with LISTEN token.
	 * @param splitLine split line that started with LISTEN token.
	 * @param origLine unformat line in case of an error.
	 * @param servers Servers container to store parsed info to.
	 */
	void parseListenLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, std::vector<ServerInfo> &servers);

	/**
	 * @brief Parse line that starts with HOST token.
	 * @param splitLine split line that started with HOST token.
	 * @param origLine unformat line in case of an error.
	 * @param servers Servers container to store parsed info to.
	 */
	void parseHostLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, std::vector<ServerInfo> &servers);

	/**
	 * @brief Parse line that starts with BODY_SIZE token.
	 * @param splitLine split line that started with BODY_SIZE token.
	 * @param origLine unformat line in case of an error.
	 * @param servers Servers container to store parsed info to.
	 */
	void parseBodySizeLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, std::vector<ServerInfo> &servers);

	/**
	 * @brief Parse line that starts with LOCATION token.
	 * @param splitLine split line that started with LOCATION token.
	 * @param origLine unformat line in case of an error.
	 * @param servers Servers container to store parsed info to.
	 */
	void parseLocationLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, std::vector<ServerInfo> &servers);

	/**
	 * @brief Parse line that starts with CLOSE_BRACKET token.
	 * @param splitLine split line that started with CLOSE_BRACKETS token.
	 * @param origLine unformat line in case of an error.
	 * @param servers Servers container to store parsed info to.
	 */
	void parseCloseBracketLine(const ConfigParser::SplitLine &splitLine, const std::string &origLine, std::vector<ServerInfo> &servers);

	/**
	 * @brief Generate default name for server.
	 * @param serversLength Amount of already parsed servers
	 * @return Generated unique name.
	 */
	std::string generateServerDefaultName(size_t serversLength);

	/**
	 * @brief Check that parsed server has all needed data.
	 * @param serverInfo Parsed server info to check.
	 */
	void checkServerInfo(const ServerInfo &serverInfo);

};
