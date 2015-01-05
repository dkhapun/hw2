/*array with init in O(1)*/

#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
using namespace std;

template <typename D>
class Array
{
	public:
	
	/*construct array of given size, init value*/
	Array(unsigned int in_n, D const& in_init = 0);

	/*construct copy*/
	Array(Array const& other);

	/*destruct*/
	~Array();

	/*assignment*/
	Array const& operator=(Array const& other);

	/*operator []*/
	D& operator[](unsigned int i);

	/*operator [] const*/
	D const& operator[](unsigned int i) const;

	/*get size*/
	unsigned int getSize() const;

	#ifndef NDEBUG
	friend ostream& operator<<(ostream& os, Array const& a)
	{
		os << "array size: " << a.n << endl;
		os << "init members: " << a.nstack << endl;
		os << "init value: " << a.init;
		os << "members:" << endl;
		for(unsigned int i=0; i<a.n; ++i)
		{
			os << a.pdata_array[i];
		}
	}
	#endif

	#ifdef NDEBUG
	private:
	#endif
	unsigned int n; /*array size*/
	D* pdata_array; /*pointer to data array*/
	unsigned int* pindex_array; /*pointer to array of stack indexes*/
	unsigned int* pstack_array; /*pointer to stack*/
	unsigned int nstack; /*number of members in stack*/
	D init; /*initial value*/

	void copyOther(Array const& other); /*for copy and assignment*/
};

/*implementation
********************/
template <typename D>
Array<D>::Array(unsigned int in_n, D const& in_init)
{
	/*set size*/
	n = in_n;
	/*if empty for some reason*/
	if(n == 0) 
	{
		pdata_array = NULL;
		pindex_array = NULL;
		pstack_array = NULL;
	}
	else
	{
		 /*malloc all the memory we need*/
		 char* pmem = (char*)malloc(sizeof(D)*n + 2*sizeof(unsigned int)*n);
		 if(pmem == NULL) throw bad_alloc();
		 /*set pointers*/
		 pdata_array = (D*)pmem;
		 pindex_array = (unsigned int*)(pmem+sizeof(D)*n);
		 pstack_array = (unsigned int*)(pmem + sizeof(D)*n + 
			 sizeof(unsigned int)*n);
	}
	/*init stack*/
	nstack = 0;
	/*set initial value for members*/
	init = in_init;
}

template <typename D>
Array<D>::Array(Array const& other)
{
	/*if empty for some reason*/
	if(other.n == 0) 
	{
		pdata_array = NULL;
		pindex_array = NULL;
		pstack_array = NULL;
	}
	else
	{
		/*malloc all the memory we need*/
		char* pmem = (char*)malloc(sizeof(D)*other.n + 
			2*sizeof(unsigned int)*other.n);
		if(pmem == NULL) throw bad_alloc();
		/*set pointers*/
		pdata_array = (D*)pmem;
		pindex_array = (unsigned int*)(pmem+sizeof(D)*other.n);
		pstack_array = (unsigned int*)(pmem + sizeof(D)*other.n + 
			sizeof(unsigned int)*other.n);
       	}
	/*copy*/
	copyOther(other);
}

template <typename D>
void Array<D>::copyOther(Array const& other)
{
	/*copy size*/
	n = other.n;
	/*copy stack*/
	nstack = other.nstack;
	for(unsigned int i=0; i<other.nstack; ++i)
	{
		pstack_array[i] = other.pstack_array[i];
	}
	/*copy index array and data*/
	for (unsigned int i = 0; i<other.nstack; ++i)
	{
		unsigned int j = pstack_array[i];
		pindex_array[j] = other.pindex_array[j];
		pdata_array[j] = other.pdata_array[j];
	}
	/*copy initial value of members*/
	init = other.init;
}

template <typename D>
Array<D>::~Array()
{
	/*this pointer frees all mem*/
	free(pdata_array);
}

template <typename D>
Array<D> const& Array<D>::operator=(Array<D> const& other)
{
	/*if empty for some reason*/
	if(other.n == 0) 
	{
		/*free old*/
		free(pdata_array);
		pdata_array = NULL;
		pindex_array = NULL;
		pstack_array = NULL;
	}
	else
	{
		/*malloc all the memory we need*/
		void* pmem = malloc(sizeof(D)*other.n + 
			2*sizeof(unsigned int)*other.n);
		if(pmem == NULL) throw bad_alloc();
		/*free old*/
		free(pdata_array);
		/*set pointers*/
		pdata_array = (D*)pmem;
		pindex_array = (unsigned int*)(pmem+sizeof(D)*other.n);
		pstack_array = (unsigned int*)(pmem + sizeof(D)*other.n + 
			sizeof(unsigned int)*other.n);
       	}
	/*copy*/
	copyOther(other);
	return *this;
}

template <typename D>
D& Array<D>::operator[](unsigned int i)
{
	if(n == 0 || i > n-1) throw out_of_range("index");
	/*check if index is not init*/
	if(pindex_array[i] >= nstack || pstack_array[pindex_array[i]] != i)
	{
		pindex_array[i] = nstack;
		pstack_array[nstack] = i;
		++nstack;
		pdata_array[i] = init;
	}
	return pdata_array[i];
}

template <typename D>
D const& Array<D>::operator[](unsigned int i) const
{
	if(n == 0 || i > n-1) throw out_of_range("index");
	/*check if index is not init*/
	if(pindex_array[i] >= nstack || pstack_array[pindex_array[i]] != i)
	{
		return init;
	}
	return pdata_array[i];
}

template <typename D>
unsigned int Array<D>::getSize() const
{
	return n;
}
