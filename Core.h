/**
 * NESToy emulator
 */
#pragma once
#ifndef _CORE_H_
#define _CORE_H_

#include <string>
#include <vector>
#include "global.h"
#include "CPU6502.h"
#include "Memory.h"
#include "Cartridge.h"


class Core
{

    static Core* oInst;
    std::string sROM_Filename;

    void Run();

public:

    Cartridge* oCartridge;
    CPU6502* oCPU;
    Memory* oMemory;

    static Core* Instance();
    void Load_And_Execute_ROM(std::string rom_filename);
    
};


#endif
