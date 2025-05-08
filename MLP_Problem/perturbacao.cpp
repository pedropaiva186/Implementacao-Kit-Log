#include <iostream>
#include "solution.h"
#include <vector>
#include <cmath>
#include <random>

Solution perturbacao(Solution & s) {
    // Setando a semente para geração de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    Data & data = Data::getInstance();

    // Criando a solução que será retornada, que será baseada na solução advinda do parâmetro
    Solution solutionAux = s;

    int tam_seg_i, tam_seg_j, i, j;
    std::vector<int> seg_i, seg_j;
    double deltaCusto = 0;

    auto & rota = solutionAux.route;
    auto & matriz = data.matrizAdj;

    std::uniform_int_distribution<> distTam(2, std::ceil(data.n / 10.0));

    // Definindo o tamanho dos dois segmentos que trocarão de lugar
    tam_seg_i = distTam(gen);
    tam_seg_j = distTam(gen);

    // Serão os indíces que definirão as posições dos vértices
    // Onde esse calculo ficou grande pois estou impondo limites para os valores nos quais "i" e "j" podem
    // assumir, para que esse processo nunca falhe e leve O(1).

    std::uniform_int_distribution<> distIndex1(1, (data.n / 2) - tam_seg_i);
    std::uniform_int_distribution<> distIndex2(data.n / 2, data.n - tam_seg_j);

    i = distIndex1(gen);
    j = distIndex2(gen);

    // Calculando o impacto da mudança no custo
    if(i + tam_seg_i == j) {
        deltaCusto = - matriz[rota[i - 1]][rota[i]] - matriz[rota[i + tam_seg_i - 1]][rota[i + tam_seg_i]]
                     - matriz[rota[j + tam_seg_j - 1]][rota[j + tam_seg_j]] + matriz[rota[i - 1]][rota[j]]
                     + matriz[rota[j + tam_seg_j - 1]][rota[i]] + matriz[rota[i + tam_seg_i - 1]][rota[j + tam_seg_j]];
    } else {
        deltaCusto = - matriz[rota[i - 1]][rota[i]] - matriz[rota[i + tam_seg_i - 1]][rota[i + tam_seg_i]]
                     - matriz[rota[j - 1]][rota[j]] - matriz[rota[j + tam_seg_j - 1]][rota[j + tam_seg_j]]
                     + matriz[rota[i - 1]][rota[j]] + matriz[rota[j + tam_seg_j - 1]][rota[i + tam_seg_i]]
                     + matriz[rota[j - 1]][rota[i]] + matriz[rota[i + tam_seg_i - 1]][rota[j + tam_seg_j]];
    }

    seg_i.insert(seg_i.begin(), rota.begin() + i, rota.begin() + i + tam_seg_i);
    seg_j.insert(seg_j.begin(), rota.begin() + j, rota.begin() + j + tam_seg_j);

    // Retirando o segmento "j" e pondo o segmento "i" no lugar
    rota.insert(rota.begin() + j, seg_i.begin(), seg_i.end());
    rota.erase(rota.begin() + j + tam_seg_i, rota.begin() + j + tam_seg_i + tam_seg_j);

    // Retirando o segmento "i" e pondo o segmento "j" no lugar
    rota.insert(rota.begin() + i, seg_j.begin(), seg_j.end());
    rota.erase(rota.begin() + i + tam_seg_j, rota.begin() + i + tam_seg_j + tam_seg_i);

    solutionAux.cost += deltaCusto;

    return solutionAux;
}