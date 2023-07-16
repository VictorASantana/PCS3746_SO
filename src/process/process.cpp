#include <iostream>
#include <vector>
#include <string>
#include <cmath>
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

// Lógica para criação de processo
int main()
{
    string input;
    vector<string> formatedInput;
    string s;
    Process process;
    cout << "Criação de processo: ";
    getline(cin, input);
    stringstream ss(input);
    vector<string> v;

    while (getline(ss, s, ' '))
    {
        v.push_back(s);
    }

    if ((v[0]) == "create")
    {
        process = createProcess(std::stoi(v[v.size() - 1]));
    }

    cout << "Processo " << process.id << " de " << process.memoryBlocks << " blocos de memória.";

    return 0;
}