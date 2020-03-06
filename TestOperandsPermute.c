#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"
#include "DecodeMap.h"

#if 1
#define MAX_LIST  4

int main(void) {
  for(int i = 0; i < MAX_LIST; i++) {
    addListNode(i+1,1);
  }

  printLinkedList();

#if PASS
  //Swap same nodes
  SwapOperands(getListNode(0), getListNode(0));
  SwapOperands(getListNode(1), getListNode(1));
  SwapOperands(getListNode(2), getListNode(2));
  SwapOperands(getListNode(3), getListNode(3));
  SwapOperands(getListNode(4), getListNode(4));


  //swap adjacent neighbours
  SwapOperands(getListNode(0), getListNode(1));
  SwapOperands(getListNode(1), getListNode(2));
  SwapOperands(getListNode(2), getListNode(3));
  SwapOperands(getListNode(3), getListNode(4));

  SwapOperands(getListNode(1), getListNode(0));
  SwapOperands(getListNode(2), getListNode(1));
  SwapOperands(getListNode(3), getListNode(2));
  SwapOperands(getListNode(4), getListNode(3));

  //swap non-adjacent neighbours
  SwapOperands(getListNode(1), getListNode(3));
  SwapOperands(getListNode(2), getListNode(3));
  SwapOperands(getListNode(1), getListNode(2));
  SwapOperands(getListNode(3), getListNode(2));
  SwapOperands(getListNode(2), getListNode(1));
  SwapOperands(getListNode(3), getListNode(1));

  //Swap with list End
  SwapOperands(getListNode(0), getListNode(4));
  SwapOperands(getListNode(1), getListNode(4));
  SwapOperands(getListNode(2), getListNode(4));
  SwapOperands(getListNode(3), getListNode(4));


  //Swap with list Front
  SwapOperands(getListNode(1), getListNode(0));
  SwapOperands(getListNode(2), getListNode(0));
  SwapOperands(getListNode(3), getListNode(0));
  SwapOperands(getListNode(4), getListNode(0));
#endif

  printf("\n");
  Permute(0, ListSize()-1);
  return 0; 
}

#endif

#if 0
void swap(char *x, char *y);
void permute(char *a, int l, int r);
void swap(char *x, char *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
/* Function to print permutations of string 
   This function takes three parameters: 
   1. String 
   2. Starting index of the string 
   3. Ending index of the string. */
void permute(char *a, int l, int r) 
{ 
   int i; 
   if (l == r) 
     printf("%s\n", a); 
   else
   { 
       for (i = l; i <= r; i++) 
       { 
          swap((a+l), (a+i)); 
          permute(a, l+1, r); 
          swap((a+l), (a+i)); //backtrack 
       } 
   } 
} 
  
/* Driver program to test above functions */
int main() 
{ 
    char str[] = "ABC"; 
    int n = strlen(str); 
    permute(str, 0, n-1); 
    return 0; 
} 
#endif

