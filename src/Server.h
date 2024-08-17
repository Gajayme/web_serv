#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <poll.h>

#include "Client.h"
#include "ServerInfo.h"


class Server {
public:

	/**
	 * @brief Constructor.
	 * @param serverInfo info with params to build server
	 */
	explicit Server(const ServerInfo &serverInfo);

	/**
	 * @brief Destructor.
	 */
	~Server();

	/**
	 * @brief Start server.
	 */
	int runServer();

private:
	/**
	 * @brief Forbid copy.
	 * @param other Another server object
	 */
	Server(const Server &other);

	/**
	 * @brief Forbid assignment.
	 * @param other Another server object
	 */
	Server &operator=(const Server &other);

	/**
	 * @brief Add new connection to connections container.
	 * @param newfd new connection fd
	 */
	void addToPfds(int newfd);

	/**
	 * @brief Remove connection from connection container.
	 * @param newfd connection to remove
	 */
	void delFromPfds(size_t idx);

	/**
	 * @brief Accept incoming connection.
	 */
	void acceptNewConnection();

	/**
	 * @brief Handle data from incoming connection.
	 * @param idx index of connection to get data from.
	 */
	void handleIncomingRequest(size_t idx);

	//! Server IP address
	std::string ip_;
	//! Server PORT address
	std::string port_;

	//! Listening socket descriptor
	int listener_;
	//! Fds of current connections
	std::vector<struct pollfd> pfds_;
	//! Connected clients
	std::map<int, Client> clients_;
};


/**
 * @brief Create listening socket.
 * @param port port tot listen on.
 * @return Listening socket fd.
 */
int getListenerSocket(const char* port);

/**
 * @brief Get addr of incoming connection.
 * @param sa struct to hold whatever ip4/ip6 connection addr
 */
void *getInAddr(struct sockaddr *sa);