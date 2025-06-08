#include <stdexcept>
#include <iomanip>
#include <cfloat>
#include <algorithm>

#include "SOMMap.h"
#include "Random.h"
#include "WeightVector.h"
#include "DataFileReader.h"
#include "DataPattern.h"

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
			WeightVector* tempWeightVector = new WeightVector(weights[i][j], weightDimension);
			mapGrid[i][j] = tempWeightVector;
		}
	}
	
}

// ===================================================
// Constructor : SOMMap(const SOMMap&)
// Purpose     : Copy constructor (private to forbid
//               copying)
// ===================================================

SOMMap::SOMMap(const SOMMap&) throw (std::runtime_error) {
	
	throw std::runtime_error("Attempt to copy SOMMap");
	
}

// ===================================================
// Destructor : ~SOMMap()
// Purpose    : De-allocates object resources
// ===================================================

SOMMap::~SOMMap() {
	
	// de-allocate map grid
	for (unsigned int i = 0; i < height; ++i) {
		delete[] mapGrid[i];
	}
	
	delete[] mapGrid;
	
}

// *** Accessors ***

// ===================================================
// Accessor : unsigned int getWidth() const
// Purpose  : Returns width of map
// ===================================================

unsigned int SOMMap::getWidth() const {
	
	return width;
	
}

// ===================================================
// Accessor : unsigned int getHeight() const
// Purpose  : Returns height of map
// ===================================================

unsigned int SOMMap::getHeight() const {
	
	return height;
	
}

// ===================================================
// Accessor : unsigned int getWeightDimension() const
// Purpose  : Returns weight dimension of map
// ===================================================

unsigned int SOMMap::getWeightDimension() const {
	
	return weightDimension;
	
}

// ===================================================
// Accessor : WeightVector getWeightVector(unsigned int, unsigned int) const
// Purpose  : Sets weight at a relevant grid position
// ===================================================

WeightVector SOMMap::getWeightVector(unsigned int row, unsigned int column) const throw (std::invalid_argument) {
	
	// check for valid row dimension
	if ((row < 0) || (row >= height)) {
		throw std::invalid_argument("Invalid row index");
	}
	
	// check for valid column dimension
	if ((column < 0) || (column >= width)) {
		throw std::invalid_argument("Invalid column index");
	}
	
	return *(mapGrid[row][column]);
	
}

// ===================================================
// Accessor : unsigned int getUnlabeledWeights() const
// Purpose  : Calculate and return the number of
//            unlabeled weight vectors on the current
//            map
// ===================================================

unsigned int SOMMap::getUnlabeledWeights() const {
	
	unsigned int unlabeledWeightsCount = 0;
	
	for (unsigned int i = 0; i < getHeight(); ++i) {
		for (unsigned int j = 0; j < getWidth(); ++j) {
			if (mapGrid[i][j]->getLabel() == "") {
				++unlabeledWeightsCount;
			}
		}
	}
	
	return unlabeledWeightsCount;
	
}

// ===================================================
// Accessor : double getUnlabeledWeightPercentage() const
// Purpose  : Calculate and return the percentage of the
//            current map's weight vectors that are unlabeled
// ===================================================

double SOMMap::getUnlabeledWeightPercentage() const {
	
	return (((double) getUnlabeledWeights()) / ((double) width * height)) * 100.0;
	
}

// ===================================================
// Accessor : double getTrainingAccuracy() const
// Purpose  : Return the current training set classification accuracy
// ===================================================

double SOMMap::getTrainingAccuracy() const {
	
	return 100.0 - trainingErrorPercentage;
	
}

// ===================================================
// Accessor : double getTestAccuracy() const
// Purpose  : Return the current test set classification accuracy
// ===================================================

double SOMMap::getTestAccuracy() const {
	
	return 100.0 - testErrorPercentage;
	
}

// ===================================================
// Accessor : double getTrainingError() const
// Purpose  : Return the current training set classification error
// ===================================================

double SOMMap::getTrainingError() const {
	
	return trainingErrorPercentage;
	
}

// ===================================================
// Accessor : double getTrainingMisclassifiedError() const
// Purpose  : Return the current training set
//            misclassification error (patterns
//            incorrectly classified)
// ===================================================

