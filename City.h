#pragma once
class City
{
public:
	City(int in_id);
	bool operator<(const City& other);
	bool operator>(const City& other);
	bool operator==(const City& other);
	operator int() const;

	int getId();
	void changePopulation(int change);
	~City();

private:
	int mPopulation;
	int mId;
};
