#include "City.h"
City::City(int id)
{
	
}
bool City::operator<(City& other)
{
	return this->mPopulation < other.mPopulation;
}

void City::changePopulation(int change)
{
	mPopulation += change;
}


void City::increase()
{

}
City::~City()
{

}