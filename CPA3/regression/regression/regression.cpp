#include "regression.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
regression::regression()
{

}


regression::~regression()
{
	for (int i = 0; i < samples.size(); ++i){
		delete samples[i];
	}
	samples.clear();
}

void regression::calulate()
{
	float result = 0;
	maxSum=-100000;
	for (float w1 = minx; w1 <= maxx; w1 += 0.1f){
		if (w1 == 0) continue;
		for (float w2 = miny; w2 <= maxy; w2 += 0.1f){
			if (w2 == 0) continue;
			float sum = 0;
			for (int i = 0; i < samples.size(); ++i){
				//I use equation format: x/w1+y/w2=1
				//so it's easier to find the boundary of x,y and represent the line
				float pr1 = 1.0f / (1.0f + exp(1.0f - samples[i]->a[1] / w1 - samples[i]->a[2]) / w2); 
				sum += ((1 - samples[i]->type)*(log(1.0f - pr1)) + samples[i]->type*log(pr1));
			}
			if (sum>maxSum){
				maxSum = sum;
				_w1 = w1;
				_w2 = w2;
			}
		}
	}
}

void regression::printData()
{
	for (int i = 0; i < samples.size(); ++i){
		string str;
		if (samples[i]->type)
			str = "Iris-setosa";
		else str = "Iris-versicolor";
		cout << setw(2) << samples[i]->id << "  " << setw(5) << samples[i]->a[1] << "  " << setw(5) << samples[i]->a[2] << "  " << str << endl;

	}

}

void regression::printResult()
{
	cout << endl;
	cout << "result: x/ " << _w1   << " + y/ " << _w2 <<" = 1" << endl;
}

bool regression::readFile(const char* filename)
{
	minx = miny = 100000;
	maxx = maxy = -100000;
	const int MAX_LINE_SIZE = 255;
	std::ifstream dataFile(filename, std::ifstream::in);
	if (dataFile.bad())
		return false;
	int num = 0;
	while (!dataFile.eof()) {
		
		dataFile.ignore(MAX_LINE_SIZE, ',');
		dataFile.ignore(MAX_LINE_SIZE, ',');
		float l, w;
		dataFile >> l;
		dataFile.ignore(MAX_LINE_SIZE, ','); 
		dataFile >> w;
		dataFile.ignore(MAX_LINE_SIZE, ',');
		string type;
		dataFile >> type;
		int itype=0;
		if (type == "Iris-setosa")
			itype = 1;
		DataNode* data = new DataNode(num++, l, w, itype);
		samples.push_back(data);
		if (l > maxx)
			maxx = l;
		if (l < minx)
			minx = l;
		if (w>maxy)
			maxy = w;
		if (w < miny)
			miny = w;
	}
	return true;
}


