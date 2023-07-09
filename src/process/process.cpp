#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Process
{
public:
    int id;
    int memoryBlocks;
    string instructions;
};

// Retorna um processo
Process createProcess(int memoryBlocks)
{
    int id = rand();
    Process proc;
    proc.id = id;
    proc.memoryBlocks = memoryBlocks;
    return proc;
}

/*Algumas observações:
1. Ainda não tenho muita ideia de como fazer a atribuição de instruções a serem executadas por parte do processo
2. É preciso fazer de uma forma que o comando "create -m X" chame a função createProcess passando X como memoryBlocks
3. Ainda não tenho muita ideia de onde esse processo vai ser manipulado.
*/