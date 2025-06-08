#include <iostream>
#include <fstream>
#include <cfloat>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
	ifstream source(argv[1]);
	
	double max = DBL_MIN;
	double min = DBL_MAX;
	
	while (!source.eof())
	{
		double discard = 0.0;
		double mean = 0.0;
		double standardDeviation = 0.0;
		
		// discard first value in line
		source >> discard;
		
		// read second value (mean) in line
		source >> mean;
		
		// read third value (standard deviation) in line
		source >> standardDeviation;
		
		double minCurrentRow = mean - standardDeviation;
		double maxCurrentRow = mean + standardDeviation;
		
		if (!source.eof())
		{
			if (maxCurrentRow > max)
			{
				max = maxCurrentRow;
			}
			
			if (minCurrentRow < min)
			{
				min = minCurrentRow;
			}
		}
	}
	
	if ((max - min) < 0.00000000000000001)
	{
		cout << "[-1:1]";
	}
	else
	{
		cout << fixed << setprecision(17) << "[" << (min - (0.05 * (max - min))) << ":" << (max + (0.05 * (max - min))) << "]";
	}
	
	return 0;
}
