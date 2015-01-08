#pragma once
#include "City.h"
#include "UnionFind.h"
class PlanetUnion : public UnionFind<City>
{
public:
	PlanetUnion(int citys);

	void unionByRootElement(int elemA, int elemB);

	~PlanetUnion();
};

