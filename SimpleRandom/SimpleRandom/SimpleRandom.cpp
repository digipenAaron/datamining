// SimpleRandom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include <time.h>
const int TOTAL_NUM = 316;
const int SAMPLE_NUM = 20;

std::vector < std::vector<int>> dataSet;
std::vector < std::vector<int>> samples;

bool readFile(const char* filename)
{
	const int MAX_LINE_SIZE = 255;
	std::ifstream dataFile(filename, std::ifstream::in);
	if (dataFile.bad())
		return false;

	std::string s;
	int pLines = 9;
	for (; pLines; --pLines)
		std::getline(dataFile, s);

	
	for (int iline = 0; iline < 316; iline++)
	{
		std::vector<int> dataItem(12);
		for (int i = 0; i < 12; i++)
			dataFile >> dataItem[i];
		dataSet.push_back(dataItem);
	}
	return true;
}
void SimpleTandomSampling()
{
	std::vector<int> numList;

	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		bool flagRandom = true;
		while (flagRandom)
		{
			int random = rand() % TOTAL_NUM;
			flagRandom = false;
			for each (int n in numList)
			{
				if (n == random)
				{
					flagRandom = true;
					break;
				}
			}
			if (flagRandom == false)
			{
				numList.push_back(random);
				samples.push_back(dataSet[random]);
			}
		}

	}
}

int getMode(std::vector<int>& nums)
{
	int result = 0;
	int freq = 0;
	int maxFreq = 0;
	int last = nums[0];
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == last)
			freq++;
		else
		{
			if (freq > maxFreq)
			{
				result = last;
				maxFreq = freq;
			}
			last = nums[i];
			freq = 1;
		}
	}
	return result;
}

float getMean(std::vector<int>& nums)
{
	float result = 0;
	float sum=0;
	for (int i = 0; i < nums.size(); i++)
		sum += nums[i];
	result = sum / nums.size();
	return result;
}

float getMedian(std::vector<int>& nums)
{
	float result = 0;
	if (nums.size() % 2 == 1)
		result = nums[nums.size() / 2];
	else
	{
		result = (float(nums[nums.size() / 2] + nums[nums.size() / 2 - 1])) / 2.0f;
	}
	return result;
}

void printResult()
{
	int dataNum = dataSet[0].size();
	std::cout << "===============Samples================";
	std::cout << std::endl;
	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		for (int j = 0; j < dataNum; j++)
			std::cout << std::setw(5) << samples[i][j];
		std::cout << std::endl;
	}
	std::vector<int> modes;
	std::vector<float> means;
	std::vector<float> medians;
	std::cout << std::endl;

	std::cout <<"=================Result==================";

	for (int k = 0; k <dataNum; k++)
	{
		std::vector<int> data;
		for (int i = 0; i < SAMPLE_NUM; ++i)
			data.push_back(samples[i][k]);
		std::sort(data.begin(), data.end());
		int mode = getMode(data);
		modes.push_back(mode);
		float mean = getMean(data);
		means.push_back(mean);
		float median = getMedian(data);
		medians.push_back(median);
	}
	std::cout << std::endl;
	std::cout << std::setw(5) << "mode";
	for (int j = 1; j < dataNum; j++)
		std::cout << std::setw(5) << modes[j];
	std::cout << std::endl;

	std::cout << std::setw(5) << "mean";
	for (int j = 1; j < dataNum; j++)
		std::cout << std::setw(8) << means[j];
	std::cout << std::endl;

	std::cout << std::setw(5) << "median";
	for (int j = 1; j < dataNum; j++)
		std::cout << std::setw(8) << medians[j];
	std::cout << std::endl;

}
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	readFile("Nudge.txt");
	SimpleTandomSampling();
	printResult();
	getchar();
	return 0;
}

