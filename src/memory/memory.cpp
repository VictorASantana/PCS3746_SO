#include <iostream>

using namespace std;

#define MAX_MEMORY 300

class Memory
{
private:
    static int memory[MAX_MEMORY];

    // Retorna index do primeiro local da memoria livre
    // ou -1 caso não haja o espaco requisitado disponivel
    int checkEmptyMemorySlot(int requiredMemoryBlocks)
    {
        int startSequenceIndex, lastSequenceIndex;

        for (int i = 0; i < MAX_MEMORY; i++)
        {
            if (memory[i] == 0)
            {
                startSequenceIndex = i;

                while (memory[i] != 1 && (i - startSequenceIndex) < requiredMemoryBlocks)
                    i++;

                lastSequenceIndex = i;

                int emptyMemorySequenceSize = lastSequenceIndex - startSequenceIndex;

                if (emptyMemorySequenceSize >= requiredMemoryBlocks)
                    return startSequenceIndex;
            };
        }

        return -1;
    };

public:
    int insertIntoMemory(int memoryBlocks)
    {
        int emptyMemorySlotStartIndex = checkEmptyMemorySlot(memoryBlocks);

        if (emptyMemorySlotStartIndex < 0)
            return -1;

        for (int i = emptyMemorySlotStartIndex; i < (emptyMemorySlotStartIndex + memoryBlocks); i++)
            memory[i] = 1;

        return 0;
    }
};
