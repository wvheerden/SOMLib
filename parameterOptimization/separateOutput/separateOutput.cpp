#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include <gsl/gsl_rng.h>

using namespace std;

double calcPercentageUnlabeled(unsigned int mapDim, double unlabeledCount)
{
	return (unlabeledCount / (mapDim * mapDim)) * 100.0;
}

class SimulationResult {
	
	public:
		
		SimulationResult() :
			dimension(0), learningRate(0.0), learningRateDecay(0.0), kernelWidth(0.0), kernelWidthDecay(0.0), meanTrainingError(0.0), meanGeneralizationError(0.0), meanUnlabeledCount(0.0)
		{
			;
		}
		
		void setDimension(unsigned int _dimension)
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
		
		void setMeanGeneralizationError(double _meanGeneralizationError)
		{
			meanGeneralizationError = _meanGeneralizationError;
		}
		
		void setStandardDeviationGeneralizationError(double _standardDeviationGeneralizationError)
		{
			standardDeviationGeneralizationError = _standardDeviationGeneralizationError;
		}
		
		void setMeanUnlabeledCount(double _meanUnlabeledCount)
		{
			meanUnlabeledCount = _meanUnlabeledCount;
		}
		
		void setStandardDeviationUnlabeledCount(double _standardDeviationUnlabeledCount)
		{
			standardDeviationUnlabeledCount = _standardDeviationUnlabeledCount;
		}
		
		unsigned int getDimension() const
		{
			return dimension;
		}
		
		double getMeanTrainingError() const
		{
			return meanTrainingError;
		}
		
		double getMeanGeneralizationError() const
		{
			return meanGeneralizationError;
		}
		
		double getMeanUnlabeledCount() const
		{
			return meanUnlabeledCount;
		}
		
		void printAll(ostream& os)
		{
			os << dimension << setprecision(14) << fixed << "\t" << learningRate << "\t" << learningRateDecay
			   << "\t" << kernelWidth << "\t" << kernelWidthDecay << "\t" << meanTrainingError
			   << "\t" << standardDeviationTrainingError << "\t" << meanGeneralizationError
			   << "\t" << standardDeviationGeneralizationError << "\t" << meanUnlabeledCount
			   << "\t" << standardDeviationUnlabeledCount << "\t" << calcPercentageUnlabeled(dimension, meanUnlabeledCount) << endl;
		}
	
	private:
		unsigned int dimension;
		double learningRate;
		double learningRateDecay;
		double kernelWidth;
		double kernelWidthDecay;
		double meanTrainingError;
		double standardDeviationTrainingError;
		double meanGeneralizationError;
		double standardDeviationGeneralizationError;
		double meanUnlabeledCount;
		double standardDeviationUnlabeledCount;
	
};

vector<SimulationResult> results;

void processFileName(char* fileName, vector<SimulationResult>& resultStructure)
{
	// create new simulation result
	SimulationResult newResult;
	
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
	
	if (argc != 2)
	{
		cout << "Invalid parameters" << endl;
		cout << "./separateOutput errorSummaryFile" << endl;
	}
	else
	{
		// result structure
		vector<SimulationResult> resultStructure;
		
		// open file and ignore first line (the header)
		ifstream errorFile;
		errorFile.open(argv[1]);
		errorFile.ignore(1000, '\n');
		
		unsigned int index = 0;
		
		// process all remaining lines
		while (!errorFile.eof())
		{
			// read line
			char readLine1[1000];
			char readLine2[1000];
			errorFile.getline(readLine1, 1000);
			strcpy(readLine2, readLine1);
			
			// process simulation file name
			char* fileName = strtok(readLine1, "\t");
			processFileName(fileName, resultStructure);
			
			// process performance measures
			strtok(readLine2, "\t");
			char* meanTrainingError = strtok(NULL, "\t");
			resultStructure[index].setMeanTrainingError(strtod(meanTrainingError, NULL));
			
			char* standardDeviationTrainingError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationTrainingError(strtod(standardDeviationTrainingError, NULL));
			
			char* meanGeneralizationError = strtok(NULL, "\t");
			resultStructure[index].setMeanGeneralizationError(strtod(meanGeneralizationError, NULL));
			
			char* standardDeviationGeneralizationError = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationGeneralizationError(strtod(standardDeviationGeneralizationError, NULL));
			
			char* meanUnlabeledCount = strtok(NULL, "\t");
			resultStructure[index].setMeanUnlabeledCount(strtod(meanUnlabeledCount, NULL));
			
			char* standardDeviationUnlabeledCount = strtok(NULL, "\t");
			resultStructure[index].setStandardDeviationUnlabeledCount(strtod(standardDeviationUnlabeledCount, NULL));
			
			++index;
		}
		
		// output the separated data
		char* separatedOutputFileName = new char[strlen(argv[1]) + 11];
		strcpy(separatedOutputFileName, argv[1]);
		strcat(separatedOutputFileName, ".separated");
		ofstream separatedOutput(separatedOutputFileName);
		
		separatedOutput << "dimension\t" << "learningRate\t" << "learningRateDecay\t" << "kernelWidth\t" << "kernelWidthDecay\t"
			        << "meanTrainingError\t" << "standardDeviationTrainingError\t" << "meanGeneralizationError\t"
			        << "standardDeviationGeneralizationError\t" << "meanUnlabeledCount\t" << "standardDeviationUnlabeledCount\t" << "meanUnlabeledPercentage" << endl;
		
		for (unsigned int i = 0; i < resultStructure.size(); ++i) {
			resultStructure[i].printAll(separatedOutput);
		}
		
		separatedOutput.close();
		errorFile.close();
	}
	
}
