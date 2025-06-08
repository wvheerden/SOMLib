#include "AggregateMapCluster.h"
#include "MapCluster.h"
#include "WeightVector.h"
#include "HitCount.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : AggregateMapCluster(MapCluster&, MapCluster&)
// Purpose     : Constructs aggregate map cluster with
//               provided sub-clusters
// ===================================================

AggregateMapCluster::AggregateMapCluster(unsigned int _clusteringLevel, MapCluster& _subCluster1, MapCluster& _subCluster2):
MapCluster(_clusteringLevel), subCluster1(&_subCluster1), subCluster2(&_subCluster2) {
	
	// calculate new cluster centroid
	double cluster1Count = (double) subCluster1->getWeightVectorCount();
	double cluster2Count = (double) subCluster2->getWeightVectorCount();
	std::vector<double> cluster1Centroid = subCluster1->getCentroid();
	std::vector<double> cluster2Centroid = subCluster2->getCentroid();
	
	for (unsigned int i = 0; i < cluster1Centroid.size(); ++i) {
		centroid.push_back(((cluster1Count * cluster1Centroid[i]) + (cluster2Count * cluster2Centroid[i])) / (cluster1Count + cluster2Count));
	}
	
}

// ===================================================
// Constructor : AggregateMapCluster(const AggregateMapCluster&)
// Purpose     : Copy constructor
// ===================================================

AggregateMapCluster::AggregateMapCluster(const AggregateMapCluster& source) :
MapCluster(source), subCluster1(source.subCluster1), subCluster2(source.subCluster2), centroid(source.centroid) {
	
	;
	
}

// ===================================================
// Destructor : ~AggregateMapCluster()
// Purpose    : Deallocates object resources
// ===================================================

AggregateMapCluster::~AggregateMapCluster() {
	
	// de-allocate sub-clusters
	delete subCluster1;
	delete subCluster2;
	
}

// *** Accessors ***

// ===================================================
// Accessor : int getWeightVectorCount() const
// Purpose  : Returns number of weight vectors in this
//            cluster (i.e. the number of leaf nodes
//            below this node)
// ===================================================

int AggregateMapCluster::getWeightVectorCount() const {
	
	// count leaf nodes under each sub-node
	return subCluster1->getWeightVectorCount() + subCluster2->getWeightVectorCount();
	
}

// ===================================================
// Accessor : vector<WeightVector*> getWeightVectors()
// Purpose  : Returns weight vectors belonging to this
//            cluster (i.e. the weight vectors that
//            are leaf nodes under this node)
// ===================================================

std::vector<const WeightVector*> AggregateMapCluster::getWeightVectors() const {
	
	// find leaf node counts for each sub-node
	int subLeafCount1 = subCluster1->getWeightVectorCount();
	int subLeafCount2 = subCluster2->getWeightVectorCount();
	
	// find lists of leaf nodes for each sub-node
	std::vector<const WeightVector*> subLeaves1 = subCluster1->getWeightVectors();
	std::vector<const WeightVector*> subLeaves2 = subCluster2->getWeightVectors();
	
	// concatenate leaf node lists
	std::vector<const WeightVector*> returnVector;
	
	for (int i = 0; i < subLeafCount1; ++i) {
		returnVector.push_back(subLeaves1[i]);
	}
	
	for (int i = 0; i < subLeafCount2; ++i) {
		returnVector.push_back(subLeaves2[i]);
	}
	
	return returnVector;
	
}

// ===================================================
// Accessor : double* getCentroid() const
// Purpose  : Returns a copy of this cluster's centroid
// ===================================================

std::vector<double> AggregateMapCluster::getCentroid() const {
	
	return centroid;
	
}

// ===================================================
// Accessor : double getIntraClusterDistance() const
// Purpose  : Calculate average Euclidean
//            intra-cluster distance (average distance
//            between constituent weight vectors and
//            cluster centroid)
// ===================================================

double AggregateMapCluster::getIntraClusterDistance() const {
	
	double intraClusterDistance = 0.0;
	std::vector<const WeightVector*> constituentWeightVectors = getWeightVectors();
	
	for (unsigned int i = 0; i < constituentWeightVectors.size(); ++i) {
		intraClusterDistance += constituentWeightVectors[i]->getEuclideanDistance(centroid);
	}
	
	return (intraClusterDistance / ((double) constituentWeightVectors.size()));
	
}

// ===================================================
// Accessor : vector<HitCount> getHitCounts() const
// Purpose  : Returns a vector of hit counts for this
//            aggregate cluster
// ===================================================

std::vector<HitCount> AggregateMapCluster::getHitCounts() const {
	
	std::vector<HitCount> subCluster1HitCounts = subCluster1->getHitCounts();
	std::vector<HitCount> subCluster2HitCounts = subCluster2->getHitCounts();
	
	mergeHitCounts(subCluster1HitCounts, subCluster2HitCounts);
	
	return subCluster1HitCounts;
	
}

// ===================================================
// Accessor : void getNClusters(unsigned int, vector<MapCluster*>&, vector<string>&) const
// Purpose  : Perform recursive tree traversal,
//            searching for specified level of
//            clustering
// ===================================================

void AggregateMapCluster::getNClusters(unsigned int targetClusteringLevel, std::vector<const MapCluster*>& storageVector, std::vector<std::string>& labelVector) const {
	
	if (targetClusteringLevel <= clusteringLevel) {
		storageVector.push_back(this);
		std::vector<HitCount> constituentHitCounts = getHitCounts();
		updateLabelVector(constituentHitCounts, labelVector);
	} else {
		subCluster1->getNClusters(targetClusteringLevel, storageVector, labelVector);
		subCluster2->getNClusters(targetClusteringLevel, storageVector, labelVector);
	}
	
}

// *** Public Utility Functions ***

// ===================================================
// Utility : bool isMember(const WeightVector&) const
// Purpose : Tests membership of supplied weight
//           vector to this map cluster (i.e. returns
//           true only if supplied weight vector is a
//           member of one of the constituent
//           sub-clusters)
// ===================================================

bool AggregateMapCluster::isMember(const WeightVector& vector) const {
	
	return ((subCluster1->isMember(vector)) || (subCluster2->isMember(vector)));
	
}

// *** Protected Utility Functions ***

// ===================================================
// Utility Function : ostream& output(ostream&, const char*, const char*, const char*) const
// Purpose          : Output AggregateCluster object
// ===================================================

std::ostream& AggregateMapCluster::output(std::ostream& out, const char* leader, const char* separator, const char* terminator) const {
	
	out << leader;
	subCluster1->output(out, leader, separator, terminator);
	out << separator;
	subCluster2->output(out, leader, separator, terminator);
	out << terminator;
	
	return out;
	
}

// *** Private Utility Functions ***

// ===================================================
// Utility : void mergeHitCounts(vector<HitCount>&, vector<HitCount>&) const
// Purpose : Merge second hit count vector into first
// ===================================================

void AggregateMapCluster::mergeHitCounts(std::vector<HitCount>& hitCounts1, std::vector<HitCount>& hitCounts2) const {
	
	for (unsigned int i = 0; i < hitCounts2.size(); ++i) {
		
		bool found = false;
		
		for (unsigned int j = 0; j < hitCounts1.size(); ++j) {
			
			if (hitCounts1[j].getLabel() == hitCounts2[i].getLabel()) {
				hitCounts1[j].incrementCount(hitCounts2[i].getCount());
				found = true;
				break;
			}
			
		}
		
		if (!found) {
			HitCount newCount(hitCounts2[i]);
			hitCounts1.push_back(newCount);
		}
		
	}
	
}
