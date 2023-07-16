#include "memory.h"
#include <iostream>

int Memory::bitMap[MAX_MEMORY_SIZE] = {0};
int Memory::memory[MAX_MEMORY_SIZE] = {0};

// Apenas para fins de testagem
int main()
{
    int processOne[2] = {1, 4};
    int processTwo[2] = {2, 2};
    int processThree[2] = {3, 5};
    int processFour[2] = {4, 2};

    Memory mem;

    mem.insertProcessIntoMemory(processOne[1], processOne[0]);
    mem.printMemoryAndBitMap();
    mem.insertProcessIntoMemory(processTwo[1], processTwo[0]);
    mem.printMemoryAndBitMap();
    mem.insertProcessIntoMemory(processThree[1], processThree[0]);
    mem.printMemoryAndBitMap();
    mem.removeProcessFromMemory(processTwo[0]);
    mem.printMemoryAndBitMap();
    mem.fixExternalFragmentation();
    mem.printMemoryAndBitMap();
    mem.insertProcessIntoMemory(processFour[1], processFour[0]);
    mem.printMemoryAndBitMap();

    return 0;
}