#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cfloat>
#include <gsl/gsl_rng.h>

using namespace std;

double calcPercentageUnlabeled(unsigned int mapDim, double unlabeledCount)
{
	return (unlabeledCount / (mapDim * mapDim)) * 100.0;
}

class SimulationResult {
	
	public:
		
		SimulationResult()
		{
			recordNumber = 0;
			
			dimension = 0.0;
			learningRate = 0.0;
			learningRateDecay = 0.0;
			kernelWidth = 0.0;
			kernelWidthDecay = 0.0;
			meanTrainingError = 0.0;
			
			standardDeviationTrainingError = 0.0;
			meanTrainingMisclassifiedError = 0.0;
			standardDeviationTrainingMisclassifiedError = 0.0;
			meanTrainingUnclassifiedError = 0.0;
			standardDeviationTrainingUnclassifiedError = 0.0;
			meanGeneralizationError = 0.0;
			
			standardDeviationGeneralizationError = 0.0;
			meanGeneralizationMisclassifiedError = 0.0;
			standardDeviationGeneralizationMisclassifiedError = 0.0;
			meanGeneralizationUnclassifiedError = 0.0;
			standardDeviationGeneralizationUnclassifiedError = 0.0;
			meanUnlabeledCount = 0.0;
			standardDeviationUnlabeledCount = 0.0;
			meanUnlabeledPercentage = 0.0;
			standardDeviationUnlabeledPercentage = 0.0;
		}
		
		void setRecordNumber(unsigned int _recordNumber)
		{
			recordNumber = _recordNumber;
		}
		
		void setDimension(double _dimension)
		{
			dimension = _dimension;
		}
		
		void setLearningRate(double _learningRate)
		{
			learningRate = _learningRate;
		}
		
		void setLearningRateDecay(double _learningRateDecay)
		{
			learningRateDecay = _learningRateDecay;
		}
		
		void setKernelWidth(double _kernelWidth)
		{
			kernelWidth = _kernelWidth;
		}
		
		void setKernelWidthDecay(double _kernelWidthDecay)
		{
			kernelWidthDecay = _kernelWidthDecay;
		}
		
		void setMeanTrainingError (double _meanTrainingError)
		{
			meanTrainingError = _meanTrainingError;
		}
		
		void setStandardDeviationTrainingError(double _standardDeviationTrainingError)
		{
			standardDeviationTrainingError = _standardDeviationTrainingError;
		}
		
		void setMeanTrainingMisclassifiedError(double _meanTrainingMisclassifiedError)
		{
			meanTrainingMisclassifiedError = _meanTrainingMisclassifiedError;
		}
		
		void setStandardDeviationTrainingMisclassifiedError(double _standardDeviationTrainingMisclassifiedError)
		{
			standardDeviationTrainingMisclassifiedError = _standardDeviationTrainingMisclassifiedError;
		}
		
		void setMeanTrainingUnclassifiedError(double _meanTrainingUnclassifiedError)
		{
			meanTrainingUnclassifiedError = _meanTrainingUnclassifiedError;
		}
		
		void setStandardDeviationTrainingUnclassifiedError(double _standardDeviationTrainingUnclassifiedError)
		{
			standardDeviationTrainingUnclassifiedError = _standardDeviationTrainingUnclassifiedError;
		}
		
		void setMeanGeneralizationError(double _meanGeneralizationError)
		{
			meanGeneralizationError = _meanGeneralizationError;
			
			if (meanGeneralizationError > maxMeanGeneralizationError)
			{
				SimulationResult::maxMeanGeneralizationError = meanGeneralizationError;
			}
			
			if (meanGeneralizationError < minMeanGeneralizationError)
			{
				SimulationResult::minMeanGeneralizationError = meanGeneralizationError;
			}
		}
		
		void setStandardDeviationGeneralizationError(double _standardDeviationGeneralizationError)
		{
			standardDeviationGeneralizationError = _standardDeviationGeneralizationError;
		}
		
