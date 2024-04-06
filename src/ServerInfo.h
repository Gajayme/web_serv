#pragma once

#include <string>
#include "Optional.h"


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
	void setIp(std::string ip);

	/**
	 * @brief Set server port.
	 * @param port port.
	 */
	void setPort(std::string port);

	/**
	 * @brief Set server name.
	 * @param name name.
	 */
	void setName(std::string name);

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

	private:

	Optional<std::string> ip_;  //!< server ip
	Optional<std::string> port_; //!< server port
	Optional<std::string> name_; //!< server name
	Optional<size_t> clientMaxBodySize_; //!< server max body size
};
