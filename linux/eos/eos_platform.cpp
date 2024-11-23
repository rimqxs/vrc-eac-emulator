#include "eos_platform.h"

#include "eos_utils.h"
#include "eos/eos_api.h"

EOS_HPlatform hPlatform = NULL;

void eos_platform::create_platform(EOS_Platform_Options const& options) {
	typedef EOS_HPlatform (EOS_CALL*EOS_Platform_Create)(EOS_Platform_Options const*);
	static auto eos_create_platform = reinterpret_cast<EOS_Platform_Create>(
		eos_utils::get_eos_proc_addr("EOS_Platform_Create"));
	if (!eos_create_platform) {
		PLOGF.printf("Could not resolve EOS_Platform_Create");
		return;
	}

	hPlatform = eos_create_platform(&options);
	if (!hPlatform) {
		PLOGE.printf("Failed to call EOS_Platform_Create!");
		return;
	}
	PLOGI.printf("Platform Created: product_id=%s, client_id=%s", options.ProductId, options.ClientCredentials.ClientId);
}
