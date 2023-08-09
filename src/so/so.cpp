#include <string>
#include <iostream>
#include <vector>
#include <deque>

#include "so.h"
#include "tcb.h"
#include "process.h"
#include "scheduler.h"

using namespace std;

OperatingSystem::OperatingSystem() {}

int OperatingSystem::createProcess(int memoryBlocks, int type)
{
    Process *p;
    TCB *t;

    if (memoryBlocks <= 0)
        return -1;
        
    p = new Process(memoryBlocks, this->currentID, type);
    t = new TCB(p);

    this->processVector.push_back(p);
    this->TCBVector.push_back(t);

    int i = this->mem.insertProcessIntoMemory(*p);
    if (i)
    {
        this->sched.addTCB(t);
        this->currentID++;
    }

    return 1;
}

int OperatingSystem::killProcess(int pID)
{
    for (int i = 0; i < processVector.size(); i++)
    {
        Process *p = processVector[i];
        TCB *t = TCBVector[i];
        int id = p->getID();

        if (pID == id)
        {
            this->mem.removeProcessFromMemory(*p);
            this->processVector.erase(processVector.begin() + i);
            this->TCBVector.erase(TCBVector.begin() + i);
            this->sched.RemoveTCB(t);
            break;
        }
    }

    return 1;
}

int OperatingSystem::addProcess(int memoryBlocks, int type)
{
    Process *p;
    TCB *t;

    p = new Process(memoryBlocks, this->currentID, type);
    t = new TCB(p);

    this->processVector.push_back(p);
    this->TCBVector.push_back(t);
    this->sched.addTCB(t);
    this->currentID++;

    return 1;
}

Process *OperatingSystem::getProcess(int pid)
{
    Process *p;
    for (int i = 0; i < this->processVector.size(); i++)
    {
        p = processVector[i];
        if (p->getID() == pid)
            return p;
    }

    return NULL;
}

TCB *OperatingSystem::getTCB(int pID)
{
    TCB *t;
    for (int i = 0; i < TCBVector.size(); i++)
    {
        t = TCBVector[i];
        int id = t->getProcess()->getID();
        if (pID == id)
            return t;
    }

    return NULL;
}

int OperatingSystem::compactMem()
{
    this->mem.fixExternalFragmentation();
    return 1;
}

int OperatingSystem::runCycle()
{
    Process *p;
    TCB *t = this->sched.getFirstElement(false);

    if (t != NULL)
    {
        int type = t->getProcess()->getType();

        if (type == 1)
        {
            this->createProcess(t->getProcess()->getMemoryBlock(), 0);
            this->sched.scheduleTCB(true);
            this->killProcess(t->getProcess()->getID());
        }

        else if (type == 2)
        {
            this->killProcess(t->getProcess()->getMemoryBlock());
            this->sched.scheduleTCB(true);
            this->killProcess(t->getProcess()->getID());
        }

        else
        {
            p = t->getProcess();
            this->compact++;

            if (p->getPC() == (p->getMemoryBlock() - 1))
            {
                this->sched.scheduleTCB(true);
                this->killProcess(p->getID());
                this->cycle = 0;
            }

            else
            {
                p->updatePC();
                this->cycle++;

                if (this->cycle == this->quantum)
                {
                    bool isRoundRobin = this->sched.getSchedulerAlgorithm();
                    if (isRoundRobin)
                        this->sched.scheduleTCB(false);
                    this->cycle = 0;
                }
            }

            if (this->compact == this->quantum)
            {
                this->compact = 0;
                this->compactMem();
            }
        }

        return p->getPC();
    }

    return -1;
}

void OperatingSystem::setAlgorithm(string str)
{
    if (str == "rr")
        this->sched.setSchedulerAlgorithm(true);

    else if (str == "fifo")
        this->sched.setSchedulerAlgorithm(false);

    else
        printf("Algoritmo nao reconhecido\n");
}

TCB *OperatingSystem::getRunning()
{
    TCB *t = this->sched.getFirstElement(false);
    if (t != NULL)
    {
        return t;
    }
    return NULL;
}

int *OperatingSystem::getBitMapState()
{
    int *m = this->mem.getBitMap();
    if (m != NULL)
    {
        return m;
    }
    return NULL;
}

deque<TCB *> OperatingSystem::getScheduler()
{
    return this->sched.getSchedulerState();
}
