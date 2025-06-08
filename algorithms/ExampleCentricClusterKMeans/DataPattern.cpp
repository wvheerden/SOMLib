#include <cstring>
#include <iostream>

#include "DataPattern.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : DataPattern(std::vector<double>, char*)
// Purpose     : Constructs data pattern with provided
//               attribute values and label
// ===================================================

DataPattern::DataPattern(std::vector<double> _attributeValues, char* _patternLabel) :
attributeValues(_attributeValues), patternLabel(_patternLabel) {
	
	;
	
}

// ===================================================
// Constructor : DataPattern(const DataPattern&)
// Purpose     : Copy constructor
// ===================================================

DataPattern::DataPattern(const DataPattern& source) :
attributeValues(source.attributeValues), patternLabel(source.patternLabel) {
	
	;
	
}

// ===================================================
// Destructor : ~DataPattern()
// Purpose    : De-allocates object resources
// ===================================================

DataPattern::~DataPattern() {
	
	;
	
}

// *** Accessors ***

// ===================================================
// Accessor : unsigned int getDimension()
// Purpose  : Return pattern dimension
// ===================================================

unsigned int DataPattern::getDimension() {
	
	return attributeValues.size();
	
}

// ===================================================
// Accessor : double getComponent(unsigned int)
// Purpose  : Return specified pattern component
// ===================================================

double DataPattern::getComponent(unsigned int componentIndex) throw (std::runtime_error) {
	
	if (componentIndex >= getDimension()) {
		throw std::runtime_error("Invalid index specified for retrieval from component");
	}
	
	return attributeValues[componentIndex];
	
}

// ===================================================
// Accessor : string getLabel()
// Purpose  : Return copy of pattern label
// ===================================================

std::string DataPattern::getLabel() {
	
	return patternLabel;
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const DataPattern&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const DataPattern& pattern) {
	
	out << "[";
	
	for (unsigned int i = 0; i < pattern.attributeValues.size(); ++i) {
		
		out << pattern.attributeValues[i];
		
		if (i != (pattern.attributeValues.size() - 1)) {
			out << "; ";
		}
		
	}
	
	out << "] : " << pattern.patternLabel;
	
	return out;
	
}
