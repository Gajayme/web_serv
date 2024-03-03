#include "ServerInfo.h"

//const std::string &ip, const std::string &port, const std::string &name, int maxBodySize
ServerInfo::ServerInfo() {
//ip_(ip),
//port_(port),
//name_(name),
//clientMaxBodySize_(maxBodySize)

}

ServerInfo::~ServerInfo() {}

ServerInfo::ServerInfo(const ServerInfo &other):
ip_(other.ip_),
port_(other.port_),
name_(other.name_),
clientMaxBodySize_(other.clientMaxBodySize_) {
};

ServerInfo &ServerInfo::operator=(const ServerInfo &other) {
	if (this == &other) {
		return *this;
	}
	ip_ = other.ip_;
	port_ = other.port_;
	name_ = other.name_;
	clientMaxBodySize_ = other.clientMaxBodySize_;
}