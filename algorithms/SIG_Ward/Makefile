CC = g++ -O3 -Wall
OBJ_FILES = SIG.o Random.o DataFileReader.o DataPattern.o MapFileReader.o SOMMap.o MapCluster.o WeightVector.o AggregateMapCluster.o HitCount.o SIGAlgorithm.o SignificanceValue.o RuleSet.o Rule.o RuleCondition.o AttributeCondition.o DisjunctiveCondition.o LessThanRuleCondition.o GreaterThanRuleCondition.o
LIBS = -lm -lgsl -lgslcblas

SIG: $(OBJ_FILES) Makefile
	$(CC) $(OBJ_FILES) $(LIBS) -o SIG

SIG.o: SIG.h SIG.cpp DataFileReader.h MapFileReader.h SOMMap.h SIGAlgorithm.h RuleSet.h Random.h Makefile
	$(CC) -c SIG.cpp

Random.o: Random.h Random.cpp Makefile
	$(CC) -c Random.cpp

DataFileReader.o: DataFileReader.h DataFileReader.cpp DataPattern.h Makefile
	$(CC) -c DataFileReader.cpp

DataPattern.o: DataPattern.h DataPattern.cpp Makefile
	$(CC) -c DataPattern.cpp

MapFileReader.o: MapFileReader.h MapFileReader.cpp SOMMap.h Makefile
	$(CC) -c MapFileReader.cpp

SOMMap.o: SOMMap.h SOMMap.cpp Random.h WeightVector.h AggregateMapCluster.h DataFileReader.h DataPattern.h GreaterThanRuleCondition.h LessThanRuleCondition.h Makefile
	$(CC) -c SOMMap.cpp

MapCluster.o: MapCluster.h MapCluster.cpp Random.h HitCount.h Makefile
	$(CC) -c MapCluster.cpp

WeightVector.o: WeightVector.h WeightVector.cpp MapCluster.h DataPattern.h HitCount.h Makefile
	$(CC) -c WeightVector.cpp

AggregateMapCluster.o: AggregateMapCluster.h AggregateMapCluster.cpp MapCluster.h HitCount.h Makefile
	$(CC) -c AggregateMapCluster.cpp

HitCount.o: HitCount.h HitCount.cpp Makefile
	$(CC) -c HitCount.cpp

SIGAlgorithm.o: SIGAlgorithm.h SIGAlgorithm.cpp Utilities.h Utilities.cpp SignificanceValue.h SOMMap.h Random.h WeightVector.h DataFileReader.h RuleSet.h Rule.h RuleCondition.h Makefile
	$(CC) -c SIGAlgorithm.cpp

SignificanceValue.o: SignificanceValue.h SignificanceValue.cpp Makefile
	$(CC) -c SignificanceValue.cpp

RuleSet.o: RuleSet.h RuleSet.cpp Utilities.h Utilities.cpp Rule.h DataFileReader.h DataPattern.h Random.h RuleCondition.h Makefile
	$(CC) -c RuleSet.cpp

Rule.o: Rule.h Rule.cpp DataPattern.h Makefile
	$(CC) -c Rule.cpp

RuleCondition.o: RuleCondition.h RuleCondition.cpp DataPattern.h Makefile
	$(CC) -c RuleCondition.cpp

AttributeCondition.o: AttributeCondition.h AttributeCondition.cpp RuleCondition.h Makefile
	$(CC) -c AttributeCondition.cpp

DisjunctiveCondition.o: DisjunctiveCondition.h DisjunctiveCondition.cpp RuleCondition.h Makefile
	$(CC) -c DisjunctiveCondition.cpp

LessThanRuleCondition.o: LessThanRuleCondition.h LessThanRuleCondition.cpp AttributeCondition.h Makefile
	$(CC) -c LessThanRuleCondition.cpp

GreaterThanRuleCondition.o: GreaterThanRuleCondition.h GreaterThanRuleCondition.cpp AttributeCondition.h Makefile
	$(CC) -c GreaterThanRuleCondition.cpp

clean:
	rm -f *.o SIG