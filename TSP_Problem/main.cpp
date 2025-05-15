#include "data.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include "ils.h"
#include "solution.h"

int main() {
    auto inicio = std::chrono::high_resolution_clock::now();

    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instances/burma14.tsp";

    srand(time(NULL));

    Data & data = Data::getInstance();

    data.read(2, argv);

    Solution s;

    int maxIter = 50, maxIterIls = data.n >= 150 ? data.n / 2: data.n;

    s = ils(maxIter, maxIterIls);

    s.print();

    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;

    std::ofstream tempo("tempo.txt", std::ios::app);
    
    if(tempo.is_open()) {
        tempo << "+ " << duracao.count() << std::endl;
        tempo.close();
    }

    std::ofstream custo("custo.txt", std::ios::app);

    if(custo.is_open()) {
        custo << "+ " << s.cost << std::endl;
    }
  
    return 0;
}