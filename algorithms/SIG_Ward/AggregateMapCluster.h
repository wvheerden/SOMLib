#ifndef AGGREGATEMAPCLUSTER_H
#define AGGREGATEMAPCLUSTER_H

#include <vector>

#include "MapCluster.h"

class WeightVector;
class HitCount;

class AggregateMapCluster : public MapCluster {
	
	public:
		// constructors
		AggregateMapCluster(unsigned int, MapCluster&, MapCluster&);
		AggregateMapCluster(const AggregateMapCluster&);
		virtual ~AggregateMapCluster();
		
		// accessors
		virtual int getWeightVectorCount() const;
		virtual std::vector<const WeightVector*> getWeightVectors() const;
		virtual std::vector<double> getCentroid() const;
		virtual double getCentroidWeight(unsigned int) const;
		virtual double getIntraClusterDistance() const;
		virtual std::vector<HitCount> getHitCounts() const;
		virtual void getNClusters(unsigned int, std::vector<const MapCluster*>&, std::vector<std::string>&) const;
		
		// utility functions
		bool isMember(const WeightVector&) const;
		virtual std::ostream& output(std::ostream&, const char*, const char*, const char*) const;
	
	private:
		// utility functions
		void mergeHitCounts(std::vector<HitCount>&, std::vector<HitCount>&) const;
		
		MapCluster* subCluster1;
		MapCluster* subCluster2;
		std::vector<double> centroid;
	
};

#endif
