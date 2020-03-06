#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "LinkedList.h"
#include "OperatorList.h"
#include "DecodeMap.h"

#define DEFAULT_RESULT      10
#define DEFAULT_INPUTSIZE   4


//INT_MAX == 2147483647
//INT_MIN == -2147483648
//Precondition: Assumes inputs fall within Integer range

void PermuteOperands(int l, int r);
static int totalInVars = 0;
static int finalResult = DEFAULT_RESULT;//the value to be computed - default to 10

int main(int argc, char* argv[]) {
   
  if(argc == 1) {
  //No input arguments specified
    printf("Input Searched result: ");
    scanf("%i", &finalResult);

    while(totalInVars <2) {
      printf("Input number of operands: ");
      scanf("%i", &totalInVars);

      if(totalInVars < 2)
        printf("  Error: Cannot have less than 2 operands\n");
    }

    for(int i = 0; i < totalInVars; i++) {
      int inputOperand = 0;
      printf("Input operand #%i: ", (i+1));
      scanf("%i", &inputOperand);
      addListNode(inputOperand,1);
    }
#if DEBUG
    //printLinkedList();
#endif    
  }

  //Multiple parameters
  //Assume inputs are specified with commas AND no spaces
  else {
    finalResult = atoi(argv[1]);
    //printf("size: %u\n" , sizeof(computeResult));
    printf("\nUpdate Searched Result: %i" , finalResult);

    const char s[2] = ",";
    for(int i = 2; i < argc; i++) {
      //printf("Variables: %s\n" , argv[i]);
      //printf("sizeof: %i\n" , strlen(argv[i]));

      //Search for values separated by comm
      char* token = strtok(argv[i], s);

      while(token != NULL) {
        //printf("\n%i   new token: %s\n" , totalInVars, token);
        addListNode(atoi(token),1);
        totalInVars++;

        token = strtok(NULL, s);                
      }
    }
#if DEBUG
    //printLinkedList();
#endif
  }

  //Permute Operands
  PermuteOperands(0, ListSize()-1);
  return 0;
}

void PermuteOperands(int l, int r) {
  int i; 
  if (l == r) {
    //Permute Operators
    int maxMap = ComputeMaxMap(totalInVars);
    if(maxMap == -1) {
      printf("\nExceed MAX Operands, unable to handle");
      return;
    }

    //LinkedList contains all the inputs
    //Every new set of values, must be pushed into DB
    clearBackupLinkedList();
    StoreBackupList();//stored in Backup List pointed by llBackupHeadPtr
#if DEBUG
    printf("\nCurrent Operands permutation: ");
    printLinkedListItems();
#endif
    int totalOperators = totalInVars-1;
    OPType getOperators[totalOperators];
    for(int i = 0; i <= maxMap; i++) {
      clearLinkedList();//clear prev Operands list
      clearOpList();//clear prev Operator list

      //Handle Operator Permutations
      //Decode based on counter i
      //Binary operators require 2 Operands
      //For 4 Operands == require 3 Operators
      //For each operator == 4 possibilities (+-*/)
      //2 OPs: 0,0      -> 3,3
      //3 OPs: 0,0,0    -> 3,3,3
      //4 OPs: 0,0,0,0  -> 3,3,3,3
      DecodeOpCount(totalOperators, maxMap, i, getOperators);

      //Apply 1 set of Decoded Operators to current Operand Set
      LoadBackupList();//***Reload the same set of operands in each iteration

      for(int k = 0; k < totalOperators; k++) {
        addOpNode(getOperators[k], getListNode(k), getListNode(k+1));
      }
    
      char getExpression[MAX_EXPRESSION_CHARS] = "";
      printFullExpression(getExpression);
#if DEBUG
      printf("\n%s", getExpression);
#endif
      //Compute this expression
      int getNumer, getDenom;
      ComputeOpList(&getNumer, &getDenom);
      int result = getNumer/getDenom;
#if DEBUG
      printf(" = %.2f (float)",(float)getNumer/getDenom);
#endif
      //Check only for Integers
      if((getNumer % getDenom) == 0) {
        int result = getNumer/getDenom;

        if(finalResult == result) {
          printf("\n%s", getExpression);
        }
        else {
          float resultF = (float)getNumer/getDenom;
          //printf("\nNon-Integer Result: %f", resultF);
        }
      }
    }
    clearLinkedList();//clear prev Operands list
    clearOpList();//clear prev Operator list//    
    LoadBackupList();//reload the same set of operands
  }

  else { 
    for (i = l; i <= r; i++) { 
      SwapOperands(getListNode(l), getListNode(i));
      PermuteOperands(l+1, r);
      SwapOperands(getListNode(l), getListNode(i)); //backtrack 
    } 
  } 
}