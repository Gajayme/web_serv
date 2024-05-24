#pragma once

#include <map>
#include <string>
#include <iostream>

#include "ServConst.h"

class LocationInfo {

public:

	/**
	 * @brief Constructor.
	 */
	explicit LocationInfo (const std::string &url);

	/**
	 * @brief Destructor.
	 */
	~LocationInfo();

	/**
	 * @brief Set Http method as allowed.
	 * @param httpMethod method that will be allowed.
	 */
	void setHttpMethodOn(constants::HttpMethod httpMethod);

	/**
	 * @brief Set Http method as allowed.
	 * @param httpMethod method that will be allowed.
	 */
	void setListing(bool isListingOn);

	/**
	 * @brief Overloading of cout operator.
	 * @param out standard output stream.
	 * @param locationInfo Location info object.
	 * @return standard output stream.
	 */
	friend std::ostream& operator<< (std::ostream &out, const LocationInfo &locationInfo);

private:

	typedef std::map<constants::HttpMethod, bool> HttpMethodsMap;

	bool isListingOn_; //! Is listing allowed in location.
	std::string url_; //! Location's url.
	HttpMethodsMap httpMethods_; //! HTTP methods that allowed in location
};


