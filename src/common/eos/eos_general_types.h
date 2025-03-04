#pragma once

#include <cstdint>
#include "eos_api.h"

#pragma pack(push, 8)

#define EOS_AllocateMemoryFunc void*
#define EOS_ReallocateMemoryFunc void*
#define EOS_ReleaseMemoryFunc void*

#define EOS_LC_ALL_CATEGORIES 0x7fffffff

struct EOS_InitializeOptions {
	int32_t ApiVersion;
	EOS_AllocateMemoryFunc AllocateMemoryFunction;
	EOS_ReallocateMemoryFunc ReallocateMemoryFunction;
	EOS_ReleaseMemoryFunc ReleaseMemoryFunction;
	const char* ProductName;
	const char* ProductVersion;
	void* Reserved;
	void* SystemInitializeOptions;
	void* OverrideThreadAffinity;
};

enum EOS_ELogLevel {
	EOS_LOG_Off = 0,
	EOS_LOG_Fatal = 100,
	EOS_LOG_Error = 200,
	EOS_LOG_Warning = 300,
	EOS_LOG_Info = 400,
	EOS_LOG_Verbose = 500,
	EOS_LOG_VeryVerbose = 600
};

struct EOS_LogMessage {
	const char* category;
	const char* message;
	EOS_ELogLevel level;
};

EOS_DECLARE_CALLBACK(EOS_LogMessageFunc, const EOS_LogMessage*);

#pragma pack(pop)
