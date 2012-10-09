/**
 * NESToy emulator
 */

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "CPU6502.h"
#include "Core.h"



/**
 * Constructor
 */
CPU6502::CPU6502()
{

    iAccumulator = 0;
    iX_Register = 0;
    iY_Register = 0;
    iX_Register = 0;
    aStatus_Register.reset();
    iProgram_Counter = 0;
    iCurrent_Opcode = 0;

}


/**
 *
 */
void CPU6502::Tick()
{
    
    iCurrent_Opcode = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter);

    std::cout << "Op: " << std::hex << (int)iCurrent_Opcode << std::endl;

    switch(iCurrent_Opcode)
    {

    // CLD
    case 0xd8:
        Op_CLD();
        break;

    // LDA
    case 0xa9:
        Op_LDA(Address_Immediate());
        break;
/*
    case 0xa5:
        Op_LDA();
        break;
    case 0xb5:
        Op_LDA();
        break;
    case 0xad:
        Op_LDA();
        break;
    case 0xbd:
        Op_LDA();
        break;
    case 0xb9:
        Op_LDA();
        break;
    case 0xa1:
        Op_LDA();
        break;
    case 0xb1:
        Op_LDA();
        break;
*/

    // SEI
    case 0x78:
        Op_SEI();
        break;

    default:
        throw "OPCODE UNSUPPORTED";
    }
        
    iProgram_Counter++;

}


/**
 * Returns the value to be passed to an opcode using immediate
 * addressing. Immediate adressing is the next value in the RPG ROM.
 */
uint8 CPU6502::Address_Immediate()
{
    iProgram_Counter++;
    return Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter);
}


/**
 * Sets the interrupt status to a specific value
 */
void CPU6502::Set_Interrupt_Flag(int set_to)
{
    aStatus_Register[INTERRUPT_FLAG] = set_to;
}


/**
 * Sets the decimal flag status to a specific value
 */
void CPU6502::Set_Decimal_Flag(int set_to)
{
    aStatus_Register[DECIMAL_FLAG] = set_to;
}


/**
 * OPCODE: CLD - 0d8
 * Clear decimal mode
 */
void CPU6502::Op_CLD()
{
    Set_Decimal_Flag(0);
}


/**
 * OPCODE: LDA - 0a9 0a5 0b5 0ad 0bd 0b9 0a1 0b1
 * Load accumulator register with memory value
 */
void CPU6502::Op_LDA(uint8 value)
{
    iAccumulator = value;
}


/**
 * OPCODE: SEI - 078
 * Set interrupt disable status
 */
void CPU6502::Op_SEI()
{
    Set_Interrupt_Flag(1);
}
