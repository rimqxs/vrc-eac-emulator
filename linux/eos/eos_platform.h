#pragma once
#include "eos/eos_login_types.h"
#include "eos/eos_platform_types.h"

class eos_platform {
public:
	static void create_platform(EOS_Platform_Options const& options);

	static void tick();

	static EOS_HConnect get_connect_interface();

	static void connect_login(EOS_HConnect hConnect, EOS_Connect_LoginOptions const& options, void* data, const EOS_Connect_OnLoginCallback callback);

	static bool is_platform_created();
};
