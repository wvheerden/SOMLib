#ifndef CN2MAPFILEWRITER_H
#define CN2MAPFILEWRITER_H

#include <stdexcept>

#include "MapFileWriter.h"

class DataFileReader;

class CN2MapFileWriter : public MapFileWriter {
	
	public:
	// constructor/destructor
		CN2MapFileWriter(std::string, SOMMap&, DataFileReader&) throw (std::runtime_error);
		virtual ~CN2MapFileWriter();
		
		// utility functions
		virtual void writeFile();
	
	protected:
		// utility functions
		virtual void writeHeader();
		virtual void writeRecord(const WeightVector&);
	
	private:
		
	
};

#endif
