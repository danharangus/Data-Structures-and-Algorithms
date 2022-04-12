#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	lines = nrLines;
	columns = nrCols;
	length = 0;
	head = NULL;
}


// Theta(1)
int Matrix::nrLines() const {
	//TODO - Implementation
	return lines;
}


// Theta(1)
int Matrix::nrColumns() const {
	//TODO - Implementation
	return columns;
}


/// O(n)
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if (i < 0 || i >= lines || j < 0 || j >= columns)
	{
		throw exception("Invalid position");
	}

	if (head == NULL)
	{
		return 0;
	}

	Node* crt = head;
	while (crt != NULL)
	{
		if (crt->line == i && crt->column == j)
		{
			return crt->val;
		}

		crt = crt->next;
	}

	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	if (i < 0 || i >= lines || j < 0 || j >= columns)
	{
		throw exception("Invalid position");
	}

	Node* newNode = new Node;
	newNode->line = i;
	newNode->column = j;
	newNode->val = e;
	newNode->next = NULL;
	if (i == 100 && j == 100)
	{
		int a = 1;
	}

	if (head == NULL)
	{
		head = newNode;
		return 0;
	}

	Node* crt = head;
	while (crt->next != NULL && crt->line != i)
	{
		crt = crt->next;
	}

	if (crt->line == i && crt->column == j)
	{
		TElem val = crt->val;
		crt->val = e;
		return val;
	}

	while (crt->next != NULL && crt->next->line == i && crt->next->column < j)
	{
		crt = crt->next;
	}

	if (crt->next != NULL && crt->next->line == i && crt->next->column == j)
	{
		TElem val = crt->next->val;
		crt->next->val = e;
		return val;
	}

	Node* tmp = crt->next;
	crt->next = newNode;
	newNode->next = tmp;

	return NULL_TELEM;
}


