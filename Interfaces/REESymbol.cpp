#include "REESymbol.h"

HREESYMBOL  REESymbolObject::GetSymbol()
{
    return HREESYMBOL(&info);
}

void*       REESymbolObject::GetSymbolAddress()
{
    return info.addrProc;
}