#include <iostream>
#include <cmath>

#include "RuleSet.h"
#include "RuleCondition.h"
#include "Utilities.h"
#include "DataPattern.h"
#include "Random.h"

// *** Constructor and Destructor

// ===================================================
// Constructor : RuleSet()
// Purpose     : Construct an empty rule set
// ===================================================

RuleSet::RuleSet() {
	
	;
	
}

// ===================================================
// Constructor : RuleSet(const RuleSet&)
// Purpose     : Copy constructor
// ===================================================

RuleSet::RuleSet(const RuleSet& copySource) {
	
	for (unsigned int i = 0; i < copySource.getRuleCount(); ++i) {
		ruleList.push_back((copySource.ruleList[i])->clone());
	}
	
}

// ===================================================
// Destructor : ~RuleSet()
// Purpose    : De-allocates object resources
// ===================================================

RuleSet::~RuleSet() {
	
	// de-allocate each rule that has been copied into the list
	for (unsigned int i = 0; i < getRuleCount(); ++i) {
		delete ruleList[i];
	}
	
}

// *** Accessors ***

// ===================================================
// Accessor : double evaluate(const DataFileReader&, double&, double&, double&) const
// Purpose  : Evaluate the supplied data file reader
//            agains the rule set, and return the
//            resultant classification error
//            percentage
// ===================================================

void RuleSet::evaluate(const DataFileReader& dataReader, double& error, double& misclassifiedError, double& unclassifiedError) const {
	
	unsigned int exampleCount = dataReader.getRecordCount();
	unsigned int errorCount = 0;
	unsigned int misclassificationCount = 0;
	unsigned int unclassifiedCount = 0;
	
	// work through entire data set
	for (unsigned int i = 0; i < exampleCount; ++i) {
		
		bool matched = false;
		
		// compare current data pattern to all rules
		for (unsigned int j = 0; j < getRuleCount(); ++j) {
			
			// test for rule match
			if (ruleList[j]->matches(dataReader.getRecord(i))) {
				
				matched = true;
				
				// log incorrect classifications
				if (ruleList[j]->getPredictedClassLabel() != dataReader.getRecord(i).getLabel()) {
					++errorCount;
					++misclassificationCount;
				}
				
				break;
			}
			
		}
		
		// log if example is unclassified
		if (!matched) {
			++errorCount;
			++unclassifiedCount;
		}
		
	}
	
	if (exampleCount > 0) {
		error = ((double) errorCount / (double) exampleCount) * 100.0;
		misclassifiedError = ((double) misclassificationCount / (double) exampleCount) * 100.0;
		unclassifiedError = ((double) unclassifiedCount / (double) exampleCount) * 100.0;
	} else {
		error = 0.0;
		misclassifiedError = 0.0;
		unclassifiedError = 0.0;
	}
	
	if (!std::isfinite(error)) {
		std::cerr << std::endl << "ERROR: Invalid error computed" << std::endl;
	}
	
	if (!std::isfinite(misclassifiedError)) {
		std::cerr << std::endl << "ERROR: Invalid misclassified error computed" << std::endl;
	}
	
	if (!std::isfinite(unclassifiedError)) {
		std::cerr << std::endl << "ERROR: Invalid unclassified error computed" << std::endl;
	}
	
}

// ===================================================
// Accessor : vector<unsigned int> calculateOrderingStats(const DataFileReader&) const
// Purpose  : Evaluate data set on current rule set,
//            update false positive count across rule
//            set
// ===================================================

void RuleSet::calculateOrderingStats(const DataFileReader& dataReader) const {
	
	// work through entire data set
	for (unsigned int i = 0; i < dataReader.getRecordCount(); ++i) {
		
		// compare current data pattern to all rules
		for (unsigned int j = 0; j < getRuleCount(); ++j) {
			
			// test for rule match
			if (ruleList[j]->matches(dataReader.getRecord(i))) {
				
				// log on incorrect classification
				if (ruleList[j]->getPredictedClassLabel() != dataReader.getRecord(i).getLabel()) {
					ruleList[j]->incrementFalsePositivesCount();
				}
				
			}
			
		}
		
	}
	
}

