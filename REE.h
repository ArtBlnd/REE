#ifndef _REE_
#define _REE_

#pragma once


#include <assert.h>
#include <stdint.h>
#include <vadefs.h>

#ifndef _MSC_VER
#warning VC++ Is Recommended.
#endif

#ifndef _WINDOWS
#error Only Supports Windows Platform. (just for now)
#else
#include <Windows.h>
#endif

#ifdef _WIN64
#error Only Supports Win32 Platform. (just for now)
#endif

#ifdef _DLL
#define REE_DLL_DEF __declspec(dllexport)
#else
#define REE_DLL_DEF __declspec(dllimport)
#endif

#ifdef _CRT_PACKING
/* set _CRT_PACKING as a defualt packing size */
#define DEFAULT_PACKING __declspec(align(_CRT_PACKING))
#else
/* Set int32_t size as a default packing size */
#define DEFAULT_PACKING __declspec(align(sizeof(int32_t)))
#endif

/* NONE_PACKING for patching. no byte paddings. */
#define NONE_PACKING __declspec(align(sizeof(1)))

#define NONE_PACKING_STRUCT NONE_PACKING struct
#define DEFAULT_PACKING_STRUCT DEFAULT_PACKING struct

#define DEBUG_ASSERT(x)

#ifdef INTERFACE
#undef INTERFACE
#endif
#define INTERFACE __interface

DEFAULT_PACKING_STRUCT REE_EXECUTE_RESULT
{
    /* Pointer Of Return Value */
    void*   retValue;
    /* Size Of Return Value */
    size_t  retSize;
};
DEFAULT_PACKING_STRUCT REE_EXECUTE_ARGUMENT{
    DEFAULT_PACKING_STRUCT
    {
        /* Pointer Of Argument */
        void*   argument;
        /* Size Of Argument */
        size_t  size;
    } argument;
    REE_EXECUTE_ARGUMENT* next;
}

#define REE_HANDLE_OBJECT(handlename) typedef class __##handlename## *handlename;
REE_HANDLE_OBJECT(HREEMEMORY);
REE_HANDLE_OBJECT(HREESYMBOL);

/* INTERFACE DEFINETION */

/* REEMemory Interfaces => Manages Memory */ 
INTERFACE REEMemoryReserved
{
    /* Allocate memory from targeted process. */
    void Allocate(HREEMEMORY* memory, size_t index, size_t size);
    /* Distroy memory from targeted process. */
    void Distroy(HREEMEMORY memory);
    /* Read memory from targeted process */
    void Read(HREEMEMORY memory, void* dest, size_t size);
    /* Write memory from targeted process */
    void Write(HREEMEMORY memory, void* source, size_t size);

    /* Get size of HREEMEMORY handle */
    size_t GetSizeOf(HREEMEMORY memory);
    /* Get address of HREEMEMORY handle */
    void* GetAddressOf(HREEMEMORY memory);
};

INTERFACE REEMemory
{
    /* Read memory from targeted process */
    void Read(void* dest, size_t size);
    /* Write memory from targeted process */
    void Write(void* source, size_t size);

    /* Get size of */
    size_t GetSizeOf();
    /* Get address of */
    void* GetAddressOf();
    /* Get memory handle */
    HREEMEMORY GetHandle();
};
/* REEExecuter Interface => Executes Memory */
INTERFACE REEExecuter
{
    REE_EXECUTE_RESULT Execute(HREEMEMORY memory, REE_EXECUTE_ARGUMENT* args);
    /* Execute with HREEMEMORY handle. */
    REE_EXECUTE_RESULT Execute(HREESYMBOL symbol, REE_EXECUTE_ARGUMENT* args);
    /* Execute with HREESYMBOL handle */
};
/* REESymbol Interface => Executes Symbol */
INTERFACE REESymbol
{
    HREESYMBOL GetSymbol();
    /* Get symbol handle */
    void* GetSymbolAddress();
    /* Get symbol address. */
};
/* REEFactory Interface => Manages REE Objects */
INTERFACE REEFactory
{
    REESymbol* CreateSymbol(char* nameProc, char* nameModule);
    /* Create symbol from factory with proc name, module name. */
    REESymbol* CreateSymbol(void* addrProc);
    /* Create symbol from factory wtih address of proc. */
    REEMemoryReserved* CreateReservedMemory(const size_t szReserve);
    /* Create reserved memory */
    REEMemory* CreateMemory(const size_t szMemory);
    /* Create memory */
    REEExecuter* CreateCustomExecuter(void* binary, size_t size);
    /* Create custom executer with custom execution binary. */
    REEExecuter* CreateExecuter();
    /* Create executer from factory */
};


/* Initalize Remote Execution Engine(REE) Instance*/
REE_DLL_DEF void        REEInitalize(char* nameProcess);
/* Release Remote Execution Engine(REE) Instance*/
REE_DLL_DEF void        REERelease();
/* Get REE instance that already registered. */
REE_DLL_DEF REEFactory* REEGetInstance();

#endif