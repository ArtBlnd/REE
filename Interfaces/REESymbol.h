#ifndef _REE_SYMBOL_
#define _REE_SYMBOL_

#include "../REE.h"
#include "REEObject.h"
#include "REEMemory.h"

struct REE_SYMBOL_INFO
{
    void* addrProc;
    char* nameProc;
    char* nameModule;
};

inline REE_SYMBOL_INFO CreateSymbolInfo(const char* nameProc, const char* nameModule);
inline REE_SYMBOL_INFO CreateSymbolInfo(void* address);
inline void            DistroySymbolInfo(REE_SYMBOL_INFO info);

class REESymbolObject : public REESymbol, public REEObject
{
    REE_SYMBOL_INFO info;

public:
    REESymbolObject(REE_SYMBOL_INFO info);
    void Initalize();
    void Distroy();

    HREESYMBOL  GetSymbol();
    void*       GetSymbolAddress();
};

#endif