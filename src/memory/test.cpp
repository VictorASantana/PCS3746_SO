// #include "memory.h"
// #include "../process/process.h"
// #include <iostream>

// int Memory::bitMap[MAX_MEMORY_SIZE] = {0};
// int Memory::memory[MAX_MEMORY_SIZE] = {0};

// // Apenas para fins de testagem
// int main()
// {
//     Process processOne = createProcess(4);
//     Process processTwo = createProcess(2);
//     Process processThree = createProcess(5);
//     Process processFour = createProcess(2);

//     Memory mem;

//     mem.insertProcessIntoMemory(processOne);
//     mem.printMemoryAndBitMap();
//     mem.insertProcessIntoMemory(processTwo);
//     mem.printMemoryAndBitMap();
//     mem.insertProcessIntoMemory(processThree);
//     mem.printMemoryAndBitMap();
//     mem.removeProcessFromMemory(processTwo);
//     mem.printMemoryAndBitMap();
//     mem.fixExternalFragmentation();
//     mem.printMemoryAndBitMap();
//     mem.insertProcessIntoMemory(processFour);
//     mem.printMemoryAndBitMap();

//     return 0;
// }