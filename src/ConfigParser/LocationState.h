#pragma once

#include "Context.h"

class LocationState: public State {

public:
	/**
	 * @brief Constructor.
	 * @param contest execution context
	 */
	LocationState(Context *contest);

	/**
	 * @brief Parse config line.
	 * @param line Config line to parse.
	 */
	virtual void parseLine(std::string &line);

};
