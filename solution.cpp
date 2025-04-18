#include "solution.h"
#include <iostream>

void Solution::print(){
    std::cout << "Route: ";
    for(int i = 0; i < Data::getInstance().n; i++){
        std::cout << route[i] << " - ";
    }
    std::cout << route[Data::getInstance().n] << std::endl;
    std::cout << "Cost: " << cost << std::endl;
}

void Solution::calculateCost() {
    Data& data = Data::getInstance();
    auto & matriz = data.matrizAdj;
    cost = 0;
    int vert1, vert2;

    for(int i = 0; i < data.n; i++) {
        vert1 = route[i];
        vert2 = route[i + 1];

        cost += matriz[vert1][vert2];
    }
}

void Solution::copy(const Solution &other){
    route = std::vector<int>(other.route);
    cost = other.cost;
}

void Solution::buildTrivial(){
    Data & data = Data::getInstance();
    int i;

    for(i = 1; i <= data.n; i++){
        route[i-1] = i;
    }
    route[data.n] = 1;
    cost = 0;
    for(i = 0; i < data.n - 1; i++){
        cost += data.matrizAdj[route[i]][route[i+1]];
    }
    cost += data.matrizAdj[route[data.n-1]][route[0]];
}

void Solution::swap(const int i, const int j){
    Data & data = Data::getInstance();
    
    int aux = route[i];
    route[i] = route[j];
    route[j] = aux;
    
}

// Função que executará o 2-OPT
void Solution::mov2OPT(Solution & s, int init, int fim) {
    Data & data = Data::getInstance();

    while(init < fim) {
        int aux = s.route[init];

        s.route[init] = s.route[fim];
        s.route[fim] = aux;

        init++;
        fim--;
    }
}

// Função que executará o Insertion
void Solution::insertion(Solution & s, int posVert, int posInserir, int bloco) {
    Data & data = Data::getInstance();
    auto & rota = s.route;
    std::vector<int> vert;

    vert.insert(vert.begin(), rota.begin() + posVert, rota.begin() + posVert + bloco);

    if(posVert < posInserir) {
        rota.insert(rota.begin() + posInserir + 1, vert.begin(), vert.end());
        rota.erase(rota.begin() + posVert, rota.begin() + posVert + bloco);
    } else {
        rota.erase(rota.begin() + posVert, rota.begin() + posVert + bloco);
        rota.insert(rota.begin() + posInserir + 1, vert.begin(), vert.end());
    }
}