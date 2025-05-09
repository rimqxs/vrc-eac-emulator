#pragma once

enum class EmulatorStauts {
	REQUIRED_CLOSE,
	OK
};

class emulator_initializer {
public:
	static EmulatorStauts init();
};
