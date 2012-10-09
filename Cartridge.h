/**
 * NESToy emulator
 */

#pragma once
#ifndef _CARTRIDGE_H_
#define _CARTRIDGE_H_


#include <stdio.h>
#include <vector>
#include "global.h"


/**
 *
 */
class Cartridge
{

    int iPRG_ROM_Size;
    int iCHR_ROM_Size;
    int iFlags6;
    int iFlags7;    
    int iMapper;
    std::vector<uint8> aPRG_ROM;
    std::vector<uint8> aCHR_ROM;

public:

    Cartridge(FILE* fileh);
    uint8 Get_PRG_Opcode_At(int address);

};


#endif
