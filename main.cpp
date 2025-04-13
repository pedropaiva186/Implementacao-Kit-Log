#include "data.h"
#include <time.h>
#include <iostream>
#include "localSearch.h"
#include "construcao.h"

int main(){

    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instancias/att48.tsp";

    srand(time(NULL));

    Data & data = Data::getInstance();

    data.read(2, argv);

    Solution s = Construcao();

    std::cout << s.cost << std::endl;

    s.calculateCost();

    s.print();
  
    return 0;
}