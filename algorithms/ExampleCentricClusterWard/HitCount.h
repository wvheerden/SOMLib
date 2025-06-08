#ifndef HITCOUNT_H
#define HITCOUNT_H

#include <string>
#include <iostream>

class HitCount {
	
	public:
		// constructor/destructor
		HitCount(std::string&);
		HitCount(const HitCount&);
		~HitCount();
		
		// mutators
		void incrementCount();
		void incrementCount(unsigned int);
		
		// accessors
		std::string getLabel() const;
		unsigned int getCount() const;
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const HitCount&);
	
	private:
		// data members
		std::string label;
		unsigned int count;
};

// friend operators
std::ostream& operator<<(std::ostream&, const HitCount&);

#endif
