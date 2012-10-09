/**
 * NESToy emulator
 */


#include "Memory.h"


Memory::Memory(int num_locations_in_memory)
{

    aMemory.clear();
    aMemory.resize(num_locations_in_memory);

}
