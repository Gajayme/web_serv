#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <array>

#include "Server.hpp"
#include "ServConst.hpp"
#include "Utils.h"


Server::Server():
listener_(),
ip_(),
pfds_(),
clients_() {
	listener_ = getListenerSocket();
	if (listener_ == -1) {
		std::cout << stderr << "error getting listening socket" << std::endl;
		exit(1);
	}
	pfds_.push_back(pollfd());
	pfds_.back().fd = listener_;
	pfds_.back().events = POLLIN; //!< Report ready to read on incoming connection
}

Server::~Server() {
	std::cout << "Destroying server" <<  std::endl;
}

int Server::runServer() {

	utils::colour_out(utils::GREEN, "Starting server");

	while (true) {
		int poll_count = poll(pfds_.data(), pfds_.size(), -1);
		if (poll_count == -1) {
			perror("poll");
			exit(1);
		}
		//! Run through the existing connections looking for data to read
		for (size_t i = 0; i < pfds_.size(); ++i) {
			//! Check if someone's ready to read
			if (pfds_[i].revents & POLLIN) { //!< We got one!!
				//! If listener is ready to read, handle new connection
				if (pfds_[i].fd == listener_) {
					acceptNewConnection();
				}
				//! If not the listener, we're just a regular client
				else {
					handleIncomingRequest(i);
				} //! END handle data from client
			} //! END got ready-to-read from poll()
		} //! END looping through file descriptors
	} //! END for main loop
	return 0;
}

void Server::addToPfds(const int newfd) {
	std::cout << "adding to pfds" << std::endl;
	//! If we don't have room, add more space in the pfds array
	pfds_.push_back(pollfd());
	pfds_.back().fd = newfd;
	pfds_.back().events = POLLIN; //! Check ready-to-read
	clients_[newfd] = Client();
	std::cout << "Added. Clients size = " << clients_.size() << std::endl;
}

void Server::delFromPfds(const size_t idx) {
	//! Copy the one from the end over this one
	clients_.erase(pfds_[idx].fd);
	pfds_[idx] = pfds_.back();
	pfds_.pop_back();
	std::cout << "Deleted. Clients size = " << clients_.size() << std::endl;
}

void Server::acceptNewConnection() {
	int newfd;
	struct sockaddr_storage remoteaddr;
	std::array<char, INET6_ADDRSTRLEN> remoteIP;
	socklen_t addrlen;
	addrlen = sizeof remoteaddr;
	newfd = accept(listener_, (struct sockaddr *) &remoteaddr, &addrlen);
	if (newfd == -1) {
		perror("accept");
	} else {
		addToPfds(newfd);
		std::string clientAddr(inet_ntop(remoteaddr.ss_family, getInAddr((struct sockaddr *) &remoteaddr), remoteIP.data(), INET6_ADDRSTRLEN));
		std::cout << "pollserver: new connection from " << clientAddr << " on socket " << newfd << std::endl;
	}
}

void Server::handleIncomingRequest(const size_t idx) {
	std::array<char, constants::buffSize> buf; //!< Buffer for client data
	ssize_t nbytes = recv(pfds_[idx].fd, buf.data(), buf.size(), 0);
	if (nbytes <= 0) {
		//! Got error or connection closed by client
		if (nbytes == 0) {
			//! Connection closed
			std::cout << "pollserver: socket " << pfds_[idx].fd << " hung up" << std::endl;
		} else {
			perror("recv");
		}
		close(pfds_[idx].fd); //! Bye!
		delFromPfds(idx);
	} else {
		for (auto it = buf.begin(); it != buf.end(); ++it) {
			std::cout << *it;
		}

	}
}

int getListenerSocket() {
	int listener;     //!< Listening socket descriptor
	int yes = 1;      //!< For setsockopt() SO_REUSEADDR, below
	int rv;
	struct addrinfo hints, *ai, *p;
	//! Get us a socket and bind it
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(nullptr, PORT, &hints, &ai)) != 0) {
		std::cout << stderr << "selectserver: " << gai_strerror(rv) << std::endl;
		exit(1);
	}

	for(p = ai; p != nullptr; p = p->ai_next) {
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) {
			continue;
		}
		//! Lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}
		break;
	}
	freeaddrinfo(ai); //!< All done with this
	//! If we got here, it means we didn't get bound
	if (p == nullptr) {
		return -1;
	}
	//! Listen
	if (listen(listener, constants::listeningBacklog) == -1) {
		return -1;
	}

	return listener;
}


void *getInAddr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &((reinterpret_cast<sockaddr_in*>(sa))->sin_addr);
	}
	return &((reinterpret_cast<sockaddr_in6*>(sa))->sin6_addr);
}