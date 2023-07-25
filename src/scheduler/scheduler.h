#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <vector>
#include "../process/process.h"

using namespace std;

class Scheduler
{
private:

    static vector<"TCB"> scheduler;

    TCB roundRobinAlgorithm(bool isFinished) {
        if (isFinished == true) {
            // Terminar o processo atual
            // Colocar o próximo em execução
            // Puxar toda a fila pra cima  
        } else {
            // Colocar o processo atual no final da fila e salvar o contexto
            // Colocar o próximo em execução
            // Puxar toda a fila pra cima
        };
    };

    TCB fifoAlgorithm() {
        // Terminar o processo atual
        // Colocar o próximo em execução
        // Puxar toda a fila pra cima 
    };

public:

    bool schedulerAlgorithm;

    void setSchedulerAlgorithm(bool algorithm) {
        schedulerAlgorithm = algorithm;
    };

    bool getSchedulerAlgorithm() {
        return schedulerAlgorithm;
    };

    void addTCBToScheduler(TCB tcb) {
        scheduler.push_back(tcb);
    };

    // Realiza o escalonamento de acordo com a boolean schedulerAlgorithm
    // schedulerAlgorithm --> 0 = Round Robin, 1 = Fifo
    TCB scheduleTCB(bool isFinished)
    {
        if(schedulerAlgorithm == 0) {
            roundRobinAlgorithm(isFinished);
        };

        if(schedulerAlgorithm == 1) {
            fifoAlgorithm();
        }
    };

    void saveTCB() 
    {
        // Chamar função de salvar TCB
    };

    void processBlock()
    {
        // Chamar função de bloquear processo
    };

};

#endif