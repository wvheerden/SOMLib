#include <stdexcept>
#include <iomanip>
#include <cfloat>
#include <cmath>

#include "SOMMap.h"
#include "Random.h"
#include "WeightVector.h"
#include "AggregateMapCluster.h"
#include "DataFileReader.h"
#include "DataPattern.h"
#include "GreaterThanRuleCondition.h"
#include "LessThanRuleCondition.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : SOMMap(unsigned int, unsigned int, unsigned int, double***)
// Purpose     : Constructs map with given map width,
//               height, weight dimension and map grid
// ===================================================

SOMMap::SOMMap(unsigned int _width, unsigned int _height, unsigned int _weightDimension, double*** weights) :
width(_width), height(_height), weightDimension(_weightDimension), mapGrid(new WeightVector**[_height]) {
	
	// initialise map grid
	for (unsigned int i = 0; i < height; ++i) {
		mapGrid[i] = new WeightVector*[width];
		
		for (unsigned int j = 0; j < width; ++j) {
			// add weight vector to grid
			WeightVector* tempWeightVector = new WeightVector((width * height), weights[i][j], weightDimension);
			mapGrid[i][j] = tempWeightVector;
			
			// add weight vector to cluster vector
			clusterVector.push_back(tempWeightVector);
			
			// add distance matrix and similarity matrix rows (don't add row for the first weight vector, which is compared only to itself)
			if ((i != 0) || (j != 0)) {
				std::vector<double> tempDistanceVector;
				std::vector<double> tempSimilarityMeasureVector;
				
				// add measures of all preceding weight vectors in the grid (exclude the current weight vector itself)
				for (unsigned int k = 0; k <= i; ++k) {
					// calculate all measures for preceding grid rows, and the partial set of vectors for the final grid row
					for (unsigned int l = 0; ((k < i) && (l < width)) || ((k == i) && (l < j)); ++l) {
						// add valid Ward distance (for neighbouring weight vectors) or maximum distance (for non-neighbouring weight vectors)
						if (((k == i) || (k == (i - 1))) && ((l == (j - 1)) || (l == j) || (l == (j + 1)))) {
							tempDistanceVector.push_back(mapGrid[i][j]->calculateWardDistance(*(mapGrid[k][l])));
						} else {
							tempDistanceVector.push_back(DBL_MAX);
						}
						
						// add valid Davies-Bouldin similarity measure (intra-cluster distance for unary clusters is 5000.0)
						tempSimilarityMeasureVector.push_back(mapGrid[i][j]->calculateSimilarityMeasure(*(mapGrid[k][l])));
					}
				}
				
				distanceMatrix.push_back(tempDistanceVector);
				similarityMeasureMatrix.push_back(tempSimilarityMeasureVector);
			}
		}
	}
	
	// calculate and store initial cluster cost
	clusterCosts.push_back(getCurrentDaviesBouldinIndex());
	
}

// ===================================================
// Constructor : SOMMap(const SOMMap&)
// Purpose     : Copy constructor (private to forbid
//               copying)
// ===================================================

SOMMap::SOMMap(const SOMMap& sourceMap) throw (std::runtime_error) {
	
	throw std::runtime_error("Attempt to copy SOMMap");
	
}

// ===================================================
// Destructor : ~SOMMap()
// Purpose    : De-allocates object resources
// ===================================================

SOMMap::~SOMMap() {
	
	// deallocate cluster tree
	for (unsigned int i = 0; i < clusterVector.size(); ++i) {
		delete clusterVector[i];
	}
	
	// de-allocate map grid
	for (unsigned int i = 0; i < height; ++i) {
		delete[] mapGrid[i];
	}
	
	delete[] mapGrid;
	
}

// *** Accessors ***

// ===================================================
// Accessor : int getWidth() const
// Purpose  : Returns width of map
// ===================================================

unsigned int SOMMap::getWidth() const {
	
	return width;
	
}

// ===================================================
// Accessor : int getHeight() const
// Purpose  : Returns height of map
// ===================================================

unsigned int SOMMap::getHeight() const {
	
	return height;
	
}

// ===================================================
// Accessor : int getWeightDimension() const
// Purpose  : Returns weight dimension of map
// ===================================================

