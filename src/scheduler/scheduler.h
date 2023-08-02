#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <deque>
#include "process.h"
#include "tcb.h"

using namespace std;

class Scheduler
{
    private:

    bool schedulerAlgorithm;

    deque<TCB> scheduler;

    public:
    Scheduler();

    void setSchedulerAlgorithm(bool);

    bool getSchedulerAlgorithm();

    void addTCBToScheduler(TCB);

    TCB getFirstElement();

    TCB scheduleTCB(bool);

    TCB roundRobinAlgorithm(bool);

    TCB fifoAlgorithm();

};

#endif