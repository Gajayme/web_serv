#pragma once

namespace constants {

	const int listeningBacklog = 10;
	const int buffSize = 512;

	enum HttpMethod {
		HttpMethodGet,
		HttpMethodPost,
		HttpMethodDelete,
	};

}
