#include"Queens.h"

extern HeadNode *NodeHeadHead, *NodeHeadLast, *NodeHeadCurrent;
extern const int Fibonacci[8];

void SetRestrict(Node *pNode, int PositionX, int PositionY)
{	
	for (int i = 0; i < 8; i++)
	{
		if (pNode->DELTA[PositionX][i])
			pNode->AvailablePositionCount[PositionX]--;
		pNode->DELTA[PositionX][i] = FALSE;

		if (pNode->DELTA[i][PositionY])
			pNode->AvailablePositionCount[i]--;
		pNode->DELTA[i][PositionY] = FALSE;
	}

	int x = PositionX, y = PositionY;
	while (x >= 0 && y >= 0)
	{
		if (pNode->DELTA[x][y])
			pNode->AvailablePositionCount[x]--;
		pNode->DELTA[x][y] = FALSE;
		x--; y--;
	}	

	x = PositionX; y = PositionY;
	while (x < 8 && y < 8)
	{
		if (pNode->DELTA[x][y])
			pNode->AvailablePositionCount[x]--;
		pNode->DELTA[x][y] = FALSE;
		x++; y++;
	}

	x = PositionX; y = PositionY;
	while (x >= 0 && y < 8)
	{
		if (pNode->DELTA[x][y])
			pNode->AvailablePositionCount[x]--;
		pNode->DELTA[x][y] = FALSE;
		x--; y++;
	}

	x = PositionX; y = PositionY;
	while (x < 8 && y >= 0)
	{
		if (pNode->DELTA[x][y])
			pNode->AvailablePositionCount[x]--;
		pNode->DELTA[x][y] = FALSE;
		x++; y--;
	}
}

void CopyQueensPosition(Node *ReadNode, Node *WrightNode)
{
	for (int i = 0; i < 8; i++)
		WrightNode->QueensPosition[i] = ReadNode->QueensPosition[i];
}

void CopyDeltaMatrix(Node *ReadNode, Node *WrightNode)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			WrightNode->DELTA[i][j] = ReadNode->DELTA[i][j];
}

void SetSolutionCount()
{
	Node *currentThis = NodeHeadCurrent->NodeHead;

	while (currentThis != NULL)
	{
		Node *current = currentThis;

		while (current != NodeHeadHead->NodeHead)
		{
			current->SolutionCount++;
			current = current->last;
		}
		currentThis = currentThis->nextThis;
	}
}

void CleanApp()
{
	HeadNode *Headcurrent = NodeHeadHead, *Headlast = NULL;
	Node *current = NULL, *last = NULL;

	while (Headcurrent != NULL)
	{
		current = Headcurrent->NodeHead;
		while (current != NULL)
		{
			last = current;
			current = current->nextThis;
			free(last);
		}

		Headlast = Headcurrent;
		Headcurrent = Headcurrent->nextHead;
		free(Headlast);
	}
}