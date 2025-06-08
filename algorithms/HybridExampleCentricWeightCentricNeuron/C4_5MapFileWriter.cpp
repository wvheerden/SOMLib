#include "C4_5MapFileWriter.h"
#include "DataFileReader.h"
#include "WeightVector.h"

// *** Constructors and Destructors ***

// ===================================================
// Constructor : C4_5MapFileWriter(string, string, DataFileReader&)
// Purpose     : Construct C4.5 map file writer using
//               specified map output file name and
//               names file output name
// ===================================================

C4_5MapFileWriter::C4_5MapFileWriter(std::string _mapOutputFileName, SOMMap& _map, DataFileReader& _dataReader) throw (std::runtime_error) :
MapFileWriter(_mapOutputFileName, _map, _dataReader) {
	
	;
	
}

// ===================================================
// Destructor : ~C4_5MapFileWriter()
// Purpose    : De-allocates object resources
// ===================================================

C4_5MapFileWriter::~C4_5MapFileWriter() {
	
	;
	
}

// *** Protected Utility Functions ***

// ===================================================
// Utility : void writeHeader()
// Purpose : Output header part of file in C4.5 format
// ===================================================

void C4_5MapFileWriter::writeHeader() {
	
	;
	
}

// ===================================================
// Utility : void writeRecord(const WeightVector&)
// Purpose : Output supplied weight vector in C4.5
//           file format
// ===================================================

void C4_5MapFileWriter::writeRecord(const WeightVector& weight) {
	
	weight.outputLabelled(outputWriter, "", ",", ".\n");
	
}
