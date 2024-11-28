#include <eos/eos_api.h>

#include "../client.h"
#include "../client_packet_processor.h"
#include "eos/eos_anticheat_types.h"
#include "protocol/packets/notify_message_to_server_packet.h"

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_Connect_AddNotifyAuthExpiration(EOS_HConnect handle, void* options, void* clientData, void* notificationFn) {
    // TODO: impl handler
    PLOG_INFO.printf("EOS_Connect_AddNotifyAuthExpiration handled");
    return 0xdeadbeef;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_AntiCheatClient_AddNotifyMessageToServer(EOS_HConnect handle, const EOS_AntiCheatClient_AddNotifyMessageToServerOptions* options, void* clientData, const EOS_AntiCheatClient_OnMessageToServerCallback notificationFn) {
	std::shared_ptr<notify_message_to_server_packet> packet = std::make_shared<notify_message_to_server_packet>();
	packet->options.ApiVersion = options->ApiVersion;
	packet->require_bind = true;
	client::send_packet(packet);

	notify_message_to_server_callback callback{};
	callback.options = *options;
	callback.client_data = clientData;
	callback.notification_fn = notificationFn;
	client_packet_processor::add_notify_message_to_server(callback);

	PLOGI.printf("EOS_AntiCheatClient_AddNotifyMessageToServer handled");;

    return 0xdeadbeef;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_Connect_AddNotifyLoginStatusChanged(EOS_HConnect handle, void* options, void* clientData, void* notificationFn) {
    // TODO: impl handler
    PLOG_INFO.printf("EOS_Connect_AddNotifyLoginStatusChanged handled");
    return 0xdeadbeef;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_AntiCheatClient_AddNotifyClientIntegrityViolated(EOS_HConnect handle, void* options, void* clientData, void* notificationFn) {
    return 0xdeadbeef;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_Achievements_AddNotifyAchievementsUnlocked(EOS_HAchievements handle, void* options, void* clientData, void* notificationFn) {
    return 0xdeadbeef;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_Achievements_AddNotifyAchievementsUnlockedV2(EOS_HAchievements handle, void* options, void* clientData, void* notificationFn) {
    return 0xdeadbeef;
}
