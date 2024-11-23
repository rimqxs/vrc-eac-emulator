#pragma once
#include <cstdint>

#pragma pack(push, 8)

#define EOS_AllocateMemoryFunc void*
#define EOS_ReallocateMemoryFunc void*
#define EOS_ReleaseMemoryFunc void*

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

#pragma pack(pop)
