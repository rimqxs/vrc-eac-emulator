#pragma once

#include <unordered_map>

#include "eos/eos_login_types.h"
#include "protocol/packets/s2c/response_login_packet.h"

class eos {
	static inline std::unordered_map<int, std::tuple<void*, EOS_Connect_OnLoginCallback>> connect_callbacks;
	static inline std::unordered_map<int, std::tuple<EOS_EResult, nullable_string, int32_t>> request_id2string_results;
public:
	static void register_connect_callback(int session_id, std::tuple<void*, EOS_Connect_OnLoginCallback> data);

	static void handle_response_login(std::shared_ptr<response_login_packet> packet);

	static void submit_id2string_result(int session_id, EOS_EResult result, nullable_string buffer, int32_t buffer_size);

	static std::tuple<EOS_EResult, nullable_string, int32_t> wait_for_id2string(int session_id);
};
