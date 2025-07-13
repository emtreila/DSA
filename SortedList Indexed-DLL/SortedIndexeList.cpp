#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
    /**
     * BC = WC = TC = Theta(1)
     */
    // Initialization
    this->r = r;
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

int SortedIndexedList::size() const {
    /**
     * BC = WC = TC = Theta(1)
     */
    // Return the size of the list
    return this->length;
}

bool SortedIndexedList::isEmpty() const {
    /**
     * BC = WC = TC = Theta(1)
     */
    if (this->length == 0) {
        return true;
    }
    return false;
}

TComp SortedIndexedList::getElement(int i) const {
    /**
     *  BC = Theta(1) - when the element is found at the head
     *  WC = Theta(n) - when the element is at the tail or is not in the list
     *  TC = O(n)
     */
    if (i < 0 || i >= this->length) {
        throw exception();
    }
    Node *current = this->head;
    int index = 0;
    while (current != nullptr) {
        if (index == i) {
            return current->getValue();
        }
        current = current->getNext();
        index++;
    }
    return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
    /**
     *  BC = Theta(1) - when the element we want to remove is found at the head
     *  WC = Theta(n) - when the element we want to remove is at the tail
     *  TC = O(n)
     */
    if (i < 0 || i >= this->length) {
        throw exception();
    }

    Node *current = this->head;
    int index = 0;

    while (current != nullptr && index != i) {
        // Traverse the list to find the node at index i
        current = current->getNext();
        index++;
    }

    TComp val = current->getValue();

    if (current == this->head && current == this->tail) {
        // Case 1 : removing the only node in the list
        this->head = nullptr;
        this->tail = nullptr;
    } else if (current == this->head) {
        // Case 2: Removing the head
        this->head = current->getNext();
        this->head->setPrev(nullptr);
    } else if (current == this->tail) {
        // Case 3: Removing the tail
        this->tail = current->getPrev();
        this->tail->setNext(nullptr);
    } else {
        // Case 4: Removing a middle node
        current->getPrev()->setNext(current->getNext());
        current->getNext()->setPrev(current->getPrev());
    }

    delete current;
    this->length--;
    return val;
}


int SortedIndexedList::search(TComp e) const {
    /**
     *  BC = Theta(1) - when the element is found at the head
     *  WC = Theta(n) - when the element is at the tail or is not in the list
     *  TC = O(n)
     */
    Node *current = this->head;
    int index = 0;
    while (current != nullptr) {
        if (current->getValue() == e) {
            return index;
        }
        index++;
        current = current->getNext();
    }
    return -1;
}

void SortedIndexedList::add(TComp e) {
    Node *newNode = new Node(e);

    if (isEmpty()) {
        // Case 1: List is empty
        this->head = newNode;
        this->tail = newNode;
        this->length++;
        return;
    }

    Node *current = this->head;

    if (!this->r(head->getValue(), e)) {
        // Case 2: Insert at the beginning (new smallest element)
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
        this->length++;
        return;
    }

    while (current->getNext() != nullptr && this->r(current->getNext()->getValue(), e)) {
        current = current->getNext();
    }

    if (current->getNext() == nullptr) {
        // Case 3: Insert at the end (new largest element)
        current->setNext(newNode);
        newNode->setPrev(current);
        this->tail = newNode;
    } else {
        // Case 4: Insert in the middle
        Node *nextNode = current->getNext();
        current->setNext(newNode);
        newNode->setPrev(current);
        newNode->setNext(nextNode);
        nextNode->setPrev(newNode);
    }

    this->length++;
}


ListIterator SortedIndexedList::iterator() {
    /**
     * BC = WC = TC : Theta(1)
     */
    return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
    /**
     * BC = WC = TC : Theta(n)
     */
    Node *current = tail;
    while (current != nullptr) {
        Node *prev = current->getPrev();
        delete current;
        current = prev;
    }
}

//removes all elements between 2 positions, start and end
//throws exception if start or end is not valid
void SortedIndexedList::removeBetween(int start, int end) {
    /**
     * BC = Theta(1) - when start == end
     * WC = Theta(n) - when we have traverse all the list
     * TC = O(n)
     */

    if (start < 0 || end >= this->length || start > end) {
        throw exception();
    }

    Node *current = this->head;
    int index = 0;
    while (index != start) {
        current = current->getNext();
        index++;
    }

    // if (start == end) {
    //
    //     current->getPrev()->setNext(current->getNext());
    //     current->getNext()->setPrev(current->getPrev());
    // }

    for (int i = start; i <= end; i++) {
        Node *toRemove = current;
        current = current->getNext();

        if (toRemove == this->head && toRemove == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
        } else if (toRemove == this->head) {
            this->head = toRemove->getNext();
            this->head->setPrev(nullptr);
        } else if (toRemove == this->tail) {
            this->tail = toRemove->getPrev();
            this->tail->setNext(nullptr);
        } else {
            toRemove->getPrev()->setNext(toRemove->getNext());
            toRemove->getNext()->setPrev(toRemove->getPrev());
        }

        this->length--;
    }
}
