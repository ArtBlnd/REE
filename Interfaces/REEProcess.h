#ifndef _REE_PROCESS_
#define _REE_PROCESS_

#include "../REE.h"

struct REE_PROCESS_INFO
{
    HANDLE      hProcess;
    uint32_t    idProcess;
    char*       nameProcess;
};

inline uint32_t            REEGetCurrnetPid();
inline HANDLE              REEGetCurrentProcess();

REE_PROCESS_INFO           GetInfoProcess(char* nameProcess);
void                       CloseProcess(REE_PROCESS_INFO info);

#endif