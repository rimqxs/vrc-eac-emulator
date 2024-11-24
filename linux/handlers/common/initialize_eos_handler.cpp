#include "initialize_eos_handler.h"

#include "../../eos/eos.h"
#include "../../eos/eos_logger.h"
#include "eos/eos_general_types.h"
#include "protocol/packets/c2s/initialize_eos_packet.h"

void initialize_eos_handler::handle(std::shared_ptr<packet> packet) {
	auto initialize_eos = std::static_pointer_cast<initialize_eos_packet>(packet);

	EOS_InitializeOptions options{};
	options.ApiVersion = initialize_eos->api_version;
	options.AllocateMemoryFunction = nullptr;
	options.ReallocateMemoryFunction = nullptr;
	options.ReleaseMemoryFunction = nullptr;
	options.ProductName = initialize_eos->product_name.c_str();
	options.ProductVersion = initialize_eos->product_version.c_str();
	options.Reserved = nullptr;
	options.SystemInitializeOptions = nullptr;
	options.OverrideThreadAffinity = nullptr;

	eos::initialize(options);

	// initialize eos logger
	eos::set_logging_callback(&eos_logger::log);
	eos::set_log_level(EOS_LC_ALL_CATEGORIES, EOS_LOG_VeryVerbose);
}
