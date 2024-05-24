#pragma once

#include <string>
#include "Optional.h"
#include "LocationInfo.h"


class ServerInfo {
public:
	ServerInfo();
	~ServerInfo();
	ServerInfo(const ServerInfo &other);
	ServerInfo &operator=(const ServerInfo &other);

	/**
	 * @brief Set server ip.
	 * @param ip ip.
	 */
	void setIp(const std::string &ip);

	/**
	 * @brief Set server port.
	 * @param port port.
	 */
	void setPort(const std::string &port);

	/**
	 * @brief Set server name.
	 * @param name name.
	 */
	void setName(const std::string &name);

	/**
	 * @brief Set maximum body size of client's request.
	 * @param name max size of client's requests body.
	 */
	void setMaxBodySize(size_t maxBodySize);

	/**
 	 * @brief Check whether server info is full.
 	 * @return true if info is full, false otherwise.
 	 */
	bool checkServerInfo();

	/**
	 * @brief Check whether servers' name set.
	 * @return true if name is set, false otherwise.
	 */
	bool hasName();

	/**
	 * @brief Add location to location's container
	 * @param url url of adding location.
	 */
	void addLocation(const std::string &url);

	/**
	 * @brief Return last added location.
	 * @return Last added location if exists, else nullptr
	 */
	LocationInfo *getLastLocation();

	/**
	 * @brief Overloading of cout operator.
	 * @param out standard output stream.
	 * @param serverInfo Server info object.
	 * @return standard output stream.
	 */
	friend std::ostream& operator<< (std::ostream &out, const ServerInfo &serverInfo);

	private:

	Optional<std::string> ip_;  //!< server ip.
	Optional<std::string> port_; //!< server port.
	Optional<std::string> name_; //!< custom server name.
	Optional<size_t> clientMaxBodySize_; //!< server max body size.
	std::vector<LocationInfo> locations_; //!< container of locations.
};
