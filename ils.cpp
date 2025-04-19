#include <iostream>
#include <cmath>
#include "solution.h"
#include "construcao.h"
#include "localSearch.h"
#include "perturbacao.h"

Solution ils(int maxIter, int maxIterIls) {
    Solution bestOfAll;
    bestOfAll.cost = INFINITY;

    for(int i = 0; i < maxIter; i++) {
        Solution s = Construcao();
        Solution best = s;

        int iterIls = 0;

        while(iterIls <= maxIterIls) {
            RVND(s);
            
            if(s.cost < best.cost) {
                best = s;
                iterIls = 0;
            }

            s = perturbacao(best);
            iterIls++;
        }

        if(best.cost < bestOfAll.cost) {
            bestOfAll = best;
        }
    }

    return bestOfAll;
}