#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "solution.h"

void RVND(Solution & s);

bool bestImprovementSwap(Solution & s);

bool bestImprovement2OPT(Solution & s);

bool bestImprovementInsertion(Solution & s, int bloco);

Solution solve();

#endif // LOCAL_SEARCH_H