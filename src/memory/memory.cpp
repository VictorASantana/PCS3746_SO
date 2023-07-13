#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define MAX_MEMORY_SIZE 20

class Memory
{
private:
    static int memory[MAX_MEMORY_SIZE];
    static int bitMap[MAX_MEMORY_SIZE];

    // Retorna index do primeiro local da memoria livre
    // ou -1 caso nao haja o espaco requisitado disponivel
    int checkEmptyMemorySlot(int requiredMemoryBlocks)
    {
        int startSequenceIndex, lastSequenceIndex;

        for (int i = 0; i < MAX_MEMORY_SIZE; i++)
        {
            if (bitMap[i] == 0)
            {
                startSequenceIndex = i;

                while (bitMap[i] != 1 && (i - startSequenceIndex) < requiredMemoryBlocks)
                    i++;

                lastSequenceIndex = i;

                int emptyMemorySequenceSize = lastSequenceIndex - startSequenceIndex;

                if (emptyMemorySequenceSize >= requiredMemoryBlocks)
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
    int insertProcessIntoMemory(int requiredMemoryBlocks, int processId)
    {
        int emptyMemorySlotStartIndex = checkEmptyMemorySlot(requiredMemoryBlocks);

        if (emptyMemorySlotStartIndex < 0)
            return -1;

        for (int i = emptyMemorySlotStartIndex; i < (emptyMemorySlotStartIndex + requiredMemoryBlocks); i++)
        {
            memory[i] = processId;
            bitMap[i] = 1;
        }

        return 0;
    }

    int removeProcessFromMemory(int processId)
    {
        int allocatedMemoryForProcessStartIndex = findProcessInMemory(processId);

        if (allocatedMemoryForProcessStartIndex < 0)
            return -1;

        for (int i = allocatedMemoryForProcessStartIndex; memory[i] == processId; i++)
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
