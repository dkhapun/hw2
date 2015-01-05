#include <iostream>
#include "UnionFind.h"

using namespace std;

void main()
{
	UnionFind<int> u(10);
	cout << u.find(6) <<endl;
	cout << u.find(3) <<endl;
	cout << u.find(8) <<endl;

	try{
		u.unionByElement(2, 9);
		u.unionByElement(9, 4);
		u.unionByElement(5, 6); 
		u.unionByElement(2, 9);
		u.unionByElement(4, 4);
		u.unionByElement(7, 7);
		u.unionByElement(8, 8);
	}
	catch (std::exception & e)
	{
		cout << e.what() << endl;
	}
	cout << u.find(1) << endl;
	cout << u.find(2) << endl;
	cout << u.find(3) << endl;
	cout << u.find(4) << endl;
	cout << u.find(5) << endl;
	cout << u.find(6) << endl;
	cout << u.find(7) << endl;
	cout << u.find(8) << endl;
	cout << u.find(9) << endl;

}