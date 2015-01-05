#pragma once
#include <stdexcept>
#include "list.h"
#include "list_iter.h"
#define inRange(A, B, C) ( ((A) >= (B)) && ((A) < (C)) )

/********************************************** UnionFind *********************************************/


template<typename T>
class UnionFind
{

protected:
	class Group;


	/********************************************** UnionElement *********************************************/
	class UnionElement
	{
	public:
		UnionElement(int id);
		~UnionElement();
		void setGroup(Group* group){ mGroup = group; }
		void setFather(UnionElement* f)
		{
			mFather = f; 
			if (f != 0)
			{
				mGroup = 0;
			}
		}

		void setValue(T* v){ mValue = v; }

		typename UnionFind<T>::Group* getGroup(){ return mGroup; }
		typename UnionFind<T>::UnionElement* getFather(){ return mFather; }
		T* getValue(){ return mValue; }

	private:
		int mId;
		UnionElement* mFather;
		UnionElement** mChildren;
		Group* mGroup;
		T* mValue;
	};

	/********************************************** Group *********************************************/
	class Group
	{
	public:
		void setRoot(UnionElement* elem);
		void setSize(int size){ mSize = size; }
		void setId(int id){ mId = id; }

		UnionElement* getRoot(){ return mRootElement; }
		int getSize(){ return mSize; }
		int getId(){ return mId; }

		Group();
		~Group();

	private:
		int mId;
		int mSize;
		UnionElement* mRootElement;
	};

public:
	UnionFind(int groups);
	~UnionFind();

	void updateGroup(int elemId);
	void unionByElement(int elemA, int elemB);

	int find(int elemId);

protected:
	void updateElementOrder(UnionElement* smallE, UnionElement* bigE);
	void unionOp(Group* groupA, Group* groupB);
	void swapValues(UnionElement* a, UnionElement* b);

protected:
	Group* mGroups;
	UnionElement** mElements;
	int mSize;

	void fixElementOrder(UnionElement* a, UnionElement* b);

};



/********************************************** Implementation *********************************************/

/********************************************** UnionElement *********************************************/
template<typename T>
UnionFind<T>::UnionElement::UnionElement(int id) : mId(id), mFather(0), mGroup(0), mValue(0)
{
	mValue = new T(id);
}

template<typename T>
UnionFind<T>::UnionElement::~UnionElement()
{
	if (mValue != 0)
	{
		delete mValue;
	}
}

/********************************************** Group *********************************************/
template<typename T>
void UnionFind<T>::Group::setRoot(UnionElement* elem)
{
	mRootElement = elem;
	if (elem != 0)
	{
		elem->setFather(0);
		elem->setGroup(this);
	}
		
}
	
template<typename T>
UnionFind<T>::Group::Group() : mId(0), mSize(1), mRootElement(0)
{

}

template<typename T>
UnionFind<T>::Group::~Group(){}

/********************************************** UnionFind *********************************************/
template<typename T>
UnionFind<T>::UnionFind(int groups)
{
	mGroups = new Group[groups];
	mElements = new UnionElement*[groups];
	mSize = groups;

	for (int i = 0; i < groups; ++i)
	{
		UnionElement* elem = new UnionElement(i);
		mGroups[i].setRoot(elem);
		mGroups[i].setId(i);
		elem->setGroup(&mGroups[i]);
		mElements[i] = elem;
	}
}

template<typename T>
void UnionFind<T>::updateGroup(int elemId)
{
	if (!inRange(elemId, 0, mSize))
		throw std::invalid_argument("element id is out of range");
}

template<typename T>
void UnionFind<T>::updateElementOrder(UnionElement* smallE, UnionElement* bigE)
{

}

template<typename T>
void UnionFind<T>::unionByElement(int elemA, int elemB)
{
	if (!inRange(elemA, 0, mSize) || !inRange(elemB, 0, mSize))
		throw std::invalid_argument("element id is out of range");

	UnionElement* elem1 = mElements[elemA];
	UnionElement* elem2 = mElements[elemB];

	unionOp(elem1->getGroup(), elem2->getGroup());
}


template<typename T>
void UnionFind<T>::fixElementOrder(UnionElement* a, UnionElement* b)
{

}
template<typename T>
void UnionFind<T>::swapValues(UnionElement* a, UnionElement* b)
{
	T* temp;
	temp = a->getValue();
	a->setValue(b->getValue());
	b->setValue(temp);
}

template<typename T>
void UnionFind<T>::unionOp(Group* groupA, Group* groupB)
{
	if (groupA == 0 || groupB == 0)
		throw std::invalid_argument("group is null");

	Group *bigG = groupA;
	Group *smallG = groupB;

	//join small to big
	if (smallG->getSize() > bigG->getSize())
	{
		bigG = groupB;
		smallG = groupA;
	}

	bigG->setSize(bigG->getSize() + groupB->getSize());
	smallG->setSize(0);
	smallG->getRoot()->setGroup(0);
	smallG->getRoot()->setFather(groupA->getRoot());

	//fix order based on element value and move root down if needed
	UnionElement * bigE = bigG->getRoot();
	UnionElement * smallE = smallG->getRoot();
	if (*bigE->getValue() < *smallE->getValue())
	{
		UnionElement * temp = bigE;
		bigG->setRoot(smallE);
		bigE->setFather(smallE);
			
	}
	fixElementOrder(smallG->getRoot(), bigG->getRoot());
	smallG->setRoot(0);
}

template<typename T>
int	UnionFind<T>::find(int elemId)
{
	if (elemId < 0 || elemId >= mSize)
		throw std::invalid_argument("element id is out of range");

	UnionElement* elem = mElements[elemId];
	List<UnionElement*> findPath;
		
	//find root element of elemId
	while (elem->getFather() != 0)
	{
		findPath.insert(findPath.end(), elem);
		elem = elem->getFather();
	}

	//flaten the tree
	for (ListIter<UnionElement*> i = findPath.begin(); i != findPath.end(); ++i)
	{
		(*i)->setFather(elem);
	}
	return elem->getGroup()->getId();
}

template<typename T>
UnionFind<T>::~UnionFind()
{
	for (int i = 0; i < mSize; i++)
	{
		delete mElements[i];
		delete[] mGroups;
	}
}
