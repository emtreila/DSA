#include <assert.h>
#include <iostream>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

void testRemoveBetween() {
	std::cout<<"remove 3-5\n";
	SortedIndexedList list = SortedIndexedList(relation1);
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);
	list.add(6);
	 for (int i = 0; i< list.size(); i++)
	 	std::cout<<list.getElement(i)<<" ";
	 std::cout<<"\n";

	 list.removeBetween(3,3);
	 for (int i = 0; i< list.size(); i++)
	 	std::cout<<list.getElement(i)<<" ";
	std::cout<<"\n";

	std::cout<<"remove 0-5\n";
	SortedIndexedList list1 = SortedIndexedList(relation1);
	list1.add(1);
	list1.add(2);
	list1.add(3);
	list1.add(4);
	list1.add(5);
	list1.add(6);
	for (int i = 0; i< list1.size(); i++)
		std::cout<<list1.getElement(i)<<" ";
	std::cout<<"\n";

	list1.removeBetween(0,5);
	for (int i = 0; i< list1.size(); i++)
		std::cout<<list1.getElement(i)<<" ";

	std::cout<<"remove 3-3\n";
	SortedIndexedList list2 = SortedIndexedList(relation1);
	list2.add(1);
	list2.add(2);
	list2.add(3);
	list2.add(4);
	list2.add(5);
	list2.add(6);
	for (int i = 0; i< list2.size(); i++)
		std::cout<<list2.getElement(i)<<" ";
	std::cout<<"\n";

	list2.removeBetween(3,3);
	for (int i = 0; i< list2.size(); i++)
		std::cout<<list2.getElement(i)<<" ";
	std::cout<<"\n";

	list2.removeBetween(0,0);
	for (int i = 0; i< list2.size(); i++)
		std::cout<<list2.getElement(i)<<" ";
	std::cout<<"\n";



}