#pragma once

#include <string>
#include <vector>
#include "ServerInfo.h"


class ConfigParser {

public:
	ConfigParser();
	~ConfigParser();

	void parseConfig(const std::string &path);

private:
	ConfigParser(const ConfigParser &other);
	ConfigParser &operator=(const ConfigParser &other);
	void parseLine(std::string &line);

	std::vector<ServerInfo> servers_;
};


