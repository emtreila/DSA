#include "Set.h"

#include <stdlib.h>

#include "SetITerator.h"

Set::Set() {
    /**
    BC = WC = TC: Theta(1)
    **/

    // set bounds
    this->minElement = 0;
    this->maxElement = 0;

    // dynamic array
    this->elements = new bool[INITIAL_CAPACITY]();
    this->capacity = INITIAL_CAPACITY;
    this->size_ = 0;
}


unsigned int Set::distance(int a, int b) const {
    /**
    BC = WC = TC: Theta(1)
    **/

    // number of elements in the interval (a, b)
    return abs(b - a);
}

void Set::resize(unsigned int newCapacity) {
    /**
    BC = WC = TC: Theta(size_)
    **/

    // resize the dynamic array
    bool *newElements = new bool[newCapacity]();
    for (unsigned int i = 0; i < this->size_; i++) {
        // copy the elements into the new array
        newElements[i] = this->elements[i];
    }

    this->capacity = newCapacity;
    delete[] this->elements;
    this->elements = newElements;
}

bool Set::add(TElem elem) {
    /**
     BC: Theta(1)     - when the elem is aleardy in the dynamic array
     WC: Theta(size_) - when the elem is not in the dynamic array and its smaller than minElement / bigger than maxElement
     TC: O(size_)
    **/

    // case for empty set
    if (this->isEmpty()) {
        minElement = maxElement = elem;
        this->elements[0] = true;
        this->size_ = 1;
        return true;
    }

    //case for non-empty set, smaller element than the lower bound
    if (this->minElement > elem) {
        unsigned int d = this->distance(elem, minElement);

        // resize if necessary
        if (this->size_ + d > this->capacity) {
            unsigned int newCapacity = this->capacity;
            while (this->size_ + d > newCapacity) {
                newCapacity *= GROWTH_FACTOR;
            }
            this->resize(newCapacity);
        }

        // move to the right all existing the elements
        for (unsigned int i = this->size_ + d; i > d; i--) {
            this->elements[i - 1] = this->elements[i - d - 1];
        }

        for (int i = 1; i < d; i++) {
            // initialize with false
            this->elements[i] = false;
        }

        this->size_ += d;
        this->elements[0] = true;
        this->minElement = elem;

        //case for non-empty set, bigger element than the upper bound
    } else if (this->maxElement < elem) {
        unsigned int d = this->distance(maxElement, elem);

        // resize if necessary
        if (this->size_ + d > this->capacity) {
            unsigned int newCapacity = this->capacity;
            while (this->size_ + d > newCapacity) {
                newCapacity *= GROWTH_FACTOR;
            }
            this->resize(newCapacity);
        }

        // grow the set to the right
        for (unsigned int i = this->size_ + 1; i < this->size_ + d; i++) {
            this->elements[i] = false;
        }

        this->elements[this->size_ + d - 1] = true;
        this->size_ += d;
        this->maxElement = elem;

        // the element is already in the dynamic array
    } else {
        unsigned int index = this->distance(minElement, elem);
        if (this->elements[index] == false) {
            this->elements[index] = true;
        } else if (this->elements[index] == true) {
            return false;
        }
    }
    return true;
}


bool Set::remove(TElem elem) {
    /**
    BC: Theta(1)       - when the element is between minElement and maxElement
    WC: Theta(size_)   - when the element is either equal to minElement or maxElement
    TC: O(size_)
     **/

    // set is empty or the element is out of bounds
    if (this->isEmpty() || elem < this->minElement || elem > this->maxElement)
        return false;

    // the element is already not present in the set
    if (this->search(elem) == false) {
        return false;
    }

    // mark the element as removed
    this->elements[this->distance(this->minElement, elem)] = false;

    // update lower and upper bounds if necessary
    if (elem == this->maxElement) {
        // truncate the set from the right
        while (this->size_ > 0 && this->elements[this->size_ - 1] == false) {
            this->size_--;
        }

        // check if we have anymore elements left in the set
        if (this->size_ > 0) {
            this->maxElement = this->minElement + this->size_ - 1;
        }

    } else if (elem == this->minElement) {
        // finding the next smallest element
        int newMinElement = this->minElement;

        while (newMinElement <= this->maxElement) {
            unsigned int index = this->distance(this->minElement, newMinElement);
            bool value = this->elements[index];

            if (value == true) {
                break;
            }

            newMinElement++;
        }

        // shifting the set with the distance between minElement and the newMinElement
        unsigned int shiftValue = this->distance(this->minElement, newMinElement);
        for (unsigned int i = 0; i < this->size_ - shiftValue; i++) {
            this->elements[i] = this->elements[i + shiftValue];
        }
        this->size_ -= shiftValue;

        this->minElement = newMinElement;
    }

    return true;
}

bool Set::search(TElem elem) const {
    /**
    BC = WC = TC : Theta(1)
    **/

    if (this->isEmpty() || elem < this->minElement || elem > this->maxElement) {
        return false;
    }
    unsigned int index = this->distance(minElement, elem);
    return this->elements[index];
}


unsigned int Set::size() const {
    /**
    BC = WC = TC : Theta(size_) - we iterate through all elements
    **/

    unsigned int trueValues = 0;
    for (int i = 0; i < this->size_; i++) {
        if (this->elements[i] == true) {
            trueValues++;
        }
    }
    return trueValues;
}


bool Set::isEmpty() const {
    /**
    BC = WC = TC : Theta(1)
    **/

    if (this->size_ == 0) {
        return true;
    }
    return false;
}


Set::~Set() {
    /**
    BC = WC = TC : Theta(1)
    **/

    delete[] this->elements;
    this->size_ = this->capacity = this->maxElement = this->minElement = 0;
}


SetIterator Set::iterator() const {
    /**
    BC = WC = TC : Theta(1)
    **/

    return SetIterator(*this);
}
