#include "REEMemory.h"

inline REEMemoryInfo*  CreateMemoryInfo(void* pAddress, size_t size)
{
    REEMemoryInfo *info = new REEMemoryInfo();

    info->pAddress = pAddress;
    info->size = size;

    return info;
}

inline void            DistroyMemoryInfo(REEMemoryInfo* memory)
{
    delete memory;
}

