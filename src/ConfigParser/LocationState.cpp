#include "iostream"

#include "LocationState.h"

LocationState::LocationState(Context *contest):
State(contest) {
}

void LocationState::parseLine(std::string &line) {
	std::cout << "Parsing line by LocationState. line: " << line   << std::endl;
	(void)line;
}