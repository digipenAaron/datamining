#pragma once
#include <vector>
#include "DataNode.h"
using namespace std;
class regression
{
public:
	bool readFile(const char*);
	regression();
	~regression();
	void calulate();
	void printResult();
	void printData();
private:
	vector<DataNode*> samples;
	float minx, maxx, miny, maxy;
	float maxSum, _w1, _w2;
};

