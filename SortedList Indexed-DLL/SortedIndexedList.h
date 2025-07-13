#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;

typedef bool (*Relation)(TComp, TComp);

#define NULL_TCOMP -11111

class SortedIndexedList {
    class Node {
    private:
        TComp value;
        Node *next;
        Node *prev;

    public:
        Node() : value(NULL_TCOMP), next(nullptr), prev(nullptr) {
        }

        Node(TComp value) : value(value), next(nullptr), prev(nullptr) {
        }

        Node(TComp value, Node *next, Node *prev) : value(value), next(next), prev(prev) {
        }

        TComp getValue() const { return value; }
        Node *getNext() const { return next; }
        Node *getPrev() const { return prev; }
        void setNext(Node *next) { this->next = next; }
        void setPrev(Node *prev) { this->prev = prev; }
    };

private:
    friend class ListIterator;

private:
    Relation r;
    Node *head;
    Node *tail;
    int length;

public:
    // constructor
    SortedIndexedList(Relation r);

    // returns the size of the list
    int size() const;

    //checks if the list is empty
    bool isEmpty() const;

    // returns an element from a position
    //throws exception if the position is not valid
    TComp getElement(int pos) const;

    // adds an element in the sortedList (to the corresponding position)
    void add(TComp e);

    // removes an element from a given position
    //returns the removed element
    //throws an exception if the position is not valid
    TComp remove(int pos);

    // searches for an element and returns the first position where the element appears or -1 if the element is not in the list
    int search(TComp e) const;

    // returns an iterator set to the first element of the list or invalid if the list is empty
    ListIterator iterator();

    //destructor
    ~SortedIndexedList();

    //removes all elements between 2 positions, start and end
    //throws exception if start or end is not valid
    void removeBetween(int start, int end);
};
