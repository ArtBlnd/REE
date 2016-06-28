#include "REEFactory.h"

REEMemoryObject* globalMemory = nullptr;

NONE_PACKING unsigned char DefaultSymbolExecuterBinary[] =
{
	0x8D, 0x44, 0x24, 0x04,         /* lea eax, dword ptr[esp + 4]	 */
	0x8B, 0x08,	                    /* mov ecx, dword ptr[eax]		 */
	0x83, 0xC4, 0x04,	            /* add esp, 4	                 */
	0x8B, 0x1C, 0x24,               /* mov ebx, dword ptr[esp]       */
	0x89, 0x18,                     /* mov dword ptr[eax], ebx	     */
	0x6B, 0xC9, 0x04,	            /* imul ecx, ecx, 4              */
	0xB9, 0x00, 0x00, 0x00, 0x00,   /* mov ecx, PATCH_HERE	         */
	0x8B, 0x0C, 0x08,	            /* mov ecx, dword ptr[eax + ecx] */
	0xFF, 0xE1	                    /* jmp ecx	                     */
};

inline void PatchSymbolBaseAddress(void* Address)
{
    memcpy(&DefaultSymbolExecuterBinary[18], 
        &Address, sizeof(void*));

    return;
}

inline REEMemoryObject* GetGlobalAllocater() { return globalMemory; }

REEFactoryObject::REEFactoryObject(REE_PROCESS_INFO info)
{
    this->infoProcess = info;

    return;
}

void REEFactoryObject::Initalize()
{
    globalMemory = new REEMemoryObject(this, 4096);
    globalMemory->Initalize();
}

void REEFactoryObject::Distroy()
{
    globalMemory->Distroy();

    delete globalMemory;
}

REESymbol* REEFactoryObject::CreateSymbol(const char* nameProc, const char* nameModule)
{
    REE_SYMBOL_INFO info = CreateSymbolInfo(nameProc, nameModule);
    REESymbolObject* symbol = new REESymbolObject(info);

    SAFE_INITALIZE(symbol);

    return (REESymbol*)(symbol);
}

REESymbol* REEFactoryObject::CreateSymbol(void* addrProc)
{
    REE_SYMBOL_INFO info = CreateSymbolInfo(addrProc);
    REESymbolObject* symbol = new REESymbolObject(info);

    SAFE_INITALIZE(symbol);

    return (REESymbol*)(symbol);
}

REEMemory* REEFactoryObject::CreateMemory(const size_t szReserve)
{
    REEMemoryObject* memory = new REEMemoryObject(this, szReserve);

    SAFE_INITALIZE(memory);

    return (REEMemory*)(memory);
}

REEExecuter* REEFactoryObject::CreateCustomExecuter(void* binary, size_t size)
{
    return new REEExecuterObject();
}
REEExecuter* REEFactoryObject::CreateExecuter()
{
    return new REEExecuterObject();
}

REE_PROCESS_INFO REEFactoryObject::GetProcessInfo()
{
    return this->infoProcess;
}

