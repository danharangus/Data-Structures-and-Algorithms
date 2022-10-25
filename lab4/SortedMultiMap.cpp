#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

#define LOAD_FACTOR 0.7

//Theta(1)
int SortedMultiMap::h(TKey k, int i) const
{
	if (k < 0)
	{
		k = -k;
	}
	return (int(k % this->capacity + 0.5 * i + 0.5 * i * i) % this->capacity);
}


//Theta(capacity)
SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->capacity = 8;
	this->elems = new TElem[this->capacity];
	this->r = r;
	this->count = 0;
	this->maxKey = 0;
	this->minKey = (1 << 30);
	for (int i = 0; i < this->capacity; i++)
	{
		this->elems[i] = EMPTY;
	}
}


//Best case: Theta(1)
//Average case: O(n) - O(1) amortized
//Worst case: Theta(n)
void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	TElem el;
	el.first = c;
	el.second = v;

	int i = 0;
	int pos = h(c, i);
	while (i < this->capacity && this->elems[pos] != EMPTY && this->elems[pos] != DELETED)
	{
		i++;
		pos = h(c, i);
	}

	if ((1.0 * this->count) / this->capacity >= LOAD_FACTOR)
	{
		TElem* old = new TElem[this->capacity];
		int oldCapacity = this->capacity;

		for (int i = 0; i < this->capacity; i++)
		{
			old[i] = this->elems[i];
		}
		
		this->capacity *= 2;
		delete[] this->elems;

		this->elems = new TElem[this->capacity];
		this->count = 0;
		for (int i = 0; i < this->capacity; i++)
		{
			this->elems[i] = EMPTY;
		}

		for (int i = 0; i < oldCapacity; i++)
		{
			if (old[i] != EMPTY && old[i] != DELETED)
			{
				this->add(old[i].first, old[i].second);
			}
		}

		delete[] old;



		this->add(c, v);
	}
	else
	{
		this->elems[pos] = el;
		this->count++;
		minKey = min(c, minKey);
		maxKey = max(c, maxKey);
	}

}


//Best case: Theta(1)
//Average case: O(n) - O(1) amortized
//Worst case: Theta(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> vals;

	int i = 0;
	int pos = h(c, i);
	while (i < this->capacity)
	{
		if (this->elems[pos].first == c)
		{
			vals.push_back(this->elems[pos].second);
		}

		if (this->elems[pos] == EMPTY)
		{
			break;
		}

		i++;
		pos = h(c, i);
	}

	return vals;
}

//Best case: Theta(1)
//Average case: O(n) - O(1) amortized
//Worst case: Theta(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	TElem el;
	el.first = c;
	el.second = v;

	int i = 0;
	int pos = h(c, i);

	while(i < this->capacity && this->elems[pos] != el && this->elems[pos] != EMPTY)
	{
		i++;
		pos = h(c, i);
	}

	if (elems[pos] == el)
	{
		this->count--;
		this->elems[pos] = DELETED;
		if (c == maxKey)
		{
			maxKey = 0;
			for (int i = 0; i < this->capacity; i++)
			{
				if (this->elems[i] != EMPTY && this->elems[i] != DELETED && this->elems[i].first > maxKey)
				{
					maxKey = this->elems[i].first;
				}
			}
		}
		if (c == minKey)
		{
			minKey = (1 << 30);
			for (int i = 0; i < this->capacity; i++)
			{
				if (this->elems[i] != EMPTY && this->elems[i] != DELETED && this->elems[i].first < minKey)
				{
					minKey = this->elems[i].first;
				}
			}
		}
		return true;
	}

	return false;
}


//Theta(1)
int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->count;
}


//Theta(1)
bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return this->count == 0;
}

//Best case: Theta(n)
//Average case: O(n^2)
//Worst case: Theta(n^2) , n = number of elements in the map
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}


//Theta(1)
int SortedMultiMap::getKeyRange() const
{
	return (this->count == 0?-1:maxKey - minKey);
}

//Theta(1)
SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	delete[] this->elems;
}
