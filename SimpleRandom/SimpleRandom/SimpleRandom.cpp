// SimpleRandom.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include <time.h>
const int TOTAL_NUM = 316;
const int SAMPLE_NUM = 20;

 class DataType
{
public:
	virtual void print(){}
	virtual void read(std::ifstream&){}
	virtual ~DataType(){}
};

 class Data1 : public DataType
 {
 public:
	 Data1() :dataItem(std::vector<int>(12)){}
	 virtual void print()
	 {
		 int dataNum = dataItem.size();
		 for (int j = 0; j < dataNum; j++)
			 std::cout << std::setw(5) << dataItem[j];
		 std::cout << std::endl;

	 }
	 virtual void read(std::ifstream& dataFile)
	 {
		 for (int i = 0; i < 12; i++)
			 dataFile >> dataItem[i];
	 }
	 virtual ~Data1(){}

	 std::vector<int> dataItem;
 };

 std::vector < DataType*> dataSet;
 std::vector < DataType*> samples;

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

	
	for (int iline = 0; iline < TOTAL_NUM; iline++)
	{
		Data1* dataItem = new Data1();
		dataItem->read(dataFile);
		dataSet.push_back(dataItem);
	}
	return true;
}

void cleanup()
{
	for (int iline = 0; iline < TOTAL_NUM; iline++)
	{
		delete dataSet[iline];
	}
}

void SimpleRandomSampling()
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

float getMode(std::vector<float>& nums)
{
	float result = 0;
	float freq = 0;
	float maxFreq = 0;
	float last = nums[0];
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

float getMean(std::vector<float>& nums)
{
	float result = 0;
	float sum=0;
	for (int i = 0; i < nums.size(); i++)
		sum += nums[i];
	result = sum / nums.size();
	return result;
}

float getMedian(std::vector<float>& nums)
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
	std::cout << "===============Samples================";
	std::cout << std::endl;
	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		samples[i]->print();
	}
	std::vector<int> modes;
	std::vector<float> means;
	std::vector<float> medians;
	std::cout << std::endl;

	std::cout <<"=================Result==================";

	for (int k = 0; k <12; k++)
	{
		std::vector<float> data;
		for (int i = 0; i < SAMPLE_NUM; ++i)
		{
			Data1* data1 = dynamic_cast<Data1*>(samples[i]);
			data.push_back(data1->dataItem[k]);
		}
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
	for (int j = 1; j < 12; j++)
		std::cout << std::setw(5) << modes[j];
	std::cout << std::endl;

	std::cout << std::setw(5) << "mean";
	for (int j = 1; j < 12; j++)
		std::cout << std::setw(8) << means[j];
	std::cout << std::endl;

	std::cout << std::setw(5) << "median";
	for (int j = 1; j < 12; j++)
		std::cout << std::setw(8) << medians[j];
	std::cout << std::endl;

}
int main()
{
	srand(time(NULL));
	readFile("Nudge.txt");
	SimpleRandomSampling();
	printResult();
	cleanup();
	getchar();
	return 0;
}