		void setMeanGeneralizationMisclassifiedError(double _meanGeneralizationMisclassifiedError)
		{
			meanGeneralizationMisclassifiedError = _meanGeneralizationMisclassifiedError;
		}
		
		void setStandardDeviationGeneralizationMisclassifiedError(double _standardDeviationGeneralizationMisclassifiedError)
		{
			standardDeviationGeneralizationMisclassifiedError = _standardDeviationGeneralizationMisclassifiedError;
		}
		
		void setMeanGeneralizationUnclassifiedError(double _meanGeneralizationUnclassifiedError)
		{
			meanGeneralizationUnclassifiedError = _meanGeneralizationUnclassifiedError;
		}
		
		void setStandardDeviationGeneralizationUnclassifiedError(double _standardDeviationGeneralizationUnclassifiedError)
		{
			standardDeviationGeneralizationUnclassifiedError = _standardDeviationGeneralizationUnclassifiedError;
		}
		
		void setMeanUnlabeledCount(double _meanUnlabeledCount)
		{
			meanUnlabeledCount = _meanUnlabeledCount;
		}
		
		void setStandardDeviationUnlabeledCount(double _standardDeviationUnlabeledCount)
		{
			standardDeviationUnlabeledCount = _standardDeviationUnlabeledCount;
		}
		
		void setMeanUnlabeledPercentage(double _meanUnlabeledPercentage)
		{
			meanUnlabeledPercentage = _meanUnlabeledPercentage;
		}

		void setStandardDeviationUnlabeledPercentage(double _standardDeviationUnlabeledPercentage)
		{
			standardDeviationUnlabeledPercentage = _standardDeviationUnlabeledPercentage;
		}
		
		double getDimension() const
		{
			return dimension;
		}
		
		double getMeanTrainingError() const
		{
			return meanTrainingError;
		}
		
		double getStandardDeviationTrainingError() const
		{
			return standardDeviationTrainingError;
		}
		
		double getMeanGeneralizationError() const
		{
			return meanGeneralizationError;
		}
		
		double getStandardDeviationGeneralizationError() const
		{
			return standardDeviationGeneralizationError;
		}
		
		double getMeanUnlabeledCount() const
		{
			return meanUnlabeledCount;
		}
		
