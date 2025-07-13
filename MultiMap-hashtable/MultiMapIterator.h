#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	int currentSlot;           // which slot in the table we're at
	MultiMap::Node* currentNode;  // pointer to current node in the linked list
	int currentValueIndex;     // index in the node's values array

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

