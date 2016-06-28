#include "REEMemory.h"

inline REE_MEMORY_INFO*  CreateMemoryInfo(void* pAddress, size_t size)
{
    REE_MEMORY_INFO* info = new REE_MEMORY_INFO;

    info->address = pAddress;
    info->size = size;

    return info;
}

inline REE_MEMORY_INFO*  GetMemoryInfo(HREEMEMORY memory)
{
    return (REE_MEMORY_INFO*)(memory);
}

inline void              DistroyMemoryInfo(REE_MEMORY_INFO* memory)
{
    delete memory;
}

HANDLE REEMemoryObject::GetProcessHandle()
{
    return (this->parent->GetProcessInfo().hProcess);
}

void* REEMemoryObject::GetReservedMemory()
{
    return (this->infoReserved->address);
}

void* GetAllocatableMemory(size_t size)
{
    return nullptr;
}

REEMemoryObject::REEMemoryObject(REEFactoryObject* parent, size_t size)
{
    this->parent = parent;

    void* preAllocMem = REEVirtualAllocEx(
        GetProcessHandle(), 
        nullptr, 
        size,
        MEM_RESERVE,
        PAGE_NOACCESS);

    infoReserved = CreateMemoryInfo(preAllocMem, size);
}

void REEMemoryObject::Initalize()
{
    return;
}

void REEMemoryObject::Distroy()
{
    DEBUG_ASSERT(!REEVirtualFreeEx(
        GetProcessHandle(), 
        infoReserved.address, 
        infoReserved.size, 
        MEM_RELEASE));

    return;
}

void REEMemoryObject::Allocate(HREEMEMORY* memory, size_t size)
{
    void* memoryAllocable = GetAllocatableMemory(size);
    DEBUG_ASSERT(!memoryAllocable);

    void* memoryAddr = REEVirtualAllocEx(
        GetProcessHandle(), 
        memoryAllocable, 
        size, 
        DEFAULT_MEMORY_FLAG, 
        DEFAULT_PAGE_FLAG);

    HREEMEMORY memoryObject = (HREEMEMORY)CreateMemoryInfo(memoryAddr, size);

    *memory = memoryObject;
}

void REEMemoryObject::Distroy(HREEMEMORY memory)
{
    REE_MEMORY_INFO* info = GetMemoryInfo(memory);

    REEVirtualFreeEx(
        GetProcessHandle(),
        info->address,
        info->size,
        MEM_DECOMMIT
        );

    DistroyMemoryInfo(info);
}

void REEMemoryObject::Read(HREEMEMORY memory, void* dest, size_t size)
{

}

void REEMemoryObject::Write(HREEMEMORY memory, void* source, size_t size)
{

}

void* REEMemoryObject::GetAddressOf(HREEMEMORY memory)
{
    return nullptr;
}

size_t REEMemoryObject::GetSizeOf(HREEMEMORY memory)
{
    return GetMemoryInfo(memory)->size;
}