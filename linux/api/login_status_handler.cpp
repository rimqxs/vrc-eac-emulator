#include "login_status_handler.h"

#include "../eos/eos_connect.h"
#include "../eos/eos_platform.h"
#include "api/requests/login_status_request.h"
#include "api/response/login_status_response.h"

std::shared_ptr<response> login_status_handler::handle(std::shared_ptr<request> request) {
	static auto connect_interface = eos_platform::get_connect_interface();

	auto login_status = std::static_pointer_cast<login_status_request>(request);
	EOS_ELoginStatus result = eos_connect::get_login_status(connect_interface, login_status->user_id);

	auto response = std::make_shared<login_status_response>();
	response->status = result;
	return response;
}
