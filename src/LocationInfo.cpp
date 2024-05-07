#include "LocationInfo.h"
#include "ServConst.h"

LocationInfo::LocationInfo(const std::string &url):
url_(url),
root_(),
httpMethods_()
/*isListingOn_(false)*/ {
	httpMethods_[constants::HttpMethodGet] = true;
}

LocationInfo::~LocationInfo() {
}
