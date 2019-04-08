
/******************************************************************************
  Title          : hash_item.cpp
  Author         : Marin Marinov
  Created on     : April 3, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     : c++11
********************************************************************************/
#include "hash_table.h"

HashTable::HashTable() {
	_total_size = INITIAL_SIZE;
	_current_size = 0;
	hashTable = new __ItemType[INITIAL_SIZE];
}

HashTable::HashTable(int initial_size) {
	_total_size = INITIAL_SIZE;
	_current_size = 0;
	hashTable = new __ItemType[initial_size];
}

HashTable::~HashTable() {
	// delete dynamically allocated array
	delete[] hashTable;
}

int HashTable::find(__ItemType& item) const {
	int found = 0;
	// if the code assigned to the string is 0 without the mod table size
	// then it was never initialized
	if (0 == item.code()) {
		// found is already 0, do nothing
	}
	else {
		unsigned int index = item.code() % _total_size;
		// constant time case: indicate item is found if the item's keys are equal
		if (hashTable[index] == item) {
			found = 1;
		} // worse case scenario, we have to search entire table for it
		else {
			for (int i = 0; i < _total_size; i++) {
				if (hashTable[i] == item) {
					found = 1;
					break;
				}
			}
		}
	}

	return found;
}

void HashTable::resize() {
	// dynamically allocate new size
	int new_size = _total_size * 2;
	__ItemType* newTable = new __ItemType[new_size];

	// copy contents of old table to the new table
	memcpy(newTable, hashTable, _total_size * sizeof(__ItemType));

	// update table size
	_total_size = new_size;

	// delete old table and make it equal the new table with updated size
	delete[] hashTable;
	hashTable = newTable;
}

int HashTable::insert(__ItemType item) {
	// if item is not initialized or found in the table, we are done
	if (0 == item.code() || 1 == find(item))
		return 0;

	// if table is not at least half empty then resize it
	if (_current_size > (_total_size / 2))
		resize();

	// get index based on our hash function
	int index = item.code() % _total_size;

	// used for linear probing support
	int helper = 1;

	// check to see if the index already has an item there
	if (hashTable[index].code() != 0) {
		// perform linear probing
		while (0 != hashTable[index].code()) {
			index += helper % _total_size;
			index %= _total_size;
			helper++;
		}

		hashTable[index] = item;
	}
	else { // slot is empty, item can be inserted in constant time
		hashTable[index] = item;
	}

	return 1;
}

int HashTable::remove(__ItemType item) {
	// if item is not found in the table, no need to delete
	if (0 == find(item))
		return 0;

	int index = item.code() % _total_size;

	// counter for linear probing
	int prober = 1;
	// check to see if item was inserted by linear probing
	if (hashTable[index].code() != item.code()) {
		// search using linear probing
		while (hashTable[index].code() != item.code()) {
			index += prober % _total_size;
			index %= _total_size;
			prober++;
		}

		// copy into parameter
		item = hashTable[index];
		// mark as empty
		hashTable[index].set("");
	}
	else {
		hashTable[index].set("");
	}

	return 1;
}

int HashTable::size() const {
	return _current_size;
}

int HashTable::listall(ostream& os) const {
	int items_listed = 0;

	for (int i = 0; i < _total_size; i++) {
		if (hashTable[i].code() != 0) {
			os << hashTable[i];
			items_listed++;
		}
	}

	return items_listed;
}
