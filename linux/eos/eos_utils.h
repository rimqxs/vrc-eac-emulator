#pragma once

#include <libloaderapi.h>

class eos_utils {
	static FARPROC get_eos_proc_addr(LPCSTR func_name) {
		return GetProcAddress(GetModuleHandleA("EOSSDK-Win64-Shipping.dll"), func_name);
	}
};
