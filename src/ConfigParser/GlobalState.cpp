#include "iostream"

#include "GlobalState.h"

GlobalState::GlobalState(Context *contest):
State(contest) {
}

void GlobalState::parseLine(std::string &line) {
	std::cout << "Parsing line by GlobalState. line: " << line   << std::endl;
	context_->setActiveState(Context::StateEnumServer);
}