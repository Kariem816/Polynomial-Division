#include <stdio.h>
#include <math.h>
#define MaxSize 50
#define getName(var) #var

void Zero(double poly[MaxSize])
{
	for (int i = 0; i < MaxSize; i++)
	{
		poly[i] = 0;
	}
}
int ChkInput(double size)
{
	double remainder = size - floor(size);
	if (size < 0 || remainder != 0 || size > MaxSize - 1)
	{
		while (size < 0 || remainder != 0 || size > MaxSize - 1)
		{
			printf("\nDegree must be: integer, not negative, less than %d.\n", MaxSize);
			printf("Enter a valid degree value: ");
			scanf("%lf", &size);
			remainder = size - floor(size);
		}
	}
	return size;
}
int getDeg(double poly[MaxSize])
{
	int deg = 0;
	for (int i = 0; i < MaxSize; i++)
	{
		if (poly[i] != 0 && i > deg)
		{
			deg = i;
		}
	}
	return deg;
}
void printPoly(double poly[MaxSize])
{
	int polyDeg = getDeg(poly);
	for (int i = polyDeg; i >= 0; i--)
	{
		if (i == 0)
		{
			if (poly[i] > 0)
			{
				if (i == polyDeg)
				{
					printf("%0.2lf", poly[i]);
				}
				else
				{
					printf("+ %0.2lf", poly[i]);
				}
			}
			else if (poly[i] < 0)
			{
				printf("- %0.2lf", -poly[i]);
			}
			else if (poly[i] == 0 && getDeg(poly) == 0)
			{
				printf("%0.2lf", poly[i]);
			}
		}
		else if (i == 1)
		{
			if (poly[i] == 1)
			{
				if (i == polyDeg)
				{
					printf("X ");
				}
				else
				{
					printf("+ X ");
				}
			}
			else if (poly[i] > 0)
			{
				if (i == polyDeg)
				{
					printf("%0.2lfX ", poly[i]);
				}
				else
				{
					printf("+ %0.2lfX ", poly[i]);
				}
			}
			else if (poly[i] == -1)
			{
				printf("- X ");
			}
			else if (poly[i] < 0)
			{
				printf("- %0.2lfX ", -poly[i]);
			}
		}
		else if (i > 1)
		{
			if (poly[i] == 1)
			{
				if (i == polyDeg)
				{
					printf("X^%d ", i);
				}
				else
				{
					printf("+ X^%d ", i);
				}
			}
			else if (poly[i] > 0)
			{
				if (i == polyDeg)
				{
					printf("%0.2lfX^%d ", poly[i], i);
				}
				else
				{
					printf("+ %0.2lfX^%d ", poly[i], i);
				}
			}
			else if (poly[i] == -1)
			{
				printf("- X^%d ", i);
			}
			else if (poly[i] < 0)
			{
				printf("- %0.2lfX^%d ", -poly[i], i);
			}
		}
	}
}
void inputPoly(double poly[MaxSize], const char polyName[10])
{
	Zero(poly);
	double testsize = 0;
	int size;
	printf("Enter the degree of the %s: ", polyName);
	scanf("%lf", &testsize);
	size = ChkInput(testsize);

	const int deg = size;
	for (int i = deg; i >= 0; i--)
	{
		if (i == 0)
		{
			printf("Enter the constant term of the %s: ", polyName);
			scanf("%lf", &poly[i]);
		}
		else if (i == 1)
		{
			printf("Enter X coefficient of the %s: ", polyName);
			scanf("%lf", &poly[i]);
		}
		else
		{
			printf("Enter X^%d coefficient of the %s: ", i, polyName);
			scanf("%lf", &poly[i]);
		}
	}
	printf("\n%s = ", polyName);
	printPoly(poly);
	printf("\n\n");
}
void multiply(double poly1[MaxSize], double poly2[MaxSize], double product[MaxSize])
{
	Zero(product);
	for (int i = 0; i <= getDeg(poly1); i++)
	{
		for (int j = 0; j <= getDeg(poly2); j++)
		{
			product[i + j] += poly1[i] * poly2[j];
		}
	}
}
void Add(double poly1[MaxSize], double poly2[MaxSize], double result[MaxSize])
{
	for (int i = 0; i < MaxSize; i++)
	{
		result[i] = poly1[i] + poly2[i];
	}
}
void subtract(double poly1[MaxSize], double poly2[MaxSize], double result[MaxSize])
{
	for (int i = 0; i < MaxSize; i++)
	{
		result[i] = poly1[i] - poly2[i];
	}
}
int IsFinished(double poly[MaxSize])
{
	int flag = 1;
	for (int i = 0; i < MaxSize; i++)
	{
		if (poly[i] != 0)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}
void divide(double numerator[MaxSize], double denominator[MaxSize], double result[MaxSize])
{
	double temp1[MaxSize], temp2[MaxSize];
	Zero(result);
	Zero(temp1);
	Zero(temp2);
	int resultDeg = getDeg(numerator) - getDeg(denominator);
	result[resultDeg] = numerator[getDeg(numerator)] / denominator[getDeg(denominator)];
	temp1[resultDeg] = result[resultDeg];
	multiply(denominator, temp1, temp2);
	subtract(numerator, temp2, numerator);
}
void CheckZero(double poly[MaxSize], const char polyName[10])
{
	if ((getDeg(poly)) == 0 && (poly[0] == 0))
	{
		do
		{
			printf("You cannot divide by zero\n");
			printf("Insert a valid Denominator\n\n");
			inputPoly(poly, polyName);
		} while ((getDeg(poly)) == 0 && (poly[0] == 0));
	}
}
void divisionResult(double poly1[MaxSize], double poly2[MaxSize])
{
	printf("Result = ");
	printPoly(poly1);
	printf("\n\n");
	printf("Remainder = ");
	printPoly(poly2);
	printf("\n\n");
}

void main()
{
	double numerator[MaxSize];
	double denominator[MaxSize];
	double temp[MaxSize];
	double result[MaxSize];
	int again = 0;
	do
	{
		Zero(result);
		Zero(temp);
		inputPoly(numerator, getName(numerator));
		inputPoly(denominator, getName(denominator));
		CheckZero(denominator, getName(denominator));

		while (IsFinished(numerator) == 0)
		{
			if (getDeg(numerator) < getDeg(denominator))
				break;
			else
				divide(numerator, denominator, temp);
			Add(result, temp, result);
		}
		divisionResult(result, numerator);

		char answer;
		do
		{
			printf("Another one? (y/n)\t");
			scanf(" %c", &answer);
		} while (answer != 'y' && answer != 'n');
		if (answer == 'y')
		{
			again = 1;
		}
		else
		{
			again = 0;
		}
	} while (again == 1);
}