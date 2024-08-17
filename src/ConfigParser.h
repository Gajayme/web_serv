#pragma once

#include <string>
#include <vector>
#include "ServerInfo.h"
#include "ServConst.h"

class ConfigParser {

public:
	/**
	 * @brief Constructor.
	 */
	ConfigParser();

	/**
	 * @brief Destructor.
	 */
	~ConfigParser();

	/**
  	 * @brief Get all parsed servers.
  	 * @return all parsed servers.
  	 */
	const std::vector<ServerInfo> &getServers();

	/**
	 * @brief Parse config.
	 * @param path Path to config file.
	 */
	void parseConfig(const std::string &path = configTokens::DEFAULT_CONFIG_PATH);

private:

	typedef std::vector<std::string> SplitLine;

	enum Context {
		ContextGlobal, // Outside server section
		ContextServer, // Inside server section
		ContextLocation, // Inside location section
	};

	/**
	 * @brief Forbid copy.
	 * @param other Config parser object.
	 */
	ConfigParser(const ConfigParser &other);

	/**
	 * @brief Forbid assignment.
	 * @param other Config parser object.
	 */
	ConfigParser &operator=(const ConfigParser &other);

	/**
	 * @brief Parse config line.
	 * @param line Config line to parse.
	 */
	void parseLine(std::string &line);

	/**
	 * @brief Parse global context line.
	 * @param line Line to parse.
	 * @param lineCopy Line to parse copy.
	 */
	void parseGlobalContext(const std::string &line, std::string &lineCopy);

	/**
	 * @brief Parse server context line.
	 * @param line Line to parse.
	 * @param lineCopy Line to parse copy.
	 */
	void parseServerContext(const std::string &line, std::string &lineCopy);

	/**
	 * @brief Parse location context line.
	 * @param line Line to parse.
	 * @param lineCopy Line to parse copy.
	 */
	void parseLocationContext(const std::string &line, std::string &lineCopy);

	/**
	 * @brief Generate default name for server.
	 * @return Generated unique name.
	 */
	std::string generateServerDefaultName();

	/**
	 * @brief Parse line that starts with CLOSE_BRACKET token.
	 * @param splitLine split line that started with CLOSE_BRACKETS token.
	 * @param origLine unformat line in case of an error.
	 */
	void parseCloseBracketLine(const SplitLine &splitLine, const std::string &origLine);

	/**
	 * @brief Parse line that starts with SERVER_NAME token.
	 * @param splitLine split line that started with SERVER_NAME token.
	 * @param origLine unformat line in case of an error.
	 */
	void parseServerNameLine(const SplitLine &splitLine, const std::string &origLine);

	/**
	 * @brief Parse line that starts with LISTEN token.
	 * @param splitLine split line that started with LISTEN token.
	 * @param origLine unformat line in case of an error.
	 */
	void parseListenLine(const SplitLine &splitLine, const std::string &origLine);

	/**
	 * @brief Parse line that starts with HOST token.
	 * @param splitLine split line that started with HOST token.
	 * @param origLine unformat line in case of an error.
	 */
	void parseHostLine(const SplitLine &splitLine, const std::string &origLine);

	/**
	 * @brief Parse line that starts with BODY_SIZE token.
	 * @param splitLine split line that started with BODY_SIZE token.
	 * @param origLine unformat line in case of an error.
	 */
	void parseBodySizeLine(const SplitLine &splitLine, const std::string &origLine);

	/**
	 * @brief Parse line that starts with LOCATION token.
	 * @param splitLine split line that started with LOCATION token.
	 * @param origLine unformat line in case of an error.
	 */
	void parseLocationLine(const SplitLine &splitLine, const std::string &origLine);

	/**
	 * @brief Parse line that starts with AUTONDEX token.
	 * @param splitLine split line that started with AUTONDEX token.
	 * @param origLine unformat line in case of an error.
	 * @param location location to set AUTONDEX for.
	 */
	void parseAutoindexLine(const SplitLine &splitLine, const std::string &origLine, LocationInfo &location);

	/**
	 * @brief Parse line that starts with METHODS token.
	 * @param splitLine split line that started with METHODS token.
	 * @param origLine unformat line in case of an error.
	 * @param location location to set METHODS for.
	 */
	void parseMethodsLine(const SplitLine &splitLine, const std::string &origLine, LocationInfo &location);

	/**
	 * @brief Parse line that starts with ROOT token.
	 * @param splitLine split line that started with ROOT token.
	 * @param origLine unformat line in case of an error.
	 * @param location location to set ROOT for.
	 */
	void parseRootLine(const SplitLine &splitLine, const std::string &origLine, LocationInfo &location);


	/**
	 * @brief Parse line that starts with INDEX token.
	 * @param splitLine split line that started with INDEX token.
	 * @param origLine unformat line in case of an error.
	 * @param location location to set INDEX for.
	 */
	void parseIndexLine(const SplitLine &splitLine, const std::string &origLine, LocationInfo &location);

	Context context_; //!< Current parse context.
	std::vector<ServerInfo> servers_; //!< Containers with servers.
};


