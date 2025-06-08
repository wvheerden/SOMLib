#include <cstring>

#include "HitCount.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : HitCount(string)
// Purpose     : Constructs hit count with supplied
//               label and a single hit
// ===================================================

HitCount::HitCount(std::string& _label) :
label(_label), count(1) {
	
	;
	
}

// ===================================================
// Constructor : HitCount(const HitCount&)
// Purpose     : Copy constructor
// ===================================================

HitCount::HitCount(const HitCount& source) :
label(source.label), count(source.count) {
	
	;
	
}

// ===================================================
// Destructor : ~HitCount()
// Purpose    : De-allocates object resources
// ===================================================

HitCount::~HitCount() {
	
	;
	
}

// *** Mutators ***

// ===================================================
// Mutator : void incrementCount()
// Purpose : Increments count by 1
// ===================================================

void HitCount::incrementCount() {
	
	++count;
	
}

// ===================================================
// Mutator : void incrementCount(unsigned int)
// Purpose : Increment count by specified value
// ===================================================

void HitCount::incrementCount(unsigned int increment) {
	
	count += increment;
	
}

// *** Accessors ***

// ===================================================
// Accessor : string getLabel() const
// Purpose  : Returns copy of count label
// ===================================================

std::string HitCount::getLabel() const {
	
	return label;
	
}

// ===================================================
// Accessor : unsigned int getCount() const
// Purpose  : Returns current count
// ===================================================

unsigned int HitCount::getCount() const {
	
	return count;
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const HitCount&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const HitCount& hitCount) {
	
	out << hitCount.label << ": " << hitCount.count;
	return out;
	
}
