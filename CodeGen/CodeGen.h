#ifndef CODE_GEN
#define CODE_GEN

/* Mini JIT Assembly CodeGen for IA32. */

/* ============================= NOTE =============================  */
/* When you are going to use this section. I highly recommend read   */
/* "IA32 Architectures Manual(from Intel)" first to understand this  */ 
/* easier.                                                           */

/* Referenced data mean accessing as pointer. "(*eax)" on C/C++.     */
/* Referenced with DISP mean "(*(eax + (DISP value)))"" on C/C++.    */
/* None referenced data mean raw data, just "eax".                   */
/* See "IA Architextures Manual 2-6 Vol.2A" for more informations.   */

enum class MOD_REG32 : uint8_t
{
    REFERENCED_DATA = 0,
    REFERENCED_WITH_DISP8 = 1,
    REFERENCED_WITH_DISP32 = 2,
    NONE_REFERENCED_DATA = 3
};

enum class RM_REG32 : uint8_t
{
    /* Only supporting extended 32bit registers.. just for now.*/
    EAX = 0, AX = 0, AL = 0, MM0 = 0, XMM0 = 0,
    ECX = 1, CX = 1, CL = 1, MM = 1 , XMM1 = 1,
    EDX = 2, DX = 2, DL = 2, MM2 = 2, XMM2 = 2,
    EBX = 3, BX = 3, BL = 3, MM3 = 3, XMM3 = 3,
    ESP = 4, SP = 4, AH = 4, MM4 = 4, XMM4 = 4, SIB_BYTE = 4,
    EBP = 5, BP = 5, CH = 5, MM5 = 5, XMM5 = 5, DISP32 = 5,
    ESI = 6, SI = 6, DH = 6, MM6 = 6, XMM6 = 6
    EDI = 7, DI = 7, BH = 7, MM7 = 7, XMM7 = 7
};

struct Opcode
{
    uint8_t* code;
    uint32_t size;
};

/* I don't really recommend these functions.. I don't like it. needs refactoring. */
namespace InstHelper
{

    /* ======================================= EXAMPLES ======================================= */
    /* InstHelper::ADD(RM_REG32::EAX, 0, MOD_REG32::NONE_REFERENCED_DATA, 100);                 */
    /* Assembly Gen ==>> add eax, 100                                                           */
    /* InstHelper::SUB(RM_REG32::EBX, 4, MOD_REG32::REFERENCED_WITH_DISP8, RM_REG32::EAX);      */
    /* Assembly Gen ==>> sub [ebx + 4], eax                                                     */
    /* InstHelper::MOV(RM_REG32::ECX, RM_REG32::ESP, 8);                                        */
    /* Assembly Gen ==>> mov ecx, [esp + 8]                                                     */
    /* ======================================================================================== */

    /* ADD reg(with mod), imm32 */
    Opcode* ADD(RM_REG32 reg, int32_t disp32, MOD_REG32 mod, uint32_t imm32);
    /* ADD reg_1(with mod), reg_2 */
    Opcode* ADD(RM_REG32 reg_1, int32_t disp32, MOD_REG32 mod, RM_REG32 reg_2);
    /* ADD reg_1, reg_2(with mod) */
    Opcode* ADD(RM_REG32 reg_1, RM_REG32 reg_2, uint_t disp32, RM_REG32 mod);

    /* SUB reg(with mod), imm32 */
    Opcode* SUB(RM_REG32 reg, int32_t disp32, MOD_REG32 mod, uint32_t imm32);
    /* SUB reg_1(with mod), reg2 */
    Opcode* SUB(RM_REG32 reg_1, int32_t disp32, MOD_REG32 mod, RM_REG32 reg_2);

    /* MOV reg(with mod), imm32 */
    Opcode* MOV(RM_REG32 reg, int32_t disp32, MOD_REG32 mod, uint32_t imm32);
    /* MOV reg_1(with mod), reg_2 */
    Opcode* MOV(RM_REG32 reg_1, int32_t disp32, MOD_REG32 mod, RM_REG32 reg_2);
    /* MOV [imm32], reg(with mod) */
    Opcode* MOV(int32_t imm32, RM_REG32 reg, int32_t disp32, MOD_REG32 mod);

    /* LEA reg_1, [reg_2 + disp32] */
    Opcode* LEA(RM_REG32 reg_1, RM_REG32 reg_2, int32_t disp32);
    /* CALL reg(with mod) */
    Opcode* CALL(RM_REG32 reg, int32_t disp32, MOD_REG32 mod);
    /* CALL imm32 */
    Opcode* CALL(uint32_t imm32);
    /* RET imm32 */
    Opcode* RET(uint32_t imm32);
    /* RETN */
    Opcode* RETN();
};

/* NOTE: You can manually make opcode with these functions if you want. */

uint8_t ModRmByteGen(RM_REG32 reg, uint8_t sbyte, MOD_REG32 mod);
uint8_t ModRmByteGen(RM_REG32 reg_1, RM_REG32 reg_2, MOD_REG32 mod);

Opcode* SingleOpcodeGen(uint8_t bOpcode, RM_REG32 reg_1, RM_REG32 reg_2, uint_t disp32, RM_REG32 mod);
Opcode* DoubleOpcodeGen(uint8_t bOpcode_8bit, uint8_t bOpcode_32bit, RM_REG32 reg_1, RM_REG32 reg_2, uint32_t disp32, MOD_REG32 mod, uint32_t imm32);

#endif