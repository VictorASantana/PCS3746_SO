#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "process.h"
#include <bits/stdc++.h>

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