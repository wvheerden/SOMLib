#include <cstring>
#include <iostream>

#include "DataPattern.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : DataPattern(std::vector<double>, char*, unsigned int)
// Purpose     : Constructs data pattern with provided
//               attribute values and label
// ===================================================

DataPattern::DataPattern(std::vector<double> _attributeValues, char* _patternLabel, unsigned int _patternLabelIndex) :
attributeValues(_attributeValues), patternLabel(_patternLabel), patternLabelIndex(_patternLabelIndex) {
	
	;
	
}

// ===================================================
// Constructor : DataPattern(const DataPattern&)
// Purpose     : Copy constructor
// ===================================================

DataPattern::DataPattern(const DataPattern& source) :
attributeValues(source.attributeValues), patternLabel(source.patternLabel), patternLabelIndex(source.patternLabelIndex) {
	
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
// Accessor : unsigned int getDimension() const
// Purpose  : Return pattern dimension
// ===================================================

unsigned int DataPattern::getDimension() const {
	
	return attributeValues.size();
	
}

// ===================================================
// Accessor : double getComponent(unsigned int) const
// Purpose  : Return specified pattern component
// ===================================================

double DataPattern::getComponent(unsigned int componentIndex) const throw (std::runtime_error) {
	
	if (componentIndex >= getDimension()) {
		throw std::runtime_error("Invalid index specified for retrieval from component");
	}
	
	return attributeValues[componentIndex];
	
}

// ===================================================
// Accessor : string getLabel() const
// Purpose  : Return copy of pattern label
// ===================================================

std::string DataPattern::getLabel() const {
	
	return patternLabel;
	
}

// ===================================================
// Accessor : unsigned int getLabelIndex() const
// Purpose  : Return the label index of this patterns
//            classification label
// ===================================================

unsigned int DataPattern::getLabelIndex() const {
	
	return patternLabelIndex;
	
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
			out << " ";
		}
		
	}
	
	out << "] : " << pattern.patternLabel;
	
	return out;
	
}
