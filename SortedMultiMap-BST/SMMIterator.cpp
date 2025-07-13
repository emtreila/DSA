#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	/*
	 * BC = WC = TC = Theta(n)
	 */
	this->stack = new int[map.capacity];
	this->stackTop = 0;
	this->currentNode = -1;
	first();
}

void SMMIterator::first() {
	/*
	 * BC = WC = TC = Theta(n) - because we traverse the leftmost path of the BST
	 */
	this->stackTop = 0;
	int node = map.root;

	while (node != -1) { // traverse to the leftmost node to start the iteration
		this->stack[this->stackTop++] = node;
		node = map.nodes[node].left;
	}

	if (this->stackTop > 0) // if the stack is not empty, set the current node to the top of the stack
		this->currentNode = this->stack[stackTop - 1];
	else // if the stack is empty, there are no elements to iterate over
		this->currentNode = -1;
}

void SMMIterator::next() {
	/*
	 * BC = WC = TC = Theta(1) - popping from the stack and moving to the right child
	 */
	if (!valid()) {
		throw std::exception();
	}

	int node = this->stack[--this->stackTop]; // pop the current node from the stack
	int right = map.nodes[node].right; // get the right child of the current node

	while (right != -1) { // traverse to the leftmost node of the right subtree
		this->stack[this->stackTop++] = right; // push the right child onto the stack
		right = map.nodes[right].left; // move to the left child
	}

	if (this->stackTop > 0)
		this->currentNode = this->stack[stackTop - 1];
	else
		this->currentNode = -1;
}

bool SMMIterator::valid() const{
	/*
	 * BC = WC = TC = Theta(1)
	 */
	return this->currentNode != -1;
}

TElem SMMIterator::getCurrent() const {
	/*
	 * BC = WC = TC = Theta(1)
	 */
	if (!valid()) {
		throw std::exception();
	}
	return this->map.nodes[this->currentNode].elem;
}



