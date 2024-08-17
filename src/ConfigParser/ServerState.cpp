#include "iostream"

#include "ServerState.h"

ServerState::ServerState(Context *contest):
		State(contest) {
}

void ServerState::parseLine(std::string &line) {
	std::cout << "Parsing line by ServerState. line: " << line   << std::endl;
	(void)line;

}