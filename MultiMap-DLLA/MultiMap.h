#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)

class MultiMapIterator;

// ADT MultiMap – using a DLLA with unique keys.
//		Every key will be associated with a DLLA of the values belonging to that key.


class MultiMap {
    friend class MultiMapIterator;

private:
    struct DLLANode{ // a node of the doubly linked list
        TElem info; // key-value pair
        int prev; // previous node
        int next; // next node

        DLLANode();
        DLLANode(TElem info, int prev, int next);
    };
    struct DLLA{ // the doubly linked list
        DLLANode *list; // the list of nodes
        int head, tail;
        int capacity, size;
        int first_empty;

        DLLA();

        DLLANode& operator[](int pos); // returns the node at position pos
    };
    DLLA elems; // the list of nodes
    int length; // the number of key-value pairs in the multimap

public:
    //constructor
    MultiMap();

    //adds a key value pair to the multimap
    void add(TKey c, TValue v);

    //removes a key value pair from the multimap
    //returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey c, TValue v);

    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    vector<TValue> search(TKey c) const;

    //returns the number of pairs from the multimap
    int size() const;

    //checks whether the multimap is empty
    bool isEmpty() const;

    //returns an iterator for the multimap
    MultiMapIterator iterator() const;

    //descturctor
    ~MultiMap();

    int trimValues(int maxSize);
};
