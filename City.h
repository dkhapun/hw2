#pragma once
class City
{
public:
	City(int in_id);
	bool operator<(City& other);
	operator int() const;
	//void increase();
	void changePopulation(int change);
	~City();
private:
	int mPopulation;
	int id;
};