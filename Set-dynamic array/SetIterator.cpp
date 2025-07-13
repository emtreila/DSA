#include "SetIterator.h"

#include <exception>

#include "Set.h"


SetIterator::SetIterator(const Set &m) : set(m) {
    /**
    BC = WC = TC : Theta(1)
    **/

    this->currentPosition = 0;
}


void SetIterator::first() {
    /**
    BC = WC = TC : Theta(1)
    **/

    this->currentPosition = 0;
}


void SetIterator::next() {
    /**
    BC: Theta(1)       - when the next element is immediately available (it is true)
    WC: Theta(size_)   - when we have to iterate over all size_ to get to a "true" element
    TC: O(size_)
    **/

    if (this->currentPosition == this->set.size_) {
        throw std::exception();
    }

    while (this->currentPosition < this->set.size_ - 1 && this->set.elements[this->currentPosition + 1] == false) {
        this->currentPosition++;
    }
    this->currentPosition++;
}


TElem SetIterator::getCurrent() {
    /**
    BC = WC = TC : Theta(1)
    **/

    if (this->currentPosition == this->set.size_) {
        throw std::exception();
    }
    return this->set.minElement + this->currentPosition;
}

bool SetIterator::valid() const {
    /**
    BC = WC = TC : Theta(1)
    **/

    return this->currentPosition < this->set.size_;
}
