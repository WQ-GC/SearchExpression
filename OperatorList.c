#include "OperatorList.h"

//OpNode consists of 5 data
//opLeft points to the operator node left of expression
//opRight points to the operator node right of expression
//leftOperand points to the left operand of this operator
//rightOperand points to the right operand of this operator
//operVar holds the enum for this operator
void simplifyResult(int* inNumerPtr,int* inDenomPtr) {
  int temp = 0;
  int a = *inNumerPtr;
  int b = *inDenomPtr;

  while(b != 0) {
    temp = b;
    b = a % b;
    a = temp;
  }    
  //printf("\nGreatest common divisor: %i", temp);

  (*inNumerPtr) /= temp;
  (*inDenomPtr) /= temp;
}

void ComputeNode(OpNode* inNodePtr, int* outResultNumer, int* outResultDenom) {
  //OpNode* ptr = inNode;
  //Compute result
  *outResultNumer = 0;
  *outResultDenom = 0;

  if(inNodePtr->operVar == OP_TIMES) {
    *outResultNumer = (inNodePtr->leftOperand->numer) * (inNodePtr->rightOperand->numer);
    *outResultDenom = (inNodePtr->leftOperand->denom) * (inNodePtr->rightOperand->denom);
    ////printf("\n%i/%i (*) %i/%i Result: %i/%i", inNodePtr->leftOperand->numer, inNodePtr->leftOperand->denom 
    ////                                      , inNodePtr->rightOperand->numer, inNodePtr->rightOperand->denom
    ////                                      , *outResultNumer, *outResultDenom);
  }

  else if (inNodePtr->operVar == OP_DIVIDE) {
    //same as multiply inverse of 2nd operand
    *outResultNumer = (inNodePtr->leftOperand->numer) * (inNodePtr->rightOperand->denom);
    *outResultDenom = (inNodePtr->leftOperand->denom) * (inNodePtr->rightOperand->numer);
    ////printf("\n%i/%i (/) %i/%i Result: %i/%i", inNodePtr->leftOperand->numer, inNodePtr->leftOperand->denom 
    ////                                        , inNodePtr->rightOperand->numer, inNodePtr->rightOperand->denom
    ////                                        , *outResultNumer, *outResultDenom);
  }

  //a/b + c/d == ((a * d) + (c * b)) / (b * d)
  else if (inNodePtr->operVar == OP_PLUS) {
    *outResultNumer = ((inNodePtr->leftOperand->numer) * (inNodePtr->rightOperand->denom)) 
                    + ((inNodePtr->rightOperand->numer) * (inNodePtr->leftOperand->denom));

    *outResultDenom = (inNodePtr->leftOperand->denom) * (inNodePtr->rightOperand->denom);
    ////printf("\n%i/%i (+) %i/%i Result: %i/%i", inNodePtr->leftOperand->numer, inNodePtr->leftOperand->denom 
    ////                                        , inNodePtr->rightOperand->numer, inNodePtr->rightOperand->denom
    ////                                        , *outResultNumer, *outResultDenom);
  }

  //a/b - c/d == ((a*d) - (c*b)) / (b * d)
  else if (inNodePtr->operVar == OP_MINUS){
    *outResultNumer = ((inNodePtr->leftOperand->numer) * (inNodePtr->rightOperand->denom)) 
                    - ((inNodePtr->rightOperand->numer) * (inNodePtr->leftOperand->denom));

    *outResultDenom = (inNodePtr->leftOperand->denom) * (inNodePtr->rightOperand->denom);
    ////printf("\n%i/%i (-) %i/%i Result: %i/%i", inNodePtr->leftOperand->numer, inNodePtr->leftOperand->denom 
    ////                                        , inNodePtr->rightOperand->numer, inNodePtr->rightOperand->denom
    ////                                        , *outResultNumer, *outResultDenom);
  }

  //Simplify result a/b -> c/d
  simplifyResult(outResultNumer, outResultDenom);
  ////printf("  == simplified %i/%i", *outResultNumer, *outResultDenom);
}


