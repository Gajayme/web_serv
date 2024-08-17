#pragma once

#include "map"

class Context;

class State {
public:

	/**
	 * @brief Constructor.
	 * @param contest execution context
 	*/
	State(Context *contest);

	/**
	 * @brief Destructor.
	 */
	virtual ~State();

	/**
	 * @brief Parse config line.
	 * @param line Config line to parse.
	 */
	virtual void parseLine(std::string &line) = 0;

protected:

	Context *context_;

private:

	/**
	* DO NOT LET CYCLED STRUCTURE BEING COPIED
	*/
	State(const State &other);

	/**
	 * DO NOT LET CYCLED STRUCTURE BEING COPIED
	 */
	State &operator=(const State &other);
};




class Context {

public:

	enum StateEnum {
		StateEnumGlobal,
		StateEnumServer,
		StateEnumLocation,
	};

	/**
	 * @brief Constructor.
 	*/
	Context();

	/**
	 * @brief Destructor.
	 */
	~Context();

	/**
	 * @brief Initialize all context states.
	 */
	void initStates();

	/**
	 * @brief Parse config line by current state.
	 * @param line Config line to parse.
	 */
	void parseLine(std::string &line);

	void setActiveState(StateEnum stateEnum);

private:

	typedef std::pair<StateEnum, State *> statesMapValue;

	/**
	 * DO NOT LET CYCLED STRUCTURE BEING COPIED
	 */
	Context(const Context &other);

	/**
	 * DO NOT LET CYCLED STRUCTURE BEING COPIED
	 */
	Context &operator=(const State &other);

	Context *context_;
	StateEnum activeState_;
	std::map<StateEnum, State *>states_;

};
