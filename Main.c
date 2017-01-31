#include"Queens.h"

HeadNode *NodeHeadHead, *NodeHeadLast, *NodeHeadCurrent;
int AnswerCount, ri;
int NodeCount;
const int Fibonacci[8] = { 0, 0, 1, 2, 3, 5, 8, 13 };
extern double Weight[5][9];

int main(void)
{	
	Init();

	for (int i = 0; i < 8; i++)
		PlaceQueen(i);

	SetSolutionCount();

	DeepLearningMain();	

	CleanApp();
}

void Init()
{
	NodeHeadHead = NodeHeadLast = NodeHeadCurrent = (HeadNode*)malloc(sizeof(HeadNode));
	NodeHeadHead->NodeHead = NodeHeadHead->NodeCurrent = (Node*)malloc(sizeof(Node));

	memset(NodeHeadHead->NodeHead->QueensPosition, 0, 8 * sizeof(int));
	NodeHeadHead->NodeHead->QueensPosition[0] = -1;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			NodeHeadHead->NodeHead->DELTA[i][j] = TRUE;

	for (int i = 0; i < 8; i++)
		NodeHeadHead->NodeHead->AvailablePositionCount[i] = 8;
	NodeHeadHead->NodeHead->SolutionCount = 0;

	NodeHeadHead->NodeHead->last = NULL;
	NodeHeadHead->NodeHead->nextThis = NULL;
	NodeHeadHead->nextHead = NULL;
}

void PlaceQueen(int line)
{
	Node *temp = NodeHeadLast->NodeHead;
	
	CreateNodeHead();

	while (temp != NULL)
	{
		for (int i = 0; i < 8; i++)
		{
			if (temp->DELTA[line][i])
			{
				AddNode(temp, line, i);
				
				if (line == 7 && ri == 1)
					AnswerCount++;
				if (ri == 1)
					NodeCount++;
			}
		}
		temp = temp->nextThis;
	}
	NodeHeadLast = NodeHeadLast->nextHead;
}

void CreateNodeHead()
{
	HeadNode *temp = (HeadNode*)malloc(sizeof(HeadNode));
	NodeHeadCurrent->nextHead = temp;
	NodeHeadCurrent = NodeHeadCurrent->nextHead;
	NodeHeadCurrent->nextHead = NULL;
	NodeHeadCurrent->NodeHead = NodeHeadCurrent->NodeCurrent = NULL;
}

void AddNode(Node *Last, int PositionX, int PositionY)
{
	Node *temp = (Node*)malloc(sizeof(Node));
	
	for (int i = 0; i < 8; i++)
		temp->AvailablePositionCount[i] = Last->AvailablePositionCount[i];

	CopyQueensPosition(Last, temp);
	temp->QueensPosition[PositionX] = PositionY;

	CopyDeltaMatrix(Last, temp);
	SetRestrict(temp, PositionX, PositionY);

	temp->SolutionCount = 0;

	temp->last = Last;
	temp->nextThis = NULL;

	if (NodeHeadCurrent->NodeHead == NULL)
		NodeHeadCurrent->NodeHead = NodeHeadCurrent->NodeCurrent = temp;
	else
	{
		NodeHeadCurrent->NodeCurrent->nextThis = temp;
		NodeHeadCurrent->NodeCurrent = temp;
	}
}