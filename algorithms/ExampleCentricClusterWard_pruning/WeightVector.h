#ifndef WEIGHTVECTOR_H
#define WEIGHTVECTOR_H

#include <vector>
#include <iostream>
#include <stdexcept>

#include "MapCluster.h"

class DataPattern;
class HitCount;

class WeightVector : public MapCluster {
	
	public:
		// constructors/destructors
		WeightVector(unsigned int, double*, unsigned int);
		WeightVector(const WeightVector&);
		virtual ~WeightVector();
		
		// mutators
		void updatePatternHitCount(std::string&);
		void setLabel(const std::string);
		void setAverageNeighbourDistance(const double);
		
		// accessors
		virtual int getWeightVectorCount() const;
		virtual std::vector<const WeightVector*> getWeightVectors() const;
		virtual std::vector<double> getCentroid() const;
		virtual double getIntraClusterDistance() const;
		virtual std::vector<HitCount> getHitCounts() const;
		virtual void getNClusters(unsigned int, std::vector<const MapCluster*>&, std::vector<std::string>&) const;
		std::string getLabel() const;
		double getEuclideanDistance(const std::vector<double>) const throw (std::runtime_error);
		double getEuclideanDistance(DataPattern&);
		double getEuclideanDistance(WeightVector&);
		double getAverageNeighbourDistance() const;
		bool isToBePruned() const;
		
		// utility functions
		bool isMember(const WeightVector&) const;
		void markForPruning();
		std::ostream& outputLabelled(std::ostream&, const char*, const char*, const char*) const;
		virtual std::ostream& output(std::ostream&, const char*, const char*, const char*) const;
		
		// operators
		bool operator==(const WeightVector&) const;
	
	private:
		// data members
		unsigned int vectorDimension;
		double* weights;
		std::vector<HitCount> hitCounts;
		std::string label;
		double averageNeighbourDistance;
		bool toBePruned;
	
};

#endif
