#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <poll.h>

#include "Client.h"

#define PORT "9034"   // Port we're listening on


class Server {
public:
	//! Constructor
	Server();

	//! Destructor
	~Server();

	//! Start webserver
	int runServer();

private:
	//! Forbid copy
	Server(const Server &other);

	//! Forbid assignment
	Server &operator=(const Server &other);

	//! Return a listening socket
	int getListenerSocket(void) const;

	//! Add a new file descriptor to the set
	void addToPfds(int newfd);

	//! Remove fd from container
	void delFromPfds(int idx);

	//! Get sockaddr, IPv4 or IPv6:
	void *getInAddr(struct sockaddr *sa);

	//! Accept new incoming connection;
	void acceptNewConnection();

	//! Get data from incoming connection
	void handleIncomingRequest(size_t idx);

	//! Server IP address
	int ip_;
	//! Listening socket descriptor
	int listener_;
	//! Number of connections allowed on the incoming queue
	int listeningBacklog_;
	//! Fds of current connections
	std::vector<struct pollfd> pfds_;
};
