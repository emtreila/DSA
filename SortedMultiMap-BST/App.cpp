#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	testAllExtended();
	testFunction();

	// ADT SortedMultiMap – using a BST with linked representation on an array.
	// In the BST (key, value) pairs are stored. If a key has multiple values, it appears in multiple pairs.
    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
