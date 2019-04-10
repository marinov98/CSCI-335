
/******************************************************************************
  Title          : hash_table.cpp
  Author         : Marin Marinov
  Created on     : April 3, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     : c++11
********************************************************************************/
#include "hash_table.h"

HashTable::HashTable() {
	// ensure table size is prime
	this->_total_size = get_next_prime(INITIAL_SIZE);

	// intialize hash table
	this->_current_size = 0;

	// test if memory could be allocated
	try {
		this->hashTable = new __ItemType[_total_size];
	}
	catch (bad_alloc) {
		cout << "too much memory requested" << '\n';
	}
}

HashTable::HashTable(int initial_size) {
	// ensure table size is prime
	this->_total_size = get_next_prime(initial_size);

	// initialize hash table
	this->_current_size = 0;

	try {
		this->hashTable = new __ItemType[_total_size];
	}
	catch (bad_alloc) {
		cout << "too much memory requested" << '\n';
	}
}

HashTable::HashTable(const HashTable& other_table) {
	this->_total_size = other_table._total_size;
	this->_current_size = other_table._current_size;

	// allocate space and fill hashtable with the contents of other table
	this->hashTable = new __ItemType[other_table._total_size];
	this->hashTable = other_table.hashTable;
}

HashTable& HashTable::operator=(const HashTable& other_table) {
	// make sure object is not copying itself
	if (this != &other_table) {
		this->_total_size = other_table._total_size;
		this->_current_size = other_table._current_size;

		// allocate memory in accordance other table's size and copy items over
		delete[] this->hashTable;
		this->hashTable = nullptr;
		this->hashTable = other_table.hashTable;
	}

	return *this;
}

HashTable::HashTable(HashTable&& other_table) :
    _total_size(other_table._total_size),
    _current_size(other_table._current_size),
    hashTable(other_table.hashTable) {
	other_table.hashTable = nullptr;
}

HashTable& HashTable::operator=(HashTable&& other_table) {
	// check to make sure we are not copying into ourselves
	if (this != &other_table) {
		// ensure total/current size is the same
		this->_total_size = other_table._total_size;
		this->_current_size = other_table._current_size;

		delete[] hashTable;
		// move the data of the other table to the original
		this->hashTable = move(other_table.hashTable);
		other_table.hashTable = nullptr;
	}

	return *this;
}

HashTable::~HashTable() {
	// delete dynamically allocated array
	delete[] this->hashTable;
	this->hashTable = nullptr;
}

bool HashTable::is_prime(int number) {
	// base cases for small table sizes
	if (number <= 1)
		return false;
	if (number <= 3)
		return true;

	// checked to skip first five numbers in loop below
	if (number % 2 == 0 || number % 3 == 0)
		return false;

	// check up until the square root of the number
	for (int i = 5; i * i <= number; i += 6) {
		if (number % i == 0 || number % (i + 2) == 0)
			return false;
	}

	// if its not divisible then its prime
	return true;
}

int HashTable::get_next_prime(int start) {
	// search for the next prime number
	while (!is_prime(start))
		start++;

	return start;
}

int HashTable::find(__ItemType& item) const {
	int found = 0;
	// if the code assigned to the string is 0 without the mod table size
	// then it was never initialized
	if (0 == item.code()) {
		// found is already 0, do nothing
	}
	else {
		int index = item.code() % _total_size;
		// constant time case: indicate item is found if the item's keys are equal
		if (hashTable[index] == item) {
			found = 1;
		} // worse case scenario, search the table for it using quadratic probing
		else {
			// used to reset the index for probing
			int initial = index;
			// variable to be incremented and added to the original
			int prober = 1;
			for (;;) {
				// checkng
				if (hashTable[index] == item) {
					found = 1;
					break;
				}

				// reset index
				index = initial;

				// search with quadratic probing
				index += (prober * prober);
				index %= _total_size;
				prober++;

				if (index == initial) {
					// indexes are repeating, stop infinite loop
					/*
					   this will be used to check if there are repeats for the
					   case where the item was initialized but never inserted into the table
					*/
					break;
				}
			}
		}
	}

	return found;
}

void HashTable::resize() {
	// create new table, making sure its size is prime
	int new_size = get_next_prime(_total_size * 2);
	HashTable newTable(new_size);

	// re-insert all items into the new table
	for (int i = 0; i < _total_size; i++) {
		if (0 != hashTable[i].code())
			newTable.insert(hashTable[i]);
	}

	// utilize our move constructor to safely copy the data
	*this = move(newTable);
}

int HashTable::insert(__ItemType item) {
	// if item is not initialized or found in the table, we are done
	if (0 == item.code() || 1 == find(item))
		return 0;

	// if table is not at least half empty then resize it
	if (_current_size >= (_total_size / 2))
		resize();

	// get index based on our hash function
	int index = item.code() % _total_size;

	// used for quadratic probing support
	int prober = 1;

	// check to see if the index already has an item there
	if (0 != hashTable[index].code()) {
		int initial = index;
		// perform quadratic probing
		while (0 != hashTable[index].code()) {
			index = initial;
			index += (prober * prober);
			index %= _total_size;
			prober++;
		}
		// insert item when a free slot is found
		hashTable[index] = item;
	}
	else { // slot is empty, item can be inserted in constant time
		hashTable[index] = item;
	}

	// increment size
	_current_size++;

	return 1;
}

int HashTable::remove(__ItemType item) {
	// if item is not found in the table, no need to delete
	if (0 == find(item))
		return 0;

	int index = item.code() % _total_size;

	// counter for quadratic probing
	int prober = 1;
	// check to see if item was inserted by linear probing
	if (hashTable[index].code() != item.code()) {
		int initial = index;
		// search using quadratic probing
		while (hashTable[index].code() != item.code()) {
			index = initial;
			index += (prober * prober);
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

	// decrement size
	_current_size--;

	return 1;
}

int HashTable::size() const {
	return _current_size;
}

int HashTable::listall(ostream& os) const {
	int items_listed = 0;

	for (int i = 0; i < _total_size; i++) {
		// print and update list when index has a valid assigned string value
		if (0 != hashTable[i].code()) {
			os << hashTable[i];
			items_listed++;
		}
	}

	return items_listed;
}
