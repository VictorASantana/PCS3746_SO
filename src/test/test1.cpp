#include <string>
#include <iostream>

#include "tcb.h"
#include "process.h"

int main() {
    Process p(3);
    TCB t(p);
    string s;
    int i;
    
    s = t.getState();
    std::cout << s << "\n";

    i = t.update("bloqueado");
    if (i == 1) {
        s = t.getState();
        std::cout << s << "\n";
    }

    i = t.update("executando");
    if (i == 1) {
        s = t.getState();
        std::cout << s << "\n";
    }

    return 0;
}