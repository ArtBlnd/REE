#include "REEFactory.h"

REEExecuterObject* GlobalSymbolExecuter = nullptr;

REEFactoryObject::REEFactoryObject(REE_PROCESS_INFO info)
{
    this->infoProcess = info;

    return;
}

void REEFactoryObject::Initalize()
{
    GlobalExecuter = new REEExecuterObject();
}
void REEFactoryObject::Distroy()
{

}

REESymbol* REEFactoryObject::CreateSymbol(const char* nameProc, const char* nameModule) override
{

}

REESymbol* REEFactoryObject::CreateSymbol(void* addrProc) override
{

}

REEMemory* REEFactoryObject::CreateMemory() override
{

}

REEExecuter* REEFactoryObject::CreateCustomExecuter(void* binary, size_t size) override
{

}
REEExecuter* REEFactoryObject::CreateExecuter() override
{

}

REE_PROCESS_INFO REEFactoryObject::GetProcessInfo()
{
    return this->infoProcess;
}

