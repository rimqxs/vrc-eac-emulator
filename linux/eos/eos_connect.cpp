#include "eos_connect.h"

#include "eos_utils.h"

void eos_connect::login(EOS_HConnect hConnect, EOS_Connect_LoginOptions const& options, void* data, const EOS_Connect_OnLoginCallback callback) {
	typedef void (EOS_CALL*EOS_Connect_Login)(EOS_HConnect, EOS_Connect_LoginOptions const*, void*, EOS_Connect_OnLoginCallback);
	static auto eos_connect_login = reinterpret_cast<EOS_Connect_Login>(
		eos_utils::get_eos_proc_addr("EOS_Connect_Login"));
	if (!eos_connect_login) {
		PLOGF.printf("Could not resolve EOS_Connect_Login");
		return;
	}

	eos_connect_login(hConnect, &options, data, callback);
}

EOS_ELoginStatus eos_connect::get_login_status(EOS_HConnect hConnect, EOS_ProductUserId local_user_id) {
	typedef EOS_ELoginStatus (EOS_CALL*EOS_Connect_GetLoginStatus)(EOS_HConnect, EOS_ProductUserId);
	static auto eos_connect_get_login_status = reinterpret_cast<EOS_Connect_GetLoginStatus>(
		eos_utils::get_eos_proc_addr("EOS_Connect_GetLoginStatus"));
	if (!eos_connect_get_login_status) {
		PLOGF.printf("Could not resolve EOS_Connect_GetLoginStatus");
		return 0;
	}

	return eos_connect_get_login_status(hConnect, local_user_id);
}
