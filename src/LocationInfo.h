#pragma once

#include <map>
#include <string>
#include <iostream>

#include "ServConst.h"

class LocationInfo {

public:

	typedef std::vector<std::string> Indexes;

	/**
	 * @brief Constructor.
	 */
	explicit LocationInfo(const std::string &url);

	/**
	 * @brief Destructor.
	 */
	~LocationInfo();

	/**
	 * @brief Copy constructor.
	 * @param other another Client object to copy from.
	 */
	LocationInfo(const LocationInfo &other);

	/**
	 * @brief Copy constructor.
	 * @param other another Client object to copy from.
	 */
	LocationInfo &operator=(const LocationInfo &other);

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
	 * @brief Set location's root.
	 * @param root root path.
	 */
	void setRoot(const std::string &root);

	/**
	 * @brief Set location's index.
	 * @param index location indexes.
	 */
	void setIndexes(const std::vector<std::string> &indexex);

	/**
	 * @brief Overloading of cout operator.
	 * @param out standard output stream.
	 * @param locationInfo Location info object.
	 * @return standard output stream.
	 */
	friend std::ostream& operator<< (std::ostream &out, const LocationInfo &locationInfo);

private:

	typedef std::map<constants::HttpMethod, bool> HttpMethodsMap;

	std::string url_; //! Location's url (name).
	std::string root_; //! Location's root.
	bool isListingOn_; //! Is listing allowed in location.
	std::vector<std::string> indexes_; //! Location's indexes.
	HttpMethodsMap httpMethods_; //! HTTP methods that allowed in location
};


