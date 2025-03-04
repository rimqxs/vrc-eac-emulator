#pragma once

#include <common/eos/eos_login_types.h>
#include <common/eos/eos_platform_types.h>

class eos_platform {
public:
	static void create_platform(EOS_Platform_Options const& options);

	static void tick();

	static EOS_HConnect get_connect_interface();

	static EOS_HAntiCheatClient get_anticheat_client_interface();

	static bool is_platform_created();
};
