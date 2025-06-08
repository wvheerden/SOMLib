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

void outputRScript(char* inputFileName, char* indexText1, char* indexText2)
{
	vector<string> values1;
	vector<string> values2;
	
	ifstream inputFile(inputFileName);
	string line;
	bool firstLine = true;
	
	while (!inputFile.eof())
	{
		getline(inputFile, line);
		
		if (line != "")
		{
			if (firstLine)
			{
				firstLine = false;
			}
			else
			{
				unsigned int index1 = atoi(indexText1);
				unsigned int index2 = atoi(indexText2);
				
				stringstream stringStream(line);
				
				istream_iterator<string> iterator(stringStream);
				istream_iterator<string> end;
				
				vector<string> results(iterator, end);
				values1.push_back(results[index1]);
				values2.push_back(results[index2]);
			}
		}
	}
	
	cout << "a <- c(";
	
	for (unsigned int i = 0; i < values1.size(); ++i)
	{
		cout << values1[i];
		
		if (i != values1.size() - 1)
		{
			cout << ", ";
		} else
		{
			cout << ")" << endl;
		}
	}
	
	cout << "b <- c(";
	
	for (unsigned int i = 0; i < values2.size(); ++i)
	{
		cout << values2[i];
		
		if (i != values2.size() - 1)
		{
			cout << ", ";
		} else
		{
			cout << ")" << endl;
		}
	}
	
	cout << "result = cor.test(a, b, alternative = \"two.sided\", method = \"spearman\", exact = TRUE, conf.level = 0.95, continuity = TRUE)" << endl;
	cout << "result$estimate" << endl;
	cout << "result$p.value";
	
	inputFile.close();
}

int main(int argc, char** argv)
{
	outputRScript(argv[1], argv[2], argv[3]);
}
