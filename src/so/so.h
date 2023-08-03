#include <vector>
#include "tcb.h"
#include "process.h"
#include "memory.h"

using namespace std;

class OperatingSystem {
    private:
    Memory mem;
    int currentID = 1;
    int cycle = 0;
    vector<Process> processVector;
    vector<TCB> TCBVector;

    public:
    OperatingSystem();

    int createProcess(int);

    int killProcess(int);

    Process* getProcess(int);

    TCB* getTCB(int);

    int compactMem();

    int runCycle();
};
