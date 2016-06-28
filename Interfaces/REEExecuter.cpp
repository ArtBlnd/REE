#include "REEExecuter.h"

void REEExecuterObject::Initalize()
{

}

void REEExecuterObject::Distroy() 
{

}

HREEMEMORY REEExecuterObject::GetExecuterMemory() 
{
    return executer;
}

void REEExecuterObject::SetCallConv(REE_CALL_TYPE conv) 
{

}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREEMEMORY memory, REE_EXECUTE_ARGUMENT* args) 
{
    return REE_EXECUTE_RESULT();
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREESYMBOL symbol, REE_EXECUTE_ARGUMENT* args) 
{
    return REE_EXECUTE_RESULT();
}