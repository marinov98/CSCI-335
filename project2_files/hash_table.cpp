
/******************************************************************************
  Title          : hash_table.cpp
  Author         : Marin Pavlinov Marinov
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
	catch (bad_alloc&) {
		cout << "too much memory requested" << '\n';
	}
}

HashTable::HashTable(int size) : _size(get_next_prime(size)), _items_inserted(0) {
	try {
		this->hash_table = new Item[_size];
	}
	catch (bad_alloc&) {
		cout << "too much memory requested" << '\n';
	}
}

HashTable::HashTable(const HashTable& other_table) :
    _size(other_table._size),
    _items_inserted(other_table._items_inserted) {
	// allocate space and fill hashtable with the contents of other table
	this->hash_table = new Item[other_table._size];
	copy(other_table.hash_table, (other_table.hash_table + _size), this->hash_table);
}

HashTable& HashTable::operator=(const HashTable& other_table) {
	// copy over size and items_inserted
	this->_items_inserted = other_table._items_inserted;
	this->_size = other_table._size;

	// delete and reallocate memory
	delete[] this->hash_table;
	this->hash_table = new Item[other_table._size];

	// copy data from other_table to current hash_table
	copy(other_table.hash_table, (other_table.hash_table + _size), this->hash_table);

	return *this;
}

HashTable::HashTable(HashTable&& other_table) noexcept :
    _size(other_table._size),
    _items_inserted(other_table._items_inserted),
    hash_table(other_table.hash_table) {
	other_table.hash_table = nullptr;
}

HashTable& HashTable::operator=(HashTable&& other_table) noexcept {
	// ensure size and items inserted are the same
	this->_size = other_table._size;
	this->_items_inserted = other_table._items_inserted;

	delete[] this->hash_table;
	// move the data of the other table to the original now that other_table is an rvalue
	this->hash_table = other_table.hash_table;
	other_table.hash_table = nullptr;

	return *this;
}

HashTable::~HashTable() {
	delete[] this->hash_table;
	this->hash_table = nullptr;
}

bool HashTable::is_prime(int number) const {
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

int HashTable::get_next_prime(int start) const {
	// search for the next prime number
	while (!is_prime(start))
		start++;

	return start;
}

void HashTable::rehash() {
	// create new table with double the size, making sure its size is prime
	int new_size = get_next_prime(_size * 2);
	HashTable newTable(new_size);

	// re-insert all items into the new table
	for (int i = 0; i < _size; i++) {
		if (!hash_table[i].is_empty)
			newTable.insert(hash_table[i].data);
	}

	/*
	    utilize our move assignment operator to safely transfer the data
	    from the new temporary table object to our current table object
	*/
	*this = move(newTable);
}

int HashTable::find(__ItemType& item) const {
	// item not initialized or table is empty
	if (0 == item.code() || empty()) {
		return 0;
	}

	int index;
	int next_index;
	int collisions = 0;
	// quadratic probing
	while (true) {
		index = (item.code() + collisions * collisions) % _size;

		// item is found and indicated as non_empty
		if (!this->hash_table[index].is_empty && this->hash_table[index].data == item) {
			return 1;
		} // if item is found but is empty then exit the loop
		else if (this->hash_table[index].is_empty && this->hash_table[index].data == item) {
			break;
		}

		collisions++;

		next_index = (item.code() + collisions * collisions) % _size;
		/*
		    when modding with a prime number there
		    always comes a case where when we probe one
		    more time, we get the same result as the
		    previous probe and the indices start repeating
		*/
		if (index == next_index) {
			break;
		}
	}

	return 0;
}

int HashTable::insert(__ItemType& item) {
	// index is already in the table or not initialized
	if (0 == item.code() || 1 == find(item))
		return 0;

	/*
	    for loop will execute once if a free spot is found right away
	    other wise it will iterate at most n times where n is the size
	*/
	int index;
	for (int i = 0; i < _size; i++) {
		index = (item.code() + i * i) % _size;
		if (this->hash_table[index].is_empty) {
			// insert into first empty slot and increment items inserted
			this->hash_table[index].data = item;
			this->hash_table[index].is_empty = false;
			_items_inserted++;
			break;
		}
	}

	// resize table if its not half empty anymore
	if (_items_inserted > (_size / 2))
		rehash();

	return 1;
}

int HashTable::insert(__ItemType&& item) {
	// index is already in the table or not initialized
	if (0 == item.code() || 1 == find(item))
		return 0;

	/*
	    Same process as normal insert but this time we are inserting a temp object
	*/
	int index;
	for (int i = 0; i < _size; i++) {
		index = (item.code() + i * i) % _size;
		if (this->hash_table[index].is_empty) {
			// MOVE contents of item and insert into table
			this->hash_table[index].data = move(item);
			this->hash_table[index].is_empty = false;
			_items_inserted++;
			break;
		}
	}

	// resize table if its not half empty anymore
	if (_items_inserted > (_size / 2))
		rehash();

	return 1;
}

int HashTable::remove(__ItemType& item) {
	// if item is not found in the table, no need to delete
	if (0 == find(item))
		return 0;

	// constant time case
	if (hash_table[item.code() % _size].data == item) {
		// mark as "empty" (this is lazy deletion)
		hash_table[item.code() % _size].is_empty = true;
	}
	// search using quadratic probing
	else {
		int index = item.code() % _size;
		// counter for quadratic probing
		int collisions = 1;

		// search using quadratic probing
		while (hash_table[index].data.code() != item.code()) {
			index = (item.code() + collisions * collisions) % _size;
			collisions++;
		}
		// mark as empty
		hash_table[index].is_empty = true;
	}

	// decrement the number of items that have been inserted
	_items_inserted--;

	return 1;
}

bool HashTable::empty() const {
	return _items_inserted == 0;
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
