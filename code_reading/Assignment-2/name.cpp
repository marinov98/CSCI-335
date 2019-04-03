#include "name.h"
#include "iomanip"


Name::Name ( string first_name, string last_name):
                fname(first_name), lname(last_name) {}

ostream& operator<< ( ostream& os, Name name )
{
    os << setw(MAXLENGTH) << left;
    os << name.fname << setw(MAXLENGTH) << left << name.lname;
    return os;
}


string Name::first() const
{
    return fname;
}

string Name::last()  const
{
    return lname;
}

void Name::set_first( string first )
{
    if ( first.length() <= MAXLENGTH  &&
         first.npos ==  first.find_first_not_of(NAME_CHARS)  )
            fname = first;
    else {
        fname = "";
        throw(Errors::InvalidName() );
    }
}

void Name::set_last( string last )
{
    if ( last.length() <= MAXLENGTH  &&
        string::npos ==  last.find_first_not_of(NAME_CHARS)  )
            lname = last;
    else {
        lname = "";
        throw(Errors::InvalidName() );
    }
}

bool operator== (Name name1, Name name2 )
{
    if ( name1.lname == name2.lname   &&
           name1.fname == name2.fname
       )
        return true;
    else
        return false;
}


bool operator<  (Name name1, Name name2 )
{
     if ( ( name1.lname < name2.lname ) ||
         ( name1.lname == name2.lname &&
           name1.fname < name2.fname )
       )
        return true;
    else
        return false;
}


bool operator>  (Name name1, Name name2 )
{
    if ( ( name1.lname > name2.lname ) ||
         ( name1.lname == name2.lname &&
           name1.fname > name2.fname )
       )
        return true;
    else
        return false;
}

