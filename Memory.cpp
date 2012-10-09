/**
 * NESToy emulator
 */


#include <iostream>
#include <iomanip>
#include "Memory.h"


/**
 *
 */
Memory::Memory(int num_locations_in_memory)
{

    aMemory.clear();
    aMemory.resize(num_locations_in_memory);

}


/**
 *
 */
void Memory::Store_At_Value(int location, uint8 value_to_store)
{

    std::cout << "Writing " << (int)value_to_store << " at mem loc " << std::hex << (int)location << std::endl;
    aMemory[location] = value_to_store;

}


/**
 *
 */
uint8 Memory::Get_Value_At(int location)
{
    std::cout << "Reading memory from loc " << std::hex << location << std::endl;    
    return aMemory[location];
}
