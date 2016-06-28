#include "REEProcess.h"
#include <TlHelp32.h>

inline uint32_t REEGetCurrentPid()
{
#ifdef _WINDOWS
	return GetCurrentProcessId();
#endif
}

inline HANDLE REEGetCurrentProcess()
{
#ifdef _WINDOWS
	return GetCurrentProcess();
#endif
}

inline DWORD FindProcessId(const char *nameProcess)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	DWORD result = FALSE;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (INVALID_HANDLE_VALUE == hProcessSnap)
		goto FAILED;

	if (!Process32First(hProcessSnap, &pe32))
		goto FAILED;

	do
	{
		if (0 == strcmp(nameProcess, pe32.szExeFile))
		{
			result = pe32.th32ProcessID;
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));

FAILED:
	if(hProcessSnap) CloseHandle(hProcessSnap);
	return result;
}

inline REE_PROCESS_INFO    GetInfoProcess(char* nameProcess)
{
    REE_PROCESS_INFO info;

    DWORD            idProcess = NULL;
    HANDLE           hProcess = NULL;

    idProcess = FindProcessId(nameProcess);
	if(idProcess != REEGetCurrentPid()) 
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, idProcess);
	else
		hProcess = REEGetCurrentProcess();

    DEBUG_ASSERT(!idProcess);
    DEBUG_ASSERT(!hProcess);

    info.nameProcess = nameProcess;
    info.idProcess = idProcess;
    info.hProcess = hProcess;

    return info;
}
inline void                CloseProcess(REE_PROCESS_INFO info)
{
    if(info.hProcess) CloseHandle(info.hProcess);
    
    return;
}