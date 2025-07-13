#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
using namespace std;

/**
*11.
ADT Set – represented as a dynamic array of Boolean values.
For example the set {5, 1, -4, 0, 8} can be represented as an array of 13 elements where position 0 corresponds
to element -4, position 1 corresponds to element -3, …, position 12 corresponds to element 8:
[true, false, false, false, true, true, false, false, false, true, false, false, true].
**/

int main() {
    testAll();
    testAllExtended();

    cout << "That's all!" << endl;
    system("pause");
}