unsigned int SOMMap::getWeightDimension() const {
	
	return weightDimension;
	
}

// ===================================================
// Accessor : unsigned int getOptimalClusterCount() const
// Purpose  : Return current number of optimal clusters
// ===================================================

unsigned int SOMMap::getOptimalClusterCount() const {
	
	return optimalClusters.size();
	
}

// ===================================================
// Accessor : string getOptimalClusterLabel(unsigned int) const
// Purpose  : Return label of specified optimal cluster
// ===================================================

std::string SOMMap::getOptimalClusterLabel(unsigned int index) const {
	
	return optimalClusterLabels[index];
	
}

// ===================================================
// Accessor : vector<DataPattern> getOptimalClusterMappedPatterns(DataFileReader&)
// Purpose  : Return mapped data patterns from the supplied
//            data reader, where each return vector index
//            corresponds to the mapped examples of an
//            optimal cluster
// ===================================================

std::vector<std::vector<DataPattern> > SOMMap::getOptimalClusterMappedPatterns(DataFileReader& dataReader) {
	
	// return structure
	std::vector<std::vector<DataPattern> > returnVector;
	
	for (unsigned int i = 0; i < optimalClusters.size(); ++i) {
		
		std::vector<DataPattern> clusterMappedPatterns;
		returnVector.push_back(clusterMappedPatterns);
		
	}
	
	// update weight vector hit counts using entire data set
	for (unsigned int i = 0; i < dataReader.getRecordCount(); ++i) {
		
		// search for set of best matching units for current data record
		DataPattern currentRecord = dataReader.getRecord(i);
		double minDistance = DBL_MAX;
		std::vector<WeightVector*> bestMatchingUnits;
		
		for (unsigned int j = 0; j < height; ++j) {
			for (unsigned int k = 0; k < width; ++k) {
				
				double tempDistance = (mapGrid[j][k])->getEuclideanDistance(currentRecord);
				
				if (tempDistance < minDistance) {
					minDistance = tempDistance;
					bestMatchingUnits.clear();
					bestMatchingUnits.push_back(mapGrid[j][k]);
				} else if (tempDistance == minDistance) {
					bestMatchingUnits.push_back(mapGrid[j][k]);
				}
				
			}
		}
		
		// select one of the best matching units (settle ties arbitrarily)
		WeightVector* selectedBestMatchingUnit = NULL;
		
		if (bestMatchingUnits.size() == 1) {
			selectedBestMatchingUnit = bestMatchingUnits[0];
		} else {
			selectedBestMatchingUnit = bestMatchingUnits[Random::getInstance()->getNextInt(bestMatchingUnits.size())];
		}
		
		// determine which emergent cluster the pattern's BMU falls within (no tie settling - a BMU can only map to one cluster)
		for (unsigned int k = 0; k < optimalClusters.size(); ++k) {
			
			// add record for the appropriate cluster
			if (optimalClusters[k]->isMember(*selectedBestMatchingUnit)) {
				returnVector[k].push_back(currentRecord);
			}
			
		}
		
	}
	
	return returnVector;
	
}

// *** Utility Functions ***

// ===================================================
// Utility : void wardClusterMap()
// Purpose : Initiates Ward clustering process
// ===================================================

