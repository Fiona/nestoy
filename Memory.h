/**
 * NESToy emulator
 */

#pragma once
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <vector>
#include "global.h"


class Memory
{

    std::vector<uint8> aMemory;

public:

    Memory(int num_locations_in_memory);
    void Store_At_Value(int location, uint8 value_to_store);
    uint8 Get_Value_At(int location);

};


#endif
