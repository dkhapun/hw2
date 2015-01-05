#include <iostream>
using namespace std;
#include "array.h"

int array_test()
{
Array<int> a0(0);
try
{
	cout << a0[0] << endl;
}
catch(out_of_range const&)
{
	cout << "catched" << endl;
}
/**/
Array<int> a1(1);
cout << a1[0] << endl;
try
{
	cout << a1[1] << endl;
}
catch(out_of_range const&)
{
	cout << "catched" << endl;
}
/**/
Array<int> a1i2(1,2);
cout << a1i2[0] << endl;
/**/
Array<int> const a_cnst_cpy(a1i2);
cout << a_cnst_cpy[0] << endl;
/**/
Array<int> a10(10);
for(int i=0; i<5; ++i)
{
	a10[i] = i;
}
for(int i=0; i<10; ++i)
{
	cout << a10[i] << " ";
}
cout << endl;
/**/
Array<int> const a10_cpy(a10);
for(int i=0; i<10; ++i)
{
	cout << a10_cpy[i] << " ";
}

return 0;
}
