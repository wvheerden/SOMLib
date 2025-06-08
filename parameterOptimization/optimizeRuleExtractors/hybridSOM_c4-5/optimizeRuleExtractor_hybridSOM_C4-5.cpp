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
			
			minOutcomes = 0.0;
			heuristic = new char[7];
			strcpy(heuristic, "");
			pruningConfidence = 0.0;
			fisherConfidence = 0.0;
			redundancy = 0.0;
			
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
			
			meanRuleSetConditionCount = 0.0;
			standardDeviationRuleSetConditionCount = 0.0;
			meanRuleCount = 0.0;
			standardDeviationRuleCount = 0.0;
			meanAverageConditionsPerRuleCount = 0.0;
			standardDeviationAverageConditionsPerRuleCount = 0.0;
		}
		
		SimulationResult(const SimulationResult& source)
		{
			recordNumber = source.recordNumber;
			
			dimension = source.dimension;
			learningRate = source.learningRate;
			learningRateDecay = source.learningRateDecay;
			kernelWidth = source.kernelWidth;
			kernelWidthDecay = source.kernelWidthDecay;
			
			minOutcomes = source.minOutcomes;
			heuristic = new char[7];
			strcpy(heuristic, source.heuristic);
			pruningConfidence = source.pruningConfidence;
			fisherConfidence = source.fisherConfidence;
			redundancy = source.redundancy;
			
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
			
			meanRuleSetConditionCount = source.meanRuleSetConditionCount;
			standardDeviationRuleSetConditionCount = source.standardDeviationRuleSetConditionCount;
			meanRuleCount = source.meanRuleCount;
			standardDeviationRuleCount = source.standardDeviationRuleCount;
			meanAverageConditionsPerRuleCount = source.meanAverageConditionsPerRuleCount;
			standardDeviationAverageConditionsPerRuleCount = source.standardDeviationAverageConditionsPerRuleCount;
		}
		
		bool operator==(const SimulationResult& source)
		{
			if ((dimension == source.dimension) && (learningRate == source.learningRate) && (learningRateDecay == source.learningRateDecay) &&
			    (kernelWidth == source.kernelWidth) && (kernelWidthDecay == source.kernelWidthDecay) &&
			    (minOutcomes == source.minOutcomes) && (strcmp(heuristic, source.heuristic) == 0) &&
			    (pruningConfidence == source.pruningConfidence) && (fisherConfidence == source.fisherConfidence) && (redundancy == source.redundancy) &&
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
			    (meanRuleSetConditionCount == source.meanRuleSetConditionCount) &&
			    (standardDeviationRuleSetConditionCount == source.standardDeviationRuleSetConditionCount) && (meanRuleCount == source.meanRuleCount) &&
			    (standardDeviationRuleCount == source.standardDeviationRuleCount) && (meanAverageConditionsPerRuleCount == source.meanAverageConditionsPerRuleCount) &&
			    (standardDeviationAverageConditionsPerRuleCount == source.standardDeviationAverageConditionsPerRuleCount))
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
		
		void setMinOutcomes(double _minOutcomes)
		{
			minOutcomes = _minOutcomes;
		}
		
		void setHeuristic(char* _heuristic)
		{
			strcpy(heuristic, _heuristic);
		}
		
		void setPruningConfidence(double _pruningConfidence)
		{
			pruningConfidence = _pruningConfidence;
		}
		
		void setFisherConfidence(double _fisherConfidence)
		{
			fisherConfidence = _fisherConfidence;
		}
		
		void setRedundancy(double _redundancy)
		{
			redundancy = _redundancy;
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
		
		void setMeanRuleSetConditionCount(double _meanRuleSetConditionCount)
		{
			meanRuleSetConditionCount = _meanRuleSetConditionCount;
			
			if (meanRuleSetConditionCount > maxMeanRuleSetConditionCount)
			{
				SimulationResult::maxMeanRuleSetConditionCount = meanRuleSetConditionCount;
			}
			
			if (meanRuleSetConditionCount < minMeanRuleSetConditionCount)
			{
				SimulationResult::minMeanRuleSetConditionCount = meanRuleSetConditionCount;
			}
		}
		
		void setStandardDeviationRuleSetConditionCount(double _standardDeviationRuleSetConditionCount)
		{
			standardDeviationRuleSetConditionCount = _standardDeviationRuleSetConditionCount;
		}
		
		void setMeanRuleCount(double _meanRuleCount)
		{
			meanRuleCount = _meanRuleCount;
		}

		void setStandardDeviationRuleCount(double _standardDeviationRuleCount)
		{
			standardDeviationRuleCount = _standardDeviationRuleCount;
		}
		
		void setMeanAverageConditionsPerRuleCount(double _meanAverageConditionsPerRuleCount)
		{
			meanAverageConditionsPerRuleCount = _meanAverageConditionsPerRuleCount;
		}
		
		void setStandardDeviationAverageConditionsPerRuleCount(double _standardDeviationAverageConditionsPerRuleCount)
		{
			standardDeviationAverageConditionsPerRuleCount = _standardDeviationAverageConditionsPerRuleCount;
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
		
		double getMeanRuleSetConditionCount() const
		{
			return meanRuleSetConditionCount;
		}
		
		double getStandardDeviationRuleSetConditionCount() const
		{
			return standardDeviationRuleSetConditionCount;
		}
		
		double scale(double value, double minValue, double maxValue, double newMinValue, double newMaxValue)
		{
			return (((value - minValue) / (maxValue - minValue)) * (newMaxValue - newMinValue)) + newMinValue;
		}
		
		void printGeneralizationErrorPlotData(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os  << setprecision(14) << fixed;
			
			os << "0 " << scale(dimension, SimulationResult::minDimension, SimulationResult::maxDimension, 0.0, 1.0) << endl;
			os << "1 " << scale(learningRate, SimulationResult::minLearningRate, SimulationResult::maxLearningRate, 0.0, 1.0) << endl;
			os << "2 " << scale(learningRateDecay, SimulationResult::minLearningRateDecay, SimulationResult::maxLearningRateDecay, 0.0, 1.0) << endl;
			os << "3 " << scale(kernelWidth, SimulationResult::minKernelWidth, SimulationResult::maxKernelWidth, 0.0, 1.0) << endl;
			os << "4 " << scale(kernelWidthDecay, SimulationResult::minKernelWidthDecay, SimulationResult::maxKernelWidthDecay, 0.0, 1.0) << endl;
			os << "5 " << scale(minOutcomes, SimulationResult::minMinOutcomes, SimulationResult::maxMinOutcomes, 0.0, 1.0) << endl;
			
			if (strcmp(heuristic, "gain") == 0)
			{
				os << "6 0" << endl;
			} else
			{
				os << "6 1" << endl;
			}
			
			os << "7 " << scale(pruningConfidence, SimulationResult::minPruningConfidence, SimulationResult::maxPruningConfidence, 0.0, 1.0) << endl;
			os << "8 " << scale(fisherConfidence, SimulationResult::minFisherConfidence, SimulationResult::maxFisherConfidence, 0.0, 1.0) << endl;
			os << "9 " << scale(redundancy, SimulationResult::minRedundancy, SimulationResult::maxRedundancy, 0.0, 1.0) << endl;
			os << "10 " << scale(meanGeneralizationError, SimulationResult::minMeanGeneralizationError, SimulationResult::maxMeanGeneralizationError, 0.0, 1.0) << endl;
			os << "11 " << scale(meanRuleSetConditionCount, SimulationResult::minMeanRuleSetConditionCount, SimulationResult::maxMeanRuleSetConditionCount, 0.0, 1.0) << endl;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printUnscaledGeneralizationErrorPlotData(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os  << setprecision(14) << fixed;
			
			os << "0 " << dimension << endl;
			os << "1 " << learningRate << endl;
			os << "2 " << learningRateDecay << endl;
			os << "3 " << kernelWidth << endl;
			os << "4 " << kernelWidthDecay << endl;
			os << "5 " << minOutcomes << endl;
			
			if (strcmp(heuristic, "gain") == 0)
			{
				os << "6 0" << endl;
			} else
			{
				os << "6 1" << endl;
			}
			
			os << "7 " << pruningConfidence << endl;
			os << "8 " << fisherConfidence << endl;
			os << "9 " << redundancy << endl;
			os << "10 " << meanGeneralizationError << endl;
			os << "11 " << meanRuleSetConditionCount << endl;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printRuleSetConditionCountPlotData(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os  << setprecision(14) << fixed;
			
			os << "0 " << scale(dimension, SimulationResult::minDimension, SimulationResult::maxDimension, 0.0, 1.0) << endl;
			os << "1 " << scale(learningRate, SimulationResult::minLearningRate, SimulationResult::maxLearningRate, 0.0, 1.0) << endl;
			os << "2 " << scale(learningRateDecay, SimulationResult::minLearningRateDecay, SimulationResult::maxLearningRateDecay, 0.0, 1.0) << endl;
			os << "3 " << scale(kernelWidth, SimulationResult::minKernelWidth, SimulationResult::maxKernelWidth, 0.0, 1.0) << endl;
			os << "4 " << scale(kernelWidthDecay, SimulationResult::minKernelWidthDecay, SimulationResult::maxKernelWidthDecay, 0.0, 1.0) << endl;
			os << "5 " << scale(minOutcomes, SimulationResult::minMinOutcomes, SimulationResult::maxMinOutcomes, 0.0, 1.0) << endl;
			
			if (strcmp(heuristic, "gain") == 0)
			{
				os << "6 0" << endl;
			} else
			{
				os << "6 1" << endl;
			}
			
			os << "7 " << scale(pruningConfidence, SimulationResult::minPruningConfidence, SimulationResult::maxPruningConfidence, 0.0, 1.0) << endl;
			os << "8 " << scale(fisherConfidence, SimulationResult::minFisherConfidence, SimulationResult::maxFisherConfidence, 0.0, 1.0) << endl;
			os << "9 " << scale(redundancy, SimulationResult::minRedundancy, SimulationResult::maxRedundancy, 0.0, 1.0) << endl;
			os << "10 " << scale(meanGeneralizationError, SimulationResult::minMeanGeneralizationError, SimulationResult::maxMeanGeneralizationError, 0.0, 1.0) << endl;
			os << "11 " << scale(meanRuleSetConditionCount, SimulationResult::minMeanRuleSetConditionCount, SimulationResult::maxMeanRuleSetConditionCount, 0.0, 1.0) << endl;
			
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printUnscaledRuleSetConditionCountPlotData(ostream& os, unsigned int totalRecordCount, unsigned int recordIndex)
		{
			os  << setprecision(14) << fixed;
			
			os << "0 " << dimension << endl;
			os << "1 " << learningRate << endl;
			os << "2 " << learningRateDecay << endl;
			os << "3 " << kernelWidth << endl;
			os << "4 " << kernelWidthDecay << endl;
			os << "5 " << minOutcomes << endl;
			
			if (strcmp(heuristic, "gain") == 0)
			{
				os << "6 0" << endl;
			} else
			{
				os << "6 1" << endl;
			}
			
			os << "7 " << pruningConfidence << endl;
			os << "8 " << fisherConfidence << endl;
			os << "9 " << redundancy << endl;
			os << "10 " << meanGeneralizationError << endl;
			os << "11 " << meanRuleSetConditionCount << endl;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printAll(ostream& os)
		{
			os << "dimension\t" << "learningRate\t" << "learningRateDecay\t" << "kernelWidth\t" << "kernelWidthDecay\t"
			   << "minOutcomes\t" << "heuristic\t" << "pruningConfidence\t" << "fisherConfidence\t" << "redundancy\t"
			   << "meanTrainingError\t" << "standardDeviationTrainingError\t"
			   << "meanTrainingMisclassifiedError\t" << "standardDeviationTrainingMisclassifiedError\t"
			   << "meanTrainingUnclassifiedError\t" << "standardDeviationTrainingUnclassifiedError\t"
			   << "meanGeneralizationError\t" << "standardDeviationGeneralizationError\t"
			   << "meanGeneralizationMisclassifiedError\t" << "standardDeviationGeneralizationMisclassifiedError\t"
			   << "meanGeneralizationUnclassifiedError\t" << "standardDeviationGeneralizationUnclassifiedError\t"
			   << "meanRuleSetConditionCount\t" << "standardDeviationRuleSetConditionCount\t"
			   << "meanRuleCount\t" << "standardDeviationRuleCount\t"
			   << "meanAverageConditionsPerRuleCount\t" << "standardDeviationAverageConditionsPerRuleCount" << endl;
			
			os << setprecision(14) << fixed << dimension << "\t" << learningRate << "\t" << learningRateDecay
			   << "\t" << kernelWidth << "\t" << kernelWidthDecay << "\t" << minOutcomes << "\t" << heuristic
			   << "\t" << pruningConfidence << "\t" << fisherConfidence << "\t" << redundancy
			   << "\t" << meanTrainingError << "\t" << standardDeviationTrainingError
			   << "\t" << meanTrainingMisclassifiedError << "\t" << standardDeviationTrainingMisclassifiedError
			   << "\t" << meanTrainingUnclassifiedError << "\t" << standardDeviationTrainingUnclassifiedError
			   << "\t" << meanGeneralizationError << "\t" << standardDeviationGeneralizationError
			   << "\t" << meanGeneralizationMisclassifiedError << "\t" << standardDeviationGeneralizationMisclassifiedError
			   << "\t" << meanGeneralizationUnclassifiedError << "\t" << standardDeviationGeneralizationUnclassifiedError
			   << "\t" << meanRuleSetConditionCount << "\t" << standardDeviationRuleSetConditionCount
			   << "\t" << meanRuleCount << "\t" << standardDeviationRuleCount
			   << "\t" << meanAverageConditionsPerRuleCount << "\t" << standardDeviationAverageConditionsPerRuleCount;
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
		
		double minOutcomes;
		static double minMinOutcomes;
		static double maxMinOutcomes;
		
		char* heuristic;
		
		double pruningConfidence;
		static double minPruningConfidence;
		static double maxPruningConfidence;
		
		double fisherConfidence;
		static double minFisherConfidence;
		static double maxFisherConfidence;
		
		double redundancy;
		static double minRedundancy;
		static double maxRedundancy;
		
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
		
		double meanRuleSetConditionCount;
		static double maxMeanRuleSetConditionCount;
		static double minMeanRuleSetConditionCount;
		
		double standardDeviationRuleSetConditionCount;
		double meanRuleCount;
		double standardDeviationRuleCount;
		double meanAverageConditionsPerRuleCount;
		double standardDeviationAverageConditionsPerRuleCount;
	
};

double SimulationResult::maxDimension = -DBL_MAX;
double SimulationResult::minDimension = DBL_MAX;
double SimulationResult::maxLearningRate = 10.0;
double SimulationResult::minLearningRate = 0.0;
double SimulationResult::maxLearningRateDecay = 1500.0;
double SimulationResult::minLearningRateDecay = 0.0;
double SimulationResult::maxKernelWidth = -DBL_MAX;
double SimulationResult::minKernelWidth = DBL_MAX;
double SimulationResult::maxKernelWidthDecay = 100.0;
double SimulationResult::minKernelWidthDecay = 0.0;
double SimulationResult::maxMinOutcomes = -DBL_MAX;
double SimulationResult::minMinOutcomes = DBL_MAX;
double SimulationResult::maxPruningConfidence = 100.0;
double SimulationResult::minPruningConfidence = 0.0;
double SimulationResult::maxFisherConfidence = 100.0;
double SimulationResult::minFisherConfidence = -10.0;
double SimulationResult::maxRedundancy = 10000.0;
double SimulationResult::minRedundancy = 0.0;
double SimulationResult::maxMeanGeneralizationError = -DBL_MAX;
double SimulationResult::minMeanGeneralizationError = DBL_MAX;
double SimulationResult::maxMeanRuleSetConditionCount = -DBL_MAX;
double SimulationResult::minMeanRuleSetConditionCount = DBL_MAX;

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
			if (result1.getMeanRuleSetConditionCount() < result2.getMeanRuleSetConditionCount())
			{
				return true;
			}
			
			if (result1.getMeanRuleSetConditionCount() == result2.getMeanRuleSetConditionCount())
			{
				if (result1.getStandardDeviationRuleSetConditionCount() < result2.getStandardDeviationRuleSetConditionCount())
				{
					return true;
				}
				
				if (result1.getStandardDeviationRuleSetConditionCount() == result2.getStandardDeviationRuleSetConditionCount())
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

bool ruleSetConditionCountSortPredicate(const SimulationResult& result1, const SimulationResult& result2)
{
	if (result1.getMeanRuleSetConditionCount() < result2.getMeanRuleSetConditionCount())
	{
		return true;
	}
	
	if (result1.getMeanRuleSetConditionCount() == result2.getMeanRuleSetConditionCount())
	{
		if (result1.getStandardDeviationRuleSetConditionCount() < result2.getStandardDeviationRuleSetConditionCount())
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
	return ((result1.getMeanGeneralizationError() == result2.getMeanGeneralizationError()) && (result1.getStandardDeviationGeneralizationError() == result2.getStandardDeviationGeneralizationError()) && (result1.getMeanRuleSetConditionCount() == result2.getMeanRuleSetConditionCount()) && (result1.getStandardDeviationRuleSetConditionCount() == result2.getStandardDeviationRuleSetConditionCount()) && (result1.getMeanTrainingError() == result2.getMeanTrainingError()) && (result1.getStandardDeviationTrainingError() == result2.getStandardDeviationTrainingError()));
}

bool ruleSetConditionCountEqual(const SimulationResult& result1, const SimulationResult& result2)
{
	return ((result1.getMeanRuleSetConditionCount() == result2.getMeanRuleSetConditionCount()) && (result1.getStandardDeviationRuleSetConditionCount() == result2.getStandardDeviationRuleSetConditionCount()));
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
	
	// remove _minOut_
	strtok(NULL, "_");
	
	// extract minimum outcomes
	char* minOutcomeString = strtok(NULL, "_");
	int newMinOutcome = strtod(minOutcomeString, NULL);
	newResult.setMinOutcomes(newMinOutcome);
	
	// remove _heur_
	strtok(NULL, "_");
	
	// extract heuristic
	char* heuristicString = strtok(NULL, "_");
	newResult.setHeuristic(heuristicString);
	
	// remove _prunConf_
	strtok(NULL, "_");
	
	// extract pruning confidence
	char* pruningConfidenceString = strtok(NULL, "_");
	double newPruningConfidence = strtod(pruningConfidenceString, NULL);
	newResult.setPruningConfidence(newPruningConfidence);
	
	// remove _fisher_
	strtok(NULL, "_");
	
	// extract Fisher confidence
	char* fisherConfidenceString = strtok(NULL, "_");
	double newFisherConfidence = 0.0;
	
	if (strcmp(fisherConfidenceString, "na") == 0)
	{
		newFisherConfidence = -10;
	} else
	{
		newFisherConfidence = strtod(fisherConfidenceString, NULL);;
	}
	
	newResult.setFisherConfidence(newFisherConfidence);
	
	// remove _redun_
	strtok(NULL, "_");
	
	// extract redundancy
	char* redundancyString = strtok(NULL, "_");
	double newRedundancy = strtod(redundancyString, NULL);
	newResult.setRedundancy(newRedundancy);
	
	// add new simulation result to result structure
	resultStructure.push_back(newResult);
}

int main(int argc, char**argv)
{
	
	if (argc != 8)
	{
		cout << "Invalid parameters" << endl;
		cout << "./optimizeLabelClassification errorSummaryFileName dimMin dimMax kernelWidthMin kernelWidthMax minOutMin minOutMax" << endl;
	}
	else
	{
		// initialize random number generator
		generator = gsl_rng_alloc(gsl_rng_mt19937);
		gsl_rng_set(generator, 24368);
		
		// set minimum and maximum ranges
		SimulationResult::minDimension = atof(argv[2]);
		SimulationResult::maxDimension = atof(argv[3]);
		SimulationResult::minKernelWidth = atof(argv[4]);
		SimulationResult::maxKernelWidth = atof(argv[5]);
		SimulationResult::minMinOutcomes = atof(argv[6]);
		SimulationResult::maxMinOutcomes = atof(argv[7]);
		
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
			
			char* meanRuleSetConditionCount = strtok(NULL, "\t");
			resultStructure[index].setMeanRuleSetConditionCount(strtod(meanRuleSetConditionCount, NULL));
			
			char* standardDeviationRuleSetConditionCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationRuleSetConditionCount(strtod(standardDeviationRuleSetConditionCount, NULL));
			
			char* meanRuleCount = strtok(NULL, "\t");
			resultStructure[index].setMeanRuleCount(strtod(meanRuleCount, NULL));
			
			char* standardDeviationRuleCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationRuleCount(strtod(standardDeviationRuleCount, NULL));
			
			char* meanAverageConditionsPerRuleCount = strtok(NULL, "\t");
			resultStructure[index].setMeanAverageConditionsPerRuleCount(strtod(meanAverageConditionsPerRuleCount, NULL));
			
			char* standardDeviationAverageConditionsPerRuleCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationAverageConditionsPerRuleCount(strtod(standardDeviationAverageConditionsPerRuleCount, NULL));
			
			++index;
		}
		
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
		
		// sort a copy of the result structure according to rule set condition count
		unbiasedSort(tempResultStructure, ruleSetConditionCountSortPredicate, ruleSetConditionCountEqual);
		
		// remove all but the top 20% of unique results (by rule set condition count)
		vector<SimulationResult> bestConditionCounts;
		vector<SimulationResult> uniqueConditionCounts;
		uniqueConditionCounts.push_back(tempResultStructure[0]);
		
		for (unsigned int i = 1; i < tempResultStructure.size(); ++i)
		{
			if (!ruleSetConditionCountEqual(tempResultStructure[i], tempResultStructure[i-1]))
			{
				uniqueConditionCounts.push_back(tempResultStructure[i]);
			}
		}
		
		// there must be at least one unique condition count
		// compute number to select (20% rounded down, ensuring that at least one is selected)
		numberToSelect = (int) (0.2 * uniqueConditionCounts.size());
		
		if (numberToSelect == 0)
		{
			numberToSelect = 1;
		}
		
		for (unsigned int i = 0; i < tempResultStructure.size(); ++i)
		{
			for (unsigned int j = 0; j < numberToSelect; ++j)
			{
				if (ruleSetConditionCountEqual(tempResultStructure[i], uniqueConditionCounts[j]))
				{
					bestConditionCounts.push_back(tempResultStructure[i]);
					break;
				}
			}
		}
		
		// find the best generalization error that has a condition count in the top 20% of the selected results
		bool optimalNotFound = true;
		
		for (unsigned int i = 0; i < resultStructure.size() && optimalNotFound; ++i)
		{
			for (unsigned int j = 0; j < bestConditionCounts.size(); ++j)
			{
				if ((resultStructure[i].getMeanRuleSetConditionCount() <= bestConditionCounts[j].getMeanRuleSetConditionCount()) && (resultStructure[i].getStandardDeviationRuleSetConditionCount() <= bestConditionCounts[j].getStandardDeviationRuleSetConditionCount()))
				{
					optimalNotFound = false;
					
					// retrieve the best condition
					SimulationResult mostOptimalSimulationResult(resultStructure[i]);
					
					// remove the best condition, and insert it at the front of the resultStructure list
					resultStructure.erase(resultStructure.begin() + i);
					resultStructure.insert(resultStructure.begin(), mostOptimalSimulationResult);
					
					// if the best condition also exists in the bestConditionCounts list (it might not), move it to the front of the list
					// also duplicate the second-last item in the list, so that there are always 21 items in the list
					bool bestConditionFound = false;
					
					for (unsigned int k = 0; k < bestConditionCounts.size(); ++k)
					{
						if (resultStructure[0] == bestConditionCounts[k])
						{
							bestConditionFound = true;
							
							SimulationResult mostOptimalConditionCountItem(bestConditionCounts[k]);
							bestConditionCounts.erase(bestConditionCounts.begin() + k);
							bestConditionCounts.insert(bestConditionCounts.begin(), mostOptimalConditionCountItem);
							
							break;
						}
					}
					
					// if the best condition is not in the bestConditionCounts list, add the best result by generalization error
					if (!bestConditionFound)
					{
						SimulationResult mostOptimalGeneralizationItem(resultStructure[0]);
						bestConditionCounts.insert(bestConditionCounts.begin(), mostOptimalGeneralizationItem);
					}
					
					// if the best condition also exists in the bestConditionCounts list (it might not), remove it from the list and duplicate the first item
					// (so that there are always the same number of results in the conditions file, without creating a new line)
					for (unsigned int k = 0; k < bestConditionCounts.size(); ++k)
					{
						if (resultStructure[0] == bestConditionCounts[k])
						{
							
							break;
						}
					}
					
					break;
				}
			}
		}
		
		// output the data for the generalization error FluxVis plot (all patterns)
		char* generalizationErrorOutputFileName = new char[strlen(argv[1]) + 18];
		strcpy(generalizationErrorOutputFileName, "1_generalization_");
		strcat(generalizationErrorOutputFileName, argv[1]);
		ofstream generalizationErrorOutput(generalizationErrorOutputFileName);
		
		for (unsigned int i = 0; i < resultStructure.size(); ++i) {
			resultStructure[i].printGeneralizationErrorPlotData(generalizationErrorOutput, resultStructure.size(), i);
		}
		
		delete generalizationErrorOutputFileName;
		generalizationErrorOutput.close();
		
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
		
		// output the data for the rule set condition count FluxVis plot (all patterns)
		char* ruleSetConditionCountOutputFileName = new char[strlen(argv[1]) + 14];
		strcpy(ruleSetConditionCountOutputFileName, "3_conditions_");
		strcat(ruleSetConditionCountOutputFileName, argv[1]);
		ofstream ruleSetConditionCountOutput(ruleSetConditionCountOutputFileName);
		
		for (unsigned int i = 0; i < bestConditionCounts.size(); ++i) {
			bestConditionCounts[i].printRuleSetConditionCountPlotData(ruleSetConditionCountOutput, bestConditionCounts.size(), i);
		}
		
		delete ruleSetConditionCountOutputFileName;
		ruleSetConditionCountOutput.close();
		
		// output the data for the unscaled rule set condition count FluxVis plot (all patterns)
		char* unscaledRuleSetConditionCountOutputFileName = new char[strlen(argv[1]) + 23];
		strcpy(unscaledRuleSetConditionCountOutputFileName, "4_unscaled_conditions_");
		strcat(unscaledRuleSetConditionCountOutputFileName, argv[1]);
		ofstream unscaledRuleSetConditionCountOutput(unscaledRuleSetConditionCountOutputFileName);
		
		for (unsigned int i = 0; i < bestConditionCounts.size(); ++i) {
			bestConditionCounts[i].printUnscaledRuleSetConditionCountPlotData(unscaledRuleSetConditionCountOutput, bestConditionCounts.size(), i);
		}
		
		delete unscaledRuleSetConditionCountOutputFileName;
		unscaledRuleSetConditionCountOutput.close();
		
		// output the parameters and performance characteristics of the best result
		char* mostOptimalOutputFileName = new char[strlen(argv[1]) + 15];
		strcpy(mostOptimalOutputFileName, "5_mostOptimal_");
		strcat(mostOptimalOutputFileName, argv[1]);
		ofstream mostOptimalOutput(mostOptimalOutputFileName);
		
		resultStructure[0].printAll(mostOptimalOutput);
		
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(3);
		
		cout << "Minimum dimension:            " << SimulationResult::minDimension << endl;
		cout << "Maximum dimension:            " << SimulationResult::maxDimension << endl << endl;
		cout << "Minimum kernel width:         " << SimulationResult::minKernelWidth << endl;
		cout << "Maximum kernel width:         " << SimulationResult::maxKernelWidth << endl << endl;
		cout << "Minimum minimum outcomes:     " << SimulationResult::minMinOutcomes << endl;
		cout << "Maximum minimum outcomes:     " << SimulationResult::maxMinOutcomes << endl << endl;
		cout << "Minimum generalization error: " << SimulationResult::minMeanGeneralizationError << endl;
		cout << "Maximum generalization error: " << SimulationResult::maxMeanGeneralizationError << endl << endl;
		cout << "Minimum rule complexity     : " << SimulationResult::minMeanRuleSetConditionCount << endl;
		cout << "Maximum rule complexity     : " << SimulationResult::maxMeanRuleSetConditionCount << endl;
		
		delete mostOptimalOutputFileName;
		mostOptimalOutput.close();
		errorFile.close();
		gsl_rng_free(generator);
	}
	
}
