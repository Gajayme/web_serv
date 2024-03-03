#pragma once

#include <string>

class ServerInfo {
public:
	//const std::string &ip, const std::string &port, const std::string &name, int client_max_body_size
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
