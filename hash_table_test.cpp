#include <iostream>
using namespace std;
#include "hash_table.h"

int main2()
{
int* p;
HashTable<int> a;
cout << "size: ";
cout << a.getSize() << endl;
cout << "find 0: ";
cout << a.find(0, NULL) << endl;
cout << endl;

cout << "inserting 7 at 1234: ";
cout << a.insert(7,1234) << endl;
cout << "size: ";
cout << a.getSize() << endl;
cout << "find 1234: ";
cout << a.find(1234, &p) << endl;
cout << "value 1234: ";
cout << *p << endl;
cout << "inserting again at 1234: ";
cout << a.insert(7,1234) << endl;
cout << endl;

cout << "inserting 3 at 345234: ";
cout << a.insert(3,345234) << endl;
cout << "size: ";
cout << a.getSize() << endl;
cout << "find 345234: ";
cout << a.find(345234, &p) << endl;
cout << "value 345234: ";
cout << *p << endl;
cout << endl;

cout << "inserting 30 members" << endl;
for(int i=100; i<130; ++i)
{
	cout << a.insert(i-100,i) << " ";
}
cout << endl;
cout << "size: ";
cout << a.getSize() << endl;
for(int i=100; i<130; ++i)
{
	//cout << a.find(i, &p) << " ";
	a.find(i, &p);
	cout << *p << " ";
}
cout << endl;

return 0;
}
