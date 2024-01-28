#include "Client.h"

Client::Client(const int fd, const short events):
fdInfo_(),
isRequestGot_(false),
requestData_() {
	fdInfo_.fd = fd;
	fdInfo_.events = events;
}

Client::~Client() {
}

//Client::Client(const Client &other) {
////TODO дописать, когда будет понятна структура клиента
//}

//Client &Client::operator=(const Client &other) {
////TODO дописать, когда будет понятна структура клиента
//}

void Client::AddRequestData(const char *data) {
	requestData_ += data;
}

