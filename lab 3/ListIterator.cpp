#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	//TODO - Implementation
	this->current = list.head;
}

void ListIterator::first(){
	//TODO - Implementation
	this->current = list.head;
}

void ListIterator::next(){
	//TODO - Implementation
	if (!this->valid())
	{
		throw exception();
	}
	this->current = this->list.elements[this->current].next;
}

bool ListIterator::valid() const{
	//TODO - Implementation
	return (this->current >= 0 && this->current < this->list.capacity && this->current != list.firstFree);
}

TComp ListIterator::getCurrent() const{
	//TODO - Implementation
	return this->list.elements[this->current].val;
}


