#pragma once
#include <vector>

namespace Utils {

	void AttachConsole();
	void DetachConsole();
	bool ConsolePrint(const char* fmt, ...);
	uintptr_t* PointerResolver(uintptr_t ptr, std::vector<unsigned int> offsets);
	std::uint8_t* PatternScan(void* module, const char* signature);
}