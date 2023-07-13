#include <iostream>

using namespace std;

#define MAX_MEMORY_SIZE 300

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
};
