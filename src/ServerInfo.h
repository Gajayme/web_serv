#pragma once

#include <string>

class ServerInfo {
public:
	ServerInfo();
	~ServerInfo();
	ServerInfo(const ServerInfo &other);
	ServerInfo &operator=(const ServerInfo &other);

	private:

	std::string ip_;
	std::string port_;
	std::string name_;
	size_t clientMaxBodySize_;
};
