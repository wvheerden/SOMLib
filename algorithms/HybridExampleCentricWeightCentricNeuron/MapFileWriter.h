#ifndef MAPFILEWRITER_H
#define MAPFILEWRITER_H

#include <stdexcept>
#include <fstream>

class SOMMap;
class WeightVector;
class DataFileReader;

class MapFileWriter {
	
	public:
		// constructor/destructor
		MapFileWriter(std::string, SOMMap&, DataFileReader&) throw (std::runtime_error);
		virtual ~MapFileWriter();
		
		// utility functions
		virtual void writeFile();
	
	protected:
		// utility functions
		virtual void writeHeader() = 0;
		virtual void writeRecord(const WeightVector&) = 0;
		
		// data members
		std::ofstream outputWriter;
		SOMMap* map;
		DataFileReader* dataReader;
	
};

#endif
