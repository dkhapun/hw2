#pragma once
class City
{
public:
	City(int in_id);
	bool operator<(City& other);
	bool operator>(City& other);
	bool operator==(City& other);
	operator int() const;

	int getId();
	void changePopulation(int change);
	~City();
private:
	int mPopulation;
	int mId;
};
