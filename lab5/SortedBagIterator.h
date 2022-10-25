#pragma once
#include "SortedBag.h"
#include <vector>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation
	
	std::vector<TComp> vec;
	int crt;

	void fillVector(int root);

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

