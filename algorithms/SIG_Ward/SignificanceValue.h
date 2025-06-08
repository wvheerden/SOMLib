#ifndef SIGNIFICANCEVALUE_H
#define SIGNIFICANCEVALUE_H

#include <iostream>

class SignificanceValue {
	
	public:
		// constructor/destructor
		SignificanceValue(unsigned int, double);
		SignificanceValue(const SignificanceValue&);
		~SignificanceValue();
		
		// accessors
		unsigned int getAttributeNumber() const;
		double getValue() const;
		bool isMarked() const;
		
		// mutators
		void normalise(double);
		void mark(bool);
		
		// member operators
		SignificanceValue& operator=(const SignificanceValue&);
		bool operator==(const double&) const;
		bool operator!=(const SignificanceValue&) const;
		
		// friend operators
		friend std::ostream& operator<<(std::ostream&, const SignificanceValue&);
	
	private:
		unsigned int attributeNumber;
		double value;
		bool marked;
	
};

// friend operators
std::ostream& operator<<(std::ostream& out, const SignificanceValue& map);

// functors
bool sortComparison(SignificanceValue, SignificanceValue);
bool equal(const SignificanceValue&, const SignificanceValue&);

#endif
