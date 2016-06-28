#include "REEExecuter.h"
#include "REEFactory.h"

void REEExecuterObject::Initalize()
{
    this->allocater = (REEMemoryObject*)REEGetInstance()->CreateMemory(1024);
}

void REEExecuterObject::Distroy() 
{
    allocater->Distroy(executer);
    allocater->Distroy();
}

REEExecuterObject::REEExecuterObject()
{
    REEExecuterObject((void*)DefaultExecuter, sizeof(DefaultExecuter));
}

REEExecuterObject::REEExecuterObject(void* binary, size_t size)
{
    HREEMEMORY memoryExecuter;

    this->Initalize();

    allocater->Allocate(&memoryExecuter, 0, size);
    allocater->Write(memoryExecuter, binary, size);

    this->executer = memoryExecuter;
}

HREEMEMORY REEExecuterObject::GetExecuterMemory() 
{
    return executer;
}

void REEExecuterObject::SetCallConv(REE_CALL_TYPE conv) 
{
    allocater->Distroy(executer);
    
    unsigned char* newbinary;

    switch(conv)
    {
        case REE_CALL_TYPE::CDECL_CONV:
        break;
        case REE_CALL_TYPE::STDCALL_CONV:
        break;
    }

    allocater->Allocate(&executer, 0, sizeof(newbinary));
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREEMEMORY memory, REE_EXECUTE_ARGUMENT* args) 
{
    return REE_EXECUTE_RESULT();
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREESYMBOL symbol, REE_EXECUTE_ARGUMENT* args) 
{
    return REE_EXECUTE_RESULT();
}