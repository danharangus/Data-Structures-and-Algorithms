#include "SetIterator.h"
#include "Set.h"
#include <exception>


SetIterator::SetIterator(const Set& m) : set(m)
{
	//TODO - Implementation
	this->current = -1;
	for (int i = 0; i < m.capacity; i++)
	{
		if (m.elements[i] == true)
		{
			this->current = i;
			break;
		}
	}
}


void SetIterator::first() {
	//TODO - Implementation
	for (int i = 0; i < this->set.capacity; i++)
	{
		if (this->set.elements[i] == true)
		{
			this->current = i;
			break;
		}
	}
}


void SetIterator::next() {
	//TODO - Implementation
	if (!this->valid())
	{
		
		throw std::exception();
	} 
	this->current++;
	while (this->current < set.capacity && set.elements[this->current] == false)
	{
		this->current++;
	}
}


TElem SetIterator::getCurrent()
{
	//TODO - Implementation
	if (!this->valid())
	{
		throw std::exception();
	}

	return this->current + this->set.minElement;
}

bool SetIterator::valid() const {
	//TODO - Implementation
	if (this->current >= 0 && this->current < this->set.capacity && this->set.elements[this->current] == true)
	{
		return true;
	}
	return false;
}