double SOMMap::getTrainingMisclassifiedError() const {
	
	return trainingMisclassificationPercentage;
	
}

// ===================================================
// Accessor : double getTrainingUnclassifiedError() const
// Purpose  : Return the current training set
//            unclassified error (patterns with
//            no classification)
// ===================================================

double SOMMap::getTrainingUnclassifiedError() const {
	
	return trainingUnclassifiedPercentage;
	
}

// ===================================================
// Accessor : double getTestError() const
// Purpose  : Return the current test set classification error
// ===================================================

double SOMMap::getTestError() const {
	
	return testErrorPercentage;
	
}

// ===================================================
// Accessor : double getTrainingMisclassifiedError() const
// Purpose  : Return the current test set
//            misclassification error (patterns
//            incorrectly classified)
// ===================================================

double SOMMap::getTestMisclassifiedError() const {
	
	return testMisclassificationPercentage;
	
}

// ===================================================
// Accessor : double getTrainingUnclassifiedError() const
// Purpose  : Return the current test set
//            unclassified error (patterns with
//            no classification)
// ===================================================

double SOMMap::getTestUnclassifiedError() const {
	
	return testUnclassifiedPercentage;
	
}

// *** Mutators ***

// ===================================================
// Accessor : double classifyTrainingData(DataFileReader&) const
// Purpose  : Calculate and store training error (as a
//            percentage), training misclassification
//            (as a percentage), and training unclassified
//            examples (as a percentage), using provided
//            data set reader
// ===================================================

void SOMMap::classifyTrainingData(DataFileReader& dataReader) {
	
	classify(dataReader, trainingErrorPercentage, trainingMisclassificationPercentage, trainingUnclassifiedPercentage);
	
}

// ===================================================
// Accessor : double classifyTrainingData(DataFileReader&) const
// Purpose  : Calculate and store test error (as a
//            percentage), test misclassification
//            (as a percentage), and test unclassified
//            examples (as a percentage), using provided
//            data set reader
// ===================================================

void SOMMap::classifyTestData(DataFileReader& dataReader) {
	
	classify(dataReader, testErrorPercentage, testMisclassificationPercentage, testUnclassifiedPercentage);
	
}

// *** Utility Functions ***

// ===================================================
// Utility : void classify(DataFileReader&, double&, double&, double&) const
// Purpose : Calculate and return classification errors
//           on provided data set reader, by means of
//           reference parameters
// ===================================================

void SOMMap::classify(DataFileReader& dataReader, double& classificationError, double& incorrectlyClassifiedError, double& unclassifiedError) const {
	
	unsigned int classificationCount = 0;
	unsigned int incorrectClassifiedCount = 0;
	unsigned int unclassifiedCount = 0;
	
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
		
		// check for a match between the current data record and the selected best matching unit
		if (currentRecord.getLabel() != selectedBestMatchingUnit->getLabel()) {
			++classificationCount;
			
			if (selectedBestMatchingUnit->getLabel() == "") {
				++unclassifiedCount;
			} else {
				++incorrectClassifiedCount;
			}
		}
		
	}
	
	classificationError = (((double) classificationCount / (double) dataReader.getRecordCount()) * 100.0);
	incorrectlyClassifiedError = (((double) incorrectClassifiedCount / (double) dataReader.getRecordCount()) * 100.0);
	unclassifiedError = (((double) unclassifiedCount / (double) dataReader.getRecordCount()) * 100.0);
	
}

// ===================================================
// Utility : void optimalKMeansClusterMap()
// Purpose : Initiates clustering process (using
//           K-means approach). Find and return an
//           optimal number of clusters using
//           Davies-Bouldin index
// ===================================================

