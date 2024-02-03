#pragma once

#include <string>
#include <poll.h>

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

	//! Add portion of client request data
	void addRequestData(const char *data);

	//! Parse request chunk and decide whether it's fully received
	bool parseRequestChunk(const char *data);

private:

	//! Current event (READ/WRITE)
	short event_;

	//! whether request received fully
	bool isRequestReceived_;

	//! buffer for request data
	std::string requestData_;

};


