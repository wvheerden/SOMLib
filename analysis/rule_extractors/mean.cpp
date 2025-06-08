#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
	double mean = 0.0;
	
	vector<double> values;
	unsigned int recordCount = 0;
	
	ifstream inputFile(argv[1]);
	
	string line;
	
	while (!inputFile.eof())
	{
		getline(inputFile, line);
		
		if (line != "")
		{
			++recordCount;
			
			stringstream stringStream(line);
			
			istream_iterator<string> iterator(stringStream);
			istream_iterator<string> end;
			
			vector<string> results(iterator, end);
			
			unsigned int index = atoi(argv[2]);
			
			istringstream valueStream(results[index]);
			double value = 0.0;
			valueStream >> value;
			
			values.push_back(value);
			
			mean += value;
		}
	}
	
	mean /= recordCount;
	
	if (strcmp(argv[3], "full") == 0)
	{
		cout << fixed << setprecision(17) << mean;
	}
	else if (strcmp(argv[3], "short") == 0)
	{
		cout << fixed << setprecision(3) << mean;
	}
	
	inputFile.close();
}
