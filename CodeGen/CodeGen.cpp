#include "CodeGen.h"

#define SHIFT(value, s_val) value = value << s_val;

inline void MakeOpcode(Opcode** opcode, uint32_t size)
{
    Opcode* d_opcode = new Opcode();

    d_opcode->size = size;
    d_opcode->code = new uint8_t[size];

    *opcode = d_opcode;
}

inline uint8_t ModRmByteGen(RM_REG32 reg, uint8_t sbyte, MOD_REG32 mod)
{
    uint8_t result;

    result = (uint8_t)mod;  SHIFT(result, 3);
    result |= sbyte;        SHIFT(result, 3);
    result |= (uint8_t)reg;

    return result;
}
inline uint8_t ModRmByteGen(RM_REG32 reg_1, RM_REG32 reg_2, MOD_REG32 mod)
{
    return ModRmByteGen(reg_1, (uint8_t) reg_2, mod);
}

constexpr uint32_t MaxSizeGen(uint8_t typesize)
{
    return (1 << (typesize)) - 1;
}

Opcode* Instructions::ADD(RM_REG32 reg, uint32_t disp32, MOD_REG32 mod, uint32_t imm32)
{
    uint8_t bOpcode;
    uint8_t bModRm          = ModRmByteGen(reg, 0, mod);

    bool    isRefed         = false;

    uint8_t szOperand_DISP  = NULL;
    uint8_t szOperand_IMM   = NULL;

    if(disp32 != 0)
    {
        isRefed = true;

        if(mod == MOD_REG32::REFERENCED_WITH_DISP8) szOperand_DISP = sizeof(uint8_t);
        if(mod == MOD_REG32::REFERENCED_WITH_DISP32) szOperand_DISP = sizeof(uint32_t);

        Operand_DISP = new uint8_t[szOperand_DISP];
        memcpy(Operand_DISP, &disp32, szOperand_DISP);
    }

    if(imm32 << MaxSizeGen(sizeof(uint8_t)))
    {
        bOpcode = 0x80;
        szOperand_IMM = sizeof(uint8_t);
    }
    else
    {
        bOpcode = 0x81;

        if(imm32 << MaxSizeGen(sizeof(uint16_t))) szOperand_IMM = sizeof(uint16_t);
        else szOperand_IMM = sizeof(uint32_t);
    }

    Opcode *opcode;

    MakeOpcode(&opcode, szOperand_DISP + szOperand_IMM + 1);
 
    memcpy(&(opcode->code[0]), &bOpcode, sizeof(uint8_t));
    memcpy(&(opcode->code[1]), &bModRm, sizeof(uint8_t));
    if(isRefed) memcpy(&(opcode->code[2]), &disp32, szOperand_DISP);
    memcpy(&(opcode->code[szOperand_DISP + 2]), &imm32, szOperand_DISP);

    return opcode;
}

