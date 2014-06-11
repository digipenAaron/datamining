#include <math.h>
#include <time.h>  
#include <vector>
#include <iostream>

#include "DataCluster.h"

int DataCluster::minDistanceCentroid(IDataNode* n)
{
	int result = 0;
	float minDistance = 10000;
	for (int i = 0; i <clusterNum; ++i){
		float d = n->distance( centroids[i]);
		if (d < minDistance){
			result = i;
			minDistance = d;
		}
	}
	return result;
}

void DataCluster::init(int k)
{
	clusterNum = k;
	centroids.clear();
	for (int i = 0; i < groups.size(); ++i)
		groups[i].clear();
	groups.clear();
	for (int i = 0; i < clusterNum; ++i){
		groups.push_back(vector<IDataNode*>());
	}

	initCentroids();
}

void DataCluster::initCentroids()
{
	for (int i = 0; i <clusterNum; ++i)
		centroids.push_back(raw[rand() % raw.size()]);
}

float DataCluster::computeCentroids()
{
	float changeValue = 0;
	for (int i = 0; i < clusterNum; ++i){
		IDataNode* newCentroid=centroids[0]->computeCentroid(groups[i]);
		changeValue +=centroids[i]->distance(newCentroid);
		centroids[i]=newCentroid;
	}
	return changeValue;
}

float DataCluster::evaluate()
{
	float result = 0;
	for (int i = 0; i < clusterNum; ++i)
		for (int j = 0; j < groups[i].size(); ++j)
			result += groups[i][j]->distance(centroids[i]);
	return result;
}

bool DataCluster::doKMeansClustering(int k)
{
	init(k);
	float change = 100000;
	while (change > 0){  //we can adjust the terminal condition
		for (int i = 0; i <clusterNum; ++i)
			groups[i].clear();

		for (int i = 0; i < raw.size(); ++i)
		{
			int n = minDistanceCentroid(raw[i]);
			groups[n].push_back(raw[i]);
		}
		change = computeCentroids();
	}
	return true;
}

void DataCluster::print()
{
	for (int i = 0; i <clusterNum; ++i){
		cout << "==============" << endl;
		for (int j = 0; j < groups[i].size(); ++j)
			groups[i][j]->print();
	}
	cout << "==============" << endl;
}