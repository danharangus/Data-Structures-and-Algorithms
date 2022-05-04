#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

int SortedIteratedList::allocateNode()
{
	if (this->firstFree == -1)
	{
		Node* tmp = new Node[this->capacity * 2];
		for (int i = 0; i < this->capacity; i++)
		{
			tmp[i] = this->elements[i];
		}

		int newCap = this->capacity * 2;
		for (int i = this->capacity - 1; i < newCap - 1; i++)
		{
			tmp[i].next = i + 1;
		}

		tmp[newCap - 1].next = -1;
		this->firstFree = this->capacity;
		this->capacity = newCap;
		delete[] this->elements;
		this->elements = tmp;
	}

	int pos = this->firstFree;
	this->firstFree = this->elements[this->firstFree].next;
	return pos;
}

SortedIteratedList::SortedIteratedList(Relation r) {
	//TODO - Implementation
	this->relation = r;

	this->count = 0;
	this->capacity = 2;
	this->head = -1;
	this->last = -1;
	this->firstFree = 0;

	this->elements = new Node[this->capacity];
	for (int i = 0; i < this->capacity - 1; i++)
	{
		this->elements[i].next = i + 1;
	}

	this->elements[this->capacity - 1].next = -1;
}

int SortedIteratedList::size() const {
	//TODO - Implementation
	return this->count;
}

bool SortedIteratedList::isEmpty() const {
	//TODO - Implementation
	return (this->count == 0);
}

ListIterator SortedIteratedList::first() const {
	//TODO - Implementation
	return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	//TODO - Implementation
	if (!poz.valid())
	{
		throw exception();
	}
	return poz.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	//TODO - Implementation
	if (!poz.valid())
	{
		throw exception();
	}
	TComp removedEl = -1;
	int index = poz.current;
	if (index == this->head)
	{
		removedEl = this->elements[head].val;
		this->head = this->elements[this->head].next;
	}
	else
	{
		int crt = this->head, prev = -1;
		while (crt != this->firstFree && crt != index)
		{
			prev = crt;
			crt = this->elements[crt].next;
		}

		if (crt == this->firstFree)
		{
			throw exception();
		}
		else
		{
			try
			{
				poz.next();
			}
			catch (exception)
			{

			}
			removedEl = this->elements[crt].val;
			this->elements[prev].next = this->elements[crt].next;
		}
	}

	this->elements[index].next = this->firstFree;
	this->firstFree = index;
	this->count--;
	return removedEl;
}

ListIterator SortedIteratedList::search(TComp e) const{
	//TODO - Implementation
	auto it = this->first();
	while (it.valid())
	{
		if (it.getCurrent() == e)
		{
			return it;
		}
		it.next();
	}

	return it;
}

void SortedIteratedList::add(TComp e) {
	//TODO - Implementation

	int pos = allocateNode();

	this->elements[pos].val = e;

	this->count++;
	if (this->head == -1)
	{
		this->head = pos;
		this->last = pos;
		this->elements[pos].next = this->firstFree;
		return;
	}

	int prev = -1, crt = this->head;
	while (crt != pos && !this->relation(e, this->elements[crt].val))
	{
		prev = crt;
		crt = this->elements[crt].next;
	}

	while (crt != pos && (e == this->elements[crt].val))
	{
		prev = crt;
		crt = this->elements[crt].next;
	}

	if (crt == pos)
	{
		this->last = pos;
		this->elements[prev].next = pos;
	}
	else if (prev == -1)
	{
		this->head = pos;
		this->elements[pos].next = crt;
		this->elements[this->last].next = this->firstFree;
	}
	else
	{
		this->elements[prev].next = pos;
		this->elements[pos].next = crt;
		this->elements[this->last].next = this->firstFree;
	}

}

SortedIteratedList::~SortedIteratedList() {
	delete[] this->elements;
}
