#include <algorithm>

#include "Random.h"
#include "Rule.h"
#include "SignificanceValue.h"

// ===================================================
// Utility : void unbiasedSort(std::vector<SignificanceValue>&)
// Purpose : Perform an unbiased sort of the provided
//           vector (i.e. sort in order chosen by item
//           functor, but with equivalent items in
//           equiprobable random order)
// ===================================================

template <class T>
void unbiasedSort(std::vector<T>& sortingList) {
	
	// perform initial sorting
	bool (*sortComparisonFunction)(T, T) = sortComparison;
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

// ===================================================
// Utility : void shuffle(std::vector<SignificanceValue>&, unsigned int, unsigned int)
// Purpose : Randomly shuffle (with equal probability)
//           supplied significance matrix row
//           from supplied start index (inclusively)
//           to supplied end index (inclusively)
// ===================================================

template <class T>
void shuffle(std::vector<T>& shuffleList, unsigned int startIndex, unsigned int endIndex) {
	
	for (unsigned int i = endIndex; i >= (startIndex + 1); --i) {
		unsigned int j = Random::getInstance()->getNextInt(i + 1 - startIndex) + startIndex;
		T temp = shuffleList[i];
		shuffleList[i] = shuffleList[j];
		shuffleList[j] = temp;
	}
	
}
