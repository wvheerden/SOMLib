#include <cstring>
#include <sstream>

#include "MapFileReader.h"
#include "SOMMap.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : MapFileReader(string)
// Purpose     : Constructs map reader with given map
//               file name
// ===================================================

MapFileReader::MapFileReader(std::string _mapFileName) throw (std::runtime_error) :
mapReader(_mapFileName.c_str()) {
	
	// check for errors
	if (!mapReader) {
		std::string errorString("Error opening map file ");
		errorString += _mapFileName += "\" for reading";
		throw (std::runtime_error(errorString));
	}
	
}

// ===================================================
// Destructor : ~MapFileReader()
// Purpose    : De-allocates object resources
// ===================================================

MapFileReader::~MapFileReader() {
	
	mapReader.close();
	
}

// *** Accessors ***

// ===================================================
// Accessor : SOMMap* getMap(double)
// Purpose  : Returns reference to map representation
//            of read file
// ===================================================

SOMMap* MapFileReader::getMap(double overallDistanceStandardDeviationFraction) {
	
	// read file header
	unsigned int weightDimension;
	unsigned int mapWidth;
	unsigned int mapHeight;
	
	mapReader >> weightDimension;
	mapReader.ignore(6);
	mapReader >> mapWidth;
	mapReader >> mapHeight;
	mapReader.ignore(9, '\n');
	
	// initialise temporary map grid
	double*** tempGrid = new double**[mapHeight];
	
	for (unsigned int i = 0; i < mapHeight; ++i) {
		tempGrid[i] = new double*[mapWidth];
		for (unsigned int j = 0; j < mapWidth; ++j) {
			tempGrid[i][j] = new double[weightDimension];
		}
	}
	
	// read file body and create map
	readBody(tempGrid, weightDimension, mapWidth);
	SOMMap* map = new SOMMap(mapWidth, mapHeight, weightDimension, tempGrid, overallDistanceStandardDeviationFraction);
	
	// deallocate temporary map grid
	for (unsigned int i = 0; i < mapHeight; ++i) {
		for (unsigned int j = 0; j < mapWidth; ++j) {
			delete[] tempGrid[i][j];
		}
		delete[] tempGrid[i];
	}
	
	delete[] tempGrid;
	
	// return reference to map
	return map;
	
}

// *** Private Utility Functions ***

// ===================================================
// Function : void readBody(double***, int, int)
// Purpose  : Reads file body and creates map
// ===================================================

void MapFileReader::readBody(double*** targetGrid, int weightDimension, int mapWidth) {
	
	// initilise temporary storage
	char line[1001];
	int currentRow = 0;
	int currentColumn = 0;
	
	while (mapReader) {
		mapReader.getline(line, 1000);
		
		// skip blank lines
		if (strcmp(line, "") != 0) {
			
			// prepare line for tokenizing
			std::istringstream lineReader(line);
			
			// tokenize weight vector components into map
			int currentWeightComponent = 0;
			
			// add weight component to map
			while (currentWeightComponent < weightDimension) {
				lineReader >> targetGrid[currentRow][currentColumn][currentWeightComponent];
				++currentWeightComponent;
			}
			
			// handle row and column updates
			++currentColumn;
			if (currentColumn == mapWidth) {
				++currentRow;
				currentColumn = 0;
			}
			
		}
	}
	
}
