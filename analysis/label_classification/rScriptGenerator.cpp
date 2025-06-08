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

void outputCoinRScript(char* inputFileName1, char* inputFileName2, char* indexText)
{
	vector<string> values1;
	vector<string> values2;
	
	ifstream inputFile1(inputFileName1);
	ifstream inputFile2(inputFileName2);
	
	string line1;
	string line2;
	
	while (!inputFile1.eof())
	{
		getline(inputFile1, line1);
		getline(inputFile2, line2);
		
		if ((line1 != "") && (line2 != ""))
		{
			unsigned int index = atoi(indexText);
			
			stringstream stringStream1(line1);
			
			istream_iterator<string> iterator1(stringStream1);
			istream_iterator<string> end1;
			
			vector<string> results1(iterator1, end1);
			values1.push_back(results1[index]);
			
			stringstream stringStream2(line2);
			
			istream_iterator<string> iterator2(stringStream2);
			istream_iterator<string> end2;
			
			vector<string> results2(iterator2, end2);
			values2.push_back(results2[index]);
		}
	}
	
	cout << "library(\'coin\')" << endl << "a <- c(";
	
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
	
	cout << "result = pvalue(wilcoxsign_test(a ~ b, alternative = \"two.sided\", distribution = exact(), zero.method = \"Pratt\"))" << endl;	
	cout << "if (result >= 0.01)" << endl;
	cout << "{" << endl;
	cout << "print(sprintf(\"%.3f\", result))" << endl;
	cout << "} else {" << endl;
	cout << "print(sprintf(\"%.3e\", result))" << endl;
	cout << "}";
	
	inputFile1.close();
	inputFile2.close();
}

void outputStandardRScript(char* inputFileName1, char* inputFileName2, char* indexText)
{
	vector<string> values1;
	vector<string> values2;
	
	ifstream inputFile1(inputFileName1);
	ifstream inputFile2(inputFileName2);
	
	string line1;
	string line2;
	
	while (!inputFile1.eof())
	{
		getline(inputFile1, line1);
		getline(inputFile2, line2);
		
		if ((line1 != "") && (line2 != ""))
		{
			unsigned int index = atoi(indexText);
			
			stringstream stringStream1(line1);
			
			istream_iterator<string> iterator1(stringStream1);
			istream_iterator<string> end1;
			
			vector<string> results1(iterator1, end1);
			values1.push_back(results1[index]);
			
			stringstream stringStream2(line2);
			
			istream_iterator<string> iterator2(stringStream2);
			istream_iterator<string> end2;
			
			vector<string> results2(iterator2, end2);
			values2.push_back(results2[index]);
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
	
	cout << "wilcox.test(a, b, alternative=\"two.sided\", paired=TRUE, exact=TRUE, conf.level=0.95)";
	
	inputFile1.close();
	inputFile2.close();
}

int main(int argc, char** argv)
{
	outputCoinRScript(argv[1], argv[2], argv[3]);
}
