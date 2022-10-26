// dllmain.cpp : Defines the entry point for the DLL application.
#include "includes.h"
#include "Utils.hpp"
#include "Globals.h"
#include "InputSys.hpp"
#include "Hooks.hpp"

DWORD WINAPI OnDllAttach(LPVOID base)
{
   
    Utils::AttachConsole();
    Globals::BaseProcess = (uintptr_t)GetModuleHandleA("Kingdom Hearts III.exe");
    /*InputSys::Get().Initialize();*/
    Hooks::Initialize();
    
    while (1)
        Sleep(1000);
        
    FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);

}

BOOL WINAPI OnDllDetach()
{
    
    Utils::DetachConsole();
    Hooks::Uninitialize();
    return TRUE;
}

BOOL WINAPI DllMain
(
    _In_      HINSTANCE hinstDll,
    _In_      DWORD     fdwReason,
    _In_opt_  LPVOID    lpvReserved
)
{
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:

        DisableThreadLibraryCalls(hinstDll);
        CreateThread(nullptr, 0, OnDllAttach, hinstDll, 0, nullptr);
        return TRUE;
    case DLL_PROCESS_DETACH:
        if (lpvReserved == nullptr)
            return OnDllDetach();
        return TRUE;
    default:
        return TRUE;
    }
}


