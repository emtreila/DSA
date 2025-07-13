#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    /*
     * BC = WC = TC = Theta(1)
     */
    this->length = 0;
}


void MultiMap::add(TKey c, TValue v) {
    /*
     * BC = Theta(1) - when there is no need to resize
     * WC = Theta(n) - when the list is full and needs to be resized
     * TC = O(n)
     */
    DLLA &elements = this->elems;

    // 1) Check if resizing is needed
    if (elements.size == elements.capacity && elements.first_empty == -1) {
        // if the list is full and there are no empty nodes
        // double the capacity
        elements.capacity *= 2;
        auto *aux = new DLLANode [elements.capacity];
        for (int i = 0; i < elements.size; ++i)
            aux[i] = elements[i];
        delete[] elements.list;
        elements.list = aux;
    }

    // 2) Ensure there is an available empty node
    if (elements.first_empty == -1) {
        // if there are no empty nodes
        elements.first_empty = elements.size; // set the first empty node to the size of the list
        elements[elements.first_empty] = DLLANode(NULL_TELEM, -1, -1); // create a new empty node
        ++elements.size;
    }

    // 3) Inserting the new element
    int copy_empty = elements.first_empty;
    elements.first_empty = elements[elements.first_empty].next;

    if (this->length == 0) {
        // first element in the list
        elements[copy_empty] = DLLANode(pair(c, v), -1, -1); // create a new node with the given key-value pair
        elements.head = elements.tail = copy_empty; // set head and tail to the new node
    } else {
        // append to the tail
        elements[copy_empty] = DLLANode(pair(c, v), elements.tail, -1);
        // create a new node with the given key-value pair
        elements[elements.tail].next = copy_empty;
        elements.tail = copy_empty;
    }

    ++this->length;
}


bool MultiMap::remove(TKey c, TValue v) {
    /*
     * BC = Theta(1) - when the element is found at the head
     * WC = Theta(n) - when the element is not found in the list or is at the tail
     * TC = O(n)
     */
    DLLA &elements = this->elems;

    // Check if the list is empty
    if (this->length == 0)
        return false;

    int current = elements.head; // start from the head of the list

    while (current != -1) {
        // iterate through the list
        if (elements[current].info == pair(c, v)) {
            // found the element
            int prev = elements[current].prev;
            int next = elements[current].next;

            if (prev != -1) // not the head
                elements[prev].next = next; // link previous node to next
            else
                elements.head = next; // removing head

            if (next != -1) // not the tail
                elements[next].prev = prev; // link next node to previous
            else
                elements.tail = prev; // removing tail

            elements[current].next = elements.first_empty; // link the current node to the first empty node
            elements[current].prev = -1; // reset the previous pointer
            elements.first_empty = current; // update the first empty node

            --this->length;
            return true;
        }

        current = elements[current].next; // move to the next node
    }

    return false;
}


vector<TValue> MultiMap::search(TKey c) const {
    /*
     * BC = Theta(1) - when the key is found at the first node
     * WC = Theta(n) - when the key is not found in the list or its the last node
     * TC = O(n)
     */
    vector<TValue> values; // vector of values to be returned
    for (int node = this->elems.head; node != -1; node = this->elems.list[node].next) // iterates through the list
        if (this->elems.list[node].info.first == c) {
            // if the key is found
            values.push_back(this->elems.list[node].info.second); // add the value to the vector
        }
    return values;
}


int MultiMap::size() const {
    /*
     * BC = WC = TC = Theta(1)
     */
    return this->length;
}


bool MultiMap::isEmpty() const {
    /*
     * BC = WC = TC = Theta(1)
     */
    return this->length == 0;
}

MultiMapIterator MultiMap::iterator() const {
    /*
     * BC = WC = TC = Theta(1)
     */
    return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    /*
     * BC = WC = TC = Theta(n)
     */
    delete[] this->elems.list; // deallocates the list
}

MultiMap::DLLA::DLLA() {
    /*
     * BC = WC = TC = Theta(1)
     */
    // initializes the list with default values
    this->capacity = 1;
    this->size = 1;
    this->list = new DLLANode[this->capacity];
    this->list[0] = DLLANode(NULL_TELEM, -1, -1);
    this->first_empty = 0;
    this->head = -1;
    this->tail = -1;
}

MultiMap::DLLANode &MultiMap::DLLA::operator[](int pos) {
    /*
     * BC = WC = TC = Theta(1)
     */
    return this->list[pos]; // returns the node at position pos
}

MultiMap::DLLANode::DLLANode() {
    /*
     * BC = WC = TC = Theta(1)
     */
    // initializes the node with default values
    this->info = NULL_TELEM;
    this->prev = -1;
    this->next = -1;
}

MultiMap::DLLANode::DLLANode(TElem info, int prev, int next) {
    /*
     * BC = WC = TC = Theta(1)
     */
    // initializes the node with the given values
    this->info = std::move(info);
    this->prev = prev;
    this->next = next;
}

int MultiMap::trimValues(int maxSize) {
    /*
     * BC = Theta(n) - when all values have less than maxSize values
     * WC = Theta(n^2) - when all values have more than maxSize values
     * TC = O(n^2)
     */

    if (maxSize < 0) {
        throw std::exception();
    }

    int removedCount = 0;
    DLLA& elements = this->elems;

    std::vector<TKey> seenKeys;
    std::vector<int> valueCounts;

    for (int node = elements.tail; node != -1; ) {
        int current = node;
        node = elements[current].prev;

        TKey key = elements[current].info.first;
        TValue value = elements[current].info.second;

        int index = -1;
        for (int i = 0; i < seenKeys.size(); ++i) {
            if (seenKeys[i] == key) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            seenKeys.push_back(key);
            valueCounts.push_back(1);
        } else {
            valueCounts[index]++;
        }

        if (index != -1 && valueCounts[index] > maxSize) {
            if (this->remove(key, value)) {
                removedCount++;
                valueCounts[index]--;
            }
        }
    }

    return removedCount;
}


