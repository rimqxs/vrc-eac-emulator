#pragma once
#include "eos/eos_api.h"
#include "eos/eos_login_types.h"

class eos_connect {
public:
	static void login(EOS_HConnect hConnect, EOS_Connect_LoginOptions const& options, void* data, const EOS_Connect_OnLoginCallback callback);

	static EOS_ELoginStatus get_login_status(EOS_HConnect hConnect, EOS_ProductUserId local_user_id);
};
