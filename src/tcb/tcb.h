#ifndef TCB_H
#define TCB_H

#include <string>
#include "process.h"

using namespace std;

class TCB
{
    private:
    Process* process;
    string state = "pronto";
    int pc = 0;

    public:
    TCB(Process*);

    string getState();

    Process* getProcess();

    int update(string);

    void printTCB();
};

#endif
