#include <iostream>

#include "Client.h"

Client::Client():
event_(POLLIN),
isRequestReceived_(false),
requestData_() {
}

Client::~Client() {
}

Client::Client(const Client &other):
event_(other.event_),
isRequestReceived_(other.isRequestReceived_),
requestData_(other.requestData_) {
}

Client &Client::operator=(const Client &other) {
	if (this != &other) {
		this->event_ = other.event_;
		this->isRequestReceived_ = other.isRequestReceived_;
		this->requestData_ = other.requestData_;
	}
	return *this;
}

bool Client::parseRequestChunk(const char *data) {
	(void *)data;
	std::cout << "Parsing request" << std::endl;
	return false;
}

void Client::addRequestData(const char *data) {
	requestData_ += data;
	isRequestReceived_ = parseRequestChunk(data);
}

