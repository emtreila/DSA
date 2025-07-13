#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
#include <functional>
using namespace std;
const int INITIAL_CAPACITY = 10;

SortedMultiMap::SortedMultiMap(Relation r) {
    /*
     * BC = WC = TC = Theta(n)
     */
    this->capacity = INITIAL_CAPACITY;
    this->nodes = new Node[this->capacity];
    this->relation = r;
    this->nrElements = 0;
    this->root = -1;

    for (int i = 0; i < this->capacity - 1; i++) {
        // needed because when we createNode() , firstEmpty = nodes[0].left will be uninitialized (-1)
        // -1 = end (no children)
        this->nodes[i].left = i + 1;
    }
    this->nodes[this->capacity - 1].left = -1;
    this->firstEmpty = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
    /*
     * BC = Theta(1) - when the tree is empty or the new element is added as a child of the root
     * WC = Theta(n) - when the new element is added as a leaf at the end of the tree
     * TC = O(n)
     */
    TElem e = pair(c, v);
    int newNode = createNode(e);

    if (this->root == -1) {
        // tree is empty
        this->root = newNode;
    } else {
        int current = this->root; // = index of the current node
        int parent = -1;
        while (current != -1) {
            // parse the tree to find the position for the new node
            parent = current;
            if (this->relation(c, this->nodes[current].elem.first)) {
                current = this->nodes[current].left; // go left
            } else {
                current = this->nodes[current].right; // go right
            }
        }

        if (this->relation(c, this->nodes[parent].elem.first)) {
            // insert as left child
            this->nodes[parent].left = newNode;
        } else {
            this->nodes[parent].right = newNode;
        }
    }
    this->nrElements++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    /*
     * BC = Theta(n) - we traverse the entire tree
     * WC = Theta(n) - we traverse the entire tree
     * TC = O(n)
     */
    vector<TValue> result;

    const int STACK_MAX = this->capacity;
    int stack[STACK_MAX];
    int top = 0;

    int current = this->root;
    if (current != -1) // if the tree is not empty push the root onto the stack
        stack[top++] = current;

    while (top > 0) {
        current = stack[--top]; // pop the top

        if (this->nodes[current].elem.first == c)
            // if the current node's key matches the search key push its value onto the result
            result.push_back(this->nodes[current].elem.second);

        if (this->nodes[current].right != -1) // if the current node has a right child, push it onto the stack
            stack[top++] = this->nodes[current].right;

        if (this->nodes[current].left != -1) // if the current node has a left child, push it onto the stack
            stack[top++] = this->nodes[current].left;
    }

    return result;
}


bool SortedMultiMap::remove(TKey c, TValue v) {
    /*
     * BC = Theta(1) - when the node to remove is the root or a leaf node
     * WC = Theta(n) - when the node to remove is deep in the tree or not found
     * TC = O(n)
     */
    int current = this->root;
    int parent = -1;
    bool isLeft = false;

    // find node to remove
    while (current != -1 && (this->nodes[current].elem.first != c || this->nodes[current].elem.second != v)) {
        parent = current;
        if (this->relation(c, this->nodes[current].elem.first)) {
            isLeft = true;
            current = this->nodes[current].left;
        } else {
            isLeft = false;
            current = this->nodes[current].right;
        }
    }

    if (current == -1) {
        // not found
        return false;
    }

    int replacement; // replacement node index
    // Case 1: No children (leaf node)
    if (this->nodes[current].left == -1 && this->nodes[current].right == -1) {
        replacement = -1; // no replacement needed, just remove the node
    }
    // Case 2: One child
    else if (this->nodes[current].left == -1) {
        replacement = this->nodes[current].right; // replace with right child
    } else if (this->nodes[current].right == -1) {
        replacement = this->nodes[current].left; // replace with left child
    }
    // Case 3: Two children
    else {
        int minParent = current; // parent of the minimum node
        int minNode = this->nodes[current].right; // start with the right child
        while (this->nodes[minNode].left != -1) {
            // find the minimum node in the right subtree (= the leftmost node in the right subtree)
            minParent = minNode;
            minNode = this->nodes[minNode].left;
        }

        this->nodes[current].elem = this->nodes[minNode].elem;
        // replace current node's element with the minimum node's element

        if (minParent != current) // if the minimum node is not the direct child of the current node
            this->nodes[minParent].left = this->nodes[minNode].right;
        else // if the minimum node is the direct child of the current node
            this->nodes[minParent].right = this->nodes[minNode].right;

        this->nodes[minNode].left = this->firstEmpty;
        this->firstEmpty = minNode;
        this->nrElements--;
        return true;
    }

    if (current == this->root)
        this->root = replacement;
    else if (isLeft)
        this->nodes[parent].left = replacement;
    else
        this->nodes[parent].right = replacement;

    this->nodes[current].left = this->firstEmpty;
    this->firstEmpty = current;
    this->nrElements--;
    return true;
}


int SortedMultiMap::size() const {
    /*
     * BC = WC = TC = Theta(1)
     */
    return this->nrElements;
}

bool SortedMultiMap::isEmpty() const {
    /*
     * BC = WC = TC = Theta(1)
     */
    return this->nrElements == 0;
}

SMMIterator SortedMultiMap::iterator() const {
    /*
     * BC = WC = TC = Theta(n)
     */
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    /*
     * BC = WC = TC = Theta(1)
     */
    delete[] this->nodes;
}

void SortedMultiMap::resize() {
    /*
     * BC = WC = TC = Theta(n)
     */
    int newCapacity = 2 * this->capacity;
    Node *newNodes = new Node[newCapacity];

    for (int i = 0; i < this->capacity; i++) {
        newNodes[i] = nodes[i];
    }

    for (int i = this->capacity; i < newCapacity - 1; i++) {
        newNodes[i].left = i + 1;
    }
    newNodes[newCapacity - 1].left = -1;

    this->firstEmpty = this->capacity;
    this->capacity = newCapacity;

    delete[] this->nodes;
    this->nodes = newNodes;
}

int SortedMultiMap::createNode(TElem elem) {
    /* Creates a new node with the given element and returns its index.
     *
     * BC = Theta(1) - when no resizing is needed
     * WC = Theta(n) - when resizing is needed
     * TC = O(n)
     */
    if (this->firstEmpty == -1) {
        // no free nodes available
        resize();
    }

    int newPos = this->firstEmpty;
    this->firstEmpty = this->nodes[newPos].left;

    this->nodes[newPos].elem = elem;
    this->nodes[newPos].left = -1;
    this->nodes[newPos].right = -1;

    return newPos;
}

void SortedMultiMap::replaceAll(Transformer t) {
    // replaces the value of every key, with the result given by a function invoked in the pair
    // where the Transformer is a function which takes as parameter a key and a value and returns a new value for that key
    // add the following typedef to the beginning of the SortedMultiMap.h : typedef TValue (*Transformer)(TKey, TValue);

    /*
     * BC = Theta(1) - when there is only the root
     * WC = Theta(n) - when we want to traverse it all
     * TC = O(n)
     */

    const int STACK_MAX = this->capacity;
    int stack[STACK_MAX];
    int top = 0;

    int current = this->root;
    stack[top++] = current;

    while (top > 0) {
        current = stack[--top];

        TKey k = this->nodes[current].elem.first;
        TValue v = this->nodes[current].elem.second;
        this->nodes[current].elem.second = t(k, v);

        if (this->nodes[current].right != -1)
            stack[top++] = this->nodes[current].right;
        if (this->nodes[current].left != -1)
            stack[top++] = this->nodes[current].left;
    }
}