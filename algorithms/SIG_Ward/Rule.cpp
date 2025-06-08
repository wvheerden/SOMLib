#include <fstream>

#include "Rule.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : Rule(string)
// Purpose     : Constructs rule with provided
//               predicted class label
// ===================================================

Rule::Rule(std::string _predictedClassLabel) :
predictedClassLabel(_predictedClassLabel), falsePositivesCount(0) {
	
	;
	
}

// ===================================================
// Constructor : Rule(const Rule&)
// Purpose     : Copy constructor
// ===================================================

Rule::Rule(const Rule& copySource) {
	
	predictedClassLabel = copySource.predictedClassLabel;
	falsePositivesCount = copySource.falsePositivesCount;
	
	for (unsigned int i = 0; i < copySource.conditions.size(); ++i) {
		conditions.push_back((copySource.conditions[i])->clone());
	}
	
}

// ===================================================
// Destructor : ~Rule()
// Purpose    : De-allocates object resources
// ===================================================

Rule::~Rule() {
	
	for (unsigned int i = 0; i < conditions.size(); ++i) {
		delete conditions[i];
	}
	
}

// *** Mutators ***

// ===================================================
// Mutator : void addCondition(RuleCondition&)
// Purpose : Add a copy of the supplied condition to
//           the rule
// ===================================================

void Rule::addCondition(RuleCondition& newCondition) {
	
	conditions.push_back(newCondition.clone());
	
}

// ===================================================
// Accessor : void incrementFalsePositivesCount()
// Purpose  : Increment the false positives count for
//            this rule
// ===================================================

void Rule::incrementFalsePositivesCount() {
	
	++falsePositivesCount;
	
}

// *** Accessors ***

// ===================================================
// Accessor : Rule* clone() const
// Purpose  : Returns a heap allocated copy of this
//            characterising rule
// ===================================================

Rule* Rule::clone() const {
	
	return new Rule(*this);
	
}

// ===================================================
// Accessor : unsigned int getTotalConditionCount() const
// Purpose  : Returns total condition count of this
//            rule
// ===================================================

unsigned int Rule::getTotalConditionCount() const {
	
	unsigned int conditionCount = 0;
	
	for (unsigned int i = 0; i < conditions.size(); ++i) {
		conditionCount += conditions[i]->getTotalConditionCount();
	}
	
	return conditionCount;
	
}

// ===================================================
// Accessor : unsigned int getRuleConditionCount() const
// Purpose  : Returns condition count of this
//            rule
// ===================================================

unsigned int Rule::getRuleConditionCount() const {
	
	return conditions.size();
	
}

// ===================================================
// Accessor : const RuleCondition& getCondition(unsigned int) const
// Purpose  : Returns a constant reference to the rule
//            condition for the rule at the supplied
//            index
// ===================================================

const RuleCondition& Rule::getCondition(unsigned int conditionIndex) const throw (std::runtime_error) {
	
	return *conditions[conditionIndex];
	
}

// ===================================================
// Accessor : bool matches(const DataPattern&) const
// Purpose  : Returns true if the supplied data
//            pattern matches the rule, false
//            otherwise
// ===================================================

bool Rule::matches(const DataPattern& pattern) const {
	
	if (getRuleConditionCount() > 0) {
		
		// test every condition in the rule
		for (unsigned int i = 0; i < getRuleConditionCount(); ++i) {
			
			// if a mismatch is found, the entire rule fails
			if (!conditions[i]->matches(pattern)) {
				return false;
			}
			
		}
		
		// if all conditions have successfully matched, entire rule matches
		return true;
	
	} else {
		
		// an empty rule always matches no patterns
		return false;
		
	}
	
}

// ===================================================
// Accessor : string getPredictedClassLabel() const
// Purpose  : Returns a copy of the predicted class
//            label for this rule
// ===================================================

std::string Rule::getPredictedClassLabel() const {
	
	return predictedClassLabel;
	
}

// ===================================================
// Accessor : unsigned int getFalsePositivesCount() const
// Purpose  : Returns the number of false positives
//            for this rule
// ===================================================

unsigned int Rule::getFalsePositivesCount() const {
	
	return falsePositivesCount;
	
}

// ===================================================
// Accessor : ostream& print(ostream&) const
// Purpose  : Prints conditional rule to supplied
//            output stream
// ===================================================

std::ostream& Rule::print(std::ostream& out) const {
	
	out << "IF ";
	out.flush();
	
	// output rule conditions
	for (unsigned int i = 0; i < getRuleConditionCount(); ++i) {
		out << "(" << *(conditions[i]) << ")";
		out.flush();
		
		if (i < (getRuleConditionCount() - 1)) {
			out << " AND ";
			out.flush();
		}
	}
	
	// output predicted class label
	out << " THEN class = " << getPredictedClassLabel();
	out.flush();
	
	return out;
	
}

// *** Utility Functions ***

// ===================================================
// Utility : ostream& printWithFalsePositives(ostream&) const
// Purpose : Print rule with false positive counts
// ===================================================

std::ostream& Rule::printWithFalsePositives(std::ostream& out) const {
	
	print(out);
	
	out << " : " << falsePositivesCount << " false positives";
	
	return out;
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const Rule&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const Rule& rule) {
	
	return rule.print(out);
	
}

// *** Functors ***

// ===================================================
// Functor : bool sortComparison(const Rule*, const Rule*)
// Purpose : Sort comparison functor for stable sort
//           component of unbiased sort algorithm,
//           generating a asscending order rule list
// ===================================================

bool sortComparison(Rule* rule1, Rule* rule2) {
	
	return rule1->getFalsePositivesCount() < rule2->getFalsePositivesCount();
	
}

// ===================================================
// Functor : bool equal(const Rule*, const Rule*)
// Purpose : Equality comparison function for
//           generating an ascending order sorted
//           rule list
// ===================================================

bool equal(const Rule* rule1, const Rule* rule2) {
	
	return rule1->getFalsePositivesCount() == rule2->getFalsePositivesCount();
	
}
