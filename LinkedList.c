#include "LinkedList.h"

#if 0
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

void swapListNode(ListNode* nodeA, ListNode* nodeB) {
  ListNode* ptrA = nodeA;
  ListNode* ptrB = nodeB;
  ListNode* prevPtrA = GetPrevNode(nodeA);
  ListNode* prevPtrB = GetPrevNode(nodeB);

  if(nodeA == nodeB)
    return;

  //HeadPtrs
  else if(nodeA == llHeadPtr) {
    llHeadPtr = nodeB;


  }
  else if(nodeB == llHeadPtr) {
    llHeadPtr = nodeA;

  }

  else{
  //General Case
    printf("\n\n=======================");
    printf("\nprevPtrA: %p", GetPrevNode(nodeA));
    printf("\nnodeA: %p", nodeA);
    printf("\nnodeA->next: %p", nodeA->next);

    printf("\n\nprevPtrB: %p", GetPrevNode(nodeB));
    printf("\nnodeB: %p", nodeB);
    printf("\nnodeB->next: %p", nodeB->next);

    ListNode* prevA = GetPrevNode(nodeA);
    ListNode* prevB = GetPrevNode(nodeB);
    ListNode* tempNodeANext = nodeA->next;
    ListNode* tempNodeBNext = nodeB->next;

    nodeB->next = tempNodeANext;
    nodeA->next = tempNodeBNext;

    prevA->next = nodeB;
    prevB->next = nodeA;

    printf("\n\n=======================");
    printf("\nprevPtrA: %p", GetPrevNode(nodeA));
    printf("\nnodeA: %p", nodeA);
    printf("\nnodeA->next: %p", nodeA->next);

    printf("\n\nprevPtrB: %p", GetPrevNode(nodeB));
    printf("\nnodeB: %p", nodeB);
    printf("\nnodeB->next: %p", nodeB->next);

#if 0
    printf("\nprevPtrA->next: %p", prevPtrA->next);
    printf("\nnodeB: %p", nodeB);
    prevPtrA->next = nodeB;

    printf("\npnodeA->next: %p", nodeA->next);
    printf("\ntempListNodeB.next: %p", tempListNodeB.next);
    nodeA->next = tempListNodeB.next;

    printf("\nprevPtrB->next: %p", prevPtrB->next);
    printf("\nnodeA: %p", nodeA);
    prevPtrB->next = nodeA;

#endif
  }
}

bool PermuteList() {
}
#endif


//Copy Load BackupList data into Active List
void LoadBackupList() {
  int count = 0;

  ListNode* ptr = llBackupHeadPtr;
  while(count < BackupListSize()) {
    //printf("\nBackup ptr: %p", ptr);
    //printf("\nBackup ptr->numer: %p   %p", ptr->numer, ptr->denom);
    addListNode(ptr->numer, ptr->denom);
    ptr = ptr->next;
    count++;
  }
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
  while(count < ListSize()) {
    ListNode* newPtr;
    newPtr = CreateListNode(getListNode(count)->numer, getListNode(count)->denom);

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

void printLinkedList(void) {
  ListNode* ptr = getLinkedListHead();
  if (ptr == NULL){
    printf("\nOperands List Empty\n");
  } 
  else {
    printf("\n\nOperands llist:");
    printf("\nllHeadptr: %p", getLinkedListHead());
    printf("\nOperands size: %i", ListSize());
    int count = 0;
    while(count <= ListSize() - 1) {
      //printf("%i:   %i\n", count, ptr->nodeData);
      printf("\n%p:   %i/%i", ptr, ptr->numer, ptr->denom);

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

