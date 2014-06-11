#include "DataCluster.h"
//Height and width
void test0()
{
	DataNode0 raw[] = {
		DataNode0(0, 65.0, 220.0),
		DataNode0(1, 73.0, 160.0),
		DataNode0(2, 59.0, 110.0),
		DataNode0(3, 61.0, 120.0),
		DataNode0(4, 75.0, 150.0),
		DataNode0(5, 67.0, 240.0),
		DataNode0(6, 68.0, 230.0),
		DataNode0(7, 70.0, 220.0),
		DataNode0(8, 62.0, 130.0),
		DataNode0(9, 66.0, 210.0),
		DataNode0(10, 77.0, 190.0),
		DataNode0(11, 75.0, 180.0),
		DataNode0(12, 74.0, 170.0),
		DataNode0(13, 70.0, 210.0),
		DataNode0(14, 61.0, 110.0),
		DataNode0(15, 58.0, 100.0),
		DataNode0(16, 66.0, 230.0),
		DataNode0(17, 59.0, 120.0),
		DataNode0(18, 68.0, 210.0),
		DataNode0(19, 61.0, 130.0)
	};
	vector<IDataNode*> Raw;
	for (int i = 0; i < 20; ++i){
		Raw.push_back(&raw[i]);
	}

	DataCluster cluster(Raw);
	cluster.doKMeansClustering(3);
	cluster.print();
}

//Income
void test1()
{
	DataIncome raw[] = {
		DataIncome(0, 17546),
		DataIncome(1, 30085.1),
		DataIncome(2, 16575.4),
		DataIncome(3, 20375.4),
		DataIncome(4, 50576.3),
		DataIncome(5, 37869.6),
		DataIncome(6, 8877.07),
		DataIncome(7, 24946.6),
		DataIncome(8, 25304.3),
		DataIncome(9, 24212.1),
		DataIncome(10, 59803.9),
		DataIncome(11, 26658.8),
		DataIncome(12, 15735.8),
		DataIncome(13, 55204.7),
		DataIncome(14, 19474.6),
		DataIncome(15, 22342.1),
		DataIncome(16, 17729.8),
		DataIncome(17, 41016),
		DataIncome(18, 26909.2),
		DataIncome(19, 22522.8)
	};
	vector<IDataNode*> Raw;
	for (int i = 0; i < 20; ++i){
		Raw.push_back(&raw[i]);
	}

	DataCluster cluster(Raw);
	cluster.doKMeansClustering(3);
	cluster.print();
}

void main(){
	test1();
	getchar();
}
