#pragma once

#include <string>
#include "Optional.h"
#include "LocationInfo.h"

struct ServerInfo {
	typedef std::vector<LocationInfo> Locations;
	Optional<std::string> ip;  //!< server ip.
	Optional<std::string> port; //!< server port.
	Optional<std::string> name; //!< custom server name.
	Optional<size_t> clientMaxBodySize; //!< server max body size.
	Locations locations; //!< container of locations.
};

/**
 * @brief Cout for serverInfo.
 * @param out standard output stream.
 * @param serverInfo Server info object.
 * @return standard output stream.
 */
std::ostream& operator<< (std::ostream &out, const ServerInfo &serverInfo);
