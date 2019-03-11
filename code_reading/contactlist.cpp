#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "contactlist.h"

using namespace std;


/******************************************************************************
                               Helper Functions
 *****************************************************************************/

bool ContactList::insert_at( NodePtr & prev, Contact new_item )
{
    NodePtr tmpPtr = new Node;
    if ( tmpPtr == NULL )
        return false;

    tmpPtr->item = new_item;
    tmpPtr->next = prev;
    prev = tmpPtr;
    return true;   
}

/*****************************************************************************/

ContactList::ContactList(char* clfile)
{
    ifstream fin;
    char line[512];
    Contact temp;

    num_items = 0;
    head = NULL;
    strcpy(clfile_pathname, clfile);

    fin.open(clfile);
    if ( fin.fail()) {
        throw "error";
    }
    while ( !fin.eof()  ) {
        fin.getline(line, 511);
        if ( fin.bad()  )
            throw "error";
         else  if ( 0 == temp.set(line)  )
            continue;
        else {
            insert(temp);
        }
    }
}

ContactList::~ContactList()
{
    make_empty();
}

void  ContactList::find_by_lname (ostream & output,
                          string lname) const
{
    NodePtr current;
    Name    tempname;

    if ( NULL == head )
        return;

    current  = head;
    while ( current != NULL ) {
        current->item.get_name(tempname);
        if ( tempname.last() < lname ) {
            current = current->next;
        }
        else if ( tempname.last() > lname ) {
            return;
        }
        else  { 
            output << current->item;
            current = current->next;
        }
    }
}

void  ContactList::find_by_fname (ostream & output,
                          string fname) const
{
    NodePtr current;
    Name    tempname;
    
    if ( NULL == head )
        return;
    
    current  = head;
    while ( current != NULL ) {
        current->item.get_name(tempname);
        if ( tempname.first() != fname ) {
            current = current->next;
        }
        else { 
            output << current->item;
            current = current->next;
        }
    }
}

void  ContactList::find (ostream & output, Contact  record_to_find ) const
{
    NodePtr current;

    if ( NULL != head ) {
        current = head;
        while ( current != NULL && !(current->item > record_to_find)) {
            if ( match(current->item, record_to_find) ) {
                output << current->item << "\n";
            }
            current = current->next;
        }
    }
}

int ContactList::remove( Contact item )
{
    NodePtr current;
    NodePtr prev;
    int     count = 0;

    
    if ( NULL != head ) {
        current = head;
        prev = NULL;
        while ( current != NULL ) {
            if ( match(current->item, item) ) {
                if ( NULL == prev ) {
                    head = current->next;
                    current->next = NULL;
                    delete current;
                    current = head;
                    count++;
                }
                else {
                    current = current->next;    
                    prev->next->next = NULL;    
                    delete prev->next;          
                    prev->next = current;       
                    count++;
                }
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    }
    num_items -= count;
    return count;
}


int ContactList::insert( Contact new_item)
{
    NodePtr current, previous;
    bool success = false;
    
    if ( NULL == head || head->item > new_item ) {
        success = insert_at( head, new_item);
        if (success)
            num_items++;
        return 1;
    }

    if ( head->item == new_item ) 
        
        return 0;

    previous = head;       
    current  = head->next;
    while ( current != NULL && !success ) {
        if ( current->item < new_item ) { 
            previous = current;
            current = current->next;
        } 
        else if ( current->item > new_item ) {
            if ( (success = insert_at(previous->next, new_item)) )
                num_items++;
            return 1;
        }
        else  
            return 0;
    }    
    
    if ( (success = insert_at(previous->next, new_item)) )
        num_items++;
    return 1;
}   

int   ContactList::insert  (ContactList contact_list)
{
    NodePtr current = contact_list.head;
    int count = 0;

    while ( current != NULL ) {
        count += insert(current->item);
        current = current->next;
    }
    return count;
}

void  ContactList::display ( ostream & output) const
{
    NodePtr current = head;
    while ( current != NULL)  {
        cout << current->item << "\n";
        current = current->next;
    }
}

int ContactList::size() const
{
    return num_items;
}

int ContactList::make_empty()
{
    NodePtr temp_ptr;
    
    for ( int i = 1; i <= num_items; i++){
        temp_ptr = head;
        head = head->next;
        temp_ptr->next = NULL;
        delete temp_ptr;
    }
    return 1;
}

int ContactList::save() const
{
    ofstream fout;
    char    backupfile[512];
    char    syscmmd[256];
    int     count = 0;
    
    sprintf(backupfile, "%s.%s", clfile_pathname,"bkp");
    sprintf(syscmmd, "mv -f %s %s", clfile_pathname, backupfile );
    if ( system (syscmmd ) < 0 )
        return -1;

    fout.open(clfile_pathname);
    if ( fout.fail() )
        return -2;

    NodePtr current = head;

    while ( current != NULL)  {
        fout << current->item.convert2csv() << "\n";
        current = current->next;
        count++;
    }
    fout.close();
    return count;
}
