#pragma once
#include <stdexcept>
#include "list.h"
#include "list_iter.h"
#define inRange(A, B, C) ( ((A) >= (B)) && ((A) < (C)) )
namespace UnionFind
{
	/********************************************** UnionFind *********************************************/


	template<typename T>
	class UnionFind
	{

	private:
		class Group;


		/********************************************** UnionElement *********************************************/
		class UnionElement
		{
		public:
			UnionElement(int id);
			~UnionElement();
			void SetGroup(Group* group){ mGroup = group; }
			void SetFather(UnionElement* f)
			{
				mFather = f; 
				if (f != 0)
				{
					mGroup = 0;
				}
			}

			void SetValue(T* v){ mValue = v; }

			typename UnionFind<T>::Group* GetGroup(){ return mGroup; }
			typename UnionFind<T>::UnionElement* GetFather(){ return mFather; }
			T* GetValue(){ return mValue; }

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
			void SetRoot(UnionElement* elem);
			void SetSize(int size){ mSize = size; }
			void SetId(int id){ mId = id; }

			UnionElement* GetRoot(){ return mRootElement; }
			int GetSize(){ return mSize; }
			int GetId(){ return mId; }

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

		void UpdateGroup(int elemId);
		void UnionByRootElement(int elemA, int elemB);
		int Find(int elemId);

	private:
		Group* mGroups;
		UnionElement** mElements;
		int mSize;

		void FixElementOrder(UnionElement* a, UnionElement* b);
		void UpdateElementOrder(UnionElement* smallE, UnionElement* bigE);
		void Union(Group* groupA, Group* groupB);
		void SwapValues(UnionElement* a, UnionElement* b);
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
	void UnionFind<T>::Group::SetRoot(UnionElement* elem)
	{
		mRootElement = elem;
		if (elem != 0)
		{
			elem->SetFather(0);
			elem->SetGroup(this);
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
			mGroups[i].SetRoot(elem);
			mGroups[i].SetId(i);
			elem->SetGroup(&mGroups[i]);
			mElements[i] = elem;
		}
	}

	template<typename T>
	void UnionFind<T>::UpdateGroup(int elemId)
	{
		if (!inRange(elemId, 0, mSize))
			throw std::invalid_argument("element id is out of range");
	}

	template<typename T>
	void UnionFind<T>::UpdateElementOrder(UnionElement* smallE, UnionElement* bigE)
	{

	}

	template<typename T>
	void UnionFind<T>::UnionByRootElement(int elemA, int elemB)
	{
		if (!inRange(elemA, 0, mSize) || !inRange(elemB, 0, mSize))
			throw std::invalid_argument("element id is out of range");

		UnionElement* elem1 = mElements[elemA];
		UnionElement* elem2 = mElements[elemB];

		if (elem1->GetFather() != 0 || elem2->GetFather() != 0 || elem1->GetGroup() == elem2->GetGroup())
		{
			throw std::invalid_argument("element is not a root");
		}
			
		Union(elem1->GetGroup(), elem2->GetGroup());
	}


	template<typename T>
	void UnionFind<T>::FixElementOrder(UnionElement* a, UnionElement* b)
	{

	}
	template<typename T>
	void UnionFind<T>::SwapValues(UnionElement* a, UnionElement* b)
	{
		T* temp;
		temp = a->GetValue();
		a->SetValue(b->GetValue());
		b->SetValue(temp);
	}

	template<typename T>
	void UnionFind<T>::Union(Group* groupA, Group* groupB)
	{
		if (groupA == 0 || groupB == 0)
			throw std::invalid_argument("group is null");

		Group *bigG = groupA;
		Group *smallG = groupB;

		//join small to big
		if (smallG->GetSize() > bigG->GetSize())
		{
			bigG = groupB;
			smallG = groupA;
		}

		bigG->SetSize(bigG->GetSize() + groupB->GetSize());
		smallG->SetSize(0);
		smallG->GetRoot()->SetGroup(0);
		smallG->GetRoot()->SetFather(groupA->GetRoot());

		//fix order based on element value and move root down if needed
		UnionElement * bigE = bigG->GetRoot();
		UnionElement * smallE = smallG->GetRoot();
		if (*bigE->GetValue() < *smallE->GetValue())
		{
			UnionElement * temp = bigE;
			bigG->SetRoot(smallE);
			bigE->SetFather(smallE);
			
		}
		FixElementOrder(smallG->GetRoot(), bigG->GetRoot());
		smallG->SetRoot(0);
	}

	template<typename T>
	int	UnionFind<T>::Find(int elemId)
	{
		if (elemId < 0 || elemId >= mSize)
			throw std::invalid_argument("element id is out of range");

		UnionElement* elem = mElements[elemId];
		List<UnionElement*> findPath;
		
		//find root element of elemId
		while (elem->GetFather() != 0)
		{
			findPath.insert(findPath.end(), elem);
			elem = elem->GetFather();
		}

		//flaten the tree
		for (ListIter<UnionElement*> i = findPath.begin(); i != findPath.end(); ++i)
		{
			(*i)->SetFather(elem);
		}
		return elem->GetGroup()->GetId();
	}

	template<typename T>
	UnionFind<T>::~UnionFind()
	{
		for (int i = 0; i < mSize; i++)
		{
			delete mElements[i];
			delete mGroups;
		}
	}
}