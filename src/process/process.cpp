#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include "process.h"

using namespace std;

Process::Process() {}

Process::Process(int memoryBlocks)
{
    int id = rand();
    string nomeArquivo = "./data/instr.txt";

    this->id = id;
    this->memoryBlocks = memoryBlocks;
    this->instructions = readInstructions(memoryBlocks, nomeArquivo);
}

int Process::getMemoryBlock()
{
    return this->memoryBlocks;
}

int Process::getID()
{
    return this->id;
}

void Process::resume(int pc)
{
    this->program_counter = pc;
}

int Process::block()
{
    int pc = this->program_counter;
    this->program_counter = 0;
    return pc;
}

vector<string> Process::readInstructions(int numberOfInstructions, const string &nomeArquivo)
{
    vector<string> linhas;
    ifstream arquivo;
    string linha;

    arquivo.open(nomeArquivo, ios::in);

    if (arquivo.is_open())
    {
        for (int i = 0; i < numberOfInstructions && std::getline(arquivo, linha); i++)
        {
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
