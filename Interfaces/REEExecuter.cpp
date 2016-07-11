#include "REEExecuter.h"
#include "REEFactory.h"

inline size_t GetTotalArgumentSize(REE_EXECUTE_ARGUMENT* arguments)
{
    size_t size = NULL;

    for(REE_EXECUTE_ARGUMENT* iterator = arguments; iterator->next == nullptr; iterator = iterator->next)
    {
        size += iterator->size;
    }

    return size;
}

void REEExecuterObject::Initalize()
{ }

void REEExecuterObject::Distroy() 
{ }

REEExecuterObject::REEExecuterObject()
{
    REEExecuterObject((void*)DefaultExecuter, sizeof(DefaultExecuter));
}

REEExecuterObject::REEExecuterObject(void* binary, size_t size)
{
    objectExecuter = new uint8_t[size];

    DEBUG_ASSERT(!memcpy_s(objectExecuter, size, binary, size));
    sizeExecuter = size;
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREEMEMORY memory, REE_EXECUTE_ARGUMENT* args) 
{
    size_t       TotalArgumentsSize = GetTotalArgumentSize(args);
    size_t       TotalExecuterSize  = sizeExecuter;

    void*        tmpMemory = new uint8_t[TotalArgumentsSize + TotalExecuterSize];
    size_t       tmpTotalWrittenSize = NULL;

    REEFactory*  instance = REEGetInstance();
    
    REEMemory*   MemExecuter = instance->CreateMemory(TotalArgumentsSize + TotalExecuterSize);
    REEMemory*   MemResult = instance->CreateMemory(DEFAULT_RESULT_SIZE);

    for(REE_EXECUTE_ARGUMENT* iterator = args; args->next == nullptr; args = args->next)
    {
        memcpy_s(
            ADD_ADDRESS(tmpMemory, tmpTotalWrittenSize), 
            args->size, 
            args->argument, 
            args->size);

        tmpTotalWrittenSize += args->size;
    }

    DEBUG_ASSERT(!objectExecuter);

    memcpy_s(
        ADD_ADDRESS(tmpMemory, tmpTotalWrittenSize), 
        TotalExecuterSize,
        objectExecuter,
        TotalExecuterSize);

    Executer->Write(tmpMemory, TotalArgumentsSize + TotalExecuterSize);
    Executer->GetAddressOf();


    delete[] tmpMemory;
    Executer->Distroy();
    Result->Distroy();

    return REE_EXECUTE_RESULT();
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREESYMBOL symbol, REE_EXECUTE_ARGUMENT* args) 
{
    for(REE_EXECUTE_ARGUMENT* iterator = args; args->next == nullptr; args = args->next)
    {

    }

    return REE_EXECUTE_RESULT();
}