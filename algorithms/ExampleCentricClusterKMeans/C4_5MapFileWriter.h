#ifndef C4_5MAPFILEWRITER_H
#define C4_5MAPFILEWRITER_H

#include <stdexcept>
#include <string>

#include "MapFileWriter.h"

class DataFileReader;

class C4_5MapFileWriter : public MapFileWriter {
	
	public:
		// constructor/destructor
		C4_5MapFileWriter(std::string, SOMMap&, DataFileReader&) throw (std::runtime_error);
		virtual ~C4_5MapFileWriter();
	
	protected:
		// utility functions
		virtual void writeHeader();
		virtual void writeRecord(const WeightVector&);
	
};

#endif
