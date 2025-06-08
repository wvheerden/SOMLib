#include <cmath>

#include "WeightVector.h"
#include "DataPattern.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : WeightVector(unsigned int, double*, unsigned int)
// Purpose     : Constructs weight vector with given
//               clustering level, weights, dimension
//               and valid label
// ===================================================

WeightVector::WeightVector(unsigned int _clusteringLevel, double* _weights, unsigned int _vectorDimension) :
MapCluster(_clusteringLevel), vectorDimension(_vectorDimension), weights(new double[_vectorDimension]), label(""), averageNeighbourDistance(0.0), toBePruned(false) {
	
	// copy weight values
	for (unsigned int i = 0; i < vectorDimension; ++i) {
		weights[i] = _weights[i];
	}
	
}

// ===================================================
// Constructor : WeightVector(const WeightVector&)
// Purpose     : Copy constructor
// ===================================================

WeightVector::WeightVector(const WeightVector& source) :
MapCluster(source), vectorDimension(source.vectorDimension), weights(new double[source.vectorDimension]), hitCounts(source.hitCounts), label(source.label), averageNeighbourDistance(source.averageNeighbourDistance), toBePruned(source.toBePruned) {
	
	// initialise LHS with RHS resources
	for (unsigned int i = 0; i < vectorDimension; ++i) {
		weights[i] = source.weights[i];
	}
	
}

// ===================================================
// Destructor : ~WeightVector()
// Purpose    : De-allocates object resources
// ===================================================

WeightVector::~WeightVector() {
	
	delete[] weights;
	
}

// *** Mutators ***

// ===================================================
// Mutator : void updatePatternHitCount(string)
// Purpose : Update the specified pattern hit count
// ===================================================

