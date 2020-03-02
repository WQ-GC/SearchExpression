#if 1
#include "OperatorList.h"
#include "LinkedList.h"
#define MAX_OPERAND   10
#define MAX_OPS       (MAX_OPERAND -1)

int main() {

  for(int k = 0; k < 9; k++) {
    addListNode(k, k+1);
  }
  printLinkedList();
  printf("\n");
  StoreBackupList();//stored in Backup List pointed by llBackupHeadPtr

  for(int k = 0; k < 8; k++) {
    addOpNode(k%4, getListNode(k), getListNode(k+1));
  }
  printOpList();
  printf("\n");

#if 0
  printf("\n==============================================\n");
  //Test Clear Operands LL and Backup
  clearLinkedList();
  printLinkedList();
  printf("\n");

  LoadBackupList();
  printLinkedList();
  printf("\n");
#endif

#if 1
  printf("\n==============================================\n");
  //Test Clear Operations List
  clearLinkedList();
  clearOpList();
  LoadBackupList();

  for(int k = 0; k < 8; k++) {
    addOpNode(k%4, getListNode(k), getListNode(k+1));
  }
  printOpList();
  printf("\n");

  printOpList();
  printf("\n");
#endif

  printFullExpression();

  int getNumer, getDenom;
  ComputeOpList(&getNumer, &getDenom);
  printf("Result: %f",(float)getNumer/getDenom);
}

#endif