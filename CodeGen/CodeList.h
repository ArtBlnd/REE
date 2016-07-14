#include "CodeGen.h"

#ifndef CODE_LIST
#define CODE_LIST

class CodeList
{
    struct objNext
    {
        Opcode*  opcode;
        objNext* next;
    }*first, *end;

public:
    void Initalize();
    void Distroy();

    void CopyToMemory(void* memory);
    uint32_t getTotalSize();
    uint32_t PushCode(Opcode* code);
};

#endif