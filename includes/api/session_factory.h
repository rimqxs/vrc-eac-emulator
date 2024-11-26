#pragma once
#include <memory>

#include "request.h"
#include "response.h"
#include "session_id.h"
#include "requests/id2string_request.h"
#include "response/id2string_response.h"

#define GENERATE_SESSION(t) return std::make_shared<t>();

class session_factory {
public:
	static std::shared_ptr<request> create_request(unsigned char req_id) {
		switch (req_id) {
			case ID2STRING_REQ_ID:
				GENERATE_SESSION(id2string_request);
			default:
				return nullptr;
		}
	}

	static std::shared_ptr<response> create_response(unsigned char req_id) {
		switch (req_id) {
			case ID2STRING_RES_ID:
				GENERATE_SESSION(id2string_response);
			default:
				return nullptr;
		}
	}
};