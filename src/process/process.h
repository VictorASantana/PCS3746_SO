#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Process
{
    private:
    int id;
    int memoryBlocks;
    int pc;
    vector<string> instructions;

    public:
    Process();

    Process(int, int);

    int getMemoryBlock();

    int getID();

    int getPC();

    void updatePC();

    void resume(int);

    int block();

    private: vector<string> readInstructions(int, const string&);
};

#endif
