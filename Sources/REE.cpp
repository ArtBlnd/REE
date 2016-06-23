#include "REE.h"
#include "REEProcess.h"
#include "REEFactory.h"

REE_DLL_DEF HREEFACTORY REECreateFactory(char* nameProcess)
{
    REE_PROCESS_INFO info = OpenProcess(nameProcess);
    REEFactory* factory = new REEFactoryObject(info);

    factory->Initalize();

    return factory;
}

#undef SAFE_CLOSE