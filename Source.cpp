#include <iostream>
#include "UnionFind.h"

using namespace std;

void main()
{
	UnionFind::UnionFind<int> u(10);
	cout << u.Find(6) <<endl;
	cout << u.Find(3) <<endl;
	cout << u.Find(8) <<endl;

	try{
		u.UnionByRootElement(2, 9);
		u.UnionByRootElement(9, 4);
		u.UnionByRootElement(5, 6); 
		u.UnionByRootElement(2, 9);
		u.UnionByRootElement(4, 4);
		u.UnionByRootElement(7, 7);
		u.UnionByRootElement(8, 8);
	}
	catch (std::exception & e)
	{
		cout << e.what() << endl;
	}
	cout << u.Find(1) << endl;
	cout << u.Find(2) << endl;
	cout << u.Find(3) << endl;
	cout << u.Find(4) << endl;
	cout << u.Find(5) << endl;
	cout << u.Find(6) << endl;
	cout << u.Find(7) << endl;
	cout << u.Find(8) << endl;
	cout << u.Find(9) << endl;

}