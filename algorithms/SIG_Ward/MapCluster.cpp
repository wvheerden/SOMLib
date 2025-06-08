#include <cmath>

#include "MapCluster.h"
#include "WeightVector.h"
#include "Random.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : MapCluster(unsigned int)
// Purpose     : Constructs map cluster with given
//               merge sequence
// ===================================================

MapCluster::MapCluster(unsigned int _clusteringLevel) :
clusteringLevel(_clusteringLevel) {
	
	;
	
}

// ===================================================
// Constructor : MapCluster(const MapCluster&)
// Purpose     : Copy constructor
// ===================================================

MapCluster::MapCluster(const MapCluster& source) :
clusteringLevel(source.clusteringLevel) {
	
	;
	
}

// ===================================================
// Destructor : ~MapCLuster()
// Purpose    : De-allocates object resources
// ===================================================

MapCluster::~MapCluster() {
	
	;
	
}

// *** Utility Functions ***

// ===================================================
// Accessor : double calculateWardDistance(MapCluster&) const
// Purpose  : Calculate Ward distance between this map
//            cluster and another
// ===================================================

double MapCluster::calculateWardDistance(MapCluster& cluster) const {
	
	double centroidDistance = 0.0;
	std::vector<double> centroid1 = this->getCentroid();
	std::vector<double> centroid2 = cluster.getCentroid();
	
	for (unsigned int i = 0; i < centroid1.size(); ++i) {
		centroidDistance += pow((centroid1[i] - centroid2[i]), 2.0);
	}
	
	double centroid1Count = (double) getWeightVectorCount();
	double centroid2Count = (double) cluster.getWeightVectorCount();
	
	double returnValue = (((centroid1Count * centroid2Count) / (centroid1Count + centroid2Count)) * centroidDistance);
	
	if (!std::isfinite(returnValue)) {
		std::cerr << std::endl << "ERROR: Invalid Ward distance computed" << std::endl;
	}
	
	return returnValue;
	
}

// ===================================================
// Accessor : double calculateInterClusterDistance(MapCluster&) const
// Purpose  : Calculate Euclidean inter-cluster
//            distance between this map cluster and
//            another (Euclidean distance between
//            respective cluster centroids)
// ===================================================

double MapCluster::calculateInterClusterDistance(MapCluster& cluster) const {
	
	double interClusterDistance = 0.0;
	std::vector<double> centroid1 = this->getCentroid();
	std::vector<double> centroid2 = cluster.getCentroid();
	
	for (unsigned int i = 0; i < centroid1.size(); ++i) {
		interClusterDistance += pow(centroid1[i] - centroid2[i], 2.0);
	}
	
	double returnValue = sqrt(interClusterDistance);
	
	if (!std::isfinite(returnValue)) {
		std::cerr << std::endl << "ERROR: Invalid inter cluster distance computed" << std::endl;
	}
	
	return returnValue;
	
}

// ===================================================
// Accessor : double calculateSimilarityMeasure(MapCluster&) const
// Purpose  : Calculate Davies-Bouldin similarity
//            measure between this map cluster and
//            another
// NOTE     : The result will be infinity if this
//            cluster has the same centroid as the
//            other cluster. This results in the
//            entire Davies-Bouldin index being
//            computed as infinity (see comment for
//            getCurrentDaviesBouldinIndex in class
//            SOMMap).
// ===================================================

double MapCluster::calculateSimilarityMeasure(MapCluster& cluster) const {
	
	return (this->getIntraClusterDistance() + cluster.getIntraClusterDistance()) / this->calculateInterClusterDistance(cluster);
	
}

// *** Protected Utility Functions ***

// ===================================================
// Utility : void updateLabelVector(vector<HitCount>&, vector<std::string>&) const
// Purpose : Update label vector appropriately using
//           data in hit count vector
// ===================================================

void MapCluster::updateLabelVector(const std::vector<HitCount>& hitCountVector, std::vector<std::string>& labelVector) const {
	
	if (hitCountVector.size() == 0) {
		labelVector.push_back("");
		return;
	}
	
	// search for set of maximum hit count indices
	unsigned int maxCount = 0;
	std::vector<unsigned int> maxCountIndices;
	
	for (unsigned int i = 0; i < hitCountVector.size(); ++i) {
		if (hitCountVector[i].getCount() > maxCount) {
			maxCount = hitCountVector[i].getCount();
			maxCountIndices.clear();
			maxCountIndices.push_back(i);
		}
		else if (hitCountVector[i].getCount() == maxCount) {
			maxCountIndices.push_back(i);
		}
	}
	
	// select one of the optimal indices (settle ties arbitrarily)
	unsigned long int maxCountIndex = 0;
	
	if (maxCountIndices.size() == 1) {
		maxCountIndex = maxCountIndices[0];
	} else {
		maxCountIndex = maxCountIndices[Random::getInstance()->getNextInt(maxCountIndices.size())];
	}
	
	// update label vector with selected optimal index
	labelVector.push_back(hitCountVector[maxCountIndex].getLabel());
	
}