		void printTrainingError(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os << dimension << setprecision(14) << fixed << "\t" << learningRate << "\t" << learningRateDecay
			   << "\t" << kernelWidth << "\t" << kernelWidthDecay << "\t" << meanTrainingError;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl;
			}
		}
		
		double scale(double value, double maxValue, double minValue)
		{
			return (value - minValue) / (maxValue - minValue);
		}
		
		void printGeneralizationError(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os  << setprecision(14) << fixed;
			os << "0 " << scale(dimension, SimulationResult::maxDimension, SimulationResult::minDimension) << " " << 0 << endl;
			os << "1 " << scale(learningRate, SimulationResult::maxLearningRate, SimulationResult::minLearningRate) << " " << 1 << endl;
			os << "2 " << scale(learningRateDecay, SimulationResult::maxLearningRateDecay, SimulationResult::minLearningRateDecay) << " " << 0 << endl;
			os << "3 " << scale(kernelWidth, SimulationResult::maxKernelWidth, SimulationResult::minKernelWidth) << " " << 1 << endl;
			os << "4 " << scale(kernelWidthDecay, SimulationResult::maxKernelWidthDecay, SimulationResult::minKernelWidthDecay) << " " << 0 << endl;
			os << "5 " << scale(meanGeneralizationError, SimulationResult::maxMeanGeneralizationError, SimulationResult::minMeanGeneralizationError) << " " << 1;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printUnlabeledCountPercentage(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os << dimension << setprecision(14) << fixed << "\t" << learningRate << "\t" << learningRateDecay
			   << "\t" << kernelWidth << "\t" << kernelWidthDecay << "\t" << calcPercentageUnlabeled(dimension, meanUnlabeledCount);
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl;
			}
		}
		
		void printAll(ostream& os)
		{
			os << "dimension\t" << "learningRate\t" << "learningRateDecay\t" << "kernelWidth\t" << "kernelWidthDecay\t"
			   << "meanTrainingError\t" << "standardDeviationTrainingError\t" << "meanGeneralizationError\t"
			   << "standardDeviationGeneralizationError\t" << "meanUnlabeledCount\t" << "standardDeviationUnlabeledCount" << endl;
			
			os << dimension << setprecision(14) << fixed << "\t" << learningRate << "\t" << learningRateDecay
			   << "\t" << kernelWidth << "\t" << kernelWidthDecay << "\t" << meanTrainingError
			   << "\t" << standardDeviationTrainingError << "\t" << meanGeneralizationError
			   << "\t" << standardDeviationGeneralizationError << "\t" << meanUnlabeledCount
			   << "\t" << standardDeviationUnlabeledCount;
		}
		
		friend ostream& operator<<(ostream& ios, const SimulationResult& result);
	
	public:
		unsigned int recordNumber;
		
		double dimension;
		static double maxDimension;
		static double minDimension;
		
		double learningRate;
		static double maxLearningRate;
		static double minLearningRate;
		
		double learningRateDecay;
		static double maxLearningRateDecay;
		static double minLearningRateDecay;
		
		double kernelWidth;
		static double maxKernelWidth;
		static double minKernelWidth;
		
		double kernelWidthDecay;
		static double maxKernelWidthDecay;
		static double minKernelWidthDecay;
		
		double meanTrainingError;
		
		double standardDeviationTrainingError;
		double meanTrainingMisclassifiedError;
		double standardDeviationTrainingMisclassifiedError;
		double meanTrainingUnclassifiedError;
		double standardDeviationTrainingUnclassifiedError;
		
		double meanGeneralizationError;
		static double maxMeanGeneralizationError;
		static double minMeanGeneralizationError;
		
		double standardDeviationGeneralizationError;
		double meanGeneralizationMisclassifiedError;
		double standardDeviationGeneralizationMisclassifiedError;
		double meanGeneralizationUnclassifiedError;
		double standardDeviationGeneralizationUnclassifiedError;
		double meanUnlabeledCount;
		double standardDeviationUnlabeledCount;
		double meanUnlabeledPercentage;
		double standardDeviationUnlabeledPercentage;
	
};

double SimulationResult::maxDimension = -DBL_MAX;
double SimulationResult::minDimension = DBL_MAX;
double SimulationResult::maxLearningRate = -DBL_MAX;
double SimulationResult::minLearningRate = DBL_MAX;
double SimulationResult::maxLearningRateDecay = -DBL_MAX;
double SimulationResult::minLearningRateDecay = DBL_MAX;
double SimulationResult::maxKernelWidth = -DBL_MAX;
double SimulationResult::minKernelWidth = DBL_MAX;
double SimulationResult::maxKernelWidthDecay = -DBL_MAX;
double SimulationResult::minKernelWidthDecay = DBL_MAX;
double SimulationResult::maxMeanGeneralizationError = -DBL_MAX;
double SimulationResult::minMeanGeneralizationError = DBL_MAX;

bool generalizationErrorSortPredicate(const SimulationResult& result1, const SimulationResult& result2)
{
	if (result1.getMeanGeneralizationError() < result2.getMeanGeneralizationError())
	{
		return true;
	}
	
	if (result1.getMeanGeneralizationError() == result2.getMeanGeneralizationError())
	{
		if (result1.getStandardDeviationGeneralizationError() < result2.getStandardDeviationGeneralizationError())
		{
			return true;
		}
		
		if (result1.getStandardDeviationGeneralizationError() == result2.getStandardDeviationGeneralizationError())
		{
			if (result1.getMeanTrainingError() < result2.getMeanTrainingError())
			{
				return true;
			}
			
			if (result1.getMeanTrainingError() == result2.getMeanTrainingError())
			{
				if (result1.getStandardDeviationTrainingError() < result2.getStandardDeviationTrainingError())
				{
					return true;
				}
			}
		}
	}
	
	return false;
}

