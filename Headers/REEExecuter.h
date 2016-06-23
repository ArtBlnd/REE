#ifndef _REE_EXECUTER_
#define _REE_EXECUTER_

#include "REE.h"
#include "REEObject.h"
#include "REEMemory.h"
#include "REEProcess.h"

inline void PatchSymbolBaseAddress(void* Address);

class REEExecuterObject : public REEExecuter
{
	REEMemoryObject *targetMemory;

public:
	void Initalize() override;
	void Release() override;

	HREEMEMORY GetMemory();
    void SetCallConv(REE_CALL_TYPE conv);
    REE_EXECUTE_RESULT Execute(HREEMEMORY memory, REEArgsTable args);
    REE_EXECUTE_RESULT Execute(HREESYMBOL symbol, REEArgsTable args);
};

#endif
