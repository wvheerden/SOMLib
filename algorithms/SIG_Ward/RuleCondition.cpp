#include <fstream>

#include "RuleCondition.h"

// *** Destructor ***

// ===================================================
// Destructor : ~RuleCondition()
// Purpose    : De-allocates object resources
// ===================================================

RuleCondition::~RuleCondition() {
	
	;
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const RuleCondition&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const RuleCondition& condition) {
	
	return condition.print(out);
	
}
