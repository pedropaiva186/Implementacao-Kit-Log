#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
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
    
    // Pegando a matriz de adjascência, que será necessária para o cálculo do custo
    Data &data = Data::getInstance();
    double** &matriz = data.matrizAdj;

    // Contador de cada InsertionInfo que for inserido no vector
    int l = 0;
    
    // Fazemos o for desse tamanho, pois ele serve para passar em cada possível local no qual podemos inserir um novo vértice
    for(int a = 0; a < s.route.size() - 1; a++) {
        // Definindo os vértices nos quais será calculado a possível inserção
        int i = s.route[a];
        int j = s.route[a + 1];
        
        // Percorrendo cada possível vértice dos CL
        for(int k : CL) {
            valoresDeInsercao[l].custo = matriz[i][k] + matriz[j][k] - matriz[i][j];
            valoresDeInsercao[l].verticeInserido = k;
            /* 
            * Aqui o valor do vértice de inserção é o "a", porque ele representa o espaço que será inserido o novo 
            * vértice, como por exemplo, no tour {1, 2, 3, 1}, temos os possíveis locais entre {1, 2}, {2, 3} e 
            * {3, 1}, aí nesse caso, a = 0, equivale ao primeiro, e assim sucessivamente
            */
            valoresDeInsercao[l].arestaRemovida = a;
            l++;
        }
    }

    return valoresDeInsercao;
}

// Preenche CL com os vértices restantes, pois o vértice 1, já está na matriz
std::vector<int> preencheCL() {
    Data &data = Data::getInstance();
    std::vector<int> c;

    // Onde os termos do "for" ficam desse jeito por conta da forma de pesquisa de custo da matriz de adjascência
    for(int i = 2; i <= data.n; i++) {
        c.push_back(i);
    }

    return c;
}

// Definindo a forma como o "sort" vai avaliar a ordem do array, que será através do custo de cada opção
bool comparandoCusto(InsertionInfo& a, InsertionInfo& b) {
    return a.custo < b.custo;
}

// Aqui o código que vai realmente ordenar o array
void ordenarEmOrdemCrescente(std::vector<InsertionInfo>& vector) {
    std::sort(vector.begin(), vector.end(), comparandoCusto);
}

void inserirNaSolucao(Solution& s, InsertionInfo& selecionado, std::vector<int>& CL) {
    // Comando para retirar o vértice escolhido do CL
    CL.erase(std::remove(CL.begin(), CL.end(), selecionado.verticeInserido), CL.end());
    // Definindo uma referência para a rota, para facilitar a escrita do código abaixo
    std::vector<int>& route = s.route;

    // Inserindo o vértice escolhido no local desejado
    route.insert(route.begin() + selecionado.arestaRemovida + 1, selecionado.verticeInserido);
    s.cost += selecionado.custo;
}

// Agora vamos implementar o "Construção()", pois a função acima serve apenas para mapear todas as opções de inserção
// que temos
Solution Construcao() {

    Solution s;
    // Criando o vector inicial, que será preenchido com os vértices do CL
    s.route = std::vector<int>(2, 1);
    s.cost = 0;
    std::vector<int> CL = preencheCL();

    while(CL.size() != 0) {
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, CL);
        ordenarEmOrdemCrescente(custoInsercao);
        // Definimos um alpha fixo porque esse valor denota uma boa média entre aleatoriedade e um número bom o suficiente
        double alpha = 0.5;
        /*
        * Aqui nós definimos um índice aleatório dentre os possíveis, fazendo isso da seguinte maneira: nós
        * primeiro vamos pegar a quantidade de escolhas possíveis, colocando a porcentagem "alpha" vezes
        * o tamanho do array de possibilidades, e então vamos usar o "(int) ceil()", para que pegamos o teto
        * do número dado no formato de inteiro, então vamos usar o "rand()", para escolher um número
        * aleatório, e com o "%", usamos módulo para poder definir um teto para esse número aleatório,
        * e assim escolhemos o indíce de um elemento dentre os possíveis.
        */
        int selecionado = rand() % (int) ceil(alpha * custoInsercao.size());
        inserirNaSolucao(s, custoInsercao[selecionado], CL);
    }

    return s;
}