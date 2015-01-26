// SimpleRandom.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include <time.h>
int TOTAL_NUM = 316;
int SAMPLE_NUM = 20;

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

 class Data2 : public DataType
 {
 public:
	 virtual void print()
	 {
		 std::cout << item << std::endl;
	 }
	 virtual void read(std::ifstream& dataFile)
	 {
		 std::getline(dataFile, item);
	 }
	 virtual ~Data2(){}
	 std::string item;
 };

 std::vector < DataType*> dataSet;
 std::vector < DataType*> samples;

bool readFile1(const char* filename)
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

bool readFile2(const char* filename)
{
	std::ifstream dataFile(filename, std::ifstream::in);
	if (dataFile.bad())
		return false;

	std::string s;
	std::getline(dataFile, s);

	TOTAL_NUM = 0;
	while (!dataFile.eof())
	{
		Data2* dataItem = new Data2();
		dataItem->read(dataFile);
		dataSet.push_back(dataItem);
		TOTAL_NUM++;
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

void ReservoirSampling(int sampleNum)
{
	SAMPLE_NUM = sampleNum;
	samples.resize(SAMPLE_NUM);
	int i; 
	for (i = 0; i < SAMPLE_NUM; i++)
		samples[i] = dataSet[i];

	for (; i < TOTAL_NUM; i++)
	{
		int j = rand() % (i + 1);
		if (j < SAMPLE_NUM)
			samples[j] = dataSet[i];
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

void printResult1()
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

void printResult2()
{
	std::cout << "===============Samples================";
	std::cout << std::endl;
	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		samples[i]->print();
	}
	std::cout << std::endl;
}

void question2()
{
	readFile2("Current_Employee_Names__Salaries__and_Position_Titles.csv");
	ReservoirSampling(20);
	printResult2();
}

void question1()
{
	readFile1("Nudge.txt");
	ReservoirSampling(20);
	printResult1();
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (argc != 2)
		 return 1;
	int num = atoi(argv[1]);
	if (num == 0)
		question1();
	else if (num == 1)
		question2();

	cleanup();

	return 0;
}

