#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

class Process
{
public:
    int id;
    int memoryBlocks;
    int program_counter;
    vector<string> instructions;
    void resume(int pc)
    {
        this->program_counter = pc;
    }
    void block()
    {
        this->program_counter = 0;
    }
};

std::vector<std::string> readInstructions(int numberOfInstructions, const std::string &nomeArquivo)
{
    std::vector<std::string> linhas;
    std::ifstream arquivo;
    arquivo.open(nomeArquivo, ios::in);
    std::string linha;

    if (arquivo.is_open())
    {
        for (int i = 0; i < numberOfInstructions && std::getline(arquivo, linha); i++)
        {
            if (i > 0)
                linhas.push_back(linha);
        }

        arquivo.close();
    }
    else
    {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }
    linhas.push_back("hlt");
    return linhas;
}

// Retorna um processo
Process createProcess(int memoryBlocks)
{
    int id = rand();
    Process proc;
    std::string nomeArquivo = "instr.txt";
    proc.id = id;
    proc.memoryBlocks = memoryBlocks;
    proc.instructions = readInstructions(memoryBlocks, nomeArquivo);
    return proc;
}

#endif