void WeightVector::updatePatternHitCount(std::string& patternLabel) {
	
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
// Mutator : void setLabel(const string)
// Purpose : Sets weight vector label
// ===================================================

void WeightVector::setLabel(const std::string _label) {
	
	label = _label;
	
}

// ===================================================
// Mutator : void setAverageNeighbourDistance(const double)
// Purpose : Sets average distance to neighbouring
//           weight vectors
// ===================================================

void WeightVector::setAverageNeighbourDistance(const double _averageNeighbourDistance) {
	
	averageNeighbourDistance = _averageNeighbourDistance;
	
}

// *** Accessors ***

// ===================================================
// Accessor : int getWeightVectorCount() const
// Purpose  : Returns number of weight vectors in this
//            cluster (i.e. 1)
// ===================================================

int WeightVector::getWeightVectorCount() const {
	
	return 1;
	
}

// ===================================================
// Accessor : vector<const WeightVector*> getWeightVectors() const
// Purpose  : Returns weight vectors belonging to this
//            weight vector
// ===================================================

std::vector<const WeightVector*> WeightVector::getWeightVectors() const {
	
	std::vector<const WeightVector*> returnVector;
	returnVector.push_back(this);
	return returnVector;
	
}

// ===================================================
// Accessor : double* getCentroid() const
// Purpose  : Returns centroid of this weight vector
//            (i.e. the values constituting the weight
//            vector itself)
// ===================================================

std::vector<double> WeightVector::getCentroid() const {
	
	std::vector<double> returnVector;
	
	// copy centroid values to returning vector
	for (unsigned int i = 0; i < vectorDimension; ++i) {
		returnVector.push_back(weights[i]);
	}
	
	return returnVector;
	
}

// ===================================================
// Accessor : double getIntraClusterDistance() const
// Purpose  : Returns an arbitrary maximum value (in
//            order to discourage selection of unary
//            clusters by the Davies-Bouldin index
// ===================================================

double WeightVector::getIntraClusterDistance() const {
	
	return 5000.0;
	
}

// ===================================================
// Accessor : vector<HitCount> getHitCounts() const
// Purpose  : Returns a vector of hit counts for this
//            weight vector
// ===================================================

std::vector<HitCount> WeightVector::getHitCounts() const {
	
	return hitCounts;
	
}

// ===================================================
// Accessor : void getNClusters(unsigned int, vector<const MapCluster*>&, vector<string>&) const
// Purpose  : Perform recursive tree traversal,
//            searching for specified level of
//            clustering
// ===================================================

void WeightVector::getNClusters(unsigned int targetClusteringLevel, std::vector<const MapCluster*>& storageVector, std::vector<std::string>& labelVector) const {
	
	if (targetClusteringLevel <= clusteringLevel) {
		
		// add appropriate vector
		storageVector.push_back(this);
		
		// add vector's label
		updateLabelVector(hitCounts, labelVector);
		
	}
	
}

// ===================================================
// Accessor : string getLabel() const
// Purpose  : Return a copy of this weight vector's
//            label
// ===================================================

std::string WeightVector::getLabel() const {
	
	return label;
	
}

// ===================================================
// Accessor : double getEuclideanDistance(vector<double>) const
// Purpose  : Returns Euclidean distance between this
//            weight vector and an arbitrary vector of
//            floating point numbers
// ===================================================

double WeightVector::getEuclideanDistance(const std::vector<double> vec) const throw (std::runtime_error) {
	
	if (vectorDimension != vec.size()) {
		throw std::runtime_error("Non-matching vector dimensions in Euclidean comparison (weight vector and vector)");
	}
	
	double returnDistance = 0.0;
	
	for (unsigned int i = 0; i < vec.size(); ++i) {
		returnDistance += pow(weights[i] - vec[i], 2.0);
	}
	
	return sqrt(returnDistance);
	
}

// ===================================================
// Accessor : double getEuclideanDistance(DataPattern&)
// Purpose  : Returns Euclidean distance between this
//            weight vector and an arbitrary data pattern
// ===================================================

double WeightVector::getEuclideanDistance(DataPattern& pattern) {
	
	if (vectorDimension != pattern.getDimension()) {
		throw std::runtime_error("Non-matching vector dimensions in Euclidean comparison (weight vector and data pattern)");
	}
	
	double returnDistance = 0.0;
	
	for (unsigned int i = 0; i < pattern.getDimension(); ++i) {
		returnDistance += pow(weights[i] - pattern.getComponent(i), 2.0);
	}
	
	return sqrt(returnDistance);
	
}

// ===================================================
// Accessor : double getEuclideanDistance(WeightVector&)
// Purpose  : Returns Euclidean distance between this
//            weight vector and an arbitrary weight vector
// ===================================================

double WeightVector::getEuclideanDistance(WeightVector& anotherWeightVector) {
	
	if (vectorDimension != anotherWeightVector.vectorDimension) {
		throw std::runtime_error("Non-matching vector dimensions in Euclidean comparison (weight vector and weight vector)");
	}
	
	double returnDistance = 0.0;
	
	for (unsigned int i = 0; i < vectorDimension; ++i) {
		returnDistance += pow(weights[i] - anotherWeightVector.weights[i], 2.0);
	}
	
	return sqrt(returnDistance);
	
}

// ===================================================
// Accessor : double getAverageNeighbourDistance() const
// Purpose  : Returns average distance to the
//            neighbours of this weight vector
// ===================================================

double WeightVector::getAverageNeighbourDistance() const {
	
	return averageNeighbourDistance;
	
}

// ===================================================
// Accessor : bool isToBePruned() const
// Purpose  : Returns average distance to the
//            neighbours of this weight vector
// ===================================================

bool WeightVector::isToBePruned() const {
	
	return toBePruned;
	
}

// *** Public Utility Functions ***

// ===================================================
// Utility : bool isMember(const WeightVector&) const
// Purpose : Tests membership of supplied weight
//           vector to this weight vector (i.e.
//           returns true only if supplied weight
//           vector is equivalent to this weight
//           vector)
// ===================================================

bool WeightVector::isMember(const WeightVector& vector) const {
	
	if (&vector == this) {
		return true;
	} else {
		return false;
	}
	
}

// ===================================================
// Utility : void markForPruning()
// Purpose : Mark this weight vector for pruning from
//           the map
// ===================================================

void WeightVector::markForPruning() {

	toBePruned = true;

}

// *** Protected Utility Functions ***

// ===================================================
// Utility : ostream& outputLabelled(ostream&, const char*, const char*, const char*) const;
// Purpose : Output only labelled WeightVector object
// ===================================================

std::ostream& WeightVector::outputLabelled(std::ostream& out, const char* leader, const char* separator, const char* terminator) const {
	
	// output only if label is defined (so CN2 and C4.5 can handle the records)
	if (label != "") {
		output(out, leader, separator, terminator);
	}
	
	return out;
	
}

// ===================================================
// Utility : ostream& output(ostream&, const char*, const char*, const char*) const
// Purpose : Output WeightVector object
// ===================================================

std::ostream& WeightVector::output(std::ostream& out, const char* leader, const char* separator, const char* terminator) const {
	
	out << leader;
	
	for (unsigned int i = 0; i < vectorDimension; ++i) {
		
		out << weights[i];
		out.flush();
		
		if (i != (vectorDimension - 1)) {
			out << separator;
		}
		
	}
	
	out << separator;
	out << label;
	out << terminator;
	
	return out;
	
}
