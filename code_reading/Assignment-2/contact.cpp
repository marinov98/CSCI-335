#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "name.h"
#include "iomanip"

#define DIGITS "0123456789"

Contact::Contact (): name("",""), telephone(""), email("") {}

Contact::Contact (Name person, string tel_num, string email_addr):
name(person), telephone(tel_num), email(email_addr) {}

int  Contact::set (string fname,
        string lname,
        string tel_num,
        string email_addr)
{
    name.set_first(fname);
    name.set_last(lname);
    telephone = tel_num;
    email = email_addr;
 
    return 1;

}

int Contact::set ( char* csv_string)
{
    char lname[33];
    char fname[33];
    char tel_num[11];
    char email_addr[128];
    char user[128];
    char domain[128];
    int count;

    count = sscanf(csv_string,
            "%32[a-zA-Z'-],%32[a-zA-Z'-],%10[0-9],%127s",
            fname, lname, tel_num, email_addr );
    if ( count < 4 ) {
        return 0;
    }
    else if ( strlen(tel_num) < 10 )
        return 0;
    else {
        name.set_first(fname);
        name.set_last(lname);
        telephone = tel_num;
        count = sscanf(email_addr,"%[^@]@%[a-zA-Z0-9.]",user, domain);
        if ( count < 2 )
            return 0;
        else {
            email = email_addr;
            return 1;
        }
    }

}

void Contact::get_name (Name & fullname)
{
    fullname.set_first(name.first());
    fullname.set_last(name.last());
}

void Contact::get_tel (string & tel_num)
{
    tel_num = telephone;
}

void Contact::get_email (string & email_addr)
{
    email_addr = email;
}

void Contact::set_name (Name fullname)
{
    name.set_first(fullname.first());
    name.set_last(fullname.last());
}


void Contact::set_tel (string tel_num)
{
    telephone = tel_num;
}



void Contact::set_email (string email_addr)
{
    email = email_addr;
}


bool operator> (Contact contact1, Contact contact2)
{
    return ( contact1.name > contact2.name );
}

bool operator<  (Contact contact1, Contact contact2)
{
    return ( contact1.name < contact2.name );
}

bool operator== (Contact contact1, Contact contact2)
{
    return ( contact1.name == contact2.name );
}

ostream& operator<< (ostream & out, Contact contact )
{
    out << contact.name << setw(12)
            << contact.telephone << setw(127)
            << contact.email << "\n";
    return out;
}

string Contact::convert2csv     ()
{
    char  csv[512];

    sprintf(csv, "%s,%s,%s,%s", name.first().c_str(), name.last().c_str(),
            telephone.c_str(), email.c_str());
    return csv;
}

bool match  (Contact contact1, Contact contact2)
{
    if ( contact1.name.last() != ""  && contact2.name.last() != "" ) {
        if ( contact1.name.last() != contact2.name.last() )
            return false;
    }

    if (contact1.name.first() != "" && contact2.name.first() != "") {
        if ( contact1.name.first() != contact2.name.first() )
            return false;
    }

    if (contact1.telephone != "" && contact2.telephone != "") {
        if ( contact1.telephone != contact2.telephone )
            return false;
    }

     if (contact1.email != "" && contact2.email != "") {
        if ( contact1.email != contact2.email )
            return false;
    }

    return true;
}


bool Contact::is_valid_telephone(string tel) const
{
    if ( tel.npos ==  tel.find_first_not_of(DIGITS)  )
        return true;
    else
        return false;
}

