#ifndef _REE_MEMORY_
#define _REE_MEMORY_

#include "REE.h"

struct REEMemoryInfo
{
    void*   address;
    size_t  size;
};

inline REEMemoryInfo*  CreateMemoryInfo(void* pAddress, size_t size);
inline void            DistroyMemoryInfo(REEMemoryInfo* memoryInfo);

class REEMemoryObject : public REEMemory
{
    REEFactory* parent;

public:
    REEFactoryObject(REEFactory* parent);
    void Initalize() override;
    void Release() override;

    void Allocate(HREEMEMORY memory, size_t size) override;
    void Distroy(HREEMEMORY memory) override;
    void Read(HREEMEMORY memory, void* dest, size_t size) override;
    void Write(HREEMEMORY memory, void* source, size_t size) override;
    size_t GetSize(HREEMEMORY memory) override;
};

#endif