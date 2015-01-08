#pragma once
class City
{
public:
	City(int id);
	bool operator<(City& other);
	operator int() { return mPopulation; }
	void increase();
	~City();
private:
	int mPopulation;
};