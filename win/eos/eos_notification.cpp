#include "eos_api.h"

EOS_DECLARE_FUNC(EOS_NotificationId) EOS_Connect_AddNotifyLoginStatusChanged(EOS_HConnect handle, void* options, void* clientData, void* notificationFn) {
    // TODO: impl handler
    PLOG_INFO.printf("EOS_Connect_AddNotifyLoginStatusChanged handled");
    return 0xdeadbeef;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_Connect_AddNotifyAuthExpiration(EOS_HConnect handle, void* options, void* clientData, void* notificationFn) {
    // TODO: impl handler
    PLOG_INFO.printf("EOS_Connect_AddNotifyAuthExpiration handled");
    return 0xdeadbeef;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_AntiCheatClient_AddNotifyMessageToServer(EOS_HConnect handle, void* options, void* clientData, void* notificationFn) {
    // TODO: impl handler
    PLOG_INFO.printf("EOS_AntiCheatClient_AddNotifyMessageToServer handled");
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
