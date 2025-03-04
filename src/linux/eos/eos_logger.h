#pragma once

#include "common/eos/eos_general_types.h"

class eos_logger {
public:
	static void log(const EOS_LogMessage* message) {
		switch (message->level) {
			case EOS_LOG_Fatal:
				PLOGF.printf("[%s] %s", message->category, message->message);
				break;
			case EOS_LOG_Error:
				PLOGE.printf("[%s] %s", message->category, message->message);
				break;
			case EOS_LOG_Warning:
				PLOGW.printf("[%s] %s", message->category, message->message);
				break;
			case EOS_LOG_Info:
				PLOGI.printf("[%s] %s", message->category, message->message);
				break;
			case EOS_LOG_Verbose | EOS_LOG_VeryVerbose:
				PLOGV.printf("[%s] %s", message->category, message->message);
				break;
			default:
				PLOGN.printf("[%s] %s", message->category, message->message);
				break;
		}
	}
};
