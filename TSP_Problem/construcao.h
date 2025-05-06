#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <iostream>
#include "solution.h"

struct InsertionInfo;

std::vector<int> preencheCL();

bool comparandoCusto(InsertionInfo& a, InsertionInfo& b);

void ordenarEmOrdemCrescente(std::vector<InsertionInfo>& vector);

void inserirNaSolucao(Solution& s, InsertionInfo& selecionado, std::vector<int>& CL);

std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL);

Solution Construcao();

#endif