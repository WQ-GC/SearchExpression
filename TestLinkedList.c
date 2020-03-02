
#if 1
#include "LinkedList.h"

#define SET_NODES     7
#define MORE_NODES    10
int main() {
  int count = 0;
  while(count < SET_NODES) {
    addListNode(count+1,1);
    count++;
  }
  printLinkedList();

#if FAILED
  swapListNode(getListNode(2), getListNode(3));
#endif  
  printLinkedList();



#if 1
  ListNode* ptr = getLinkedListHead();
  count = 0;
  while(count < SET_NODES) {
    printf("\nEND prevPtr: %p", GetPrevNode(ptr));
    count++;
    ptr = ptr->next;
  }

  printf("\n\nBackup list:");
  StoreBackupList();//stored with llBackupHeadPtr
 
  printf("\n\nDelete list:");
  clearLinkedList();
  printLinkedList();

  printf("\n\nReload Backup list:");
  LoadBackupList();//stored with llBackupHeadPtr
  printLinkedList();
#endif

#if 0
  int count = 0;
  while(count < SET_NODES) {
    addListNode(count);
    count++;
  }
  printLinkedList();

  //Remove middle node
  int count = 0;
  while(count < SET_NODES) {
    addListNode(count);
    count++;
  }

  count = 0;
  while(count < MORE_NODES) {
    printf("\n\nCurr ListSize: %i\n", ListSize());
    printLinkedList();
    printf("Remove: [%i]\n", (ListSize()-1)/2);
    removeListNode((ListSize()-1)/2);
    count++;
  }


  //Remove always last node
  count = 0;
  while(count < SET_NODES) {
    addListNode(count);
    count++;
  }

  count = 0;
  while(count < MORE_NODES) {
    printf("\n\nCurr ListSize: %i\n", ListSize());
    printLinkedList();
    printf("Remove: [%i]\n", ListSize()-1);
    removeListNode(ListSize()-1);

    count++;
  }

  count = 0;
  while(count < SET_NODES) {
    addListNode(count);
    count++;
  }

  //Remove always first node
  count = 0;
  while(count < MORE_NODES) {
    printf("\n\nCurr ListSize: %i\n", ListSize());
    printLinkedList();
    printf("Remove: [0]\n");
    removeListNode(0);

    count++;
  }


  //Remove from Second Node
  count = 0;
  while(count < SET_NODES) {
    addListNode(count);
    count++;
  }

  count = 0;
  while(count < MORE_NODES) {
    printf("\n\nCurr ListSize: %i\n", ListSize());
    printLinkedList();
    printf("Remove: [1]\n");
    removeListNode(1);

    count++;
  }


  //Remove from Second Last Node
  count = 0;
  while(count < SET_NODES) {
    addListNode(count);
    count++;
  }

  count = 0;
  while(count < MORE_NODES) {
    printf("\n\nCurr ListSize: %i\n", ListSize());
    printLinkedList();
    printf("Remove: [%i]\n", (SET_NODES-1));
    removeListNode((SET_NODES-1));

    count++;
  }
#endif  
}
#endif