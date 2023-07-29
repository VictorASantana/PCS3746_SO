#include <string>
#include <iostream>
#include <vector>

#include "tcb.h"
#include "process.h"
#include "memory.h"

using namespace std;

class OperatingSystem {
    private:
    Memory mem;
    vector<Process> processVector;
    vector<TCB> TCBVector;

    public:
    OperatingSystem() {}

    int createProcess(int memoryBlocks) {
        Process *p;
        TCB *t;

        p = new Process(memoryBlocks);
        t = new TCB(*p);

        this->processVector.push_back(*p);
        this->TCBVector.push_back(*t);
        this->mem.insertProcessIntoMemory(*p);
        this->mem.printMemoryAndBitMap();

        return 1;
    }

    int killProcess(int pID) {
        for (int i = 0; i < processVector.size(); i++) {
            Process p = processVector[i];
            int id = p.getID();

            if (pID == id) {
                this->mem.removeProcessFromMemory(p);
                this->processVector.erase(processVector.begin() + i);
                this->TCBVector.erase(TCBVector.begin() + i);
                this->mem.printMemoryAndBitMap();
                break;
            }
        }

        return 1;
    }

    int getProcessID(int i) {
        Process p = processVector[i];
        int id = p.getID();

        return id;
    }

    TCB* getTCB(int pID) {
        for (int i = 0; i < TCBVector.size(); i++) {
            TCB *t = &TCBVector[i];
            int id = t->getProcess().getID();

            if (pID == id) {
                return t;
            }
        }

        return NULL;
    }

    int compactMem() {
        this->mem.fixExternalFragmentation();
        this->mem.printMemoryAndBitMap();

        return 1;
    }
};

int main() {
    OperatingSystem SO;
    TCB *t;
    int pid;

    SO.createProcess(3);
    SO.createProcess(4);

    pid = SO.getProcessID(0);
    SO.killProcess(pid);
    SO.compactMem();
    t = SO.getTCB(pid);

    if (t == NULL) {
        std::cout << "Processo não encontrado!" << "\n";
    } else {
        std::cout << pid << "\n";
    }

    return 0;
}
