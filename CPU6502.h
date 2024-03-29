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
    uint8 iStack_Pointer;
    std::bitset<8> aStatus_Register;
    int iProgram_Counter;
    uint8 iCurrent_Opcode;

    void Push_Stack(uint8 value);
    uint8 Pop_Stack();

    uint8 Address_Immediate();
    int Address_Absolute();
    int Address_Relative();
    int Address_Zero_Page();
    int Address_Absolute_X();

    void Set_Interrupt_Flag(int set_to);
    void Set_Decimal_Flag(int set_to);
    void Set_Negative_Flag(int set_to);
    void Set_Zero_Flag(int set_to);
    void Set_Negative_Flag_From_Value(uint8 value);
    void Set_Zero_Flag_From_Value(uint8 value);

    void Op_BPL();
    void Op_CLD();
    void Op_JSR(int value);
    void Op_LDA(int value);
    void Op_LDX(int value);
    void Op_SEI();
    void Op_STA(int value);
    void Op_TXS();

public:

    CPU6502();
    void Tick();

};


#endif
