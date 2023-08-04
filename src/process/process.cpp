#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include "process.h"

using namespace std;

Process::Process(int memoryBlocks, int id, int type)
{
    string nomeArquivo = "./data/instr.txt";

    this->id = id;
    this->type = type;
    this->memoryBlocks = memoryBlocks;
    this->instructions = readInstructions(memoryBlocks - 1, nomeArquivo);
}

int Process::getMemoryBlock() { return this->memoryBlocks; }

int Process::getID() { return this->id; }

int Process::getPC() { return this->pc; }

int Process::getType() { return this->type; }

vector<string> Process::getInstructions() { return this->instructions; }

void Process::updatePC() { this->pc = this->pc + 1; }

void Process::resume(int pc) { this->pc = pc; }

int Process::block()
{
    int pc = this->pc;
    this->pc = 0;
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
        for (int i = 0; i < numberOfInstructions && getline(arquivo, linha); i++)
            linhas.push_back(linha);

        linhas.push_back("HLT");
        arquivo.close();
    }

    else
        cout << "Não foi possível abrir o arquivo." << endl;

    return linhas;
}
