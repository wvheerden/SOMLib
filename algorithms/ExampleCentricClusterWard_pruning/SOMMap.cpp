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

// *** Constructors and Destructors ***

// ===================================================
// Constructor : SOMMap(int, int, int, double***)
// Purpose     : Constructs map with given map file
// ===================================================

SOMMap::SOMMap(unsigned int _width, unsigned int _height, unsigned int _weightDimension, double*** weights, double overallDistanceStandardDeviationFraction) :
width(_width), height(_height), weightDimension(_weightDimension), mapGrid(new WeightVector**[_height]), prunedNeuronCount(0) {
	
	// initialise map grid
	for (unsigned int i = 0; i < height; ++i) {
		mapGrid[i] = new WeightVector*[width];
		
		for (unsigned int j = 0; j < width; ++j) {
			// add weight vector to grid
			WeightVector* tempWeightVector = new WeightVector((width * height), weights[i][j], weightDimension);
			mapGrid[i][j] = tempWeightVector;
		}
	}
	
	markInterpolatingUnits(overallDistanceStandardDeviationFraction);
	
	// initialise clusters
	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; ++j) {
			// get weight vector from grid
			WeightVector* tempWeightVector = mapGrid[i][j];
			
			if (!(mapGrid[i][j]->isToBePruned())) {
				
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
							if (!(mapGrid[k][l]->isToBePruned())) {


CHECK


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
					}
					
					distanceMatrix.push_back(tempDistanceVector);
					similarityMeasureMatrix.push_back(tempSimilarityMeasureVector);
				}
			}
		}
	}
	
std::cout << std::endl << std::endl;
outputDistanceMatrix(std::cout);
std::cout << std::endl << std::endl;

	// calculate and store initial cluster cost
	clusterCosts.push_back(getCurrentDaviesBouldinIndex());
	
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
// Accessor : WeightVector getWeightVector(int, int) const
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
// Accessor : unsigned int getOptimalClusterCount() const
// Purpose  : Return current number of optimal clusters
// ===================================================

unsigned int SOMMap::getOptimalClusterCount() const {
	
	return optimalClusters.size();
	
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

// ===================================================
// Accessor : double getPrunedNeuronPercentage() const
// Purpose  : Return the percentage of neurons that
//            were pruned
// ===================================================

double SOMMap::getPrunedNeuronPercentage() const {
	
	return ((((double) prunedNeuronCount) / ((double) width * height)) * 100.0);
	
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
				
				// only include this neuron in BMU search if it is not pruned
				if (!(mapGrid[j][k]->isToBePruned())) {
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
		}
		
		// select one of the best maching units (settle ties arbitrarily)
		if (bestMatchingUnits.size() != 0) {
			WeightVector* selectedBestMatchingUnit = NULL;
			
			if (bestMatchingUnits.size() == 1) {
				selectedBestMatchingUnit = bestMatchingUnits[0];
			} else {
				selectedBestMatchingUnit = bestMatchingUnits[Random::getInstance()->getNextInt(bestMatchingUnits.size())];
			}
			
			// check for a match between the current data record and the selected best matching unit
			if (currentRecord.getLabel() != selectedBestMatchingUnit->getLabel()) {
				++classificationCount;
				
				// unclassified because pattern is mapped to an unlabeled neuron
				if (selectedBestMatchingUnit->getLabel() == "") {
					++unclassifiedCount;
				// incorrectly classified because pattern is mapped to a neuron with a label that doesn't match
				} else {
					++incorrectClassifiedCount;
				}
			}
		// unclassified because pattern didn't map to any neuron (only if all neurons have been pruned)
		} else {
			++classificationCount;
			++unclassifiedCount;
		}
		
	}
	
	classificationError = (((double) classificationCount / (double) dataReader.getRecordCount()) * 100.0);
	incorrectlyClassifiedError = (((double) incorrectClassifiedCount / (double) dataReader.getRecordCount()) * 100.0);
	unclassifiedError = (((double) unclassifiedCount / (double) dataReader.getRecordCount()) * 100.0);
	
}

// ===================================================
// Utility : void markInterpolatingUnits(double)
// Purpose : Mark interpolating units on map using
//           a provided fraction of the standard
//           deviation from the overall mean of
//           inter-neighbour distances across the map
// ===================================================

