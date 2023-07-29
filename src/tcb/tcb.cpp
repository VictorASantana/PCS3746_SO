#include <string>
#include "tcb.h"
#include "process.h"

using namespace std;

TCB::TCB(Process proc)
{
    this->process = proc;
    this->state = "pronto";
    this->pc = 0;
}

string TCB::getState()
{
    return this->state;
}

Process TCB::getProcess()
{
    return this->process;
}

int TCB::update(string new_state)
{
    if (new_state == "bloqueado") {
        int procPC = this->process.block();
        this->pc = procPC;
        this->state = "pronto";
    } 
    
    else if (new_state == "executando") {
        this->state = new_state;
        this->process.resume(pc);
    }

    return 1;
}
