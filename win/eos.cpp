#include <Windows.h>
#include <plog/Log.h>

#define EOS_Success 0

#define EOS_EResult int
#define EOS_HPlatform uintptr_t
#define EOS_HConnect uintptr_t
#define EOS_HAntiCheatClient uintptr_t
#define EOS_HAchievements uintptr_t
#define EOS_NotificationId uintptr_t

#define EOS_DECLARE_FUNC(ret_type) extern "C" ret_type __stdcall

EOS_DECLARE_FUNC(void) dummy_func() {
    PLOGF.printf("This should never happened");
}

///////// General

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Initialize(void* options) {
    PLOGD.printf("EOS_Initialize called");
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Platform_SetApplicationStatus(EOS_HPlatform handle, int newStatus) {
    PLOGD.printf("EOS_Platform_SetApplicationStatus called");
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_Achievements_AddNotifyAchievementsUnlocked(EOS_HAchievements handle, void* options, void* clientData, void* callback) {
    return 0x1861ACCAA40;
}

EOS_DECLARE_FUNC(EOS_NotificationId) DummyEOS_Achievements_AddNotifyAchievementsUnlockedV2(EOS_HAchievements handle, void* options, void* clientData, void* notificationFn) {
    return 0x6AB1C9C4AB0;

}

///////// Logging
EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Logging_SetCallback(void* callback) {
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Logging_SetLogLevel(int category, int level) {
    return EOS_Success;
}

///////// Platform
EOS_DECLARE_FUNC(EOS_HPlatform) DummyEOS_Platform_Create(void* options) {
    PLOGD.printf("EOS_Platform_Create called and returning the fake handle");
    return 0x28B857C4A60;
}

EOS_DECLARE_FUNC(EOS_HConnect) DummyEOS_Platform_GetConnectInterface(EOS_HPlatform handle) {
    PLOGD.printf("EOS_Platform_GetConnectInterface called and returning the fake handle");
    return 0x30A129C4A60;
}

EOS_DECLARE_FUNC(EOS_HAntiCheatClient) DummyEOS_Platform_GetAntiCheatClientInterface(EOS_HPlatform handle) {
    PLOGD.printf("EOS_Platform_GetAntiCheatClientInterface called and returning the fake handle");
    return 0x12B139C4A40;
}
