#pragma warning(disable:4996)
#ifndef _QUEENS_H_
#define _QUEENS_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<float.h>

typedef int BOOL;
#define TRUE  1
#define FALSE 0

typedef struct MyNode
{
	int QueensPosition[8];
	BOOL DELTA[8][8];
	int AvailablePositionCount[8];
	int SolutionCount; 
	struct MyNode *last;
	struct MyNode *nextThis;
} Node;

typedef struct MyHeadNode
{
	Node *NodeHead;
	Node *NodeCurrent;
	struct MyHeadNode *nextHead;
} HeadNode;


//Main.c
void Init();
void PlaceQueen(int line);
void CreateNodeHead();
void AddNode(Node *Last, int PositionX, int PositionY);

//Util.c
void SetRestrict(Node *pNode, int PositionX, int PositionY);
void CopyQueensPosition(Node *ReadNode, Node *WrightNode);
void CopyDeltaMatrix(Node *ReadNode, Node *WrightNode);
void Print(int StepNumber);
void PrintChessBoard(Node *pNode, int StepNumber);
void SetSolutionCount();
void CleanApp();

//DeepLearning.c
void DeepLearningMain();
void InitWeight();
void LearningMain();
void LearningCurrentData(Node *current, enum WeightX Step);
void CalculateX(Node *current, int Step);
void CalculateY();
void CalculateError(Node *current, enum WeightX Step);
void Backpick(Node *current, enum WeightX Step);
void PrintResult();

#endif