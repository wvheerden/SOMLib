#include <stdexcept>
#include <iomanip>
#include <cfloat>

#include "SOMMap.h"
#include "Random.h"
#include "WeightVector.h"
#include "DataFileReader.h"
#include "DataPattern.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : SOMMap(int, int, int, double***)
// Purpose     : Constructs map with given map file
// ===================================================

SOMMap::SOMMap(unsigned int _width, unsigned int _height, unsigned int _weightDimension, double*** weights) :
width(_width), height(_height), weightDimension(_weightDimension), mapGrid(new WeightVector**[_height]), trainingMisclassificationPercentage(0.0), testMisclassificationPercentage(0.0) {
	
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
		
		// select one of the best maching units (settle ties arbitrarily)
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
				//std::cout << "Unclassified" << std::endl;
			} else {
				++incorrectClassifiedCount;
				//std::cout << "Incorrectly classified" << std::endl;
			}
		}
		
	}
	
	classificationError = (((double) classificationCount / (double) dataReader.getRecordCount()) * 100.0);
	incorrectlyClassifiedError = (((double) incorrectClassifiedCount / (double) dataReader.getRecordCount()) * 100.0);
	unclassifiedError = (((double) unclassifiedCount / (double) dataReader.getRecordCount()) * 100.0);
	
}

// ===================================================
// Utility : void hybridNeuronCentricWeightCentricLabelMap(DataFileReader&)
// Purpose : Initiates neuron labelling process using
//           the neuron centric method
// ===================================================

void SOMMap::hybridNeuronCentricWeightCentricLabelMap(DataFileReader& dataReader) {
	
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
		
		std::string label = currentRecord.getLabel();
		bestMatchingUnit->updatePatternHitCount(label);
		
	}
	
	// label individual weight vectors
	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; ++j) {
			
			// select most common label for the current weight vector (if no hits have been registered for the weight vector, leave the label empty)
			std::vector<HitCount> currentWeightVectorHitCounts = mapGrid[i][j]->getHitCounts();
			
			if (currentWeightVectorHitCounts.size() > 0) {
				
				unsigned int maxHits = 0;
				std::vector<HitCount> maxHitCounts;
				
				for (unsigned int k = 0; k < currentWeightVectorHitCounts.size(); ++k) {
					
					if (currentWeightVectorHitCounts[k].getCount() > maxHits) {
						maxHits = currentWeightVectorHitCounts[k].getCount();
						maxHitCounts.clear();
						maxHitCounts.push_back(currentWeightVectorHitCounts[k]);
					} else if (currentWeightVectorHitCounts[k].getCount() == maxHits) {
						maxHitCounts.push_back(currentWeightVectorHitCounts[k]);
					}
					
				}
				
				// select one of the maximum hit counts (settle ties arbitrarily)
				if (maxHitCounts.size() == 1) {
					(mapGrid[i][j])->setLabel(maxHitCounts[0].getLabel());
				} else {
					(mapGrid[i][j])->setLabel(maxHitCounts[Random::getInstance()->getNextInt(maxHitCounts.size())].getLabel());
				}
				
			}
			
		}
	}
   
   // label unlabelled neurons using weight-centric neuron labelling
   for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; ++j) {
         if (mapGrid[i][j]->getLabel() == "") {
            
            WeightVector* currentWeightVector = mapGrid[i][j];
            double minDistance = DBL_MAX;
            std::vector<DataPattern> bestMatchingRecords;
            
            // compare currently considered weight vector to all possible records
            // no duplicate tracking - records may (and probably will) map to multiple weight vectors
            for (unsigned int k = 0; k < dataReader.getRecordCount(); ++k) {
               
               // find best matching record according to Euclidean distance between weight vector and all possible records
               DataPattern currentRecord = dataReader.getRecord(k);
               double tempDistance = currentWeightVector->getEuclideanDistance(currentRecord);
               
               if (tempDistance < minDistance) {
                  minDistance = tempDistance;
                  bestMatchingRecords.clear();
                  bestMatchingRecords.push_back(currentRecord);
               } else if (tempDistance == minDistance) {
                  bestMatchingRecords.push_back(currentRecord);
               }
               
            }
            
            // select one of the best matching patterns (settle ties arbitrarily)
            DataPattern* bestMatchingRecord = NULL;
            
            if (bestMatchingRecords.size() == 1) {
               bestMatchingRecord = &(bestMatchingRecords[0]);
            } else {
               bestMatchingRecord = &(bestMatchingRecords[Random::getInstance()->getNextInt(bestMatchingRecords.size())]);
            }
            
            // set label of currently considered weight vector to label of best matching record
            std::string label = bestMatchingRecord->getLabel();
            currentWeightVector->setLabel(label);
            
         }
      }
   }
	
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

/*

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

*/
