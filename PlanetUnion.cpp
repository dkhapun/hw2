#include "PlanetUnion.h"

PlanetUnion::PlanetUnion(int citys) : UnionFind<City>(citys)
{

}


PlanetUnion::~PlanetUnion()
{

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