#include <eos/eos_api.h>

EOS_DECLARE_FUNC(EOS_HPlatform) DummyEOS_Platform_Create(void* options) {
    PLOG_INFO.printf("EOS_Platform_Create called");
    return 0x28B857C4A60;
}

EOS_DECLARE_FUNC(void) DummyEOS_Platform_Tick(EOS_HPlatform handle) {
}

EOS_DECLARE_FUNC(EOS_HConnect) DummyEOS_Platform_GetConnectInterface(EOS_HPlatform handle) {
    PLOG_INFO.printf("EOS_Platform_GetConnectInterface called");
    return 0x30A129C4A60;
}

EOS_DECLARE_FUNC(EOS_HAntiCheatClient) DummyEOS_Platform_GetAntiCheatClientInterface(EOS_HPlatform handle) {
    PLOG_INFO.printf("EOS_Platform_GetAntiCheatClientInterface called");
    return 0x12B139C4A40;
}
