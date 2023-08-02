#include <string>
#include <iostream>
#include <vector>

#include "so.h"
#include "tcb.h"
#include "process.h"

using namespace std;

OperatingSystem::OperatingSystem() {}

int OperatingSystem::createProcess(int memoryBlocks)
{
    Process *p;
    TCB *t;

    p = new Process(memoryBlocks, this->currentID);
    t = new TCB(*p);

    this->processVector.push_back(*p);
    this->TCBVector.push_back(*t);
    this->mem.insertProcessIntoMemory(*p);
    this->mem.printMemoryAndBitMap();
    this->currentID++;

    return 1;
}

int OperatingSystem::killProcess(int pID)
{
    for (int i = 0; i < processVector.size(); i++)
    {
        Process p = processVector[i];
        int id = p.getID();

        if (pID == id)
        {
            this->mem.removeProcessFromMemory(p);
            this->processVector.erase(processVector.begin() + i);
            this->TCBVector.erase(TCBVector.begin() + i);
            this->mem.printMemoryAndBitMap();
            break;
        }
    }

    return 1;
}

Process* OperatingSystem::getProcess(int pid)
{
    Process *p;
    for (int i = 0; i < this->processVector.size(); i++)
    {
        p = &processVector[i];
        if (p->getID() == pid)
            return p;
    }

    return NULL;
}

TCB* OperatingSystem::getTCB(int pID)
{
    TCB *t;
    for (int i = 0; i < TCBVector.size(); i++)
    {
        t = &TCBVector[i];
        int id = t->getProcess().getID();
        if (pID == id) return t;
    }

    return NULL;
}

int OperatingSystem::compactMem()
{
    this->mem.fixExternalFragmentation();
    this->mem.printMemoryAndBitMap();
    return 1;
}

int OperatingSystem::runCycle() 
{
    Process *p;
    p = this->getProcess(1);
    p->updatePC();

    this->cycle = this->cycle + 1;
    if (this->cycle == 4)
    {
        this->compactMem();
        this->cycle = 0;
    }

    return (p->getPC());
}
