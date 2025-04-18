#include "localSearch.h"
#include "stdlib.h"
#include <iostream>

void RVND(Solution & s){

    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false){
        int n = (rand() % NL.size());

        switch(NL[n]){
            case 1:
                improved = bestImprovementSwap(s);
                break;
            case 2:
                improved = bestImprovement2OPT(s);
                break;
            case 3:
                improved = bestImprovementInsertion(s, 1);
                break;
            case 4:
                improved = bestImprovementInsertion(s, 2);
                break;
            case 5:
                improved = bestImprovementInsertion(s, 3);
                break;
            default:
                break;
        }

        if(improved) {
        NL = {1, 2, 3, 4, 5};
        } else {
            NL.erase(NL.begin() + n);
        }
    }
}

// Função que vai calcular a variação de todos os "2-OPT"
bool bestImprovement2OPT(Solution & s) {
    Data & data = Data::getInstance();
    auto & matriz = data.matrizAdj;
    int best_i, best_j;
    double best_delta = 0;

    // Definindo os índices dos possíveis vértices
    for(int i = 1; i < data.n - 1; i++) {
        // Definindo os índices do vértices do lado direito para fazer a troca
        for(int j = i + 1; j < data.n; j++) {

            // Aqui fazemos o calculo da possível inserção
            double delta = - matriz[s.route[i - 1]][s.route[i]] 
                - matriz[s.route[j]][s.route[j + 1]]
                + matriz[s.route[i - 1]][s.route[j]]
                + matriz[s.route[i]][s.route[j + 1]];

            if(delta < best_delta) {
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(best_delta < 0) {
        s.mov2OPT(s, best_i, best_j);
        s.cost += best_delta;
        return true;
    }

    return false;
}

// Função que vai comparar a variação de todos os "Insertion"
bool bestImprovementInsertion(Solution & s, int bloco) {
    Data & data = Data::getInstance();
    auto & matriz = data.matrizAdj;
    int indexVert = -1, indexFinal = -1;
    double best_delta = 0;

    // Definindo os possíveis vértices, colocando o bloco na subtração, pois o elemento que ele escolher será
    // o primeiro do bloco a ser movido
    for(int i = 1; i < data.n - bloco + 1; i++) {
        // Definindo os possíveis locais para ocupação, mirando nos vértices nos quais o vértice escolhido
        // será adicionado após ele
        for(int j = 0; j < data.n; j++) {
            // Retirando as condições desnecessárias, caso não haja mudança, ou se ele imitar um swap
            if(j == i || j == i - 1 || (j <= i + 1 + (bloco / 3) && j > i)) {
                continue;
            }

            double delta = - matriz[s.route[i - 1]][s.route[i]] - matriz[s.route[i + bloco - 1]][s.route[i + bloco]]
                    - matriz[s.route[j]][s.route[j + 1]] + matriz[s.route[i - 1]][s.route[i + bloco]] 
                    + matriz[s.route[j]][s.route[i]] + matriz[s.route[i + bloco - 1]][s.route[j + 1]];

            if(delta < best_delta) {
                best_delta = delta;
                indexVert = i;
                indexFinal = j;
            }
        }
    }

    if(best_delta < 0) {
        s.insertion(s, indexVert, indexFinal, bloco);
        s.cost += best_delta;
        return true;
    }

    return false;
}

bool bestImprovementSwap(Solution &s) {
    Data & data = Data::getInstance();
    auto & route = s.route;
    double bestDelta = 0;
    int bestI, bestJ, i, j;

    for(i = 1; i < data.n - 1; i++) {
        for(j = i + 1; j < data.n; j++) {
            double a_subtrair, a_somar, delta;

            if ((j == i + 1)){
                a_subtrair = data.matrizAdj[route[i - 1]][route[i]] + data.matrizAdj[route[j]][route[j + 1]];
                a_somar = data.matrizAdj[route[i - 1]][route[j]] + data.matrizAdj[route[i]][route[j + 1]];
            } else {
                a_subtrair = data.matrizAdj[route[i - 1]][route[i]] + data.matrizAdj[route[i]] [route[i + 1]] 
                            + data.matrizAdj[route[j - 1]][route[j]] + data.matrizAdj[route[j]][route[j + 1]];
                a_somar = data.matrizAdj[route[i - 1]][route[j]] + data.matrizAdj[route[j]] [route[i + 1]] 
                            + data.matrizAdj[route[j - 1]][route[i]] + data.matrizAdj[route[i]][route[j + 1]];
            }

            delta = a_somar - a_subtrair;

            if(delta < bestDelta) {
                bestDelta = delta;
                bestI = i;
                bestJ = j;
            }
        }
    }

    if(bestDelta < 0) {
        s.swap(bestI, bestJ);
        s.cost += bestDelta;
        return true;
    }

    return false;
}



Solution solve(){
    Solution s = Solution();
    s.buildTrivial();
    std::cout << "Solucao inicial:" << std::endl;
    s.print();
    std::cout << "Solucao final:" << std::endl;
    RVND(s);
    return s;
}