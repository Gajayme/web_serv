#pragma once

#include <string>
#include <vector>
#include "ServerInfo.h"
#include <stack>

#include "ServConst.h"

namespace {
	std::string DEFAULT_CONFIG_PATH("/Users/georgii/School_21/web_serv/configs/default.conf");
	std::string DEFAULT_SERVER_NAME("default_");
	std::string SERVER("server");
	std::string SERVER_NAME("server_name");
	std::string LISTEN("listen");
	std::string HOST("host");
	std::string BODY_SIZE("client_max_body_size");
	std::string	OPEN_BRACKET("{");
	std::string	CLOSE_BRACKET("}");
	std::string	WHITESPACE(" ");
	// TODO надо сделать так, чтобы ключи и значения в конфиге отделялись пробелами, а не двоеточиями
	std::string	SEMICOLON(":");
	std::string ZERO("0");
	std::string HASHTAG("#");
}

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
	 * @brief Parse config.
	 * @param path Path to config file
	 */
	void parseConfig(const std::string &path = DEFAULT_CONFIG_PATH);

private:

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
	 */
	void parseGlobalContext(const std::string &line);

	/**
	 * @brief Parse server context line.
	 * @param line Line to parse.
	 */
	void parseServerContext(const std::string &line);

	/**
	 * @brief Generate default name for server.
	 * @return Generated unique name.
	 */
	std::string generateServerDefaultName();


	Context context_; //!< Current parse context.
	std::vector<ServerInfo> servers_; //!< Containers with servers.
};


