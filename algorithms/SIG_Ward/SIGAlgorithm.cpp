#include <cmath>
#include <cfloat>
#include <algorithm>

#include "SIGAlgorithm.h"
#include "Utilities.h"
#include "SignificanceValue.h"
#include "SOMMap.h"
#include "Random.h"
#include "WeightVector.h"
#include "DataFileReader.h"

// *** Constructor and Destructor ***

// ===================================================
// Constructor : SIGAlgorithm(SOMMap&, DataFileReader&, double, double, double, double, double, double)
// Purpose     : Constructs SIG* algorithm with
//               supplied map, data reader and
//               algorithm parameters
// ===================================================

SIGAlgorithm::SIGAlgorithm(SOMMap& _map, DataFileReader& _trainingDataReader, double _characterisingThreshold, double _characterisingLowConstant, double _characterisingHighConstant, double _differentiatingThreshold, double _differentiatingLowConstant, double _differentiatingHighConstant, bool _isContinuous) :
map(_map), trainingDataReader(_trainingDataReader), characterisingThreshold(_characterisingThreshold), characterisingLowConstant(_characterisingLowConstant), characterisingHighConstant(_characterisingHighConstant), differentiatingThreshold(_differentiatingThreshold), differentiatingLowConstant(_differentiatingLowConstant), differentiatingHighConstant(_differentiatingHighConstant), isContinuous(_isContinuous) {
	
	// perform error checking
	if ((characterisingThreshold < 0.0) || (characterisingThreshold > 100.0)) {
		throw std::runtime_error("Characterising threshold outside range [0.0 : 100]");
	}
	
	if ((differentiatingThreshold < 0.0) || (differentiatingThreshold > 100.0)) {
		throw std::runtime_error("Differentiating threshold outside range [0.0 : 100]");
	}
	
	if (characterisingLowConstant < 0.0) {
		throw std::runtime_error("Characterising low constant outside range [0.0 : 100]");
	}
	
	if (characterisingHighConstant < 0.0) {
		throw std::runtime_error("Characterising high constant outside range [0.0 : 100]");
	}
	
	if (differentiatingLowConstant < 0.0) {
		throw std::runtime_error("Differentiating low constant outside range [0.0 : 100]");
	}
	
	if (differentiatingHighConstant < 0.0) {
		throw std::runtime_error("Differentiating high constant outside range [0.0 : 100]");
	}
	
	// retrieve the data pattern mappings to the optimal emergent clusters
	std::vector<std::vector<DataPattern> > mappedPatterns = map.getOptimalClusterMappedPatterns(trainingDataReader);
	
	// build rules
	buildCharacterisingRules(mappedPatterns);
	buildDifferentiatingRules(mappedPatterns);
	
	// order rules (fewer false positives first)
	ruleSet.calculateOrderingStats(trainingDataReader);
	ruleSet.orderRules();
	
}

// ===================================================
// Destructor : ~SIGAlgorithm()
// Purpose    : De-allocates object resources
// ===================================================

SIGAlgorithm::~SIGAlgorithm() {
	
	;
	
}

// *** Accessors ***

// ===================================================
// Utility : RuleSet getRuleSet() const
// Purpose : Return a copy of the current rule set
// ===================================================

RuleSet SIGAlgorithm::getRuleSet() const {
	
	return ruleSet;
	
}

// *** Private Utility Functions ***

// ===================================================
// Utility : void buildCharacterisingRules(vector<vector<DataPattern> >&)
// Purpose : Build and add characterising rules to
//           unified rule set
// ===================================================

void SIGAlgorithm::buildCharacterisingRules(std::vector<std::vector<DataPattern> >& mappedPatterns) {
	
	// initialise significance matrix
	std::vector<std::vector<SignificanceValue> > characterisingSignificanceMatrix;
	
	// populate significance values in matrix
	populateCharacterisingSignificanceMatrix(characterisingSignificanceMatrix, mappedPatterns);
	
	// perform rule construction for each class
	for (unsigned int i = 0; i < map.getOptimalClusterCount(); ++i) {
		constructCharacterisingRuleForCluster(characterisingSignificanceMatrix, mappedPatterns, i);
	}
	
//TEST
if (map.getOptimalClusterCount() == 1) {
	std::cout << std::endl;
	printSignificanceMatrix(std::cout, characterisingSignificanceMatrix);
	std::cout << std::endl;
}
	
}

