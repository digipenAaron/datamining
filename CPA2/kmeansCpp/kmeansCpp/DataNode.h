#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
class IDataNode
{
public:
	virtual void print() = 0;
	virtual double distance(IDataNode* data) = 0;
	virtual IDataNode* computeCentroid(vector<IDataNode*>) = 0;
};

class DataNode0 : public IDataNode
{
public:
	DataNode0(int _id, float h, float w) :id(_id), height(h), width(w){}
	void print()
	{
		cout << setw(2) << id << " (" << height << "," << width << ")" << endl;
	}

	double distance(IDataNode* node)
	{
		DataNode0* d2 = dynamic_cast<DataNode0*>(node);
		return (height - d2->height)*(height - d2->height) + (width - d2->width)*(width - d2->width);
	}

	IDataNode* computeCentroid(vector<IDataNode*> group)
	{
		float sumHeight = 0;
		float sumWidth = 0;
		for (int i = 0; i < group.size(); ++i){
			DataNode0* node = dynamic_cast<DataNode0*>(group[i]);
			sumHeight += node->height;
			sumWidth += node->width;
		}
		if (!group.size())
			return 0;
		DataNode0* centroid = new DataNode0(0, sumHeight / group.size(), sumWidth / group.size());
		return centroid;
	}

	int id;
	double height;
	double width;
};

class DataIncome : public IDataNode
{
public:
	DataIncome(int _id, double _income) :id(_id), income(_income){}
	void print()
	{
		cout << setw(2) << id << " (" << income << ")" << endl;
	}

	double distance(IDataNode* node)
	{
		DataIncome* d2 = dynamic_cast<DataIncome*>(node);
		return fabs(income - d2->income);
	}

	IDataNode* computeCentroid(vector<IDataNode*> group)
	{
		double sum = 0;
		for (int i = 0; i < group.size(); ++i){
			DataIncome* node = dynamic_cast<DataIncome*>(group[i]);
			sum += node->income;
		}
		if (!group.size())
			return 0;
		DataIncome* centroid = new DataIncome(0, sum / group.size());
		return centroid;
	}

	int id;
	double income;
};