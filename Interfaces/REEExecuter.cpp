#include "REEExecuter.h"
#include "REEFactory.h"

void REEExecuterObject::Initalize()
{
    this->executer = (REEMemoryObject*)REEGetInstance()->CreateMemory(1024);
}

void REEExecuterObject::Distroy() 
{
    executer->Distroy();
}

REEExecuterObject::REEExecuterObject()
{
    REEExecuterObject((void*)DefaultExecuter, sizeof(DefaultExecuter));
}

REEExecuterObject::REEExecuterObject(void* binary, size_t size)
{
    this->Initalize();

    executer->Allocate(&memoryExecuter, 0, size);
    executer->Write(memoryExecuter, binary, size);
}

HREEMEMORY REEExecuterObject::GetExecuterMemory() 
{
    return executer->GetHandle();
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREEMEMORY memory, REE_EXECUTE_ARGUMENT* args) 
{
    
    return REE_EXECUTE_RESULT();
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREESYMBOL symbol, REE_EXECUTE_ARGUMENT* args) 
{
    return REE_EXECUTE_RESULT();
}