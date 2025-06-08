#ifndef DATAFILEREADER_H
#define DATAFILEREADER_H

#include <fstream>
#include <stdexcept>
#include <vector>

class DataPattern;

class DataFileReader {
	
	public:
		// constructor
		DataFileReader(char*, char*) throw (std::runtime_error);
		~DataFileReader();
		
		// accessors
		unsigned int getAttributeLabelCount();
		std::string getAttributeLabel(unsigned int) throw (std::runtime_error);
		unsigned int getClassLabelCount();
		std::string getClassLabel(unsigned int) throw (std::runtime_error);
		unsigned int getRecordCount();
		DataPattern getRecord(unsigned int) throw (std::runtime_error);
		
		// operators
		friend std::ostream& operator<<(std::ostream&, const DataFileReader&);
	
	private:
		// utility functions
		void readMetaData() throw (std::runtime_error);
		void buildDataSet() throw (std::runtime_error);
		
		// data members
		std::ifstream dataReader;
		std::ifstream namesReader;
		std::vector<std::string> attributeLabels;
		std::vector<std::string> classLabels;
		std::vector<DataPattern*> dataSet;
	
};

// friend operators
std::ostream& operator<<(std::ostream&, const DataFileReader&);

#endif
