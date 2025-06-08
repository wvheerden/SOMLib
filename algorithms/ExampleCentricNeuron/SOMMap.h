#ifndef SOMMAP_H
#define SOMMAP_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

class WeightVector;
class DataFileReader;

class SOMMap {
	
	public:
		// constructors/destructors
		SOMMap(unsigned int, unsigned int, unsigned int, double***);
		~SOMMap();
		
		// accessors
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int getWeightDimension() const;
		WeightVector getWeightVector(unsigned int, unsigned int) const throw (std::invalid_argument);
		
		unsigned int getUnlabeledWeights() const;
		double getUnlabeledWeightPercentage() const;
		
		double getTrainingAccuracy() const;
		double getTestAccuracy() const;
		
		double getTrainingError() const;
		double getTrainingMisclassifiedError() const;
		double getTrainingUnclassifiedError() const;
		
		double getTestError() const;
		double getTestMisclassifiedError() const;
		double getTestUnclassifiedError() const;
		
		// mutators
		void classifyTrainingData(DataFileReader&);
		void classifyTestData(DataFileReader&);
		
		// utility functions
		void neuronCentricLabelMap(DataFileReader&);
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const SOMMap&);
	
	private:
		// private copy constructor (forbid copying)
		SOMMap(const SOMMap&) throw (std::runtime_error);
		
		// private utility function
		void classify(DataFileReader& dataReader, double&, double&, double&) const;
		
		// data members
		unsigned int width;
		unsigned int height;
		unsigned int weightDimension;
		WeightVector*** mapGrid;
		double trainingErrorPercentage;
		double trainingMisclassificationPercentage;
		double trainingUnclassifiedPercentage;
		double testErrorPercentage;
		double testMisclassificationPercentage;
		double testUnclassifiedPercentage;
		
};

// friend operators
std::ostream& operator<<(std::ostream& out, const SOMMap& map);

#endif
