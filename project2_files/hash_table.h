
/******************************************************************************
  Title          : hash_item.h
  Author         : Marin Pavlinov Marinov
  Created on     : April 3, 2019
  Description    : Inherits from the _hash_table interface
  Purpose        : header for the _hash_table class
  Usage          :
  Build with     : c++11
********************************************************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "_hash_table.h"
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

// struct to help implement deletion without using getters and setters
struct Item {
	__ItemType data;
	// true if item is empty or deletion occured, false if iposition is filled
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
	HashTable(int size);

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
	 move constructor throws pre:nothing

	    post: safely transfers contents of other table over to current table
	    and sets the other table to point to nullptr when finished
	*/
	HashTable(HashTable&& other_table) noexcept;

	// Move assignment operator:
	/*
	 *  NOTE: similarly to the move constructor, noexcept is used to let the library know it can
	 move

	    pre: objects are not equal

	    post: deletes current hashtable and moves the contents of other table
	    to the current and points the other table to nullptr after all data is transfered
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
	int find(__ItemType& item) const;

	/** insert() inserts the given item into the table
	 *  @precondition: item is initialized
	 *  @postcondition: if item is not in table already, it is inserted
	 *  @param  ItemType [in] item : item to insert
	 *  @return int 0 if item is not inserted in table, and 1 if it is
	 */
	int insert(__ItemType item);

	/** remove() removes the specified  item from the table, if it is there
	 *  @precondition: item's key is initialized
	 *  @postcondition: if item was in table already, it is removed and copied
	 *                  into the parameter, item
	 *  @param  ItemType [in, out] item : item to remove
	 *  @return int 0 if item is not removed from the table, and 1 if it is
	 */
	int remove(__ItemType item);

	/** size() returns the number of items in the table
	 *  @precondition: none
	 *  @postcondition: none
	 *  @return int the number of items in the table
	 */
	int size() const;

	/** listall() lists all items currently in the table
	 *  @note   This function writes each item in the tabel onto the given stream.
	 *          Items should be written one per line, in whatever format the
	 *          underlying _ItemType output operator formats them.
	 *  @param  ostream [in,out] the stream onto which items are written
	 *  @return int the number of items written to the stream
	 */
	int listall(ostream& os) const;

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
	bool is_prime(int number);

	/*
	    function that gets the next prime number assuming number is not already prime
	    pre: nothing

	    post: returns the next bigger prime number
	 */
	int get_next_prime(int start);

	// function to resize table if needed
	/*
	    pre: table is more than half empty
	    post: items are reinserted into a table with double the size of the previous one
	 */
	void resize();

	/*
	    variable used to keep track of the total size of the hashtable
	    * IMPORTANT: the _size variable is only doubled when table is half empty
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

#endif /* __HASH_TABLE_H__ */
