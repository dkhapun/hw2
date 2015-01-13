#include "Planet.h"
#include "assert.h"

using namespace avl_tree;
void union_and_tree_test();
int main()
{

	//List<City> cities;
	//RankTree<City> tree;
	//RankTree<City> lsttree;
	Planet p(100);
      //citiesTree.display(1);

	/*test AddCitizen*/
	/********************************/
	/*try to add citizen with invalid ID*/
	assert(p.AddCitizen(-1) == INVALID_INPUT);
	/*add some citizens*/
	int m = 20;
	int id[] = {0, 3, 64, 2, 7,
			55, 6, 34, 65, 9,
			12, 16, 13, 15, 19,
			11, 23, 24, 22, 27 };

    /*test AddCitizen*/
    /********************************/
    /*try to add citizen with invalid ID*/
    assert(p.AddCitizen(-1) == INVALID_INPUT);
    /*add some citizens*/
    for(int i=0; i<m; ++i)
    {
	assert(p.AddCitizen(id[i]) == SUCCESS);
    }
    /*try to add some duplicate*/
    assert(p.AddCitizen(0) == FAILURE);
    assert(p.AddCitizen(64) == FAILURE);
    assert(p.AddCitizen(22) == FAILURE);

	/*test MoveToCity*/
	/********************************/
    /*try to move invalid id*/
    assert(p.MoveToCity(-1, 0) == INVALID_INPUT);
    /*try to move to invalid city*/
    assert(p.MoveToCity(0, -1) == INVALID_INPUT);
    assert(p.MoveToCity(0, 100) == INVALID_INPUT);
    /*try to move ids that dont exist*/
    assert(p.MoveToCity(1, 0) == FAILURE);
    assert(p.MoveToCity(4, 0) == FAILURE);
    /*move all citizens to some city*/
    int city[] = {0, 1, 2, 3, 4,
		9, 8, 7, 6, 5,
		10, 11, 12, 13, 14,
		75, 20, 51, 29, 99 };

	for(int i=0; i<m; ++i)
	{
		assert(p.MoveToCity(id[i], city[i]) == SUCCESS);
	}
	/*try to move someone again*/
	assert(p.MoveToCity(0, 0) == FAILURE);
	assert(p.MoveToCity(3, 0) == FAILURE);

	/*test JoinKingdoms*/
	/********************************/
	/*try with invalid city*/
	assert(p.JoinKingdoms(-1, 0) == INVALID_INPUT);
	assert(p.JoinKingdoms(100, 0) == INVALID_INPUT);
	assert(p.JoinKingdoms(0, -1) == INVALID_INPUT);
	assert(p.JoinKingdoms(0, 100) == INVALID_INPUT);
	/*try with same city*/
	assert(p.JoinKingdoms(0, 0) == FAILURE);
	/*join some cities*/
	int uni[] = {0, 1,
			2, 3,
			4, 5,
			6, 7,
			8, 9};
	for(int i=0; i<(5*2); i+=2)
	{
		assert(p.JoinKingdoms(uni[i], uni[i+1]) == SUCCESS);
	}
	/*try to join using non capital*/
	assert(p.JoinKingdoms(0, 1) == FAILURE);
	assert(p.JoinKingdoms(0, 3) == FAILURE);
	/*join some more*/
	int uni2[] = {10, 11,
			10, 12,
			10, 13,
			10, 14,
			10, 15,
			10, 16,
			10, 17,
			10, 18,
			10, 19,

			20, 21,
			20, 22, 
			20, 23, 
			20, 24,
			20, 25,
			20, 26,
			20, 27,
			20, 28,
			20, 29,

			10, 20};
	for(int i=0; i<(19*2); i+=2)
	{
cout << uni2[i] << " " << uni2[i+1] << endl;
		assert(p.JoinKingdoms(uni2[i], uni2[i+1]) == SUCCESS);
	}

	/*test GetCapital*/
	/********************************/
	/*try with invalid input*/
      int capi;
      assert(p.GetCapital(-1, &capi) == INVALID_INPUT);
      assert(p.GetCapital(0, NULL) == INVALID_INPUT);
      /*try with unknown id*/
      assert(p.GetCapital(123, &capi) == FAILURE);
      /*try with a citizen without a city*/
      assert(p.AddCitizen(123) == SUCCESS);
      assert(p.GetCapital(123, &capi) == FAILURE);
	/*get some capitals*/
      assert(p.GetCapital(0, &capi) == SUCCESS); assert(capi == 0);
      assert(p.GetCapital(55, &capi) == SUCCESS); assert(capi == 8);
      assert(p.GetCapital(12, &capi) == SUCCESS); assert(capi == 10);
      assert(p.GetCapital(11, &capi) == SUCCESS); assert(capi == 75);
      assert(p.GetCapital(9, &capi) == SUCCESS); assert(capi == 4);
      assert(p.GetCapital(23, &capi) == SUCCESS); assert(capi == 10);

	/*test SelectCity*/
	/********************************/
	/*try with invalid input*/
      int scity;
      assert(p.SelectCity(-1, &scity) == INVALID_INPUT);
      assert(p.SelectCity(100, &scity) == INVALID_INPUT);
      assert(p.SelectCity(0, NULL) == INVALID_INPUT);
      /*select some*/
      assert(p.SelectCity(0, &scity) == SUCCESS);  assert(scity == 15);
      assert(p.SelectCity(1, &scity) == SUCCESS);  assert(scity == 16);
      assert(p.SelectCity(2, &scity) == SUCCESS);  assert(scity == 17);
      assert(p.SelectCity(80, &scity) == SUCCESS); assert(scity == 0);
      assert(p.SelectCity(81, &scity) == SUCCESS); assert(scity == 1);
      assert(p.SelectCity(82, &scity) == SUCCESS); assert(scity == 2);
      assert(p.SelectCity(83, &scity) == SUCCESS); assert(scity == 3);
      assert(p.SelectCity(83, &scity) == SUCCESS); assert(scity == 3);
      assert(p.SelectCity(98, &scity) == SUCCESS);  assert(scity == 75);
      assert(p.SelectCity(99, &scity) == SUCCESS);  assert(scity == 99);

      assert(p.AddCitizen(234) == SUCCESS);
      assert(p.MoveToCity(234, 0) == SUCCESS);
      assert(p.SelectCity(99, &scity) == SUCCESS);  assert(scity == 0);

      /*test GetCitiesBySize*/
      /********************************/
      int allcities[100];
      assert(p.MoveToCity(123, 10) == SUCCESS);
      assert(p.GetCitiesBySize(allcities) == SUCCESS);
      for(int i=90; i<100; ++i)
      {
      	cout << allcities[i] << endl;
      }
	return 0;
}

//
void union_and_tree_test()
{
	PlanetUnion u(10);
	cout << u.find(6) << endl;
	cout << u.find(3) << endl;
	cout << u.find(8) << endl;

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

	RankTree<City> rtree;
	rtree.insert(City(2));
	rtree.insert(City(10));
	rtree.insert(City(4));
	rtree.insert(City(15));
	rtree.insert(City(16));
	rtree.insert(City(3));
	rtree.insert(City(7));
	rtree.insert(City(11));

	rtree.display(1);

	cout << endl << (int) *rtree.select(1);
	cout << endl << (int) *rtree.select(2);
	cout << endl << (int) *rtree.select(3);
	cout << endl << (int) *rtree.select(4);
	cout << endl << (int) *rtree.select(5);
	cout << endl << (int) *rtree.select(6);
	cout << endl << (int) *rtree.select(7);
	cout << endl << (int) *rtree.select(8);

}
