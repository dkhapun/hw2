#include "Planet.h"

using namespace avl_tree;

/* Description:   Construct
 * Input:         n - Number of cities in the planet.
 * May throw an exception.
 */
Planet::Planet(int in_n)
:planetUnion(in_n)
{
	n = in_n;
	/*init tree*/
      /*create a list of cities*/
      List< RankNode<City> > tempList;
      for(int i=0; i<in_n; ++i)
      {
    	/*insert city with id = i*/
      	RankNode<City> node( new City(i) ); //this is bad
      	tempList.insert(tempList.end(), node);
      }
      /*init tree from the list*/
      citiesTree = avl_tree::RankTree<City>( tempList );
      citiesTree.display(1);
}

/* Description:   Destruct
 */
Planet::~Planet()
{
}

/* Description:   Add citizen
 * Input:         citizenID - The ID of the citizen.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If citizenID<0.
 *                FAILURE - If a citizen with citizenID already lives in the planet, or in the case of any other problem.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::AddCitizen(int citizenID)
{
	if(citizenID < 0) return INVALID_INPUT;
	if(!citizensTable.insert(-1, citizenID))
	{
		return FAILURE; //already exists
	}
	return SUCCESS;
}


/* Description:   A citizen with ID citizenID decides to live in city.
 * Input:         citizenID - The ID of the citizen.
 *                city - The ID of the city.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If citizenID<0 or city is not an illegal city number.
 *                FAILURE - If a citizen with same ID already lives in a city,there is no citizen in the planet with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::MoveToCity(int citizenID, int city)
{
	/*check input*/
	if(citizenID<0 || city<0 || city>(n-1)) return INVALID_INPUT;
	/*find citizen*/
	int* pcity;
	if(!citizensTable.find(citizenID, &pcity)) return FAILURE; //citizen not found
	if(*pcity != -1) return FAILURE; //already in a city
	/*set city of citizen*/
	*pcity = city;
	/*+1 to the city in union find, it might update the capital*/
	planetUnion.updateCity(city, 1);
	/*remove city from rank tree*/
	RankNode<City>* pNode = citiesTree.find(city);
	if(pNode == NULL) return FAILURE; //can't find city in tree
	City cityCopy = *(pNode->value);
cout << "here" << endl;

	citiesTree.remove(city);
	/*insert back with +1 citizens*/
	cityCopy.changePopulation(1);
	citiesTree.insert(cityCopy);
	return SUCCESS;
}



/* Description:   Joins two kingdoms of city1 and city2 together.
 *				  This can happen only if the cities are the kingdoms' capitals.
 * Input:         city1 - The identifier of the 1st city.
 *                city2 - The identifier of the 2nd city.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If either city2 or city1 are illegal city numbers.
 *                FAILURE - If either cities is not a kingdom capital, both cities belong to the same capital, or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::JoinKingdoms(int city1, int city2)
{
	/*check input*/
	if(city1<0 || city1>(n-1) || city2<0 || city2>(n-1)) return INVALID_INPUT;
	try
	{
		this->planetUnion.unionByRootElement(city1, city2);
	}
	catch(...)
	{
		return FAILURE;
	}
	return SUCCESS;
}



/* Description:   Returns the capital of the kingdom in which citizen with ID citizenID lives.
 *                The capital is the city which has the maximal number of
 *                citizens in the kingdom. In case more than one of the cities in
 *                the kingdom have the maximal number of citizens, the one with the
 *                smallest index will be chosen.
 * Input:         citizenID - The identifier of the citizen.
 * Output:        capital - The identifier of the capital city.
 * Return Values: INVALID_INPUT - If citizenID<0 or capital==NULL.
 *                FAILURE - If there is no citizen in the planet with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::GetCapital(int citizenID, int* capital)
{
	/*check input*/
	if(citizenID<0 || capital == NULL) return INVALID_INPUT;
	int* data = 0;
	if (false == this->citizensTable.find(citizenID, &data))
		return FAILURE;
	int groupid;
	try
	{

		groupid = planetUnion.find(*data);
	}
	catch(...)
	{
if(citizenID == 0) cout << *data << endl;
		return FAILURE;
	}
	*capital = planetUnion.getCapitalOfGroup(groupid);
	return SUCCESS;
}



/* Description:   Returns the city ranked in the k-th place when all the cities in the planet are ordered by size.
 * Input:         k - The rank.
 * Output:        city - The identifier of the k-th city.
 * Return Values: INVALID_INPUT - If k<0 or city==NULL.
 *                FAILURE - If there is no city in the required rank or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::SelectCity(int k, int* city)
{
	if (k < 0 || city == NULL)
		return INVALID_INPUT;
	try
	{
		*city = citiesTree.select(k)->getId();
	}
	catch(...)
	{
		return FAILURE;
	}
	if (city == 0)
		return FAILURE;
	return SUCCESS;
}

class AddElementToArray
{
public:
	AddElementToArray(int* results) : i(0), mResult(results) {}
	void operator()(const RankNode<City>& data)
	{
		mResult[i] = data.value->getId();
		i++;
	}
	int i;
	int* mResult;
};

/* Description:   Returns an array of the cities in the capital ranked by size.
 * Output:        results - An array of size n where the cities will be written.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If results==NULL.
 *                FAILURE - In case of an error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::GetCitiesBySize(int results[])
{


	if (results == 0)
		return INVALID_INPUT;
	AddElementToArray func = AddElementToArray(results);
	citiesTree.forEachInorder(func);


	return SUCCESS;
}

