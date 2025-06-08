#ifndef DISJUNCTIVECONDITION_H
#define DISJUNCTIVECONDITION_H

#include <vector>

#include "RuleCondition.h"

class DisjunctiveCondition : public RuleCondition {
	
	public:
		// constructor/destructor
		DisjunctiveCondition();
		DisjunctiveCondition(const DisjunctiveCondition&);
		virtual ~DisjunctiveCondition();
		
		// accessors
		virtual bool matches(const DataPattern&) const;
		virtual RuleCondition* clone() const;
		virtual std::ostream& print(std::ostream&) const;
		virtual double getTotalConditionCount() const;
		virtual double getConjunctiveConditionCount() const;
		virtual bool isDisjunctive() const;
		
		// mutators
		void addAttributeCondition(RuleCondition&);
	
	private:
		std::vector<RuleCondition*> conditions;
};

#endif
