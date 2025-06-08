#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	cout << fixed << setprecision(3) << 0.8455684 << endl;
	cout << fixed << scientific << setprecision(3) << 4.086723e-141 << endl;
	
	if (9.223e-3 < 0.008333333) {
		cout << "YES" << endl;
	}
}

