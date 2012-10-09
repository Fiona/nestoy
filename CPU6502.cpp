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

    // LDX
    case 0xa2:
        Op_LDX(Address_Immediate());
        break;

    // SEI
    case 0x78:
        Op_SEI();
        break;

    // STA
    case 0x8d:
        Op_STA(Address_Absolute());
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
 * Returns the value to be passed to an opcode using absolute addressing.
 * Absolute adressing gets a value that is stored in the next two bytes.
 */
int CPU6502::Address_Absolute()
{

	uint8 low_byte = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter + 1);
	uint8 high_byte = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter + 2);
    iProgram_Counter += 2;

    return ((int)high_byte << 8) + (int)low_byte;

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
 * Sets the negative flag status to a specific value
 */
void CPU6502::Set_Negative_Flag(int set_to)
{
    aStatus_Register[NEGATIVE_FLAG] = set_to;
}


/**
 * Sets the zero flag status to a specific value
 */
void CPU6502::Set_Zero_Flag(int set_to)
{
    aStatus_Register[ZERO_FLAG] = set_to;
}


/**
 * Used by opcodes to check a value that has been set and 
 * set the negative flag accordingly.
 */
void CPU6502::Set_Negative_Flag_From_Value(uint8 value)
{

    if((value & 0x80) == 0x80)
        Set_Negative_Flag(1);
    else
        Set_Negative_Flag(0);

}


/**
 * Used by opcodes to check if the result of a command or an assigned
 * value was zero or not and sets the zero flag accordingly.
 */
void CPU6502::Set_Zero_Flag_From_Value(uint8 value)
{

    if(value == 0x00)
        Set_Zero_Flag(1);
    else
        Set_Zero_Flag(0);

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
void CPU6502::Op_LDA(int value)
{
    iAccumulator = value;
    Set_Negative_Flag_From_Value(iAccumulator);
    Set_Zero_Flag_From_Value(iAccumulator);
}


/**
 * OPCODE: LDX - 0A2 0A6 0B6 0AE 0BE
 * Load X register with memory value
 */
void CPU6502::Op_LDX(int value)
{
    iX_Register = Core::Instance()->oMemory->Get_Value_At(value);
    Set_Negative_Flag_From_Value(iX_Register);
    Set_Zero_Flag_From_Value(iX_Register);
}


/**
 * OPCODE: SEI - 078
 * Set interrupt disable status
 */
void CPU6502::Op_SEI()
{
    Set_Interrupt_Flag(1);
}


/**
 * OPCODE: STA - 085 095 081 091 08D 09D 099
 * Store value from accumulator into memory
 */
void CPU6502::Op_STA(int value)
{
    Core::Instance()->oMemory->Store_At_Value(value, iAccumulator);
}
