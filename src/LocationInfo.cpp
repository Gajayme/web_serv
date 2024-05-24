#include "LocationInfo.h"
#include "ServConst.h"

LocationInfo::LocationInfo(const std::string &url):
isListingOn_(false),
url_(url),
httpMethods_() {
	httpMethods_[constants::HttpMethodGet] = true;
}

LocationInfo::~LocationInfo() {
}

void LocationInfo::setHttpMethodOn(const constants::HttpMethod httpMethod) {
	httpMethods_[httpMethod] = true;
}

void LocationInfo::setListing(const bool isListingOn) {
	isListingOn_ = isListingOn;
}

std::ostream& operator<< (std::ostream &out, const LocationInfo &locationInfo) {
	out << "Location: " << locationInfo.url_ << std::endl << //
	"is listing on: " << locationInfo.isListingOn_ << std::endl;

		return out;
}
