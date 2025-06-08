#ifndef DATAPATTERN_H
#define DATAPATTERN_H

#include <stdexcept>
#include <vector>

class DataPattern {
	
	public:
		// constructor/destructor
		DataPattern(std::vector<double>, char*, unsigned int);
		DataPattern(const DataPattern&);
		~DataPattern();
		
		// accessors
		unsigned int getDimension() const;
		double getComponent(unsigned int) const throw (std::runtime_error);
		std::string getLabel() const;
		unsigned int getLabelIndex() const;
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const DataPattern&);
	
	private:
		// data members
		std::vector<double> attributeValues;
		std::string patternLabel;
		unsigned int patternLabelIndex;
	
};

// friend operators
std::ostream& operator<<(std::ostream&, const DataPattern&);

#endif
