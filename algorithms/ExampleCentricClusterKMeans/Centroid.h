#ifndef CENTROID_H
#define CENTROID_H

#include <vector>
#include <iostream>

#include "WeightVector.h"
#include "HitCount.h"

class Centroid {
	
	public:
		// constructor
		Centroid(WeightVector*);
		
		// accessors
		std::vector<double> getComponents() const;
		double getIntraClusterSimilarity() const;
		double getInterClusterSimilarity(Centroid&) const;
		bool contains(WeightVector*) const;
		std::string getLabel() const;
		std::ostream& output(std::ostream&, const char*, const char*, const char*) const;	
	
		// mutators
		void resetLabel();
		void updateCentroid(WeightVector*);
		void addWeightVector(WeightVector*);
		void updatePatternHitCount(std::string);
	
	private:
		std::vector<double> centroidComponents;
		unsigned int weightVectorCount;
		std::vector<WeightVector*> weightVectorConstituents;
		std::vector<HitCount> hitCounts;
		std::string label;
	
};

#endif
