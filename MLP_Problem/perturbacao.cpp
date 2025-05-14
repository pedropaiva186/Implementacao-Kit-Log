#include <iostream>
#include "solution.h"
#include "subsequence.h"
#include <vector>
#include <cmath>

Solution perturbacao(Solution &s) {
    Data &data = Data::getInstance();

    int n = data.n;
    int half_n = n / 2;
    int max_seg = ceil(n / 10.0);

    // Criando a solução que será retornada, que será baseada na solução advinda do parâmetro
    Solution solutionAux = s;
    Subsequence subseq;
    std::vector<std::vector<Subsequence>> matrizSub(s.route.size(), std::vector<Subsequence>(s.route.size()));

    // Atualizando a matriz de subsequências a partir da solução atual
    updateAllSubseq(s, matrizSub);

    int tam_seg_i, tam_seg_j, i, j;
    std::vector<int> seg_i, seg_j;

    auto &rota = solutionAux.route;

    // Definindo o tamanho dos dois segmentos que trocarão de lugar
    tam_seg_i = 2 + (rand() % (max_seg - 1));
    tam_seg_j = 2 + (rand() % (max_seg - 1));

    // Definindo os indíces
    i = 1 + (rand() % (half_n - tam_seg_i));
    j = half_n + (rand() % (n - tam_seg_j - half_n + 1));

    subseq = Subsequence::Concatenate(matrizSub[0][i - 1], matrizSub[j][j + tam_seg_j - 1]);

    // Caso sejam adjascentes
    if(i + tam_seg_i != j) {
        subseq = Subsequence::Concatenate(subseq, matrizSub[i + tam_seg_i][j - 1]);
    }

    subseq = Subsequence::Concatenate(subseq, matrizSub[i][i + tam_seg_i - 1]);
    subseq = Subsequence::Concatenate(subseq, matrizSub[j + tam_seg_j][data.n]);

    seg_i.insert(seg_i.begin(), rota.begin() + i, rota.begin() + i + tam_seg_i);
    seg_j.insert(seg_j.begin(), rota.begin() + j, rota.begin() + j + tam_seg_j);

    // Retirando o segmento "j" e pondo o segmento "i" no lugar
    rota.insert(rota.begin() + j, seg_i.begin(), seg_i.end());
    rota.erase(rota.begin() + j + tam_seg_i, rota.begin() + j + tam_seg_i + tam_seg_j);

    // Retirando o segmento "i" e pondo o segmento "j" no lugar
    rota.insert(rota.begin() + i, seg_j.begin(), seg_j.end());
    rota.erase(rota.begin() + i + tam_seg_j, rota.begin() + i + tam_seg_j + tam_seg_i);

    solutionAux.cost = subseq.C;

    return solutionAux;
}