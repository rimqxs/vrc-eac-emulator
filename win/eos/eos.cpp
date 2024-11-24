#include "eos.h"

void eos::register_connect_callback(int session_id, std::tuple<void*, EOS_Connect_OnLoginCallback> data) {
	connect_callbacks[session_id] = data;
}

void eos::handle_response_login(std::shared_ptr<response_login_packet> packet) {
	if (!connect_callbacks.contains(packet->session_id)) {
		PLOGE.printf("No callback found for session_id=%d", packet->session_id);
		return;
	}

	auto data = connect_callbacks[packet->session_id];

	EOS_Connect_LoginCallbackInfo info{};
	info.ResultCode = packet->result_code;
	info.ClientData = std::get<0>(data);
	info.LocalUserId = packet->local_user_id;
	info.ContinuanceToken = packet->continuance_token;

	PLOGI.printf("Calling callback for localUserId=%lld, session_id=%d", packet->local_user_id, packet->session_id);;
	std::get<1>(data)(&info);
}

void eos::submit_id2string_result(int session_id, int result, nullable_string buffer, int32_t buffer_size) {
	request_id2string_results[session_id] = std::make_tuple(result, buffer, buffer_size);
}

std::tuple<int, nullable_string, int32_t> eos::wait_for_id2string(int session_id) {
	while (!request_id2string_results.contains(session_id)) {
		Sleep(100);
	}

	return request_id2string_results[session_id];
}
