#pragma once
#include <cstdint>

#pragma pack(push, 8)

#define EOS_HIntegratedPlatformOptionsContainer void*

struct EOS_Platform_ClientCredentials {
	const char* ClientId;
	const char* ClientSecret;
};

struct EOS_Platform_RTCOptions {
	int32_t ApiVersion;
	void* PlatformSpecificOptions;
	int BackgroundMode;
};

struct EOS_Platform_Options {
	int32_t ApiVersion;
	void* Reserved;
	const char* ProductId;
	const char* SandboxId;
	EOS_Platform_ClientCredentials ClientCredentials;
	bool bIsServer;
	const char* EncryptionKey;
	const char* OverrideCountryCode;
	const char* OverrideLocaleCode;
	const char* DeploymentId;
	uint64_t Flags;
	const char* CacheDirectory;
	uint32_t TickBudgetInMilliseconds;
	const EOS_Platform_RTCOptions* RTCOptions;
	EOS_HIntegratedPlatformOptionsContainer IntegratedPlatformOptionsContainerHandle;
	const void* SystemSpecificOptions;
	double* TaskNetworkTimeoutSeconds;
};

#pragma pack(pop)
