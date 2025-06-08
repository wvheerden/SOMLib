#include "LessThanRuleCondition.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : LessThanRuleCondition(string, unsigned int, double)
// Purpose     : Construct a "less than" rule
//               condition with the supplied attribute
//               label, attribute number, and
//               condition threshold
// ===================================================

LessThanRuleCondition::LessThanRuleCondition(std::string _attributeLabel, unsigned int _attributeNumber, double _threshold) :
AttributeCondition(_attributeLabel, _attributeNumber, _threshold) {
	
	;
	
}

// ===================================================
// Destructor : ~LessThanRuleCondition()
// Purpose    : De-allocates object resources
// ===================================================

LessThanRuleCondition::~LessThanRuleCondition() {
	
	;
	
}

// *** Accessors ***

// ===================================================
// Accessor : bool matches(const DataPattern&) const
// Purpose  : Returns a boolean value indicating
//            whether the supplied data patter
//            satisfies this condition
// ===================================================

bool LessThanRuleCondition::matches(const DataPattern& pattern) const {
	
	if (pattern.getComponent(getAttributeNumber()) <= getThreshold()) {
		return true;
	} else {
		return false;
	}
	
}

// ===================================================
// Accessor : RuleCondition* clone() const
// Purpose  : Returns a heap allocated copy of this
//            "less than" rule condition
// ===================================================

RuleCondition* LessThanRuleCondition::clone() const {
	
	return new LessThanRuleCondition(*this);
	
}

// ===================================================
// Accessor : ostream& print(ostream&) const
// Purpose  : Prints "less than" rule condition to
//            supplied output stream
// ===================================================

std::ostream& LessThanRuleCondition::print(std::ostream& out) const {
	
	out << getAttributeLabel() << " <= " << getThreshold();
	
	return out;
	
}
