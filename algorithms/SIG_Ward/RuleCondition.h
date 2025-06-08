#ifndef RULECONDITION_H
#define RULECONDITION_H

#include <string>
#include <iostream>
#include <stdexcept>

#include "DataPattern.h"

class RuleCondition {
	
	public:
		// constructor/destructor
		virtual ~RuleCondition();
		
		// accessors
		virtual bool matches(const DataPattern&) const = 0;
		virtual RuleCondition* clone() const = 0;
		virtual std::ostream& print(std::ostream&) const = 0;
		virtual double getTotalConditionCount() const = 0;
		virtual double getConjunctiveConditionCount() const = 0;
		virtual bool isDisjunctive() const = 0;
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const RuleCondition&);
	
};

// friend operators
std::ostream& operator<<(std::ostream&, const RuleCondition&);

#endif
