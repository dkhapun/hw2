#include "PlanetUnion.h"

PlanetUnion::PlanetUnion(int citys) : UnionFind<CityIdSmaller>(citys)
{

}


PlanetUnion::~PlanetUnion()
{

}

City* PlanetUnion::getCity(int cityid)
{
	if (!inRange(cityid, 0, mSize))
		throw std::invalid_argument("element id is out of range");

	return mElements[cityid]->getValue();
}

void PlanetUnion::unionByRootElement(int elemA, int elemB)
{
	if (!inRange(elemA, 0, mSize) || !inRange(elemB, 0, mSize))
		throw std::invalid_argument("element id is out of range");

	UnionElement* elem1 = mElements[elemA];
	UnionElement* elem2 = mElements[elemB];

	if (elem1->getFather() != 0 || elem2->getFather() != 0 || elem1->getGroup() == elem2->getGroup())
	{
		throw std::invalid_argument("element is not a root");
	}

	unionOp(elem1->getGroup(), elem2->getGroup());
}
void PlanetUnion::updateCity(int cityId, int change)
{
	int cgroup = find(cityId);
	UnionElement* elem1 = mElements[cityId];
	elem1->getValue()->changePopulation(change);

	//need to update capital
	if (*(mGroups[cgroup].getRoot()->getValue()) < *(elem1->getValue()))
	{
		UnionElement* temp = mGroups[cgroup].getRoot();
		elem1->setGroup(&(mGroups[cgroup]));
		mGroups[cgroup].setRoot(elem1);
		temp->setFather(elem1);
	}
}

int PlanetUnion::getCapitalOfGroup(int g)
{
	if(mGroups[g].getSize() > 0)
		return mGroups[g].getRoot()->getId();
	else
		return -1;

}
