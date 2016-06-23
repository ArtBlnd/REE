#ifndef _REE_
#define _REE_

#ifndef _MSC_VER
#warning VC++ Is Recommended.
#endif

#ifndef _WINDOWS
#error Only Supports Windows Platform.
#endif

#ifdef _WIN64
#error Only Supports Win32 Platform. (just for now)
#endif

/* Only Assert When Debugging. */
#ifdef _DEBUG
#include <assert.h>
#define DEBUG_ASSERT(condit) if(condit) assert();
#endif
#define DEBUG_ASSERT(condit)

#include <Windows.h>
#include <stdint.h>
#include <vadefs.h>

#ifdef _DLL
#define REE_DLL_DEF __declspec(dllexport) __cdecl
#else
#define REE_DLL_DEF __declspec(dllimport) __cdecl
#endif

#ifdef _CRT_PACKING
/* set _CRT_PACKING as a defualt packing sise(8 bytes) */
#define DEFAULT_PACKING __declspec(align(_CRT_PACKING))
#else
/* Set int32_t size as a default packing size */
#define DEFAULT_PACKING __declspec(align(sizeof(int32_t)))
#endif

/* NONE_PACKING for patching. no byte paddings. */
#define NONE_PACKING __declspec(align(sizeof(1)))

#define NONE_PACKING_STRUCT NONE_PACKING struct
#define DEFAULT_PACKING_STRUCT DEFAULT_PACKING struct
#define INTERFACE __interface

enum class REE_CALL_TYPE : uint32_t
{
    STDCALL = 1 << 0,
    CDECL = 1 << 1
};

DEFAULT_PACKING_STRUCT REE_EXECUTE_RESULT
{
    bool    isSuccessed;

    size_t  retSize;
    void*   retValue;
};
DEFAULT_PACKING_STRUCT REE_EXECUTE_ARGUMENT
{
    void*   argument;
    size_t  size;
};

typedef class __REE_HANDLE* REEHANDLE;
#define REE_HANDLE_OBJECT(handlename) typedef class REEHANDLE* handlename;
REE_HANDLE_OBJECT(HREEMEMORY);
REE_HANDLE_OBJECT(HREESYMBOL);

/* INTERFACE DEFINETION */
INTERFACE REEObject
{
    void Release();
    void Initalize();
};
#define REE_INTERFACE_OBJECT(classname, interfacename) INTERFACE classname : public interfacename

/* REEMemory Interface => Manages Memory */ 
REE_INTERFACE_OBJECT(REEMemory, REEObject)
{
    void Allocate(HREEMEMORY* memory, size_t size);
    void Distroy(HREEMEMORY memory);
    void Read(HREEMEMORY memory, void* dest, size_t size);
    void Write(HREEMEMORY memory, void* source, size_t size);

    size_t GetSizeOf(HREEMEMORY memory);
    void* GetAddressOf(HREEMEMORY memory);
};
/* REEExecuter Interface => Executes Memory */
REE_INTERFACE_OBJECT(REEExecuter, REEObject)
{
    HREEMEMORY GetMemory();
    void SetCallConv(REE_CALL_TYPE conv);
    REE_EXECUTE_RESULT Execute(HREEMEMORY memory, REEArgsTable args);
    REE_EXECUTE_RESULT Execute(HREESYMBOL symbol, REEArgsTable args);
};
/* REESymbol Interface => Executes Symbol */
REE_INTERFACE_OBJECT(REESymbol, REEObject)
{
    HREESYMBOL GetSymbol();
    void* GetSymbolAddress();
};
/* REEFactory Interface => Manages REE Objects */
REE_INTERFACE_OBJECT(REEFactory, REEObject)
{
    REESymbol* CreateSymbol(const char* nameProc, const char* nameModule);
    REESymbol* CreateSymbol(void* addrProc);
    REEMemory* CreateMemory();
    REEExecuter* CreateCustonExecuter(void* binary, size_t size);
    REEExecuter* CreateExecuter();
};

/* Create REEFactory Object */
REE_DLL_DEF REEFactory* REECreateFactory(const char* nameProcess);

#undef REE_DLL_DEF

#endif