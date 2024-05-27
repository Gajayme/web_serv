#include "LocationInfo.h"
#include "ServConst.h"

LocationInfo::LocationInfo(const std::string &url):
url_(url),
root_(),
isListingOn_(false),
indexes_(),
httpMethods_() {
	httpMethods_[constants::HttpMethodGet] = true;
}

LocationInfo::~LocationInfo() {
}

LocationInfo::LocationInfo(const LocationInfo &other):
url_(other.url_),
root_(other.root_),
isListingOn_(other.isListingOn_),
indexes_(other.indexes_),
httpMethods_(other.httpMethods_) {
}

LocationInfo &LocationInfo::operator=(const LocationInfo &other) {
	if (this != &other) {
		this->url_ = other.url_;
		this->root_ = other.root_;
		this->isListingOn_ = other.isListingOn_;
		this->indexes_ = other.indexes_;
		this->httpMethods_ = other.httpMethods_;
	}
	return *this;
}

void LocationInfo::setHttpMethodOn(const constants::HttpMethod httpMethod) {
	httpMethods_[httpMethod] = true;
}

void LocationInfo::setListing(const bool isListingOn) {
	isListingOn_ = isListingOn;
}

void LocationInfo::setRoot(const std::string &root) {
	root_ = root;
}

void LocationInfo::setIndexes(const std::vector<std::string> &indexes) {
	indexes_ = indexes;
}

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
