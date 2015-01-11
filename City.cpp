#include "City.h"
City::City(int in_id)
{
	id = in_id;
	mPopulation = 0;
}
bool City::operator<(City& other)
{
	return this->mPopulation < other.mPopulation;
}

void City::changePopulation(int change)
{
	mPopulation += change;
}

City::operator int() const
{ 
	return mPopulation;
}


//void City::increase()
//{

//}
City::~City()
{

}