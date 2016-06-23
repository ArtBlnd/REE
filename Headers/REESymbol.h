#ifndef _REE_SYMBOL_
#define _REE_SYMBOL_

#include "REE.h"
#include "REEMemory.h"

static REEMemoryObject* symbolTable = NULL;

DEFUALT_PACKING_STRUCT REE_SYMBOL_INFO
{
    uint32_t index;
};

class REESymbolObject : public REESymbol
{
    REE_SYMBOL_INFO info;

public:
    HREESYMBOL  GetSymbol() override;
    void*       GetSymbolAddress();
};

#endif