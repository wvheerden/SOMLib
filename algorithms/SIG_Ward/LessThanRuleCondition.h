#ifndef LESSTHANRULECONDITION_H
#define LESSTHANRULECONDITION_H

#include "AttributeCondition.h"

class LessThanRuleCondition : public AttributeCondition {
	
	public:
		// constructor/destructor
		LessThanRuleCondition(std::string, unsigned int, double);
		virtual ~LessThanRuleCondition();
		
		// accessors
		virtual bool matches(const DataPattern&) const;
		virtual RuleCondition* clone() const;
		virtual std::ostream& print(std::ostream&) const;

	
};

#endif
