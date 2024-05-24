#pragma once

namespace configTokens {
	const std::string DEFAULT_CONFIG_PATH("/Users/georgii/School_21/web_serv/configs/default.conf");
	const std::string DEFAULT_SERVER_NAME("default_");
	const std::string SERVER("server");
	const std::string SERVER_NAME("server_name");
	const std::string LISTEN("listen");
	const std::string HOST("host");
	const std::string BODY_SIZE("client_max_body_size");
	const std::string LOCATION("location");
	const std::string AUTONDEX("autoindex");
	const std::string METHODS("allow_methods");
	const std::string GET("get");
	const std::string POST("post");
	const std::string DELETE("delete");
	const std::string UNSUPPORTED("unsupported");
	const std::string ON("on");
	const std::string OFF("off");
	const std::string	OPEN_BRACKET("{");
	const std::string	CLOSE_BRACKET("}");
	const std::string	WHITESPACE(" ");
	const std::string ZERO("0");
	const std::string HASHTAG("#");
} // namespace configTokens


namespace constants {

	const int listeningBacklog = 10;
	const int buffSize = 512;

	enum HttpMethod {
		HttpMethodGet,
		HttpMethodPost,
		HttpMethodDelete,
	};

	inline const std::string &HttpMethodToString(const HttpMethod httpMethod) {
		switch (httpMethod) {
			case HttpMethodGet:
				return configTokens::GET;
			case HttpMethodPost:
				return configTokens::POST;
			case HttpMethodDelete:
				return configTokens::DELETE;
			default:
				return configTokens::UNSUPPORTED;
		}
	}

}
