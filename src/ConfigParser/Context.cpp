#include "Context.h"
#include "GlobalState.h"
#include "ServerState.h"
#include "LocationState.h"

//======
// State
//======

State::State(Context *contest):
		context_(contest) {
}

State::~State() {
}


//========
// Context
//========

Context::Context():
states_(),
activeState_(StateEnumGlobal) {
}

Context::~Context() {
}

void Context::parseLine(std::string &line) {
	states_[activeState_]->parseLine(line);
}

void Context::initStates() {
	states_.insert(statesMapValue(StateEnumGlobal, new GlobalState(this)));
	states_.insert(statesMapValue(StateEnumServer, new ServerState(this)));
	states_.insert(statesMapValue(StateEnumLocation, new LocationState(this)));
}

void Context::setActiveState(Context::StateEnum stateEnum) {
	activeState_ = stateEnum;
}
