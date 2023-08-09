#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <deque>
#include "tcb.h"

using namespace std;

class Scheduler
{
private:
    bool roundRobin = true;
    deque<TCB *> scheduler = {};

public:
    Scheduler();

    void setSchedulerAlgorithm(bool);

    bool getSchedulerAlgorithm();

    deque<TCB *> getSchedulerState();

    void addTCB(TCB *);

    void RemoveTCB(TCB *);

    TCB *getFirstElement(bool);

    TCB *scheduleTCB(bool);

private:
    TCB *roundRobinAlgorithm(bool);

private:
    TCB *fifoAlgorithm();

public:
    void printScheduler();
};

#endif
