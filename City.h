#pragma once
class City
{
public:
	City(int id);
	bool operator<(City& other);
	void increase();
	~City();
private:
	int mPopulation;
};