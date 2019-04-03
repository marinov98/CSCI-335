/******************************************************************************
  Title          : _hash_item.h
  Author         : Stewart Weiss
  Created on     : March 31, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#ifndef __HASH_ITEM_H__
#define __HASH_ITEM_H__

class __ItemType
{
public:
    /** ItemType() constructor
     *  Creates an item with given values
     */
    __ItemType();


    /** operator==() returns true if given parameter equal item
     *  @precondition: rhs is initialized
     *  @param  __ItemType [in] rhs : item to compare
     *  @return bool 0 if rhs is not equal, 1 if it is.
     */
    bool operator==(__ItemType rhs) const;
};


#endif /* __HASH_ITEM_H__ */

