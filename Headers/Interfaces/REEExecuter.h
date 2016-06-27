#ifndef _REE_EXECUTER_
#define _REE_EXECUTER_

#include "REE.h"
#include "REEObject.h"
#include "REEMemory.h"
#include "REEProcess.h"

inline void PatchSymbolBaseAddress(void* Address);

class REEExecuterObject : public REEExecuter, public REEObject
{
	REEMemoryObject *executer;

public:
	void Initalize() override;
	void Release() override;

	HREEMEMORY GetMemory() override;
    void SetCallConv(REE_CALL_TYPE conv) override;
    REE_EXECUTE_RESULT Execute(HREEMEMORY memory, REEArgsTable args) override;
    REE_EXECUTE_RESULT Execute(HREESYMBOL symbol, REEArgsTable args) override;
};

#endif
