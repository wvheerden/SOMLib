// CURRENT TEST COMMAND: ./SIG 50 2 2 55 2 2 Ward continuous iris.11.0.map.out iris.data.0.train iris.data.0.test iris.names out.accuracy out.error
// CURRENT TEST COMMAND: ./SIG 50 2 2 55 2 2 Ward binary monks1.11.0.map.out monks1.data.0.train monks1.data.0.test monks1.names out.accuracy out.error

#include <cstdlib>
#include <cfloat>
#include <stdexcept>
#include <iomanip>
#include <cstring>

#include "SIG.h"
#include "DataFileReader.h"
#include "MapFileReader.h"
#include "SOMMap.h"
#include "SIGAlgorithm.h"
#include "RuleSet.h"
#include "Random.h"

// ===================================================
// Function: int main(int, char**)
// Purpose : Main program function
// ===================================================

int main(int argc, char** argv) {
	
	// check parameters
	if ((argc != 15) || (strcmp(argv[7], "Ward") != 0) || ((strcmp(argv[8], "continuous") != 0) && (strcmp(argv[8], "binary") != 0))) {
		std::cerr << "Error: Invalid parameters" << std::endl << std::endl;
		std::cerr << "Usage: SIG [charThresh] [charLow] [charHi] [diffThresh] [diffLow] [diffHi] Ward [continuous|binary] [SOMFile] [trainingDataFile] [testDataFile] [NamingFileName] [accuracyOutFile] [errorOutFile]" << std::endl;
		return 1;
	}
	
	try {
		// output admin
		std::cout.setf(std::ios::fixed);
		std::cerr.setf(std::ios::fixed);
		std::cout.precision(2);
		
		// validate parameters
		if ((atof(argv[1]) < 0.0) || (atof(argv[1]) > 100.0)) {
			std::cerr << "Error: Characterising threshold outside range [0.0 : 100]" << std::endl;
			return 1;
		}
		
		if ((atof(argv[4]) < 0.0) || (atof(argv[4]) > 100.0)) {
			std::cerr << "Error: Differentiating threshold outside range [0.0 : 100]" << std::endl;
			return 1;
		}
		
		if (atof(argv[2]) < 0.0) {
			std::cerr << "Characterising low constant outside range [0.0 : 100]" << std::endl;
			return 1;
		}
		
		if (atof(argv[3]) < 0.0) {
			std::cerr << "Characterising high constant outside range [0.0 : 100]" << std::endl;
			return 1;
		}
		
		if (atof(argv[5]) < 0.0) {
			std::cerr << "Differentiating low constant outside range [0.0 : 100]" << std::endl;
			return 1;
		}
		
		if (atof(argv[6]) < 0.0) {
			std::cerr << "Differentiating high constant outside range [0.0 : 100]" << std::endl;
			return 1;
		}
		
		// output algorithm parameters
		std::cout << "SIG* algorithm using parameters:" << std::endl << std::endl;
		std::cout << "Characterising significance threshold   : " << atof(argv[1]) << " %" << std::endl;
		std::cout << "Characterising condition low constant   : " << atof(argv[2]) << std::endl;
		std::cout << "Characterising condition high constant  : " << atof(argv[3]) << std::endl;
		std::cout << "Differentiating significance threshold  : " << atof(argv[4]) << " %" << std::endl;
		std::cout << "Differentiating condition low constant  : " << atof(argv[5]) << std::endl;
		std::cout << "Differentiating condition high constant : " << atof(argv[6]) << std::endl;
		std::cout << "Clustering algorithm                    : Ward" << std::endl << std::endl;
		
		// enable high precision output
		std::cout.precision(DBL_DIG);
		std::cerr.precision(DBL_DIG);
		
		// read data file
		std::cout << "Reading training data file (" << argv[10] << ")...";
		DataFileReader trainingDataReader(argv[10], argv[12]);
		std::cout << " Done" << std::endl;
		
		std::cout << "Reading test data file (" << argv[11] << ")...";
		DataFileReader testDataReader(argv[11], argv[12]);
		std::cout << " Done" << std::endl;
		
		// create map reader and get map
		std::cout << "Reading map file(" << argv[9] << ")...";
		MapFileReader mapReader(argv[9]);
		SOMMap* readMap = mapReader.getMap();
		std::cout << " Done" << std::endl;
		
		// cluster map
		std::cout << "Clustering map (Ward)...";
		readMap->wardClusterMap();
		std::cout << " Done" << std::endl;
		
		// label map
		std::cout << "Labelling map vectors";
		readMap->labelMap(trainingDataReader);
		std::cout << " (using " << readMap->getOptimalClusterCount() << " clusters)... Done" << std::endl;
		
		if (readMap->getOptimalClusterCount() != 0) {
			
			// execute SIG* algorithm on clustered map
			std::cout << "Extracting rules using SIG* algorithm...";
			
			SIGAlgorithm* ruleExtractor = NULL;
			
			if (strcmp(argv[8], "continuous") == 0) {
				ruleExtractor = new SIGAlgorithm(*readMap, trainingDataReader, atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), true);
			} else {
				ruleExtractor = new SIGAlgorithm(*readMap, trainingDataReader, atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), false);
			}
			
			RuleSet ruleSet = ruleExtractor->getRuleSet();
			std::cout << " Done" << std::endl;
			
			// evaluate training and test data
			double trainingError = 0.0;
			double trainingMisclassifiedError = 0.0;
			double trainingUnclassifiedError = 0.0;
			double testError = 0.0;
			double testMisclassifiedError = 0.0;
			double testUnclassifiedError = 0.0;
			
			std::cout << "Evaluating rule set against training data (" << argv[10] << ")...";
			ruleSet.evaluate(trainingDataReader, trainingError, trainingMisclassifiedError, trainingUnclassifiedError);
			std::cout << " Done" << std::endl;
			std::cout << "Evaluating rule set against test data (" << argv[11] << ")...";
			ruleSet.evaluate(testDataReader, testError, testMisclassifiedError, testUnclassifiedError);
			std::cout << " Done" << std::endl;
			
			double trainingAccuracy = 100.0 - trainingError;
			double trainingMisclassifiedAccuracy = 0.0;
			double trainingUnclassifiedAccuracy = 0.0;
			double testAccuracy = 100.0 - testError;
			double testMisclassifiedAccuracy = 0.0;
			double testUnclassifiedAccuracy = 0.0;
			
			// output accuracy summary to file
			std::cout << "Outputting accuracy summary...";
			std::ofstream accuracyWriter(argv[13], std::ios::out | std::ios::app);
			accuracyWriter.setf(std::ios::fixed);
			accuracyWriter.precision(DBL_DIG);
			accuracyWriter << trainingAccuracy << "\t" << trainingMisclassifiedAccuracy << "\t" << trainingUnclassifiedAccuracy << "\t" << testAccuracy << "\t" << testMisclassifiedAccuracy << "\t" << testUnclassifiedAccuracy << "\t" << ruleSet.getTotalConditionCount() << "\t" << ruleSet.getRuleCount() << "\t" << ruleSet.getAverageConditionsPerRule() << "\t" << ruleSet.getTotalConjunctiveConditionCount() << "\t" << ruleSet.getConjunctiveRuleCount() << "\t" << ruleSet.getAverageConditionsPerConjunctiveRule() << std::endl;
			accuracyWriter.close();
			std::cout << " Done" << std::endl;
			
			// output error summary to file
			std::cout << "Outputting error summary...";
			std::ofstream errorWriter(argv[14], std::ios::out | std::ios::app);
			errorWriter.setf(std::ios::fixed);
			errorWriter.precision(DBL_DIG);
			errorWriter << trainingError << "\t" << trainingMisclassifiedError << "\t" << trainingUnclassifiedError << "\t" << testError << "\t" << testMisclassifiedError << "\t" << testUnclassifiedError << "\t" << ruleSet.getTotalConditionCount() << "\t" << ruleSet.getRuleCount() << "\t" << ruleSet.getAverageConditionsPerRule()  << "\t" << ruleSet.getTotalConjunctiveConditionCount() << "\t" << ruleSet.getConjunctiveRuleCount() << "\t" << ruleSet.getAverageConditionsPerConjunctiveRule() << std::endl;
			errorWriter.close();
			std::cout << " Done" << std::endl;
			
			// print rule set to screen
			std::cout << std::endl;
			std::cout << "===================" << std::endl;
			std::cout << "Generated rule set:" << std::endl;
			std::cout << "===================" << std::endl << std::endl;
			std::cout << ruleSet << std::endl;
			
			// print summary statistics
			std::cout << "===================" << std::endl;
			std::cout << "Summary statistics:" << std::endl;
			std::cout << "===================" << std::endl << std::endl;
			std::cout << "Percentage misclassified (training set)          : " << trainingError << " %" << std::endl;
			std::cout << "Percentage misclassified (test set)              : " << testError << " %" << std::endl;
			std::cout << "Normal rule set rule count                       : " << ruleSet.getRuleCount() << " rule(s)" << std::endl;
			std::cout << "Normal rule set total condition count            : " << ruleSet.getTotalConditionCount() << " condition(s)" << std::endl;
			std::cout << "Normal rule set average conditions per rule      : " << ruleSet.getAverageConditionsPerRule() << " condition(s)" << std::endl;
			std::cout << std::endl;
			std::cout << "Conjunctive rule set rule count                  : " << ruleSet.getConjunctiveRuleCount() << " rule(s)" << std::endl;
			std::cout << "Conjunctive rule set total condition count       : " << ruleSet.getTotalConjunctiveConditionCount() << " condition(s)" << std::endl;
			std::cout << "Conjunctive rule set average conditions per rule : " << ruleSet.getAverageConditionsPerConjunctiveRule() << " condition(s)" << std::endl;
std::cout << std::endl;
std::cout << "Alt conjunctive rule set rule count                  : " << ruleSet.getConjunctiveRuleCount_alternative() << " rule(s)" << std::endl;
std::cout << "Alt conjunctive rule set total condition count       : " << ruleSet.getTotalConjunctiveConditionCount_alternative() << " condition(s)" << std::endl;
std::cout << "Alt conjunctive rule set average conditions per rule : " << ruleSet.getAverageConditionsPerConjunctiveRule_alternative() << " condition(s)" << std::endl;

std::cout << std::endl;
if ((ruleSet.getConjunctiveRuleCount() != ruleSet.getConjunctiveRuleCount_alternative()) or (ruleSet.getTotalConjunctiveConditionCount() != ruleSet.getTotalConjunctiveConditionCount_alternative()) or (ruleSet.getAverageConditionsPerConjunctiveRule() != ruleSet.getAverageConditionsPerConjunctiveRule_alternative())) {
	std::cout << "Mismatch found" << std::endl;
	std::cerr << "Mismatch found" << std::endl;
}
			
			delete ruleExtractor;
			
		} else {
			
			std::cout << std::endl;
			std::cout << "No rules extracted" << std::endl << std::endl;
			
			std::cout << "Outputting accuracy summary...";
			std::ofstream accuracyWriter(argv[13]);
			accuracyWriter.setf(std::ios::fixed);
			accuracyWriter.precision(DBL_DIG);
			accuracyWriter << 0.0 << "\t" << 0.0 << "\t" << 0.0 << "\t" << 0.0 << "\t" << 0.0 << "\t" << 0.0 << "\t" << 0.0 << "\t" << 0.0 << "\t" << 0.0;
			accuracyWriter.close();
			std::cout << " Done" << std::endl;
			
			// output error summary to file
			std::cout << "Outputting error summary...";
			std::ofstream errorWriter(argv[14]);
			errorWriter.setf(std::ios::fixed);
			errorWriter.precision(DBL_DIG);
			errorWriter << 100.0 << "\t" << 0.0 << "\t" << 100.0 << "\t" << 100.0 << "\t" << 0.0 << "\t" << 100.0 << "\t" << 0.0 << "\t" << 0.0 << "\t" << 0.0;
			errorWriter.close();
			std::cout << " Done" << std::endl;
			
			std::cout << "===================" << std::endl;
			std::cout << "Summary statistics:" << std::endl;
			std::cout << "===================" << std::endl << std::endl;
			std::cout << "Percentage misclassified (training set) : 100%" << std::endl;
			std::cout << "Percentage misclassified (test set)     : 100%" << std::endl;
			std::cout << "Rule set rule count                     : 0 rule(s)" << std::endl;
			std::cout << "Rule set condition count                : 0 condition(s)" << std::endl;
			std::cout << "Rule set average conditions per rule    : 0 condition(s)" << std::endl;
			
		}
		
		delete readMap;
		
	} catch (const std::runtime_error& e) {
		
		std::cout.flush();
		Random::reset();
		std::cerr << std::endl << e.what() << std::endl << "Exiting..." << std::endl;
		return 1;
		
	}
	
	Random::reset();
	return 0;
	
}
