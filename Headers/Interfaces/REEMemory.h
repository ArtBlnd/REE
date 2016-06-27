#ifndef _REE_MEMORY_
#define _REE_MEMORY_

#include "REE.h"
#include "REEObject.h"
#include "REEFactory.h"

#define DEFAULT_MEMORY_FLAG MEM_COMMIT
#define DEFUALT_PAGE_FLAG   PAGE_READWRITE

struct REE_MEMORY_INFO
{
    void*   address;
    size_t  size;
};

struct REE_MEMORY_INFO_LIST : public REE_MEMORY_INFO
{
    REE_MEMORY_INFO_LIST* next;
};

REE_MEMORY_INFO*         CreateMemoryInfo(void* pAddress, size_t size);
inline REE_MEMORY_INFO*  GetMemoryInfo(HREEMEMORY memory);
inline void              DistroyMemoryInfo(REE_MEMORY_INFO* memoryInfo);

class REEMemoryObject : public REEMemory, public REEObject
{
    REEFactoryObject* parent;

    REE_MEMORY_INFO infoReserved;
    REE_MEMORY_INFO_LIST *first;

    HANDLE GetProcessHandle();
    void*  GetReservedMemory();
    void*  GetAllocatableMemory();

public:
    REEFactoryObject(REEFactoryObject* parent);
    void Initalize() override;
    void Release() override;

    void Allocate(HREEMEMORY* memory, size_t size) override;
    void Distroy(HREEMEMORY memory) override;
    void Read(HREEMEMORY memory, void* dest, size_t size) override;
    void Write(HREEMEMORY memory, void* source, size_t size) override;
    void* GetAddress(HREEMEMORY memory);
    size_t GetSize(HREEMEMORY memory) override;
};

#endif