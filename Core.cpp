/**
 * NESToy emulator
 */

#include <stdio.h>
#include <iostream>
#include "Core.h"



/**
* Singleton implementation
* @return Core Reference to the singleton instance.
*/
Core* Core::Instance()
{

    if(!oInst)
        oInst = new Core;
    return oInst;

}


/**
 * Main way to start off the emulator, takes in a rom filename as 
 * a path, opens it and starts the emulator
 */
void Core::Load_And_Execute_ROM(std::string rom_filename)
{

    sROM_Filename = rom_filename;

    // Load file in
    FILE *fileh = fopen(sROM_Filename.c_str(), "rb");
    if(fileh == NULL)
        throw "Error loading ROM file";
    std::cout << "Loaded ROM " << sROM_Filename << std::endl;

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
    fgetc(fileh);

    // Flags 6. Upper nibble of mapper number is stored in first 4 bits.
    fgetc(fileh);

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

    // Close file
    fclose(fileh);

    // Init CPU
    oCPU = new CPU6502;
}


// Static initialisers
Core* Core::oInst = NULL;
