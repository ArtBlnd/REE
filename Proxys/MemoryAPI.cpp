#include "MemoryAPI.h"

void* REEVirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, size_t dwSize, DWORD flAllocationType, DWORD flProtect)
{
#ifdef _WIN32
    return VirtualAllocEx(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
#endif
}

BOOL REEVirtualFreeEx(HANDLE hProcess, LPVOID lpAddress, size_t dwSize, DWORD dwFreeType)
{
#ifdef _WIN32
    return VirtualFreeEx(hProcess, lpAddress, dwSize, dwFreeType);
#endif
}
