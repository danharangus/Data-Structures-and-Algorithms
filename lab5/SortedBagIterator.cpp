#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//Theta(n);
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
	this->vec = std::vector<TComp>{};
	this->crt = 0;
	if (b.head == -1)
		return;
	fillVector(b.head);
}


//Theta(n)
void SortedBagIterator::fillVector(int root)
{
	if (this->bag.elems[root].left != -1)
	{
		fillVector(this->bag.elems[root].left);
	}

	vec.push_back(this->bag.elems[root].val);

	if (this->bag.elems[root].right != -1)
	{
		fillVector(this->bag.elems[root].right);
	}
}


//Theta(1)
TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (!this->valid())
		throw exception();

	return this->vec[this->crt];
}


//Theta(1)
bool SortedBagIterator::valid() {
	//TODO - Implementation
	return this->crt < this->vec.size();
}


//Theta(1)
void SortedBagIterator::next() {
	//TODO - Implementation
	if (!this->valid())
		throw exception();
	this->crt++;
}


//Theta(1)
void SortedBagIterator::first() {
	//TODO - Implementation
	this->crt = 0;
}

