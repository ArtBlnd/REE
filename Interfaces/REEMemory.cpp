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

void REEMemoryObject::Allocate(HREEMEMORY* memory, size_t index, size_t size)
{

    void* memoryAddr = REEVirtualAllocEx(
        GetProcessHandle(), 
        ADD_ADDRESS(infoReserved->address, index), 
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
    SIZE_T size_read;

    ReadProcessMemory(GetProcessHandle(), GetMemoryInfo(memory)->address, dest, size, &size_read);

    DEBUG_ASSERT(size_read != size);
}

void REEMemoryObject::Write(HREEMEMORY memory, void* source, size_t size)
{
    SIZE_T size_written;

    WriteProcessMemory(GetProcessHandle(), GetMemoryInfo(memory)->address, source, size, &size_written);

    DEBUG_ASSERT(size_written != size);
}

void* REEMemoryObject::GetAddressOf(HREEMEMORY memory)
{
    return GetMemoryInfo(memory)->address;
}

size_t REEMemoryObject::GetSizeOf(HREEMEMORY memory)
{
    return GetMemoryInfo(memory)->size;
}