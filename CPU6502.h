/**
 * NESToy emulator
 */

#pragma once
#ifndef _CPU6502_H_
#define _CPU6502_H_

#include <vector>
#include <bitset>
#include "global.h"


class CPU6502
{

    uint8 iAccumulator;
    uint8 iX_Register;
    uint8 iY_Register;
    std::bitset<8> aStatus_Register;
    int iProgram_Counter;
    uint8 iCurrent_Opcode;

    uint8 Address_Immediate();
    
    void Set_Interrupt_Flag(int set_to);
    void Set_Decimal_Flag(int set_to);
    void Set_Negative_Flag(int set_to);
    void Set_Zero_Flag(int set_to);
    void Set_Negative_Flag_From_Value(uint8 value);
    void Set_Zero_Flag_From_Value(uint8 value);

    void Op_CLD();
    void Op_LDA(uint8 value);
    void Op_SEI();

public:

    CPU6502();
    void Tick();

};


#endif
