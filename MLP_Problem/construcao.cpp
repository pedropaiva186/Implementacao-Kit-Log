#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include "construcao.h"

struct verticeECusto {
    int vertice;
    double custo;
};

std::vector<int> preencheCL(int &n, int &n_ale) {
    std::vector<int> c = {};

    for(int i = 2; i <= n; i++) {
        if(i == n_ale) {
            continue;
        }
        c.push_back(i);
    }

    return c;
}

// Calculando o custo de inserção de cada possível vértice ao final da solução
std::vector<verticeECusto> CalculaCusto(int &vertFinal, std::vector<int> &CL, double ** matrizAdj) {
    std::vector<verticeECusto> custos = {};
    verticeECusto aux;

    // Salvando o custo de cada possível inserção no vector com os custos
    for(int i : CL) {
        aux.vertice = i;
        aux.custo = matrizAdj[vertFinal][i];
        custos.push_back(aux);
    }

    return custos;
}

bool compareByCost(const verticeECusto &a, const verticeECusto &b) {
    return a.custo < b.custo;
}

Solution Construcao() {
    // Utilizando a biblioteca random para obter números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());

    Data &data = Data::getInstance();
    auto &matriz_adj = data.matrizAdj;
    Solution s;
    auto &rota = s.route;
    double custo_auxiliar, duracao_auxiliar;
    rota = {1};

    // Inserindo um número aleatório na rota
    std::uniform_int_distribution<> ger(2, data.n);
    int n_ale = ger(gen);
    rota.push_back(n_ale);
    std::vector<int> CL = preencheCL(data.n, n_ale);
    duracao_auxiliar = matriz_adj[1][n_ale];
    custo_auxiliar = duracao_auxiliar;

    // Servirá como auxiliar para definirmos o vértice escolhido
    int r = n_ale;
    
    while(CL.size() != 0) {
        // Organizando e preenchendo o vector de custo de inserção
        std::vector<verticeECusto> custoInsercao = CalculaCusto(r, CL, matriz_adj);
        std::sort(custoInsercao.begin(), custoInsercao.end(), compareByCost);

        // Escolhendo um valor aleatório dentre os possíveis
        double alpha = 0.5;
        std::uniform_int_distribution<> ger(0, (int) floor(alpha * custoInsercao.size()));
        verticeECusto selecionado = custoInsercao[ger(gen)];

        // Adicionando os valores referentes ao vértice escolhido
        duracao_auxiliar += selecionado.custo;
        custo_auxiliar += duracao_auxiliar;

        // Apagando o vértice escolhido do CL e colocando-o dentro da rota
        CL.erase(std::remove(CL.begin(), CL.end(), selecionado.vertice), CL.end());
        rota.push_back(selecionado.vertice);

        // Definindo o vértice final atual
        r = selecionado.vertice;
    }

    // Adicionando o custo da última aresta
    duracao_auxiliar += matriz_adj[r][1];
    custo_auxiliar += duracao_auxiliar;

    // Transferindo o valor do custo para a rota
    rota.push_back(1);
    s.cost = custo_auxiliar;
    return s;
}