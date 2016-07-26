#include "REEExecuter.h"
#include "REEFactory.h"
#include "REESymbol.h"

#include "../CodeGen/CodeGen.h"
#include "../CodeGen/CodeList.h"

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

REE_EXECUTE_RESULT REEExecuterObject::Execute(REEMemory* memory, REE_EXECUTE_ARGUMENT* args, uint32_t szResult) 
{
    size_t       TotalArgumentsSize = GetTotalArgumentSize(args);
    size_t       TotalExecuterSize  = sizeExecuter;

    REEFactory*  instance = REEGetInstance();
    
    REEMemory*   MemExecuter = instance->CreateMemory(TotalArgumentsSize + TotalExecuterSize);
    REEMemory*   MemResult;

    if(szResult < 8) szResult = 8;
    MemResult = instance->CreateMemory(szResult);

    CodeList     opcodes;

    opcodes.Initalize();
    opcodes.PushCode(InstHelper::SUB(
        RM_REG32::ESP, 
        0, 
        MOD_REG32::NONE_REFERENCED_DATA, 
        TotalArgumentsSize)
    );
    /* Reserve ESP =>> sub esp, TotalArgumentsSize*/

    try
    {
        uint32_t TotalWritten = NULL;
        
        /* move arguments to stack */
        for(REE_EXECUTE_ARGUMENT* iterator = args; args->next == nullptr; args = args->next)
        {
            opcode.PushCode(
                InstHelper::MOV(
                    RM_REG32::ESP, 
                    args->argument.size + TotalWritten, 
                    MOD_REG32::REFERENCED_WITH_DISP32, 
                    args->argument.argument)
            );
            /* mov [esp + args->argument.size + TotalWritten], args->argument.argument */
            /* create instructions manually. */

            TotalWritten += args->argument.size;
        }

        DEBUG_ASSERT(!objectExecuter);

        opcode.PushCode(
            InstHelper::CALL()
        );
        /* call memory->GetAddressOf() */
        opcode.PushCode(
            InstHelper::MOV(
                RM_REG32::ECX,
                0,
                MOD_REG32::NONE_REFERENCED_DATA,
                MemResult->GetAddressOf());
        );
        /* mov ecx, MemResult->GetAddressOf() */
        opcode.PushCode(
            InstHelper::MOV(
                RM_REG32::ECX,
                0,
                MOD_REG32::REFERENCED_DATA,
                RM_REG32::EAX)
        );
        /* mov [ecx], eax */
        opcode.PushCode(
            InstHelper::RET(4)
        );
        /* you have to restore esp becouse CreateRemoteThread function use LPVOID argument. */ 
        /* RET 4 */
    }
    catch(...)
    {
        /* TODO HERE: exception handler */
    }

    uint8_t byteCodes = new uint8_t[opcodes.getTotalSize()];

    opcodes.CopyToMemory(byteCodes);
    Executer->Write(byteCodes, opcodes.getTotalSize());
    
    /* TODO HERE: Execute "Executer" memory with CreateRemoteThread. */
    /* Also WaitForSingleObject. */

    REE_EXECUTE_RESULT result;

    result.retSize = szResult;
    result.retValue = new uint8_t[szResult];
    Result->Read(result.retValue, szResult);

    delete[] byteCodes;
    opcodes.Distroy();
    Executer->Distroy();
    Result->Distroy();

    /* doesn't seems really good that way return Executer result.*/
    return result;
}

REE_EXECUTE_RESULT REEExecuterObject::Execute(HREESYMBOL symbol, REE_EXECUTE_ARGUMENT* args) 
{
    return this->Execute(GetSymbolInfo(symbol)->addrProc, args);
}