#include "iArray.h"


void cbArray(void* data)
{
	
}

iArray::iArray(MethodArray method)
{
	node = nullptr;
	this->method = method;
	count = 0;
}

iArray::~iArray()
{
	removeAll();
}

void iArray::add(void* data)
{
	Node* n = new Node;
	n->prev = node;
	n->data = data;

	node = n;
	count++;
}

void iArray::add(int index, void* data)
{
	Node* n = node;

	for (int i = count - 1; i > -1; i--)
	{
		if (i == index)
		{
			Node* t = new Node;
			t->prev = n->prev;
			t->data = data;

			n->prev = t;
			count++;
			return;
		}
		n = n->prev;
	}
}

void* iArray::at(int index)
{
	int i = count - 1;

	for (Node* n = node; n; n = n->prev, i--)
	{
		if (i == index) return n->data;
	} 

	return nullptr;
}

void iArray::removeAll()
{
	for (Node* n = node; n;)
	{
		Node* t = n->prev;

		if (method)
			method(n->data);
		delete n;
		n = t;
	}

	node = nullptr;
}

void iArray::remove(int index)
{
	Node* prevN = nullptr;
	Node* n = node;
	for (int i = count - 1; i > -1; i--)
	{
		if (i == index)
		{
			prevN->prev = n->prev;
			if (method)
				method(n->data);
			delete n;
			count--;
			return;
		}

		prevN = n;
		n = n->prev;
	}
}
