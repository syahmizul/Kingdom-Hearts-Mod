//HRESULT hkPresent(IDXGISwapChain* pSwapChain,
//    UINT SyncInterval,
//    UINT Flags
//)
//{
//    if (!g_SwapChain)
//        g_SwapChain = pSwapChain;
//
//
//    // TODO: Move these into game logic.
//
//    uintptr_t* HealthBase = Utils::PointerResolver(BaseProcess, { 0x0A70B4A0,0x48,0x3E8 });
//    BYTE* HealthPtr = (BYTE*)((uintptr_t)HealthBase + 0x5FC);
//    if (HealthBase && HealthPtr )
//        *HealthPtr = 255;
//    return oPresent(pSwapChain,SyncInterval,Flags);
//}