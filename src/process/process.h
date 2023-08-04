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
    int pc = 0;
    int type;
    int memoryBlocks;
    vector<string> instructions;

public:
    Process(int, int, int);

    int getMemoryBlock();

    int getID();

    int getPC();

    int getType();

    vector<string> getInstructions();

    void updatePC();

    void resume(int);

    int block();

private:
    vector<string> readInstructions(int, const string &);
};

#endif
