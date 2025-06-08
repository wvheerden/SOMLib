#include "DisjunctiveCondition.h"

#include <fstream>

// *** Constructor and Destructor ***

// ===================================================
// Constructor : DisjunctiveCondition()
// Purpose     : Constructs an empty disjunctive condition
// ===================================================

DisjunctiveCondition::DisjunctiveCondition() {
	
	;
	
}

// ===================================================
// Constructor : DisjunctiveCondition(const DisjunctiveCondition&)
// Purpose     : Copy constructor
// ===================================================

DisjunctiveCondition::DisjunctiveCondition(const DisjunctiveCondition& copySource) {
	
	for (unsigned int i = 0; i < copySource.conditions.size(); ++i) {
		conditions.push_back(copySource.conditions[i]->clone());
	}
	
}

// ===================================================
// Destructor : ~DisjunctiveCondition()
// Purpose    : De-allocates object resources
// ===================================================

DisjunctiveCondition::~DisjunctiveCondition() {
	
	for (unsigned int i = 0; i < conditions.size(); ++i) {
		delete conditions[i];
	}
	
}

// *** Accessors ***

// ===================================================
// Accessor : bool matches(const DataPattern&) const
// Purpose  : Returns a boolean value indicating
//            whether the supplied data patter
//            satisfies this condition
// ===================================================

bool DisjunctiveCondition::matches(const DataPattern& pattern) const {
	
	if (getTotalConditionCount() > 0) {
		
		// test every constituent condition in the disjunctive condition
		for (unsigned int i = 0; i < conditions.size(); i += 2) {
			
			// if one match is found, the entire condition succeeds
			if ((conditions[i]->matches(pattern)) && (conditions[i + 1]->matches(pattern))) {
				return true;
			}
			
		}
		
		// if no constituent conditions have successfully matched, entire conjunctive condition fails
		return false;
		
	} else {
		
		// an empty disjunctive condition always matches no patterns
		return false;
		
	}
	
}

// ===================================================
// Accessor : RuleCondition* clone() const
// Purpose  : Returns a heap allocated copy of this
//            disjunctive rule condition
// ===================================================

RuleCondition* DisjunctiveCondition::clone() const {
	
	return new DisjunctiveCondition(*this);
	
}

// ===================================================
// Accessor : ostream& print(ostream&) const
// Purpose  : Prints disjunctive rule condition to
//            supplied output stream
// ===================================================

std::ostream& DisjunctiveCondition::print(std::ostream& out) const {
	
	for (unsigned int i = 0; i < conditions.size(); i += 2) {
		
		out << "(";
		conditions[i]->print(out);
		out << " AND ";
		
		conditions[i + 1]->print(out);
		out << ")";
		
		if (i != conditions.size() - 2) {
			out << " OR ";
		}
		
	}
	
	return out;
	
}

// ===================================================
// Accessor : double getTotalConditionCount() const
// Purpose  : Returns the total number of conditions
//            in this disjunctive condition
// ===================================================

double DisjunctiveCondition::getTotalConditionCount() const {
	
	double conditionCount = 0.0;
	
	for (unsigned int i = 0; i < conditions.size(); ++i) {
		conditionCount += conditions[i]->getTotalConditionCount();
	}
	
	return conditionCount;
	
}

// ===================================================
// Accessor : double getConjunctiveConditionCount() const
// Purpose  : Returns the number of conjunctive
//            conditions in this disjunctive condition
// ===================================================

double DisjunctiveCondition::getConjunctiveConditionCount() const {
	
	return (((double) conditions.size()) / 2.0);
	
}

// ===================================================
// Accessor : bool isDisjunctive() const
// Purpose  : Returns true (the condition is
//            disjunctive)
// ===================================================

bool DisjunctiveCondition::isDisjunctive() const {
	
	return true;
	
}

// *** Mutators ***

// ===================================================
// Mutator : void addAttributeCondition(RuleCondition&)
// Purpose : Adds supplied rule condition to this
//           disjunctive condition
// ===================================================

void DisjunctiveCondition::addAttributeCondition(RuleCondition& newCondition) {
	
	conditions.push_back(newCondition.clone());
	
}
