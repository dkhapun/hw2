#pragma once
class City
{
public:
	City(int in_id);
	virtual bool operator<(const City& other);
	virtual bool operator>(const City& other);
	bool operator==(const City& other);
	operator int() const;

	int getId() const;
	int getPopulation() const;
	void changePopulation(int change);
	virtual ~City();

protected:
	int mPopulation;
	int mId;
};

class CityIdSmaller : public City
{
public:
	CityIdSmaller(int in_id);
	virtual bool operator<(const City& other);
	virtual bool operator>(const City& other);
};
