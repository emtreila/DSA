#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	/**
	 * BC = WC = TC = Theta(1)
	 */
	// Sets the index to 0
	this->index = 0;
}

void ListIterator::first(){
	/**
	 * BC = WC = TC = Theta(1)
	 */
	// Resets the index to 0
	this->index = 0;
}

void ListIterator::next(){
	/**
	 * BC = WC = TC = Theta(1)
	 */
	if (this->index >= this->list.size()) {
		throw std::exception();
	}
	this->index++; // Increments the index
}

bool ListIterator::valid() const{
	/**
	 * BC = WC = TC = Theta(1)
	 */
	// Checks if the index is within the bounds of the list
	if (this->index >= 0 && this->index < this->list.size())
		return true;
	return false;
}

TComp ListIterator::getCurrent() const{
	/**
	 * BC = WC = TC = Theta(1)
	 */
	// Checks if the index is valid and returns the current element
	if (this->valid()) {
		return this->list.getElement(this->index);
	}
	return NULL_TCOMP;
}