// ===================================================
// Accessor : double getRuleCount() const
// Purpose  : Returns the number of rules in the rule
//            set
// ===================================================

double RuleSet::getRuleCount() const {
	
	return (double) ruleList.size();
	
}

// ===================================================
// Accessor : double getTotalConditionCount() const
// Purpose  : Returns the total number of conditions
//            of the rule set
// ===================================================

double RuleSet::getTotalConditionCount() const {
	
	double totalSize = 0.0;
	
	for (unsigned int i = 0; i < getRuleCount(); ++i) {
		totalSize += ruleList[i]->getTotalConditionCount();
	}
	
	return totalSize;
	
}

// ===================================================
// Accessor : double getAverageConditionsPerRule() const
// Purpose  : Returns the average number of conditions
//            per rule in the rule set
// ===================================================

double RuleSet::getAverageConditionsPerRule() const throw (std::runtime_error) {
	
	double totalConditionCount = getTotalConditionCount();
	double ruleCount = getRuleCount();
	
	if (totalConditionCount <= 0) {
		throw std::runtime_error("Non-positive condition count found while calculating average conditions per rule");
	}
	
	if (ruleCount <= 0) {
		throw std::runtime_error("Non-positive rule count found while calculating average conditions per rule");
	}
	
	double returnValue = totalConditionCount / ruleCount;
	
	if (!std::isfinite(returnValue)) {
		std::cerr << std::endl << "ERROR: Invalid average conditions per rule computed" << std::endl;
	}
	
	return returnValue;
	
}

// ===================================================
// Accessor : double getConjunctiveRuleCountForRule() const
// Purpose  : Returns the number of rules in the
//            specified rule (modified to contain only
//            conjunctive conditions)
// ===================================================

double RuleSet::getConjunctiveRuleCountForRule(unsigned int ruleIndex) const {
	
	double returnValue = 1.0;
	
	// consider the specified rule
	Rule* currentRule = ruleList[ruleIndex];
	
	// run through each condition in the rule
	for (unsigned int i = 0; i < currentRule->getRuleConditionCount(); ++i) {
		
		// retrieve only differentiating conditions, and combine into the count
		const RuleCondition& currentCondition = currentRule->getCondition(i);
		
		if (currentCondition.isDisjunctive()) {
			returnValue *= currentCondition.getConjunctiveConditionCount();
		}
		
	}
	
	return returnValue;
	
}








double RuleSet::getConjunctiveRuleCountForRule_alternative(unsigned int ruleIndex) const {
	
	double returnValue = 1.0;
	
	// consider the specified rule
	Rule* currentRule = ruleList[ruleIndex];
	
	// run through each condition in the rule
	for (unsigned int i = 0; i < currentRule->getRuleConditionCount(); ++i) {
		
		// retrieve only differentiating conditions, and combine into the count
		const RuleCondition& currentCondition = currentRule->getCondition(i);
		returnValue *= currentCondition.getConjunctiveConditionCount();
		
	}
	
	return returnValue;
	
}










// ===================================================
// Accessor : double getConjunctiveRuleCount() const
// Purpose  : Returns the number of rules in the rule
//            set (modified to contain only
//            conjunctive conditions)
// ===================================================

double RuleSet::getConjunctiveRuleCount() const {
	
	double conjunctiveRuleCount = 0.0;
	
	// consider each rule in turn
	for (unsigned int i = 0; i < ruleList.size(); ++i) {
		conjunctiveRuleCount += getConjunctiveRuleCountForRule(i);
	}
	
	return conjunctiveRuleCount;
	
}










double RuleSet::getConjunctiveRuleCount_alternative() const {
	
	double conjunctiveRuleCount = 0.0;
	
	// consider each rule in turn
	for (unsigned int i = 0; i < ruleList.size(); ++i) {
		conjunctiveRuleCount += getConjunctiveRuleCountForRule_alternative(i);
	}
	
	return conjunctiveRuleCount;
	
}









// ===================================================
// Accessor : double getConjunctiveConditionCountForRule(unsigned int) const
// Purpose  : Returns the number of conditions in the
//            specified rule (modified to contain only
//            conjunctive conditions)
// ===================================================

