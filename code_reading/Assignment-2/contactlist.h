#ifndef __CONTACTLIST_H__
#define __CONTACTLIST_H__

#include <iostream>
#include "name.h"
#include "contact.h"

using namespace std;

class ContactList;

typedef class Node*  NodePtr;
class Node
{
    Contact  item;
    NodePtr  next;
    friend class ContactList;
};


class ContactList
{
public:
    ContactList(char* clfile) ;
    ~ContactList();

    void  display       (ostream & output) const;
    int   insert        (Contact record_to_insert);
    int   insert        (ContactList contact_list);
    int   remove        (Contact record_to_delete);
    int   size          () const;
    int   save          () const;
    void  find_by_lname (ostream & output, string lname) const;
    void  find_by_fname (ostream & output, string fname) const;
    void  find (ostream & output, Contact  record_to_find ) const;
    int   make_empty    ();

private:
    NodePtr   head;
    int       num_items;
    char      clfile_pathname[512];

    bool      find( Contact item, NodePtr & where );
    bool      insert_at( NodePtr & prev, Contact new_item );
   
};


#endif /* __CONTACTLIST_H__ */


