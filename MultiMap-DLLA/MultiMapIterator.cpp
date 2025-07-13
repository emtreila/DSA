#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	/**
	 * BC = WC = TC = Theta(1)
	 */
	this->pos = this->col.elems.head; // initialize the iterator position to the head of the list
}

TElem MultiMapIterator::getCurrent() const{
	/**
	 * BC = WC = TC = Theta(1)
	 */
	if (!this->valid()) // check if the iterator is valid
		throw std::exception();
	return this->col.elems.list[this->pos].info; // return the current element
}


bool MultiMapIterator::valid() const {
	/**
	 * BC = WC = TC = Theta(1)
	 */
	return pos != -1; // check if the iterator is valid
}

void MultiMapIterator::next() {
	/**
	 * BC = WC = TC = Theta(1)
	 */
	if (!this->valid()) // check if the iterator is valid
		throw std::exception();
	this->pos = this->col.elems.list[this->pos].next; // move to the next element
}

void MultiMapIterator::first() {
	/**
	 * BC = WC = TC = Theta(1)
	 */
	this->pos = this->col.elems.head; // reset the iterator to the head
}

