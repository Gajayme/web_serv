#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#include "Server.hpp"
#include "ServConst.hpp"
#include "array"

// TODO нужен конструктор копирования и присваивания
Server::Server():
listeningBacklog_(constants::listeningBacklog),
fdCount_(0),
listener_(),
ip_(),
//TODO лучше запушить первый элемент в теле конструктора
pfds_(1) {
	listener_ = getListenerSocket();
	if (listener_ == -1) {
		std::cout << stderr << "error getting listening socket" << std::endl;
		exit(1);
	}
	pfds_[0].fd = listener_;
	pfds_[0].events = POLLIN; //!< Report ready to read on incoming connection
	//TODO можно избавится от этого использую размер вектора
	fdCount_ = 1; //!< For the listener
}

Server::~Server() {
	std::cout << "Destroyed" <<  std::endl;
}

int Server::runServer() {

	std::cout << "Running server"<<  std::endl;

	int newfd;        //!< Newly accept()ed socket descriptor
	struct sockaddr_storage remoteaddr; //!< Client address
	std::array<char, constants::buffSize> buf; //!< Buffer for client data
	std::array<char, INET6_ADDRSTRLEN> remoteIP;
	socklen_t addrlen;

	while (true) {
		std::cout << "pfds_ size = " << pfds_.size() << " " << fdCount_ << std::endl;
		int poll_count = poll(pfds_.data(), fdCount_, -1);
		if (poll_count == -1) {
			perror("poll");
			exit(1);
		}
		//! Run through the existing connections looking for data to read
		for (size_t i = 0; i < fdCount_; ++i) {
			//! Check if someone's ready to read
			if (pfds_[i].revents & POLLIN) { //!< We got one!!
				//! If listener is ready to read, handle new connection
				if (pfds_[i].fd == listener_) {
					addrlen = sizeof remoteaddr;
					std::cout << "before accept" << std::endl;
					newfd = accept(listener_, (struct sockaddr *) &remoteaddr, &addrlen);
					std::cout << "after accept" << std::endl;
					if (newfd == -1) {
						perror("accept");
					} else {
						addToPfds(newfd);
						std::cout << "pollserver: new connection from " <<
								  inet_ntop(remoteaddr.ss_family, getInAddr((struct sockaddr *) &remoteaddr),
											remoteIP.data(), INET6_ADDRSTRLEN) <<
								  "on socket " << newfd << std::endl;
					}
				} else {
					//! If not the listener, we're just a regular client
					int nbytes = recv(pfds_[i].fd, buf.data(), constants::buffSize, 0);
					if (nbytes <= 0) {
						//! Got error or connection closed by client
						if (nbytes == 0) {
							//! Connection closed
							printf("pollserver: socket %d hung up\n", pfds_[i].fd);
							std::cout << "pollserver: socket " << pfds_[i].fd << " hung up" << std::endl;
						} else {
							perror("recv");
						}
						close(pfds_[i].fd); //! Bye!
						delFromPfds(i);
					} else {
						//! We got some good data from a client
						for (int j = 0; j < pfds_.size(); ++j) {
							//! Send to everyone!
							int dest_fd = pfds_[j].fd;
							//! Except the listener and ourselves
							if (dest_fd != listener_ && dest_fd != pfds_[i].fd) {
								if (send(dest_fd, buf.data(), nbytes, 0) == -1) {
									perror("send");
								}
							}
						}
					}
				} //! END handle data from client
			} //! END got ready-to-read from poll()
		} //! END looping through file descriptors
	} //! END for main loop
	return 0;
}

int Server::getListenerSocket(void) const {
	std::cout << "Getting listener socket" << std::endl;

	int listener;     //!< Listening socket descriptor
	int yes = 1;      //!< For setsockopt() SO_REUSEADDR, below
	int rv;
	struct addrinfo hints, *ai, *p;
	//! Get us a socket and bind it
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
		std::cout << stderr << "selectserver: " << gai_strerror(rv) << std::endl;
		exit(1);
	}

	for(p = ai; p != NULL; p = p->ai_next) {
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
	if (p == NULL) {
		return -1;
	}
	//! Listen
	if (listen(listener, listeningBacklog_) == -1) {
		return -1;
	}

	return listener;
}

void Server::addToPfds(const int newfd) {
	//! If we don't have room, add more space in the pfds array
	pfds_.push_back(pollfd());
	pfds_.back().fd = newfd;
	pfds_.back().events = POLLIN; //! Check ready-to-read
	++fdCount_;
}

void Server::delFromPfds(const int idx) {
	//! Copy the one from the end over this one
	// TODO использовать свап
	pfds_[idx] = pfds_.back();
	pfds_.pop_back();
}

// TODO переписать на ссылки и добавить касты в ++ стиле
void * Server::getInAddr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
