#include <cstdlib>
#include <cmath>
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
			
			characterisingThreshold = 0.0;
			characterisingLow = 0.0;
			characterisingHigh = 0.0;
			differentiatingThreshold = 0.0;
			differentiatingLow = 0.0;
			differentiatingHigh = 0.0;
			
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
			
			meanTotalConjunctiveConditionCount = 0.0;
			standardDeviationTotalConjunctiveConditionCount = 0.0;
			meanConjunctiveRuleCount = 0.0;
			standardDeviationConjunctiveRuleCount = 0.0;
			meanAverageConditionsPerConjunctiveRule = 0.0;
			standardDeviationAverageConditionsPerConjunctiveRule = 0.0;
		}
		
		SimulationResult(const SimulationResult& source)
		{
			recordNumber = source.recordNumber;
			
			dimension = source.dimension;
			learningRate = source.learningRate;
			learningRateDecay = source.learningRateDecay;
			kernelWidth = source.kernelWidth;
			kernelWidthDecay = source.kernelWidthDecay;
			
			characterisingThreshold = source.characterisingThreshold;
			characterisingLow = source.characterisingLow;
			characterisingHigh = source.characterisingHigh;
			differentiatingThreshold = source.differentiatingThreshold;
			differentiatingLow = source.differentiatingLow;
			differentiatingHigh = source.differentiatingHigh;
			
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
			
			meanTotalConjunctiveConditionCount = source.meanTotalConjunctiveConditionCount;
			standardDeviationTotalConjunctiveConditionCount = source.standardDeviationTotalConjunctiveConditionCount;
			meanConjunctiveRuleCount = source.meanConjunctiveRuleCount;
			standardDeviationConjunctiveRuleCount = source.standardDeviationConjunctiveRuleCount;
			meanAverageConditionsPerConjunctiveRule = source.meanAverageConditionsPerConjunctiveRule;
			standardDeviationAverageConditionsPerConjunctiveRule = source.standardDeviationAverageConditionsPerConjunctiveRule;
		}
		
		bool operator==(const SimulationResult& source)
		{
			if ((dimension == source.dimension) && (learningRate == source.learningRate) && (learningRateDecay == source.learningRateDecay) &&
			    (kernelWidth == source.kernelWidth) && (kernelWidthDecay == source.kernelWidthDecay) &&
			    (characterisingThreshold == source.characterisingThreshold) && (characterisingLow == source.characterisingLow) &&
			    (characterisingHigh == source.characterisingHigh) && (differentiatingThreshold == source.differentiatingThreshold) &&
			    (differentiatingLow == source.differentiatingLow) && (differentiatingHigh == source.differentiatingHigh) &&
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
			    (standardDeviationAverageConditionsPerRuleCount == source.standardDeviationAverageConditionsPerRuleCount) &&
			    (meanTotalConjunctiveConditionCount == source.meanTotalConjunctiveConditionCount) &&
			    (standardDeviationTotalConjunctiveConditionCount == source.standardDeviationTotalConjunctiveConditionCount) &&
			    (meanConjunctiveRuleCount == source.meanConjunctiveRuleCount) &&
			    (standardDeviationConjunctiveRuleCount == source.standardDeviationConjunctiveRuleCount) &&
			    (standardDeviationAverageConditionsPerConjunctiveRule == source.standardDeviationAverageConditionsPerConjunctiveRule))
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
		
		void setCharacterisingThreshold(double _characterisingThreshold)
		{
			characterisingThreshold = _characterisingThreshold;
		}
		
		void setCharacterisingLow(double _characterisingLow)
		{
			characterisingLow = _characterisingLow;
		}
		
		void setCharacterisingHigh(double _characterisingHigh)
		{
			characterisingHigh = _characterisingHigh;
		}
		
		void setDifferentiatingThreshold(double _differentiatingThreshold)
		{
			differentiatingThreshold = _differentiatingThreshold;
		}
		
		void setDifferentiatingLow(double _differentiatingLow)
		{
			differentiatingLow = _differentiatingLow;
		}
		
		void setDifferentiatingHigh(double _differentiatingHigh)
		{
			differentiatingHigh = _differentiatingHigh;
		}
		
		void setMeanTrainingError(double _meanTrainingError)
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
		
		void setMeanConjunctiveRuleCount(double _meanConjunctiveRuleCount)
		{
			meanConjunctiveRuleCount = _meanConjunctiveRuleCount;
		}
		
		void setStandardDeviationConjunctiveRuleCount(double _standardDeviationConjunctiveRuleCount)
		{
			standardDeviationConjunctiveRuleCount = _standardDeviationConjunctiveRuleCount;
		}
		
		void setMeanAverageConditionsPerConjunctiveRule(double _meanAverageConditionsPerConjunctiveRule)
		{
			meanAverageConditionsPerConjunctiveRule = _meanAverageConditionsPerConjunctiveRule;
		}
		
		void setStandardDeviationAverageConditionsPerConjunctiveRule(double _standardDeviationAverageConditionsPerConjunctiveRule)
		{
			standardDeviationAverageConditionsPerConjunctiveRule = _standardDeviationAverageConditionsPerConjunctiveRule;
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
		
		void setMeanTotalConjunctiveConditionCount(double _meanTotalConjunctiveConditionCount)
		{
			meanTotalConjunctiveConditionCount = _meanTotalConjunctiveConditionCount;
			
			if (meanTotalConjunctiveConditionCount > maxMeanTotalConjunctiveConditionCount)
			{
				SimulationResult::maxMeanTotalConjunctiveConditionCount = meanTotalConjunctiveConditionCount;
			}
			
			if (meanTotalConjunctiveConditionCount < minMeanTotalConjunctiveConditionCount)
			{
				SimulationResult::minMeanTotalConjunctiveConditionCount = meanTotalConjunctiveConditionCount;
			}
		}
		
		void setStandardDeviationTotalConjunctiveConditionCount(double _standardDeviationTotalConjunctiveConditionCount)
		{
			standardDeviationTotalConjunctiveConditionCount = _standardDeviationTotalConjunctiveConditionCount;
		}
		
		double getMeanTotalConjunctiveConditionCount() const
		{
			return meanRuleSetConditionCount;
		}
		
		double getStandardDeviationTotalConjunctiveConditionCount() const
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
			os << "5 " << scale(characterisingThreshold, SimulationResult::minCharacterisingThreshold, SimulationResult::maxCharacterisingThreshold, 0.0, 1.0) << endl;
			os << "6 " << scale(characterisingLow, SimulationResult::minCharacterisingLow, SimulationResult::maxCharacterisingLow, 0.0, 1.0) << endl;
			os << "7 " << scale(characterisingHigh, SimulationResult::minCharacterisingHigh, SimulationResult::maxCharacterisingHigh, 0.0, 1.0) << endl;
			os << "8 " << scale(differentiatingThreshold, SimulationResult::minDifferentiatingThreshold, SimulationResult::maxDifferentiatingThreshold, 0.0, 1.0) << endl;
			os << "9 " << scale(differentiatingLow, SimulationResult::minDifferentiatingLow, SimulationResult::maxDifferentiatingLow, 0.0, 1.0) << endl;
			os << "10 " << scale(differentiatingHigh, SimulationResult::minDifferentiatingHigh, SimulationResult::maxDifferentiatingHigh, 0.0, 1.0) << endl;
			os << "11 " << scale(meanGeneralizationError, SimulationResult::minMeanGeneralizationError, SimulationResult::maxMeanGeneralizationError, 0.0, 1.0) << endl;
			os << "12 " << log10(scale(meanTotalConjunctiveConditionCount, SimulationResult::minMeanTotalConjunctiveConditionCount, SimulationResult::maxMeanTotalConjunctiveConditionCount, 1.0, SimulationResult::logScaleBase)) / log10(SimulationResult::logScaleBase) << endl;
			
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
			os << "5 " << characterisingThreshold << endl;
			os << "6 " << characterisingLow << endl;
			os << "7 " << characterisingHigh << endl;
			os << "8 " << differentiatingThreshold << endl;
			os << "9 " << differentiatingLow << endl;
			os << "10 " << differentiatingHigh << endl;
			os << "11 " << meanGeneralizationError << endl;
			os << "12 " << std::scientific << meanTotalConjunctiveConditionCount << endl;
			
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
			os << "5 " << scale(characterisingThreshold, SimulationResult::minCharacterisingThreshold, SimulationResult::maxCharacterisingThreshold, 0.0, 1.0) << endl;
			os << "6 " << scale(characterisingLow, SimulationResult::minCharacterisingLow, SimulationResult::maxCharacterisingLow, 0.0, 1.0) << endl;
			os << "7 " << scale(characterisingHigh, SimulationResult::minCharacterisingHigh, SimulationResult::maxCharacterisingHigh, 0.0, 1.0) << endl;
			os << "8 " << scale(differentiatingThreshold, SimulationResult::minDifferentiatingThreshold, SimulationResult::maxDifferentiatingThreshold, 0.0, 1.0) << endl;
			os << "9 " << scale(differentiatingLow, SimulationResult::minDifferentiatingLow, SimulationResult::maxDifferentiatingLow, 0.0, 1.0) << endl;
			os << "10 " << scale(differentiatingHigh, SimulationResult::minDifferentiatingHigh, SimulationResult::maxDifferentiatingHigh, 0.0, 1.0) << endl;
			os << "11 " << scale(meanGeneralizationError, SimulationResult::minMeanGeneralizationError, SimulationResult::maxMeanGeneralizationError, 0.0, 1.0) << endl;
			os << "12 " << log10(scale(meanTotalConjunctiveConditionCount, SimulationResult::minMeanTotalConjunctiveConditionCount, SimulationResult::maxMeanTotalConjunctiveConditionCount, 1.0, SimulationResult::logScaleBase)) / log10(SimulationResult::logScaleBase) << endl;  // log scale with base 1.000 x 10^125
			
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
			os << "5 " << characterisingThreshold << endl;
			os << "6 " << characterisingLow << endl;
			os << "7 " << characterisingHigh << endl;
			os << "8 " << differentiatingThreshold << endl;
			os << "9 " << differentiatingLow << endl;
			os << "10 " << differentiatingHigh << endl;
			os << "11 " << meanGeneralizationError << endl;
			os << "12 " << std::scientific << meanTotalConjunctiveConditionCount << endl;
			
			if (recordIndex < totalRecordCount - 1)
			{
				os << endl << endl << endl;
			}
		}
		
		void printAll(ostream& os)
		{
			os << "dimension\t" << "learningRate\t" << "learningRateDecay\t" << "kernelWidth\t" << "kernelWidthDecay\t"
			   << "characterisingThreshold\t" << "characterisingLow\t" << "characterisingHigh\t"
			   << "differentiatingThreshold\t" << "differentiatingLow\t" << "differentiatingHigh\t"
			   << "meanTrainingError\t" << "standardDeviationTrainingError\t"
			   << "meanTrainingMisclassifiedError\t" << "standardDeviationTrainingMisclassifiedError\t"
			   << "meanTrainingUnclassifiedError\t" << "standardDeviationTrainingUnclassifiedError\t"
			   << "meanGeneralizationError\t" << "standardDeviationGeneralizationError\t"
			   << "meanGeneralizationMisclassifiedError\t" << "standardDeviationGeneralizationMisclassifiedError\t"
			   << "meanGeneralizationUnclassifiedError\t" << "standardDeviationGeneralizationUnclassifiedError\t"
			   << "meanRuleSetConditionCount\t" << "standardDeviationRuleSetConditionCount\t"
			   << "meanRuleCount\t" << "standardDeviationRuleCount\t"
			   << "meanAverageConditionsPerRuleCount\t" << "standardDeviationAverageConditionsPerRuleCount\t"
			   << "meanTotalConjunctiveConditionCount\t" << "standardDeviationTotalConjunctiveConditionCount\t"
			   << "meanConjunctiveRuleCount\t" << "standardDeviationConjunctiveRuleCount\t"
			   << "meanAverageConditionsPerConjunctiveRule\t" << "standardDeviationAverageConditionsPerConjunctiveRule" << endl;
			
			os << setprecision(14) << fixed << dimension << "\t" << learningRate << "\t" << learningRateDecay
			   << "\t" << kernelWidth << "\t" << kernelWidthDecay
			   << "\t" << characterisingThreshold << "\t" << characterisingLow << "\t" << characterisingHigh
			   << "\t" << differentiatingThreshold << "\t" << differentiatingLow << "\t" << differentiatingHigh
			   << "\t" << meanTrainingError << "\t" << standardDeviationTrainingError
			   << "\t" << meanTrainingMisclassifiedError << "\t" << standardDeviationTrainingMisclassifiedError
			   << "\t" << meanTrainingUnclassifiedError << "\t" << standardDeviationTrainingUnclassifiedError
			   << "\t" << meanGeneralizationError << "\t" << standardDeviationGeneralizationError
			   << "\t" << meanGeneralizationMisclassifiedError << "\t" << standardDeviationGeneralizationMisclassifiedError
			   << "\t" << meanGeneralizationUnclassifiedError << "\t" << standardDeviationGeneralizationUnclassifiedError
			   << "\t" << meanRuleSetConditionCount << "\t" << standardDeviationRuleSetConditionCount
			   << "\t" << meanRuleCount << "\t" << standardDeviationRuleCount
			   << "\t" << meanAverageConditionsPerRuleCount << "\t" << standardDeviationAverageConditionsPerRuleCount
			   << "\t" << meanTotalConjunctiveConditionCount << "\t" << standardDeviationTotalConjunctiveConditionCount
			   << "\t" << meanConjunctiveRuleCount << "\t" << standardDeviationConjunctiveRuleCount
			   << "\t" << meanAverageConditionsPerConjunctiveRule << "\t" << standardDeviationAverageConditionsPerConjunctiveRule << endl;
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
		
		double characterisingThreshold;
		static double maxCharacterisingThreshold;
		static double minCharacterisingThreshold;
		
		double characterisingLow;
		static double maxCharacterisingLow;
		static double minCharacterisingLow;
		
		double characterisingHigh;
		static double maxCharacterisingHigh;
		static double minCharacterisingHigh;
		
		double differentiatingThreshold;
		static double maxDifferentiatingThreshold;
		static double minDifferentiatingThreshold;
		
		double differentiatingLow;
		static double maxDifferentiatingLow;
		static double minDifferentiatingLow;
		
		double differentiatingHigh;
		static double maxDifferentiatingHigh;
		static double minDifferentiatingHigh;
		
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
		double standardDeviationRuleSetConditionCount;
		double meanRuleCount;
		double standardDeviationRuleCount;
		double meanAverageConditionsPerRuleCount;
		double standardDeviationAverageConditionsPerRuleCount;
		
		double meanTotalConjunctiveConditionCount;
		static double maxMeanTotalConjunctiveConditionCount;
		static double minMeanTotalConjunctiveConditionCount;
		
		double standardDeviationTotalConjunctiveConditionCount;
		double meanConjunctiveRuleCount;
		double standardDeviationConjunctiveRuleCount;
		double meanAverageConditionsPerConjunctiveRule;
		double standardDeviationAverageConditionsPerConjunctiveRule;
		
		static double logScaleBase;
	
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
double SimulationResult::maxCharacterisingThreshold = 100.0;
double SimulationResult::minCharacterisingThreshold = 0.0;
double SimulationResult::maxCharacterisingLow = 3.0;
double SimulationResult::minCharacterisingLow = 0.0;
double SimulationResult::maxCharacterisingHigh = 3.0;
double SimulationResult::minCharacterisingHigh = 0.0;
double SimulationResult::maxDifferentiatingThreshold = 100.0;
double SimulationResult::minDifferentiatingThreshold = 0.0;
double SimulationResult::maxDifferentiatingLow = 3.0;
double SimulationResult::minDifferentiatingLow = 0.0;
double SimulationResult::maxDifferentiatingHigh = 3.0;
double SimulationResult::minDifferentiatingHigh = 0.0;
double SimulationResult::maxMeanGeneralizationError = -DBL_MAX;
double SimulationResult::minMeanGeneralizationError = DBL_MAX;
double SimulationResult::maxMeanTotalConjunctiveConditionCount = -DBL_MAX;
double SimulationResult::minMeanTotalConjunctiveConditionCount = DBL_MAX;
double SimulationResult::logScaleBase = 0.0;

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
			if (result1.getMeanTotalConjunctiveConditionCount() < result2.getMeanTotalConjunctiveConditionCount())
			{
				return true;
			}
			
			if (result1.getMeanTotalConjunctiveConditionCount() == result2.getMeanTotalConjunctiveConditionCount())
			{
				if (result1.getStandardDeviationTotalConjunctiveConditionCount() < result2.getStandardDeviationTotalConjunctiveConditionCount())
				{
					return true;
				}
				
				if (result1.getStandardDeviationTotalConjunctiveConditionCount() == result2.getStandardDeviationTotalConjunctiveConditionCount())
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
	if (result1.getMeanTotalConjunctiveConditionCount() < result2.getMeanTotalConjunctiveConditionCount())
	{
		return true;
	}
	
	if (result1.getMeanTotalConjunctiveConditionCount() == result2.getMeanTotalConjunctiveConditionCount())
	{
		if (result1.getStandardDeviationTotalConjunctiveConditionCount() < result2.getStandardDeviationTotalConjunctiveConditionCount())
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
	return ((result1.getMeanGeneralizationError() == result2.getMeanGeneralizationError()) && (result1.getStandardDeviationGeneralizationError() == result2.getStandardDeviationGeneralizationError()) && (result1.getMeanTotalConjunctiveConditionCount() == result2.getMeanTotalConjunctiveConditionCount()) && (result1.getStandardDeviationTotalConjunctiveConditionCount() == result2.getStandardDeviationTotalConjunctiveConditionCount()) && (result1.getMeanTrainingError() == result2.getMeanTrainingError()) && (result1.getStandardDeviationTrainingError() == result2.getStandardDeviationTrainingError()));
}

bool ruleSetConditionCountEqual(const SimulationResult& result1, const SimulationResult& result2)
{
	return ((result1.getMeanTotalConjunctiveConditionCount() == result2.getMeanTotalConjunctiveConditionCount()) && (result1.getStandardDeviationTotalConjunctiveConditionCount() == result2.getStandardDeviationTotalConjunctiveConditionCount()));
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
	
	// remove _charThr_
	strtok(NULL, "_");
	
	// extract characterising threshold
	char* characterisingThresholdString = strtok(NULL, "_");
	double newCharacterisingThreshold = strtod(characterisingThresholdString, NULL);
	newResult.setCharacterisingThreshold(newCharacterisingThreshold);
	
	// remove _charL_
	strtok(NULL, "_");
	
	// extract characterising low value
	char* characterisingLowString = strtok(NULL, "_");
	double newCharacterisingLow = strtod(characterisingLowString, NULL);
	newResult.setCharacterisingLow(newCharacterisingLow);
	
	// remove _charH_
	strtok(NULL, "_");
	
	// extract characterising high value
	char* characterisingHighString = strtok(NULL, "_");
	double newCharacterisingHigh = strtod(characterisingHighString, NULL);;
	newResult.setCharacterisingHigh(newCharacterisingHigh);
	
	// remove _diffThr_
	strtok(NULL, "_");
	
	// extract differentiating threshold
	char* differentiatingThresholdString = strtok(NULL, "_");
	double newDifferentiatingThreshold = strtod(differentiatingThresholdString, NULL);
	newResult.setDifferentiatingThreshold(newDifferentiatingThreshold);
	
	// remove _diffL_
	strtok(NULL, "_");
	
	// extract characterising low value
	char* differentiatingLowString = strtok(NULL, "_");
	double newDifferentiatingLow = strtod(differentiatingLowString, NULL);
	newResult.setDifferentiatingLow(newDifferentiatingLow);
	
	// remove _diffH_
	strtok(NULL, "_");
	
	// extract differentiating high value
	char* differentiatingHighString = strtok(NULL, "_");
	double newDifferentiatingHigh = strtod(differentiatingHighString, NULL);;
	newResult.setDifferentiatingHigh(newDifferentiatingHigh);
	
	// add new simulation result to result structure
	resultStructure.push_back(newResult);
}

int main(int argc, char**argv)
{
	
	if (argc != 7)
	{
		cout << "Invalid parameters" << endl;
		cout << "./optimizeLabelClassification errorSummaryFileName dimMin dimMax kernelWidthMin kernelWidthMax logScaleBase" << endl;
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
		SimulationResult::logScaleBase = atof(argv[6]);
		
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
			
			char* meanTotalConjunctiveConditionCount = strtok(NULL, "\t");
			resultStructure[index].setMeanTotalConjunctiveConditionCount(strtod(meanTotalConjunctiveConditionCount, NULL));
			
			char* standardDeviationTotalConjunctiveConditionCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationTotalConjunctiveConditionCount(strtod(standardDeviationTotalConjunctiveConditionCount, NULL));
			
			char* meanConjunctiveRuleCount = strtok(NULL, "\t");
			resultStructure[index].setMeanConjunctiveRuleCount(strtod(meanConjunctiveRuleCount, NULL));
			
			char* standardDeviationConjunctiveRuleCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationConjunctiveRuleCount(strtod(standardDeviationConjunctiveRuleCount, NULL));
			
			char* meanAverageConditionsPerConjunctiveRule = strtok(NULL, "\t");
			resultStructure[index].setMeanAverageConditionsPerConjunctiveRule(strtod(meanAverageConditionsPerConjunctiveRule, NULL));
			
			char* standardDeviationAverageConditionsPerConjunctiveRule = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationAverageConditionsPerConjunctiveRule(strtod(standardDeviationAverageConditionsPerConjunctiveRule, NULL));
			
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
				if ((resultStructure[i].getMeanTotalConjunctiveConditionCount() <= bestConditionCounts[j].getMeanTotalConjunctiveConditionCount()) && (resultStructure[i].getStandardDeviationTotalConjunctiveConditionCount() <= bestConditionCounts[j].getStandardDeviationTotalConjunctiveConditionCount()))
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
		cout << "Minimum generalization error: " << SimulationResult::minMeanGeneralizationError << endl;
		cout << "Maximum generalization error: " << SimulationResult::maxMeanGeneralizationError << endl << endl;
		cout << "Minimum rule complexity     : " << SimulationResult::minMeanTotalConjunctiveConditionCount << endl;
		std::cout.precision(3);
		cout << "Maximum rule complexity     : " << std::scientific << SimulationResult::maxMeanTotalConjunctiveConditionCount << endl << endl;
		cout << "Log scale base              : " << std::scientific << SimulationResult::logScaleBase << endl;
		
		delete mostOptimalOutputFileName;
		mostOptimalOutput.close();
		errorFile.close();
		gsl_rng_free(generator);
	}
	
}
