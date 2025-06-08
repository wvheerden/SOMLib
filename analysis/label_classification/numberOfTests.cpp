#include <iostream>
#include <cstdlib>

using namespace std;

int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main(int argc, char** argv)
{
	int numAlgorithms = atoi(argv[1]);
	cout << factorial(numAlgorithms) / (2 * factorial(numAlgorithms - 2));
}