void SOMMap::wardClusterMap() {
	
	while (clusterVector.size() > 2) {
		
		// locate closest set of cluster pairs to merge (mergeClusterIndex1 is always smaller than mergeClusterIndex2)
		double minDistance = DBL_MAX;
		std::vector<unsigned int> mergeCluster1Indices;
		std::vector<unsigned int> mergeCluster2Indices;
		
		for (unsigned int i = 0; i < distanceMatrix.size(); ++i) {
			for (unsigned int j = 0; j < distanceMatrix[i].size(); ++j) {
				if (distanceMatrix[i][j] < minDistance) {
					minDistance = distanceMatrix[i][j];
					mergeCluster1Indices.clear();
					mergeCluster1Indices.push_back(j);
					mergeCluster2Indices.clear();
					mergeCluster2Indices.push_back(i + 1);
				}
				else if (distanceMatrix[i][j] == minDistance) {
					mergeCluster1Indices.push_back(j);
					mergeCluster2Indices.push_back(i + 1);
				}
			}
		}
		
		// select one of the merge cluster pairs (settle ties arbitrarily)
		unsigned int mergeCluster1Index = 0;
		unsigned int mergeCluster2Index = 0;
		
		if (mergeCluster1Indices.size() == 1) {
			mergeCluster1Index = mergeCluster1Indices[0];
			mergeCluster2Index = mergeCluster2Indices[0];
		} else {
			unsigned long int selectIndex = Random::getInstance()->getNextInt(mergeCluster1Indices.size());
			mergeCluster1Index = mergeCluster1Indices[selectIndex];
			mergeCluster2Index = mergeCluster2Indices[selectIndex];
		}
		
		// store constituent clusters and create new aggregate cluster
		MapCluster* constituentCluster1 = clusterVector[mergeCluster1Index];
		MapCluster* constituentCluster2 = clusterVector[mergeCluster2Index];
		AggregateMapCluster* newCluster = new AggregateMapCluster((clusterVector.size() - 1), *constituentCluster1, *constituentCluster2);
		
		// delete old clusters and add new cluster to cluster vector at position mergeCluster1Index
		clusterVector.erase(clusterVector.begin() + mergeCluster2Index);
		clusterVector.erase(clusterVector.begin() + mergeCluster1Index);
		clusterVector.insert(clusterVector.begin() + mergeCluster1Index, newCluster);
		
		// update distance matrix and similarity measure matrix rows at mergeCluster1Index
		for (unsigned int i = 0; ((mergeCluster1Index > 0) && (i < distanceMatrix[mergeCluster1Index - 1].size())); ++i) {
			
			if ((distanceMatrix[mergeCluster1Index - 1][i] != DBL_MAX) || (distanceMatrix[mergeCluster2Index - 1][i] != DBL_MAX)) {
				distanceMatrix[mergeCluster1Index - 1][i] = newCluster->calculateWardDistance(*(clusterVector[i]));
			} else {
				distanceMatrix[mergeCluster1Index - 1][i] = DBL_MAX;
			}
			
			similarityMeasureMatrix[mergeCluster1Index - 1][i] = newCluster->calculateSimilarityMeasure(*(clusterVector[i]));
		}
		
		// update distance matrix and similarity measure matrix columns at mergeCluster1Index
		for (unsigned int i = mergeCluster1Index; i < distanceMatrix.size(); ++i) {
			
			if (i < (mergeCluster2Index - 1)) {
				
				if ((distanceMatrix[i][mergeCluster1Index] != DBL_MAX) || (distanceMatrix[mergeCluster2Index - 1][i + 1] != DBL_MAX)) {
					distanceMatrix[i][mergeCluster1Index] = newCluster->calculateWardDistance(*(clusterVector[i + 1]));
				} else {
					distanceMatrix[i][mergeCluster1Index] = DBL_MAX;
				}
				
				similarityMeasureMatrix[i][mergeCluster1Index] = newCluster->calculateSimilarityMeasure(*(clusterVector[i + 1]));
				
			} else if (i > (mergeCluster2Index - 1)) {
				
				if ((distanceMatrix[i][mergeCluster1Index] != DBL_MAX) || (distanceMatrix[i][mergeCluster2Index] != DBL_MAX)) {
					distanceMatrix[i][mergeCluster1Index] = newCluster->calculateWardDistance(*(clusterVector[i]));
				} else {
					distanceMatrix[i][mergeCluster1Index] = DBL_MAX;
				}
				
				similarityMeasureMatrix[i][mergeCluster1Index] = newCluster->calculateSimilarityMeasure(*(clusterVector[i]));
				
			}
			
		}
		
		// delete distance matrix and similarity measure matrix rows at mergeCluster2Index
		distanceMatrix.erase(distanceMatrix.begin() + (mergeCluster2Index - 1));
		similarityMeasureMatrix.erase(similarityMeasureMatrix.begin() + (mergeCluster2Index - 1));
		
		// delete distance matrix and similarity measure matrix columns at mergeCluster2Index
		for (unsigned int i = (mergeCluster2Index - 1); i < distanceMatrix.size(); ++i) {
			distanceMatrix[i].erase(distanceMatrix[i].begin() + mergeCluster2Index);
			similarityMeasureMatrix[i].erase(similarityMeasureMatrix[i].begin() + mergeCluster2Index);
		}
		
		// calculate and store cluster cost
		clusterCosts.insert(clusterCosts.begin(), getCurrentDaviesBouldinIndex());
		
	}
	
	// merge last 2 remaining clusters
	MapCluster* constituentCluster1 = clusterVector[0];
	MapCluster* constituentCluster2 = clusterVector[1];
	AggregateMapCluster* newCluster = new AggregateMapCluster(1, *constituentCluster1, *constituentCluster2);
	clusterVector.clear();
	clusterVector.push_back(newCluster);
	
}

