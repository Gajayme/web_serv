#include "LocationInfo.h"
#include "ServConst.h"


std::ostream& operator<< (std::ostream &out, const LocationInfo &locationInfo) {
	out << "Location: " << locationInfo.url_ << std::endl << //
	"root: " << locationInfo.root_ << std::endl << //
	"is listing on: " << locationInfo.isListingOn_ << std::endl;

	out << "indexes:" << std::endl;
	for (size_t i = 0; i < locationInfo.indexes_.size(); ++i) {
		out << locationInfo.indexes_[i] << std::endl;
	}

	return out;
}


/**
	* @brief Set Http method as allowed.
	* @param httpMethod method that will be allowed.
	*/
void SetHttpMethodOn(LocationInfo locationInfo, constants::HttpMethod httpMethod) {
	locationInfo.httpMethods_[httpMethod] = true;
}