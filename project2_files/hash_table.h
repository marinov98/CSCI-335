
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

#include <string>
#include "hash_item.h"

using namespace std;


// The INITIAL_SIZE should be large enough that it will not need to be
// resized, but you might want to implement resizing in your class.
#define INITIAL_SIZE 4096



class HashTable : public __HashTable
{
public:

    /** find() searches in table for given item
     *  @precondition: item's key value is initialized
     *  @postcondition: if matching item is found, it is filled with value from
     *                  table.
     *  @param  ItemType [in,out] item : item to search for
     *  @return int 0 if item is not in table, and 1 if it is
     */
    int find ( __ItemType & item ) const;

    /** insert() inserts the given item into the table
     *  @precondition: item is initialized
     *  @postcondition: if item is not in table already, it is inserted
     *  @param  ItemType [in] item : item to insert
     *  @return int 0 if item is not inserted in table, and 1 if it is
     */
    int insert ( __ItemType item   );

    /** remove() removes the specified  item from the table, if it is there
     *  @precondition: item's key is initialized
     *  @postcondition: if item was in table already, it is removed and copied
     *                  into the parameter, item
     *  @param  ItemType [in, out] item : item to remove
     *  @return int 0 if item is not removed from the table, and 1 if it is
     */
    int remove ( __ItemType  item );


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
    int listall ( ostream & os ) const;

};



#endif /* __HASH_TABLE_H__ */