// ===================================================
// Utility : void labelMap(DataFileReader&)
// Purpose : Initiates cluster labelling process
// ===================================================

void SOMMap::labelMap(DataFileReader& dataReader) {
	
	// update weight vector hit counts using entire data set
	for (unsigned int i = 0; i < dataReader.getRecordCount(); ++i) {
		
		// search for set of best matching units for current data record
		DataPattern currentRecord = dataReader.getRecord(i);
		double minDistance = DBL_MAX;
		std::vector<WeightVector*> bestMatchingUnits;
		
		for (unsigned int j = 0; j < height; ++j) {
			for (unsigned int k = 0; k < width; ++k) {
				
				double tempDistance = (mapGrid[j][k])->getEuclideanDistance(currentRecord);
				
				if (tempDistance < minDistance) {
					minDistance = tempDistance;
					bestMatchingUnits.clear();
					bestMatchingUnits.push_back(mapGrid[j][k]);
				} else if (tempDistance == minDistance) {
					bestMatchingUnits.push_back(mapGrid[j][k]);
				}
				
			}
		}
		
		// select one of the best matching units (settle ties arbitrarily)
		WeightVector* bestMatchingUnit = NULL;
		
		if (bestMatchingUnits.size() == 1) {
			bestMatchingUnit = bestMatchingUnits[0];
		} else {
			bestMatchingUnit = bestMatchingUnits[Random::getInstance()->getNextInt(bestMatchingUnits.size())];
		}
		
		// update BMU's hit count
		std::string label = currentRecord.getLabel();
		bestMatchingUnit->updatePatternHitCount(label);
		
	}
	
	// search for set of optimal cluster counts (using Davies-Bouldin indices)
	double minCost = DBL_MAX;
	std::vector<unsigned int> optimalClusterCounts;
	
	for (unsigned int i = 0; i < clusterCosts.size(); ++i) {
		if (clusterCosts[i] < minCost) {
			minCost = clusterCosts[i];
			optimalClusterCounts.clear();
			optimalClusterCounts.push_back(i + 2);
		}
		else if (clusterCosts[i] == minCost) {
			optimalClusterCounts.push_back(i + 2);
		}
	}
	
	// select one of the optimal cluster counts (settle ties arbitrarily)
	unsigned int optimalClusterCount = 0;
	
	if (optimalClusterCounts.size() == 1) {
		optimalClusterCount = optimalClusterCounts[0];
	} else {
		optimalClusterCount = optimalClusterCounts[Random::getInstance()->getNextInt(optimalClusterCounts.size())];
	}
	
//optimalClusterCount = 3;
	// locate optimal set of clusters (for minimum cost), and associated labels
	clusterVector[0]->getNClusters(optimalClusterCount, optimalClusters, optimalClusterLabels);
	
	// strip unlabeled clusters (SIG* can't derive a rule for a cluster that has no label or mapped patterns)
	std::vector<const MapCluster*> keepClusters;
	std::vector<std::string> keepClusterLabels;
	
	for (unsigned int i = 0; i < optimalClusterLabels.size(); ++i) {
		
		if (optimalClusterLabels[i] != "") {
			keepClusters.push_back(optimalClusters[i]);
			keepClusterLabels.push_back(optimalClusterLabels[i]);
		}
		
	}
	
	optimalClusters = keepClusters;
	optimalClusterLabels = keepClusterLabels;
	
	// label individual weight vectors (no tie settling: weight vector member of only 1 cluster)
	if (optimalClusterLabels.size() != 0) {
		for (unsigned int i = 0; i < height; ++i) {
			for (unsigned int j = 0; j < width; ++j) {
				
				unsigned int matchIndex = 0;
				
				for (unsigned int k = 0; k < optimalClusters.size(); ++k) {
					if ((optimalClusters[k])->isMember(*(mapGrid[i][j]))) {
						matchIndex = k;
						break;
					}
				}
				
				(mapGrid[i][j])->setLabel(optimalClusterLabels[matchIndex]);
				
			}
		}
	}
	
}

