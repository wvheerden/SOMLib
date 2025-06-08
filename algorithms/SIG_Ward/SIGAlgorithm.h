#ifndef SIGALGORITHM_H
#define SIGALGORITHM_H

#include <vector>

#include "RuleSet.h"
#include "Rule.h"
#include "RuleCondition.h"
#include "DisjunctiveCondition.h"

class SignificanceValue;
class SOMMap;
class WeightVector;
class DataFileReader;

class SIGAlgorithm {
	
	public:
		// constructor/destructor
		SIGAlgorithm(SOMMap&, DataFileReader&, double, double, double, double, double, double, bool);
		~SIGAlgorithm();
		
		// accessors
		RuleSet getRuleSet() const;
		
	private:
		// utility functions
		void buildCharacterisingRules(std::vector<std::vector<DataPattern> >&);
		void populateCharacterisingSignificanceMatrix(std::vector<std::vector<SignificanceValue> >&, std::vector<std::vector<DataPattern> >&);
		void constructCharacterisingRuleForCluster(std::vector<std::vector<SignificanceValue> >&, std::vector<std::vector<DataPattern> >&, unsigned int);
		
		void buildDifferentiatingRules(std::vector<std::vector<DataPattern> >&);
		void populateDifferentiatingSignificanceMatrix(std::vector<SignificanceValue>&, std::vector<std::vector<DataPattern> >&, unsigned int, unsigned int);
		void constructDifferentiatingConditionsFromCharacterisingRules(unsigned int, unsigned int, DisjunctiveCondition&, DisjunctiveCondition&, std::vector<std::vector<DataPattern> >&);
		std::vector<Rule*> getDifferentiatingRules(RuleSet&, unsigned int, std::vector<std::vector<RuleCondition*> >&, unsigned int, unsigned int);
		
		double calculateKSStatistic(std::vector<DataPattern>&, std::vector<DataPattern>&, unsigned int);
		double calculateChiSquareStatistic(std::vector<DataPattern>&, std::vector<DataPattern>&, unsigned int);
		
		// debugging output functions
		std::ostream& printSignificanceMatrix(std::ostream&, std::vector<std::vector<SignificanceValue> >&);
		std::ostream& printDifferentiatingSignificanceMatrix(std::ostream&, std::vector<SignificanceValue>, unsigned int, unsigned int);
	
	private:
		SOMMap& map;
		DataFileReader& trainingDataReader;
		RuleSet ruleSet;
		RuleSet prunedRuleSet;
		double characterisingThreshold;
		double characterisingLowConstant;
		double characterisingHighConstant;
		double differentiatingThreshold;
		double differentiatingLowConstant;
		double differentiatingHighConstant;
		bool isContinuous;
	
};

#endif
