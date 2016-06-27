#ifndef _REE_FACTORY_
#define _REE_FACTORY_

#include "REE.h"
#include "REEObject.h"
#include "REEProcess.h"
#include "REEMemory.h"
#include "REESymbol.h"

inline REEExecuterObject* GetGlobalAllocater();

class REEFactoryObject : public REEFactory, public REEObject
{
    REE_PROCESS_INFO infoProcess;

public:
    REEFactoryObject(REE_PROCESS_INFO info);

    void Initalize() override;
    void Distroy() override;

    REESymbol* CreateSymbol(const char* nameProc, const char* nameModule) override;
    REESymbol* CreateSymbol(void* addrProc) override;
    REEMemory* CreateMemory(const size_t szReserve) override;
    REEExecuter* CreateCustomExecuter(void* binary, size_t size) override;
    REEExecuter* CreateExecuter() override;

    REE_PROCESS_INFO GetProcessInfo();
};

#endif