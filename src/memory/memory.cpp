#include <iostream>
#include <vector>

using namespace std;

#define MAX_MEMORY 300

class Memory
{
private:
    static vector<int> memory;
    static int allocatedMemorySlots;

public:
    int insertIntoMemory(int memoryBlocks)
    {
        if (memoryBlocks < (MAX_MEMORY - allocatedMemorySlots))
        {
            // TODO: algoritmo de First-Fit
            memory.insert(memory.end(), 1);
            allocatedMemorySlots++;
            return 0;
        }

        return -1;
    }
};