void SOMMap::markInterpolatingUnits(double overallDistanceStandardDeviationFraction) {
	
	double overallAverageDistance = 0.0;
	double overallDistanceStandardDeviation = 0.0;
	
	// compute average distance to neighbours for each neuron
	for (unsigned int j = 0; j < height; ++j) {
		for (unsigned int k = 0; k < width; ++k) {
			
			double averageValue = 0.0;
			
			// on first row, first column (top left)
			if ((j == 0) && (k == 0)) {
				averageValue += mapGrid[0][0]->getEuclideanDistance(*(mapGrid[0][1]));
				averageValue += mapGrid[0][0]->getEuclideanDistance(*(mapGrid[1][0]));
				averageValue /= 2.0;
				mapGrid[0][0]->setAverageNeighbourDistance(averageValue);
			}
			
			// on first row, last column (top right)
			else if ((j == 0) && (k == (width - 1))) {
				averageValue += mapGrid[0][width - 1]->getEuclideanDistance(*(mapGrid[0][width - 2]));
				averageValue += mapGrid[0][width - 1]->getEuclideanDistance(*(mapGrid[1][width - 1]));
				averageValue += mapGrid[0][width - 1]->getEuclideanDistance(*(mapGrid[1][width - 2]));
				averageValue /= 3.0;
				mapGrid[0][width - 1]->setAverageNeighbourDistance(averageValue);
			}
			
			// on first row, middle column (top middle)
			else if ((j == 0) && (k > 0) && (k < (width - 1))) {
				averageValue += mapGrid[0][k]->getEuclideanDistance(*(mapGrid[0][k - 1]));
				averageValue += mapGrid[0][k]->getEuclideanDistance(*(mapGrid[1][k - 1]));
				averageValue += mapGrid[0][k]->getEuclideanDistance(*(mapGrid[1][k]));
				averageValue += mapGrid[0][k]->getEuclideanDistance(*(mapGrid[0][k + 1]));
				averageValue /= 4.0;
				mapGrid[0][k]->setAverageNeighbourDistance(averageValue);
			}
			
			// any row after the first row
			else {
				// even rows
				if ((j + 1) % 2 == 0) {
				
					// on last row, first column (bottom left)
					if ((j == (height - 1)) && (k == 0)) {
						averageValue += mapGrid[height - 1][0]->getEuclideanDistance(*(mapGrid[height - 2][0]));
						averageValue += mapGrid[height - 1][0]->getEuclideanDistance(*(mapGrid[height - 2][1]));
						averageValue += mapGrid[height - 1][0]->getEuclideanDistance(*(mapGrid[height - 1][1]));
						averageValue /= 3.0;
						mapGrid[height - 1][0]->setAverageNeighbourDistance(averageValue);
					}
				
					// on last row, last column (bottom right)
					else if ((j == (height - 1)) && (k == (width - 1))) {
						averageValue += mapGrid[height - 1][width - 1]->getEuclideanDistance(*(mapGrid[height - 1][width - 2]));
						averageValue += mapGrid[height - 1][width - 1]->getEuclideanDistance(*(mapGrid[height - 2][width - 1]));
						averageValue /= 2.0;
						mapGrid[height - 1][width - 1]->setAverageNeighbourDistance(averageValue);
					}
				
					// on last row, middle column (bottom middle)
					else if ((j == (height - 1)) && (k > 0) && (k < (width - 1))) {
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 1][k - 1]));
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 2][k]));
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 2][k + 1]));
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 1][k + 1]));
						averageValue /= 4.0;
						mapGrid[height - 1][k]->setAverageNeighbourDistance(averageValue);
					}
				
					// on middle row, first column (left middle)
					else if ((j > 0) && (j < (height - 1)) && (k == 0)) {
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j - 1][0]));
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j - 1][1]));
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j][1]));
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j + 1][1]));
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j + 1][0]));
						averageValue /= 5.0;
						mapGrid[j][0]->setAverageNeighbourDistance(averageValue);
					}
				
					// on middle row, last column (right middle)
					else if ((j > 0) && (j < (height - 1)) && (k == (width - 1))) {
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j - 1][width - 1]));
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j][width - 2]));
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j + 1][width - 1]));
						averageValue /= 3.0;
						mapGrid[j][width - 1]->setAverageNeighbourDistance(averageValue);
					}
				
					// middle row, middle column (middle)
					else if ((j > 0) && (j < (height - 1)) && (k > 0) && (k < (width - 1))) {
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j][k - 1]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j + 1][k]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j + 1][k + 1]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j][k + 1]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j - 1][k + 1]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j - 1][k]));
						averageValue /= 6.0;
						mapGrid[j][k]->setAverageNeighbourDistance(averageValue);
					}
				
				// odd rows
				} else {
				
					// on last row, first column (bottom left)
					if ((j == (height - 1)) && (k == 0)) {
						averageValue += mapGrid[height - 1][0]->getEuclideanDistance(*(mapGrid[height - 2][0]));
						averageValue += mapGrid[height - 1][0]->getEuclideanDistance(*(mapGrid[height - 1][1]));
						averageValue /= 2.0;
						mapGrid[height - 1][0]->setAverageNeighbourDistance(averageValue);
					}
				
					// on last row, last column (bottom right)
					else if ((j == (height - 1)) && (k == (width - 1))) {
						averageValue += mapGrid[height - 1][width - 1]->getEuclideanDistance(*(mapGrid[height - 1][width - 2]));
						averageValue += mapGrid[height - 1][width - 1]->getEuclideanDistance(*(mapGrid[height - 2][width - 2]));
						averageValue += mapGrid[height - 1][width - 1]->getEuclideanDistance(*(mapGrid[height - 2][width - 1]));
						averageValue /= 3.0;
						mapGrid[height - 1][width - 1]->setAverageNeighbourDistance(averageValue);
					}
				
					// on last row, middle column (bottom middle)
					else if ((j == (height - 1)) && (k > 0) && (k < (width - 1))) {
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 1][k - 1]));
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 2][k - 1]));
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 2][k]));
						averageValue += mapGrid[height - 1][k]->getEuclideanDistance(*(mapGrid[height - 1][k + 1]));
						averageValue /= 4.0;
						mapGrid[height - 1][k]->setAverageNeighbourDistance(averageValue);
					}
				
					// on middle row, first column (left middle)
					else if ((j > 0) && (j < (height - 1)) && (k == 0)) {
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j - 1][0]));
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j][1]));
						averageValue += mapGrid[j][0]->getEuclideanDistance(*(mapGrid[j + 1][0]));
						averageValue /= 3.0;
						mapGrid[j][0]->setAverageNeighbourDistance(averageValue);
					}
				
					// on middle row, last column (right middle)
					else if ((j > 0) && (j < (height - 1)) && (k == (width - 1))) {
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j - 1][width - 1]));
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j - 1][width - 2]));
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j][width - 2]));
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j + 1][width - 2]));
						averageValue += mapGrid[j][width - 1]->getEuclideanDistance(*(mapGrid[j + 1][width - 1]));
						averageValue /= 5.0;
						mapGrid[j][width - 1]->setAverageNeighbourDistance(averageValue);
					}
				
					// middle row, middle column (middle)
					else if ((j > 0) && (j < (height - 1)) && (k > 0) && (k < (width - 1))) {
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j][k - 1]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j + 1][k - 1]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j + 1][k]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j][k + 1]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j - 1][k]));
						averageValue += mapGrid[j][k]->getEuclideanDistance(*(mapGrid[j - 1][k - 1]));
						averageValue /= 6.0;
						mapGrid[j][k]->setAverageNeighbourDistance(averageValue);
					}
				}
			}
			
			// add current neuron's average distance to neighbours to the overall mean total
			overallAverageDistance += averageValue;
		}
	}
	
	// compute overall distance mean
	overallAverageDistance /= (width * height);
	
	// compute distance standard deviation (population standard deviation, because we have all weight vectors, not just a sample)
	for (unsigned int j = 0; j < height; ++j) {
		for (unsigned int k = 0; k < width; ++k) {
			overallDistanceStandardDeviation += pow(mapGrid[j][k]->getAverageNeighbourDistance() - overallAverageDistance, 2.0);
		}
	}
	
	overallDistanceStandardDeviation /= (width * height);
	overallDistanceStandardDeviation = sqrt(overallDistanceStandardDeviation);
	
	// check interpolating unit status for each neuron on the map
	for (unsigned int j = 0; j < height; ++j) {
		for (unsigned int k = 0; k < width; ++k) {
			// compute distance of the current weight vector's mean from neighbours from the overall mean across the entire map
			double distanceFromMean = mapGrid[j][k]->getAverageNeighbourDistance() - overallAverageDistance;
			
			// neuron is an interpolating unit if it is further than a fraction of a standard deviation from the overall mean
			if (distanceFromMean > (overallDistanceStandardDeviationFraction * overallDistanceStandardDeviation)) {
				++prunedNeuronCount;
				mapGrid[j][k]->markForPruning();
			}
		}

	}
