#include "LinkedList.h"

ListNode* GetPrevNode(ListNode* inNode) {
  //printf("\n\ninNode: %p", inNode);
  ListNode* ptr = llHeadPtr;
  ListNode* prevPtr = NULL;
  bool searchStatus = false;

  for(int i = 0; i < ListSize(); i++) {
    if(ptr == inNode) {
      searchStatus = true;
      break;
    }
    prevPtr = ptr;
    ptr = ptr->next;
    //printf("\n  ptr    : %p", ptr);
    //printf("\n  prevPtr: %p", prevPtr);
  }
  //printf("\nEND prevPtr: %p", prevPtr);
  return prevPtr;
}

void SwapOperands(ListNode *nodeA, ListNode *nodeB) { 
  if(nodeA == nodeB) 
    return;//no need to swop

  ListNode* nodeAPrev = GetPrevNode(nodeA);
  ListNode* nodeBPrev = GetPrevNode(nodeB);

  if(nodeAPrev == NULL) {
  //nodeA is head
    //nodeAPrev stores nodeA's prev (but since it is head, it is NULL)
    //nodeBPrev stores nodeB's prev

    //Link the prev nodes
    nodeBPrev->next = nodeA;
    setLinkedListHead(nodeB);

    ListNode* tempPtr = nodeA->next;
    nodeA->next = nodeB->next;
    nodeB->next = tempPtr;
  }

  else if(nodeBPrev == NULL) {
  //nodeB is head
    nodeAPrev->next = nodeB;
    setLinkedListHead(nodeA);

    ListNode* tempPtr = nodeB->next;
    nodeB->next = nodeA->next;
    nodeA->next = tempPtr;
  }

  else {
    nodeAPrev->next = nodeB; 
    nodeBPrev->next = nodeA; 

    ListNode* tempPtr = nodeB;
    ListNode temp;
    temp.next = nodeB->next;
    nodeB->next = nodeA->next;
    nodeA->next = temp.next;
  }

  //printLinkedList();
}

//Copy Load BackupList data into Active List
void LoadBackupList() {
  int count = 0;
#if DEBUG  
//  printf("\nReload Backup: ");
#endif
  ListNode* ptr = llBackupHeadPtr;
  while(count < BackupListSize()) {
    //printf("\nBackup ptr: %p", ptr);
    //printf("\nBackup ptr->numer: %p   %p", ptr->numer, ptr->denom);
    addListNode(ptr->numer, ptr->denom);
#if DEBUG  
    //printf("%i ",ptr->numer);    
#endif
    ptr = ptr->next;
    count++;
  }
#if DEBUG
//  printf("\n");
#endif  
}

int BackupListSize() {
  int listCount = 0;
  if (llBackupHeadPtr == NULL){
    return 0;
  }
  else {
    listCount = 1;
    ListNode* ptr;
    for (ptr = llBackupHeadPtr; ptr->next != NULL; ptr=ptr->next){
      listCount++;
    }
  }
  return listCount;
}

void StoreBackupList() {
  int count = 0;
#if DEBUG  
  printf("\nBackup: ");
#endif
  while(count < ListSize()) {
    ListNode* newPtr;
    newPtr = CreateListNode(getListNode(count)->numer, getListNode(count)->denom);
#if DEBUG  
    printf("%i  ", newPtr->numer);
#endif
    //printf("\n");
    if (llBackupHeadPtr == NULL){
      llBackupHeadPtr = newPtr;
      //printf("\nBackup Head ptr: %p", newPtr);
      //printf("   numer: %i   denom: %i", newPtr->numer, newPtr->denom);
    } 
    else {
    //find the last node in the list
      ListNode* ptr = llBackupHeadPtr;
      for(ptr = llBackupHeadPtr; ptr->next != NULL; ptr=ptr->next){
      }
      ptr->next = newPtr;
      //printf("\nBackup ptr: %p", ptr);
      //printf("   numer: %i   denom: %i", newPtr->numer, newPtr->denom);
    }
    count++;
  }

  ListNode* ptr;
  //printf("\nsize of Backup list: %i", count);
  for(ptr = llBackupHeadPtr; ptr != NULL; ptr = ptr->next) {
    //printf("\nptr: %p", ptr);
    //printf("   num: %i    denom: %i", ptr->numer, ptr->denom);

  }
}

ListNode* getLinkedListHead() {
  return llHeadPtr;
}

void setLinkedListHead(ListNode* inHead) {
  llHeadPtr = inHead;
}

ListNode* getListNode(int listIdx) {
  int listCount = 0;
  ListNode* ptr = getLinkedListHead();

  if(listIdx > ListSize()-1) {
    printf("\nIndex outside of list size");
    ptr = NULL;
  }

  else if(listIdx == 0) {
    return ptr;
  }
  else {
    while(listCount < listIdx) {
      ptr = ptr->next;
      listCount++;
    }
  }
  return ptr;
}

//Counts the size of List
int ListSize(void){
  int listCount = 0;

  if (getLinkedListHead() == NULL){
    return 0;
  }
  else {
    listCount = 1;
    ListNode* ptr = getLinkedListHead();
    for (ptr = getLinkedListHead(); ptr->next != NULL; ptr=ptr->next){
      listCount++;
    }
  }
  return listCount;
}


//Allocates memory for a ListNode
ListNode* CreateListNode(int inNumer, int inDenom) {
  ListNode* ptr;
  if ((ptr = (ListNode *)malloc(sizeof(ListNode))) == NULL) {
    printf("malloc() failed.\n");
    return NULL;
  }
  ptr->next = NULL;
  ptr->numer = inNumer;
  ptr->denom = inDenom;
  return ptr;
}