bool generalizationErrorEqual(const SimulationResult& result1, const SimulationResult& result2)
{
	return ((result1.getMeanGeneralizationError() == result2.getMeanGeneralizationError()) && (result1.getStandardDeviationGeneralizationError() == result2.getStandardDeviationGeneralizationError()) && (result1.getMeanTrainingError() == result2.getMeanTrainingError()) && (result1.getStandardDeviationTrainingError() == result2.getStandardDeviationTrainingError()));
}

gsl_rng* generator;

template <class T>
void shuffle(std::vector<T>& shuffleList, unsigned int startIndex, unsigned int endIndex)	
{
	for (unsigned int i = endIndex; i >= (startIndex + 1); --i)
	{
		unsigned int j = gsl_rng_uniform_int(generator, i + 1 - startIndex) + startIndex;
		T temp = shuffleList[i];
		shuffleList[i] = shuffleList[j];
		shuffleList[j] = temp;
	}
}

void unbiasedSort(vector<SimulationResult>& sortingList, bool (*sortComparisonFunction)(const SimulationResult&, const SimulationResult&), bool equal(const SimulationResult&, const SimulationResult&)) {
	
	// perform initial sorting
	stable_sort(sortingList.begin(), sortingList.end(), sortComparisonFunction);
	
	// test all ranges for equivalent significance values
	for (unsigned int i = 0; i < (sortingList.size() - 1); ++i) {
		
		// find single range of equivalent significance values
		unsigned int equivalentRange = 0;
		
		for (unsigned int j = (i + 1); ((j < sortingList.size()) && equal(sortingList[i], sortingList[j])); ++j) {
			++equivalentRange;
		}
		
		// shuffle required range of significance values
		if (equivalentRange > 0) {
			
			shuffle(sortingList, i, i + equivalentRange);
			
			// skip over equivalent range (to avoid re-shuffling portions of the equivalent sequence)
			i += equivalentRange;
		}
		
	}
	
}

vector<SimulationResult> results;

void processFileName(char* fileName, vector<SimulationResult>& resultStructure, unsigned int recordNumber)
{
	// create new simulation result
	SimulationResult newResult;
	newResult.setRecordNumber(recordNumber);
	
	// truncate the first part of the file name, up to end of _dim_
	strtok(fileName, "_");
	strtok(NULL, "_");
	strtok(NULL, "_");
	strtok(NULL, "_");
	
	// extract map dimension
	char* dimensionString = strtok(NULL, "_");
	int newDimension = atoi(dimensionString);
	newResult.setDimension(newDimension);
	
	// remove _lr_
	strtok(NULL, "_");
	
	// extract learning rate
	char* learningRateString = strtok(NULL, "_");
	double newLearningRate = strtod(learningRateString, NULL);
	newResult.setLearningRate(newLearningRate);
	
	// remove _lrd_
	strtok(NULL, "_");
	
	// extract learning rate decay
	char* learningRateDecayString = strtok(NULL, "_");
	double newLearningRateDecay = strtod(learningRateDecayString, NULL);
	newResult.setLearningRateDecay(newLearningRateDecay);
	
	// remove _kw_
	strtok(NULL, "_");
	
	// extract kernel width
	char* kernelWidthString = strtok(NULL, "_");
	double newKernelWidth = strtod(kernelWidthString, NULL);
	newResult.setKernelWidth(newKernelWidth);
	
	// remove _kwd_
	strtok(NULL, "_");
	
	// extract kernel width decay
	char* kernelWidthDecayString = strtok(NULL, "_");
	double newKernelWidthDecay = strtod(kernelWidthDecayString, NULL);
	newResult.setKernelWidthDecay(newKernelWidthDecay);
	
	// add new simulation result to result structure
	resultStructure.push_back(newResult);
	
}

