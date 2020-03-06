#include "DecodeMap.h"
#include "OperatorList.h"
#include "LinkedList.h"
#include "Limits.h"
#define MAX_ALLOWABLE_OPERANDS   10


void Permute(int l, int r) { 
  int i; 
  if (l == r) {
    printLinkedListItems();
  }
  else { 
    for (i = l; i <= r; i++) { 
      SwapOperands(getListNode(l), getListNode(i));
      Permute(l+1, r); 
      SwapOperands(getListNode(l), getListNode(i)); //backtrack 
    } 
  } 
} 

//Decode counter value into (000 -> 333 format)
//counter = 6  -> 012 Operators Encoded value
//counter = 13 -> 031 Operators Encoded value
void DecodeOpCount(int numOperators, int inMaxCount, int inCount, OPType* outOpArr) {
  //printf("\nDecode: %i", inCount);
  //Decode for Extreme left == inMaxCount

#if DEBUG
//  printf("\nDecode: ");
#endif
  for(int j = (numOperators-2); j >= 0; j--) {
    outOpArr[j] = (inCount / (int)(pow(MAX_SYMBOLS_TYPE,j+1)));
    inCount -= (outOpArr[j] * (pow(MAX_SYMBOLS_TYPE,j+1)));
#if DEBUG
    //printf("%i", inCount);
    //printf("\n%i",j);
//    printf("%i",outOpArr[j]);
#endif    
  }

  outOpArr[numOperators-1] = inCount;

#if DEBUG
//  printf("%i    ",outOpArr[numOperators-1]);//last value
#endif
}

//Specify max Operands
//2 Operands => 1 Operator ==> 4 Permutations
//3 Operands => 2 Operator ==> 4^2 Permutations
//4 Operands => 3 Operator ==> 4^3 Permutations
//5 Operands => 4 Operator ==> 4^4 Permutations
int ComputeMaxMap(int inputVar) {
  if(inputVar >= 2) {
    //printf("\nsizeof int: %i", sizeof(int));
    int totalOperands = inputVar - 1;

    long result = pow(MAX_SYMBOLS_TYPE, totalOperands)-1;
    //printf("\Max map count: %ld", result);
    //printf("\nINT MAX: %i", INT_MAX);
    if(result > INT_MAX) {
      printf("\nError: Exceed max allowable operands");
      return -1;
    }
    else
      return (int)result;
  }
  else {
    return -1;
  }
}