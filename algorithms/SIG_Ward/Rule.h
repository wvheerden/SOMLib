#ifndef RULE_H
#define RULE_H

#include <string>
#include <iostream>

#include "DataPattern.h"
#include "RuleCondition.h"

class Rule {
	
	public:
		// constructor/destructor
		Rule(std::string);
		Rule(const Rule&);
		virtual ~Rule();
		
		// mutators
		void incrementFalsePositivesCount();
		virtual void addCondition(RuleCondition& newCondition);
		
		// accessors
		std::string getPredictedClassLabel() const;
		unsigned int getFalsePositivesCount() const;
		Rule* clone() const;
		unsigned int getTotalConditionCount() const;
		unsigned int getRuleConditionCount() const;
		const RuleCondition& getCondition(unsigned int) const throw (std::runtime_error);
		bool matches(const DataPattern&) const;
		std::ostream& print(std::ostream&) const;
		
		// utlity functions
		std::ostream& printWithFalsePositives(std::ostream&) const;
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const Rule&);
	
	private:
		std::vector<RuleCondition*> conditions;
		std::string predictedClassLabel;
		unsigned int falsePositivesCount;
	
};

// friend operators
std::ostream& operator<<(std::ostream&, const Rule&);

// functors
bool sortComparison(Rule*, Rule*);
bool equal(const Rule*, const Rule*);

#endif
