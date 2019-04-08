
/******************************************************************************
  Title          : hash_item.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 3, 2019
  Description    : Cpp file for hash item
  Purpose        : Implements Hash item
  Usage          :
  Build with     : c++11
********************************************************************************/
#include "_hash_item.h"



__ItemType::__ItemType() {
    this->name = "";
    this->position = 0;
}

void __ItemType::set(string s, int pos) {
    this->name = s;
    this->position = pos;
}



void __ItemType::get(string& s, int& pos) {
    s = this->name;
    pos = this->position;
}
 
bool __ItemType::operator==(__ItemType rhs) const {
    if (rhs.name != "") {
	if (rhs.name == this->name)
	    return 1;
    }
    
    return 0;	
}

unsigned int __ItemType::code() {
    // initialize return type
    unsigned int assigned_position = 0;

    if (this->name != "") {
	// adds an extra number to create more unique positions
	int precedence = 4;

	for (const char c : this->name) {
	    // assign number to string 
	    assigned_position += (int)c * (precedence * precedence);
	    precedence *= 3;
	}
    }
    
    return assigned_position;
}

ostream& operator<<(ostream& os, __ItemType item) {
    os << "name: " << item.name << " position: " << item.position << '\n';

    return os;
}
