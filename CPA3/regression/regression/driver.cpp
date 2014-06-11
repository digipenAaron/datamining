#include <stdio.h>
#include "regression.h"

void main()
{
	regression logisticRegression = regression();
	logisticRegression.readFile("iris.data.txt");
	logisticRegression.calulate();
	logisticRegression.printData();
	logisticRegression.printResult();
	getchar();
}