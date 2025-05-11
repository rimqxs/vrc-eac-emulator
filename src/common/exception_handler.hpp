#pragma once

#include <crashlog/parser.h>
#include <winuser.h>

#include <sstream>

class exception_handler {
	static LONG WINAPI TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo) {
		crashlog::initSym();
		crashlog::loadSym();

		auto info = crashlog::parseException(ExceptionInfo);
		std::ostringstream stream;
		stream << crashlog::exceptionInfoToString(info) << std::endl;
		stream << std::endl;
		stream << "StackTrace:" << std::endl;
		stream << crashlog::createStackTraceString(info) << std::endl;
		stream << std::endl;

		printf("%s\n", stream.str().c_str());
		MessageBoxA(nullptr, stream.str().c_str(), "Crashed!", MB_OK | MB_ICONERROR);

		return 0;
	}

public:
	static void init() {
		SetUnhandledExceptionFilter(&TopLevelExceptionFilter);
	}
};
