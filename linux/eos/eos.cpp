#include "eos.h"

#include "eos_utils.h"
#include "eos/eos_api.h"


bool initialized = false;
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
	initialized = true;
}

void eos::set_logging_callback(EOS_LogMessageFunc callback) {
	typedef EOS_EResult(EOS_CALL* EOS_Logging_SetCallback)(EOS_LogMessageFunc);
	static auto eos_logging_set_callback = reinterpret_cast<EOS_Logging_SetCallback>(
		eos_utils::get_eos_proc_addr("EOS_Logging_SetCallback"));
	if (!eos_logging_set_callback) {
		PLOGF.printf("Could not resolve EOS_Logging_SetCallback");
		return;
	}

	auto status_code = eos_logging_set_callback(callback);
	if (status_code != EOS_Success) {
		PLOGE.printf("Failed to set logging callback: %d", status_code);
		return;
	}
	PLOGI.printf("Logging callback has been set successfully");
}

void eos::set_log_level(int category, EOS_ELogLevel level) {
	typedef EOS_EResult(EOS_CALL* EOS_Logging_SetLogLevel)(int, EOS_ELogLevel);
	static auto eos_logging_set_log_level = reinterpret_cast<EOS_Logging_SetLogLevel>(
		eos_utils::get_eos_proc_addr("EOS_Logging_SetLogLevel"));
	if (!eos_logging_set_log_level) {
		PLOGF.printf("Could not resolve EOS_Logging_SetLogLevel");
		return;
	}

	auto status_code = eos_logging_set_log_level(category, level);
	if (status_code != EOS_Success) {
		PLOGE.printf("Failed to set log level: %d", status_code);
		return;
	}
	PLOGI.printf("Log level has been set successfully: category=%d, level=%d", category, level);
}

bool eos::is_eos_initialized() {
	return initialized;
}
