#pragma once
#include <dxgi.h>
typedef long(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);


namespace Globals
{
	inline IDXGISwapChain* g_SwapChain = nullptr;
	inline Present oPresent = NULL;
	inline uintptr_t BaseProcess = NULL;
	inline uintptr_t HealthBase = NULL;
}
