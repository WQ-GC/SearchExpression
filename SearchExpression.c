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

int main(int argc, char* argv[]) {
  int totalInVars = 0;
  int finalResult = DEFAULT_RESULT;//the value to be computed - default to 10
    
  if(argc == 1) {
  //No input arguments specified
    printf("Input Final result: ");
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
    
    printLinkedList();
  }

  //Multiple parameters
  //Assume inputs are specified with commas AND no spaces
  else {
    finalResult = atoi(argv[1]);
    //printf("size: %u\n" , sizeof(computeResult));
    printf("Update Final Result: %i\n" , finalResult);

    const char s[2] = ",";
    for(int i = 1; i < argc; i++) {
      //printf("Variables: %s\n" , argv[i]);
      //printf("sizeof: %i\n" , strlen(argv[i]));

      //Search for values separated by comm
      char* token = strtok(argv[i], s);

      while(token != NULL) {
        //printf("\n%i   new token: %s\n" , totalInVars, token);
        addListNode(atoi(token),1);
        //printLinkedList();
        totalInVars++;

        token = strtok(NULL, s);                
      }
    }
    //printLinkedList();
  }

  //LinkedList contains all the inputs
  //Every new set of values, must be pushed into DB
  StoreBackupList();//stored in Backup List pointed by llBackupHeadPtr

#if NOT_READY
  //Shuffle Operands
  //HandleOperandsPermutations();
  bool endPermute = false;
  while(!endPermute) {
    LoadBackupList();//reload new list
    endPermute = PermuteList();
  }
#endif


  //Shuffle Operators
  int maxMap = ComputeMaxMap(totalInVars);
  if(maxMap == -1) {
    printf("\nExceed MAX Operands, unable to handle");
    return 0;
  }

  int totalOperators = totalInVars-1;
  OPType getOperators[totalOperators];
  for(int i = 0; i <= maxMap; i++) {
    clearLinkedList();
    clearOpList();

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
    LoadBackupList();//reload the same set of operands
    //printLinkedList();

    for(int k = 0; k < totalOperators; k++) {
      addOpNode(getOperators[k], getListNode(k), getListNode(k+1));
    }
    
    char getExpression[MAX_EXPRESSION_CHARS] = "";
    printFullExpression(getExpression);
    printf("%s", getExpression);

    //Compute this expression
    int getNumer, getDenom;
    ComputeOpList(&getNumer, &getDenom);
    //printf("\nResult: %f",(float)getNumer/getDenom);
    int result = getNumer/getDenom;
    printf(" = %i", result);
    if((getNumer % getDenom) == 0) {
      int result = getNumer/getDenom;

      if(finalResult == result) {
        printf("   [MATCHED] %i", finalResult);
      }
    }
    else {
      float resultF = (float)getNumer/getDenom;
      //printf("\nNon-Integer Result: %f", resultF);
    }
  }
  return 0;
}

