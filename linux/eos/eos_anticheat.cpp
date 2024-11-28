#include "eos_anticheat.h"

#include "eos_utils.h"

EOS_EResult eos_anticheat::begin_session(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_BeginSessionOptions const& options) {
	typedef EOS_EResult (EOS_CALL*EOS_AntiCheatClient_BeginSession)(EOS_HAntiCheatClient, const EOS_AntiCheatClient_BeginSessionOptions*);
	static auto eos_anticheat_client_begin_session = reinterpret_cast<EOS_AntiCheatClient_BeginSession>(
		eos_utils::get_eos_proc_addr("EOS_AntiCheatClient_BeginSession"));
	if (!eos_anticheat_client_begin_session) {
		PLOGF.printf("Could not resolve EOS_AntiCheatClient_BeginSession");
		return 0;
	}

	return eos_anticheat_client_begin_session(handle, &options);
}

EOS_EResult eos_anticheat::end_session(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_EndSessionOptions const& options) {
	typedef EOS_EResult (EOS_CALL*EOS_AntiCheatClient_EndSession)(EOS_HAntiCheatClient, const EOS_AntiCheatClient_EndSessionOptions*);
	static auto eos_anticheat_client_end_session = reinterpret_cast<EOS_AntiCheatClient_EndSession>(
		eos_utils::get_eos_proc_addr("EOS_AntiCheatClient_EndSession"));
	if (!eos_anticheat_client_end_session) {
		PLOGF.printf("Could not resolve EOS_AntiCheatClient_EndSession");
		return 0;
	}

	return eos_anticheat_client_end_session(handle, &options);
}

EOS_NotificationId eos_anticheat::add_notify_message_to_server(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_AddNotifyMessageToServerOptions const& options, void* client_data, EOS_AntiCheatClient_OnMessageToServerCallback notification_fn) {
	typedef EOS_NotificationId (EOS_CALL*EOS_AntiCheatClient_AddNotifyMessageToServer)(EOS_HAntiCheatClient, const EOS_AntiCheatClient_AddNotifyMessageToServerOptions*, void*, EOS_AntiCheatClient_OnMessageToServerCallback);
	static auto eos_anticheat_client_add_notify_message_to_server = reinterpret_cast<EOS_AntiCheatClient_AddNotifyMessageToServer>(
		eos_utils::get_eos_proc_addr("EOS_AntiCheatClient_AddNotifyMessageToServer"));
	if (!eos_anticheat_client_add_notify_message_to_server) {
		PLOGF.printf("Could not resolve EOS_AntiCheatClient_AddNotifyMessageToServer");
		return 0;
	}

	return eos_anticheat_client_add_notify_message_to_server(handle, &options, client_data, notification_fn);
}

void eos_anticheat::receive_message_from_server(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_ReceiveMessageFromServerOptions const& options) {
	typedef void (EOS_CALL*EOS_AntiCheatClient_ReceiveMessageFromServer)(EOS_HAntiCheatClient, const EOS_AntiCheatClient_ReceiveMessageFromServerOptions*);
	static auto eos_anticheat_client_receive_message_from_server = reinterpret_cast<EOS_AntiCheatClient_ReceiveMessageFromServer>(
		eos_utils::get_eos_proc_addr("EOS_AntiCheatClient_ReceiveMessageFromServer"));
	if (!eos_anticheat_client_receive_message_from_server) {
		PLOGF.printf("Could not resolve EOS_AntiCheatClient_ReceiveMessageFromServer");
		return;
	}

	eos_anticheat_client_receive_message_from_server(handle, &options);
}