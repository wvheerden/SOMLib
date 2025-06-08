#ifndef SOMMAP_H
#define SOMMAP_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "Rule.h"

class MapCluster;
class WeightVector;
class DataFileReader;
class DataPattern;

class SOMMap {
	
	public:
		// constructors/destructor
		SOMMap(unsigned int, unsigned int, unsigned int, double***);
		~SOMMap();
		
		// accessors
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int getWeightDimension() const;
		unsigned int getOptimalClusterCount() const;
		std::string getOptimalClusterLabel(unsigned int) const;
		std::vector<std::vector<DataPattern> > getOptimalClusterMappedPatterns(DataFileReader&);
		
		// utility functions
		void wardClusterMap();
		void labelMap(DataFileReader&);
		void addRuleCondition(Rule&, std::vector<std::vector<DataPattern> >&,unsigned int, unsigned int, std::string, double, double) const;
		void addRuleCondition(std::vector<RuleCondition*>&, std::vector<std::vector<DataPattern> >& mappedPatterns, unsigned int, unsigned int, std::string, double, double) const;
		std::ostream& outputOptimalClusterConstituents(std::ostream&);
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const SOMMap&);
	
	protected:
		// accessors
		double getCurrentDaviesBouldinIndex() const throw (std::runtime_error);
	
	private:
		// private copy constructor (forbid copying)
		SOMMap(const SOMMap&) throw (std::runtime_error);
		
		// data members
		unsigned int width;
		unsigned int height;
		unsigned int weightDimension;
		WeightVector*** mapGrid;
		std::vector<MapCluster*> clusterVector;
		std::vector<std::vector<double> > distanceMatrix;
		std::vector<std::vector<double> > similarityMeasureMatrix;
		std::vector<double> clusterCosts;
		std::vector<const MapCluster*> optimalClusters;
		std::vector<std::string> optimalClusterLabels;
	
};

// friend operators
std::ostream& operator<<(std::ostream&, const SOMMap&);

#endif
