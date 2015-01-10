#pragma once
class City
{
public:
	City(int id);
	bool operator<(City& other);
	operator int() { return mPopulation; }
	void increase();
	void changePopulation(int change);
	~City();
private:
	int mPopulation;
	int id;
};