// ===================================================
// Utility : void populateCharacterisingSignificanceMatrix(vector<vector<SignificanceValue> >&, vector<vector<DataPattern> >&)
// Purpose : Populate characterising significance
//           matrix with values
//
// NOTE    : Matrix is arranged such that rows
//           indicate clusters (i.e. classes), and
//           columns indicate attribute labels
// ===================================================

void SIGAlgorithm::populateCharacterisingSignificanceMatrix(std::vector<std::vector<SignificanceValue> >& characterisingSignificanceMatrix, std::vector<std::vector<DataPattern> >& mappedPatterns) {
	
	// build initial maximal significance value candidate vector
	std::vector<double> maxSigValues(trainingDataReader.getAttributeCount());
	
	// populate significance values for each row (i.e. cluster or class) in matrix
	for (unsigned int i = 0; i < map.getOptimalClusterCount(); ++i) {
		
		// get data pattern constituents of the cluster (class) being considered
		std::vector<DataPattern> clusterDataPatternConstituents = mappedPatterns[i];
		
		// unify constituents of all clusters (classes) other than the one being considered
		std::vector<DataPattern> otherClusterDataPatternConstituents;
		
		for (unsigned int j = 0; j < map.getOptimalClusterCount(); ++j) {
			if (j != i) {
				
				for (unsigned int k = 0; k < mappedPatterns[j].size(); ++k) {
					otherClusterDataPatternConstituents.push_back(mappedPatterns[j][k]);
				}
				
			}
		}
		
		// create new row for significance matrix
		std::vector<SignificanceValue> newCharacterisingSignificanceMatrixRow;
		
		// calculate significance value for each attribute (in the current class)
		for (unsigned int j = 0; j < trainingDataReader.getAttributeCount(); ++j) {
			
			double newSigValue = 1.0;
			
			if (map.getOptimalClusterCount() <= 0) {
				
				std::cout << "ERROR: Invalid number of clusters";
				
			} else {
				
				// calculate significance value
				// if there is only one cluster, because the other had no label, all significance values are 1.0
				// the actual significance value is irrelevant, since all attributes are marked, and thus selected
				// therefore, it would be more "correct" to use something like standard deviation, but unnecessary to do the calculation
				if (map.getOptimalClusterCount() > 1) {
					if (isContinuous) {
						newSigValue = calculateKSStatistic(clusterDataPatternConstituents, otherClusterDataPatternConstituents, j);
					} else {
						newSigValue = calculateChiSquareStatistic(clusterDataPatternConstituents, otherClusterDataPatternConstituents, j);
					}
				}
				
			}
			
			if (!std::isfinite(newSigValue)) {
				std::cerr << std::endl << "ERROR: Invalid characterising significance value computed" << std::endl;
			}
			
			SignificanceValue newSignificanceValue(j, newSigValue);
			newCharacterisingSignificanceMatrixRow.push_back(newSignificanceValue);
			
			// update maximum significance values per matrix column (i.e. attribute label)
			if ((i == 0) || ((i > 0) && (newSigValue > maxSigValues[j]))) {
				maxSigValues[j] = newSigValue;
			}
			
		}
		
		// add new row to significance matrix
		characterisingSignificanceMatrix.push_back(newCharacterisingSignificanceMatrixRow);
		
	}
	
	// mark all appropriate significance matrix cells per matrix column (i.e. attribute label)
	// NOTE: If there are only 2 clusters and the significance meaure is complementary (gives the same value for an attribute in both of the clusters),
	//       this results in ALL attributes being marked (and subsequently selected)
	
	for (unsigned int i = 0; i < trainingDataReader.getAttributeCount(); ++i) {
		for (unsigned int j = 0; j < map.getOptimalClusterCount(); ++j) {
			if (characterisingSignificanceMatrix[j][i] == maxSigValues[i]) {
				(characterisingSignificanceMatrix[j][i]).mark(true);
			}
		}
	}
	
}

// ===================================================
// Utility : void constructCharacterisingRuleForCluster(vector<vector<SignificanceValue> >&, vector<vector<DataPattern> >*, unsigned int)
// Purpose : Construct characterising conditions for
//           specified class index
//
// NOTE    : Matrix is arranged such that rows
//           indicate clusters (i.e. classes), and
//           columns indicate attribute labels
// ===================================================