void HandleNodeLinks(OpNode* inNodePtr, int inResultNum, int inResultDenom) {  
  //if Left most OpNode
  if(inNodePtr->opLeft == NULL) {
    //Link the rightOperand == shared with next OpNode's leftOperand
    inNodePtr->rightOperand->numer = inResultNum;
    inNodePtr->rightOperand->denom = inResultDenom;
    
    //Update LinkedList Head
    setLinkedListHead(inNodePtr->rightOperand);
    //printf("\nllHeadPtr': %p", (getLinkedListHead()));
    //printLinkedList();

    //Dellocate Left Operand
    //printf("\nfree inNodePtr->leftOperand: %p", inNodePtr->leftOperand);
    free(inNodePtr->leftOperand);
    
    //Update OpNode Head
    //printf("\ngetOpListHead(): %p", (getOpListHead()));
    setOpListHead(inNodePtr->opRight);
    //printf("\nupdate getOpListHead(): %p", (getOpListHead()));

    //Update right OpNode's left operator
    if(inNodePtr->opRight != NULL)
      inNodePtr->opRight->opLeft = NULL;

    //Handle NULL links
    inNodePtr->leftOperand = NULL;
    inNodePtr->rightOperand = NULL;
    inNodePtr->opLeft = NULL;
    inNodePtr->opRight = NULL;

    //deallocate this node
    //printf("\nfree inNodePtr: %p", inNodePtr);
    free(inNodePtr);
    inNodePtr = NULL;//reset to head
    //printf("\ngetOpListHead(): %p", (getOpListHead()));
    //printf("\ngetHeadPtr     : %p", getHeadPtr);
    //printf("\ninNodePtr: %p", inNodePtr);
  }

  //if Right most OpNode (mirror image of Left mode OpNode)
  else if(inNodePtr->opRight == NULL) {
    //Link the leftOperand == shared with next OpNode's leftOperand
    inNodePtr->leftOperand->numer = inResultNum;
    inNodePtr->leftOperand->denom = inResultDenom;

    //Update LinkedList Head  
    //setLinkedListHead(inNodePtr->rightOperand);
    //printf("\nllHeadPtr': %p", (getLinkedListHead()));
    //printLinkedList();

    //Update Extreme right ListNode to point NULL
    ListNode* removePtr = inNodePtr->rightOperand;
    inNodePtr->rightOperand = NULL;
    inNodePtr->leftOperand->next = NULL;

    //Dellocate Left Operand
    //printf("\nfree inNodePtr->rightOperand: %p", inNodePtr->rightOperand);
    free(removePtr);
    removePtr = NULL;

    //Update left OpNode's left operator
    if(inNodePtr->opLeft != NULL)
      inNodePtr->opLeft->opRight = NULL;

    //Handle NULL links
    inNodePtr->rightOperand = NULL;
    inNodePtr->leftOperand = NULL;
    inNodePtr->opLeft = NULL;
    inNodePtr->opRight = NULL;

    //deallocate this node
    //printf("\nfree inNodePtr: %p", inNodePtr);
    free(inNodePtr);
    inNodePtr = NULL;//reset to head
    //printf("\ngetOpListHead(): %p", (getOpListHead()));
    //printf("\ngetHeadPtr     : %p", getHeadPtr);
    //printf("\ninNodePtr: %p", inNodePtr);
  }

  //Remove from middle
  //Retain left operand
  //unlink this node
  //Relink opRight left operand to this left operand
  else {
    //Link the leftOperand == shared with next OpNode's leftOperand
    inNodePtr->leftOperand->numer = inResultNum;
    inNodePtr->leftOperand->denom = inResultDenom;

    //Update right ListNode
    //ListNode* removePtr = inNodePtr->rightOperand;
    inNodePtr->leftOperand->next = inNodePtr->opRight->rightOperand;
    inNodePtr->opRight->leftOperand = inNodePtr->opLeft->rightOperand;

    //Dellocate Right Operand
    //printf("\nfree inNodePtr->rightOperand: %p", inNodePtr->rightOperand);
    free(inNodePtr->rightOperand);
    
    //relink left OpNode's left operator
    if(inNodePtr->opLeft != NULL)
      inNodePtr->opLeft->opRight = inNodePtr->opRight;

    //relink right OpNode's left operator
    if(inNodePtr->opRight != NULL)
      inNodePtr->opRight->opLeft = inNodePtr->opLeft;

    //Handle NULL links
    inNodePtr->leftOperand = NULL;
    inNodePtr->rightOperand = NULL;
    inNodePtr->opLeft = NULL;
    inNodePtr->opRight = NULL;

    //deallocate this node
    //printf("\nfree inNodePtr: %p", inNodePtr);
    free(inNodePtr);
    inNodePtr = NULL;//reset to head
    //printf("\ngetOpListHead(): %p", (getOpListHead()));
    //printf("\ngetHeadPtr     : %p", getHeadPtr);
    //printf("\ninNodePtr: %p", inNodePtr);
  }
}

