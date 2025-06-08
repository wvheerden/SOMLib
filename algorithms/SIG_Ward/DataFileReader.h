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
		unsigned int getAttributeCount() const;
		std::string getAttributeLabel(unsigned int) const throw (std::runtime_error);
		unsigned int getClassCount() const;
		std::string getClassLabel(unsigned int) const throw (std::runtime_error);
		unsigned int getClassFrequency(unsigned int) const throw (std::runtime_error);
		unsigned int getRecordCount() const;
		DataPattern getRecord(unsigned int) const throw (std::runtime_error);
		
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
		std::vector<unsigned int> classFrequencies;
		std::vector<DataPattern*> dataSet;
	
};

// friend operators
std::ostream& operator<<(std::ostream&, const DataFileReader&);

#endif