void SIGAlgorithm::constructCharacterisingRuleForCluster(std::vector<std::vector<SignificanceValue> >& characterisingSignificanceMatrix, std::vector<std::vector<DataPattern> >& mappedPatterns, unsigned int cluster) {
	
	// normalise class significance values as percentages of total sum of significance values
	double significanceTotal = 0.0;
	
	for (unsigned int i = 0; i < trainingDataReader.getAttributeCount(); ++i) {
		significanceTotal += (characterisingSignificanceMatrix[cluster][i]).getValue();
	}
	
	for (unsigned int i = 0; i < trainingDataReader.getAttributeCount(); ++i) {
		characterisingSignificanceMatrix[cluster][i].normalise(significanceTotal);
		
		if (!std::isfinite(characterisingSignificanceMatrix[cluster][i].getValue())) {
			std::cerr << std::endl << "ERROR: Invalid normalised characterising significance value computed" << std::endl;
		}
	}
	
	// sort specified row into ascending order (without any order-based bias for equivalent significance values)
	unbiasedSort(characterisingSignificanceMatrix[cluster]);
	
	// build a new characterising rule and select required number of attribute conditions (based on characterising threshold)
	Rule newRule(map.getOptimalClusterLabel(cluster));
	double cumulativeSignificanceTotal = 0.0;
	unsigned int i = 0;
	
	while ((i < trainingDataReader.getAttributeCount()) && (cumulativeSignificanceTotal < characterisingThreshold)) {
		// add a condition to the new characterising rule
		unsigned int attributeIndex = (characterisingSignificanceMatrix[cluster][i]).getAttributeNumber();
		std::string attributeLabel = trainingDataReader.getAttributeLabel(attributeIndex);
		map.addRuleCondition(newRule, mappedPatterns, cluster, attributeIndex, attributeLabel, characterisingLowConstant, characterisingHighConstant);
		cumulativeSignificanceTotal += characterisingSignificanceMatrix[cluster][i].getValue();
		++i;
	}
	
	// add additionally marked attributes (that are as yet unselected)
	for (unsigned int j = i; j < trainingDataReader.getAttributeCount(); ++j) {
		if ((characterisingSignificanceMatrix[cluster][j]).isMarked()) {
			unsigned int attributeIndex = (characterisingSignificanceMatrix[cluster][j]).getAttributeNumber();
			std::string attributeLabel = trainingDataReader.getAttributeLabel(attributeIndex);
			map.addRuleCondition(newRule, mappedPatterns, cluster, attributeIndex, attributeLabel, characterisingLowConstant, characterisingHighConstant);
		}
	}
	
	// add built rule if it is not empty
	if (newRule.getRuleConditionCount() > 0) {
		ruleSet.addRule(newRule);
	}
	
}

// ===================================================
// Utility : void buildDifferentiatingRules(vector<vector<DataPattern> >&)
// Purpose : Build and add differentiating rules to
//           unified rule set
// ===================================================

