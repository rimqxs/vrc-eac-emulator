#pragma once

#include "common/eos/eos_general_types.h"

class eos {
public:
	static void initialize(EOS_InitializeOptions const& options);

	static void set_logging_callback(EOS_LogMessageFunc callback);

	static void set_log_level(int category, EOS_ELogLevel level);

	static EOS_EResult product_user_id_to_string(EOS_ProductUserId user_id, char* out_buffer, int32_t* in_out_buffer_length);

	static bool is_eos_initialized();
};
