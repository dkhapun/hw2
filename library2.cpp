#include "library2.h"
#include "Planet.h"

/* Description:   Initializes the planet with n cities.
 * Input:         n - Number of cities in the planet.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void* Init(int n)
{
	/*check input*/
	Planet* p = 0;
	if(n < 2) 
		return NULL;
	/*new*/
	try
	{
		p = new Planet(n);
	}
	catch(...)
	{
		return NULL;
	}
	return (void*)p;
}


/* Description:   A citizen was added to the planet.
 * Input:         DS - A pointer to the data structure.
 *                citizenID - The ID of the citizen.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or citizenID<0.
 *                FAILURE - If a citizen with citizenID already lives in the planet, or in the case of any other problem.
 *                SUCCESS - Otherwise.
 */
StatusType AddCitizen(void* DS, int citizenID)
{
	Planet* p = (Planet*)DS;
	return p->AddCitizen(citizenID);
}


/* Description:   A citizen with ID citizenID decides to live in city.
 * Input:         DS - A pointer to the data structure.
 *                citizenID - The ID of the citizen.
 *                city - The ID of the city.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, citizenID<0 or city is not an illegal city number.
 *                FAILURE - If a citizen with same ID already lives in a city,there is no citizen in the planet with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   MoveToCity(void* DS, int citizenID, int city)
{
	Planet* p = (Planet*)DS;
	return p->MoveToCity(citizenID, city);
}


/* Description:   Joins two kingdoms of city1 and city2 together.
 *				  This can happen only if the cities are the kingdoms' capitals.
 * Input:         DS - A pointer to the data structure.
 *                city1 - The identifier of the 1st city.
 *                city2 - The identifier of the 2nd city.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or either city2 or city1 are illegal city numbers.
 *                FAILURE - If either cities is not a kingdom capital, both cities belong to the same capital, or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   JoinKingdoms(void* DS, int city1, int city2)
{
	Planet* p = (Planet*)DS;
	return p->JoinKingdoms(city1, city2);
}


/* Description:   Returns the capital of the kingdom in which citizen with ID citizenID lives.
 *                The capital is the city which has the maximal number of
 *                citizens in the kingdom. In case more than one of the cities in
 *                the kingdom have the maximal number of citizens, the one with the
 *                smallest index will be chosen.
 * Input:         DS - A pointer to the data structure.
 *                citizenID - The identifier of the citizen.
 * Output:        capital - The identifier of the capital city.
 * Return Values: INVALID_INPUT - If DS==NULL, citizenID<0 or capital==NULL.
 *                FAILURE - If there is no citizen in the planet with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetCapital(void* DS, int citizenID, int* capital)
{
	Planet* p = (Planet*)DS;
	return p->GetCapital(citizenID, capital);
}


/* Description:   Returns the city ranked in the k-th place when all the cities in the planet are ordered by size.
 * Input:         DS - A pointer to the data structure.
 *                k - The rank.
 * Output:        city - The identifier of the k-th city.
 * Return Values: INVALID_INPUT - If DS==NULL, k<0 or city==NULL.
 *                FAILURE - If there is no city in the required rank or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   SelectCity(void* DS, int k, int* city)
{
	Planet* p = (Planet*)DS;
	return p->SelectCity(k, city);
}


/* Description:   Returns an array of the cities in the capital ranked by size.
 * Input:         DS - A pointer to the data structure.
 * Output:        results - An array of size n where the cities will be written.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or results==NULL.
 *                FAILURE - In case of an error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetCitiesBySize(void* DS, int results[])
{
	Planet* p = (Planet*)DS;
	return p->GetCitiesBySize(results);
}

/* Description:   Quits and deletes the database.
 *                The variable pointed by DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS)
{
	Planet* p = (Planet*)(*DS);
	delete p;
	*DS = NULL;
}
