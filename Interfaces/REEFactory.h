#ifndef _REE_FACTORY_
#define _REE_FACTORY_

#include "../REE.h"

#include "REEExecuter.h"
#include "REEObject.h"
#include "REEProcess.h"
#include "REESymbol.h"
#include "REEMemory.h"


class REEMemoryObject;

inline REEMemoryObject* GetGlobalAllocater();

class REEFactoryObject : public REEFactory, public REEObject
{
    REE_PROCESS_INFO infoProcess;

public:
    REEFactoryObject(REE_PROCESS_INFO info);

    void Initalize();
    void Distroy();

    REESymbol* CreateSymbol(const char* nameProc, const char* nameModule);
    REESymbol* CreateSymbol(void* addrProc);
    REEMemory* CreateMemory(const size_t szReserve);
    REEExecuter* CreateCustomExecuter(void* binary, size_t size);
    REEExecuter* CreateExecuter();

    REE_PROCESS_INFO GetProcessInfo();
};

#endif