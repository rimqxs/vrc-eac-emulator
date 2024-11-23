#pragma once

#include <Windows.h>
#include <plog/Log.h>

#define EOS_Success 0
#define EOS_NS_Online 2

#define EOS_EResult int
#define EOS_ENetworkStatus int

#define EOS_HPlatform uintptr_t
#define EOS_HConnect uintptr_t
#define EOS_HAntiCheatClient uintptr_t
#define EOS_HAchievements uintptr_t
#define EOS_NotificationId uintptr_t
#define EOS_ProductUserId uintptr_t
#define EOS_ProductUserId uintptr_t
#define EOS_ContinuanceToken uintptr_t

#define EOS_EXTERN_C extern "C"
#define EOS_CALL __stdcall
#define EOS_DECLARE_FUNC(ret_type) EOS_EXTERN_C ret_type EOS_CALL
#define EOS_DECALRE_CALLBACK(CallbackName, ...) EOS_EXTERN_C typedef void (EOS_CALL* CallbackName)(__VA_ARGS__)
