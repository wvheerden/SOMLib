#include "CN2MapFileWriter.h"
#include "DataFileReader.h"
#include "WeightVector.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : CN2MapFileWriter(string, DataFileReader&)
// Purpose     : Construct CN2 map file writer using
//               specified map output file name and
//               data file reader
// ===================================================

CN2MapFileWriter::CN2MapFileWriter(std::string _mapOutputFileName, SOMMap& _map, DataFileReader& _dataReader) throw (std::runtime_error) :
MapFileWriter(_mapOutputFileName, _map, _dataReader) {
	
	;
	
}

// ===================================================
// Destructor : ~CN2MapFileWriter()
// Purpose    : De-allocates object resources
// ===================================================

CN2MapFileWriter::~CN2MapFileWriter() {
	
	;
	
}

// *** Utility Functions ***

// ===================================================
// Utility : void writeFile()
// Purpose : Write file contents to disc
// ===================================================

void CN2MapFileWriter::writeFile() {
	
	MapFileWriter::writeFile();
	
	outputWriter << "@";
	
}

// *** Protected Utility Functions ***

// ===================================================
// Utility : void writeHeader()
// Purpose : Output header part of file in CN2 format
// ===================================================

void CN2MapFileWriter::writeHeader() {
	
	outputWriter << "**ATTRIBUTE AND EXAMPLE FILE**" << std::endl;
	
	// write attribute labels to output data file
	for (unsigned int i = 0; i < dataReader->getAttributeLabelCount(); ++i) {
		outputWriter << dataReader->getAttributeLabel(i) << ": (FLOAT)" << std::endl;
	}
	
	outputWriter << "class: ";
	
	// write class labels to output data file
	for (unsigned int i = 0; i < dataReader->getClassLabelCount(); ++i) {
		outputWriter << dataReader->getClassLabel(i);
		
		if (i < (dataReader->getClassLabelCount() - 1)) {
			outputWriter << " ";
		}
		
	}
	
	outputWriter << ";" << std::endl << "@" << std::endl;
	
}

// ===================================================
// Utility : void writeRecord(const WeightVector&)
// Purpose : Output supplied weight vector in CN2
//           file format
// ===================================================

void CN2MapFileWriter::writeRecord(const WeightVector& weight) {
	
	weight.outputLabelled(outputWriter, "", "\t", ";\n");
	
}