//L1 is for Multiplication & Division
void ComputeOpL1() {
  OpNode* ptr = getOpListHead();
  //OpNode** ptrPtr = &ptr;
  while(ptr != NULL) {
    OpNode* nextPtr = ptr->opRight;//store next node
    if((ptr->operVar == OP_TIMES) || (ptr->operVar == OP_DIVIDE )) {
      ////printf("\nCompute: L1");      
      int tempNumer = 0;
      int tempDenom = 0;
      // printOpList();
      // printLinkedList();
      ComputeNode(ptr, &tempNumer, &tempDenom);
      //printf("\nHandle %p",ptr);      
      HandleNodeLinks(ptr, tempNumer, tempDenom);
      //printOpList();
      //printLinkedList();
      ////printFullExpression();
    }
    ptr = nextPtr;//update ptr to next ptr
    //printf("\nnext Handle %p",ptr);      
  }
}

//L2 is for PLUS & MINUS
void ComputeOpL2(){
  OpNode* ptr = getOpListHead();
  while(ptr != NULL) {
    OpNode* nextPtr = ptr->opRight;//store next node
    if((ptr->operVar == OP_PLUS) || (ptr->operVar == OP_MINUS)) {
      ////printf("\nCompute: L2");
      int tempNumer = 0;
      int tempDenom = 0;
      // printOpList();
      // printLinkedList();
      ComputeNode(ptr, &tempNumer, &tempDenom);
      //printf("\nHandle %p",ptr);      
      HandleNodeLinks(ptr, tempNumer, tempDenom);
      //printOpList();
      //printLinkedList();
      ////printFullExpression();
    }
    ptr = nextPtr;//update ptr to next ptr
    //("\nnext Handle %p",ptr);      
  }
}

void ComputeOpList(int* outNumer, int* outDenom) {
  ComputeOpL1();
  ComputeOpL2();

  if(OpListSize() == 0 && ListSize() == 1) {
    *outNumer = (getListNode(0))->numer;
    *outDenom = (getListNode(0))->denom;
  }
}

OpNode* getOpListHead() {
  return opHeadPtr;
}

void setOpListHead(OpNode* setHeadPtr) {
  opHeadPtr = setHeadPtr;
}

OpNode* getOpListNode(int opIdx) {
  int opListCount = 0;
  OpNode* ptr = getOpListHead();

  if(opIdx > OpListSize()-1) {
    printf("Index outside of Op list size");
    ptr = NULL;
  }

  else if(opIdx == 0) {
    return ptr;
  }
  else {
    while(opListCount < opIdx) {
      ptr = ptr->opRight;
      opListCount++;
    }
  }
  return ptr;
}


