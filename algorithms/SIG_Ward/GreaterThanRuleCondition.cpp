#include "GreaterThanRuleCondition.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : GreaterThanRuleCondition(string, unsigned int, double)
// Purpose     : Construct a "greater than" rule
//               condition with the supplied attribute
//               label, attribute number, and
//               condition threshold
// ===================================================

GreaterThanRuleCondition::GreaterThanRuleCondition(std::string _attributeLabel, unsigned int _attributeNumber, double _threshold) :
AttributeCondition(_attributeLabel, _attributeNumber, _threshold) {
	
	;
	
}

// ===================================================
// Destructor : ~GreaterThanRuleCondition()
// Purpose    : De-allocates object resources
// ===================================================

GreaterThanRuleCondition::~GreaterThanRuleCondition() {
	
	;
	
}

// *** Accessors ***

// ===================================================
// Accessor : bool matches(const DataPattern&) const
// Purpose  : Returns a boolean value indicating
//            whether the supplied data patter
//            satisfies this condition
// ===================================================

bool GreaterThanRuleCondition::matches(const DataPattern& pattern) const {
	
	if (pattern.getComponent(getAttributeNumber()) >= getThreshold()) {
		return true;
	} else {
		return false;
	}
	
}

// ===================================================
// Accessor : RuleCondition* clone() const
// Purpose  : Returns a heap allocated copy of this
//            "greater than" rule condition
// ===================================================

RuleCondition* GreaterThanRuleCondition::clone() const {
	
	return new GreaterThanRuleCondition(*this);
	
}

// ===================================================
// Accessor : ostream& print(ostream&) const
// Purpose  : Prints "greater than" rule condition to
//            supplied output stream
// ===================================================

std::ostream& GreaterThanRuleCondition::print(std::ostream& out) const {
	
	out << getAttributeLabel() << " >= " << getThreshold();
	
	return out;
	
}
