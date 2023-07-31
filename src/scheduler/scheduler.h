#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <vector>
#include "process.h"
#include "tcb.h"

using namespace std;

class Scheduler
{
private:
    TCB tcb;

    vector<TCB> scheduler;

public:
    bool schedulerAlgorithm;

    void setSchedulerAlgorithm(bool algorithm);

    bool getSchedulerAlgorithm();

    Scheduler(TCB tcb);

    TCB roundRobinAlgorithm(bool isFinished);

    TCB fifoAlgorithm();

    void addTCBToScheduler(TCB tcb);

    // Realiza o escalonamento de acordo com a boolean schedulerAlgorithm
    // schedulerAlgorithm --> 0 = Round Robin, 1 = Fifo
    TCB scheduleTCB(bool isFinished);

    void saveTCB();

    void processBlock();
};

#endif