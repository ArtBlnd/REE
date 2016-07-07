#include "REE.h"

#pragma comment(lib, "REE.lib")

int main()
{
    REEFactory* factory;
    REEMemory*  memory;

    HREEMEMORY memory_object;

    REEInitalize("test_memory_allocate.exe");
    factory = REEGetInstance();
    factory->CreateMemory(&memory, 1024);

    memory->Allocate(&memory_object, 0, 1024);
    if(memory->GetSizeOf(memory_object) != 1024)
    {
        return -1;
    }
    if(!memory->GetAddressOf(memory_object))
    {
        return -1;   
    }
    memory->Distroy(memory_object);

    REERelease();

    return 1;
}