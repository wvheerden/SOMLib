#include "AttributeCondition.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : AttributeCondition(string, unsigned int, double)
// Purpose     : Construct an attyribute condition with the
//               supplied attribute label, attribute
//               number, and condition threshold
// ===================================================

AttributeCondition::AttributeCondition(std::string _attributeLabel, unsigned int _attributeNumber, double _threshold) :
attributeLabel(_attributeLabel), attributeNumber(_attributeNumber), threshold(_threshold) {
	
	;
	
}

// ===================================================
// Destructor : ~RuleCondition()
// Purpose    : De-allocates object resources
// ===================================================

AttributeCondition::~AttributeCondition() {
	
	;
	
}

// *** Accessors ***

// ===================================================
// Accessor : string getAttributeLabel() const
// Purpose  : Returns the attribute label of this
//            attribute condition
// ===================================================

std::string AttributeCondition::getAttributeLabel() const {
	
	return attributeLabel;
	
}

// ===================================================
// Accessor : unsigned int getAttributeNumber() const
// Purpose  : Returns the attribute number of this
//            attribute condition
// ===================================================

unsigned int AttributeCondition::getAttributeNumber() const {
	
	return attributeNumber;
	
}

// ===================================================
// Accessor : double getThreshold() const
// Purpose  : Returns the threshold of this attribute
//            condition
// ===================================================

double AttributeCondition::getThreshold() const {
	
	return threshold;
	
}

// ===================================================
// Accessor : double getTotalConditionCount() const
// Purpose  : Returns the total number of conditions
//            in this attribute condition
// ===================================================

double AttributeCondition::getTotalConditionCount() const {
	
	return 1.0;
	
}

// ===================================================
// Accessor : double getConditionCount() const
// Purpose  : Returns the number of conjunctive
//            conditions in this attribute condition
// ===================================================

double AttributeCondition::getConjunctiveConditionCount() const {
	
	return 1.0;
	
}

// ===================================================
// Accessor : bool isDisjunctive() const
// Purpose  : Returns false (the condition is not
//            disjunctive)
// ===================================================

bool AttributeCondition::isDisjunctive() const {
	
	return false;
	
}

// *** Friend Operators ***

// ===================================================
// Operator : bool operator==(const AttributeCondition&)
// Purpose  : Equivalence operator
// ===================================================

bool AttributeCondition::operator==(const AttributeCondition& rhs) {
	
	return ((attributeLabel == rhs.attributeLabel) && (attributeNumber == rhs.attributeNumber) && (threshold == rhs.threshold));
	
}
