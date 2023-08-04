#ifndef MEMORY_H
#define MEMORY_H

#include "process.h"

using namespace std;
#define MAX_MEMORY_SIZE 20

class Memory
{
private:
    int memory[MAX_MEMORY_SIZE];
    int bitMap[MAX_MEMORY_SIZE];

public:
    Memory();

    int insertProcessIntoMemory(Process process);

    int removeProcessFromMemory(Process process);

    int *getBitMap();

    // Transfere espaços livres para final da memória
    void fixExternalFragmentation();

private:
    int checkEmptyMemorySlot(Process process);

private:
    int findProcessInMemory(int processId);

    // Apenas para fins de testagem
public:
    void printMemoryAndBitMap();
};

#endif
