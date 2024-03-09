#pragma once

#include <string>
#include <vector>
#include "ServerInfo.h"
#include <stack>
#include "ServConst.h"

namespace {
	std::string DEFAULT_CONFIG_PATH("/Users/georgii/School_21/web_serv/configs/default.conf");
	std::string SERVER("server");
	std::string NAME("server_name");
	std::string LISTEN("listen");
	std::string HOST("host");
	std::string BODY_SIZE("client_max_body_size");
	std::string	OPENBRACKET("{");
	std::string	CLOSEBRACKET("}");
	std::string	WHITESPACE(" ");
	std::string	SEMICOLON(":");
}

class ConfigParser {

public:
	ConfigParser();
	~ConfigParser();

	void parseConfig(const std::string &path = DEFAULT_CONFIG_PATH);

private:


	enum ConfigScope {
		ConfigScopeGlobal, // Outside server section
		ConfigScopeServer, // Inside server section
		ConfigScopeLocation, // Inside location section
	};

	ConfigParser(const ConfigParser &other);
	ConfigParser &operator=(const ConfigParser &other);
	void parseLine(std::string &line);
	bool isSeverScope(const std::vector<std::string> &toParse);

	ConfigScope configScope_;
	std::vector<ServerInfo> servers_;
	std::stack<std::string> brackets_;
};


