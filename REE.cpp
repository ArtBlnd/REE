#include "REE.h"

#include "Interfaces/REEFactory.h"
#include "Interfaces/REEProcess.h"
#include "Interfaces/REEObject.h"
#include "Interfaces/REEMemory.h"
#include "Interfaces/REESymbol.h"
#include "Interfaces/REEExecuter.h"

bool isAlreadyCreated = false;
REEFactoryObject* factory = NULL;

inline void SetFactoryStats(bool stats)
{
    isAlreadyCreated = true;
}

REE_DLL_DEF void REEInitalize(char* nameProcess)
{
    if(isAlreadyCreated) return;

    REE_PROCESS_INFO info = GetInfoProcess(nameProcess);
    factory = new REEFactoryObject(info);

    factory->Initalize();

    SetFactoryStats(true);
}

REE_DLL_DEF void REERelease()
{
    factory->Distroy();
    delete factory;

    SetFactoryStats(false);
}

REE_DLL_DEF REEFactory* REEGetInstance()
{
    return (REEFactory*)factory;
}

#undef SAFE_CLOSE