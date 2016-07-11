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

HANDLE REEMemoryReservedObject::GetProcessHandle()
{
    return (this->parent->GetProcessInfo().hProcess);
}

void* REEMemoryReservedObject::GetReservedMemory()
{
    return (this->infoReserved->address);
}

REEMemoryReservedObject::REEMemoryReservedObject(REEFactoryObject* parent, size_t size)
{
    this->parent = parent;

    void* preAllocMem = VirtualAllocEx(
        GetProcessHandle(), 
        nullptr, 
        size,
        DEFAULT_RESERVE_MEMORY_FLAG,
        DEFAULT_RESERVE_PAGE_FLAG);
    DEBUG_ASSERT(!preAllocMem);

    infoReserved = CreateMemoryInfo(preAllocMem, size);
}

void REEMemoryReservedObject::Initalize()
{ }

void REEMemoryReservedObject::Distroy()
{
    DEBUG_ASSERT(!VirtualFreeEx(
        GetProcessHandle(), 
        infoReserved.address, 
        infoReserved.size, 
        MEM_RELEASE));

    return;
}

void REEMemoryReservedObject::Allocate(HREEMEMORY* memory, size_t index, size_t size)
{

    void* memoryAddr = VirtualAllocEx(
        GetProcessHandle(), 
        ADD_ADDRESS(GetReservedMemory(), index), 
        size, 
        DEFAULT_MEMORY_COMMIT_FLAG, 
        DEFAULT_PAGE_FLAG);

    HREEMEMORY memoryObject = (HREEMEMORY)CreateMemoryInfo(memoryAddr, size);

    *memory = memoryObject;
}

void REEMemoryReservedObject::Distroy(HREEMEMORY memory)
{
    REE_MEMORY_INFO* info = GetMemoryInfo(memory);

    DEBUG_ASSERT(!VirtualFreeEx(
        GetProcessHandle(),
        info->address,
        info->size,
        MEM_DECOMMIT));

    DistroyMemoryInfo(info);
}

void REEMemoryReservedObject::Read(HREEMEMORY memory, void* dest, size_t size)
{
    SIZE_T size_read;

    ReadProcessMemory(GetProcessHandle(), GetMemoryInfo(memory)->address, dest, size, &size_read);

    DEBUG_ASSERT(size_read != size);
}

void REEMemoryReservedObject::Write(HREEMEMORY memory, void* source, size_t size)
{
    SIZE_T size_written;

    WriteProcessMemory(GetProcessHandle(), GetMemoryInfo(memory)->address, source, size, &size_written);

    DEBUG_ASSERT(size_written != size);
}

void* REEMemoryReservedObject::GetAddressOf(HREEMEMORY memory)
{
    return GetMemoryInfo(memory)->address;
}

size_t REEMemoryReservedObject::GetSizeOf(HREEMEMORY memory)
{
    return GetMemoryInfo(memory)->size;
}

REEMemoryObject::REEMemoryObject(REEFactoryObject* parent, size_t size)
{
    this->parent = parent;

    void* AllocMem = VirtualAllocEx(
        GetProcessHandle(), 
        nullptr, 
        size,
        DEFAULT_MEMORY_FLAG,
        DEFAULT_PAGE_FLAG);
    DEBUG_ASSERT(!AllocMem);

    this->infoMemory = CreateMemoryInfo(AllocMem, size);
}

void REEMemoryObject::Initalize()
{ }

void REEMemoryObject::Distroy()
{
    DEBUG_ASSERT(!VirtualFreeEx(GetProcessHandle()));
}

void REEMemoryObject::Read(void* dest, size_t size)
{
    SIZE_T size_read;

    ReadProcessMemory(GetProcessHandle(), GetMemoryInfo(infoMemory)->address, dest, size, &size_read);

    DEBUG_ASSERT(size_read != size);
}

void REEMemoryObject::Write(void* source, size_t size)
{
    SIZE_T size_written;

    WriteProcessMemory(GetProcessHandle(), GetMemoryInfo(infoMemory)->address, source, size, &size_written);

    DEBUG_ASSERT(size_written != size);
}

void* REEMemoryObject::GetAddressOf()
{
    return infoMemory->address;
}

size_t GetSizeOf()
{
    return infoMemory->size;
}

HREEMEMORY REEMemoryObject::GetHandle()
{
    return (HREEMEMORY)infoMemory;
}