#pragma once
#include "DataNode.h"
#include <map>


using namespace std;
class OneRule
{
public:
	OneRule();
	~OneRule();
	bool readFile(const char*);

	void calulate();
	void printResult();
	void printData();
private:
	vector<DataNode> samples;
	map<string, string> bestRules; //rule set that has min error rate
	vector<string> AttrNames;
	string bestAttrName;
};

