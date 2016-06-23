#include "REESymbol.h"

HREESYMBOL  REESymbolObject::GetSymbol() override
{
    return HREESYMBOL(&info);
}

void*       REESymbolObject::GetSymbolAddress() override
{
}