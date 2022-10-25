#include "SMMIterator.h"
#include "SortedMultiMap.h"


//Best case: Theta(n)
//Average case: O(n^2)
//Worst case: Theta(n^2) , n = number of elements in the map
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation

	this->sortedElems = new TElem[map.capacity];
	this->last = map.count;

	int current = 0;

	for (int i = 0; i < map.capacity; i++)
	{
		if (map.elems[i] != EMPTY && map.elems[i] != DELETED)
		{
			this->sortedElems[current] = map.elems[i];
			current++;
		}
	}

	bool sorted = true;

	do
	{
		sorted = true;

		for (int i = 0; i < this->last - 1; i++)
		{
			if (!map.r(this->sortedElems[i].first, this->sortedElems[i + 1].first))
			{
				std::swap(this->sortedElems[i], this->sortedElems[i + 1]);
				sorted = false;
			}
		}
	} while (!sorted);

	this->crt = 0;
}

//Theta(1)
void SMMIterator::first(){
	//TODO - Implementation
	this->crt = 0;
}


//Theta(1)
void SMMIterator::next(){
	//TODO - Implementation
	if (!this->valid())
	{
		throw exception();
	}
	this->crt++;
}


//Theta(1)
bool SMMIterator::valid() const{
	//TODO - Implementation
	return this->crt < this->last;
}


//Theta(1)
TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (!this->valid())
	{
		throw exception();
	}
	return this->sortedElems[this->crt];
}


