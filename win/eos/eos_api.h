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

#define EOS_DECLARE_FUNC(ret_type) extern "C" ret_type __stdcall