double RuleSet::getConjunctiveConditionCountForRule(unsigned int ruleIndex) const {
	
	double numberOfCharacterisingConditions = 0.0;
	double numberOfDifferentiatingConditions = 0.0;
	
	// consider the specified rule
	Rule* currentRule = ruleList[ruleIndex];
	
	// run through each condition in the rule
	for (unsigned int i = 0; i < currentRule->getRuleConditionCount(); ++i) {
		
		// consider each condition, and handle appropriately
		const RuleCondition& currentCondition = currentRule->getCondition(i);
		
		if (currentCondition.isDisjunctive()) {
			++numberOfDifferentiatingConditions;
		} else {
			++numberOfCharacterisingConditions;
		}
		
	}
	
	return numberOfCharacterisingConditions + (numberOfDifferentiatingConditions * 2.0);
	
}









double RuleSet::getConjunctiveConditionCountForRule_alternative(unsigned int ruleIndex) const {
	
	double characterisingConditions = 0.0;
	double differentiatingConditions = 0.0;
	
	for (unsigned int i = 0; i < ruleList[ruleIndex]->getRuleConditionCount(); ++i) {
		
		if (ruleList[ruleIndex]->getCondition(i).isDisjunctive()) {
			++differentiatingConditions;
		} else {
			++characterisingConditions;
		}
		
	}
	
	return getConjunctiveRuleCountForRule_alternative(ruleIndex) * (characterisingConditions + (differentiatingConditions * 2));
	
}










// ===================================================
// Accessor : unsigned int getTotalConjunctiveConditionCount() const
// Purpose  : Returns the total number of conditions
//            of the rule set (modified to contain
//            only conjunctive conditions)
// ===================================================

double RuleSet::getTotalConjunctiveConditionCount() const {
	
	double totalRuleConjunctiveConditionCount = 0.0;
	
	// consider each rule in turn
	for (unsigned int i = 0; i < ruleList.size(); ++i) {
		totalRuleConjunctiveConditionCount += getConjunctiveRuleCountForRule(i) * getConjunctiveConditionCountForRule(i);
	}
	
	return totalRuleConjunctiveConditionCount;
	
}







double RuleSet::getTotalConjunctiveConditionCount_alternative() const {
	
	double totalRuleConjunctiveConditionCount = 0.0;
	
	// consider each rule in turn
	for (unsigned int i = 0; i < ruleList.size(); ++i) {
		totalRuleConjunctiveConditionCount += getConjunctiveConditionCountForRule_alternative(i);
	}
	
	return totalRuleConjunctiveConditionCount;
	
}










// ===================================================
// Accessor : unsigned int getAverageConditionsPerConjunctiveRule() const
// Purpose  : Returns the average number of conditions
//            per rule in the rule set (modified to
//            contain only conjunctive conditions)
// ===================================================

double RuleSet::getAverageConditionsPerConjunctiveRule() const throw (std::runtime_error) {
	
	double totalConjunctiveConditionCount = getTotalConjunctiveConditionCount();
	double conjunctiveRuleCount = getConjunctiveRuleCount();
	
	if (totalConjunctiveConditionCount <= 0) {
		throw std::runtime_error("Non-positive conjunctive condition count found while calculating average conjunctive conditions per rule");
	}
	
	if (conjunctiveRuleCount <= 0) {
		throw std::runtime_error("Non-positive conjunctive rule count found while calculating average conjunctive conditions per rule");
	}
	
	double returnValue = totalConjunctiveConditionCount / conjunctiveRuleCount;
	
	if (!std::isfinite(returnValue)) {
		std::cerr << std::endl << "ERROR: Invalid average conditions per conjunctive rule computed" << std::endl;
	}
	
	return returnValue;
	
}







