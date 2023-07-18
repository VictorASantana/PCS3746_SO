#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <bits/stdc++.h>
#include "../process/process.h"

using namespace std;

#define MAX_MEMORY_SIZE 20

class Memory
{
private:
    static int memory[MAX_MEMORY_SIZE];
    static int bitMap[MAX_MEMORY_SIZE];

    // Retorna index do primeiro local da memoria livre
    // ou -1 caso nao haja o espaco requisitado disponivel
    int checkEmptyMemorySlot(Process process)
    {
        int startSequenceIndex, lastSequenceIndex;

        for (int i = 0; i < MAX_MEMORY_SIZE; i++)
        {
            if (bitMap[i] == 0)
            {
                startSequenceIndex = i;

                while (bitMap[i] != 1 && (i - startSequenceIndex) < process.memoryBlocks)
                    i++;

                lastSequenceIndex = i;

                int emptyMemorySequenceSize = lastSequenceIndex - startSequenceIndex;

                if (emptyMemorySequenceSize >= process.memoryBlocks)
                    return startSequenceIndex;
            };
        }

        return -1;
    };

    // Retorna index do primeiro local da memoria alocada ao processo
    // ou -1 caso nao encontre o processo na memoria
    int findProcessInMemory(int processId)
    {
        for (int i = 0; i < MAX_MEMORY_SIZE; i++)
        {
            if (memory[i] == processId)
                return i;
        }

        return -1;
    }

public:
    int insertProcessIntoMemory(Process process)
    {
        int emptyMemorySlotStartIndex = checkEmptyMemorySlot(process);

        if (emptyMemorySlotStartIndex < 0)
            return -1;

        for (int i = emptyMemorySlotStartIndex; i < (emptyMemorySlotStartIndex + process.memoryBlocks); i++)
        {
            memory[i] = process.id;
            bitMap[i] = 1;
        }

        return 0;
    }

    int removeProcessFromMemory(Process process)
    {
        int allocatedMemoryForProcessStartIndex = findProcessInMemory(process.id);

        if (allocatedMemoryForProcessStartIndex < 0)
            return -1;

        for (int i = allocatedMemoryForProcessStartIndex; memory[i] == process.id; i++)
        {
            memory[i] = 0;
            bitMap[i] = 0;
        }

        return 0;
    }

    // Apenas para fins de testagem
    void printMemoryAndBitMap()
    {
        printf("////////////// MEMORIA ////////////// \n");

        for (int i = 0; i < MAX_MEMORY_SIZE; i++)
        {
            printf("%d, ", memory[i]);
        }

        printf("\n");

        printf("////////////// BITMAP ////////////// \n");

        for (int i = 0; i < MAX_MEMORY_SIZE; i++)
        {
            printf("%d, ", bitMap[i]);
        }

        printf("\n");

        printf("\n");
    }

    // Transfere espaços livres para final da memória
    void fixExternalFragmentation()
    {
        int j = 0;
        for (int i = 0; i < MAX_MEMORY_SIZE; i++)
        {
            if (bitMap[i] != 0)
            {
                swap(bitMap[j], bitMap[i]);
                swap(memory[j], memory[i]);
                j++;
            }
        }
    }
};

#endif