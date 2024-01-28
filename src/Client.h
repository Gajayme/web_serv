#pragma once

#include <string>
#include <poll.h>

class Client {
public:

	//! Constructor
	Client(int fd, short events);

	//! Destructor
	~Client();

//	//! Copy constructor
//	Client(const Client &other);
//
//	//! Assignment operator
//	Client &operator=(const Client &other);

	//! Add portion of client request data
	void AddRequestData(const char *data);

private:

	bool isRequestGot_;
	pollfd fdInfo_;
	//TODO потом заменить на вектор (если будет необходимость)
	std::string requestData_;

};


