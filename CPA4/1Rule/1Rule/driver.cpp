#include <stdio.h>
#include "DataNode.h"
#include "OneRule.h"

void test0()
{
	OneRule oneRule = OneRule();
	oneRule.readFile("weather_data.txt");
	oneRule.printData();
	oneRule.calulate();
	oneRule.printResult();
}

void test1()
{
	OneRule oneRule = OneRule();
	oneRule.readFile("vote.txt");
	oneRule.printData();
	oneRule.calulate();
	oneRule.printResult();
}

void main()
{
	test0();
	test1();
	getchar();
}