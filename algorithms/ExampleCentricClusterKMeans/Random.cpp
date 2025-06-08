#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <ctime>

#include "Random.h"

Random* Random::instance = 0;

// *** Constructor and Destructor ***

// ===================================================
// Constructor : Random()
// Purpose     : Default random number generator
//               constructor (private to allow only
//               singleton instantiation)
// ===================================================

Random::Random() {
	
	// initialise random number generator to use Mersenne Twister generator
	generator = gsl_rng_alloc(gsl_rng_mt19937);
	gsl_rng_set(generator, time(NULL));
	
}

// ===================================================
// Constructor : Random(const Random&)
// Purpose     : Copy constructor (private to forbid
//               copying)
// ===================================================

Random::Random(const Random& source) throw (std::runtime_error) {
	
	throw std::runtime_error("Attempt to copy Random");
	
}

// ===================================================
// Destructor : ~Random()
// Purpose    : De-allocates object resources
// ===================================================

Random::~Random() {
	
	gsl_rng_free(generator);
	
}

// *** Utility Functions ***

// ===================================================
// Utility function : unsigned long int random_seed()
// Purpose          : Generate a random seed from
//                    /dev/null (if possible)
//
//                    UNUSED DUE TO SPEED ISSUES
// ===================================================

unsigned long int Random::random_seed() {
	
	unsigned int seed;
	struct timeval tv;
	FILE *devrandom;
	
	if ((devrandom = fopen("/dev/random","r")) == NULL) {
		gettimeofday(&tv,0);
		seed = tv.tv_sec + tv.tv_usec;
		std::cout << " (seed " << seed << " from gettimeofday) ";
	} else {
		if (!fread(&seed,sizeof(seed),1,devrandom)) {
			std::cout << " (failed: seed 0) ";
			fclose(devrandom);
			seed = 0;
		}
		
		std::cout << " (seed " << seed << " from /dev/random) ";
		fclose(devrandom);
	}
	
	return(seed);
	
}

// *** Accessors ***

// ===================================================
// Accessor : unsigned long int getNextInt(unsigned long int)
// Purpose  : Return next random integer inclusively
//            between 0 and (range - 1)
// ===================================================

unsigned long int Random::getNextInt(unsigned long int range) {
	
	return gsl_rng_uniform_int(generator, range);
	
}

// *** Static Accessors ***

// ===================================================
// Accessor : static Random* getInstance()
// Purpose  : Return singleton instance
// ===================================================

Random* Random::getInstance() {
	
	if (Random::instance == 0) {
		Random::instance = new Random();
	}
	
	return instance;
	
}

// *** Static Utitliy Functions ***

// ===================================================
// Utility Function : static void reset()
// Purpose          : Resets random number generator
//                    thus allowing a new instance to
//                    be created
// ===================================================

void Random::reset() {
	
	delete instance;
	
}
