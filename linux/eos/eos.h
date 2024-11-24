#pragma once
#include "eos/eos_general_types.h"

class eos {
public:
	static void initialize(EOS_InitializeOptions const& options);

	static void set_logging_callback(EOS_LogMessageFunc callback);

	static void set_log_level(int category, EOS_ELogLevel level);

	static bool is_eos_initialized();
};
