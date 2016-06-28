#ifndef _REE_EXECUTER_
#define _REE_EXECUTER_

#include "../REE.h"
#include "REEObject.h"
#include "REEMemory.h"
#include "REEProcess.h"

/* Pre Define Class */
class REEMemoryObject;

NONE_PACKING const unsigned char DefaultExecuter[] = 
{
	0x90
};

class REEExecuterObject : public REEExecuter, public REEObject
{
	HREEMEMORY executer;
	REEMemoryObject* allocater;

public:
	void Initalize();
	void Distroy();

	REEExecuterObject();
	REEExecuterObject(void* binary, size_t size);

	HREEMEMORY GetExecuterMemory();
    void SetCallConv(REE_CALL_TYPE conv);
    REE_EXECUTE_RESULT Execute(HREEMEMORY memory, REE_EXECUTE_ARGUMENT* args);
    REE_EXECUTE_RESULT Execute(HREESYMBOL symbol, REE_EXECUTE_ARGUMENT* args);
};

#endif
