#include <iostream>
#include <deque>
#include "scheduler.h"
#include "tcb.h"
#include "process.h"

using namespace std;

Scheduler::Scheduler() {}

void Scheduler::setSchedulerAlgorithm(bool algorithm) { this->roundRobin = algorithm; }

bool Scheduler::getSchedulerAlgorithm() { return this->roundRobin; }

void Scheduler::addTCB(TCB *tcb) { this->scheduler.push_back(tcb); }

deque<TCB *> Scheduler::getSchedulerState() { return this->scheduler; }

void Scheduler::RemoveTCB(TCB *tcb)
{
    for (int i = 0; i < this->scheduler.size(); i++)
    {
        if (this->scheduler[i]->getProcess()->getID() == tcb->getProcess()->getID())
            this->scheduler.erase(this->scheduler.begin() + i);
    }
}

TCB *Scheduler::getFirstElement(bool drop)
{
    if (!this->scheduler.empty())
    {
        TCB *tcb = this->scheduler.front();
        if (drop)
            this->scheduler.pop_front();
        return tcb;
    }

    else
        return NULL;
}

TCB *Scheduler::scheduleTCB(bool isFinished)
{
    TCB *tcb;

    if (this->scheduler.size() > 1)
    {
        if (this->roundRobin == true)
            tcb = this->roundRobinAlgorithm(isFinished);
            
        else if (this->roundRobin == false)
            tcb = fifoAlgorithm();

        return tcb;
    }

    else return NULL;
}
        

TCB *Scheduler::roundRobinAlgorithm(bool isFinished)
{
    if (isFinished)
    {
        this->scheduler.pop_front();
        TCB *tcb = this->getFirstElement(false);
        int id = tcb->getProcess()->getID();
        tcb->update("executando");

        return tcb;
    }

    else
    {
        TCB *tcbBlock = this->getFirstElement(true);
        tcbBlock->update("bloqueado");
        this->scheduler.push_back(tcbBlock);

        TCB *tcbRes = this->getFirstElement(false);
        tcbRes->update("executando");

        return tcbRes;
    };
}

TCB *Scheduler::fifoAlgorithm()
{
    this->scheduler.pop_front();
    TCB *tcb = this->getFirstElement(false);
    int id = tcb->getProcess()->getID();
    tcb->update("executando");

    return tcb;
}

void Scheduler::printScheduler()
{
    printf("| ");
    for (int i = 0; i < this->scheduler.size(); i++)
    {
        int pid = this->scheduler[i]->getProcess()->getID();
        printf("%d | ", pid);
    }
    printf("\n\n");
}
