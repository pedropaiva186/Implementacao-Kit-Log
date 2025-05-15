#ifndef SOLUTION_H
#define SOLUTION_H

#include "data.h"
#include <vector>

struct Solution
{
    std::vector<int> route;
    double cost;

    Solution(std::vector<int> route, double cost): route(route), cost(cost) {}
    Solution() : route(std::vector<int>(Data::getInstance().n + 1)), cost(0) {}
    Solution(const Solution &s) : route(s.route), cost(s.cost) {}

    void calculateCostAcum();

    void buildTrivial();

    void calculateCost();

    void print();

    void copy(const Solution & other);

    void swap(const int i, const int j);

    void mov2OPT(Solution & s, int init, int fim);

    void insertion(Solution & s, int init, int fim, int bloco);
};


#endif