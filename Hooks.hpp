#pragma once
#include <wtypes.h>
//typedefs

namespace Hooks 
{

	void Initialize();
	void Uninitialize();

	// Function Address
	inline uintptr_t* aApplyHealth = nullptr;
	inline uintptr_t* aFormChange1 = nullptr;
	inline uintptr_t* asub_173A560 = nullptr;

	// Hook Functions
	__int64 __fastcall hkApplyHealth(__int64 a1, int a2);
	__int64 __fastcall hkFormChange1(__int64 a1, float a2);
	char	__fastcall hksub_173A560(__int64* a1, float a2);

	// Function originals
	inline decltype(&hkApplyHealth) oApplyHealth = nullptr;
	inline decltype(&hkFormChange1) oFormChange1 = nullptr;
	inline decltype(&hksub_173A560) osub_173A560 = nullptr;
}