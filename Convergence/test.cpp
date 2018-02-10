#include "GewekeTest.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	GewekeTest *test = new GewekeTest() ;
	vector<double> value ;

	for(int i=1; i<=100; i++)
		value.push_back(i*1.0) ;

	bool z = test->assessConvergenceSingleChain(value, 10);
	if(z)
		cout << "Convergenc" << endl ;
	else
		cout << "Not Convergence" << endl ;

	return 0 ;
}
