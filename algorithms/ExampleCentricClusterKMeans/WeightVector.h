#ifndef WEIGHTVECTOR_H
#define WEIGHTVECTOR_H

#include <vector>
#include <iostream>
#include <stdexcept>

class DataPattern;
class HitCount;

class WeightVector {
	
	public:
		// constructors/destructors
		WeightVector(double*, unsigned int);
		WeightVector(const WeightVector&);
		virtual ~WeightVector();
		
		// mutators
		void updatePatternHitCount(std::string&);
		void setLabel(const std::string);
		
		// accessors
		int getWeightVectorCount() const;
		std::vector<const WeightVector*> getWeightVectors() const;
		std::vector<double> getCentroid() const;
		double getIntraClusterDistance() const;
		std::vector<HitCount> getHitCounts() const;
		std::string getLabel() const;
		double getEuclideanDistance(const std::vector<double>) const throw (std::runtime_error);
		double getEuclideanDistance(DataPattern&);
		
		// utility functions
		bool isMember(const WeightVector&) const;
		std::ostream& outputLabelled(std::ostream&, const char*, const char*, const char*) const;
		std::ostream& output(std::ostream&, const char*, const char*, const char*) const;
	
	private:
		// data members
		unsigned int vectorDimension;
		double* weights;
		std::vector<HitCount> hitCounts;
		std::string label;
	
};

#endif
