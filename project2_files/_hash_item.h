/******************************************************************************
  Title          : _hash_item.h
  Author         : Stewart Weiss
  Created on     : March 31, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     :
  Modifications  :
     4/4/2019 by SW


******************************************************************************/

#ifndef __HASH_ITEM_H__
#define __HASH_ITEM_H__

#include <string>
#include <iostream>

using namespace std;

class  __ItemType
{
public:
    /** ItemType() constructor
     *  Creates an item with given values
     */
    __ItemType();

    /** set() sets the item's data
     */
    void set(string s, int pos = -1) ;

    /** get() retrieves the item's data
     */
    void get(string & s, int & pos);


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

    /** operator<<() 
     *  @precondition: none
     *  @param  
     *  @return 
     */
    friend ostream&  operator<<(ostream& os, __ItemType item);


private:
    string name;
    int    position;

};







#endif /* __HASH_ITEM_H__ */

