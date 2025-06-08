#include "SignificanceValue.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : SignificanceValue(int, double)
// Purpose     : Constructs significance value with
//               given attribute number and value
// ===================================================

SignificanceValue::SignificanceValue(unsigned int _attributeNumber, double _value) :
attributeNumber(_attributeNumber), value(_value), marked(false) {
	
	;
	
}

// ===================================================
// Constructor : SignificanceValue(const SignificanceValue&)
// Purpose     : Constructs significance value with
//               given attribute number and value
// ===================================================

SignificanceValue::SignificanceValue(const SignificanceValue& copySource) :
attributeNumber(copySource.attributeNumber), value(copySource.value), marked(copySource.marked) {
	
	;
	
}

// ===================================================
// Destructor : ~SignificanceValue()
// Purpose    : De-allocates object resources
// ===================================================

SignificanceValue::~SignificanceValue() {
	
	;
	
}

// *** Accessors ***

// ===================================================
// Accessor : unsigned int getAttributeNumber() const
// Purpose  : Returns current attribute number
// ===================================================

unsigned int SignificanceValue::getAttributeNumber() const {
	
	return attributeNumber;
	
}

// ===================================================
// Accessor : int getValue() const
// Purpose  : Returns current significance value
// ===================================================

double SignificanceValue::getValue() const {
	
	return value;
	
}

// ===================================================
// Accessor : bool isMarked() const
// Purpose  : Returns current marked status
// ===================================================

bool SignificanceValue::isMarked() const {
	
	return marked;
	
}

// *** Mutators ***

// ===================================================
// Mutator : void normalise(double)
// Purpose : Normalises current significance value by
//           specified normalisation average
// ===================================================

void SignificanceValue::normalise(double normalisationAverage) {
	
	value = (value / normalisationAverage) * 100.0;
	
}

// ===================================================
// Mutator : void mark(bool)
// Purpose : Mark current significance value using
//           supplied flag value
// ===================================================

void SignificanceValue::mark(bool _marked) {
	
	marked = _marked;
	
}

// *** Member Operators ***

// ===================================================
// Operator : SignificanceValue& operator=(const SignificanceValue&);
// Purpose  : Assignment operator operator
// ===================================================

SignificanceValue& SignificanceValue::operator=(const SignificanceValue& copySource) {
	
	attributeNumber = copySource.attributeNumber;
	value = copySource.value;
	marked = copySource.marked;
	
	return *this;
	
}

// ===================================================
// Operator : bool operator==(const double&) const
// Purpose  : Equality comparison operator
// ===================================================

bool SignificanceValue::operator==(const double& comparisonValue) const {
	
	return value == comparisonValue;
	
}

// ===================================================
// Operator : bool operator!=(const SignificanceValue&) const
// Purpose  : Equality comparison operator
// ===================================================

bool SignificanceValue::operator!=(const SignificanceValue& comparisonSignificanceValue) const {
	
	return value != comparisonSignificanceValue.getValue();
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const SignificanceValue&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const SignificanceValue& sigValue) {
	
	switch (sigValue.attributeNumber) {
		case 0:
			out << "SepalLength";
			break;
		case 1:
			out << "SepalWidth ";
			break;
		case 2:
			out << "PetalLength";
			break;
		case 3:
			out << "PetalWidth ";
	}
	
	out << ":" << sigValue.value << " ";
	
	if (sigValue.marked) {
		out << "*";
	} else {
		out << " ";
	}
	
	return out;
	
}

// *** Functors ***

// ===================================================
// Functor : bool sortComparison(const SignificanceValue&, const SignificanceValue&)
// Purpose : Sort comparison functor for stable sort
//           component of unbiased sort algorithm,
//           generating a descending order
//           significance value list
// ===================================================

bool sortComparison(const SignificanceValue significanceValue1, const SignificanceValue significanceValue2) {
	
	return significanceValue1.getValue() > significanceValue2.getValue();
	
}

// ===================================================
// Functor : bool equal(const SignificanceValue&, const SignificanceValue&)
// Purpose : Equality comparison function for
//           generating an descending order sorted
//           significance vluae list
// ===================================================

bool equal(const SignificanceValue& significanceValue1, const SignificanceValue& significanceValue2) {
	
	return significanceValue1.getValue() == significanceValue2.getValue();
	
}
