// ./classify iris.11.0.map.out iris.data.0.train iris.data.0.test iris.names a b

#include <cfloat>
#include <stdexcept>

#include "classify.h"
#include "DataFileReader.h"
#include "MapFileReader.h"
#include "SOMMap.h"
#include "Random.h"

class DataFileReader;

// ===================================================
// Function: int main(int, char**)
// Purpose : Main program function
// ===================================================

int main(int argc, char** argv) {
	
	// check parameters
	if (argc != 8) {
		std::cerr << "Error: Invalid parameters" << std::endl << std::endl;
		std::cerr << "Usage: classify [SOMFileName] [trainingDataFileName] [testDataFileName] [NamingFileName] [accuracyOutFile] [errorOutFile] [standardDeviationFraction]" << std::endl;
		return 1;
	}
	
	// output admin
	std::cout.precision(DBL_DIG);
	std::cout.setf(std::ios::fixed);
	std::cerr.precision(DBL_DIG);
	std::cerr.setf(std::ios::fixed);
	
	try {
		// read data file
		std::cout << "Reading data files...";
		DataFileReader trainingDataReader(argv[2], argv[4]);
		DataFileReader testDataReader(argv[3], argv[4]);
		std::cout << " Done" << std::endl;
		
		// create map reader and get map
		std::cout << "Reading map file and pruning interpolating units...";
		MapFileReader mapReader(argv[1]);
		SOMMap* readMap = mapReader.getMap(atof(argv[7]));
		std::cout << " Done" << std::endl;
		
		// cluster map
		std::cout << "Clustering map...";
		readMap->clusterMap();
		std::cout << " Done" << std::endl;
		
		// label map
		std::cout << "Labeling map vectors";
		readMap->labelMap(trainingDataReader);
		std::cout << " (using " << readMap->getOptimalClusterCount() << " clusters)... Done" << std::endl;
		
		// output to file
		std::ofstream outputAccuracyWriter(argv[5], std::ios_base::app);
		outputAccuracyWriter.precision(15);
		outputAccuracyWriter.setf(std::ios::fixed);
		
		std::ofstream outputErrorWriter(argv[6], std::ios_base::app);
		outputErrorWriter.precision(15);
		outputErrorWriter.setf(std::ios::fixed);
		
		readMap->classifyTrainingData(trainingDataReader);
		readMap->classifyTestData(testDataReader);
		
		outputAccuracyWriter << readMap->getTrainingAccuracy() << "\t" << "0.000000000000000"                      << "\t" << "0.000000000000000"                     << "\t" << readMap->getTestAccuracy() << "\t" << "0.000000000000000"                  << "\t" << "0.000000000000000"                 << "\t" << readMap->getUnlabeledWeights() << "\t" << readMap->getUnlabeledWeightPercentage() << "\t" << readMap->getPrunedNeuronPercentage() << std::endl;
		outputAccuracyWriter.close();
		outputErrorWriter    << readMap->getTrainingError()    << "\t" << readMap->getTrainingMisclassifiedError() << "\t" << readMap->getTrainingUnclassifiedError() << "\t" << readMap->getTestError()    << "\t" << readMap->getTestMisclassifiedError() << "\t" << readMap->getTestUnclassifiedError() << "\t" << readMap->getUnlabeledWeights() << "\t" << readMap->getUnlabeledWeightPercentage() << "\t" << readMap->getPrunedNeuronPercentage() << std::endl;
		outputErrorWriter.close();
		
		delete readMap;
		
	} catch (const std::runtime_error& e) {
		
		std::cout.flush();
		Random::reset();
		std::cerr << std::endl << std::endl << e.what() << std::endl << "Exiting..." << std::endl;
		return 1;
		
	}
	
	Random::reset();
	return 0;
	
}