int main(int argc, char**argv)
{
	
	if (argc != 12)
	{
		cout << "Invalid parameters" << endl;
		cout << "./optimizeLabelClassification errorSummaryFileName dimMin dimMax lrateMin lrateMax lrateDecayMin lrateDecayMax kwidthMin kwidthMax kwidthDecayMin kwidthDecayMax" << endl;
	}
	else
	{
		// initialize random number generator
		generator = gsl_rng_alloc(gsl_rng_mt19937);
		gsl_rng_set(generator, 24368);
		
		// set minimum and maximum ranges
		SimulationResult::minDimension = atof(argv[2]);
		SimulationResult::maxDimension = atof(argv[3]);
		SimulationResult::minLearningRate = atof(argv[4]);
		SimulationResult::maxLearningRate = atof(argv[5]);
		SimulationResult::minLearningRateDecay = atof(argv[6]);
		SimulationResult::maxLearningRateDecay = atof(argv[7]);
		SimulationResult::minKernelWidth = atof(argv[8]);
		SimulationResult::maxKernelWidth = atof(argv[9]);
		SimulationResult::minKernelWidthDecay = atof(argv[10]);
		SimulationResult::maxKernelWidthDecay = atof(argv[11]);
		
		// result structure
		vector<SimulationResult> resultStructure;
		
		// open file and ignore first line (the header)
		ifstream errorFile;
		errorFile.open(argv[1]);
		errorFile.ignore(1000, '\n');
		
		unsigned int index = 0;
		
		// process all remaining lines
		while (!errorFile.eof()) {
			
			// read line
			char readLine1[1000];
			char readLine2[1000];
			errorFile.getline(readLine1, 1000);
			strcpy(readLine2, readLine1);
			
			// process simulation file name
			char* fileName = strtok(readLine1, "\t");
			processFileName(fileName, resultStructure, index);
			
			// process performance measures
			strtok(readLine2, "\t");
			char* meanTrainingError = strtok(NULL, "\t");
			resultStructure[index].setMeanTrainingError(strtod(meanTrainingError, NULL));
			
			char* standardDeviationTrainingError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationTrainingError(strtod(standardDeviationTrainingError, NULL));
			
			char* meanTrainingMisclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setMeanTrainingMisclassifiedError(strtod(meanTrainingMisclassifiedError, NULL));
			
			char* standardDeviationTrainingMisclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationTrainingMisclassifiedError(strtod(standardDeviationTrainingMisclassifiedError, NULL));
			
			char* meanTrainingUnclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setMeanTrainingUnclassifiedError(strtod(meanTrainingUnclassifiedError, NULL));
			
			char* standardDeviationTrainingUnclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationTrainingUnclassifiedError(strtod(standardDeviationTrainingUnclassifiedError, NULL));
			
			char* meanGeneralizationError = strtok(NULL, "\t");
			resultStructure[index].setMeanGeneralizationError(strtod(meanGeneralizationError, NULL));
			
			char* standardDeviationGeneralizationError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationGeneralizationError(strtod(standardDeviationGeneralizationError, NULL));
			
			char* meanGeneralizationMisclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setMeanGeneralizationMisclassifiedError(strtod(meanGeneralizationMisclassifiedError, NULL));
			
			char* standardDeviationGeneralizationMisclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationGeneralizationMisclassifiedError(strtod(standardDeviationGeneralizationMisclassifiedError, NULL));
			
			char* meanGeneralizationUnclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setMeanGeneralizationUnclassifiedError(strtod(meanGeneralizationUnclassifiedError, NULL));
			
			char* standardDeviationGeneralizationUnclassifiedError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationGeneralizationUnclassifiedError(strtod(standardDeviationGeneralizationUnclassifiedError, NULL));
			
			char* meanUnlabeledCount = strtok(NULL, "\t");
			resultStructure[index].setMeanUnlabeledCount(strtod(meanUnlabeledCount, NULL));
			
			char* standardDeviationUnlabeledCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationUnlabeledCount(strtod(standardDeviationUnlabeledCount, NULL));
			
			char* meanUnlabeledPercentage = strtok(NULL, "\t");
			resultStructure[index].setMeanUnlabeledPercentage(strtod(meanUnlabeledPercentage, NULL));
			
			char* standardDeviationUnlabeledPercentage = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationUnlabeledPercentage(strtod(standardDeviationUnlabeledPercentage, NULL));
			
			++index;
			
		}
		
		// output the data for the generalization error FluxVis plot (all patterns)
		char* generalizationOutputFileName = new char[strlen(argv[1]) + 18];
		strcpy(generalizationOutputFileName, "1_generalization_");
		strcat(generalizationOutputFileName, argv[1]);
		ofstream generalizationOutput(generalizationOutputFileName);
		
		// sort the result structure according to generalization error
		unbiasedSort(resultStructure, generalizationErrorSortPredicate, generalizationErrorEqual);
		
		// remove all but the top 20% of the results (by generalization error)
		vector<SimulationResult> tempResultStructure;
		int numberToSelect = (int) (0.2 * resultStructure.size());
		
		for (unsigned int i = 0; i < numberToSelect; ++i)
		{
			tempResultStructure.push_back(resultStructure[i]);
		}
		
		resultStructure.erase(resultStructure.begin(), resultStructure.end());
		resultStructure.assign(tempResultStructure.begin(), tempResultStructure.end());
		tempResultStructure.erase(tempResultStructure.begin(), tempResultStructure.end());

		// output all results to generalization error file
		for (unsigned int i = 0; i < resultStructure.size(); ++i) {
			resultStructure[i].printGeneralizationError(generalizationOutput, resultStructure.size(), i);
		}
		
		delete generalizationOutputFileName;
		generalizationOutput.close();
		
		char* mostOptimalOutputFileName = new char[strlen(argv[1]) + 15];
		
		strcpy(mostOptimalOutputFileName, "2_mostOptimal_");
		
		strcat(mostOptimalOutputFileName, argv[1]);
		ofstream mostOptimalOutput(mostOptimalOutputFileName);
		
		// output the parameters and performance characteristics of the best result
		resultStructure[0].printAll(mostOptimalOutput);
		
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(3);
		
		cout << "Minimum map dimension: " << SimulationResult::minDimension << endl;
		cout << "Maximum map dimension: " << SimulationResult::maxDimension << endl;
		cout << endl;
		
		cout << "Minimum learning rate: " << SimulationResult::minLearningRate << endl;
		cout << "Maximum learning rate: " << SimulationResult::maxLearningRate << endl;
		cout << endl;
		
		cout << "Minimum learning rate decay: " << SimulationResult::minLearningRateDecay << endl;
		cout << "Maximum learning rate decay: " << SimulationResult::maxLearningRateDecay << endl;
		cout << endl;
		
		cout << "Minimum kernel width: " << SimulationResult::minKernelWidth << endl;
		cout << "Maximum kernel width: " << SimulationResult::maxKernelWidth << endl;
		cout << endl;
		
		cout << "Minimum kernel width decay: " << SimulationResult::minKernelWidthDecay << endl;
		cout << "Maximum kernel width decay: " << SimulationResult::maxKernelWidthDecay << endl;
		cout << endl;
		
		cout << "Minimum generalization error: " << SimulationResult::minMeanGeneralizationError << endl;
		cout << "Maximum generalization error: " << SimulationResult::maxMeanGeneralizationError << endl;
		
		delete mostOptimalOutputFileName;
		mostOptimalOutput.close();
		errorFile.close();
		gsl_rng_free(generator);
	}
	
}
