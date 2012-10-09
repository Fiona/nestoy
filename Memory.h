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

};


#endif
