#ifndef _REE_MEMORY_
#define _REE_MEMORY_

#include "../REE.h"

#include "REEObject.h"
#include "REEFactory.h"

#include "../APIs/MemoryAPI.h"

#define DEFAULT_MEMORY_FLAG MEM_COMMIT
#define DEFAULT_PAGE_FLAG   PAGE_READWRITE

class REEFactoryObject;

struct REE_MEMORY_INFO
{
    void*   address;
    size_t  size;
};

struct REE_MEMORY_INFO_LIST : public REE_MEMORY_INFO
{
    REE_MEMORY_INFO_LIST* next;
};

inline REE_MEMORY_INFO*  CreateMemoryInfo(void* pAddress, size_t size);
inline REE_MEMORY_INFO*  GetMemoryInfo(HREEMEMORY memory);
inline void             DistroyMemoryInfo(REE_MEMORY_INFO* memoryInfo);

class REEMemoryObject : public REEMemory, public REEObject
{
    REEFactoryObject* parent;

    REE_MEMORY_INFO* infoReserved;
    REE_MEMORY_INFO_LIST* first;

    HANDLE GetProcessHandle();
    void*  GetReservedMemory();
    void*  GetAllocatableMemory(size_t size);

public:
    REEMemoryObject(REEFactoryObject* parent, size_t size);
    void Initalize();
    void Distroy();

    void Allocate(HREEMEMORY* memory, size_t size);
    void Distroy(HREEMEMORY memory);
    void Read(HREEMEMORY memory, void* dest, size_t size);
    void Write(HREEMEMORY memory, void* source, size_t size);
    void* GetAddressOf(HREEMEMORY memory);
    size_t GetSizeOf(HREEMEMORY memory);
};

#endif