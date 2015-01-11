#include "City.h"
City::City(int in_id)
{
	mId = in_id;
	mPopulation = 0;
}
bool City::operator==(City& other)
{
	return this->mId == other.mId;
}
bool City::operator<(City& other)
{
	if(this->mPopulation == other.mPopulation)
		return this->mId < other.mId;
	return this->mPopulation < other.mPopulation;
}
bool City::operator>(City& other)
{
	if(this->mPopulation == other.mPopulation)
		return this->mId > other.mId;
	return this->mPopulation > other.mPopulation;
}
void City::changePopulation(int change)
{
	mPopulation += change;
}
int City::getId()
{
	return mId;
}

City::operator int() const
{ 
	return mId;
}


//void City::increase()
//{

//}
City::~City()
{

}
