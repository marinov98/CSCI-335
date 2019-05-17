
/******************************************************************************
  Title          : hash_table.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 3, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     : c++11
********************************************************************************/
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

// struct to help implement deletion without using getters and setters
struct Item {
	__ItemType data;
	// true if item is empty or deletion occurred, false if position is filled
	bool is_empty = true;
};

// The INITIAL_SIZE should be large enough that it will not need to be
// resized, but you might want to implement resizing in your class.
#define INITIAL_SIZE 4096

class HashTable : public __HashTable {
  public:
	// constructor needed to initialize values
	HashTable();

	// constructor for table with specified size
	explicit HashTable(int size);

	// copy constructor
	/*
	    pre: nothing

	    post: total size and current size are copied to current table
	    into current hashtable object. Memory allocated in accordance with other table's size
	    contents of other table are copied byte by byte into the current table
	*/
	HashTable(const HashTable& other_table);

	// copy assignment operator
	/*
	    pre: objects are not equal

	    post: allocate space in current table in accordance to other table's size
	    and copy the contents of other_table over to current object file
	*/
	HashTable& operator=(const HashTable& other_table);

	// move constructor
	/*
	 *  NOTE: I use noexcept because standard containers disable moves if the contained object's
	 *  move constructor throws

	    pre: nothing

	    post: safely transfers contents of other table over to current table
	    and sets the other table to point to nullptr when finished
	*/
	HashTable(HashTable&& other_table) noexcept;

	// Move assignment operator:
	/*
	 *  NOTE: similar reason as above , noexcept is used to let the library know it can move

	    pre: nothing

	    post: deletes current hashtable and moves the contents of other table
	    to the current and points the other table to nullptr after all data is transferred
	*/
	HashTable& operator=(HashTable&& other_table) noexcept;

	// destructor to delete hashtable when it is no longer in use
	~HashTable();

	/** find() searches in table for given item
	 *  @precondition: item's key value is initialized
	 *  @postcondition: if matching item is found, it is filled with value from
	 *                  table.
	 *  @param  ItemType [in,out] item : item to search for
	 *  @return int 0 if item is not in table, and 1 if it is
	 */
	int find(const __ItemType& item) const override;

	/** insert() inserts the given item into the table
	 *  @precondition: item is initialized
	 *  @postcondition: if item is not in table already, it is inserted
	 *  @param  ItemType [in] item : item to insert
	 *  @return int 0 if item is not inserted in table, and 1 if it is
	 */
	int insert(const __ItemType& item) override;

	/** insert() inserts the given item into the table
	 *  @pre: item is initialized
	 *  @post: if item is not in table already, it is inserted
	 *  @param:  rvalue item : temporary object to be inserted
	 *  @return int 0 if item is not inserted in table, and 1 if it is
	 */
	int insert(__ItemType&& item);

	/** remove() removes the specified  item from the table, if it is there
	 *  @precondition: item's key is initialized
	 *  @postcondition: if item was in table already, it is removed and copied
	 *                  into the parameter, item
	 *  @param  ItemType [in, out] item : item to remove
	 *  @return int 0 if item is not removed from the table, and 1 if it is
	 */
	int remove(const __ItemType& item) override;

	/** size() returns the number of items in the table
	 *  @precondition: none
	 *  @postcondition: none
	 *  @return int the number of items in the table
	 */
	int size() const override;

	/*
	 * pre: nothing
	 *
	 * post: returns true if table is empty, false if its not
	 */
	bool empty() const;

	/** listall() lists all items currently in the table
	 *  @note   This function writes each item in the tabel onto the given stream.
	 *          Items should be written one per line, in whatever format the
	 *          underlying _ItemType output operator formats them.
	 *  @param  ostream [in,out] the stream onto which items are written
	 *  @return int the number of items written to the stream
	 */
	int listall(ostream& os) const override;

  private:
	/*
	    Purpose of the next two functions:
	    I want to use quadratic probing, to do this I must ensure that:
	        i) the table size is always prime
	        ii) Table is always at least half empty
	 */

	/*
	    function that checks if the number is prime
	    pre: nothing
	    post: true if its prime, false if its not prime
	 */
	bool is_prime(int number) const;

	/*
	    function that gets the next prime number assuming number is not already prime
	    pre: nothing

	    post: returns the next prime number
	    if input is already prime, the function does not do anything
	 */
	int get_next_prime(int start) const;

	// function to resize table if needed
	/*
	    pre: table is more than half empty
	    post: items are reinserted into a table with double the size of the previous one
	 */
	void rehash();

	/*
	    variable used to keep track of the total size of the hashtable
	    * IMPORTANT: the _size variable is only doubled when table is less than half empty
	    otherwise it stays as it is during insertion and removal
	    _items inserted is what keeps track of how many items are left in the table
	*/
	int _size;

	/*
	    keep track of how many items have been inserted
	    Also lets the table know when it is not half empty and
	    needs to be resized
	*/
	int _items_inserted;

	// actual hash table
	Item* hash_table;
};



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
	HashTable newTable(get_next_prime(_size * 2));

	// re-insert all items into the new table
	for (int i = 0; i < _size; i++) {
		if (!hash_table[i].is_empty)
			newTable.insert(move(hash_table[i].data));
	}

	/*
	    utilize our move assignment operator to safely transfer the data
	    from the new temporary table object to our current table object
	*/
	*this = move(newTable);
}

int HashTable::find(const __ItemType& item) const {
	// item not initialized or table is empty
	if (0 == item.code() || empty())
		return 0;

	int index;
	int next_index;
	int collisions = 0;
	// quadratic probing
	while (collisions != _size) {
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

int HashTable::insert(const __ItemType& item) {
	// index is already in the table or not initialized
	if (0 == item.code() || 1 == find(item))
		return 0;

	/*
	    while loop will execute once if a free spot is found right away
	    other wise it will iterate at most n times where n is the size
	*/
	int index;
	int collisions = 0;
	while (collisions != _size) {
		index = (item.code() + collisions * collisions) % _size;

		if (this->hash_table[index].is_empty) {
			// insert into first empty slot and increment items inserted
			this->hash_table[index].data = item;
			this->hash_table[index].is_empty = false;
			_items_inserted++;
			break;
		}

		collisions++;
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
	int collisions = 0;
	while (collisions != _size) {
		index = (item.code() + collisions * collisions) % _size;

		if (this->hash_table[index].is_empty) {
			// MOVE contents of item and insert into table
			this->hash_table[index].data = move(item);
			this->hash_table[index].is_empty = false;
			_items_inserted++;
			break;
		}

		collisions++;
	}

	// resize table if its not half empty anymore
	if (_items_inserted > (_size / 2))
		rehash();

	return 1;
}

int HashTable::remove(const __ItemType& item) {
	// if item is not found in the table, no need to delete
	if (0 == find(item))
		return 0;

	int index;
	int collisions = 0;
	while (collisions != _size) {
		index = (item.code() + collisions * collisions) % _size;

		if (this->hash_table[index].data == item && !this->hash_table[index].is_empty) {
			// mark as empty
			this->hash_table[index].is_empty = true;
			// decrement the number of items that have been inserted
			_items_inserted--;
			break;
		}

		collisions++;
	}

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
