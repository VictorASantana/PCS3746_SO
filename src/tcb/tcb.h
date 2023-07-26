#ifndef TCB_H
#define TCB_H

#include <string>
#include "process.h"

using namespace std;

class TCB
{
    private:
    Process process;
    string state;
    int pc;

    public:
    TCB(Process);

    string getState();

    Process getProcess();

    int update(string);
};

#endif
