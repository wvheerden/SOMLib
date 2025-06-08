#include <cstring>
#include <cstdlib>

#include "DataFileReader.h"
#include "DataPattern.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : DataFileReader(char*, char*)
// Purpose     : Constructs data file reader with
//               given data file and naming file names
// ===================================================

DataFileReader::DataFileReader(char* _dataFileName, char* _namingFileName) throw (std::runtime_error) :
dataReader(_dataFileName), namesReader(_namingFileName) {
	
	// check for errors
	if (!dataReader) {
		char errorString[100] = "Error opening data file ";
		strcat(errorString, _dataFileName);
		
		dataReader.close();
		namesReader.close();
		throw std::runtime_error(errorString);
	}
	
	if (!namesReader) {
		char errorString[100] = "Error opening naming file ";
		strcat(errorString, _namingFileName);
		
		dataReader.close();
		namesReader.close();
		throw std::runtime_error(errorString);
	}
	
	readMetaData();
	buildDataSet();
	
}

// ===================================================
// Destructor : ~DataFileReader()
// Purpose    : De-allocates object resources
// ===================================================

DataFileReader::~DataFileReader() {
	
	dataReader.close();
	namesReader.close();
	
	for (unsigned int i = 0; i < dataSet.size(); ++i) {
		delete dataSet[i];
	}
	
}

// *** Accessors ***

// ===================================================
// Accessor : unsigned int getAttributeCount()
// Purpose  : Return number of attributes
// ===================================================

unsigned int DataFileReader::getAttributeCount() const {
	
	return attributeLabels.size();
	
}

// ===================================================
// Accessor : string getAttributeLabel(unsigned int)
// Purpose  : Return copy of specified attribute label
// ===================================================

std::string DataFileReader::getAttributeLabel(unsigned int labelIndex) const throw (std::runtime_error) {
	
	if (labelIndex >= getAttributeCount()) {
		throw std::runtime_error("Invalid index specified for retrieval of attribute label");
	}
	
	return attributeLabels[labelIndex];
	
}

// ===================================================
// Accessor : unsigned int getClassCount()
// Purpose  : Return number of classes
// ===================================================

unsigned int DataFileReader::getClassCount() const {
	
	return classLabels.size();
	
}

// ===================================================
// Accessor : string getClassLabel(unsigned int)
// Purpose  : Return copy of specified class label
// ===================================================

std::string DataFileReader::getClassLabel(unsigned int labelIndex) const throw (std::runtime_error) {
	
	if (labelIndex >= getClassCount()) {
		throw std::runtime_error("Invalid index specified for retrieval of class label");
	}
	
	return classLabels[labelIndex];
	
}

// ===================================================
// Accessor : unsigned int getClassFrequency(unsigned int)
// Purpose  : Return specified class frequency count
// ===================================================

unsigned int DataFileReader::getClassFrequency(unsigned int labelIndex) const throw (std::runtime_error) {
	
	if (labelIndex >= getClassCount()) {
		throw std::runtime_error("Invalid index specified for retrieval of class frequency");
	}
	
/*
if (labelIndex == 0)
	return 60;
if (labelIndex == 1)
	return 60;
if (labelIndex == 2)
	return 50;
return 0;
*/
	return classFrequencies[labelIndex];
	
}

// ===================================================
// Accessor : unsigned int getRecordCount()
// Purpose  : Return record count of internal data set
// ===================================================

unsigned int DataFileReader::getRecordCount() const {
	
	return dataSet.size();
	
}

// ===================================================
// Accessor : DataPattern getRecord(unsigned int)
// Purpose  : Return copy of specified data pattern
// ===================================================

DataPattern DataFileReader::getRecord(unsigned int recordIndex) const throw (std::runtime_error) {
	
	if (recordIndex >= getRecordCount()) {
		throw std::runtime_error("Invalid index specified for retrieval of data record");
	}
	
	return *(dataSet[recordIndex]);
	
}

// *** Utility Functions ***

