#ifndef CODE_GEN
#define CODE_GEN

/* Mini JIT Assembly CodeGen for IA32. */

/* ============================= NOTE =============================  */
/* When you are going to use this section. I highly recommend read   */
/* "IA32 Architectures Manual(from Intel)" first to understand this  */ 
/* easier.                                                           */

/* Referenced data means accessing as pointer. "(*eax)" on C/C++.    */
/* Referenced with DISP mean "(*(eax + (DISP value)))"" on C/C++.    */
/* None referenced data means raw data, just "eax".                  */
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

namespace Instructions
{

    /* ======================================= EXAMPLES ======================================= */
    /* Instructions::ADD(RM_REG32::EAX, MOD_REG32::NONE_REFERENCED_DATA, 10);                   */
    /* Assembly Gen ==>> add eax, 10                                                            */
    /* Instructions::SUB(RM_REG32::EBX, MOD_REG32::NONE_REFERENCED_DATA, RM_REG32::EAX);        */
    /* Assembly Gen ==>> sub ebx, eax                                                           */
    /* Instructions::MOV(RM_REG32::ECX, RM_REG32::ESP, 8);                                      */
    /* Assembly Gen ==>> mov ecx, [esp + 8]                                                     */
    /* ======================================================================================== */

    /* ADD reg(with mod), imm32 */
    Opcode* ADD(RM_REG32 reg, MOD_REG32 mod, uint32_t imm32);
    /* ADD reg_1(with mod), reg_2 */
    Opcode* ADD(RM_REG32 reg_1, MOD_REG32 mod, RM_REG32 reg_2);

    /* SUB reg(with mod), imm32 */
    Opcode* SUB(RM_REG32 reg, MOD_REG32 mod, uint32_t imm32);
    /* SUB reg_1(with mod), reg2 */
    Opcode* SUB(RM_REG32 reg_1, MOD_REG32 mod, RM_REG32 reg2);

    /* MOV reg(with mod), imm32 */
    Opcode* MOV(RM_REG32 reg, MOD_REG32 mod, uint32_t imm32);
    /* MOV reg_1(with mod), reg_2 */
    Opcode* MOV(RM_REG32 reg_1, MOD_REG32 mod_1, RM_REG32 reg_2);
    /* MOV reg_1, [reg_2 + imm32]*/
    Opcode* Mov(RM_REG32 reg_1, RM_REG32 reg_2, int32_t imm32);

    /* LEA reg_1, [reg_2 + imm32] */
    Opcode* LEA(RM_REG32 reg_1, RM_REG32 reg_2, int32_t imm32);
}

#endif