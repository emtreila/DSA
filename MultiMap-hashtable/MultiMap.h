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
#define INITIAL_CAPACITY 13
class MultiMapIterator;

class MultiMap {
    friend class MultiMapIterator;

private:
    struct Node {
        TKey key; // the unique key
        TValue *values; // dynamic array of values for each key ( key -> values )
        int capacity; // capacity of values array
        int size; // current number of values

        Node *next; // pointer to next node in the linked list
    };

    Node **table;
    int tableCapacity; // number of slots ( = number of linked lists)
    int totalElements; // total number of key-value pairs
    int totalKeys; // number of unique keys
    const float LOAD_FACTOR = 0.75f;

    int hashFunction(TKey key) const;

    void resizeAndRehash();

    void addValue(Node *node, TValue value);

    bool removeValue(Node *node, TValue value);

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
