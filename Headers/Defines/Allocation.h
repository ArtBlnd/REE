#ifndef _ALLOCATION_
#define _ALLOCATION_

#include "REE.h"

/* Memory Management in OS Definion For Multiplatform */

inline BOOL REEVirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, size_t dwSize, DWORD flAllocationType, DWORD flProtect);
inline BOOL REEVirtualFreeEx(HANDLE hPRocess, LPVOID lpAddress, size_t dwSize, DWORD dwFreeType);

#define MEM_DECOMMIT            0x4000
#define MEM_RELEASE             0x8000

#define MEM_COMMIT              0x00001000
#define MEM_RESERVE             0x00002000
#define MEM_RESET               0x00080000
#define MEM_RESET_UNDO          0x10000000

#define MEM_LARGE_PAGES         0x20000000
#define MEM_PHYSICAL            0x00400000
#define MEM_TOP_DOWN            0x00100000

#define PAGE_EXECUTE            0x10
#define PAGE_EXECUTE_READ       0x20
#define PAGE_EXECUTE_READWRITE  0x40
#define PAGE_EXECUTE_WRITE_COPY 0x80
#define PAGE_NOACCESS           0x01
#define PAGE_READONLY           0x02
#define PAGE_READWRITE          0x04
#define PAGE_WRITECOPY          0x08
#define PAGE_TARGETS_INVALID    0x40000000
#define PAGE_TARGETS_NO_UPDATE  0x40000000

#define PAGE_GUARD              0x100
#define PAGE_NOCACHE            0x200
#define PAGE_WRITECOMBINE       0x400

#endif