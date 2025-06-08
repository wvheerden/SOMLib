#include <cfloat>
#include <stdexcept>
#include <cstring>

#include "outputLabels.h"
#include "DataFileReader.h"
#include "MapFileReader.h"
#include "SOMMap.h"
#include "MapFileWriter.h"
#include "CN2MapFileWriter.h"
#include "C4_5MapFileWriter.h"
#include "Random.h"

class DataFileReader;

// ===================================================
// Function: int main(int, char**)
// Purpose : Main program function
// ===================================================

int main(int argc, char** argv) {
	
	// check parameters
	if ((argc != 6) || ((strcmp(argv[4], "-cn2") != 0) && (strcmp(argv[4], "-c4.5") != 0))) {
		std::cerr << "Error: Invalid parameters" << std::endl << std::endl;
		std::cerr << "Usage: outputLabels [SOMFileName] [trainingDataFileName] [NamingFileName] -cn2 [outFile]" << std::endl;
		std::cerr << "       outputLabels [SOMFileName] [trainingDataFileName] [NamingFileName] -c4.5 [outFile]" << std::endl;
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
		DataFileReader dataReader(argv[2], argv[3]);
		std::cout << " Done" << std::endl;
		
		// create map reader and get map
		std::cout << "Reading map file...";
		MapFileReader mapReader(argv[1]);
		SOMMap* readMap = mapReader.getMap();
		std::cout << " Done" << std::endl;
		
		// cluster map
		std::cout << "Clustering map...";
		readMap->clusterMap();
		std::cout << " Done" << std::endl;
		
		// label map
		std::cout << "Labeling map vectors";
		readMap->labelMap(dataReader);
		std::cout << " (using " << readMap->getOptimalClusterCount() << " clusters)... Done" << std::endl;
		
		// output to file
		std::cout << "Outputting file...";
		MapFileWriter* writer;
		
		if (strcmp(argv[4], "-cn2") == 0) {
			writer = new CN2MapFileWriter(argv[5], *readMap, dataReader);
		} else {
			writer = new C4_5MapFileWriter(argv[5], *readMap, dataReader);
		}
		
		writer->writeFile();
		std::cout << " Done" << std::endl;
		
		delete readMap;
		delete writer;
		
	} catch (const std::runtime_error& e) {
		
		std::cout.flush();
		Random::reset();
		std::cerr << std::endl << std::endl << e.what() << std::endl << "Exiting..." << std::endl;
		return 1;
		
	}
	
	Random::reset();
	return 0;
	
}
