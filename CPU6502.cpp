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
    iStack_Pointer = 0xfd;
    aStatus_Register.reset();
    Set_Interrupt_Flag(1);
    iProgram_Counter = 0;
    iCurrent_Opcode = 0;

}


/**
 *
 */
void CPU6502::Tick()
{
    
    iCurrent_Opcode = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter);
    iProgram_Counter++;

    std::cout << "Op: " << std::hex << (int)iCurrent_Opcode << std::endl;

    switch(iCurrent_Opcode)
    {

    // BPL
    case 0x10:
        Op_BPL();
        break;

    // CLD
    case 0xd8:
        Op_CLD();
        break;

    // LDA
    case 0xa9:
        Op_LDA(Address_Immediate());
        break;
    case 0xad:
        Op_LDA(Address_Absolute());
        break;
    case 0xbd:
        Op_LDA(Address_Absolute_X());
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
    case 0x85:
        Op_STA(Address_Zero_Page());
        break;

    // TXS
    case 0x9a:
        Op_TXS();
        break;

    default:
        throw "OPCODE UNSUPPORTED";
    }
        
}


/**
 * Returns the value to be passed to an opcode using immediate
 * addressing. Immediate adressing is the next value in the RPG ROM.
 */
uint8 CPU6502::Address_Immediate()
{
    iProgram_Counter++;
    return Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter - 1);
}


/**
 * Returns the value to be passed to an opcode using absolute addressing.
 * Absolute adressing gets a value that is stored in the next two bytes.
 */
int CPU6502::Address_Absolute()
{

	uint8 low_byte = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter);
	uint8 high_byte = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter + 1);
    iProgram_Counter += 2;

    return ((int)high_byte << 8) + (int)low_byte;

}


/**
 * Much like addressing absolutely, except this uses the X register to help
 * determine the correct address.
 */
int CPU6502::Address_Absolute_X()
{

	uint8 low_byte = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter);
	uint8 high_byte = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter + 1);
    iProgram_Counter += 2;

    int addr = ((int)high_byte << 8) + (int)low_byte + (int)iX_Register;
    if(addr > 0xffff)
        addr &= 0xffff;

    return addr;

}


/**
 * Returns the value to be passed to an opcode using zero-page adressing.
 * Zero-page is like abslolute except the requested value is low enough to be
 * stored as a single byte, so no messing around is necessary.
 */
int CPU6502::Address_Zero_Page()
{
    iProgram_Counter++;
	return Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter - 1);
}


/**
 * Returns the program counter to jump to based on the current program counter and
 * the address following this one. It treats the given address as a signed number 
 * allowing a value between -127 and 127.
 */
int CPU6502::Address_Relative()
{

	uint8 address = Core::Instance()->oCartridge->Get_PRG_Opcode_At(iProgram_Counter + 1);

    if(address < 0x80)
        address = iProgram_Counter + address;
    else
        address = (iProgram_Counter - 0x100) + address;

    address++;

    return address;

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
 * OPCODE: BPL - 010
 * Branch on result plus. Branches to the relative address unless negative flag is 1.
 */
void CPU6502::Op_BPL()
{

    if(!aStatus_Register[NEGATIVE_FLAG])
        iProgram_Counter = Address_Relative();
    else
        iProgram_Counter++;

    std::cout << "BPL branch to " << std::hex << (iProgram_Counter) << std::endl;

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


/**
 * OPCODE: TXS - 09a
 * Transfer X register to stack pointer.
 */
void CPU6502::Op_TXS()
{
    iStack_Pointer = iX_Register;
}
