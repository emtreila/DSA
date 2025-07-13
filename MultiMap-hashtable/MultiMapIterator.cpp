#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <stdexcept>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	/*
	 * BC = Theta(1) - when the first slot is not empty and the first node has values
	 * WC = Theta(n) - when the first slot is empty and we need to iterate through the table
	 * TC = Theta(n)
	 */
	this->currentSlot = 0;
	this->currentNode = nullptr;
	this->currentValueIndex = 0;
	first();  // set the iterator to the first valid position
}

void MultiMapIterator::first() {
	/*
	 * BC = Theta(1) - when the first slot is not empty and the first node has values
	 * WC = Theta(n) - when the first slot is empty and we need to iterate through the table
	 * TC = Theta(n)
	 */
	this->currentSlot = 0;
	this->currentNode = nullptr;
	this->currentValueIndex = 0;

	while (this->currentSlot < this->col.tableCapacity) { // iterate through the table to find the first non-empty slot
		if (this->col.table[this->currentSlot] != nullptr) { // check if the slot is not empty
			this->currentNode = this->col.table[this->currentSlot]; // get the first node in the linked list
			if (this->currentNode->size > 0) { // if the node has values stored
				this->currentValueIndex = 0;
				return;
			}

			while (this->currentNode != nullptr && this->currentNode->size == 0) // iterate  until we find a node with values or reach the end of the list
				this->currentNode = this->currentNode->next;

			if (this->currentNode != nullptr) { // if we found a node with values
				this->currentValueIndex = 0;
				return;
			}
		}
		this->currentSlot++;
	}
}

bool MultiMapIterator::valid() const {
	/*
     * BC = WC = TC = Theta(1)
     */
	// check if the current node is valid and if the current value index is within bounds
	return this->currentNode != nullptr && this->currentValueIndex < this->currentNode->size;
}

TElem MultiMapIterator::getCurrent() const {
	/*
     * BC = WC = TC = Theta(1)
     */
	if (!valid())
		throw std::exception();
	// return the current key-value pair
	return pair(this->currentNode->key, this->currentNode->values[this->currentValueIndex]);
}

void MultiMapIterator::next() {
	/*
	 * BC = Theta(1) - when the current node has more values
	 * WC = Theta(n) - when we need to iterate through the table to find the next non-empty slot
	 * TC = Theta(n)
	 */
	if (!valid())
		throw std::exception();

	// Case 1: if the current node has more values
	this->currentValueIndex++; // move to the next value in the current node
	if (this->currentValueIndex < this->currentNode->size) { // if there are more values in the current node
		return;
	}

	// Case 2: if the current node has no more values
	this->currentNode = this->currentNode->next; // move to the next node in the linked list
	while (this->currentNode != nullptr && this->currentNode->size == 0) // iterate until we find a node with values or reach the end of the list
		this->currentNode = this->currentNode->next;

	if (this->currentNode != nullptr) { // if we found a node with values
		this->currentValueIndex = 0; // reset the value index
		return;
	}

	// Case 3: if we reached the end of the linked list and need to find the next non-empty slot
	this->currentSlot++;
	while (this->currentSlot < this->col.tableCapacity) { // iterate through the table to find the next non-empty slot
		MultiMap::Node* node = this->col.table[this->currentSlot]; // get the linked list at the current slot
		while (node != nullptr && node->size == 0) // iterate through the linked list to find a node with values
			node = node->next;
		if (node != nullptr) {
			this->currentNode = node;
			this->currentValueIndex = 0;
			return;
		}
		this->currentSlot++;
	}

	this->currentNode = nullptr;
	this->currentValueIndex = 0;
}
