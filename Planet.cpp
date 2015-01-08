#include "Planet.h"

/* Description:   Construct
 * Input:         n - Number of cities in the planet.
 * May throw an exception.
 */
Planet::Planet(int n)
:planetUnion(n)
{
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
 *                INVALID_INPUT - If DS==NULL or citizenID<0.
 *                FAILURE - If a citizen with citizenID already lives in the planet, or in the case of any other problem.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::AddCitizen(int citizenID)
{


	return SUCCESS;
}


/* Description:   A citizen with ID citizenID decides to live in city.
 * Input:         citizenID - The ID of the citizen.
 *                city - The ID of the city.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, citizenID<0 or city is not an illegal city number.
 *                FAILURE - If a citizen with same ID already lives in a city,there is no citizen in the planet with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::MoveToCity(int citizenID, int city)
{


	return SUCCESS;
}



/* Description:   Joins two kingdoms of city1 and city2 together.
 *				  This can happen only if the cities are the kingdoms' capitals.
 * Input:         city1 - The identifier of the 1st city.
 *                city2 - The identifier of the 2nd city.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or either city2 or city1 are illegal city numbers.
 *                FAILURE - If either cities is not a kingdom capital, both cities belong to the same capital, or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::JoinKingdoms(int city1, int city2)
{


	return SUCCESS;
}



/* Description:   Returns the capital of the kingdom in which citizen with ID citizenID lives.
 *                The capital is the city which has the maximal number of
 *                citizens in the kingdom. In case more than one of the cities in
 *                the kingdom have the maximal number of citizens, the one with the
 *                smallest index will be chosen.
 * Input:         citizenID - The identifier of the citizen.
 * Output:        capital - The identifier of the capital city.
 * Return Values: INVALID_INPUT - If DS==NULL, citizenID<0 or capital==NULL.
 *                FAILURE - If there is no citizen in the planet with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::GetCapital(int citizenID, int* capital)
{


	return SUCCESS;
}



/* Description:   Returns the city ranked in the k-th place when all the cities in the planet are ordered by size.
 * Input:         k - The rank.
 * Output:        city - The identifier of the k-th city.
 * Return Values: INVALID_INPUT - If DS==NULL, k<0 or city==NULL.
 *                FAILURE - If there is no city in the required rank or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::SelectCity(int k, int* city)
{


	return SUCCESS;
}



/* Description:   Returns an array of the cities in the capital ranked by size.
 * Output:        results - An array of size n where the cities will be written.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or results==NULL.
 *                FAILURE - In case of an error.
 *                SUCCESS - Otherwise.
 */
StatusType Planet::GetCitiesBySize(int results[])
{


	return SUCCESS;
}

