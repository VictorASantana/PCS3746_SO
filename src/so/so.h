#include <vector>
#include <deque>
#include "tcb.h"
#include "process.h"
#include "memory.h"
#include "scheduler.h"

using namespace std;

class OperatingSystem
{
private:
    int currentID = 1;
    int quantum = 4;
    int cycle = 0;
    int compact = 0;

private:
    Memory mem;
    Scheduler sched;
    vector<Process *> processVector;
    vector<TCB *> TCBVector;

public:
    OperatingSystem();

    int createProcess(int, int);

    int killProcess(int);

    int addProcess(int, int);

    Process *getProcess(int);

    TCB *getTCB(int);

    TCB *getRunning();

    int *getBitMapState();

    int compactMem();

    int runCycle();

    void setAlgorithm(string);
    
    deque<TCB*> getScheduler();

    bool getAlgorithm();
};
