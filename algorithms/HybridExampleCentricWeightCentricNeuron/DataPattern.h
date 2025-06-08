#ifndef DATAPATTERN_H
#define DATAPATTERN_H

#include <stdexcept>
#include <vector>

class DataPattern {
	
	public:
		// constructor/destructor
		DataPattern(std::vector<double>, char*);
		DataPattern(const DataPattern&);
		~DataPattern();
		
		// accessors
		unsigned int getDimension();
		double getComponent(unsigned int) throw (std::runtime_error);
		std::string getLabel();
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const DataPattern&);
	
	private:
		// data members
		std::vector<double> attributeValues;
		std::string patternLabel;
	
};

// friend operators
std::ostream& operator<<(std::ostream&, const DataPattern&);

#endif
