#pragma once

#include <string>
#include <vector>
#include "../ServerInfo.h"
#include "../ServConst.h"

class ConfigParser;

class ConfigParserState {
public:

	/**
	 * @brief Constructor.
	 * @param configParser execution context
 	*/
	explicit ConfigParserState(ConfigParser *configParser);

	/**
	 * @brief Destructor.
	 */
	virtual ~ConfigParserState();

	/**
	 * @brief Parse config line.
	 * @param line orig config line to log errors.
	 * @param lineCopy copy of orig line. To parse.
	 * @param servers container with servers to store parsed info to.
	 */
	virtual void parseLine(const std::string &line, std::string &lineCopy, std::vector<ServerInfo> &servers) = 0;

protected:

	ConfigParser *configParser_;

private:

	/**
	* DO NOT LET CYCLED STRUCTURE BEING COPIED
	*/
	ConfigParserState(const ConfigParserState &other);

	/**
	 * DO NOT LET CYCLED STRUCTURE BEING COPIED
	 */
	ConfigParserState &operator=(const ConfigParserState &other);

};



class ConfigParser {

public:

	typedef std::vector<std::string> SplitLine;

	enum StateType {
		StateTypeGlobal,
		StateTypeServer,
		StateTypeLocation,
	};

	/**
	 * @brief Constructor.
	 */
	ConfigParser();

	/**
	 * @brief Destructor.
	 */
	~ConfigParser();

	/**
	 * @brief Initialize all context states.
	 */
	void initStates();

	/**
	 * @brief Set active state.
	 * @param state State to set as an active.
	 */
	void setActiveState(StateType state);

	/**
  	 * @brief Get all parsed servers.
  	 * @return all parsed servers.
  	 */
	const std::vector<ServerInfo> &getServers();

	/**
	 * @brief Parse config.
	 * @param path Path to config file.
	 */
	void parseConfig(const std::string &path = configTokens::DEFAULT_CONFIG_PATH);

private:

	typedef std::pair<StateType, ConfigParserState *> statesMapValue;

	/**
	 * DO NOT LET CYCLED STRUCTURE BEING COPIED
	 */
	ConfigParser(const ConfigParser &other);

	/**
	 * DO NOT LET CYCLED STRUCTURE BEING COPIED
	 */
	ConfigParser &operator=(const ConfigParser &other);

	/**
	 * @brief Parse config line.
	 * @param line Config line to parse.
	 */
	void parseLine(std::string &line);

	StateType activeState_;  //!< Current parse state.
	std::map<StateType, ConfigParserState *>states_; //!< Container with all parse states.
	std::vector<ServerInfo> servers_; //!< Containers with servers.
};


