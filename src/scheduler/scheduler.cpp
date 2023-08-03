#include <iostream>
#include <deque>
#include "scheduler.h"
#include "tcb.h"
#include "process.h"

using namespace std;

Scheduler::Scheduler()
{
    this->schedulerAlgorithm = false;
    this->scheduler = {};
}

void Scheduler::setSchedulerAlgorithm(bool algorithm)
{
    this->schedulerAlgorithm = algorithm;
};

bool Scheduler::getSchedulerAlgorithm() // Se for false é RoundRobin se for true é FIFO
{
    return this->schedulerAlgorithm;
};

void Scheduler::addTCBToScheduler(TCB tcb)
{
    this->scheduler.push_back(tcb);
};

TCB Scheduler::getFirstElement()
{
    TCB tcb = this->scheduler.front();
    this->scheduler.pop_front();
    return tcb;
}

TCB Scheduler::scheduleTCB(bool isFinished)
{
    if (schedulerAlgorithm == false)
    {
        roundRobinAlgorithm(isFinished);
    };

    if (schedulerAlgorithm == true)
    {
        fifoAlgorithm();
    }
};

TCB Scheduler::roundRobinAlgorithm(bool isFinished)
{
    if (isFinished == true)
    {
        this->scheduler.pop_front();
        TCB tcb = this->getFirstElement();
        tcb.update("executando");

        return tcb;
    }
    else
    {
        TCB tcbBloq = this->getFirstElement();
        tcbBloq.update("bloqueado");
        this->scheduler.push_back(tcbBloq);

        TCB tcbRes = this->getFirstElement();
        tcbRes.update("executando");

        return tcbRes;
    };
}

TCB Scheduler::fifoAlgorithm()
{
    this->scheduler.pop_front();
    TCB tcb = this->getFirstElement();
    tcb.update("executando");

    return tcb;
};
