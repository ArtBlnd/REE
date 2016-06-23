#ifndef _REE_CODEGEN_
#define _REE_CODEGEN_

#ifdef USE_CODEGEN_FUNCTIONS

#define MAKE_OPCODE_STRUCT(name, size) NONE_PACKING_STRUCT name { BYTE opcode[size] };

MAKE_OPCODE_STRUCT(OPCODE_1BYTE, 1);
MAKE_OPCODE_STRUCT(OPCODE_2BYTES, 2);
MAKE_OPCODE_STRUCT(OPCODE_3BYTES, 3);
MAKE_OPCODE_STRUCT(OPCODE_4BYTES, 4);
MAKE_OPCODE_STRUCT(OPCODE_5BYTES, 5);
MAKE_OPCODE_STRUCT(OPCODE_6BYTES, 6);

constexpr OPCODE_3BYTES GenSubEsp(uint32_t value);
constexpr OPCODE_4BYTES GenMovEspOffset(uint32_t offset, uint32_t value);
constexpr OPCODE_6BYTES GenAbsoluteJmp(uint32_t value);

#undef MAKE_OPCODE_STRUCT

#endif
#endif