#include "REEFactory.h"

REEFactoryObject::REEFactoryObject(REE_PROCESS_INFO info)
{
    this->infoProcess = info;

    return;
}

void REEFactoryObject::Initalize()
{
    return;
}

void REEFactoryObject::Distroy()
{
    return;
}

REESymbol* REEFactoryObject::CreateSymbol(char* nameProc, char* nameModule)
{
    REE_SYMBOL_INFO* info = CreateSymbolInfo(nameProc, nameModule);
    REESymbolObject* symbol = new REESymbolObject(info);

    SAFE_INITALIZE(symbol);

    return (REESymbol*)(symbol);
}

REESymbol* REEFactoryObject::CreateSymbol(void* addrProc)
{
    REE_SYMBOL_INFO* info = CreateSymbolInfo(addrProc);
    REESymbolObject* symbol = new REESymbolObject(info);

    SAFE_INITALIZE(symbol);

    return (REESymbol*)(symbol);
}
REEMemoryReserved* REEFactoryObject::CreateReservedMemory(const size_t szReserve)
{
    REEMemoryReservedObject* memory = new REEMemoryReservedObject(this, szReserve);

    SAFE_INITALIZE(memory);

    return (REEMemoryReserved*)(memory);
}
REEMemory* REEFactoryObject::CreateMemory(const size_t szMemory)
{
    REEMemoryObject* memory = new REEMemoryObject(this, szMemory);

    SAFE_INITALIZE(memory);

    return (REEMemory*)(memory);
}

REEExecuter* REEFactoryObject::CreateCustomExecuter(void* binary, size_t size)
{
    return new REEExecuterObject(binary, size);
}
REEExecuter* REEFactoryObject::CreateExecuter()
{
    return new REEExecuterObject();
}

REE_PROCESS_INFO REEFactoryObject::GetProcessInfo()
{
    return this->infoProcess;
}