void SIGAlgorithm::buildDifferentiatingRules(std::vector<std::vector<DataPattern> >& mappedPatterns) {
	
	// list of rule indices for overlapping rules, with corresponding differentiating conditions for these rules
	std::vector<unsigned int> differentiatedRuleIndices;
	std::vector<DisjunctiveCondition*> differentiatedRuleDisjunctiveConditions;
	
	// work through all possible rule pairs
	for (unsigned int i = 0; i < (ruleSet.getRuleCount() - 1); ++i) {
		for (unsigned int j = (i + 1); j < ruleSet.getRuleCount(); ++j) {
			
			// check whether current rule pair overlaps
			if (ruleSet.rulesOverlap(trainingDataReader, i, j)) {
				
				bool rule1DifferentiatingConditionFound = false;
				DisjunctiveCondition* rule1DisjunctiveCondition = NULL;
				
				bool rule2DifferentiatingConditionFound = false;
				DisjunctiveCondition* rule2DisjunctiveCondition = NULL;
				
				// search for correct differentiating condition to add a condition to
				for (unsigned int k = 0; k < differentiatedRuleIndices.size() && rule1DifferentiatingConditionFound && rule2DifferentiatingConditionFound; ++k) {
					
					if (differentiatedRuleIndices[k] == i) {
						rule1DifferentiatingConditionFound = true;
						rule1DisjunctiveCondition = differentiatedRuleDisjunctiveConditions[k];
					}
					
					if (differentiatedRuleIndices[k] == j) {
						rule2DifferentiatingConditionFound = true;
						rule2DisjunctiveCondition = differentiatedRuleDisjunctiveConditions[k];
					}
					
				}
				
				// add new (empty) differentiating conditions for first overlapping rule, if necessary
				if (!rule1DifferentiatingConditionFound) {
					differentiatedRuleIndices.push_back(i);
					differentiatedRuleDisjunctiveConditions.push_back(new DisjunctiveCondition());
					rule1DisjunctiveCondition = differentiatedRuleDisjunctiveConditions[differentiatedRuleDisjunctiveConditions.size() - 1];
				}
				
				// add new (empty) differentiating conditions for second overlapping rule, if necessary
				if (!rule2DifferentiatingConditionFound) {
					differentiatedRuleIndices.push_back(j);
					differentiatedRuleDisjunctiveConditions.push_back(new DisjunctiveCondition());
					rule2DisjunctiveCondition = differentiatedRuleDisjunctiveConditions[differentiatedRuleDisjunctiveConditions.size() - 1];
				}
				
				constructDifferentiatingConditionsFromCharacterisingRules(i, j, *rule1DisjunctiveCondition, *rule2DisjunctiveCondition, mappedPatterns);
				
				// add differentiating conditions if they are not empty
				if (rule1DisjunctiveCondition->getTotalConditionCount() > 0) {
					ruleSet.addConditionToRule(i, *rule1DisjunctiveCondition);
					ruleSet.addConditionToRule(j, *rule2DisjunctiveCondition);
				}
				
			}
			
		}
		
	}
	
	for (unsigned int i = 0; i < differentiatedRuleDisjunctiveConditions.size(); ++i) {
		delete differentiatedRuleDisjunctiveConditions[i];
	}
	
}

// ===================================================
// Utility : void populateDifferentiatingSignificanceMatrix(vector<SignificanceValue>&, vector<vector<DataPattern> >&, unsigned int, unsigned int)
// Purpose : Populate differentiating significance
//           matrix with values for the pair of
//           supplied rule indices
// ===================================================

void SIGAlgorithm::populateDifferentiatingSignificanceMatrix(std::vector<SignificanceValue>& differentiatingSignificanceMatrix, std::vector<std::vector<DataPattern> >& mappedDataPatterns, unsigned int ruleIndex1, unsigned int ruleIndex2) {
	
	std::vector<DataPattern> cluster1DataPatternConstituents = mappedDataPatterns[ruleIndex1];
	std::vector<DataPattern> cluster2DataPatternConstituents = mappedDataPatterns[ruleIndex2];
	
	double significanceTotal = 0.0;
	
	for (unsigned int i = 0; i < trainingDataReader.getAttributeCount(); ++i) {
		
		double newDiffSigValue = 0.0;
		
		if (isContinuous) {
			newDiffSigValue = calculateKSStatistic(cluster1DataPatternConstituents, cluster2DataPatternConstituents, i);
		} else {
			newDiffSigValue = calculateChiSquareStatistic(cluster1DataPatternConstituents, cluster2DataPatternConstituents, i);
		}
		
		if (!std::isfinite(newDiffSigValue)) {
			std::cerr << std::endl << "ERROR: Invalid differentiating significance value computed" << std::endl;
		}
		
		SignificanceValue newSignificanceValue(i, newDiffSigValue);
		differentiatingSignificanceMatrix.push_back(newSignificanceValue);
		significanceTotal += newDiffSigValue;
	}
	
	// normalise significance values as percentages of their total sum
	for (unsigned int i = 0; i < trainingDataReader.getAttributeCount(); ++i) {
		differentiatingSignificanceMatrix[i].normalise(significanceTotal);
		
		if (!std::isfinite(differentiatingSignificanceMatrix[i].getValue())) {
			std::cerr << std::endl << "ERROR: Invalid normalised differentiating significance value computed" << std::endl;
		}
	}
	
	// sort specified row into ascending order (without any order-based bias for equivalent significance values)
	unbiasedSort(differentiatingSignificanceMatrix);
	
}

