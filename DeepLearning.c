#include"Queens.h"
#define LEARNINGSPEED 0.001
#define REPEAT 100000

extern HeadNode *NodeHeadHead, *NodeHeadLast, *NodeHeadCurrent;

double Weight[5][9];
double AvgError[5] = { 0 };

double X, Y, errorX, errorY;

//Enumeratem the significance of the index X in Weight array
enum WeightX
{
	Step1 = 0,
	Step2,
	Step3,
	Step4,
	Step5
};

//Enumeratem the significance of the index Y in Weight array
enum WeightY
{
	ParamiterInLine0 = 0,
	ParamiterInLine1,
	ParamiterInLine2,
	ParamiterInLine3,
	ParamiterInLine4,
	ParamiterInLine5,
	ParamiterInLine6,
	ParamiterInLine7,
	ParamiterAdd
};

//Using DeepLearning from step1 to step five, unable DeepLearning in step0, step6 and step 7
void DeepLearningMain()
{
	InitWeight();

	for (int ri = 1; ri <= REPEAT; ri++)
		LearningMain();

	PrintResult();
}

void InitWeight()
{
	for (enum WeightX (i) = Step1; i <= Step5; i++)
		for (enum WeightY (j) = ParamiterInLine0; j <= ParamiterAdd; j++)
			Weight[i][j] = 0.1;
}

void LearningMain()
{
	HeadNode *CurrentHead = NodeHeadHead->nextHead->nextHead;

	//There are mostly eight steps in a branch, each step may has its own parameter, now learning from data after step X
	for (enum WeightX(Step) = Step1; Step <= Step5; Step++)
	{
		Node *current = CurrentHead->NodeHead;

		while (current != NULL)
		{
			LearningCurrentData(current, Step);
			current = current->nextThis;
		}

		CurrentHead = CurrentHead->nextHead;
	}

}

void LearningCurrentData(Node *current, enum WeightX Step)
{
	X = 0, Y = 0;
	
	CalculateX(current, Step);

	//Calculate Y under the control of Activation Fuction Y = X^2 (odd expansion)
	CalculateY();

	CalculateError(current, Step);

	Backpick(current, Step);
}

void CalculateX(Node *current, int Step)
{
	for (int i = Step + 2; i < 8; i++)
		X += Weight[Step][i] * current->AvailablePositionCount[i];
	X += Weight[Step][8];
}

void CalculateY()
{
	if (X >= 0)
		Y = (X) * (X);
	else
		Y = -(X) * (X);
}

void CalculateError(Node *current, enum WeightX Step)
{
	errorY = Y - current->SolutionCount;

	if (errorY < DBL_EPSILON && errorY > -DBL_EPSILON)
		errorX = 0;
	else if (X >= 0)
		errorX = errorY / ( 2 * X );
	else
		errorX = -errorY / ( 2 * X );

	//Add total error
	AvgError[Step] += fabs(errorY);
}

void Backpick(Node *current, enum WeightX Step)
{
	for (enum WeightY(i) = Step + 2; i <= ParamiterInLine7; i++)
		Weight[Step][i] -= LEARNINGSPEED * errorX * current->AvailablePositionCount[i];
	Weight[Step][8] -= LEARNINGSPEED * errorX;
}

void PrintResult()
{
	//There are totally 42 branches in Step1, 140 branches in Step2, 342 branches in Step3, 568 branches in Step4, 550 branches in Step5
	const int BranchCount[5] = { 42, 140, 342, 568, 550 };

	for (enum Weight(i) = Step1; i <= Step5; i++)
	{
		AvgError[i] /= REPEAT;
		AvgError[i] /= BranchCount[i];
	}

	printf("DeepLearning Result:\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
			printf("%6.3lf ", Weight[i][j]);
		printf("\n");
	}
	for (int i = 0; i < 5; i++)
		printf("Error = %.6lf\n", AvgError[i]);
	system("pause");
}