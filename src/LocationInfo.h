#pragma once

#include <map>
#include <string>
#include <iostream>

#include "ServConst.h"


struct LocationInfo {

	typedef std::vector<std::string> Indexes;
	typedef std::map<constants::HttpMethod, bool> HttpMethodsMap;

	std::string root_; //! Location's root.
	std::string url_; //! Location's url (name).
	bool isListingOn_; //! Is listing allowed in location.
	std::vector<std::string> indexes_; //! Location's indexes.
	HttpMethodsMap httpMethods_; //! HTTP methods that allowed in location

	/**
	 * @brief Overloading of cout operator.
	 * @param out standard output stream.
	 * @param locationInfo Location info object.
	 * @return standard output stream.
	 */
	friend std::ostream& operator<< (std::ostream &out, const LocationInfo &locationInfo);

};

/**
 * @brief Set Http method as allowed.
 * @param httpMethod method that will be allowed.
 */
void SetHttpMethodOn(LocationInfo locationInfo, constants::HttpMethod httpMethod);


