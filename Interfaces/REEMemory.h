#ifndef _REE_MEMORY_
#define _REE_MEMORY_

#include "../REE.h"

#include "REEObject.h"
#include "REEFactory.h"

#define DEFAULT_RESERVE_MEMORY_FLAG  MEM_RESERVE
#define DEFAULT_RESERVE_PAGE_FLAG    PAGE_NOACESS
#define DEFAULT_MEMORY_FLAG          MEM_COMMIT  | MEM_RESERVE
#define DEFAULT_MEMORY_COMMIT_FLAG   MEM_COMMIT
#define DEFAULT_PAGE_FLAG            PAGE_READWRITE

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

class REEMemoryReservedObject : public REEMemoryReserved, public REEObject
{
    REEFactoryObject* parent;

    REE_MEMORY_INFO* infoReserved;
    struct REE_MEMORY_INFO_LIST{
        REE_MEMORY_INFO*      info;
        REE_MEMORY_INFO_LIST* next;
    }*first, *end;

    void PushInfo(REE_MEMORY_INFO* info);
    void DeleteInfo(REE_MEMORY_INFO* info);

    HANDLE GetProcessHandle();
    void*  GetReservedMemory();

public:
    REEMemoryReservedObject(REEFactoryObject* parent, size_t size);
    void Initalize();
    void Distroy();

    void Allocate(HREEMEMORY* memory, size_t index, size_t size);
    void Distroy(HREEMEMORY memory);
    void Read(HREEMEMORY memory, void* dest, size_t size);
    void Write(HREEMEMORY memory, void* source, size_t size);
    void* GetAddressOf(HREEMEMORY memory);
    size_t GetSizeOf(HREEMEMORY memory);
};

class REEMemoryObject : public REEMemory, public REEObject
{
    REEFactoryObject* parent;

    REE_MEMORY_INFO* infoMemory;
public:
    REEMemoryObject(REEFactoryObject* parent, size_t size);
    void Initalize();
    void Distroy();

    void Read(void* dest, size_t size);
    void Write(void* source, size_t size);
    void* GetAddressOf();
    size_t GetSizeOf();
    HREEMEMORY GetHandle();
}
#endif