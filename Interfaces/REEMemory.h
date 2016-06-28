#ifndef _REE_MEMORY_
#define _REE_MEMORY_

#include "../REE.h"

#include "REEObject.h"
#include "REEFactory.h"

#include "../Proxys/MemoryAPI.h"

#define DEFAULT_MEMORY_FLAG MEM_COMMIT
#define DEFAULT_PAGE_FLAG   PAGE_READWRITE

#define ADD_ADDRESS(source, dest) ((void*)((size_t)(source) + (size_t)(dest)))

class REEFactoryObject;

struct REE_MEMORY_INFO
{
    void*   address;
    size_t  size;
};

inline REE_MEMORY_INFO*  CreateMemoryInfo(void* pAddress, size_t size);
inline REE_MEMORY_INFO*  GetMemoryInfo(HREEMEMORY memory);
inline void              DistroyMemoryInfo(REE_MEMORY_INFO* memoryInfo);

class REEMemoryObject : public REEMemory, public REEObject
{
    REEFactoryObject* parent;

    REE_MEMORY_INFO* infoReserved;

    HANDLE GetProcessHandle();
    void*  GetReservedMemory();
    void*  GetAllocatableMemory(size_t size);

public:
    REEMemoryObject(REEFactoryObject* parent, size_t size);
    void Initalize();
    void Distroy();

    void Allocate(HREEMEMORY* memory, size_t index, size_t size);
    void Distroy(HREEMEMORY memory);
    void Read(HREEMEMORY memory, void* dest, size_t size);
    void Write(HREEMEMORY memory, void* source, size_t size);
    void* GetAddressOf(HREEMEMORY memory);
    size_t GetSizeOf(HREEMEMORY memory);
};

#endif