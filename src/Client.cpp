#include <iostream>

#include "Client.h"

Client::Client():
event_(POLLIN),
parser() {
}

Client::~Client() {
}

Client::Client(const Client &other):
event_(other.event_),
parser(other.parser) {
}

Client &Client::operator=(const Client &other) {
	if (this != &other) {
		this->event_ = other.event_;
		this->parser = other.parser;
	}
	return *this;
}

void Client::receive(const char* request_data) {
	try
	{
		parser.read(request_data);
	}
	catch (const bad_request& e)
	{
		// todo
		// the server SHOULD respond with a 400 (Bad Request) response and close the connection.
		std::cout << e.what() << std::endl;
	}
}