std::vector<Centroid> SOMMap::optimalKMeansClusterMap() {
	
	std::vector<std::vector<Centroid> > clusterings;
	std::vector<double> clusterCosts;
	double minCost = DBL_MAX;
	std::vector<unsigned int> minIndices;
	
	// find all the possible clusterings from the minimum (2) up to the maximum (the number of map units)
	for (unsigned int i = 2; i <= getWidth() * getHeight(); ++i) {
		std::vector<Centroid> centroids = kMeansCluster(i);
		clusterings.push_back(centroids);
		
		// calculate Davies-Bouldin index for clustering level, and check for minimum value
		double currentDaviesBouldinIndex = calculateDaviesBouldinIndex(centroids);
		clusterCosts.push_back(currentDaviesBouldinIndex);
		
		if (currentDaviesBouldinIndex < minCost) {
			minCost = currentDaviesBouldinIndex;
			minIndices.clear();
			minIndices.push_back(clusterCosts.size() - 1);
		}
		else if (currentDaviesBouldinIndex == minCost) {
			minIndices.push_back(clusterCosts.size() - 1);
		}
	}
	
	// select one of the optimal cluster counts (settle ties arbitrarily)
	unsigned int minIndex = 0;
	
	if (minIndices.size() == 1) {
		minIndex = minIndices[0];
	} else {
		minIndex = minIndices[Random::getInstance()->getNextInt(minIndices.size())];
	}
	
	return clusterings[minIndex];
	
}

// ===================================================
// Utility : void kMeansLabelMap(DataFileReader&)
// Purpose : Initiates cluster labelling process
// ===================================================

void SOMMap::kMeansLabelMap(std::vector<Centroid> centroids, DataFileReader& dataReader) {
	
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
		
		// update appropriate centroid
		std::string label = currentRecord.getLabel();
		
		for (unsigned int j = 0; j < centroids.size(); ++j) {
			if (centroids[j].contains(bestMatchingUnit)) {
				centroids[j].updatePatternHitCount(label);
				break;
			}
		}
		
	}
	
	// label each centroid
	for (unsigned int i = 0; i < centroids.size(); ++i) {
		
		// tie settling is handled when label is reset
		centroids[i].resetLabel();
		
	}
	
	// label individual weight vectors (no tie settling: weight vector member of only 1 centroid)
	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; ++j) {
			
			unsigned int matchIndex = 0;
			
			for (unsigned int k = 0; k < centroids.size(); ++k) {
				if ((centroids[k]).contains(mapGrid[i][j])) {
					matchIndex = k;
					break;
				}
			}
			
			(mapGrid[i][j])->setLabel(centroids[matchIndex].getLabel());
			
		}
	}
	
}

// ===================================================
// Utility : double calculateDaviesBouldinIndex(vector<Centroid>) const throw (runtime_error)
// Purpose : Calculate the Davies-Bouldin index that
//           characterises the supplied list of
//           centroids
// ===================================================

double SOMMap::calculateDaviesBouldinIndex(std::vector<Centroid> centroids) const throw (std::runtime_error) {
	
	// Davies-Boulding index invalid for 2 clusters (inter-cluster distance = 0.0)
	if (centroids.size() < 2) {
		throw std::runtime_error("Attempting to get Davies-Boulding of single cluster");
	}
	
	double totalSimilarityMeasure = 0.0;
	
	// add a similarity measure for each centroid
	for (unsigned int i = 0; i < centroids.size(); ++i) {
		
		// find maximum similarity measure between i and j where i != j
		double maxSimilarity = -DBL_MAX;
		
		for (unsigned int j = 0; j < centroids.size(); ++j) {
			if (i != j) {
				double intraI = centroids[i].getIntraClusterSimilarity();
				double intraJ = centroids[j].getIntraClusterSimilarity();
				
				double inter = centroids[i].getInterClusterSimilarity(centroids[j]);
				double currentSimilarity = (intraI + intraJ) / inter;
				
				if (currentSimilarity > maxSimilarity) {
					maxSimilarity = currentSimilarity;
				}
			}
		}
		
		totalSimilarityMeasure += maxSimilarity;
		
	}
	
	return totalSimilarityMeasure / ((double) centroids.size());
	
}

// *** Protected Accessors ***

// ===================================================
// Accessor : vector<Centroid> kMeansCluster(unsigned int) const
// Purpose  : Calculate and return centroids generated
//            by K-means clustering for user-specified
//            number of clusters
// ===================================================