// ===================================================
// Utility Function : void readMetaData()
// Purpose          : Reads data file meta data from
//                    names file
// ===================================================

void DataFileReader::readMetaData() throw (std::runtime_error) {
	
	char line[1001];
	
	// get and process attribute label line
	namesReader.getline(line, 1000);
	
	if (strlen(line) == 0) {
		dataReader.close();
		namesReader.close();
		throw std::runtime_error("Error: Expected attribute label list not found");
	}
	
	char* token = strtok(line, " ");
	
	while (token != 0) {
		std::string newAttributeLabel(token);
		attributeLabels.push_back(newAttributeLabel);
		token = strtok(0, " ");
	}
	
	// get and process class label line
	namesReader.getline(line, 1000);
	
	if (strlen(line) == 0) {
		dataReader.close();
		namesReader.close();
		throw std::runtime_error("Error: Expected class label list not found");
	}
	
	token = strtok(line, " ");
	
	while (token != 0) {
		std::string newClassLabel(token);
		classLabels.push_back(newClassLabel);
		classFrequencies.push_back(0);
		token = strtok(0, " ");
	}
	
}

// ===================================================
// Utility Function : void buildDataSet()
// Purpose          : Reads data file and constructs
//                    data set from it
// ===================================================

void DataFileReader::buildDataSet() throw (std::runtime_error) {
	
	char line[1001];
	
	// read and check vector dimensionality
	dataReader.getline(line, 1000);
	
	if (((unsigned int) atoi(line)) != getAttributeCount()) {
		dataReader.close();
		namesReader.close();
		throw std::runtime_error("Error: Data set dimension does not match names file dimension");
	}
	
	// read and tokenise data records
	dataReader.getline(line, 1000);
	
	while (dataReader) {
		std::vector<double> newPatternValues;
		unsigned int newPatternIndex;
		
		unsigned int numTokens = 0;
		char* token = strtok(line, " ");
		
		// get all data vector values
		while ((token != 0) && (numTokens != getAttributeCount())) {
			++numTokens;
			newPatternValues.push_back(atof(token));
			token = strtok(0, " ");
		}
		
		// validate pattern classification
		bool match = false;
		
		for (unsigned int i = 0; i < getClassCount(); ++i) {
			
			if (classLabels[i] == token) {
				// record a match and update appropriate class frequency count
				match = true;
				++(classFrequencies[i]);
				newPatternIndex = i;
				break;
			}
			
		}
		
		if (!match) {
			char errorString[100] = "Error: Invalid attribute label ";
			strcat(errorString, token);
			strcat(errorString, " found");
			throw (std::runtime_error(errorString));
		}
		
		// build new pattern and add to data set
		DataPattern* newPattern = new DataPattern(newPatternValues, token, newPatternIndex);
		dataSet.push_back(newPattern);
		
		dataReader.getline(line, 1000);
	}
	
}

// *** Friend Operators ***

// ===================================================
// Operator : ostream& operator<<(ostream&, const DataFileReader&)
// Purpose  : Stream insertion operator
// ===================================================

std::ostream& operator<<(std::ostream& out, const DataFileReader& reader) {
	
	out << "Data set:" << std::endl << "Attributes{";
	
	// output attribute labels
	for (unsigned int i = 0; i < reader.getAttributeCount(); ++i) {
		
		out << reader.attributeLabels[i];
		
		if (i != (reader.getAttributeCount() - 1)) {
			out << "; ";
		}
	}
	
	out << "}" << std::endl << "Classes{";
	
	// output class labels
	for (unsigned int i = 0; i < reader.getClassCount(); ++i) {
		
		out << reader.classLabels[i];
		
		if (i != (reader.getClassCount() - 1)) {
			out << "; ";
		}
		
	}
	
	out << "}" << std::endl;
	
	// output data patterns
	for (unsigned int i = 0; i < reader.dataSet.size(); ++i) {
		
		out << *(reader.dataSet[i]);
		
		if (i != (reader.dataSet.size() - 1)) {
			out << std::endl;
		}
		
	}
	
	return out;
	
}
