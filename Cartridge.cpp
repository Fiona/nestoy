/**
 * NESToy emulator
 */


#include <iostream>
#include <iomanip>
#include "Cartridge.h"
#include "Core.h"


/**
 *
 */
Cartridge::Cartridge(FILE* fileh)
{

    // Make sure the file signature is correct
    // The first characters in an iNES ROM file are the characters NES followed by
    // a DOS end-of-line sequence (032)
    if(fgetc(fileh) != 'N' || fgetc(fileh) != 'E' || fgetc(fileh) != 'S' || fgetc(fileh) != '\32')
        throw "File supplied does not have iNES ROM header signature.";

    // PRG ROM is the section of the ROM that contains the program commands. 
    // The size of this is denoted here as 16KB units. Hence, the
    // real size in bytes is this value by 16384.
    iPRG_ROM_Size = fgetc(fileh) * 16384;
    std::cout << "PRG ROM size is " << iPRG_ROM_Size << std::endl;

    // CHR ROM is graphical tile data. It's size is in 8KB units.
    iCHR_ROM_Size = fgetc(fileh) * 8192;
    std::cout << "CHR ROM size is " << iCHR_ROM_Size << std::endl;

    // Flags 6. Lower nibble of mapper number is stored in first 4 bits.
    // (a mapper is the name given to a separate bit of hardware on some cartridge
    // boards to give games extra capabilities and must each be emulated separately.)
    iFlags6 = fgetc(fileh);

    // Flags 7. Upper nibble of mapper number is stored in first 4 bits.
    iFlags7 = fgetc(fileh);

    // Size of PRG RAM in 8KB units. PRG RAM is graphical data that is not loaded
    // immediately on program execution. This number is not relevant.
    fgetc(fileh);
    
    // Flags 9. Not relevant.
    fgetc(fileh);

    // Flags 10. Not relevant.
    fgetc(fileh);

    // Bytes 11-15 are zero filled.
    for(int i = 11; i <= 15; i++)
        fgetc(fileh);

    // Resize vectors and load ROM contents into memory
    aPRG_ROM.resize(iPRG_ROM_Size);
    fread(&aPRG_ROM[0], 1, iPRG_ROM_Size, fileh);
    aCHR_ROM.resize(iCHR_ROM_Size);
    fread(&aCHR_ROM[0], 1, iCHR_ROM_Size, fileh);

    // Put the PRG ROM into memory.
    for(std::vector<uint8>::size_type i = 0; i != aPRG_ROM.size(); i++)
        Core::Instance()->oMemory->Store_At_Value(0x8000 + (int)i, aPRG_ROM[i]);

    // What mapper are we using?
    iMapper = iFlags6 >> 4 | (iFlags7 & 0xF0);
    std::cout << "Using mapper " << std::hex << iMapper << std::endl;

}


/**
 *
 */
uint8 Cartridge::Get_PRG_Opcode_At(int address)
{
    return aPRG_ROM.at(address);
}
