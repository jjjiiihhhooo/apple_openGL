#pragma once

#include "iDefine.h"

struct Node
{
	Node* prev;
	void* data;
};

typedef void (*MethodArray)(void* data);

struct iArray
{
	Node* node;
	int count;

	MethodArray method;

	iArray(MethodArray method = NULL);
	virtual ~iArray();

	void add(void* data);
	void add(int index, void* data);

	void* at(int index);

	void removeAll();
	void remove(int index);
};