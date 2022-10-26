#pragma once
#include <stdio.h>
#include <Windows.h>
#include <dxgi.h>

#if defined _DEBUG
	#if defined _M_X64
	#pragma comment(lib, "minhook/lib/Debug/libMinHook.x64.lib") 
	#elif defined _M_IX86
	#pragma comment(lib, "minhook/lib/Debug/libMinHook.x86.lib") 
	#endif
#else
	#if defined _M_X64
	#pragma comment(lib, "minhook/lib/Release/libMinHook.x64.lib") 
	#elif defined _M_IX86
	#pragma comment(lib, "minhook/lib/Release/libMinHook.x86.lib") 
	#endif
#endif
