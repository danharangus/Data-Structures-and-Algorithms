#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	//TODO - Implementation
	this->capacity = 1;
	this->maxElement = 0;
	this->minElement = 0;
	this->elements = new bool[1];
	this->elements[0] = false;
}


bool Set::add(TElem elem) {
	//TODO - Implementation
	int prevMinElement = minElement;
	int prevMaxElement = maxElement;
	if (elem > maxElement)
	{
		maxElement = elem;
	}

	if (elem < minElement)
	{
		minElement = elem;
	}

	if (maxElement - minElement + 1 > capacity)
	{
		int old_capacity = capacity;
		capacity = maxElement - minElement + 1;
		bool* tmp = new bool[capacity];
		for (int i = 0; i < capacity; i++)
		{
			tmp[i] = false;
		}

		for (int i = 0; i < old_capacity; i++)
		{
			if (elements[i] == true)
			{
				tmp[i + prevMinElement - minElement] = true;
			}
		}

		delete[] elements;
		elements = tmp;

		elements[elem - minElement] = true;
		return true;
	}

	if (elements[elem - minElement] == true)
	{
		return false;
	}

	elements[elem - minElement] = true;
	return true;
}


//Theta(1)
bool Set::remove(TElem elem) {
	//TODO - Implementation
	if (elem >= minElement && elem <= maxElement)
	{
		if (elements[elem - minElement] == true)
		{
			elements[elem - minElement] = false;
			return true;
		}
	}

	return false;
}


//Theta(1)
bool Set::search(TElem elem) const {
	//TODO - Implementation
	if (elem >= minElement && elem <= maxElement)
	{
		return elements[elem - minElement];
	}

	return false;
}


//Theta(capacity)
int Set::size() const {
	//TODO - Implementation
	int count = 0;

	for (int i = 0; i < capacity; i++)
	{
		count += (elements[i] == true);
	}

	return count;
}


//Theta(capacity)
bool Set::isEmpty() const {
	//TODO - Implementation
	for (int i = 0; i < capacity; i++)
	{
		if (elements[i] == true)
		{
			return false;
		}
	}

	return true;
}


Set::~Set() {
	//TODO - Implementation
	delete[] elements;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