// ===================================================
// Utility : void addRuleCondition(Rule&, unsigned int, unsigned int, string, double, double) const
// Purpose : Create conditions on the supplied
//           attribute (using the supplied high and
//           low attribute condition constants), for
//           the supplied cluster, and add them to the
//           supplied rule
// ===================================================

void SOMMap::addRuleCondition(Rule& rule, std::vector<std::vector<DataPattern> >& mappedPatterns, unsigned int clusterIndex, unsigned int attributeIndex, std::string attributeLabel, double lowConstant, double highConstant) const {
	
	// compute attribute mean over the mapped patterns for this cluster
	double attributeMean = 0.0;
	
	for (unsigned int i = 0; i < mappedPatterns[clusterIndex].size(); ++i) {
		attributeMean += mappedPatterns[clusterIndex][i].getComponent(attributeIndex);
	}
	
	attributeMean /= mappedPatterns[clusterIndex].size();
	
	// compute attribute standard deviation over the mapped patterns for this cluster
	double accumulator = 0.0;
	
	for (unsigned int i = 0; i < mappedPatterns[clusterIndex].size(); ++i) {
		accumulator += (mappedPatterns[clusterIndex][i].getComponent(attributeIndex) - attributeMean) * (mappedPatterns[clusterIndex][i].getComponent(attributeIndex) - attributeMean);
	}
	
	double attributeStandardDeviation = 0.0;
	
	if (mappedPatterns[clusterIndex].size() <= 0) {
		std::cerr << std::endl << "ERROR: Invalid mapped patterns used when computing rule condition for rule" << std::endl;;
	}
	
	// A cluster containing 1 pattern has a standard deviation of 0.0
	if (mappedPatterns[clusterIndex].size() > 1) {
		attributeStandardDeviation = sqrt(accumulator / (((double) mappedPatterns[clusterIndex].size()) - 1));
	}
	
	if (!std::isfinite(attributeStandardDeviation)) {
		std::cerr << std::endl << "ERROR: Invalid attribute standard deviation computed for rule" << std::endl;;
	}
	
	// calculate new upper and lower condition bounds
	double newConditionLowerBound = attributeMean - (lowConstant * attributeStandardDeviation);
	double newConditionUpperBound = attributeMean + (highConstant * attributeStandardDeviation);
	
	// construct new conditions and add to rule
	GreaterThanRuleCondition newLowerBoundCondition(attributeLabel, attributeIndex, newConditionLowerBound);
	rule.addCondition(newLowerBoundCondition);
	LessThanRuleCondition newUpperBoundCondition(attributeLabel, attributeIndex, newConditionUpperBound);
	rule.addCondition(newUpperBoundCondition);
	
}

// ===================================================
// Utility : void addRuleCondition(vector<RuleCondition*>, unsigned int, unsigned int, string, double, double) const
// Purpose : Create conditions on the supplied
//           attribute (using the supplied high and
//           low attribute condition constants), for
//           the supplied cluster, and add them to the
//           supplied rule condition list
//           (this is a bit of a hack, necessitated by
//           the convoluted SIG* algorithm)
// ===================================================

