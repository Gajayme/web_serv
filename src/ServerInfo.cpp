#include "ServerInfo.h"

ServerInfo::ServerInfo() {
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
	return  *this;
}