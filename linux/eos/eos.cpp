#include "eos.h"

#include "eos_utils.h"
#include "eos/eos_api.h"

void eos::initialize(EOS_InitializeOptions const& options) {
	typedef EOS_EResult(EOS_CALL* EOS_Initialize)(EOS_InitializeOptions const*);
	static auto eos_initialize = reinterpret_cast<EOS_Initialize>(eos_utils::get_eos_proc_addr("EOS_Initialize"));
	if (!eos_initialize) {
		PLOGF.printf("Could not resolve EOS_Initialize");
		return;
	}

	auto status_code = eos_initialize(&options);
	if (status_code != EOS_Success) {
		PLOGE.printf("Failed to initialize eos: %d", status_code);
		return;
	}
	PLOGI.printf("EOS has been initialized successfully: productName=%s", options.ProductName);
}