void SOMMap::addRuleCondition(std::vector<RuleCondition*>& conditionList, std::vector<std::vector<DataPattern> >& mappedPatterns, unsigned int clusterIndex, unsigned int attributeIndex, std::string attributeLabel, double lowConstant, double highConstant) const {
	
	// compute attribute mean over the mapped patterns for this cluster
	double attributeMean = 0.0;
	
	for (unsigned int i = 0; i < mappedPatterns[clusterIndex].size(); ++i) {
		attributeMean += mappedPatterns[clusterIndex][i].getComponent(attributeIndex);
	}
	
	attributeMean /= mappedPatterns[clusterIndex].size();
	
	// compute attribute standard deviation over the mapped patterns for this cluster
	double accumulator = 0.0;
	
	if (mappedPatterns[clusterIndex].size() <= 0) {
		std::cerr << std::endl << "ERROR: Invalid mapped patterns used when computing rule condition for condition list" << std::endl;;
	}
	
	for (unsigned int i = 0; i < mappedPatterns[clusterIndex].size(); ++i) {
		accumulator += (mappedPatterns[clusterIndex][i].getComponent(attributeIndex) - attributeMean) * (mappedPatterns[clusterIndex][i].getComponent(attributeIndex) - attributeMean);
	}
	
	double attributeStandardDeviation = 0.0;
	
	// A cluster containing 1 pattern has a standard deviation of 0.0
	if (mappedPatterns[clusterIndex].size() > 1) {
		attributeStandardDeviation = sqrt(accumulator / (((double) mappedPatterns[clusterIndex].size()) - 1));
	}
	
	if (!std::isfinite(attributeStandardDeviation)) {
		std::cerr << std::endl << "ERROR: Invalid attribute standard deviation computed for condition list" << std::endl;;
	}
	
	// calculate new upper and lower condition bounds
	double newConditionLowerBound = attributeMean - (lowConstant * attributeStandardDeviation);
	double newConditionUpperBound = attributeMean + (highConstant * attributeStandardDeviation);
	
	// construct new conditions and add to rule
	GreaterThanRuleCondition* newLowerBoundCondition = new GreaterThanRuleCondition(attributeLabel, attributeIndex, newConditionLowerBound);
	conditionList.push_back(newLowerBoundCondition);
	LessThanRuleCondition* newUpperBoundCondition = new LessThanRuleCondition(attributeLabel, attributeIndex, newConditionUpperBound);
	conditionList.push_back(newUpperBoundCondition);
	
}

// *** Protected Accessors ***

// ===================================================
// Accessor : double getCurrentDaviesBouldinIndex() const
// Purpose  : Calculate and return Davies-Bouldin
//            index for the current clustering level
// NOTE     : This will be infinity (i.e. the worst
//            possible index value) if any one of the
//            clusters has the same centroid value as
//            another. This is not a problem, since it
//            only means that this clustering level
//            will not be selected, which makes sense
//            if two clusters have the same centre point
// ===================================================

double SOMMap::getCurrentDaviesBouldinIndex() const throw (std::runtime_error) {
	
	// Davies-Boulding index invalid for fewer than 2 clusters (inter-cluster distance = 0.0)
	if (clusterVector.size() < 2) {
		throw std::runtime_error("Attempting to get Davies-Bouldin index of single cluster");
	}
	
	double maxSimilarityTotal = 0.0;
	
	// for each cluster, find maximum similarity measure, and add to return value
	for (unsigned int i = 0; i < clusterVector.size(); ++i) {
		
		double maxSimilarityValue = -DBL_MAX;
		
		// check appropriate similarity matrix row
		for (unsigned int j = 0; ((i > 0) && (j < similarityMeasureMatrix[i - 1].size())); ++j) {
			
			if (similarityMeasureMatrix[i - 1][j] > maxSimilarityValue) {
				maxSimilarityValue = similarityMeasureMatrix[i - 1][j];
			}
			
		}
		
		// check appropriate similarity matrix column
		for (unsigned int j = i; j < similarityMeasureMatrix.size(); ++j) {
			
			if (similarityMeasureMatrix[j][i] > maxSimilarityValue) {
				maxSimilarityValue = similarityMeasureMatrix[j][i];
			}
			
		}
		
		maxSimilarityTotal += maxSimilarityValue;
	}
	
	return (maxSimilarityTotal / ((double) clusterVector.size()));
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const SOMMap&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const SOMMap& map) {
	
	for (unsigned int i = 0; i < map.height; ++i) {
		
		for (unsigned int j = 0; j < map.width; ++j) {
			(map.mapGrid[i][j])->outputLabelled(out, "[", ";", "]");
			
			if (j != (map.width - 1)) {
				out << ";";
			}
		}
		
		if (i != (map.height - 1)) {
			out << std::endl;
		}
		
	}
	
	return out;
	
}
