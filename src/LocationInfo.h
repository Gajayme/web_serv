#pragma once

#include <string>
#include <map>
#include "ServConst.h"

class LocationInfo {

public:

	/**
	 * @brief Constructor.
	 */
	LocationInfo(const std::string &url);

	/**
	 * @brief Destructor.
	 */
	~LocationInfo();

private:

	std::string url_;
	std::string root_;
	std::map<constants::HttpMethod, bool> httpMethods_;
//	bool isListingOn_;
};


