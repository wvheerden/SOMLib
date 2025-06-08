#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

void stripDataFile(char* inputFileName)
{
	vector<string> values;
	ifstream inputFile(inputFileName);
	string line;
	bool firstLine = true;
	
	while (!inputFile.eof())
	{
		getline(inputFile, line);
		
		if (line != "")
		{
			stringstream stringStream(line);
			
			istream_iterator<string> iterator(stringStream);
			istream_iterator<string> end;
			
			vector<string> results(iterator, end);
			
			if (firstLine)
			{
				cout << "#";
				firstLine = false;
			}
			
			cout << results[7] << "\t";
			cout << results[8] << "\t";
			cout << results[9] << "\t";
			cout << results[10] << "\t";
			cout << results[11] << "\t";
			cout << results[12] << "\t";
			cout << results[15] << "\t";
			cout << results[16] << endl;
		}
	}
	
	inputFile.close();
}

int main(int argc, char** argv)
{
	stripDataFile(argv[1]);
}
