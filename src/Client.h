#pragma once

#include <string>
#include <poll.h>
#include "HttpParser.h"

class Client {
public:

	/**
	 * @brief Constructor. Create empty Optional.
	 */
	Client();

	/**
	 * @brief Constructor. Create empty Optional.
	 */
	~Client();

	/**
	 * @brief Copy constructor.
	 * @param other another Client object to copy from.
	 */
	Client(const Client &other);


	/**
	 * @brief Assignment operator.
	 * @param other another Client object to assign from
	 */
	Client &operator=(const Client &other);

	void receive(const char* request_data);

private:

	//! Current event (READ/WRITE)
	short event_;

	HttpParser parser;

};


