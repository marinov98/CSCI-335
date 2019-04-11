
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

HashTable::HashTable() : _size(get_next_prime(INITIAL_SIZE)), _items_inserted(0) {
	// test if memory could be allocated
	try {
		this->hash_table = new Item[_size];
	}
	catch (bad_alloc) {
		cout << "too much memory requested" << '\n';
	}
}

HashTable::HashTable(int size) : _size(get_next_prime(size)), _items_inserted(0) {
	_probe_tester = 0;

	try {
		this->hash_table = new Item[_size];
	}
	catch (bad_alloc) {
		cout << "too much memory requested" << '\n';
	}
}

HashTable::HashTable(const HashTable& other_table) :
    _size(other_table._size),
    _items_inserted(other_table._items_inserted) {
	// allocate space and fill hashtable with the contents of other table
	this->hash_table = new Item[other_table._size];
	memcpy(this->hash_table, other_table.hash_table, sizeof(Item) * _size);
}

HashTable& HashTable::operator=(const HashTable& other_table) {
	/*
	    call copy constructor to copy data of other_table
	    into a temporary table
	*/
	HashTable temp_table = other_table;

	/*
	    Because we do not care about the temp_table existing
	    after we copy it over , we can just move its contents
	    into the current table which will call our
	    move assignment operator that will safely transfer
	    its contents. We do not move(other_table) because we
	    care about its existance after the exchange of data is made
	*/
	*this = move(temp_table);

	return *this;
}

HashTable::HashTable(HashTable&& other_table) :
    _size(other_table._size),
    _items_inserted(other_table._items_inserted),
    hash_table(other_table.hash_table) {
	other_table.hash_table = nullptr;
}

HashTable& HashTable::operator=(HashTable&& other_table) {
	// ensure size and items inserted are the same
	this->_size = other_table._size;
	this->_items_inserted = other_table._items_inserted;

	delete[] this->hash_table;
	// move the data of the other table to the original
	this->hash_table = move(other_table.hash_table);
	other_table.hash_table = nullptr;

	return *this;
}

HashTable::~HashTable() {
	cout << "amount of times quadratic probing was used: " << _probe_tester << '\n';
	delete[] this->hash_table;
	this->hash_table = nullptr;
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

void HashTable::resize() {
	// create new table with double the size, making sure its size is prime
	int new_size = get_next_prime(_size * 2);
	HashTable newTable(new_size);

	// re-insert all items into the new table
	for (int i = 0; i < _size; i++) {
		if (!hash_table[i].is_empty)
			newTable.insert(hash_table[i].data);
	}

	/*
	    utilize our move assignment operator to safely copy the data
	    from the new table object to our current table object
	*/
	*this = move(newTable);
}

int HashTable::find(__ItemType& item) const {
	int found = 0;
	// if the code assigned to the string is 0 without the mod table size
	// then it was never initialized
	if (0 == item.code()) {
		// found is already 0, do nothing
	}
	else {
		int index = item.code() % _size;
		// constant time case: indicate item is found if the item's keys are equal
		if (!hash_table[index].is_empty && hash_table[index].data == item) {
			found = 1;
		} // case where its found but its marked as empty
		else if (hash_table[index].is_empty && hash_table[index].data == item) {
			// found aready 0 do nothing
		}
		// worse case scenario, search the table for it using quadratic probing
		else {
			// used to reset the index for probing
			int initial = index;
			// variable to be incremented and added to the original
			int prober = 1;
			for (;;) {
				// checking to see if item was found and not marked empty
				if (hash_table[index].data == item && !hash_table[index].is_empty) {
					found = 1;
					break;
				}

				// reset index
				index = initial;

				// search with quadratic probing
				index += (prober * prober);
				index %= _size;
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

int HashTable::insert(__ItemType item) {
	// if item is not initialized or found in the table, we are done
	if (0 == item.code() || 1 == find(item))
		return 0;

	// if table is not at least half empty then resize it
	if (_items_inserted >= (_size / 2))
		resize();

	// get index based on our hash function
	int index = item.code() % _size;

	// used for quadratic probing support when collisions occur
	int prober = 1;

	// check to see if the index already has an item there
	if (!hash_table[index].is_empty) {
		_probe_tester++;

		int initial = index;
		// perform quadratic probing to find an empty index
		while (!hash_table[index].is_empty) {
			index = initial;
			index += (prober * prober);
			index %= _size;
			prober++;
		}
		// insert item when a free slot is found and indicate that it's not empty
		hash_table[index].data = item;
		hash_table[index].is_empty = false;
	}
	else { // slot is empty, item can be inserted in constant time
		hash_table[index].data = item;
		hash_table[index].is_empty = false;
	}

	// add to the amount of items inserted
	_items_inserted++;

	return 1;
}

int HashTable::remove(__ItemType item) {
	// if item is not found in the table, no need to delete
	if (0 == find(item))
		return 0;

	int index = item.code() % _size;

	// counter for quadratic probing
	int prober = 1;
	// constant time case
	if (hash_table[index].data == item) {
		// mark as "empty" (this is lazy deletion)
		hash_table[index].is_empty = true;
	}
	// search using quadratic probing
	else {
		int initial = index;
		// search using quadratic probing
		while (hash_table[index].data.code() != item.code()) {
			index = initial;
			index += (prober * prober);
			index %= _size;
			prober++;
		}

		// copy into parameter
		item = hash_table[index].data;
		// mark as empty
		hash_table[index].is_empty = true;
	}

	// decrement the number of items that have been inserted
	_items_inserted--;

	return 1;
}

int HashTable::size() const {
	return _size;
}

int HashTable::listall(ostream& os) const {
	int items_listed = 0;

	for (int i = 0; i < _size; i++) {
		// print and update list when index has a valid assigned string value
		if (!hash_table[i].is_empty) {
			os << hash_table[i].data;
			items_listed++;
		}
	}

	return items_listed;
}
