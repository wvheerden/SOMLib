#ifndef ATTRIBUTECONDITION_H
#define ATTRIBUTECONDITION_H

#include <string>
#include <stdexcept>

#include "RuleCondition.h"

class AttributeCondition : public RuleCondition {
	
	public:
		// constructor/destructor
		AttributeCondition(std::string, unsigned int, double);
		virtual ~AttributeCondition();
		
		// accessors
		std::string getAttributeLabel() const;
		unsigned int getAttributeNumber() const;
		double getThreshold() const;
		double getTotalConditionCount() const;
		double getConjunctiveConditionCount() const;
		virtual bool isDisjunctive() const;
		
		// operators
		virtual bool operator==(const AttributeCondition&);
	
	private:
		std::string attributeLabel;
		unsigned int attributeNumber;
		double threshold;
};

#endif
