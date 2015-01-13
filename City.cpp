#include "City.h"
City::City(int in_id)
{
	mId = in_id;
	mPopulation = 0;
}
bool City::operator==(const City& other)
{
	return this->mId == other.mId;
}
bool City::operator<(const City& other)
{
	if(this->mPopulation == other.mPopulation)
		return this->mId < other.mId;
	return this->mPopulation < other.mPopulation;
}
bool City::operator>(const City& other)
{
	if(this->mPopulation == other.mPopulation)
		return this->mId > other.mId;
	return this->mPopulation > other.mPopulation;
}
void City::changePopulation(int change)
{
	mPopulation += change;
}
int City::getId()const
{
	return mId;
}

City::operator int() const
{ 
	return mId;
}

int City::getPopulation()const
{
	return mPopulation;
}
//void City::increase()
//{

//}
City::~City()
{

}

CityIdSmaller::CityIdSmaller(int id) : City(id) { }
bool CityIdSmaller::operator<(const City& other)
{
	if(this->getPopulation() == other.getPopulation())
		return this->getId() > other.getId();
	return this->getPopulation() < other.getPopulation();
}
bool CityIdSmaller::operator>(const City& other)
{
	if(this->getPopulation() == other.getPopulation())
		return this->getId() < other.getId();
	return this->getPopulation() > other.getPopulation();
}
