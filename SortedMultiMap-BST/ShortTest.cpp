#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

TValue transformer(TKey key, TValue value) {
	return key + value;
}

void testFunction() {
	SortedMultiMap smm = SortedMultiMap(relation1);
	smm.add(1,2);
	smm.add(1,3);
	smm.add(2,5);
	smm.add(4,2);
	smm.replaceAll(transformer);

	vector<TValue> values1 = smm.search(1);
	assert(values1[0] == 3 && values1[1] == 4);
	vector<TValue> values2 = smm.search(2);
	assert(values2[0] == 7);
	vector<TValue> values4 = smm.search(4);
	assert(values4[0] == 6);

	std::cout<<"ok!\n";

}
