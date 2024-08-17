#pragma once

#include "Context.h"


class ServerState: public State {

public:
	/**
	 * @brief Constructor.
	 * @param contest execution context
	 */
	ServerState(Context *contest);

	/**
	 * @brief Parse config line.
	 * @param line Config line to parse.
	 */
	virtual void parseLine(std::string &line);

};
