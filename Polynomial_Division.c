#include <stdio.h>
#include <math.h>
#define MaxSize 50
#define getName(var) #var

/**
 *	@brief Zeroes out the array
 *
 *  @param poly[] - array to be zeroed out
 */
void Zero(double poly[MaxSize])
{
	for (int i = 0; i < MaxSize; i++)
	{
		poly[i] = 0;
	}
}

/**
 *  @brief  Checks if the input is valid
 *
 *  @param size - the input degree of the polynomial
 *  @return size - the valid degree of the
 *
 *  @note The degree must be an integer, not negative, and less than MaxSize
 */
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

/**
 * @brief Gets the degree of the polynomial
 *
 * @param poly[] - the polynomial
 * @return deg - the degree of the polynomial
 */
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

/**
 * @brief Prints the polynomial to standard output
 * @param poly[] - the polynomial
 */
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

/**
 * @brief Gets the polynomial from the user
 * @param poly[] - the polynomial to store the input
 * @param polyName - the name of the polynomial
 */
void inputPoly(double poly[MaxSize], const char *polyName)
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

/**
 * @brief Multiplies two polynomials
 * @param poly1[] - the first polynomial
 * @param poly2[] - the second polynomial
 * @param product[] - array to store the product
 */
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

/**
 * @brief Adds two polynomials
 * @param poly1[] - the first polynomial
 * @param poly2[] - the second polynomial
 * @param result[] - array to store the result
 */
void Add(double poly1[MaxSize], double poly2[MaxSize], double result[MaxSize])
{
	for (int i = 0; i < MaxSize; i++)
	{
		result[i] = poly1[i] + poly2[i];
	}
}

/**
 * @brief Subtracts two polynomials
 * @param poly1[] - the first polynomial
 * @param poly2[] - the second polynomial
 * @param result[] - array to store the result
 */
void subtract(double poly1[MaxSize], double poly2[MaxSize], double result[MaxSize])
{
	for (int i = 0; i < MaxSize; i++)
	{
		result[i] = poly1[i] - poly2[i];
	}
}

/**
 * @brief Checks if the polynomial is finished
 * @param poly[] - the polynomial to check
 * @return 1 if the polynomial is finished, 0 otherwise
 */
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

/**
 * @brief Divides two polynomials
 * @param numerator[] - the numerator polynomial
 * @param denominator[] - the denominator polynomial
 * @param result[] - array to store the result
 */
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

/**
 * @brief Checks if the denominator is zero
 * @param poly[] - the polynomial to check
 * @param polyName - the name of the polynomial
 */
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

/**
 * @brief Prints the result and remainder of the division
 * @param poly1[] - the result polynomial
 * @param poly2[] - the remainder polynomial
 */
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
	// Main Loop Variables
	double numerator[MaxSize];
	double denominator[MaxSize];
	double temp[MaxSize];
	double result[MaxSize];

	// Again Loop Variables
	int again = 0;
	char answer;

	do
	{
		// Resetting Arrays
		Zero(result);
		Zero(temp);

		// Input Polynomials
		inputPoly(numerator, getName(numerator));
		inputPoly(denominator, getName(denominator));

		// Checking if denominator is zero
		CheckZero(denominator, getName(denominator));

		// Division
		while (IsFinished(numerator) == 0) // While numerator is not zero
		{
			if (getDeg(numerator) < getDeg(denominator)) // Don't divide if numerator degree is less than denominator degree
				break;
			else
				divide(numerator, denominator, temp); // Divide numerator by denominator and store result in temp
			Add(result, temp, result);				  // Add temp to result
		}
		divisionResult(result, numerator); // Print result and remainder

		// Ask user if they want to do another division
		printf("Another one? (y/n)\t");
		scanf("%c", &answer);
		if (answer == 'y' || answer == 'Y')
		{
			again = 1;
		}
	} while (again == 1);
}