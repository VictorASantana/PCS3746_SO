#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Process
{
public:
    int id;
    int memoryBlocks;
    string instructions;
};

// Retorna um processo
Process createProcess(int memoryBlocks)
{
    int id = rand();
    Process proc;
    proc.id = id;
    proc.memoryBlocks = memoryBlocks;
    return proc;
}

#endif
