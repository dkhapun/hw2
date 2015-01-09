#include <iostream>
#include "PlanetUnion.h"
#include "RankTree.h"

using namespace std;
using namespace avl_tree;

void test_uf()
{
	PlanetUnion u(10);
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

	RankTree<int> rtree;
	rtree.insert(2);
	rtree.insert(10);
	rtree.insert(4);
	rtree.insert(15);
	rtree.insert(16);
	rtree.insert(3);
	rtree.insert(7);
	rtree.insert(11);

	rtree.display(1);

	cout << (int)*rtree.rank(1);
	cout << (int)*rtree.rank(2);
	cout << (int)*rtree.rank(3);
	cout << (int)*rtree.rank(4);
	cout << (int)*rtree.rank(5);
	cout << (int)*rtree.rank(6);

	
}