#pragma once

#include "common/api/request.h"
#include "common/api/response.h"

class login_handler {
public:
	static std::shared_ptr<response> handle(std::shared_ptr<request> request);
};
