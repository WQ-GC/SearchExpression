#ifndef DECODE_MAP_H
#define DECODE_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "OperatorList.h"

void HandleOperandsPermutations();
void DecodeOpCount(int numOperators, int inMaxCount, int inCount, OPType* outOpArr);
int ComputeMaxMap(int inputVar);

#endif