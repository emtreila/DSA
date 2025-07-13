#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    /*
     * BC = WC = TC = Theta(n)
     */
    this->tableCapacity = INITIAL_CAPACITY;
    this->table = new Node *[this->tableCapacity]; // initialize the table with empty slots for linked lists
    for (int i = 0; i < this->tableCapacity; i++) {
        this->table[i] = nullptr; // initialize each slot to nullptr
    }
    this->totalElements = 0;
    this->totalKeys = 0;
}


void MultiMap::add(TKey c, TValue v) {
    /*
     * BC = Theta(1) - when the key is already in the table and the value is added to the existing node
     * WC = Theta(n) - when the key is not in the table and a new node is created
     * TC = Theta(1)
     */

    int index = hashFunction(c); // compute the index for the key
    Node *current = this->table[index]; // get the linked list at the index

    // Case 1: if the key is already in the table, add the value to the existing node
    while (current != nullptr) {
        // iterate through the linked list
        if (current->key == c) {
            addValue(current, v);
            this->totalElements++;
            return;
        }
        current = current->next;
    }

    // Case 2: if the key is not in the table, create a new node
    Node *newNode = new Node;
    newNode->key = c;
    newNode->capacity = 2;
    newNode->size = 1; // initialize the size of the values array
    newNode->values = new TValue[newNode->capacity]; // create the values array
    newNode->values[0] = v; // add the value to the array
    newNode->next = this->table[index]; // link the new node to the existing list at the head
    this->table[index] = newNode;

    this->totalElements++;
    this->totalKeys++;

    // if the load factor exceeds the threshold, resize and rehash the table
    if ((float) this->totalKeys / this->tableCapacity > this->LOAD_FACTOR) {
        resizeAndRehash();
    }
}


bool MultiMap::remove(TKey c, TValue v) {
    /*
     * BC = Theta(1) - when the key is on the first position of the linked list
     * WC = Theta(n) - when the key is at the end of the linked list
     * TC = Theta(1)
     */
    int index = hashFunction(c); // compute the index for the key
    Node *current = this->table[index]; // get the linked list at the index
    Node *prev = nullptr; // pointer to the previous node

    while (current != nullptr) {
        // iterate through the linked list
        if (current->key == c) {
            bool removed = removeValue(current, v); // remove the value from the node
            if (removed) {
                this->totalElements--;
                if (current->size == 0) { // if the dynamic array is empty
                    if (prev == nullptr) // if the node is the head of the list
                        this->table[index] = current->next; // update the head of the list
                    else
                        prev->next = current->next; // update the next pointer of the previous node

                    delete[] current->values;
                    delete current;
                    this->totalKeys--;
                }
            }
            return removed;
        }
        prev = current;
        current = current->next;
    }
    return false;
}


vector<TValue> MultiMap::search(TKey c) const {
    /*
     * BC = Theta(1) - when the key is on the first position of the linked list
     * WC = Theta(n) - when the key is at the end of the linked list
     * TC = Theta(1)
     */

    int index = hashFunction(c); // compute the index for the key
    Node *current = table[index]; // get the linked list at the index

    while (current != nullptr) {
        // iterate through the linked list
        if (current->key == c) {
            // if the key is found
            vector<TValue> result; // create a vector to store the values
            for (int i = 0; i < current->size; i++) {
                result.push_back(current->values[i]); // add the values to the vector
            }
            return result;
        }
        current = current->next;
    }
    return {};
}


int MultiMap::size() const {
    /*
     * BC = WC = TC = Theta(1)
     */
    return this->totalElements;
}


bool MultiMap::isEmpty() const {
    /*
     * BC = WC = TC = Theta(1)
     */
    return this->totalElements == 0;
}

MultiMapIterator MultiMap::iterator() const {
    /*
     * BC = Theta(1) - when the current node has more values
     * WC = Theta(n) - when we need to iterate through the table to find the next non-empty slot
     * TC = Theta(n)
     */
    return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    /*
     * BC = WC = TC = Theta(n)
     */
    for (int i = 0; i < this->tableCapacity; i++) {
        Node *current = this->table[i];
        while (current != nullptr) {
            Node *next = current->next;
            delete[] current->values;
            delete current;
            current = next;
        }
    }
    delete[] this->table;
}

int MultiMap::hashFunction(TKey key) const {
    /*
     * BC = WC = TC = Theta(1)
     */
    int hash = abs(key) % this->tableCapacity; // hash function to compute the index for the key
    return hash;
}

void MultiMap::resizeAndRehash() {
    /*
     * BC = WC = TC = Theta(n)
     */
    int oldCapacity = this->tableCapacity; // store the old capacity and table
    Node **oldTable = this->table;

    this->tableCapacity *= 2; // double the capacity and create a new table
    this->table = new Node *[this->tableCapacity];
    for (int i = 0; i < this->tableCapacity; i++) {
        // initialize the new table with empty slots
        this->table[i] = nullptr;
    }

    this->totalKeys = 0; // reset the total keys and elements
    this->totalElements = 0;

    for (int i = 0; i < oldCapacity; i++) {
        // iterate through the old table and rehash the elements
        Node *current = oldTable[i];
        while (current != nullptr) {
            for (int j = 0; j < current->size; j++) {
                add(current->key, current->values[j]);
            }
            Node *next = current->next;
            delete[] current->values;
            delete current;
            current = next;
        }
    }
    delete[] oldTable;
}

void MultiMap::addValue(Node *node, TValue value) {
    /*
     * BC = Theta(1) - when the values array is not full
     * WC = Theta(n) - when the values array is full and needs to be resized
     * TC = Theta(1)
     */

    // adds a value to the node's values array
    if (node->size == node->capacity) {
        // check if the values array is full -> resize the array
        int newCapacity = node->capacity * 2;
        if (newCapacity == 0) newCapacity = 2;
        TValue *newValues = new TValue[newCapacity];
        for (int i = 0; i < node->size; i++) {
            // copy the old values to the new array
            newValues[i] = node->values[i];
        }
        delete[] node->values; // delete the old array
        node->values = newValues;
        node->capacity = newCapacity;
    }
    node->values[node->size++] = value;
}

bool MultiMap::removeValue(Node *node, TValue value) {
    /*
     * BC = Theta(1) - when the value is found at the first position
     * WC = Theta(n) - when the value is at the end of the array / not found
     * TC = Theta(1)
     */
    // removes a value from the node's values array
    for (int i = 0; i < node->size; i++) {
        // iterate through the values
        if (node->values[i] == value) {
            // check if the value is found
            for (int j = i; j < node->size - 1; j++) {
                // shift the values to the left
                node->values[j] = node->values[j + 1];
            }
            node->size--;
            return true;
        }
    }
    return false;
}


// limits the number of values for a key to maxSize. From the keys with more than maxSize values, some values (doesnt matter which ones)
//     // will me removed until the number of associated values will be equal to maxSize. If a key has less than maxSize values
//     // they will not be changed. returns the total number of removed values
int MultiMap::trimValues(int maxValue) {
    /*
     * BC = Theta(1)
     * WC = Theta(n)
     * TC = Theta(n)
     */
    if (maxValue < 0)
        return 0;
    int removedCount = 0;

    for (int i = 0; i < this->tableCapacity; i++) {
        Node* current = this->table[i];

        while (current != nullptr) {
            if (current->size > maxValue) {
                int toRemove = current->size - maxValue;
                current->size = maxValue;
                removedCount = removedCount + toRemove;
                this->totalElements = this->totalElements - toRemove;
            }
            current = current->next;
        }
    }
    return removedCount;
}
