#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Invalid parameters" << endl;
		return 1;
	}
	
	double value = atof(argv[1]);
	
	if (value < 1000.0)
	{
		cout << argv[1];
	}
	else
	{
		cout << argv[1][0] << "\\;";
		
		for (int i = 1; i < strlen(argv[1]); ++i)
		{
			cout << argv[1][i];
		}
	}
	
	return 0;
}
