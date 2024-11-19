#include "eos_api.h"

EOS_DECLARE_FUNC(void) dummy_func() {
    PLOGF.printf("This should never happened");
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Initialize(void* options) {
    PLOG_INFO.printf("EOS_Initialize called");
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_ENetworkStatus) DummyEOS_Platform_GetNetworkStatus(EOS_HPlatform handle) {
    return EOS_NS_Online;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Platform_SetApplicationStatus(EOS_HPlatform handle, int newStatus) {
    PLOG_INFO.printf("EOS_Platform_SetApplicationStatus called: newStatus=%d", newStatus);
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Platform_SetNetworkStatus(EOS_HPlatform handle, EOS_ENetworkStatus newStatus) {
    PLOG_INFO.printf("EOS_Platform_SetNetworkStatus called: newStatus=%d", newStatus);
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Logging_SetCallback(void* callback) {
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Logging_SetLogLevel(int category, int level) {
    return EOS_Success;
}
