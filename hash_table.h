/*hash table, linear probing, no remove, dynamic size*/
/*to keep hashing simple, key is unsigned int*/

#pragma once
#include <iostream>
#include "array.h"
#include <stdlib.h>
#include <stdexcept>
using namespace std;

template <typename D>
class HashTable
{
public:

	/*construct empty*/
	HashTable();
	/*construct copy*/
	HashTable(HashTable const& other);
	/*destruct*/
	~HashTable();
	/*assignment*/
	HashTable const& operator=(HashTable const& other);
	/*insert entry*/
	bool insert(D const& data, unsigned int key);
	/*find entry*/
	bool find(unsigned int key, D** ppdata);
	/*get size*/
	unsigned int getSize() const;
	
	#ifdef NDEBUG
	private:
	#endif
	
	/*struct for table entries*/
	enum EntryStat {ES_EMPTY, ES_FULL};
	struct TableEntry
	{
		EntryStat stat;
		unsigned int key;
		D data;

		#ifndef NDEBUG
		friend ostream& operator<<(ostream& os, TableEntry const& a)
		{
			if(a.stat == ES_EMPTY)
			{
				os << "empty" << endl;
			}
			else
			{
				os << a.key << ":" << a.data << endl;
			}
			return os;
		}
		#endif
	};

	Array<TableEntry>* parray; /*pointer to array*/
	unsigned int n; /*table size*/
	
	static unsigned int hash(unsigned int x, unsigned int n); /*hashing function*/
	void insertArray(TableEntry const& entry, Array<TableEntry>* parr); /*used in insert*/
};

/*implementation
********************/
template <typename D>
HashTable<D>::HashTable()
{
	/*empty array (instead of dealing with NULL)*/
	parray = new Array<TableEntry>(0, TableEntry());
	/*set table size*/
	n = 0;
}

template <typename D>
HashTable<D>::HashTable(HashTable const& other)
{
	/*new array*/
	parray = new Array<TableEntry>(*(other.parray));
	/*set table size*/
	n = other.n;
}

template <typename D>
HashTable<D>::~HashTable()
{
	delete parray;
}

template <typename D>
HashTable<D> const& HashTable<D>::operator=(HashTable const& other)
{
	/*new array*/
	Array<TableEntry>* ptemp = new Array<TableEntry>(*(other.parray));
	/*delete old*/
	delete parray;
	/*set pointer, size*/
	parray = ptemp;
	n = other.n;
}

template <typename D>
bool HashTable<D>::insert(D const& data, unsigned int key)
{
	/*if already exists*/
	if(find(key, NULL)) return false;
	unsigned int size = parray->getSize();
	/*if full*/
	if(n == size)
	{
		/*create a new array*/
		unsigned int newSize;
		if(size==0)
		{
			newSize = 1;
		}
		else
		{
			newSize = 2*size;
		}
		TableEntry emptyEnt;
		emptyEnt.stat = ES_EMPTY;
		Array<TableEntry>* ptemp = 
			new Array<TableEntry>(newSize, emptyEnt);
		/*rehash*/
		for(unsigned int i=0; i<size; ++i)
		{
			insertArray((*parray)[i], ptemp);
		}
		/*delete old*/
		delete parray;
		parray = ptemp;
	}
	/*insert*/
	TableEntry entry;
	entry.stat = ES_FULL;
	entry.key = key;
	entry.data = data;
	insertArray(entry, parray);

	++n;
	return true;
}

template <typename D>
void HashTable<D>::insertArray(TableEntry const& entry, Array<TableEntry>* parr)
{
	/*no need to insert empty*/
	if(entry.stat == ES_EMPTY) return;
	/*find place to insert*/
	unsigned int i = hash(entry.key, parr->getSize());
	while(((*parr)[i]).stat == ES_FULL)
	{
		/*next index*/
		i = (i+1)%(parr->getSize());
	}
	/*copy*/
	(*parr)[i] = entry;
}

template <typename D>
bool HashTable<D>::find(unsigned int key, D** ppdata)
{
	/*if table empty*/
	if(n==0) return false;
	/*try to find*/
	bool found = false;
	unsigned int start = hash(key, parray->getSize());
	unsigned int i = start;
	while(true)
	{
		/*break if empty*/
		if((*parray)[i].stat == ES_EMPTY) break;
		/*check if key is matching*/
		if((*parray)[i].key == key)
		{
			found = true;
			if(ppdata != NULL)
			{
				*ppdata = &((*parray)[i].data);
			}
			break;
		}
		/*next index*/
		i = (i+1)%(parray->getSize());
		/*break if completed a loop*/
		if(i==start) break;
	}
	return found;
}

template <typename D>
unsigned int HashTable<D>::hash(unsigned int x, unsigned int n)
{
	return x%n;
}

template <typename D>
unsigned int HashTable<D>::getSize() const
{
	return n;
}
