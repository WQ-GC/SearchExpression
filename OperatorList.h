#ifndef OPERATOR_LIST_H
#define OPERATOR_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "LinkedList.h"
#include <string.h>
#define MAX_SYMBOLS_TYPE              4
#define MAX_EXPRESSION_CHARS          1024
#define MAX_SINGLE_EXPRESSION_CHARS   20

enum OperatorType{
  OP_PLUS,
  OP_MINUS,
  OP_TIMES,
  OP_DIVIDE,
  OP_NULL
};
typedef enum OperatorType OPType;

struct OperatorNode {
  struct OperatorNode* opLeft;
  struct OperatorNode* opRight;

  ListNode* leftOperand;
  ListNode* rightOperand;
  OPType operVar;
};
typedef struct OperatorNode OpNode;

static OpNode* opHeadPtr = NULL;

void ComputeNode(OpNode* inNodePtr, int* outResultNumer, int* outResultDenom);
void HandleNodeLinks(OpNode* inNodePtr, int inResultNum, int inResultDenom);
void ComputeOpL1();
void ComputeOpL2();
void ComputeOpList(int* outNumer, int* outDenom);

OpNode* getOpListHead();
void setOpListHead(OpNode* setHeadPtr);
OpNode* getOpListNode(int listIdx);
OpNode* CreateNode();
void addOpNode(OPType inSetOperator, ListNode* inLeftVarPtr, ListNode* inRightVarPtr);
int  removeOpNode(int opIdx);
char DecodeOpSymbol(OpNode* inPtr);

int OpListSize(void);
void printFullExpression(void *outExpression);
void ExtractFullExpression(char *outExpression);
void printOpList(void);
void clearOpList(void);

#endif