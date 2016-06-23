#include "REEExecuter.h"


static NONE_PACKING unsigned char DefaultSymbolExecuterBinary[] =
{
	0x8D, 0x44, 0x24, 0x04,			/* lea eax, dword ptr[esp + 4]	 */
	0x8B, 0x08,						/* mov ecx, dword ptr[eax]		 */
	0x83, 0xC4, 0x04,				/* add esp, 4					 */
	0x8B, 0x1C, 0x24,				/* mov ebx, dword ptr[esp]		 */
	0x89, 0x18,						/* mov dword ptr[eax], ebx		 */
	0x6B, 0xC9, 0x04,				/* imul ecx, ecx, 4				 */
	0xB9, 0x00, 0x00, 0x00, 0x00,	/* mov ecx, PATCH_HERE			 */
	0x8B, 0x0C, 0x08,				/* mov ecx, dword ptr[eax + ecx] */
	0xFF, 0xE1						/* jmp ecx						 */
};

inline void PatchSymbolBaseAddress(void* Address)
{
    memcpy(&DefaultSymbolExecuterBinary[18], 
        &Address, sizeof(void*));

    return;
}
