#include "REEMemory.h"

REE_MEMORY_INFO*         CreateMemoryInfo(void* pAddress, size_t size)
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

HANDLE REEMemoryObject::GetProcessHandle()
{
    return (this->parent->GetProcessInfo().hProcess);
}

void* REEMemoryObject::GetReservedMemory()
{
    return (this->infoReserved.address);
}

REEMemoryObject::REEFactoryObject(REEFactoryObject* parent, size_t size)
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

void REEMemoryObject::Initalize() override
{
    return;
}

void REEMemoryObject::Release() override
{
    return;
}

void REEMemoryObject::Allocate(HREEMEMORY* memory, size_t size) override
{
    void* memoryAllocable = GetAllocableMemory(size);
    DEBUG_ASSERT(!memoryAllocable);

    void* memoryAddr = REEVirtualAlloc(
        GetProcessHandle(), 
        memoryAllocable, 
        size, 
        DEFAULT_MEMORY_FLAG, 
        DEFAULT_PAGE_FLAG);

    HREEMEMORY memoryObject = CreateMemoryInfo(memoryAddr, size);

    *memory = memoryObject;
}

void REEMemoryObject::Distroy(HREEMEMORY memory) override
{
    REEVirtualFreeEx(
        GetProcessHandle(),
        (REE_MEMORY_INFO*)memory->address,
        (REE_MEMORY_INFO*)memory->size,
        MEM_DECOMMIT
        );

    DistroyMemoryInfo(memory);
}

void REEMemoryObject::Read(HREEMEMORY memory, void* dest, size_t size) override
{

}

void REEMemoryObject::Write(HREEMEMORY memory, void source, size_t size)
{

}

void* REEMemoryObject::GetAddress(HREEMEMORY memory)
{

}

size_t GetSize(HREEMEMORY memory) override
{

}