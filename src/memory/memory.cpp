#include <iostream>
#include <bits/stdc++.h>
#include "process.h"
#include "memory.h"

using namespace std;

Memory::Memory() {}

int Memory::checkEmptyMemorySlot(Process process)
{
    int startSequenceIndex, lastSequenceIndex;

    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        if (this->bitMap[i] == 0)
        {
            startSequenceIndex = i;

            while (this->bitMap[i] != 1 && (i - startSequenceIndex) < process.getMemoryBlock())
                i++;

            lastSequenceIndex = i;

            int emptyMemorySequenceSize = lastSequenceIndex - startSequenceIndex;

            if (emptyMemorySequenceSize >= process.getMemoryBlock())
                return startSequenceIndex;
        };
    }

    return -1;
};

// Retorna index do primeiro local da memoria alocada ao processo
// ou -1 caso nao encontre o processo na memoria
int Memory::findProcessInMemory(int processId)
{
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        if (this->memory[i] == processId)
            return i;
    }

    return -1;
}

int Memory::insertProcessIntoMemory(Process process)
{
    int emptyMemorySlotStartIndex = checkEmptyMemorySlot(process);

    if (emptyMemorySlotStartIndex < 0)
        return -1;

    for (int i = emptyMemorySlotStartIndex; i < (emptyMemorySlotStartIndex + process.getMemoryBlock()); i++)
    {
        this->memory[i] = process.getID();
        this->bitMap[i] = 1;
    }

    return 0;
}

int Memory::removeProcessFromMemory(Process process)
{
    int allocatedMemoryForProcessStartIndex = findProcessInMemory(process.getID());

    if (allocatedMemoryForProcessStartIndex < 0)
        return -1;

    for (int i = allocatedMemoryForProcessStartIndex; memory[i] == process.getID(); i++)
    {
        memory[i] = 0;
        this->bitMap[i] = 0;
    }

    return 0;
}

// Transfere espaços livres para final da memória
void Memory::fixExternalFragmentation()
{
    int j = 0;
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        if (this->bitMap[i] != 0)
        {
            swap(this->bitMap[j], this->bitMap[i]);
            swap(this->memory[j], this->memory[i]);
            j++;
        }
    }
}

// Apenas para fins de testagem
void Memory::printMemoryAndBitMap()
{
    printf("////////////// MEMORIA ////////////// \n");
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        printf("%d, ", this->memory[i]);
    }

    printf("\n");
    printf("////////////// bitMap ////////////// \n");
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        printf("%d, ", this->bitMap[i]);
    }

    printf("\n");
    printf("\n");
}
