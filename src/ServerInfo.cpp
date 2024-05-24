#include "ServerInfo.h"
#include "iostream"

namespace {

std::string defaultIp = "0.0.0.0";
std::string defaultPort = "8080";

} // namespace


/**
 * @brief Print server info error.
 * @param error error description.
 */
void configError(const std::string &error = "") {
	std::cout << "ServerInfo: " << error << std::endl;
}

ServerInfo::ServerInfo():
ip_(),
port_(),
name_(),
clientMaxBodySize_(),
locations_() {
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

void ServerInfo::setIp(const std::string &ip) {
	if (ip_.hasValue() && ip_.value() != defaultIp)
		configError("ip already set");
	ip_ = ip;
}

void ServerInfo::setPort(const std::string &port) {
	if (port_.hasValue() && port_.value() != defaultPort)
		configError("port already set");
	port_ = port;
}

void ServerInfo::setName(const std::string &name) {
	if (name_.hasValue())
		configError("name already set");
	name_ = name;
}

void ServerInfo::setMaxBodySize(size_t maxBodySize) {
	if (clientMaxBodySize_.hasValue())
		configError("client max body size already set");
	clientMaxBodySize_ = maxBodySize;
}

bool ServerInfo::checkServerInfo() {
	return (ip_.hasValue() && port_.hasValue() && clientMaxBodySize_.hasValue());
}

bool ServerInfo::hasName() {
	return name_.hasValue();
}

void ServerInfo::addLocation(const std::string &url) {
	locations_.push_back(LocationInfo(url));
}

LocationInfo *ServerInfo::getLastLocation() {
	if (locations_.empty()) {
		return nullptr;
	}
	return locations_.data() + locations_.size() - 1;
}

std::ostream& operator<< (std::ostream &out, const ServerInfo &serverInfo) {
	out << "Server " << serverInfo.name_.valueOr("NoName") << " info:" << std::endl << //
	"ip: " << serverInfo.ip_.valueOr("undefined") << std::endl << //
	"port: " << serverInfo.port_.valueOr("undefined") << std::endl <<
	"client max body size: " << serverInfo.clientMaxBodySize_.valueOr(0) << std::endl;
	return out;
}