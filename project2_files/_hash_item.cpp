
/******************************************************************************
  Title          : _hash_item.cpp
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
	this->name = move(s);
	this->position = move(pos);
}

void __ItemType::get(string& s, int& pos) {
	s = this->name;
	pos = this->position;
}

bool __ItemType::operator==(__ItemType rhs) const {
	if (!rhs.name.empty()) {
		if (rhs.name == this->name)
			return 1;
	}

	return 0;
}

unsigned int __ItemType::code() {
	// initialize return type
	unsigned int string_code = 0;

	if (!this->name.empty()) {
		string_code++; // make sure string code does not begin at 0
		// arbitrary number I chose to use for my hash function, creates more unique keys
		int precedence = 26;

		/*
		    The result of the below for loop is the function: 1 + Σ (ASCII value of char) *
		   precedence^2 where precedence goes from 26 -> (26 + string length - 1)
		*/

		for (const char& c : this->name) {
			// assign number to string
			string_code += (int) c * (precedence * precedence);
			precedence++;
		}
	}

	return string_code;
}

ostream& operator<<(ostream& os, __ItemType item) {
	os << "key: " << item.name << "  position: " << item.position << '\n';

	return os;
}
