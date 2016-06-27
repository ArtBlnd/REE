#include "REEProcess.h"

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
	SAFE_CLOSE(hProcessSnap);
	return result;
}

inline REE_PROCESS_INFO    OpenProcess(char* nameProcess)
{
    REE_PROCESS_INFO info;

    DWORD            idProcess = NULL;
    HANDLE           hProcess = NULL;

    idProcess = FindProcessId(nameProcess);
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcessId);

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