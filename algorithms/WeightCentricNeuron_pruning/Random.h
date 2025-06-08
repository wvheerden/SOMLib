#ifndef RANDOM_H
#define RANDOM_H

#include <stdexcept>
#include <gsl/gsl_rng.h>

class Random {
	
	private:
		// constructor
		Random();
		Random(const Random&) throw (std::runtime_error);
		
		// utility functions
		static unsigned long int random_seed();
	
	public:
		// destructor
		~Random();
		
		// accessors
		unsigned long int getNextInt(unsigned long int);
		
		// static accessors
		static Random* getInstance();
		
		// static utility functions
		static void reset();
	
	private:
		// data members
		gsl_rng* generator;
		
		// static data members
		static Random* instance;
	
};

#endif
