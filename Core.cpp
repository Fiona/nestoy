/**
 * NESToy emulator
 */

#include <stdio.h>
#include <iostream>
#include <iomanip>
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

    // Create file handler for ROM from file source
    sROM_Filename = rom_filename;

    FILE* fileh = fopen(sROM_Filename.c_str(), "rb");
    if(fileh == NULL)
        throw "Error loading ROM file";

    // Init subsystems
    oCPU = new CPU6502;
    oMemory = new Memory(2048);
    oCartridge = new Cartridge(fileh);

    fclose(fileh);

    // Start emulator
    Run();

}


/**
 *
 */
void Core::Run()
{

    while(true)
        oCPU->Tick();

}



// Static initialisers
Core* Core::oInst = NULL;