double RuleSet::getAverageConditionsPerConjunctiveRule_alternative() const throw (std::runtime_error) {
	
	double totalConjunctiveConditionCount = getTotalConjunctiveConditionCount_alternative();
	double conjunctiveRuleCount = getConjunctiveRuleCount_alternative();
	
	if (totalConjunctiveConditionCount <= 0) {
		throw std::runtime_error("Non-positive conjunctive condition count found while calculating average conjunctive conditions per rule");
	}
	
	if (conjunctiveRuleCount <= 0) {
		throw std::runtime_error("Non-positive conjunctive rule count found while calculating average conjunctive conditions per rule");
	}
	
	double returnValue = totalConjunctiveConditionCount / conjunctiveRuleCount;
	
	if (!std::isfinite(returnValue)) {
		std::cerr << std::endl << "ERROR: Invalid average conditions per conjunctive rule (alternative) computed" << std::endl;
	}
	
	return returnValue;
	
}







// ===================================================
// Accessor : bool rulesOverlap(const DataFileReader&, unsigned int, unsigned int) const
// Purpose  : Returns a boolean value indicating
//            whether the specified rules "overlap" or
//            not, where "overlapping" is defined as
//            occuring when one or more examples from
//            the data set are classified (matched) by
//            the same rule
// ===================================================

bool RuleSet::rulesOverlap(const DataFileReader& dataReader, unsigned int ruleIndex1, unsigned int ruleIndex2) const {
	
	for (unsigned int i = 0; i < dataReader.getRecordCount(); ++i) {
		
		if (((ruleList[ruleIndex1])->matches(dataReader.getRecord(i))) && ((ruleList[ruleIndex2])->matches(dataReader.getRecord(i)))) {
			return true;
		}
		
	}
	
	return false;
	
}

// *** Mutators ***

// ===================================================
// Mutator : void addRule(Rule&)
// Purpose : Add a copy of the supplied rule to the
//           rule set
// ===================================================

void RuleSet::addRule(const Rule& newRule) {
	
	// make a copy of the supplied rule and add it to the list
	ruleList.push_back(newRule.clone());
	
}

// ===================================================
// Mutator : void addConditionToRule(unsigned int, RuleCondition&)
// Purpose : Add a copy of the supplied rule to the
//           rule set
// ===================================================

void RuleSet::addConditionToRule(unsigned int ruleIndex, RuleCondition& newCondition) {
	
	ruleList[ruleIndex]->addCondition(newCondition);
	
}

// ===================================================
// Mutator : void removeRule(unsigned int)
// Purpose : Remove rule at specified rule index in
//           the rule set
// ===================================================

void RuleSet::removeRule(unsigned int ruleIndex) {
	
	delete ruleList[ruleIndex];
	ruleList.erase(ruleList.begin() + ruleIndex);
	
}

// ===================================================
// Mutator : void orderRules()
// Purpose : Sort the rule list, with fewer false
//           positives first
// ===================================================

void RuleSet::orderRules() {
	
	unbiasedSort(ruleList);
	
}

// *** Utility Functions ***

// ===================================================
// Utility : ostream& printWithFalsePositives(ostream&) const
// Purpose : Print rule set with false positive counts
// ===================================================

std::ostream& RuleSet::printWithFalsePositives(std::ostream& out) const {
	
	for (unsigned int i = 0; i < getRuleCount(); ++i) {
		
		ruleList[i]->printWithFalsePositives(out);
		out << std::endl;
		
		if (i < (getRuleCount() - 1)) {
			out << std::endl;
		}
		
	}
	
	return out;
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const RuleSet&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const RuleSet& ruleSet) {
	
	for (unsigned int i = 0; i < ruleSet.getRuleCount(); ++i) {
		
		out << *(ruleSet.ruleList[i]) << std::endl;
		
		if (i < (ruleSet.getRuleCount() - 1)) {
			out << std::endl;
		}
		
	}
	
	return out;
	
}

// ===================================================
// Operator : RuleSet& operator=(const RuleSet&)
// Purpose  : Assignment operator
// ===================================================

RuleSet& RuleSet::operator=(const RuleSet& rhs) {
	
	if (&rhs == this) {
		return *this;
	}
	
	ruleList.clear();
	
	for (unsigned int i = 0; i < rhs.getRuleCount(); ++i) {
		ruleList.push_back((rhs.ruleList[i])->clone());
	}
	
	return *this;
	
}
