#ifndef GREATERTHANRULECONDITION_H
#define GREATERTHANRULECONDITION_H

#include "AttributeCondition.h"

class GreaterThanRuleCondition : public AttributeCondition {
	
	public:
		// constructor/destructor
		GreaterThanRuleCondition(std::string, unsigned int, double);
		virtual ~GreaterThanRuleCondition();
		
		// accessors
		virtual bool matches(const DataPattern&) const;
		virtual RuleCondition* clone() const;
		virtual std::ostream& print(std::ostream&) const;
	
};

#endif