// ===================================================
// Utility : void constructDifferentiatingConditionsFromCharacterisingRules(unsigned int, unsigned int, RuleSet&, vector<vector<DataPattern> >&)
// Purpose : Construct differentiating conditions from
//           supplied pair of characterising rule
//           indices, and differentiating rule
//           significance matrix
// ===================================================

void SIGAlgorithm::constructDifferentiatingConditionsFromCharacterisingRules(unsigned int ruleIndex1, unsigned int ruleIndex2, DisjunctiveCondition& rule1DisjunctiveCondition, DisjunctiveCondition& rule2DisjunctiveCondition, std::vector<std::vector<DataPattern> >& mappedPatterns) {
	
	// significance matrix is a single dimensional vector, since it
	// is a single column characterising the significance values
	// between only two clusters
	std::vector<SignificanceValue> differentiatingSignificanceMatrix;
	populateDifferentiatingSignificanceMatrix(differentiatingSignificanceMatrix, mappedPatterns, ruleIndex1, ruleIndex2);
	
	// add required number of differentiating attributes to the first and second overlapping rules (using characterising threshold)
	double cumulativeSignificanceTotal = 0.0;
	std::vector<RuleCondition*> firstRuleNewDifferentiatingConditionSet;
	std::vector<RuleCondition*> secondRuleNewDifferentiatingConditionSet;
	
	for (unsigned int i = 0; (i < differentiatingSignificanceMatrix.size() && (cumulativeSignificanceTotal < differentiatingThreshold)); ++i) {
		unsigned int attributeIndex = (differentiatingSignificanceMatrix[i]).getAttributeNumber();
		std::string attributeLabel = trainingDataReader.getAttributeLabel(attributeIndex);
		map.addRuleCondition(firstRuleNewDifferentiatingConditionSet, mappedPatterns, ruleIndex1, attributeIndex, attributeLabel, differentiatingLowConstant, differentiatingHighConstant);
		map.addRuleCondition(secondRuleNewDifferentiatingConditionSet, mappedPatterns, ruleIndex2, attributeIndex, attributeLabel, differentiatingLowConstant, differentiatingHighConstant);
		cumulativeSignificanceTotal += differentiatingSignificanceMatrix[i].getValue();
	}
	
	for (unsigned int i = 0; i < firstRuleNewDifferentiatingConditionSet.size(); ++i) {
		rule1DisjunctiveCondition.addAttributeCondition(*(firstRuleNewDifferentiatingConditionSet[i]));
		delete firstRuleNewDifferentiatingConditionSet[i];
		
		rule2DisjunctiveCondition.addAttributeCondition(*(secondRuleNewDifferentiatingConditionSet[i]));
		delete secondRuleNewDifferentiatingConditionSet[i];
	}
	
}

// ===================================================
// Utility : void calculateKSStatistic(vector<DataPattern>&, vector<DataPattern>&, unsigned int)
// Purpose : Calculate and return K-S statistic for
//           two floating point data distributions
// ===================================================

double SIGAlgorithm::calculateKSStatistic(std::vector<DataPattern>& vectors1, std::vector<DataPattern>& vectors2, unsigned int index) {
	
	std::vector<double> data1;
	std::vector<double> data2;
	
	// build data vectors
	for (unsigned int i = 0; i < vectors1.size(); ++i) {
		data1.push_back(vectors1[i].getComponent(index));
	}
	
	for (unsigned int i = 0; i < vectors2.size(); ++i) {
		data2.push_back(vectors2[i].getComponent(index));
	}
	
	sort(data1.begin(), data1.end());
	sort(data2.begin(), data2.end());
	
	// calculate KS metric
	unsigned int j1 = 0;
	unsigned int j2 = 0;
	double fn1 = 0.0;
	double fn2 = 0.0;
	double KSMetric = 0.0;
	
	while ((j1 < data1.size()) && (j2 < data2.size())) {
		
		double d1 = data1[j1];
		double d2 = data2[j2];
		
		if (d1 <= d2) {
			fn1 = ((double) j1 + 1.0) / ((double) data1.size());
			j1++;
		}
		
		if (d2 <= d1) {
			fn2 = ((double) j2 + 1.0) / ((double) data2.size());
			j2++;
		}
		
		double dt = fabs(fn2 - fn1);
		
		if (dt > KSMetric) {
			KSMetric = dt;
		}
		
	}
	
	return KSMetric;
	
}

