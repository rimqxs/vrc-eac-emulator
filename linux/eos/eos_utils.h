#pragma once

#include <windows.h>

class eos_utils {
public:
	static FARPROC get_eos_proc_addr(LPCSTR func_name) {
		return GetProcAddress(GetModuleHandleA("EOSSDK-Win64-Shipping.dll"), func_name);
	}
};