void addListNode(int inNumer, int inDenom) {
  ListNode* newPtr;
  newPtr = CreateListNode(inNumer, inDenom);

  if (getLinkedListHead() == NULL){
    setLinkedListHead(newPtr);
  } 
  else {
  //find the last node in the list
    ListNode* ptr = getLinkedListHead();
    for(ptr = getLinkedListHead(); ptr->next != NULL; ptr=ptr->next){
    }
    //printf("\nptr: %p", ptr);
    //printf("\nptr->next: %p", ptr->next);
    ptr->next = newPtr;
  }
}

//Removes a ListNode from LinkedList
int removeListNode(int listIdx){
  ListNode* ptr;
  int reval = 0;

  if (getLinkedListHead() == NULL){
    printf("\nOperands List empty, unable to delete.\n");
    reval = 0;
  }

  else if(listIdx > ListSize() - 1) {
    printf("\nList index out of range, unable to delete\n");
    reval = -1;
  }

  //Within normal range
  else {
    if(listIdx == 0) {   
      //Remove from first Node 
      ptr = getLinkedListHead();
      ListNode* nextPtr = ptr->next;//get nextNode
      if(nextPtr == NULL) {
        //only 1 node in list
        free(ptr);
        ptr = NULL;
        setLinkedListHead(NULL);
      }
      else {
        setLinkedListHead(nextPtr);//update Head
        free(ptr);
        ptr = NULL;
      }      
    }

    else if(listIdx == ListSize() -1) {
      //remove from last element
      //traverse to last element
      int counter = 0;
      ListNode* prevPtr = getLinkedListHead();
      while(counter != ListSize() -2) {
        prevPtr = prevPtr->next;
        counter++;
      }
      free(prevPtr->next);
      prevPtr->next = NULL;
    }

    else {
      //traverse idx and link
      int counter = 0;
      ListNode* prevPtr = NULL;
      ListNode* ptr = getLinkedListHead();
      while(counter < (listIdx)) {
        prevPtr = ptr;
        ptr = ptr->next;
        counter++;
      }

      if(prevPtr == NULL) {
        //prevPtr does not exist for Head
        printf("prevPtr does not exist for head");
      }
      else {
        //link prev to next
        prevPtr->next = ptr->next;
        free(ptr);
        ptr = NULL;
      }
    }
  }
  return reval;
}

void printLinkedListItems(void) {
  ListNode* ptr = getLinkedListHead();
  if (ptr == NULL){
    printf("\nOperands List Empty\n");
  } 
  else {
  printf("\n");
    int count = 0;
    while(count <= ListSize() - 1) {
      printf("%i ", ptr->numer);
      ptr = ptr->next;
      count++;
    }
  }
}

void printLinkedList(void) {
  ListNode* ptr = getLinkedListHead();
  if (ptr == NULL){
    printf("\nOperands List Empty\n");
  } 
  else {
    printf("\n\nOperands llist:");
    printf("\nOperands size: %i", ListSize());
    printf("\nllHeadptr: %p", getLinkedListHead());
    int count = 0;
    while(count <= ListSize() - 1) {
      //printf("%i:   %i\n", count, ptr->nodeData);
      printf("\n%p  %p  %p: %i/%i", GetPrevNode(ptr), ptr, ptr->next , ptr->numer, ptr->denom);

      ptr = ptr->next;
      count++;
    }
  }
}

void clearLinkedList(void) {
  if(llHeadPtr == NULL) {
    return;
  }
  else {
    int count = ListSize();
    while(count != 0) {
      removeListNode(count-1);
      count--;
    }
  }
}

void clearBackupLinkedList(void) {
  if(llBackupHeadPtr == NULL) {
    return;
  }
  else {
    int count = BackupListSize();
    while(count != 0) {
      removeBackupListNode(count-1);
      count--;
    }
  }
}

//Removes a ListNode from LinkedList
int removeBackupListNode(int backupListIdx){
  ListNode* ptr;
  int reval = 0;

  if (llBackupHeadPtr == NULL){
    printf("\nBackup Operands List empty, unable to delete.\n");
    reval = 0;
  }

  else if(backupListIdx > BackupListSize() - 1) {
    printf("\nBackup List index out of range, unable to delete\n");
    reval = -1;
  }

  //Within normal range
  else {
    if(backupListIdx == 0) {   
      //Remove from first Node 
      ptr = llBackupHeadPtr;
      ListNode* nextPtr = ptr->next;//get nextNode
      if(nextPtr == NULL) {
        //only 1 node in list
        free(ptr);
        ptr = NULL;
        llBackupHeadPtr = NULL;
      }
      else {
        llBackupHeadPtr = nextPtr;//update Head
        free(ptr);
        ptr = NULL;
      }      
    }

    else if(backupListIdx == BackupListSize() -1) {
      //remove from last element
      //traverse to last element
      int counter = 0;
      ListNode* prevPtr = llBackupHeadPtr;
      while(counter != BackupListSize() -2) {
        prevPtr = prevPtr->next;
        counter++;
      }
      free(prevPtr->next);
      prevPtr->next = NULL;
    }

    else {
      //traverse idx and link
      int counter = 0;
      ListNode* prevPtr = NULL;
      ListNode* ptr = llBackupHeadPtr;
      while(counter < (backupListIdx)) {
        prevPtr = ptr;
        ptr = ptr->next;
        counter++;
      }

      if(prevPtr == NULL) {
        //prevPtr does not exist for Head
        printf("prevPtr does not exist for head");
      }
      else {
        //link prev to next
        prevPtr->next = ptr->next;
        free(ptr);
        ptr = NULL;
      }
    }
  }
  return reval;
}
