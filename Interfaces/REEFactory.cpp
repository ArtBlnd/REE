#include "REEFactory.h"

REEFactoryObject::REEFactoryObject(REE_PROCESS_INFO info)
{
    this->infoProcess = info;

    return;
}

void REEFactoryObject::Initalize()
{
}

void REEFactoryObject::Distroy()
{
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

REEMemory* REEFactoryObject::CreateMemory(const size_t szReserve)
{
    REEMemoryObject* memory = new REEMemoryObject(this, szReserve);

    SAFE_INITALIZE(memory);

    return (REEMemory*)(memory);
}

REEExecuter* REEFactoryObject::CreateCustomExecuter(void* binary, size_t size)
{
    return new REEExecuterObject();
}
REEExecuter* REEFactoryObject::CreateExecuter()
{
    return new REEExecuterObject();
}

REE_PROCESS_INFO REEFactoryObject::GetProcessInfo()
{
    return this->infoProcess;
}

