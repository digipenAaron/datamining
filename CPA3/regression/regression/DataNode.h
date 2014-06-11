#include <vector>
#include <iostream>
#include <iomanip>
#include <stdarg.h>
using namespace std;
class DataNode
{
public:
	DataNode(int _id, float a1, float a2, int t) :id(_id), type(t)
	{
		a.push_back(1);
		a.push_back(a1);
		a.push_back(a2);
	}
	int id;
	vector<float> a;
	int type;
};

