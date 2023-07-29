// #include <iostream>
// #include <vector>
// #include <string>
// #include <cmath>
// #include <fstream>
// #include "process.h"
// #include <bits/stdc++.h>

// // Lógica para criação de processo
// int main()
// {
//     string input;
//     vector<string> formatedInput;
//     string s;
//     Process process;
//     cout << "Criação de processo: ";
//     getline(cin, input);
//     stringstream ss(input);
//     vector<string> v;

//     ifstream arquivo("instr.txt");

//     while (getline(ss, s, ' '))
//     {
//         v.push_back(s);
//     }

//     if ((v[0]) == "create")
//     {
//         process = createProcess(std::stoi(v[v.size() - 1]));
//     }

//     cout << "Processo " << process.id << " de " << process.memoryBlocks << " blocos de memória.\n";

//     for (int i = 0; i < process.memoryBlocks; i++)
//     {
//         cout << "Instrucao atual: " << process.instructions[i] << "\n";
//     }

//     cout << process.program_counter;
//     process.block();
//     cout << process.program_counter;
//     process.resume(5);
//     cout << process.program_counter;
//     getline(cin, input);

//     return 0;
// }
