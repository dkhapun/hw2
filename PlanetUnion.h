#pragma once
#include "City.h"
#include "UnionFind.h"
class PlanetUnion : public UnionFind<CityIdSmaller>
{
public:
	PlanetUnion(int citys);
	City* getCity(int cityid);
	void unionByRootElement(int elemA, int elemB);
	void updateCity(int id, int change);
	int getCapitalOfGroup(int g);
	~PlanetUnion();
};

