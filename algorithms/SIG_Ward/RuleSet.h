#ifndef RULESET_H
#define RULESET_H

#include <string>
#include <vector>

#include "Rule.h"
#include "DataFileReader.h"

class RuleCondition;

class RuleSet {
	
	public:
		// constructor/destructor
		RuleSet();
		RuleSet(const RuleSet&);
		~RuleSet();
		
		// accessors
		void evaluate(const DataFileReader&, double&, double&, double&) const;
		void calculateOrderingStats(const DataFileReader&) const;
		double getRuleCount() const;
		double getTotalConditionCount() const;
		double getAverageConditionsPerRule() const throw (std::runtime_error);
		
		double getConjunctiveRuleCount() const;
		double getTotalConjunctiveConditionCount() const;
		double getAverageConditionsPerConjunctiveRule() const throw (std::runtime_error);
		
		
		
		double getConjunctiveRuleCount_alternative() const;
		double getTotalConjunctiveConditionCount_alternative() const;
		double getAverageConditionsPerConjunctiveRule_alternative() const throw (std::runtime_error);
		
		
		
		bool rulesOverlap(const DataFileReader&, unsigned int, unsigned int) const;
		
		// mutators
		void addRule(const Rule&);
		void addConditionToRule(unsigned int, RuleCondition&);
		void removeRule(unsigned int);
		void orderRules();
		
		// utility functions
		std::ostream& printWithFalsePositives(std::ostream&) const;
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const RuleSet&);
		RuleSet& operator=(const RuleSet&);
	
	private:
		double getConjunctiveRuleCountForRule(unsigned int) const;
		double getConjunctiveConditionCountForRule(unsigned int) const;
		
		
		
		
		double getConjunctiveRuleCountForRule_alternative(unsigned int) const;
		double getConjunctiveConditionCountForRule_alternative(unsigned int) const;
		
		
		
		std::vector<Rule*> ruleList;
	
};

std::ostream& operator<<(std::ostream&, const RuleSet&);

#endif
