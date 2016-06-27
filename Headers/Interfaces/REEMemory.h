#ifndef _REE_MEMORY_
#define _REE_MEMORY_

#include "REE.h"
#include "REEFactory.h"

struct REE_MEMORY_INFO
{
    void*   address;
    size_t  size;
};

inline REE_MEMORY_INFO*  CreateMemoryInfo(void* pAddress, size_t size);
inline void              DistroyMemoryInfo(REE_MEMORY_INFO* memoryInfo);

class REEMemoryObject : public REEMemory
{
    REEFactoryObject* parent;

public:
    REEFactoryObject(REEFactoryObject* parent);
    void Initalize() override;
    void Release() override;

    void Allocate(HREEMEMORY* memory, size_t size) override;
    void Distroy(HREEMEMORY memory) override;
    void Read(HREEMEMORY memory, void* dest, size_t size) override;
    void Write(HREEMEMORY memory, void* source, size_t size) override;
    void *GetAddress(HREEMEMORY memory);
    size_t GetSize(HREEMEMORY memory) override;
};

#endif