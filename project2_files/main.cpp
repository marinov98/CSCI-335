/******************************************************************************
  Title          : main.cpp
  Author         : Stewart Weiss
  Created on     : April  6, 2019
  Description    : Driver for testing hash table implementation
  Purpose        : To exercise hash table for testing
  Usage          : main  <file containing strings of any kind>
  Build with     : g++ -Wall -g -o main main.cpp hash_table.cpp _hash_item.cpp
  Modifications  :

  License        :
    Copyright (c) 2019 Stewart Weiss

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.


*******************************************************************************/

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <stdlib.h>
#include <string>

#include "hash_table.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream inputfile;
	string str;
	ostringstream strstream;
	int result;
	int num_inserted;
	HashTable hashtable(197);
	__ItemType item;

	if (argc < 2) {
		cerr << "usage: " << argv[0] << " filename\n";
		exit(1);
	}

	inputfile.open(argv[1]);

	if (inputfile.fail()) {
		cerr << "Could not open " << argv[1] << " for reading.\n";
		exit(1);
	}

	// inputfile.open("othertest.txt");

	// Read each line from the input file, construct an item with the
	// string from that line and an integer equal to the item's line
	// number.

	num_inserted = 0;
	//	item.set("cock");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("vagina");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("kcock");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("lol");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("cokck");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("ajani");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("inaja");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("see");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("the");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("sun");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("around");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("the fire");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("in");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("this");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("gayyy");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("ayyye");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("yyyag");
	//	hashtable.insert(item);
	//	item.set("skadush");
	//	hashtable.insert(item);
	//	item.set("babush");
	//	hashtable.insert(item);
	//	item.set("einseint");
	//	hashtable.insert(item);
	//	item.set("yako");
	//	hashtable.insert(item);
	//	item.set("ayko");
	//	hashtable.insert(item);
	//	item.set("maiko");
	//	hashtable.insert(item);
	//	item.set("akyo");
	//	hashtable.insert(item);
	//	item.set("koay");
	//	hashtable.insert(item);
	//	item.set("koay");
	//	hashtable.insert(item);
	//	item.set("einstein");
	//	hashtable.insert(item);
	//	item.set("sum");
	//	hashtable.insert(item);
	//	item.set("fak");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("kaf");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("akf");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("askuid");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("weiss");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("ajani");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("naj");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("neshasnite");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("zheni");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("v");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("skupite");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("koli");
	//	hashtable.insert(item);
	//	num_inserted++;
	//	item.set("ykoa");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("obichash");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("kio");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("miom");
	//	num_inserted++;
	//	hashtable.insert(item);
	//	item.set("akyo");
	//	hashtable.insert(item);
	//	item.set("koay");
	//	hashtable.insert(item);
	//	item.set("ykoa");
	//	hashtable.insert(item);
	//	item.set("einstein");
	//	item.set("koya");
	//	hashtable.insert(item);
	//	item.set("yako");
	//	hashtable.insert(item);
	//	item.set("ayko");
	//	hashtable.insert(item);
	//	item.set("maiko");
	//	hashtable.insert(item);
	//	item.set("akyo");
	//	hashtable.insert(item);
	//	item.set("koay");
	//	hashtable.insert(item);
	//	item.set("koay");
	//	hashtable.insert(item);
	//	item.set("einstein");
	//	hashtable.insert(item);
	//	item.set("sum");
	//	hashtable.insert(item);
	//	item.set("moe");
	//	hashtable.insert(item);
	//	item.set("meo");
	//	hashtable.insert(item);
	//	item.set("hoe");
	//	hashtable.insert(item);
	//	item.set("toe");
	//	hashtable.insert(item);
	//	item.set("eto");
	//	hashtable.insert(item);
	//	item.set("zaeto");
	//	hashtable.insert(item);
	//	item.set("zeb");
	//	hashtable.insert(item);
	//	item.set("ebz");
	//	hashtable.insert(item);
	//	item.set("ezb");
	//	hashtable.insert(item);
	//	item.set("bez");
	//	hashtable.insert(item);
	//
	//	item.set("mus");
	//	hashtable.insert(item);
	//	item.set("povqrvai");
	//	hashtable.insert(item);
	//	item.set("mi");
	//	hashtable.insert(item);
	//	item.set("shte");
	//	hashtable.insert(item);
	//	item.set("vidish");
	//	hashtable.insert(item);
	//	item.set("ti");
	//	hashtable.insert(item);
	//	item.set("jivotut");
	//	hashtable.insert(item);
	//	item.set("kolko");
	//	hashtable.insert(item);
	//	item.set("silno");
	//	hashtable.insert(item);
	//	item.set("ydrya");
	//	hashtable.insert(item);
	//	item.set("bez");
	//
	//	item.set("shte");
	//	hashtable.insert(item);
	//	item.set("kke");
	//	hashtable.insert(item);
	//	item.set("vi");
	//	hashtable.insert(item);
	//	item.set("eba");
	//	hashtable.insert(item);
	//	item.set("maikata");
	//	hashtable.insert(item);
	//	item.set("vi");
	//	hashtable.insert(item);
	//	item.set("shibana");
	//	hashtable.insert(item);
	//	item.set("koqto");
	//	hashtable.insert(item);
	//	item.set("bad");
	//	hashtable.insert(item);
	//	item.set("dum ");
	//	hashtable.insert(item);
	//	item.set("dzum");
	//	cout << hashtable.find(item) << '\n';
	while (getline(inputfile, str)) {
		num_inserted++;
		// strstream contains the string just read
		strstream.str(str);

		// set item's string to it, with int num_inserted
		item.set(strstream.str(), num_inserted);

		// insert into hash and check if successful
		result = hashtable.insert(item);
		if (0 == result) {
			num_inserted--; // decrement so that it counts how many were inserted
		}
	}

	// Display all items stored in the hash table (using a method not in the
	// abstract interface

	//	item.set("HI");
	//	hashtable.insert(item);
	//
	//	item.set("bye");
	//	hashtable.insert(item);
	//
	//	item.set("kobra");
	//	hashtable.insert(item);
	//
	//	item.set("kai");
	//	hashtable.insert(item);
	//
	int count = hashtable.listall(cout);

	// and print how many were displayed
	cout << count << " items were stored  in the hash table\n";

	// Check that size function is correct.
	cout << hashtable.size() << " is reported size of hash table.\n";

	// error check - if the number displayed is not the same as the number
	// stored, something is wrong
	if (count != num_inserted) {
		cout << "number of items displayed is not equal to number in table.\n";
	}

	// now check how the find and remove functions work
	// item.set("eto");
	// hashtable.insert(item);
	// int x = hashtable.find(item);
	// cout << x << " me!" << '\n';
	while (true) {
		cout << "Enter 'f', to find, 'r' to remove, or 'q' to quit: ";
		getline(cin, str);
		if (str == "f") {
			cout << "Enter item key:";
			getline(cin, str);
			item.set(str);
			result = hashtable.find(item);
			if (result)
				cout << str << " is in the table\n";
			else
				cout << str << " is not in the table\n";
		}
		else if (str == "r") {
			cout << "Enter item key:";
			getline(cin, str);
			item.set(str);
			result = hashtable.remove(item);
			if (result)
				cout << str << " was removed from the table\n";
			else
				cout << str << " is not in the table\n";
			cout << " Table size is " << hashtable.size() << "\n.";
		}
		else if (str == "q")
			break;
	}

	return 0;
}
