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

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

#include "hash_table.h"
using namespace std;




int main( int argc, char* argv[])
{

    ifstream        inputfile;
    string          str;
    ostringstream   strstream;
    int             result;
    int             num_inserted;
    HashTable       hashtable(2000);
    __ItemType      item;
    
    if ( argc < 2 ) {
        cerr << "usage: " << argv[0] << " filename\n";
        exit(1);
    }

    inputfile.open(argv[1]);
    
    if ( inputfile.fail() ) {
        cerr << "Could not open " << argv[1] << " for reading.\n";
        exit(1);
    }
    
    // Read each line from the input file, construct an item with the
    // string from that line and an integer equal to the item's line
    // number.
    num_inserted = 0;
    while ( getline(inputfile, str) ) {
        num_inserted++;
        // strstream contains the string just read
        strstream.str(str);

        // set item's string to it, with int num_inserted 
        item.set(strstream.str(),num_inserted);  

        // insert into hash and check if successful
        result = hashtable.insert(item);
        if ( 0 == result ) {
            num_inserted--;  // decrement so that it counts how many were inserted
        }
    }

    // Display all items stored in the hash table (using a method not in the
    // abstract interface
    int count = hashtable.listall(cout);

    // and print how many were displayed
    cout << count << " items were stored  in the hash table\n";

    // Check that size function is correct.
    cout << hashtable.size() << " is reported size of hash table.\n";

    // error check - if the number displayed is not the same as the number
    // stored, something is wrong
    if ( count != num_inserted ) {
        cout << "number of items displayed is not equal to number in table.\n";
    }

    // now check how the find and remove functions work
    
    while ( 1 ) {
       cout << "Enter 'f', to find, 'r' to remove, or 'q' to quit: ";
       getline(cin,str);
       if ( str == "f" ) {
           cout << "Enter item key:";
           getline(cin,str);
           item.set( str);
           result = hashtable.find(item);
           if ( result )
               cout << str << " is in the table\n";
           else
               cout << str << " is not in the table\n";
       }
       else if ( str == "r" ) {
           cout << "Enter item key:";
           getline(cin,str);
           item.set( str);
           result = hashtable.remove(item);
           if ( result )
               cout << str << " was removed from the table\n";
           else
               cout << str << " is not in the table\n";
           cout << " Table size is " << hashtable.size() << "\n.";
       }
       else if ( str == "q" )
           break;
    }
    return 0;
}
