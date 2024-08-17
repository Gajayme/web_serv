#include "ServerInfo.h"
#include "iostream"

std::ostream& operator<< (std::ostream &out, const ServerInfo &serverInfo) {
	out << "Server " << serverInfo.name.valueOr("NoName") << " info:" << std::endl << //
	"ip: " << serverInfo.ip.valueOr("undefined") << std::endl << //
	"port: " << serverInfo.port.valueOr("undefined") << std::endl <<
	"client max body size: " << serverInfo.clientMaxBodySize.valueOr(0) << std::endl << std::endl;

	for (size_t i = 0; i < serverInfo.locations.size(); ++i) {
		out << serverInfo.locations[i] << std::endl;
	}
	return out;
}
