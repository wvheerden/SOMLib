#include "DataStats.h"

// *** Constructors ***

DataStats::DataStats(double _trainingClassificationError, double _testClassificationError)
: trainingClassificationError(_trainingClassificationError), testClassificationError(_testClassificationError) {
	
	;
	
}

// *** Accessors ***

double DataStats::getTrainingError() const {
	
	return trainingClassificationError;
	
}

double DataStats::getTestError() const {
	
	return testClassificationError;
	
}