std::vector<Centroid> SOMMap::kMeansCluster(unsigned int numClusters) const {
	
	// copy weight vectors into a unifying vector (so that added vectors may be removed)
	std::vector<WeightVector*> mapConstituents;
	
	for (unsigned int i = 0; i < getHeight(); ++i) {
		for (unsigned int j = 0; j < getWidth(); ++j) {
			mapConstituents.push_back(mapGrid[i][j]);
		}
	}
	
	// randomly choose k initial centroids
	std::vector<Centroid> centroids;
	
	for (unsigned int i = 0; i < numClusters; ++i) {
		
		// randomly select a unique weight vector from the map
		unsigned long int randomWeightVectorIndex = Random::getInstance()->getNextInt(mapConstituents.size());
		
		// create centroid for selected weight vector
		Centroid newCentroid(mapConstituents[randomWeightVectorIndex]);
		centroids.push_back(newCentroid);
		
		// remove selected weight vector (to avoid re-selection)
		std::vector<WeightVector*>::iterator tempIterator = mapConstituents.begin();
		
		for (unsigned int j = 0; j < randomWeightVectorIndex; ++j) {
			tempIterator++;
		}
		
		mapConstituents.erase(tempIterator);
		
	}
	
	// iterate randomly through all remaining training vectors, using each to update the closest centroid
	while (mapConstituents.size() > 0) {
		
		// randomly select a weight vector
		unsigned int randomWeightVectorIndex = Random::getInstance()->getNextInt(mapConstituents.size());
		
		// isolate nearest centroid
		double minDistance = DBL_MAX;
		std::vector<unsigned int> minCentroidIndices;
		
		for (unsigned int i = 0; i < centroids.size(); ++i) {
			if (mapConstituents[randomWeightVectorIndex]->getEuclideanDistance(centroids[i].getComponents()) < minDistance) {
				minDistance = mapConstituents[randomWeightVectorIndex]->getEuclideanDistance(centroids[i].getComponents());
				minCentroidIndices.clear();
				minCentroidIndices.push_back(i);
			}
			else if (mapConstituents[randomWeightVectorIndex]->getEuclideanDistance(centroids[i].getComponents()) == minDistance) {
				minCentroidIndices.push_back(i);
			}
		}
		
		// select one of the optimal centroids (settle ties arbitrarily)
		unsigned int minCentroidIndex = 0;
		
		if (minCentroidIndices.size() == 1) {
			minCentroidIndex = minCentroidIndices[0];
		} else {
			minCentroidIndex = minCentroidIndices[Random::getInstance()->getNextInt(minCentroidIndices.size())];
		}
		
		// update nearest centroid using randomly selected weight vector
		centroids[minCentroidIndex].updateCentroid(mapConstituents[randomWeightVectorIndex]);
		
		// remove randomly selected weight vector from considered map constituents
		std::vector<WeightVector*>::iterator tempIterator = mapConstituents.begin();
		
		for (unsigned int j = 0; j < randomWeightVectorIndex; ++j) {
			tempIterator++;
		}
		
		mapConstituents.erase(tempIterator);
	}
	
	// assign each weight vector to its nearest centroid
	for (unsigned int i = 0; i < getHeight(); ++i) {
		for (unsigned int j = 0; j < getWidth(); ++j) {
			
			// isolate nearest centroid
			double minDistance = DBL_MAX;
			std::vector<unsigned int> minCentroidIndices;
			
			for (unsigned int k = 0; k < centroids.size(); ++k) {
				
				if (mapGrid[i][j]->getEuclideanDistance(centroids[k].getComponents()) < minDistance) {
					minDistance = mapGrid[i][j]->getEuclideanDistance(centroids[k].getComponents());
					minCentroidIndices.clear();
					minCentroidIndices.push_back(k);
				}
				else if (mapGrid[i][j]->getEuclideanDistance(centroids[k].getComponents()) == minDistance) {
					minCentroidIndices.push_back(k);
				}
				
			}
			
			// select one of the optimal centroids (settle ties arbitrarily)
			unsigned int minCentroidIndex = 0;
			
			if (minCentroidIndices.size() == 1) {
				minCentroidIndex = minCentroidIndices[0];
			} else {
				minCentroidIndex = minCentroidIndices[Random::getInstance()->getNextInt(minCentroidIndices.size())];
			}
			
			centroids[minCentroidIndex].addWeightVector(mapGrid[i][j]);
			
		}
	}
	
	return centroids;
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const SOMMap&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const SOMMap& map) {
	
	for (unsigned int i = 0; i < map.height; ++i) {
		
		for (unsigned int j = 0; j < map.width; ++j) {
			(map.mapGrid[i][j])->output(out, "[", ";", "]");
			
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
