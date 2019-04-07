/******************************************************************************
  Title          : hash_item.h
  Author         : Marin Pavlinov
  Created on     : April 3, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     : c++11
********************************************************************************/


#ifndef HASH_ITEM_H
#define HASH_ITEM_H

#include "_hash_item.h"

using namespace std;

class ItemType : public __ItemType
{
public:
    /** ItemType() constructor
     *  Creates an item with given values
     */
    ItemType();

    /** set() sets the item's data
     */
    void set( string, int);

    /** get() retrieves the item's data
     */
    void get( string &, int &);
     

    /** operator==() returns true if given parameter equal item
     *  @precondition: rhs is initialized
     *  @param  __ItemType [in] rhs : item to compare
     *  @return bool 0 if rhs is not equal, 1 if it is.
     */
    bool operator==( __ItemType rhs) const;

    /** code() returns an unsigned integer for the item
     *  @note Every item, regardless of its key type, should be mapped
     *        to a positive integer value. If the key is a string, this should
     *        assign a number to the string. If it is a number already, this
     *        has the option to assign a different number.
     *  @precondition: item is initialized
     *  @return unsigned int
     */
    unsigned int code();

private:
  /* You must fill in the private part */
};







#endif /* __HASH_ITEM_H__ */
