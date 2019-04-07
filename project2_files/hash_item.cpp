
/******************************************************************************
  Title          : hash_item.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 3, 2019
  Description    : Cpp file for hash item
  Purpose        : Implements Hash item
  Usage          :
  Build with     : c++11
********************************************************************************/
#include "hash_item.h"



ItemType::ItemType() {}

void ItemType::set(string, int) {}

void ItemType::get(string &, int &) {}

bool ItemType::operator==(__ItemType rhs) const {}

unsigned int ItemType::code() {}
