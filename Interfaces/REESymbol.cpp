#include "REESymbol.h"

REE_SYMBOL_INFO* CreateSymbolInfo(char* nameProc, char* nameModule)
{
    REE_SYMBOL_INFO* info = new REE_SYMBOL_INFO();

    info->nameProc = nameProc;
    info->nameModule = nameModule;

    return info;
}
REE_SYMBOL_INFO* CreateSymbolInfo(void* address)
{
    REE_SYMBOL_INFO* info = new REE_SYMBOL_INFO();

    info->addrProc = address;

    return info;
}
REE_SYMBOL_INFO* GetSymbolInfo(HREESYMBOL symbol)
{
    return (REE_SYMBOL_INFO*)symbol;
}
inline void             DistroySymbolInfo(REE_SYMBOL_INFO* info)
{
    delete info;
}

REESymbolObject::REESymbolObject(REE_SYMBOL_INFO* info)
{
    this->info = info;
}

void REESymbolObject::Initalize()
{ }

void REESymbolObject::Distroy()
{ }

HREESYMBOL  REESymbolObject::GetSymbol()
{
    return HREESYMBOL(info);
}

void*       REESymbolObject::GetSymbolAddress()
{
    return (info->addrProc);
}