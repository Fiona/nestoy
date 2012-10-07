/**
 * NESToy emulator
 */

#pragma once
#ifndef _CORE_H_
#define _CORE_H_

#include <string>
#include <vector>
#include "CPU6502.h"


class Core
{

    static Core* oInst;
    std::string sROM_Filename;
    int iPRG_ROM_Size;
    int iCHR_ROM_Size;
    std::vector<int> aPRG_ROM;
    std::vector<int> aCHR_ROM;
    CPU6502* oCPU;

public:

    static Core* Instance();
    void Load_And_Execute_ROM(std::string rom_filename);

};


#endif
