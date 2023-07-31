#include <iostream>
#include "scheduler.h"
#include "tcb.h"

using namespace std;

/* Scheduler::Scheduler()
{
    aaaaa
}

*/

TCB Scheduler::roundRobinAlgorithm(bool isFinished)
{
    if (isFinished == true)
    {
        // Terminar o processo atual
        // Colocar o próximo em execução
        // Puxar toda a fila pra cima
    }
    else
    {
        // Colocar o processo atual no final da fila e salvar o contexto
        // Colocar o próximo em execução
        // Puxar toda a fila pra cima
    };
}

TCB Scheduler::fifoAlgorithm(){
    // Terminar o processo atual
    // Colocar o próximo em execução
    // Puxar toda a fila pra cima
};

void Scheduler::setSchedulerAlgorithm(bool algorithm)
{
    schedulerAlgorithm = algorithm;
};

bool Scheduler::getSchedulerAlgorithm()
{
    return schedulerAlgorithm;
};

void Scheduler::addTCBToScheduler(TCB tcb)
{
    scheduler.push_back(tcb);
};

TCB Scheduler::scheduleTCB(bool isFinished)
{
    if (schedulerAlgorithm == 0)
    {
        roundRobinAlgorithm(isFinished);
    };

    if (schedulerAlgorithm == 1)
    {
        fifoAlgorithm();
    }
};

void Scheduler::saveTCB(){
    // Chamar função de salvar TCB
};

void Scheduler::processBlock(){
    // Chamar função de bloquear processo
};
