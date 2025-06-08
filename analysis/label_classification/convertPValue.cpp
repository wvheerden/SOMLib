#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Error" << endl;
		return 1;
	}
	
	char* inputPValue = argv[1];
	char* resultString = new char[strlen(inputPValue) + 13];
	int fromIndex = 0;
	int toIndex = 0;
	
	while ((fromIndex < strlen(inputPValue)) && (inputPValue[fromIndex] != 'e'))
	{
		resultString[toIndex] = inputPValue[fromIndex];
		++fromIndex;
		++toIndex;
	}
	
	if (fromIndex == strlen(inputPValue))
	{
		cout << resultString;
		return 0;
	}
	
	strcat(resultString, "\\times10^{");
	toIndex += 10;
	++fromIndex;
	
	if (inputPValue[fromIndex] == '-')
	{
		strcat(resultString, "-");
		++toIndex;
		++fromIndex;
	}
	
	while (inputPValue[fromIndex] == '0')
	{
		++fromIndex;
	}
	
	while (fromIndex < strlen(inputPValue))
	{
		//cout << inputPValue[fromIndex] << endl;
		
		
		resultString[toIndex] = inputPValue[fromIndex];
		++fromIndex;
		++toIndex;
	}
	
	strcat(resultString, "}");
	++toIndex;
	resultString[toIndex] = '\0';
	
	cout << resultString;
	
	return 0;
}
