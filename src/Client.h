#pragma once

#include <string>
#include <poll.h>
#include "HttpParser.h"

class Client {
public:

	//! Constructor
	Client();

	//! Destructor
	~Client();

	//! Copy constructor
	Client(const Client &other);

	//! Assignment operator
	Client &operator=(const Client &other);

	void receive(const char* request_data);

private:

	//! Current event (READ/WRITE)
	short event_;

	HttpParser parser;

};


