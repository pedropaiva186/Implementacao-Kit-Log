#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "construcao.h"

struct verticeECusto {
    int vertice;
    double custo;
};

std::vector<int> preencheCL() {
    Data &data = Data::getInstance();
    std::vector<int> c;

    for(int i = 2; i <= data.n; i++) {
        c.push_back(i);
    }

    return c;
}

// Calculando o custo de inserção de cada possível vértice ao final da solução
std::vector<verticeECusto> CalculaCusto(int &vertFinal, std::vector<int> &CL) {
    Data &data = Data::getInstance();
    std::vector<verticeECusto> custos = std::vector<verticeECusto>();
    verticeECusto aux;

    // Salvando o custo de cada possível inserção no vector com os custos
    for(int i : CL) {
        aux.vertice = i;
        aux.custo = data.matrizAdj[vertFinal][i];
        custos.push_back(aux);
    }

    return custos;
}

bool compareByCost(const verticeECusto &a, const verticeECusto &b) {
    return a.custo < b.custo;
}

Solution Construcao() {
    auto &matriz_adj = Data::getInstance().matrizAdj;
    Solution s;
    s.route = {1, 1};
    double custo_auxiliar = 0, duracao_auxiliar = 0;
    std::vector<int> CL = preencheCL();

    // Servirá como auxiliar para definirmos o vértice escolhido
    int r = 1;
    
    while(CL.size() != 0) {
        // Organizando e preenchendo o vector de custo de inserção
        std::vector<verticeECusto> custoInsercao = CalculaCusto(r, CL);
        std::sort(custoInsercao.begin(), custoInsercao.end(), compareByCost);

        // Escolhendo um valor aleatório dentre os possíveis
        double alpha = 0.5;
        verticeECusto selecionado = custoInsercao[rand() % (int) ceil(alpha * custoInsercao.size())];

        // Adicionando os valores referentes ao vértice escolhido
        duracao_auxiliar += selecionado.custo;
        custo_auxiliar += duracao_auxiliar;

        // Apagando o vértice escolhido do CL e colocando-o dentro da rota
        CL.erase(std::remove(CL.begin(), CL.end(), selecionado.vertice), CL.end());
        s.route.insert(s.route.begin() + s.route.size() - 1, selecionado.vertice);

        // Definindo o vértice final atual
        r = selecionado.vertice;
    }

    // Adicionando o custo da última aresta
    duracao_auxiliar += matriz_adj[r][1];
    custo_auxiliar += duracao_auxiliar;

    // Transferindo o valor do custo para a rota
    s.cost = custo_auxiliar;
    return s;
}