//Create a new OpNode
OpNode* CreateNode(){
  OpNode *ptr;
  if ((ptr = (OpNode *)malloc(sizeof(OpNode))) == NULL) {
    printf("malloc() failed.\n");
    return NULL;
  }
  ptr->operVar = OP_NULL;
  ptr->opLeft = NULL;
  ptr->opRight = NULL;  
  ptr->leftOperand = NULL;//link to ListNode
  ptr->rightOperand = NULL;//link to ListNode
  return ptr;
}

//Adds new Node to OperatorList
void addOpNode(OPType inSetOperator, ListNode* inLeftVarPtr, ListNode* inRightVarPtr) {
  OpNode *newPtr, *ptr;
  newPtr = CreateNode();

  if(getOpListHead() == NULL){
    //Link Single operator, 2 operands
    setOpListHead(newPtr);
    //printf("\nOpNode Head  : %p", newPtr);
    //printf("\ngetOpListHead: %p", getOpListHead());
    newPtr->operVar = inSetOperator;
    newPtr->opLeft = NULL;
    newPtr->opRight = NULL;
    newPtr->leftOperand = inLeftVarPtr;//link to ListNode
    newPtr->rightOperand = inRightVarPtr;//link to ListNode
    //printf("\n\nSet OpHead : %p", getOpListHead());
    //printf("\nnewPtr : %p", newPtr);    
    //printf("\nHead inLeftVarPtr : %i %i", inLeftVarPtr->numer, inLeftVarPtr->denom);    
    //printf("\nHead inRightVarPtr: %i %i", inRightVarPtr->numer, inRightVarPtr->denom);
  }

  else {
    //find the last node in the list (use opRight to traverse left to right)
    //printf("\n\ngetOpListHead : %p", getOpListHead());    
    ptr = getOpListHead();
    for (ptr = getOpListHead(); ptr->opRight != NULL; ptr=ptr->opRight){
    }

    //Link all pointers
    //printf("\nold ptr : %p", ptr);        
    //printf("\nnewPtr : %p", newPtr);    
    //printf("\ninLeftVarPtr : %i %i", inLeftVarPtr->numer, inLeftVarPtr->denom);    
    //printf("\ninRightVarPtr: %i %i", inRightVarPtr->numer, inRightVarPtr->denom);
    ptr->opRight = newPtr;

    newPtr->operVar = inSetOperator;
    newPtr->opLeft = ptr;//ptr becomes prev ptr
    newPtr->opRight = NULL;
    newPtr->leftOperand = inLeftVarPtr;//link to ListNode
    newPtr->rightOperand = inRightVarPtr;//link to ListNode

    ptr->rightOperand = newPtr->leftOperand;//share operands
  }
}    

int removeOpNode(int opIdx){
  OpNode* ptr;
  int reval = 0;

  if (getOpListHead() == NULL){
    printf("\nOp List empty, unable to delete.\n");
    reval = 0;
  }

  else if(opIdx > OpListSize() - 1) {
    printf("\nOp List index out of range, unable to delete\n");
    reval = -1;
  }

  //Within normal range
  else {
    if(opIdx == 0) {   
      //Remove from first Node 
      ptr = getOpListHead();
      //printf("\nRemove node: %p", ptr);
      free(ptr);
      ptr = NULL;
      setOpListHead(NULL);
    }

    else if(opIdx == OpListSize() -1) {
      //remove from last element
      //traverse to last element
      int counter = 0;
      OpNode* ptr = getOpListHead();
      while(counter < OpListSize() -1) {
        ptr = ptr->opRight;
        counter++;
      }
      //printf("\nRemove node: %p", ptr);
      ptr->opLeft->opRight = NULL;
      free(ptr);
      ptr = NULL;
    }

    else {
      //traverse idx and link
      int counter = 0;
      OpNode* prevPtr = NULL;
      OpNode* ptr = getOpListHead();
      while(counter < (opIdx)) {
        prevPtr = ptr;
        ptr = ptr->opRight;
        counter++;
      }

      if(prevPtr == NULL) {
        //prevPtr does not exist for Head
        printf("prevPtr does not exist for head");
      }
      else {
        //link prev to next
        prevPtr->opRight = ptr->opRight;
        free(ptr);
        ptr = NULL;
      }
    }
  }
  return reval;
}

