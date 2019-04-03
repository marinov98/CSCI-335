/******************************************************************************
  Title          : _hash_table.h
  Author         : Stewart Weiss
  Created on     : March 31, 2019
  Description    : Interface description for a hash table class
  Purpose        : To define the minimal requirements of a hash table
  Usage          : Derive a concrete hash table class from this interface
  Build with     : no building
  Modifications  :

******************************************************************************/
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__


#include "_hash_item.h"

// The INITIAL_SIZE should be large enough that it will not need to be
// resized, but you might want to implement resizing in your class.
#define INITIAL_SIZE 4096

class ItemType : public __ItemType
{
   // to be completed by you
}

class __HashTable
{
public:
    /** __HashTable() constructor
     *  Creates a hash table of the specified size
     *  @param int [in] initial_size : size to create, defaults to INITIAL_SIZE
     */
    __HashTable(int initial_size = INITIAL_SIZE );

    /** find() searches in table for given item
     *  @precondition: item's key value is initialized
     *  @postcondition: if matching item is found, it is filled with value from
     *                  table.
     *  @param  ItemType [in,out] item : item to search for
     *  @return int 0 if item is not in table, and 1 if it is
     */
    virtual int find   ( ItemType & item ) const = 0;

    /** insert() inserts the given item into the table
     *  @precondition: item is initialized
     *  @postcondition: if item is not in table already, it is inserted
     *  @param  ItemType [in] item : item to insert
     *  @return int 0 if item is not inserted in table, and 1 if it is
     */
    virtual int insert ( ItemType item   ) = 0;

    /** remove() removes the specified  item from the table, if it is there
     *  @precondition: item's key is initialized
     *  @postcondition: if item was in table already, it is removed and copied
     *                  into the parameter, item
     *  @param  ItemType [in, out] item : item to remove
     *  @return int 0 if item is not removed from the table, and 1 if it is
     */
    virtual int remove ( ItemType & item ) = 0;


    /** size() returns the number of items in the table
     *  @precondition: none
     *  @postcondition: none
     *  @return int the number of items in the table
     */
    virtual int size() const = 0;

};



#endif /* __HASH_TABLE_H__ */

