CC = g++ -std=c++98 -O3 -Wall
COMMON_OBJ_FILES = Random.o DataFileReader.o DataPattern.o MapFileReader.o SOMMap.o WeightVector.o HitCount.o
OUTPUTLABELS_OBJ_FILES = outputLabels.o MapFileWriter.o CN2MapFileWriter.o C4_5MapFileWriter.o $(COMMON_OBJ_FILES)
CLASSIFY_OBJ_FILES = classify.o $(COMMON_OBJ_FILES)
LIBS = -lm -lgsl -lgslcblas

default: outputLabels classify

outputLabels: $(OUTPUTLABELS_OBJ_FILES) Makefile
	$(CC) $(OUTPUTLABELS_OBJ_FILES) $(LIBS) -o outputLabels

classify: $(CLASSIFY_OBJ_FILES) Makefile
	$(CC) $(CLASSIFY_OBJ_FILES) $(LIBS) -o classify

outputLabels.o: outputLabels.h outputLabels.cpp DataFileReader.h MapFileReader.h SOMMap.h Random.h Makefile
	$(CC) -c outputLabels.cpp

classify.o: classify.h classify.cpp DataFileReader.h MapFileReader.h SOMMap.h Random.h Makefile
	$(CC) -c classify.cpp

Random.o: Random.h Random.cpp Makefile
	$(CC) -c Random.cpp

DataFileReader.o: DataFileReader.h DataFileReader.cpp DataPattern.h Makefile
	$(CC) -c DataFileReader.cpp

DataPattern.o: DataPattern.h DataPattern.cpp Makefile
	$(CC) -c DataPattern.cpp

MapFileReader.o: MapFileReader.h MapFileReader.cpp SOMMap.h Makefile
	$(CC) -c MapFileReader.cpp

MapFileWriter.o: MapFileWriter.h MapFileWriter.cpp SOMMap.h WeightVector.o Makefile
	$(CC) -c MapFileWriter.cpp

CN2MapFileWriter.o: CN2MapFileWriter.h CN2MapFileWriter.cpp MapFileWriter.h Makefile
	$(CC) -c CN2MapFileWriter.cpp

C4_5MapFileWriter.o: C4_5MapFileWriter.h C4_5MapFileWriter.cpp MapFileWriter.h Makefile
	$(CC) -c C4_5MapFileWriter.cpp

SOMMap.o: SOMMap.h SOMMap.cpp Random.h WeightVector.o DataFileReader.h DataPattern.h Makefile
	$(CC) -c SOMMap.cpp

WeightVector.o: WeightVector.h WeightVector.cpp DataPattern.h HitCount.h Makefile
	$(CC) -c WeightVector.cpp

HitCount.o: HitCount.h HitCount.cpp Makefile
	$(CC) -c HitCount.cpp

clean:
	rm -f *.o outputLabels classify