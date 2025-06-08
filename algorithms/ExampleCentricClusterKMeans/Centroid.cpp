#include <cmath>

#include "Centroid.h"
#include "Random.h"

// *** Constructor ***

// ===================================================
// Constructor : Centroid(WeightVector&)
// Purpose     : Constructs centroid with given weight
//               vector as the initial constituent
// ===================================================

Centroid::Centroid(WeightVector* initialConstituent) :
centroidComponents(initialConstituent->getCentroid()), weightVectorCount(0), label("") {
	
	;
	
}

// *** Accessors ***

// ===================================================
// Accessor : vector<double> getComponents() const
// Purpose  : Returns a vector of double values
//            representing the components making up
//            this centroid
// ===================================================

std::vector<double> Centroid::getComponents() const {
	
	std::vector<double> returnVector;
	
	// copy centroid values to returning vector
	for (unsigned int i = 0; i < centroidComponents.size(); ++i) {
		returnVector.push_back(centroidComponents[i]);
	}
	
	return returnVector;
	
}

// ===================================================
// Accessor : double getIntraClusterSimilarity() const
// Purpose  : Return the intra-cluster similarity
//            measure for this centroid
// ===================================================

double Centroid::getIntraClusterSimilarity() const {
	
	if (weightVectorConstituents.size() <= 1) {
		return 5000;
	}
	
	double returnMeasure = 0.0;
	
	for (unsigned int i = 0; i < weightVectorConstituents.size(); ++i) {
		returnMeasure += weightVectorConstituents[i]->getEuclideanDistance(centroidComponents);
	}
	
	return returnMeasure / ((double) weightVectorConstituents.size());
	
}

// ===================================================
// Accessor : double getInterClusterSimilarity(Centroid&) const
// Purpose  : Return the inter-cluster similarity
//            measure between this centroid and the
//            supplied one (i.e. the Euclidean
//            distance between the respective
//            centroids)
// ===================================================

double Centroid::getInterClusterSimilarity(Centroid& otherCentroid) const {
	
	double returnMeasure = 0.0;
	
	for (unsigned int i = 0; i < centroidComponents.size(); ++i) {
		returnMeasure += pow(centroidComponents[i] - otherCentroid.centroidComponents[i], 2.0);
	}
	
	return sqrt(returnMeasure);
	
}

// ===================================================
// Accessor : bool contains(WeightVector*) const
// Purpose  : Return true if the supplied weight
//            vector is contained by this centroid,
//            false otherwise
// ===================================================

bool Centroid::contains(WeightVector* comparisonWeightVector) const {
	
	for (unsigned int i = 0; i < weightVectorConstituents.size(); ++i) {
		if (weightVectorConstituents[i] == comparisonWeightVector) {
			return true;
		}
	}
	
	return false;
	
}

// ===================================================
// Accessor : string getLabel() const
// Purpose  : Return the appropriate label for this
//            centroid (i.e. the label that has the
//            majority of hits)
// ===================================================

std::string Centroid::getLabel() const {
	
	return label;
	
}

// *** Mutators ***

// ===================================================
// Mutator : void addWeightVector(WeightVector*)
// Purpose : Add supplied weight vector to this
//           centroid, updating weight vector list
//           accordingly
// ===================================================

void Centroid::addWeightVector(WeightVector* newVector) {
	
	weightVectorConstituents.push_back(newVector);
	
}

// ===================================================
// Mutator : void resetLabel()
// Purpose : Resets the label of this centroid, based
//           on its member weight vectors
// ===================================================

void Centroid::resetLabel() {
	
	// if there are no hits for this centroid, don't reset the label (i.e. leave it as an empty string)
	if (hitCounts.size() > 0) {
		
		// find set of maximal hit count indices
		unsigned int maxCount = 0;
		std::vector<unsigned int> maxIndices;
		
		for (unsigned int i = 0; i < hitCounts.size(); ++i) {
			if (hitCounts[i].getCount() > maxCount) {
				maxCount = hitCounts[i].getCount();
				maxIndices.clear();
				maxIndices.push_back(i);
			}
			else if (hitCounts[i].getCount() == maxCount) {
				maxIndices.push_back(i);
			}
		}
		
		// settle ties arbitrarily
		unsigned int maxIndex;
		
		if (maxIndices.size() == 1) {
			maxIndex = maxIndices[0];
		} else {
			maxIndex = maxIndices[Random::getInstance()->getNextInt(maxIndices.size())];
		}
		
		// set appropriate label for this centroid
		label = hitCounts[maxIndex].getLabel();
		
	}
	
}

// ===================================================
// Mutator : void updateCentroid(WeightVector*)
// Purpose : update centroid, using supplied weight
//           vector
// ===================================================

void Centroid::updateCentroid(WeightVector* newVector) {
	
	++weightVectorCount;
	
	// recompute centroid
	std::vector<double> newVectorComponents = newVector->getCentroid();
	
	for (unsigned int i = 0; i < newVectorComponents.size(); ++i) {
		centroidComponents[i] = ((weightVectorCount * centroidComponents[i]) + newVectorComponents[i]) / (weightVectorCount + 1);
	}
	
}

// ===================================================
// Mutator : void updatePatternHitCount(string)
// Purpose : Update the pattern hitcounts
//           appropriately for this centroid
// ===================================================

void Centroid::updatePatternHitCount(std::string patternLabel) {
	
	// search for matching pattern label
	bool found = false;
	unsigned int foundIndex = 0;
	
	for (unsigned int i = 0; i < hitCounts.size(); ++i) {
		
		if (patternLabel == hitCounts[i].getLabel()) {
			found = true;
			foundIndex = i;
			break;
		}
		
	}
	
	// handle appropriately
	if (found) {
		(hitCounts[foundIndex]).incrementCount();
	} else {
		HitCount newCount(patternLabel);
		hitCounts.push_back(newCount);
	}
	
}

// ===================================================
// Mutator : ostream& output(ostream& out, const char*, const char*, const char*) const
// Purpose : Output Centroid object
// ===================================================

std::ostream& Centroid::output(std::ostream& out, const char* leader, const char* separator, const char* terminator) const {
	
	out << leader;
	
	for (unsigned int i = 0; i < centroidComponents.size(); ++i) {
		
		out << centroidComponents[i];
		out.flush();
		
		if (i != (centroidComponents.size() - 1)) {
			out << separator;
		}
		
	}
	
	out << terminator;
	
	return out;
	
}