/*
std::cout << std::endl;
for (unsigned int j = 0; j < height; ++j) {
	for (unsigned int k = 0; k < width; ++k) {
		std::cout << "[" << mapGrid[j][k]->getAverageNeighbourDistance() << "]";
	}
	std::cout << std::endl;
}

std::cout << std::endl << std::endl;
for (unsigned int j = 0; j < height; ++j) {
	for (unsigned int k = 0; k < width; ++k) {
		if (mapGrid[j][k]->isToBePruned()) {
			std::cout << "[ ]";
		} else {
			std::cout << "[X]";
		}
	}
	std::cout << std::endl;
}
*/

}

// ===================================================
// Utility : void clusterMap()
// Purpose : Initiates clustering process
// ===================================================

void SOMMap::clusterMap() {
	
	while (clusterVector.size() > 2) {
		
//std::cout << "here1" << std::endl;
		// locate closest set of cluster pairs to merge (mergeClusterIndex1 is always smaller than mergeClusterIndex2)
		double minDistance = DBL_MAX;
		std::vector<unsigned int> mergeCluster1Indices;
		std::vector<unsigned int> mergeCluster2Indices;
		
		for (unsigned int i = 0; i < distanceMatrix.size(); ++i) {
			for (unsigned int j = 0; j < distanceMatrix[i].size(); ++j) {
				if (distanceMatrix[i][j] < minDistance) {
					minDistance = distanceMatrix[i][j];
std::cout << "Pushing " << j << " and " << i+1 << std::endl;
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
		
//std::cout << "here2" << std::endl;
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
		
//std::cout << "here3" << std::endl;
		// store constituent clusters and create new aggregate cluster
		MapCluster* constituentCluster1 = clusterVector[mergeCluster1Index];
		MapCluster* constituentCluster2 = clusterVector[mergeCluster2Index];
//std::cout << std::endl << "Before creating aggregare cluster" << std::endl;

/*
for (unsigned int i = 0; i < clusterVector.size(); ++i) {
	std::cout << clusterVector[i] << std::endl;
}
*/

//std::cout << "Merge index 1: " << mergeCluster1Index << std::endl;
//std::cout << "Merge clust 1: " << constituentCluster1 << std::endl;
//std::cout << "Merge index 2: " << mergeCluster2Index << std::endl;
//std::cout << "Merge clust 1: " << constituentCluster2 << std::endl;
		AggregateMapCluster* newCluster = new AggregateMapCluster((clusterVector.size() - 1), *constituentCluster1, *constituentCluster2);
		
//std::cout << "here4" << std::endl;
		// delete old clusters and add new cluster to cluster vector at position mergeCluster1Index
		clusterVector.erase(clusterVector.begin() + mergeCluster2Index);
		clusterVector.erase(clusterVector.begin() + mergeCluster1Index);
		clusterVector.insert(clusterVector.begin() + mergeCluster1Index, newCluster);
		
//std::cout << "here5" << std::endl;
		// update distance matrix and similarity measure matrix rows at mergeCluster1Index
		for (unsigned int i = 0; ((mergeCluster1Index > 0) && (i < distanceMatrix[mergeCluster1Index - 1].size())); ++i) {
			
			if ((distanceMatrix[mergeCluster1Index - 1][i] != DBL_MAX) || (distanceMatrix[mergeCluster2Index - 1][i] != DBL_MAX)) {
				distanceMatrix[mergeCluster1Index - 1][i] = newCluster->calculateWardDistance(*(clusterVector[i]));
			} else {
				distanceMatrix[mergeCluster1Index - 1][i] = DBL_MAX;
			}
			
			similarityMeasureMatrix[mergeCluster1Index - 1][i] = newCluster->calculateSimilarityMeasure(*(clusterVector[i]));
		}
		
//std::cout << "here6" << std::endl;
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
		
//std::cout << "here7" << std::endl;
		// delete distance matrix and similarity measure matrix rows at mergeCluster2Index
		distanceMatrix.erase(distanceMatrix.begin() + (mergeCluster2Index - 1));
		similarityMeasureMatrix.erase(similarityMeasureMatrix.begin() + (mergeCluster2Index - 1));
		
//std::cout << "here8" << std::endl;
		// delete distance matrix and similarity measure matrix columns at mergeCluster2Index
		for (unsigned int i = (mergeCluster2Index - 1); i < distanceMatrix.size(); ++i) {
			distanceMatrix[i].erase(distanceMatrix[i].begin() + mergeCluster2Index);
			similarityMeasureMatrix[i].erase(similarityMeasureMatrix[i].begin() + mergeCluster2Index);
		}
		
//std::cout << "here9" << std::endl;
		// calculate and store cluster cost
		clusterCosts.insert(clusterCosts.begin(), getCurrentDaviesBouldinIndex());
		
//std::cout << "here10" << std::endl;
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
				
				// only include this neuron in BMU search if it is not pruned
				if (!(mapGrid[j][k]->isToBePruned())) {
					
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
		}
		
		// select one of the best matching units (settle ties arbitrarily)
		if (bestMatchingUnits.size() != 0) {
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
	
	// locate optimal set of clusters (for minimum cost), and associated labels
	clusterVector[0]->getNClusters(optimalClusterCount, optimalClusters, optimalClusterLabels);
	
	// label individual weight vectors (no tie settling: weight vector member of only 1 cluster)
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

// *** Protected Accessors ***

// ===================================================
// Accessor : double getCurrentDaviesBouldinIndex() const
// Purpose  : Calculate and return Davies Bouldin
//            index for the current clustering level
// ===================================================

double SOMMap::getCurrentDaviesBouldinIndex() const throw (std::runtime_error) {
	
	// Davies-Boulding index invalid for 2 clusters (inter-cluster distance = 0.0)
	if (clusterVector.size() < 2) {
		throw std::runtime_error("Attempting to get Davies-Boulding of single cluster");
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



// *** Utility Output Functions ***

// ===================================================
// Utility : ostream& outputDistanceMatrix(ostream&) const
// Purpose : Prints current distance matrix to ostream
// ===================================================

std::ostream& SOMMap::outputDistanceMatrix(std::ostream& out) const {
	
	std::vector<std::vector<double> >::const_iterator iter1;
	unsigned int i;
	
	out << std::right << std::setw(17) << "0:" << std::endl;
	
	for (iter1 = distanceMatrix.begin(), i = 1; iter1 != distanceMatrix.end(); iter1++, ++i) {
		
		std::vector<double> tempVector = *iter1;
		std::vector<double>::iterator iter2;
		
		out << std::setw(4) << std::setfill(' ') << i << ": ";
		
		for (iter2 = tempVector.begin(); iter2 != tempVector.end(); ++iter2) {
			if (*iter2 != DBL_MAX) {
				out << std::left << std::setprecision(15) << std::setw(22) << *iter2;
			} else {
				out << std::right << std::setw(15) << "infinity" << std::setw(7) << "";
			}
		}
		
		if (i != distanceMatrix.size()) {
			out << std::right << std::setw(11) << i << ":" << std::endl;
		}
		
	}
	
	return out;
	
}

// ===================================================
// Utility : ostream& outputSimilarityMeasureMatrix(ostream&) const
// Purpose : Prints current similarity measure matrix
//           to ostream
// ===================================================

std::ostream& SOMMap::outputSimilarityMeasureMatrix(std::ostream& out) const {
	
	std::vector<std::vector<double> >::const_iterator iter1;
	unsigned int i;
	
	out << std::right << std::setw(17) << "0:" << std::endl;
	
	for (iter1 = similarityMeasureMatrix.begin(), i = 1; iter1 != similarityMeasureMatrix.end(); iter1++, ++i) {
		
		std::vector<double> tempVector = *iter1;
		std::vector<double>::iterator iter2;
		
		out << std::setw(4) << std::setfill(' ') << i << ": ";
		
		for (iter2 = tempVector.begin(); iter2 != tempVector.end(); ++iter2) {
			out << std::left << std::setprecision(15) << std::setw(22) << *iter2;
		}
		
		if (i != similarityMeasureMatrix.size()) {
			out << std::right << std::setw(11) << i << ":" << std::endl;
		}
		
	}
	
	return out;
	
}


