#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct LinkedListNode {
  struct LinkedListNode* next;
  int numer;
  int denom;
};
typedef struct LinkedListNode ListNode;

static ListNode* llHeadPtr = NULL;
static ListNode* llBackupHeadPtr = NULL;

#if 0
ListNode* GetPrevNode(ListNode* inNode);
void swapListNode(ListNode* nodeA, ListNode* nodeB);
bool PermuteList();
#endif

void LoadBackupList();
void StoreBackupList();
int BackupListSize();

ListNode* getLinkedListHead();
void setLinkedListHead(ListNode* inHead);
ListNode* getListNode(int listIdx);
int ListSize(void);
ListNode* CreateListNode(int inNumer, int inDenom);
void addListNode(int inNumer, int inDenom);
int  removeListNode(int listIdx);
void printLinkedList(void);
void clearLinkedList(void);

#endif