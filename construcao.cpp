#include <iostream>
#include "construcao.h"

/*
* Esse struct serve para armazenar as informações importantes para que possamos executar o GRASP, ele guarda o vértice
* a ser inserido, a aresta que será removida, e o custo desta inserção no tour.
*/
struct InsertionInfo {
    int verticeInserido;
    int arestaRemovida;
    double custo;
};

/*
* Esta função serve para calcular o custo de inserção de cada possível vértice entre cada possível par de vértices, onde
* ele vai receber uma solução inicial, um s', que não estará completamente preenchida, terá apenas subconjunto de vértices,
* e o "CL", que equivale ao restante dos vértices, aqueles que fazem parte do conjunto total de vértices da solução, mas
* que não estão inclusos na solução inicial.
*/
std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL) {
    // Definindo o vector que armazenará as inserções
    std::vector<InsertionInfo> valoresDeInsercao = std::vector<InsertionInfo>((s.route.size() - 1) * CL.size());
}
