#ifndef DATASTATS_H
#define DATASTATS_H

class DataStats {
	
	public:
		// constructor
		DataStats(double, double);
		
		// accessors
		double getTrainingError() const;
		double getTestError() const;
	
	private:
		double trainingClassificationError;
		double testClassificationError;
	
};

#endif
