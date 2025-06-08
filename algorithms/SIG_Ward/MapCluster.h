#ifndef MAPCLUSTER_H
#define MAPCLUSTER_H

#include <vector>

#include "HitCount.h"

class WeightVector;

class MapCluster {
	
	public:
		// constructors
		MapCluster(unsigned int);
		MapCluster(const MapCluster&);
		virtual ~MapCluster();
		
		// accessors
		virtual int getWeightVectorCount() const = 0;
		virtual std::vector<const WeightVector*> getWeightVectors() const = 0;
		virtual std::vector<double> getCentroid() const = 0;
		virtual double getCentroidWeight(unsigned int) const = 0;
		virtual double getIntraClusterDistance() const = 0;
		virtual std::vector<HitCount> getHitCounts() const = 0;
		virtual void getNClusters(unsigned int, std::vector<const MapCluster*>&, std::vector<std::string>&) const = 0;
		
		// utility functions
		virtual bool isMember(const WeightVector&) const = 0;
		virtual double calculateWardDistance(MapCluster&) const;
		virtual double calculateInterClusterDistance(MapCluster&) const;
		virtual double calculateSimilarityMeasure(MapCluster&) const;
		virtual std::ostream& output(std::ostream&, const char*, const char*, const char*) const = 0;
	
	protected:
		// utility functions
		virtual void updateLabelVector(const std::vector<HitCount>&, std::vector<std::string>&) const;
		
		// data members
		unsigned int clusteringLevel;
	
};

#endif
