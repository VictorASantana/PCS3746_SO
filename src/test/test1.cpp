#include <string>
#include <iostream>
#include <vector>

#include "tcb.h"
#include "process.h"
#include "memory.h"
#include "so.h"

using namespace std;

int main() {
    OperatingSystem SO;
    TCB *t;
    int pid;

    SO.createProcess(3);
    SO.createProcess(4);

    pid = SO.getProcessID(0);
    SO.killProcess(pid);
    SO.compactMem();
    t = SO.getTCB(pid);

    if (t == NULL) {
        std::cout << "Processo não encontrado!" << "\n";
    } else {
        std::cout << pid << "\n";
    }   

    return 0;
}
