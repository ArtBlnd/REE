#include "REEMemory.h"

inline REE_MEMORY_INFO*  CreateMemoryInfo(void* pAddress, size_t size)
{
    REE_MEMORY_INFO *info = new REE_MEMORY_INFO();

    info->pAddress = pAddress;
    info->size = size;

    return info;
}

inline void              DistroyMemoryInfo(REE_MEMORY_INFO* memory)
{
    delete memory;
}

REEMemoryObject::REEFactoryObject(REEFactoryObject* parent)
{
    this->parent = parent;
}

void REEMemoryObject::Initalize() override
{

}

void REEMemoryObject::Release() override
{

}