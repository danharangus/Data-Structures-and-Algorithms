#include "SortedBag.h"
#include "SortedBagIterator.h"


//Theta(capacity)
SortedBag::SortedBag(Relation r) {
	//TODO - Implementation

	this->r = r;
	this->capacity = 2;
	this->elems = new Node[this->capacity];
	for (int i = 0; i < this->capacity; i++)
	{
		this->elems[i].val = NULL_TCOMP;
		this->elems[i].left = -1;
		this->elems[i].right = -1;
		this->elems[i].parent = -1;
	}
	this->firstFree = 0;
	this->head = -1;
	this->tail = -1;
	this->count = 0;
}


//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) - Theta(log2(n)), if the tree is balanced
void SortedBag::insertRec(int prev, int crt, TElem e)
{
	if (crt == -1)
	{
		int pos = this->firstFree;

		this->elems[pos].val = e;
		this->elems[pos].left = -1;
		this->elems[pos].right = -1;
		this->elems[pos].parent = prev;


		if (prev == -1)
		{
			this->head = pos;
		}
		else
		{
			if (this->r(e, elems[prev].val))
			{
				this->elems[prev].left = pos;
			}
			else
			{
				this->elems[prev].right = pos;
			}
		}
		this->count++;
	}
	else if (this->r(e, elems[crt].val))
	{
		insertRec(crt, this->elems[crt].left, e);
	}
	else
	{
		insertRec(crt, this->elems[crt].right, e);
	}
}

//Worst case: Theta(n)
//Average case: O(n);
//Best case: Theta(1);
void SortedBag::updateFirstFree()
{
	for (int i = 0; i < this->capacity; i++)
	{
		if (this->elems[i].val == NULL_TCOMP)
		{
			firstFree = i;
			return;
		}
	}
}


//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) - Theta(log2(n)), if the tree is balanced
void SortedBag::add(TComp e) {
	//TODO - Implementation
	if (this->count == this->capacity)
	{
		this->capacity *= 2;
		Node* tmp = new Node[this->capacity];

		for (int i = 0; i < this->count; i++)
		{
			tmp[i] = this->elems[i];
		}
		delete[] this->elems;
		this->elems = tmp;

		for (int i = this->count; i < this->capacity; i++)
		{
			this->elems[i].val = NULL_TCOMP;
			this->elems[i].left = -1;
			this->elems[i].right = -1;
			this->elems[i].parent = -1;
		}

		this->firstFree = this->count;
	}

	this->updateFirstFree();
	this->insertRec(-1, this->head, e);
}



//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) = Theta(log2(n)), if the tree is balanced
int SortedBag::removeRec(int root, TElem e)
{
	if (root == -1)
	{
		return root;
	}

	if (e == this->elems[root].val)
	{
		if (this->elems[root].left == -1 && this->elems[root].right == -1)
		{
			this->elems[root].left = -1;
			this->elems[root].right = -1;
			this->elems[root].parent = -1;
			this->elems[root].val = NULL_TCOMP;
			return -1;
		}
		else if(this->elems[root].left == -1)
		{
			int tmp = this->elems[root].right;
			this->elems[root].left = -1;
			this->elems[root].right = -1;
			this->elems[root].parent = -1;
			this->elems[root].val = NULL_TCOMP;
			return tmp;
		}
		else if (this->elems[root].right == -1)
		{
			int tmp = this->elems[root].left;
			this->elems[root].left = -1;
			this->elems[root].right = -1;
			this->elems[root].parent = -1;
			this->elems[root].val = NULL_TCOMP;
			return tmp;
		}
		
		//node with two children
		int tmp = this->elems[root].right;
		while (this->elems[tmp].left != -1)
		{
			tmp = this->elems[tmp].left;
		}

		this->elems[root].val = this->elems[tmp].val;
		this->elems[root].right = removeRec(this->elems[root].right, this->elems[tmp].val);
	}
	else if (this->r(e, this->elems[root].val))
	{
		this->elems[root].left = this->removeRec(this->elems[root].left, e);
	}
	else
	{
		this->elems[root].right = this->removeRec(this->elems[root].right, e);
	}

	return root;
}


//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) = Theta(log2(n)), if the tree is balanced
bool SortedBag::remove(TComp e) {
	//TODO - Implementation
	if (this->search(e) == false)
	{
		return false;
	}

	this->head = this->removeRec(this->head, e);
	this->updateFirstFree();

	this->count--;
	return true;
}


//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) = Theta(log2(n)), if the tree is balanced
bool SortedBag::searchRec(int crt, TElem e) const
{
	if (crt == -1)
	{
		return false;
	}

	if (this->elems[crt].val == e)
	{
		return true;
	}
	else if (this->r(e, this->elems[crt].val))
	{
		searchRec(this->elems[crt].left, e);
	}
	else
	{
		searchRec(this->elems[crt].right, e);
	}
}



//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) = Theta(log2(n)), if the tree is balanced
bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
	bool retVal = searchRec(this->head, elem);
	return retVal;
}


//Theta(n);
int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
	int count = 0;
	for (int i = 0; i < this->capacity; i++)
	{
		if (this->elems[i].val == elem)
		{
			count++;
		}
	}

	return count;
}



//Theta(1)
int SortedBag::size() const {
	//TODO - Implementation
	return this->count;
}


//Theta(1)
bool SortedBag::isEmpty() const {
	//TODO - Implementation
	return this->count == 0;
}


//Theta(n)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


//Theta(1)
SortedBag::~SortedBag() {
	//TODO - Implementation
	delete[] this->elems;
}


//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) = Theta(log2(n)), if the tree is balanced
TComp SortedBag::getMinEl(int crt) const
{
	if (this->elems[crt].left == -1)
	{
		return this->elems[crt].val;
	}
	else
	{
		getMinEl(this->elems[crt].left);
	}
}


//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) = Theta(log2(n)), if the tree is balanced
TComp SortedBag::getMaxEl(int crt) const
{
	if (this->elems[crt].right == -1)
	{
		return this->elems[crt].val;
	}
	else
	{
		getMaxEl(this->elems[crt].right);
	}
}


//Worst case: Theta(n)
//Average case: O(h), h = height of the tree (which in general should be < n)
//Best case: Theta(h) = Theta(log2(n)), if the tree is balanced
int SortedBag::getRange() const
{
	if (this->count == 0)
	{
		return -1;
	}
	
	TComp minEl = getMinEl(this->head);
	TComp maxEl = getMaxEl(this->head);

	return (maxEl - minEl);

}

