#ifndef __NAME_H__
#define __NAME_H__

#include <iostream>
#include <string>
using namespace std;


#define MAXLENGTH 12
#define NAME_CHARS  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-'"

namespace Errors
{
    struct InvalidName { };
}

class Name
{
public:
    Name        ( string first_name = "", string last_name = "");
    string first() const;
    string last()  const;
    void   set_first( string fname );
    void   set_last( string lname);
    friend ostream& operator<< ( ostream & os, Name name );
    friend bool operator== (Name name1, Name name2 );
    friend bool operator<  (Name name1, Name name2 );
    friend bool operator>  (Name name1, Name name2 );
private:
    string fname;
    string lname;
};

#endif /* __NAME_H__ */



