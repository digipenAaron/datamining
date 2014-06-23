#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdarg.h>
using namespace std;
class DataNode
{
public:
	//the first element of attributes store the type to be classified
	DataNode(int _id, vector<string> attrs) :id(_id), attributes(attrs){}
	int id;
	vector<string> attributes;
};

