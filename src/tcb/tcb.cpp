#include <string>
#include "tcb.h"
#include "process.h"

using namespace std;

TCB::TCB(Process *proc) {this->process = proc;}

string TCB::getState() {return this->state;}

Process* TCB::getProcess() {return this->process;}

int TCB::update(string new_state)
{
    if (new_state == "bloqueado")
    {
        int procPC = this->process->block();
        this->pc = procPC;
        this->state = "pronto";
    } 
    
    else if (new_state == "executando")
    {
        this->state = new_state;
        this->process->resume(this->pc);
    }

    return 1;
}

void TCB::printTCB()
{
    std::cout << "TCB estado: " << this->state << endl;
    std::cout << "TCB pc: " << this->pc << endl << endl;
}
