#include <string>
#include "tcb.h"
#include "process.h"

using namespace std;

TCB::TCB(Process proc)
{
    process = proc;
    state = "pronto";
    pc = 0;
}

string TCB::getState()
{
    return state;
}

Process TCB::getProcess()
{
    return process;
}

int TCB::update(string new_state)
{
    if (new_state == "bloqueado") {
        int procPC = process.block();
        pc = procPC;
        state = "pronto";
    } 
    
    else if (new_state == "executando") {
        state = new_state;
        process.resume(pc);
    }

    return 1;
}
