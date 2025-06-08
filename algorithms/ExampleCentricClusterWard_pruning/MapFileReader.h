#ifndef MAPFILEREADER_H
#define MAPFILEREADER_H

#include <string>
#include <fstream>
#include <stdexcept>

class SOMMap;

class MapFileReader {
	
	public:
		// constructors/destructors
		MapFileReader(std::string) throw (std::runtime_error);
		MapFileReader(const MapFileReader&);
		~MapFileReader();
		
		// accessors
		SOMMap* getMap(double);
	
	private:
		// utility functions
		void readBody(double***, int, int);
		
		// data Members
		std::ifstream mapReader;
	
};

#endif
