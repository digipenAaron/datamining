
#include <vector>
#include "DataNode.h"
using namespace std;

//the class used to do kmean clustering
class DataCluster
{
public:
	DataCluster(vector<IDataNode*> rawData) :raw(rawData){}

	~DataCluster()
	{
		for (int i = 0; i < centroids.size(); ++i)
			delete centroids[i];
	}

	bool doKMeansClustering(int k); //run the kmeans algorithm, k is the cluster number

	void print(); //print result

private:

	int minDistanceCentroid(IDataNode* n); //find the index of the centroid closest to n

	void init(int clusterNum);

	void initCentroids(); //initialize centroids randomly

	float computeCentroids(); //re-calculate centroids depends on clustering

	float evaluate(); //not be used now

private:
	int clusterNum;
	vector<vector<IDataNode*>> groups; //groups of clustering result
	vector<IDataNode*> centroids;
	vector<IDataNode*> raw;
};
