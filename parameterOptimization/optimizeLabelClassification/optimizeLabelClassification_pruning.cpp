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
			stdDev = 0.0;
			
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
			
			meanPrunedNeuronCount = 0.0;
			standardDeviationPrunedNeuronCount = 0.0;
			meanPrunedNeuronPercentage = 0.0;
			standardDeviationPrunedNeuronPercentage = 0.0;
			meanUnprunedNeuronCount = 0.0;
			standardDeviationUnprunedNeuronCount = 0.0;
			meanUnprunedNeuronPercentage = 0.0;
			standardDeviationUnprunedNeuronPercentage = 0.0;
		}
		
		SimulationResult(const SimulationResult& source)
		{
			recordNumber = source.recordNumber;
			
			dimension = source.dimension;
			learningRate = source.learningRate;
			learningRateDecay = source.learningRateDecay;
			kernelWidth = source.kernelWidth;
			kernelWidthDecay = source.kernelWidthDecay;
			stdDev = source.stdDev;
			
			meanTrainingError = source.meanTrainingError;
			standardDeviationTrainingError = source.standardDeviationTrainingError;
			meanTrainingMisclassifiedError = source.meanTrainingMisclassifiedError;
			standardDeviationTrainingMisclassifiedError = source.standardDeviationTrainingMisclassifiedError;
			meanTrainingUnclassifiedError = source.meanTrainingUnclassifiedError;
			standardDeviationTrainingUnclassifiedError = source.standardDeviationTrainingUnclassifiedError;
			
			meanGeneralizationError = source.meanGeneralizationError;
			standardDeviationGeneralizationError = source.standardDeviationGeneralizationError;
			meanGeneralizationMisclassifiedError = source.meanGeneralizationMisclassifiedError;
			standardDeviationGeneralizationMisclassifiedError = source.standardDeviationGeneralizationMisclassifiedError;
			meanGeneralizationUnclassifiedError = source.meanGeneralizationUnclassifiedError;
			standardDeviationGeneralizationUnclassifiedError = source.standardDeviationGeneralizationUnclassifiedError;
			
			meanUnlabeledCount = source.meanUnlabeledCount;
			standardDeviationUnlabeledCount = source.standardDeviationUnlabeledCount;
			meanUnlabeledPercentage = source.meanUnlabeledPercentage;
			standardDeviationUnlabeledPercentage = source.standardDeviationUnlabeledPercentage;
			
			meanPrunedNeuronCount = source.meanPrunedNeuronCount;
			standardDeviationPrunedNeuronCount = source.standardDeviationPrunedNeuronCount;
			meanPrunedNeuronPercentage = source.meanPrunedNeuronPercentage;
			standardDeviationPrunedNeuronPercentage = source.standardDeviationPrunedNeuronPercentage;
			meanUnprunedNeuronCount = source.meanUnprunedNeuronCount;
			standardDeviationUnprunedNeuronCount = source.standardDeviationUnprunedNeuronCount;
			meanUnprunedNeuronPercentage = source.meanUnprunedNeuronPercentage;
			standardDeviationUnprunedNeuronPercentage = source.standardDeviationUnprunedNeuronPercentage;
		}
		
		bool operator==(const SimulationResult& source)
		{
			if ((dimension == source.dimension) && (learningRate == source.learningRate) && (learningRateDecay == source.learningRateDecay) &&
			    (kernelWidth == source.kernelWidth) && (kernelWidthDecay == source.kernelWidthDecay) && (stdDev == source.stdDev) &&
			    (meanTrainingError == source.meanTrainingError) && (standardDeviationTrainingError == source.standardDeviationTrainingError) &&
			    (meanTrainingMisclassifiedError == source.meanTrainingMisclassifiedError) &&
			    (standardDeviationTrainingMisclassifiedError == source.standardDeviationTrainingMisclassifiedError) &&
			    (meanTrainingUnclassifiedError == source.meanTrainingUnclassifiedError) &&
			    (standardDeviationTrainingUnclassifiedError == source.standardDeviationTrainingUnclassifiedError) &&
			    (meanGeneralizationError == source.meanGeneralizationError) && (standardDeviationGeneralizationError == source.standardDeviationGeneralizationError) &&
			    (meanGeneralizationMisclassifiedError == source.meanGeneralizationMisclassifiedError) &&
			    (standardDeviationGeneralizationMisclassifiedError == source.standardDeviationGeneralizationMisclassifiedError) &&
			    (meanGeneralizationUnclassifiedError == source.meanGeneralizationUnclassifiedError) &&
			    (standardDeviationGeneralizationUnclassifiedError == source.standardDeviationGeneralizationUnclassifiedError) &&
			    (meanUnlabeledCount == source.meanUnlabeledCount) &&
			    (standardDeviationUnlabeledCount == source.standardDeviationUnlabeledCount) &&
			    (meanUnlabeledPercentage == source.meanUnlabeledPercentage) &&
			    (standardDeviationUnlabeledPercentage == source.standardDeviationUnlabeledPercentage) &&
			    (meanPrunedNeuronCount == source.meanPrunedNeuronCount) &&
			    (standardDeviationPrunedNeuronCount == source.standardDeviationPrunedNeuronCount) &&
			    (meanPrunedNeuronPercentage == source.meanPrunedNeuronPercentage) &&
			    (standardDeviationPrunedNeuronPercentage == source.standardDeviationPrunedNeuronPercentage) &&
			    (meanUnprunedNeuronCount == source.meanUnprunedNeuronCount) &&
			    (standardDeviationUnprunedNeuronCount == source.standardDeviationUnprunedNeuronCount) &&
			    (meanUnprunedNeuronPercentage == source.meanUnprunedNeuronPercentage) &&
			    (standardDeviationUnprunedNeuronPercentage == source.standardDeviationUnprunedNeuronPercentage))
			{
				return true;
			}
			else
			{
				return false;
			}
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
		
		void setStdDev(double _stdDev)
		{
			stdDev = _stdDev;
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
		
		void setMeanPrunedNeuronCount(double _meanPrunedNeuronCount)
		{
			meanPrunedNeuronCount = _meanPrunedNeuronCount;
		}
		
		void setStandardDeviationPrunedNeuronCount(double _standardDeviationPrunedNeuronCount)
		{
			standardDeviationPrunedNeuronCount = _standardDeviationPrunedNeuronCount;
		}
		
		void setMeanPrunedNeuronPercentage(double _meanPrunedNeuronPercentage)
		{
			meanPrunedNeuronPercentage = _meanPrunedNeuronPercentage;
		}
		
		void setStandardDeviationPrunedNeuronPercentage(double _standardDeviationPrunedNeuronPercentage)
		{
			standardDeviationPrunedNeuronPercentage = _standardDeviationPrunedNeuronPercentage;
		}
		
		void setMeanUnprunedNeuronCount(double _meanUnprunedNeuronCount)
		{
			meanUnprunedNeuronCount = _meanUnprunedNeuronCount;
		}
		
		void setStandardDeviationUnprunedNeuronCount(double _standardDeviationUnprunedNeuronCount)
		{
			standardDeviationUnprunedNeuronCount = _standardDeviationUnprunedNeuronCount;
		}
		
		void setMeanUnprunedNeuronPercentage(double _meanUnprunedNeuronPercentage)
		{
			meanUnprunedNeuronPercentage = _meanUnprunedNeuronPercentage;
		}
		
		void setStandardDeviationUnprunedNeuronPercentage(double _standardDeviationUnprunedNeuronPercentage)
		{
			standardDeviationUnprunedNeuronPercentage = _standardDeviationUnprunedNeuronPercentage;
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
		
		double getStandardDeviationUnlabeledCount() const
		{
			return standardDeviationUnlabeledCount;
		}
		
		double getMeanUnlabeledPercentage() const
		{
			return meanUnlabeledPercentage;
		}
		
		double getStandardDeviationUnlabeledPercentage() const
		{
			return standardDeviationUnlabeledPercentage;
		}
		
		double getMeanPrunedNeuronCount() const
		{
			return meanPrunedNeuronCount;
		}
		
		double getStandardDeviationPrunedNeuronCount() const
		{
			return standardDeviationPrunedNeuronCount;
		}
		
		double getMeanPrunedNeuronPercentage() const
		{
			return meanPrunedNeuronPercentage;
		}
		
		double getStandardDeviationPrunedNeuronPercentage() const
		{
			return standardDeviationPrunedNeuronPercentage;
		}
		
		double getMeanUnprunedNeuronCount() const
		{
			return meanUnprunedNeuronCount;
		}
		
		double getStandardDeviationUnprunedNeuronCount() const
		{
			return standardDeviationUnprunedNeuronCount;
		}
		
		double getMeanUnprunedNeuronPercentage() const
		{
			return meanUnprunedNeuronPercentage;
		}
		
		double getStandardDeviationUnprunedNeuronPercentage() const
		{
			return standardDeviationUnprunedNeuronPercentage;
		}
		
		void printUnscaledGeneralizationErrorPlotData(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os  << setprecision(14) << fixed;
			
			os << "0 " << dimension << endl;
			os << "1 " << learningRate << endl;
			os << "2 " << learningRateDecay << endl;
			os << "3 " << kernelWidth << endl;
			os << "4 " << kernelWidthDecay << endl;
			os << "5 " << stdDev << endl;
			os << "6 " << meanGeneralizationError << endl;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printUnscaledUnprunedNeuronPercentagePlotData(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os  << setprecision(14) << fixed;
			
			os << "0 " << dimension << endl;
			os << "1 " << learningRate << endl;
			os << "2 " << learningRateDecay << endl;
			os << "3 " << kernelWidth << endl;
			os << "4 " << kernelWidthDecay << endl;
			os << "5 " << stdDev << endl;
			os << "6 " << meanGeneralizationError << endl;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printAll(ostream& os)
		{
			os << "dimension\t" << "learningRate\t" << "learningRateDecay\t" << "kernelWidth\t" << "kernelWidthDecay\t" << "stdDev\t"
			   << "meanTrainingError\t" << "standardDeviationTrainingError\t"
			   << "meanTrainingMisclassifiedError\t" << "standardDeviationTrainingMisclassifiedError\t"
			   << "meanTrainingUnclassifiedError\t" << "standardDeviationTrainingUnclassifiedError\t"
			   << "meanGeneralizationError\t" << "standardDeviationGeneralizationError\t"
			   << "meanGeneralizationMisclassifiedError\t" << "standardDeviationGeneralizationMisclassifiedError\t"
			   << "meanGeneralizationUnclassifiedError\t" << "standardDeviationGeneralizationUnclassifiedError\t"
			   << "meanUnlabeledNeuronCount\t" << "stdDevUnlabeledNeuronCount\t"
			   << "meanUnlabeledNeuronPercentage\t" << "stdDevUnlabeledNeuronPercentage\t"
			   << "meanPrunedNeuronCount\t" << "stdDevPrunedNeuronCount\t"
			   << "meanPrunedNeuronPercentage\t" << "stdDevPrunedNeuronPercentage\t"
			   << "meanUnprunedNeuronCount\t" << "stdDevUnprunedNeuronCount\t"
			   << "meanUnprunedNeuronPercentage\t" << "stdDevUnprunedNeuronPercentage" << endl;
			
			os << setprecision(14) << fixed << dimension << "\t" << learningRate << "\t" << learningRateDecay
			   << "\t" << kernelWidth << "\t" << kernelWidthDecay << "\t" << stdDev
			   << "\t" << meanTrainingError << "\t" << standardDeviationTrainingError
			   << "\t" << meanTrainingMisclassifiedError << "\t" << standardDeviationTrainingMisclassifiedError
			   << "\t" << meanTrainingUnclassifiedError << "\t" << standardDeviationTrainingUnclassifiedError
			   << "\t" << meanGeneralizationError << "\t" << standardDeviationGeneralizationError
			   << "\t" << meanGeneralizationMisclassifiedError << "\t" << standardDeviationGeneralizationMisclassifiedError
			   << "\t" << meanGeneralizationUnclassifiedError << "\t" << standardDeviationGeneralizationUnclassifiedError
			   << "\t" << meanUnlabeledCount << "\t" << standardDeviationUnlabeledCount
			   << "\t" << meanUnlabeledPercentage << "\t" << standardDeviationUnlabeledPercentage		
			   << "\t" << meanPrunedNeuronCount << "\t" << standardDeviationPrunedNeuronCount
			   << "\t" << meanPrunedNeuronPercentage << "\t" << standardDeviationPrunedNeuronPercentage
			   << "\t" << meanUnprunedNeuronCount << "\t" << standardDeviationUnprunedNeuronCount
			   << "\t" << meanUnprunedNeuronPercentage << "\t" << standardDeviationUnprunedNeuronPercentage;
		}
		
		friend ostream& operator<<(ostream& ios, const SimulationResult& result);
	
	public:
		unsigned int recordNumber;
		
		double dimension;
		double learningRate;
		double learningRateDecay;
		double kernelWidth;
		double kernelWidthDecay;
		double stdDev;
		
		double meanTrainingError;
		double standardDeviationTrainingError;
		double meanTrainingMisclassifiedError;
		double standardDeviationTrainingMisclassifiedError;
		double meanTrainingUnclassifiedError;
		double standardDeviationTrainingUnclassifiedError;
		
		double meanGeneralizationError;
		double standardDeviationGeneralizationError;
		double meanGeneralizationMisclassifiedError;
		double standardDeviationGeneralizationMisclassifiedError;
		double meanGeneralizationUnclassifiedError;
		double standardDeviationGeneralizationUnclassifiedError;
		
		double meanUnlabeledCount;
		double standardDeviationUnlabeledCount;
		double meanUnlabeledPercentage;
		double standardDeviationUnlabeledPercentage;
		
		double meanPrunedNeuronCount;
		double standardDeviationPrunedNeuronCount;
		double meanPrunedNeuronPercentage;
		double standardDeviationPrunedNeuronPercentage;
		double meanUnprunedNeuronCount;
		double standardDeviationUnprunedNeuronCount;
		double meanUnprunedNeuronPercentage;
		double standardDeviationUnprunedNeuronPercentage;
	
};

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
			if (result1.getMeanUnprunedNeuronPercentage() < result2.getMeanUnprunedNeuronPercentage())
			{
				return true;
			}
			
			if (result1.getMeanUnprunedNeuronPercentage() == result2.getMeanUnprunedNeuronPercentage())
			{
				if (result1.getStandardDeviationUnprunedNeuronPercentage() < result2.getStandardDeviationUnprunedNeuronPercentage())
				{
					return true;
				}
				
				if (result1.getStandardDeviationUnprunedNeuronPercentage() == result2.getStandardDeviationUnprunedNeuronPercentage())
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
		}
	}
	
	return false;
}

bool unprunedNeuronPercentageSortPredicate(const SimulationResult& result1, const SimulationResult& result2)
{
	if (result1.getMeanUnprunedNeuronPercentage() < result2.getMeanUnprunedNeuronPercentage())
	{
		return true;
	}
	
	if (result1.getMeanUnprunedNeuronPercentage() == result2.getMeanUnprunedNeuronPercentage())
	{
		if (result1.getStandardDeviationUnprunedNeuronPercentage() < result2.getStandardDeviationUnprunedNeuronPercentage())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return false;
}

bool generalizationErrorEqual(const SimulationResult& result1, const SimulationResult& result2)
{
	return ((result1.getMeanGeneralizationError() == result2.getMeanGeneralizationError()) && (result1.getStandardDeviationGeneralizationError() == result2.getStandardDeviationGeneralizationError()) && (result1.getMeanUnprunedNeuronPercentage() == result2.getMeanUnprunedNeuronPercentage()) && (result1.getStandardDeviationUnprunedNeuronPercentage() == result2.getStandardDeviationUnprunedNeuronPercentage()) && (result1.getMeanTrainingError() == result2.getMeanTrainingError()) && (result1.getStandardDeviationTrainingError() == result2.getStandardDeviationTrainingError()));
}

bool unprunedNeuronPercentageEqual(const SimulationResult& result1, const SimulationResult& result2)
{
	return ((result1.getMeanUnprunedNeuronPercentage() == result2.getMeanUnprunedNeuronPercentage()) && (result1.getStandardDeviationUnprunedNeuronPercentage() == result2.getStandardDeviationUnprunedNeuronPercentage()));
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

void unbiasedSort(vector<SimulationResult>& sortingList, bool (*sortComparisonFunction)(const SimulationResult&, const SimulationResult&), bool equal(const SimulationResult&, const SimulationResult&))
{
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

void orderedSort(vector<SimulationResult>& sortingList, bool (*sortComparisonFunction)(const SimulationResult&, const SimulationResult&))
{
	// perform sorting, while preserving order
	stable_sort(sortingList.begin(), sortingList.end(), sortComparisonFunction);
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
	
	// remove _stdDev
	strtok(NULL, "_");
	
	// extract pruning standard deviation
	char* stdDevString = strtok(NULL, "_");
	double newStdDev = strtod(stdDevString, NULL);
	newResult.setStdDev(newStdDev);
	
	// add new simulation result to result structure
	resultStructure.push_back(newResult);
}

int main(int argc, char**argv)
{
	
	if (argc != 2)
	{
		cout << "Invalid parameters" << endl;
		cout << "./optimizeLabelClassification errorSummaryFileName" << endl;
	}
	else
	{
		// initialize random number generator
		generator = gsl_rng_alloc(gsl_rng_mt19937);
		gsl_rng_set(generator, 24368);
		
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
			
			char* meanPrunedNeuronCount = strtok(NULL, "\t");
			resultStructure[index].setMeanPrunedNeuronCount(strtod(meanPrunedNeuronCount, NULL));
			
			char* standardDeviationPrunedNeuronCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationPrunedNeuronCount(strtod(standardDeviationPrunedNeuronCount, NULL));
			
			char* meanPrunedNeuronPercentage = strtok(NULL, "\t");
			resultStructure[index].setMeanPrunedNeuronPercentage(strtod(meanPrunedNeuronPercentage, NULL));
			
			char* standardDeviationPrunedNeuronPercentage = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationPrunedNeuronPercentage(strtod(standardDeviationPrunedNeuronPercentage, NULL));
			
			char* meanUnprunedNeuronCount = strtok(NULL, "\t");
			resultStructure[index].setMeanUnprunedNeuronCount(strtod(meanUnprunedNeuronCount, NULL));
			
			char* standardDeviationUnprunedNeuronCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationUnprunedNeuronCount(strtod(standardDeviationUnprunedNeuronCount, NULL));
			
			char* meanUnprunedNeuronPercentage = strtok(NULL, "\t");
			resultStructure[index].setMeanUnprunedNeuronPercentage(strtod(meanUnprunedNeuronPercentage, NULL));
			
			char* standardDeviationUnprunedNeuronPercentage = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationUnprunedNeuronPercentage(strtod(standardDeviationUnprunedNeuronPercentage, NULL));
			
			++index;
		}
		
		// sort the result structure according to mean generalization error (break ties in favor of generalization error standard deviation, then mean unpruned neuron percentage,
		// then unpruned neuron percentage standard deviation, then mean training error, then training error standard deviation)
		unbiasedSort(resultStructure, generalizationErrorSortPredicate, generalizationErrorEqual);
		
		// remove all but the top 20% of the results (by generalization error), overwrite resultStructure and store a copy in tempResultStructure
		vector<SimulationResult> tempResultStructure;
		int numberToSelect = (int) (0.2 * resultStructure.size());
		
		for (unsigned int i = 0; i < numberToSelect; ++i)
		{
			tempResultStructure.push_back(resultStructure[i]);
		}
		
		resultStructure.erase(resultStructure.begin(), resultStructure.end());
		resultStructure.assign(tempResultStructure.begin(), tempResultStructure.end());
		
		// sort a copy of the result structure (tempResultStructure) according to unpruned neuron percentage (break ties in favor of unpruned neuron percentage standard deviation)
		unbiasedSort(tempResultStructure, unprunedNeuronPercentageSortPredicate, unprunedNeuronPercentageEqual);
		
		// store all unique unpruned percentages from tempResultStructure in uniqueUnprunedPercentages
		// determine number of top 20% of unique unpruned percentages from uniqueUnprunedPercentages
		// store all from tempResultStructure with unprunedNeuronPercentage found in uniqueUnprunedPercentages, to bestUnprunedNeuronPercentages
		vector<SimulationResult> bestUnprunedNeuronPercentages;
		vector<SimulationResult> uniqueUnprunedPercentages;
		uniqueUnprunedPercentages.push_back(tempResultStructure[0]);
		
		for (unsigned int i = 1; i < tempResultStructure.size(); ++i)
		{
			if (!unprunedNeuronPercentageEqual(tempResultStructure[i], tempResultStructure[i-1]))
			{
				uniqueUnprunedPercentages.push_back(tempResultStructure[i]);
			}
		}
		
		// there must be at least one unique unpruned neuron percentage
		// compute number to select (20% rounded down, ensuring that at least one is selected)
		numberToSelect = (int) (0.2 * uniqueUnprunedPercentages.size());
		
		if (numberToSelect == 0)
		{
			numberToSelect = 1;
		}
		
		for (unsigned int i = 0; i < tempResultStructure.size(); ++i)
		{
			for (unsigned int j = 0; j < numberToSelect; ++j)
			{
				if (unprunedNeuronPercentageEqual(tempResultStructure[i], uniqueUnprunedPercentages[j]))
				{
					bestUnprunedNeuronPercentages.push_back(tempResultStructure[i]);
					break;
				}
			}
		}
		
		// find the best generalization error that has an unpruned neuron percentage in the top 20% of the selected results
		bool optimalNotFound = true;
		
		for (unsigned int i = 0; i < resultStructure.size() && optimalNotFound; ++i)
		{
			for (unsigned int j = 0; j < bestUnprunedNeuronPercentages.size(); ++j)
			{
				if ((resultStructure[i].getMeanUnprunedNeuronPercentage() <= bestUnprunedNeuronPercentages[j].getMeanUnprunedNeuronPercentage()) && (resultStructure[i].getStandardDeviationUnprunedNeuronPercentage() <= bestUnprunedNeuronPercentages[j].getStandardDeviationUnprunedNeuronPercentage()))
				{
					optimalNotFound = false;
					
					// retrieve the best result
					SimulationResult mostOptimalSimulationResult(resultStructure[i]);
					
					// remove the best result, and insert it at the front of the resultStructure list
					resultStructure.erase(resultStructure.begin() + i);
					resultStructure.insert(resultStructure.begin(), mostOptimalSimulationResult);
					
					// if the best result also exists in the bestUnprunedNeuronPercentages list (it might not), move it to the front of the list
					// also duplicate the second-last item in the list, so that there are always 21 items in the list
					bool bestConditionFound = false;
					
					for (unsigned int k = 0; k < bestUnprunedNeuronPercentages.size(); ++k)
					{
						if (resultStructure[0] == bestUnprunedNeuronPercentages[k])
						{
							bestConditionFound = true;
							
							SimulationResult mostOptimalConditionCountItem(bestUnprunedNeuronPercentages[k]);
							bestUnprunedNeuronPercentages.erase(bestUnprunedNeuronPercentages.begin() + k);
							bestUnprunedNeuronPercentages.insert(bestUnprunedNeuronPercentages.begin(), mostOptimalConditionCountItem);
							
							break;
						}
					}
					
					// if the best result is not in the bestUnprunedNeuronPercentages list, add the best result by generalization error
					if (!bestConditionFound)
					{
						SimulationResult mostOptimalGeneralizationItem(resultStructure[0]);
						bestUnprunedNeuronPercentages.insert(bestUnprunedNeuronPercentages.begin(), mostOptimalGeneralizationItem);
					}
					
					// if the best result also exists in the bestUnprunedNeuronPercentages list (it might not), remove it from the list and duplicate the first item
					// (so that there are always the same number of results in the conditions file, without creating a new line)
					for (unsigned int k = 0; k < bestUnprunedNeuronPercentages.size(); ++k)
					{
						if (resultStructure[0] == bestUnprunedNeuronPercentages[k])
						{
							
							break;
						}
					}
					
					break;
				}
			}
		}
		
		// output the data for the unscaled generalization error FluxVis plot (all patterns)
		char* unscaledGeneralizationErrorOutputFileName = new char[strlen(argv[1]) + 27];
		strcpy(unscaledGeneralizationErrorOutputFileName, "2_unscaled_generalization_");
		strcat(unscaledGeneralizationErrorOutputFileName, argv[1]);
		ofstream unscaledGeneralizationErrorOutput(unscaledGeneralizationErrorOutputFileName);
		
		for (unsigned int i = 0; i < resultStructure.size(); ++i) {
			resultStructure[i].printUnscaledGeneralizationErrorPlotData(unscaledGeneralizationErrorOutput, resultStructure.size(), i);
		}
		
		delete unscaledGeneralizationErrorOutputFileName;
		unscaledGeneralizationErrorOutput.close();
		
		// output the data for the unscaled unpruned neuron percentage FluxVis plot (all patterns)
		char* unscaledUnprunedNeuronPercentageOutputFileName = new char[strlen(argv[1]) + 23];
		strcpy(unscaledUnprunedNeuronPercentageOutputFileName, "4_unscaled_conditions_");
		strcat(unscaledUnprunedNeuronPercentageOutputFileName, argv[1]);
		ofstream unscaledUnprunedNeuronPercentageOutput(unscaledUnprunedNeuronPercentageOutputFileName);
		
		for (unsigned int i = 0; i < bestUnprunedNeuronPercentages.size(); ++i) {
			bestUnprunedNeuronPercentages[i].printUnscaledUnprunedNeuronPercentagePlotData(unscaledUnprunedNeuronPercentageOutput, bestUnprunedNeuronPercentages.size(), i);
		}
		
		delete unscaledUnprunedNeuronPercentageOutputFileName;
		unscaledUnprunedNeuronPercentageOutput.close();
		
		// output the parameters and performance characteristics of the best result
		char* mostOptimalOutputFileName = new char[strlen(argv[1]) + 15];
		strcpy(mostOptimalOutputFileName, "5_mostOptimal_");
		strcat(mostOptimalOutputFileName, argv[1]);
		ofstream mostOptimalOutput(mostOptimalOutputFileName);
		
		resultStructure[0].printAll(mostOptimalOutput);
		
		delete mostOptimalOutputFileName;
		mostOptimalOutput.close();
		errorFile.close();
		gsl_rng_free(generator);
	}
	
}