// ===================================================
// Utility : void calculateChiSquareStatistic(vector<DataPattern>&, vector<DataPattern>&, unsigned int)
// Purpose : Calculate and return Pearson's
//           Chi-squared statistic for two floating
//           point data distributions
// ===================================================

double SIGAlgorithm::calculateChiSquareStatistic(std::vector<DataPattern>& vectors1, std::vector<DataPattern>& vectors2, unsigned int index) {
	
	// prepare bins (we assume binary bins for simplicity, and because we shouldn't be working with categorical data that hasn't been scaled to a range between 0 and 1)
	std::vector<double> bins1;
	bins1.push_back(0.0);
	bins1.push_back(0.0);
	
	std::vector<double> bins2;
	bins2.push_back(0.0);
	bins2.push_back(0.0);
	
	for (unsigned int i = 0; i < vectors1.size(); ++i) {
		if ((vectors1[i].getComponent(index) == 0) || (vectors1[i].getComponent(index) == 1)) {
			bins1[vectors1[i].getComponent(index)] = bins1[vectors1[i].getComponent(index)] + 1.0;
		} else {
			std::cerr << std::endl << "ERROR: Non-binary attribute value encountered" << std::endl;
		}
	}
	
	for (unsigned int i = 0; i < vectors2.size(); ++i) {
		if ((vectors2[i].getComponent(index) == 0) || (vectors2[i].getComponent(index) == 1)) {
			bins2[vectors2[i].getComponent(index)] = bins2[vectors2[i].getComponent(index)] + 1.0;
		} else {
			std::cerr << std::endl << "ERROR: Non-binary attribute value encountered" << std::endl;
		}
	}
	
	// calculate and return Chi-square statistic
	double temp;
	
	double chsq = 0.0;
	
	for (unsigned int j = 0; j < bins1.size(); j++) {
		
		if (!(bins1[j] == 0.0 && bins2[j] == 0.0)) {
			
			double observationsBins1 = 0.0;
			
			for (unsigned int k = 0; k < bins1.size(); ++k) {
				observationsBins1 += bins1[k];
			}
			
			double observationsBins2 = 0.0;
			
			for (unsigned int k = 0; k < bins2.size(); ++k) {
				observationsBins2 += bins2[k];
			}
			
			// we disregard situations where both bins contain zero observations
			// (this situation is equivalent to both bins holding an equal number of observations, which contribute 0.0 to the statistic,
			// since those bins have the same distribution)
			if ((bins1[j] != 0) || (bins2[j] != 0)) {
				temp = (sqrt(observationsBins2 / observationsBins1) * bins1[j]) - (sqrt(observationsBins1 / observationsBins2) * bins2[j]);
				chsq += temp * temp / (bins1[j] + bins2[j]);
			}
			
		}
		
	}
	
	return chsq;
	
}

// *** Debugging Output Functions ***

std::ostream& SIGAlgorithm::printSignificanceMatrix(std::ostream& out, std::vector<std::vector<SignificanceValue> >& significanceMatrix) {
	
	// print class labels
	for (unsigned int i = 0; i < significanceMatrix.size(); ++i) {
		
		std::string currentClassLabel = map.getOptimalClusterLabel(i);
		out << "Class: " << currentClassLabel;
		
		for (unsigned int j = 0; j < (20 - map.getOptimalClusterLabel(i).length()); ++j) {
			out << " ";
		}
		
	}
	
	out << std::endl;
	
	// print significance matrix
	for (unsigned int i = 0; i < significanceMatrix[0].size(); ++i) {
		for (unsigned int j = 0; j < significanceMatrix.size(); ++j) {
			out << significanceMatrix[j][i] << " ";
		}
		
		out << std::endl;
	}
	
	return out;
	
}

std::ostream& SIGAlgorithm::printDifferentiatingSignificanceMatrix(std::ostream& out, std::vector<SignificanceValue> significanceMatrix, unsigned int ruleIndex1, unsigned int ruleIndex2) {
	
	out << "Class " << ruleIndex1 << " and " << ruleIndex2 << std::endl;
	
	for (unsigned int i = 0; i < significanceMatrix.size(); ++i) {
		out << significanceMatrix[i] << std::endl;
	}
	
	return out;
	
}
