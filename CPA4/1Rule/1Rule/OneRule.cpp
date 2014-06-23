#include "OneRule.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <set>
#include <limits>
#include <time.h> 
#include <sstream> 

typedef std::map<std::string, int> M;

bool value_comparer(M::value_type &i1, M::value_type &i2)
{
	return i1.second < i2.second;
}

OneRule::OneRule()
{
	srand(time(NULL));
}


OneRule::~OneRule()
{
}


void OneRule::calulate()
{

	int attrNum = samples[0].attributes.size(); //get how many attritubes

	vector<set<string>> attributes = vector<set<string>>(attrNum);   //this container is for record all value range of each attribute

	for (int i = 1; i < samples.size(); ++i)  //iterate all samples to record all value range of each attribute
	{
		for (int iattr = 0; iattr < attrNum; ++iattr)
		{
				attributes[iattr].insert(samples[i].attributes[iattr]);
		}
	}

	// the following code will follow this pseudocode

	//For each attribute,
	//	For each value of that attribute, make a rule as follows :
	//		count how often each class appears
	//		find the most frequent class
	//		make the rule assign that class to this attribute value.
	//	Calculate the error rate of the rules.
	//Choose the rules with the smallest error rate.


	int minError = numeric_limits<int>::max();	//rule set that has min error number 
	int classIndex = samples[0].attributes.size()-1;
	//For each attribute
	for (int iattr = 0; iattr < attributes.size()-1; ++iattr)
	{
		cout << AttrNames[iattr] << endl;
		map<string, string> rules;
		//For each value of that attribute, make a rule
		for (set<string>::iterator iter = attributes[iattr].begin(); iter != attributes[iattr].end(); iter++)
		{
			string attr = *iter;
			map<string, int> classAppearTimes;

			//count how often each class appears
			for (int i = 1; i < samples.size(); ++i)
			{
				
				if (samples[i].attributes[iattr] == attr)
					classAppearTimes[samples[i].attributes[classIndex]]++;
			}

			//	find the most frequent class
			map<string, int>::iterator it = max_element(classAppearTimes.begin(), classAppearTimes.end(), value_comparer);

			//	make the rule assign that class to this attribute value.
			string mostClass = it->first;
			rules[attr] = mostClass;
			cout << attr << " -> " << mostClass << endl;
		}

		//	Calculate the error rate of the rules.
		int errorNum = 0;
		for (int i = 1; i < samples.size(); ++i)
		{
			string currentAttr = samples[i].attributes[iattr];
			//the first element of attributes(attributes[classIndex]) of each sample store the class value
			if (rules[currentAttr] != samples[i].attributes[classIndex])
				errorNum++;
		}
		cout << "error: " << errorNum << "/" << samples.size() << endl <<endl;

		//	Choose the rules with the smallest error rate.
		if (errorNum<minError || (errorNum == minError&&rand()%2==0))  //Arbitrarily breaking the tie
		{
			minError = errorNum;
			bestRules = rules;
			bestAttrName = AttrNames[iattr];
		}

	}


}

void OneRule::printData()
{
	for (int i = 0; i < samples.size(); ++i){
		for (int j = 0; j < samples[i].attributes.size(); ++j)
			cout << setw(10) << samples[i].attributes[j];
		cout << endl;

	}
	cout << endl;
	cout << endl;
}


void OneRule::printResult()
{
	cout << endl << "Best Rules:" << endl << bestAttrName <<endl;
	for (map<string, string>::iterator iter = bestRules.begin(); iter != bestRules.end(); iter++)
	{
		cout << iter->first << " -> " << iter->second <<endl;
	}
	cout << "-------------------------------------" << endl << endl;
}

bool OneRule::readFile(const char* filename)
{
	std::ifstream dataFile(filename, std::ifstream::in);
	if (dataFile.bad())
		return false;
	int num = 0;
	
	string line;
	while (getline(dataFile, line))
	{
		vector<string> attrs;
		std::istringstream iss(line);
		string sub;
		while (iss >> sub)
			attrs.push_back(sub);
		DataNode data = DataNode(num++, attrs);
		samples.push_back(data);
	}
	//the first sample stores AttrNames
	AttrNames=samples[0].attributes;
	return true;
}

