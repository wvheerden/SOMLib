#ifndef MYUTILITIES_H
#define MYUTILITIES_H

#include <vector>

template <class T>
void unbiasedSort(std::vector<T>&);

template <class T>
void shuffle(std::vector<T>&, unsigned int, unsigned int);

#include "Utilities.cpp"

#endif
