#include "REE.h"
#include "REEProcess.h"
#include "REEFactory.h"

bool isAlreadyCreated = false;
REEFactoryObject* factory = NULL;

inline void SetFactoryStats(bool stats)
{
    isAlreadyCreated = true;

    return;
}

REE_DLL_DEF void REEInitalize(const char* nameProcess)
{
    if(isAlreadyCreated) return nullptr;

    REE_PROCESS_INFO info = OpenProcess(nameProcess);
    factory = new REEFactoryObject(info);

    factory->Initalize();

    SetFactoryStats(true);
}

REE_DLL_DEF void REERelease()
{
    factory->Distory();
    delete factory;

    SetFactoryStats(false);
}

REE_DLL_DEF REEFactory* REECreateFactory(char* nameProcess)
{
    return (REEFactory*)factory;
}

#undef SAFE_CLOSE