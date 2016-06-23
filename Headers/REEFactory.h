#ifndef _REE_FACTORY_
#define _REE_FACTORY_

#include "REE.h"
#include "REEProcess.h"

class REEFactoryObject : public REEFactory
{
    REE_PROCESS_INFO infoProcess;

public:
    REEFactoryObject(REE_PROCESS_INFO info);

    void Initalize() override;
    void Distroy() override;

    REESymbol* CreateSymbol(const char* nameProc, const char* nameModule) override;
    REESymbol* CreateSymbol(void* addrProc) override;
    REEMemory* CreateMemory() override;
    REEExecuter* CreateCustomExecuter(void* binary, size_t size) override;
    REEExecuter* CreateExecuter() override;

    REE_PROCESS_INFO GetProcessInfo();
};

#endif