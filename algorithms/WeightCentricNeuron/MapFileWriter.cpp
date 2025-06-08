#include "MapFileWriter.h"
#include "SOMMap.h"
#include "WeightVector.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : MapFileWriter(string, SOMMap&, DataFileReader&)
// Purpose     : Construct map file writer using
//               specified map output file name, SOM
//               map and data file reader
// ===================================================

MapFileWriter::MapFileWriter(std::string _mapOutputFileName, SOMMap& _map, DataFileReader& _dataReader) throw (std::runtime_error) :
outputWriter(_mapOutputFileName.c_str()), map(&_map), dataReader(&_dataReader) {
	
	if (!outputWriter) {
		std::string errorString("Error opening output data file ");
		errorString += _mapOutputFileName += "\" for writing";
		throw (std::runtime_error(errorString));
	}
	
	outputWriter.precision(15);
	outputWriter.setf(std::ios::fixed);
	
}

// ===================================================
// Destructor : ~MapFileWriter()
// Purpose    : De-allocates object resources
// ===================================================

MapFileWriter::~MapFileWriter() {
	
	outputWriter.close();
	
}

// *** Utility Functions ***

// ===================================================
// Utility : void writeFile()
// Purpose : Write file contents to disc
// ===================================================

void MapFileWriter::writeFile() {
	
	writeHeader();
	
	// output each weight vector
	for (unsigned int i = 0; i < map->getHeight(); ++i) {
		for (unsigned int j = 0; j < map->getWidth(); ++j) {
			writeRecord(map->getWeightVector(i, j));
		}
	}
	
}
