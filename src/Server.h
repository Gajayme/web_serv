#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <poll.h>

#include "Client.h"

#define PORT "9034"   // Port we're listening on.

class Server {
public:

	/**
	 * @brief Constructor.
	 */
	Server();

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
	int ip_;
	//! Listening socket descriptor
	int listener_;
	//! Fds of current connections
	std::vector<struct pollfd> pfds_;
	//! Connected clients
	std::map<int, Client> clients_;
};


/**
 * @brief Create listening socket.
 * @return Listening socket fd.
 */
int getListenerSocket();

/**
 * @brief Get addr of incoming connection.
 * @param sa struct to hold whatever ip4/ip6 connection addr
 */
void *getInAddr(struct sockaddr *sa);