char DecodeOpSymbol(OpNode* inPtr) {
  char printOp = '\0';
  switch(inPtr->operVar) {
    case OP_PLUS:
      printOp = '+';
    break;
    case OP_MINUS:
      printOp = '-';
    break;

    case OP_TIMES:
      printOp = '*';
    break;

    case OP_DIVIDE:
      printOp = '/';
    break;

    case OP_NULL:
      printOp = ' ';
    break;    
  }
  return printOp;
}

int OpListSize(void) {
  int opListCount = 0;
  if (getOpListHead() == NULL){
    return 0;
  }
  else {
    opListCount = 1;
    OpNode* ptr = getOpListHead();
    for (ptr = getOpListHead(); ptr->opRight != NULL; ptr=ptr->opRight){
      opListCount++;
    }
  }
  return opListCount;
}

void printFullExpression(void *outExpression) {
  char str[MAX_SINGLE_EXPRESSION_CHARS];

  OpNode* ptr = getOpListHead();
  ListNode* listPtr = getLinkedListHead();

  if(ptr == NULL && listPtr != NULL) {
    //printf("\nExpression: ");
    //printf("%i/%i", listPtr->numer, listPtr->denom);
    //printf("\nOperands size: %i", ListSize());
    //printf("\nOperator size: %i", OpListSize());
  }
  else if (ptr != NULL) {
    //printf("   -   Expression: ");
    int count = 0;

      while(count <= OpListSize() - 1) {
      ////printf("%i/%i  %c  ", ptr->leftOperand->numer, ptr->leftOperand->denom, DecodeOpSymbol(ptr));
      sprintf(str, "%i %c ",ptr->leftOperand->numer, DecodeOpSymbol(ptr));
      strcat(outExpression, str);


      if(count == (OpListSize() -1)) {
        ////printf("%i/%i", ptr->rightOperand->numer, ptr->rightOperand->denom);
        sprintf(str, "%i",ptr->rightOperand->numer);
        strcat(outExpression, str);
      }

      ptr = ptr->opRight;
      count++;
    }
    //printf("\nOperands size: %i", ListSize());
    //printf("\nOperator size: %i", OpListSize());
  }
  else {
    printf("\nOP List Empty\n");
  }
}

void printOpList(void) {
  OpNode* ptr = getOpListHead();
  if (ptr == NULL){
    printf("\nOP List Empty\n");
  } 
  else {
    printf("\n\nOP llist:");
    printf("\nopHeadptr: %p", getOpListHead());
    printf("\nOperator size: %i", OpListSize());
    //printf("\n\nOperands size: %i", ListSize());
    int count = 0;
    while(count <= OpListSize() - 1) {
      printf("\n(OP)%p  (LOperand)%p  (ROperand)%p", ptr, ptr->leftOperand, ptr->rightOperand);
      printf("  %i/%i  %c  %i/%i", ptr->leftOperand->numer, ptr->leftOperand->denom, DecodeOpSymbol(ptr), 
                                ptr->rightOperand->numer, ptr->rightOperand->denom);
      ptr = ptr->opRight;
      count++;
    }
    //printf("opHeadPtr: %p", getOpListHead());

  }
}

void clearOpList(void){
  if(opHeadPtr == NULL) {
    return;
  }
  else {
    int count = OpListSize()-1;
    while(count >= 0) {
      removeOpNode(count);
      count--;
    }
  }
}
