#ifndef _REE_PROCESS_
#define _REE_PROCESS_

DEFAULT_PACKING_STRUCT REE_PROCESS_INFO
{
    HANDLE      hProcess;
    uint32_t    idProcess;
    char*       nameProcess;
};

inline uint32_t            REEGetCurrnetPid();
inline HANDLE              REEGetCurrentProcess();

inline REE_PROCESS_INFO    OpenProcess(char* nameProcess);
inline void                CloseProcess(REE_PROCESS_INFO info);

#endif